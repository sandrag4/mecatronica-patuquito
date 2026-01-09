

void inicio_prueba1() {
  long medida1, medida2, medida3;

  servo1_angle = 180;
  HeadServo1.write(servo1_angle);

  delay(2000);

  // medir la distancia 3 veces
  medida1 = ultrasonic_sensor1();
  medida2 = ultrasonic_sensor1();
  medida3 = ultrasonic_sensor1();

  distancia_pared = (medida1 + medida2 + medida3) / 3;

  Serial.print("PRUEBA 1  ----------------------->");
  Serial.println(distancia_pared);

  prueba1_time_start = millis();
}

void prueba1() {
  long distance;
  int time_seconds;

  time_seconds = (millis() - time_start_count) / 1000;

  if (time_seconds >= 1) {
    distance = ultrasonic_sensor1();
    if (abs(distance - distancia_pared) < 2) {
      direccion = RECTO;
      Serial.print("RECTO  -->");
      Serial.println(distance);

    } else if ((distance - distancia_pared) > 2) {
      direccion = GIRO_IZQUIERDA;
      Serial.print("GIRO_IZQUIERDA  -->");
      Serial.println(distance);

    } else if ((distance - distancia_pared) < -2) {
      direccion = GIRO_DERECHA;
      Serial.print("GIRO_DERECHA  -->");
      Serial.println(distance);
    }

    time_start_count = millis();
  }

  controlar_motores();
}
