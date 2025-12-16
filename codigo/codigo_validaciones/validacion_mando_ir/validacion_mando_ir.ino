// Este codigo imprime el codigo hexadecimal correspondiente al boton del mando presionado

#include <IRremote.h>

#define IR_PIN 11


void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);

}

void loop() {
  if (IrReceiver.decode()) {
    unsigned long codigo = IrReceiver.decodedIRData.decodedRawData;
    Serial.print("Código: 0x");
    Serial.println(codigo, HEX);
    IrReceiver.resume();
  }
}
