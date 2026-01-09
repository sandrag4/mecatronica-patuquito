

void inicio_prueba2() {
  servo1_angle = 90;
  HeadServo1.write(servo1_angle);

  servo2_angle = 90;
  HeadServo2.write(servo2_angle);

  delay(100);
}


bool check_collision() {
  long distance;

  for (int i = 0; i < 5; i++) {
    servo2_angle = angulos_laser_check[i];
    HeadServo2.write(servo2_angle);
    delay(100);
    distance = ultrasonic_sensor2();
    if (distance < 25) {
      Serial.println("near collision");
      servo2_angle = 90;
      HeadServo2.write(servo2_angle);
      delay(100);
      return true;
    }
  }

  servo2_angle = 90;
  HeadServo2.write(servo2_angle);
  delay(100);
  Serial.println("seguir recto");
  return false;
}


void check_wall_or_obstacle() {
  long distance;

  distance = ultrasonic_sensor1();

  if (distance > 25) {
    // objeto
    Serial.println("objeto");
    obtacle_detected = true;
    wall_detected = false;
  } else {
    // pared
    Serial.println("pared");
    wall_detected = true;
    obtacle_detected = false;
  }
}


void obstacle_avoidance(){
  long distance1_inicial, distance1, distance2;

  // girar 90 grados a la derecha
  Serial.println("GIRO_90_DERECHA");
  direccion = GIRO_90_DERECHA;
  controlar_motores();
  esquivar_derecha = true;

  // comprobar que no haya obstaculo delante, si hay, girar 180 grados hacia la izquierda
  distance2 = ultrasonic_sensor2();
  if (distance2 < 50) {
    // girar 90 grados a la izquierda 
    Serial.println("GIRO_90_IZQUIERDA");
    direccion = GIRO_90_IZQUIERDA;
    controlar_motores();

    // girar 90 grados a la izquierda //
    Serial.println("GIRO_90_IZQUIERDA");
    direccion = GIRO_90_IZQUIERDA;
    controlar_motores();
    esquivar_derecha = false;
  }

  // Avanzar recto hasta que deje de haber obstaculo (un poco mas), utilizar pared como referencia
  distance1_inicial = ultrasonic_sensor1();
  Serial.println("RECTO");
  direccion = RECTO;
  controlar_motores();
  distance1 = ultrasonic_sensor1();
  
  while (distance1_inicial - distance1 < 50) {
    // SEGUIR RECTO
    distance1 = ultrasonic_sensor1();
  }

  // Girar robot -90 grados
  if (esquivar_derecha) {
    // girar 90 grados a la izquierda
    Serial.println("GIRO_90_IZQUIERDA");
    direccion = GIRO_90_IZQUIERDA;

  } else {
    // girar 90 grados a la derecha
    Serial.println("GIRO_90_DERECHA");
    direccion = GIRO_90_DERECHA;
  }

  // Avanzar recto, ya ha superado el obstaculo
  Serial.println("RECTO");
  direccion = RECTO;
}


void wall_aproximance() {
  long distance1;

  distance1 = ultrasonic_sensor1();

  while (distance1 > 5) {
    // SEGUIR RECTO
    distance1 = ultrasonic_sensor1();
  }

  direccion = PARAR;
}


void wall_deaproximance() {
  long distance1;

  distance1 = ultrasonic_sensor1();

  direccion = RETROCEDER;

  while (distance1 < 30) {
    // RETROCEDER
    distance1 = ultrasonic_sensor1();
  }

  direccion = PARAR;
}


void parpadeo_led() {
  while (led_parpadeo_counter < 6) {
    valor_led_amarillo = !valor_led_amarillo;
    digitalWrite(LED_AMARILLO, valor_led_amarillo); 
    led_parpadeo_counter++;
    delay(200);
  }

  // after blinking 3 times
  digitalWrite(LED_AMARILLO, HIGH); 
  led_parpadeo_counter = 0;
}

void elegir_pared() {
  if (wall_counter == 1) {
    // girar 90 grados a la derecha
    Serial.println("GIRO_90_DERECHA");
    direccion = GIRO_90_DERECHA;
    controlar_motores();
    
  } else if (wall_counter == 2) {
    // girar 90 grados a la derecha
    Serial.println("GIRO_90_DERECHA");
    direccion = GIRO_90_DERECHA;
    controlar_motores();
    
  } else if (wall_counter == 3) {
    // girar 90 grados a la derecha 2 veces (180 grados)
    Serial.println("GIRO_90_DERECHA");
    direccion = GIRO_90_DERECHA;
    controlar_motores(); 
    
  } else if (wall_counter == 4) {
    // parar
    Serial.println("PARAR");
    direccion = PARAR;
    controlar_motores();
    state = INICIO;
  }
}


void prueba2() {
  int time_seconds;

  state = RECTO;
  controlar_motores();
  Serial.print("paredes: " );
  Serial.println(wall_counter);

  

  while (wall_counter < 4) {
    time_seconds = (millis() - time_start_count) / 1000;

    if (time_seconds >= 2) {
      if (check_collision()) {
        // pared o obstaculo
        check_wall_or_obstacle();

        if (obtacle_detected) {
          obstacle_avoidance();

        } else if (wall_detected) {
          wall_aproximance();
          wall_counter++;
          parpadeo_led();
          elegir_pared();
          wall_deaproximance();
        }
      }
      time_start_count = millis();
    }
  }
}
