// TRANSMISSOR (Controle Remoto)
#include <VirtualWire.h>

int pothorizontal = A0;
int potvertical = A1;
int pothelice = A2;
int pottanques = A3;
int botao = 8;

void setup() {
    vw_setup(2000); // Configura a velocidade da comunicação RF (2000 bps)
    vw_set_tx_pin(12); // Define o pino de transmissão (conectado ao módulo RF)
    pinMode(botao, INPUT);
}

void loop() {
    int valHorizontal = analogRead(pothorizontal) / 4;
    int valVertical = analogRead(potvertical) / 4;
    int valHelice = analogRead(pothelice) / 4;
    int valTanques = analogRead(pottanques) / 4;
    int estadoBotao = digitalRead(botao);
    
    char mensagem[20];
    sprintf(mensagem, "%d,%d,%d,%d,%d", valHorizontal, valVertical, valHelice, valTanques, estadoBotao);
    vw_send((uint8_t *)mensagem, strlen(mensagem));
    vw_wait_tx();
    delay(100);
}
