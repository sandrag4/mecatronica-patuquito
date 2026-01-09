
// Distance cabeza1 (arriba)
long ultrasonic_sensor1() {
  long time, distance;

  digitalWrite(TRIG1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG1, LOW);
  
  time = pulseIn(ECHO1, HIGH); 
  distance = time/58.2;

  return distance;
}

// Distance cabeza2 (abajo)
long ultrasonic_sensor2() {
  long time, distance;

  digitalWrite(TRIG2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG2, LOW);
  
  time = pulseIn(ECHO2, HIGH); 
  distance = time/58.2;

  return distance;
}