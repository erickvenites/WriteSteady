#include <Arduino.h>

// Pinos dos sensores e botão
const int xPin = A0;
const int yPin = A1;
const int buttonPin = 2;

// Pinos PWM para os motores de vibração
const int vibrationMotorPins[] = {3, 4, 5, 6, 7};
const int numMotors = sizeof(vibrationMotorPins) / sizeof(vibrationMotorPins[0]);

// Variáveis do sistema
bool systemOn = false;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 300;
const int tremorThreshold = 500;

// Buffers de suavização
int xBuffer[5] = {0};
int yBuffer[5] = {0};

void setup() {
  Serial.begin(9600);

  // Configura o botão
  pinMode(buttonPin, INPUT_PULLUP);

  // Configura os pinos dos motores de vibração
  for (int i = 0; i < numMotors; i++) {
    pinMode(vibrationMotorPins[i], OUTPUT);
    analogWrite(vibrationMotorPins[i], 0); // Motores começam desligados
  }
}

int readAverage(int pin, int samples = 5, int delayTime = 2) {
  int total = 0;
  for (int i = 0; i < samples; i++) {
    total += analogRead(pin);
    delay(delayTime);
  }
  return total / samples;
}

int smoothMovement(int newValue, int* buffer, int size) {
  int sum = 0;
  for (int i = 0; i < size - 1; i++) {
    buffer[i] = buffer[i + 1];
    sum += buffer[i];
  }
  buffer[size - 1] = newValue;
  sum += newValue;
  return sum / size;
}

void activateMotors(int intensity) {
  for (int i = 0; i < numMotors; i++) {
    analogWrite(vibrationMotorPins[i], intensity);
  }
}

void loop() {
  // Verifica o estado do botão para alternar o sistema
  if (digitalRead(buttonPin) == LOW && (millis() - lastDebounceTime > debounceDelay)) {
    systemOn = !systemOn;
    lastDebounceTime = millis();
    Serial.println(systemOn ? "Sistema ligado" : "Sistema desligado");
  }

  if (systemOn) {
    int xVal = readAverage(xPin);
    int yVal = readAverage(yPin);

    // Suavização dos valores
    int smoothX = smoothMovement(xVal, xBuffer, 5);
    int smoothY = smoothMovement(yVal, yBuffer, 5);

    // Verifica tremores
    int tremorX = abs(smoothX - 512);
    int tremorY = abs(smoothY - 512);

    if (tremorX > tremorThreshold || tremorY > tremorThreshold) {
      // Calcula intensidade dos motores (baseado no maior tremor)
      int intensity = map(max(tremorX, tremorY), tremorThreshold, 512, 100, 255);
      intensity = constrain(intensity, 0, 255);

      activateMotors(intensity);

      Serial.print("Tremor detectado - Intensidade: ");
      Serial.println(intensity);
    } else {
      activateMotors(0); // Desativa motores se não houver tremores
    }

    delay(50);
  } else {
    activateMotors(0); // Garante que os motores estão desligados
    delay(500);
  }
}
