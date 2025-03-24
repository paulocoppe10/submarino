// RECEPTOR (Arduino que recebe os comandos)
#include <Servo.h>
#include <VirtualWire.h>

Servo horizontal;
Servo vertical;
int LED = 11;
int motor1 = 6;
int motor2 = 7;
int tanque1 = 12;
int tanque2 = 13;

void setup() {
    horizontal.attach(9);
    vertical.attach(10);
    pinMode(LED, OUTPUT);
    pinMode(motor1, OUTPUT);
    pinMode(motor2, OUTPUT);
    pinMode(tanque1, OUTPUT);
    pinMode(tanque2, OUTPUT);
    vw_setup(2000);
    vw_set_rx_pin(12);
    vw_rx_start();
}

void loop() {
    uint8_t tamanho = 20;
    char mensagem[20];
    if (vw_get_message((uint8_t *)mensagem, &tamanho)) {
        int valHorizontal, valVertical, valHelice, valTanques, estadoBotao;
        sscanf(mensagem, "%d,%d,%d,%d,%d", &valHorizontal, &valVertical, &valHelice, &valTanques, &estadoBotao);

        horizontal.write(map(valHorizontal, 0, 255, 0, 180));
        vertical.write(map(valVertical, 0, 255, 0, 180));

        digitalWrite(motor1, valHelice > 150 ? HIGH : LOW);
        digitalWrite(motor2, valHelice < 100 ? HIGH : LOW);
        digitalWrite(tanque1, valTanques > 150 ? HIGH : LOW);
        digitalWrite(tanque2, valTanques < 100 ? HIGH : LOW);
        analogWrite(LED, estadoBotao ? 255 : 0);
    }
}
