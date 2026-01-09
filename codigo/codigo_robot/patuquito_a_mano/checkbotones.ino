
// Checkbotones
void checkbotones() {
  // botones
  int boton1_presionado = digitalRead(BOTON_1);
  int boton2_presionado = digitalRead(BOTON_2);

  if (boton1_presionado == 1) {
    if (interrupcion1_start == 0) {
      // se ha empezado a presionar el boton 1
      interrupcion1_start = millis();
    }
  }

  if (boton2_presionado == 1) {
    if (interrupcion2_start == 0) {
      // se ha empezado a presionar el boton 2
      interrupcion2_start = millis();
    }
  }

  if (interrupcion1_start > 0) {
    if ((boton1_presionado == 0) && ((millis() - interrupcion1_start) > t_antirrebote)) {
      interrupcion1_start = 0;
      // Si se presiona el boton 1 durante suficiente tiempo y no estaba en la prueba 1 -> prueba 1
      // si estaba en la prueba 1 -> sale de la prueba 1
      if (state != PRUEBA1) {
        state = PRUEBA1;
        digitalWrite(LED_AZUL, HIGH);
        digitalWrite(LED_AMARILLO, LOW);
        Serial.println("PRUEBA 1");
        inicio_prueba1();
      } else {
        state = INICIO;
        digitalWrite(LED_AZUL, LOW);
      }
    }
  }

  if (interrupcion2_start > 0) {
    if ((boton2_presionado == 0) && ((millis() - interrupcion2_start) > t_antirrebote)) {
      interrupcion2_start = 0;
      // Si se presiona el boton 2 durante suficiente tiempo y no estaba en la prueba 2 -> prueba 2
      // si estaba en la prueba 2 -> sale de la prueba 2
      if (state != PRUEBA2) {
        state = PRUEBA2;
        digitalWrite(LED_AZUL, LOW);
        digitalWrite(LED_AMARILLO, HIGH);
        Serial.println("PRUEBA 2");
        inicio_prueba2();
      } else {
        state = INICIO;
        digitalWrite(LED_AMARILLO, LOW);
      }
    }
  }
}
