
void movimiento_recto() { // Avanzar recto indeterminadamente
  for(int i=0; i<numMitadServos; i++) { 
    servos[i].write(70);
  }
  for(int i=numMitadServos; i<numServos; i++) {
    servos[i].write(110);
  }
}


void movimiento_retroceder() { // retroceder
  for(int i=0; i<numMitadServos; i++) { 
    servos[i].write(110);
  }
  for(int i=numMitadServos; i<numServos; i++) {
    servos[i].write(70);
  }
}


void movimiento_parar() { // Parar
  for(int i=0; i<numServos; i++) {
    servos[i].write(90); 
  }
}


void movimiento_giro_derecha() { // Girar hacia la derecha
  for(int i=0; i<numServos; i++) {
    servos[i].write(110); 
  }
}


void movimiento_giro_izquierda() { // Girar hacia la izquierda
  for(int i=0; i<numServos; i++) {
    servos[i].write(70); 
  }
}


void movimiento_recto_largo() {
  for (int i=0; i<numServos; i++) {
    vueltas[i] = 0;
  }
  bool todosListos = false;

  while (!todosListos) {
    for(int i=0; i<numServos; i++) { // Girar vueltasRectoLargo
      if(vueltas[i] < vueltasRectoLargo) {
        servos[i].write(110);
      } else {
        servos[i].write(90);
      }
    }

    delay(10);

    for(int i=0; i<numServos; i++) { // Leer feedback y actualizar vueltas
      float angle = readServoPWM(fbPins[i], prevAngle[i]);

      if(angle < 0) angle += 180;   // normaliza a 0-180
      if(prevAngle[i] < 0) prevAngle[i] += 180;

      if(prevAngle[i] > 90 && angle < 90) { // contar vueltas
        vueltas[i]++;
        Serial.print("Servo ");
        Serial.print(i+1);
        Serial.print(" vueltas: ");
        Serial.println(vueltas[i]);
      }
      prevAngle[i] = angle;
    }

    todosListos = true; // Comprobar si todos los servos ya dieron vueltasRectoLargo
    for(int i=0; i<numServos; i++) {
      if(vueltas[i] < vueltasRectoLargo) todosListos = false;
    }
  }
}

void movimiento_giro_90_derecha() {
  for (int i=0; i<numServos; i++){
    vueltas[i] = 0;
  }
  bool todosListos = false;

  while (!todosListos) {
    for(int i=numMitadServos; i<numServos; i++) { // Girar vueltas90Derecha
      if(vueltas[i] < vueltas90Derecha) {
        servos[i].write(110);
        servos[i-3].write(70);
      } else {
        servos[i].write(90);
        servos[i-3].write(90);
      }
    }

    delay(10);

    for(int i=0; i<numServos; i++) { // Leer feedback y actualizar vueltas
      float angle = readServoPWM(fbPins[i], prevAngle[i]);

      if(angle < 0) angle += 180;   // normaliza a 0-180
      if(prevAngle[i] < 0) prevAngle[i] += 180;

      if (i >= numMitadServos) {
        if(prevAngle[i] > 90 && angle < 90) { // contar vueltas
          vueltas[i]++;
          Serial.print("Servo ");
          Serial.print(i+1);
          Serial.print(" vueltas: ");
          Serial.println(vueltas[i]);
        }
      }
      prevAngle[i] = angle;
    }

    todosListos = true; // Comprobar si todos los servos ya dieron vueltas90Derecha
    for(int i=numMitadServos; i<numServos; i++) {
      if(vueltas[i] < vueltas90Derecha) todosListos = false;
    }
  }
}

void movimiento_giro_90_izquierda(){
  for (int i=0; i<numServos; i++) {
    vueltas[i] = 0;
  }
  bool todosListos = false;

  while (!todosListos) {
    for(int i=0; i<numMitadServos; i++) { // Girar vueltas90Izquierda
      if(vueltas[i] < vueltas90Izquierda) {
        servos[i].write(110);
        servos[i+3].write(70);
      } else {
        servos[i].write(90);
        servos[i+3].write(90);
      }
    }

    delay(10);

    for(int i=0; i<numServos; i++) { // Leer feedback y actualizar vueltas
      float angle = readServoPWM(fbPins[i], prevAngle[i]);

      if(angle < 0) angle += 180;   // normaliza a 0-180
      if(prevAngle[i] < 0) prevAngle[i] += 180;

      if (i < numMitadServos) {
        if(prevAngle[i] > 90 && angle < 90) { // contar vueltas
          vueltas[i]++;
          Serial.print("Servo ");
          Serial.print(i+1);
          Serial.print(" vueltas: ");
          Serial.println(vueltas[i]);
        }
      }
      prevAngle[i] = angle;
    }

    todosListos = true; // Comprobar si todos los servos ya dieron vueltas90Izquierda
    for(int i=0; i<numMitadServos; i++) {
      if(vueltas[i] < vueltas90Izquierda) todosListos = false;
    }
  }
}
