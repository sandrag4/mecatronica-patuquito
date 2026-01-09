
// Checkmando
void checkmando() {
  if (IrReceiver.decode()) {
    unsigned long codigo = IrReceiver.decodedIRData.decodedRawData;

    if (codigo == CODIGO_BOTON_1) {
      interrupcion1_start = 0;
      // Si se presiona el boton 1 y no estaba en la prueba 1 -> prueba 1
      if (state != PRUEBA1) {
        state = PRUEBA1;
        digitalWrite(LED_AZUL, HIGH);
        digitalWrite(LED_AMARILLO, LOW);
        Serial.println("PRUEBA 1");
        inicio_prueba1();
      }
    }

    if (codigo == CODIGO_BOTON_2) {
      interrupcion2_start = 0;
      // Si se presiona el boton 2 y no estaba en la prueba 2 -> prueba 2
      if (state != PRUEBA2) {
        state = PRUEBA2;
        digitalWrite(LED_AZUL, LOW);
        digitalWrite(LED_AMARILLO, HIGH);
        inicio_prueba2();
      }
    }

    IrReceiver.resume();
  }
}








