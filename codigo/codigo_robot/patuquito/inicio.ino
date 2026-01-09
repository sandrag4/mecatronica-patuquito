
void posicion_de_inicio() {
  servo1_angle = 90;
  HeadServo1.write(servo1_angle);

  servo2_angle = 90;
  HeadServo2.write(servo2_angle);

  robot_inicializado = true;
}