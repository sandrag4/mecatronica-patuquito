
// izquierda delante 12 -> 6
// izquierda medio 10 -> 4
// izquierda detras 8 -> 2

// derecha delante 13 -> 7
// derecha medio 11 -> 5
// derecha detras 9 -> 3


// leer el ángulo del feedback PWM
float readServoPWM(int pin, float lastAngle) {
  long dur = pulseIn(pin, HIGH, 25000); // timeout 25 ms
  if(dur == 0) return lastAngle; // si no hay pulso, retorna anterior
  // Mapear 1000–2000 us a 0–180°
  float angle = map(dur, 1000, 2000, 0, 180);
  return angle;
}

void controlar_motores(){
  if (direccion == RECTO) {
    movimiento_recto();

  } else if (direccion == GIRO_DERECHA) {
    movimiento_giro_derecha();

  } else if (direccion == GIRO_IZQUIERDA) {
    movimiento_giro_izquierda();
    
  } else if (direccion == GIRO_90_DERECHA) {
    movimiento_giro_90_derecha();

  } else if (direccion == GIRO_90_IZQUIERDA) {
    movimiento_giro_90_izquierda();

  } else if (direccion == RECTO_LARGO) {
    movimiento_recto_largo();

  } else if (direccion == PARAR) {
    movimiento_parar();

  } else if (direccion == RETROCEDER) {
    movimiento_retroceder();
  }
}



