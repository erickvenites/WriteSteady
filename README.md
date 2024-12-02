# WriteSteady

Este projeto implementa um sistema baseado em Arduino para detecção de tremores e ativação de motores de vibração como resposta tátil proporcional à intensidade dos movimentos. Ele utiliza sensores analógicos para medir tremores em dois eixos (X e Y) e processa os dados suavizados para acionar feedback de forma eficiente.

## **Funcionalidades**

- **Detecção de tremores:** Monitora movimentos nos eixos X e Y, suaviza leituras e detecta tremores acima de um limite configurável.
- **Feedback tátil:** Aciona motores de vibração proporcionalmente à intensidade dos tremores detectados.
- **Controle por botão:** Permite ligar e desligar o sistema facilmente, com debounce para evitar acionamentos acidentais.
- **Configuração flexível:** Número de motores, intensidade PWM e limite de detecção podem ser ajustados conforme a necessidade.

## **Componentes utilizados**

- **Arduino**: Microcontrolador para processamento.
- **Sensores analógicos**: Detectam movimentos nos eixos X e Y.
- **Botão**: Alterna o estado do sistema (ligado/desligado).
- **Motores de vibração**: Fornecem feedback tátil.
- **Resistores e outros componentes**: Para montagem do circuito.

## **Como funciona**

1. O botão ativa/desativa o sistema.
2. Quando ativado:
   - Os sensores medem tremores nos eixos X e Y.
   - Os dados são suavizados para reduzir ruídos.
   - Tremores acima do limite configurado acionam os motores com intensidade proporcional.
3. Quando desativado:
   - Os motores permanecem desligados para economia de energia.

## **Configuração do código**

O código pode ser personalizado para atender diferentes aplicações. Principais variáveis ajustáveis:

- `tremorThreshold`: Limite de sensibilidade para detecção de tremores.
- `numMotors`: Quantidade de motores de vibração conectados.
- `vibrationMotorPins[]`: Pinos PWM utilizados para controlar os motores.

## **Diagrama de conexão**

> ![protótipo no tinkercad](<Projeto de Extensão.png>)

## **Instalação**

1. Clone este repositório:
   ```bash
   git clone https://github.com/seu-usuario/nome-do-repositorio.git
   ```
2. Abra o código no Arduino IDE.
3. Conecte seu Arduino ao computador e envie o código para a placa.
4. Monte o circuito conforme o diagrama de conexão.

## **Uso**

1. Ligue o sistema pressionando o botão.
2. Movimente os sensores para gerar tremores nos eixos X e Y.
3. Observe os motores de vibração sendo acionados proporcionalmente à intensidade detectada.

## **Contribuições**

Contribuições são bem-vindas! Sinta-se à vontade para abrir **Issues** ou enviar um **Pull Request**.
