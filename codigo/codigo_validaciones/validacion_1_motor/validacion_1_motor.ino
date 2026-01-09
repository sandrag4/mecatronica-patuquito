// Este codigo comprueba un servo de 5 vueltas
// El servo deja de girar cuando ha completado 5 vueltas

// Para comprobar otro motor, hay que cambiar el numero en
// const int pwmPins[numServos] = {13}; y en const int fbPins[numServos] = {7};
// por el del motor correspondiente

// posicion:

// izquierda delante 12 -> 6
// izquierda medio 10 -> 4
// izquierda detras 8 -> 2

// derecha delante 13 -> 7
// derecha medio 11 -> 5
// derecha detras 9 -> 3

#include <Servo.h>


const int numServos = 1;

// Pines PWM para mover los servos
const int pwmPins[numServos] = {13};

// Pines para leer feedback PWM
const int fbPins[numServos] = {7};

Servo servos[numServos];

// Variables para contar vueltas
float prevAngle[numServos] = {0};
int vueltas[numServos] = {0};
const int maxVueltas = 5;

// Función para leer el ángulo del feedback PWM
float readServoPWM(int pin, float lastAngle){
  long dur = pulseIn(pin, HIGH, 25000); // timeout 25 ms
  if(dur == 0) return lastAngle; // si no hay pulso, retorna anterior
  // Mapear 1000–2000 us a 0–180°
  float angle = map(dur, 1000, 2000, 0, 180);
  return angle;
}

void setup(){
  Serial.begin(9600);

  // Inicializar servos
  for(int i=0;i<numServos;i++){
    servos[i].attach(pwmPins[i]);
  }
}

void loop(){
  for(int i=0;i<numServos;i++){
    // Si no alcanzó las 5 vueltas, girar hacia adelante
    if(vueltas[i] < maxVueltas){
      servos[i].write(160); // máximo hacia adelante
    } else {
      servos[i].write(90);  // detener servo
    }
  }

  delay(10); // pequeña pausa para estabilidad

  // Leer feedback y actualizar vueltas
  for(int i=0;i<numServos;i++){
    float angle = readServoPWM(fbPins[i], prevAngle[i]);

    if(angle < 0) angle += 180;   // normaliza a 0-180
    if(prevAngle[i] < 0) prevAngle[i] += 180;

    // Detectar cruce de 180° → 0° para contar vueltas
    if(prevAngle[i] > 90 && angle < 90){
      vueltas[i]++;
      Serial.print("Servo ");
      Serial.print(i+1);
      Serial.print(" vueltas: ");
      Serial.println(vueltas[i]);
    }

    prevAngle[i] = angle;
  }

  // Comprobar si todos los servos ya dieron 5 vueltas
  bool todosListos = true;
  for(int i=0;i<numServos;i++){
    if(vueltas[i] < maxVueltas) todosListos = false;
  }

  if(todosListos){
    Serial.println("El servo completo 5 vueltas.");
    while(1){
      // detener todo
      for(int i=0;i<numServos;i++) servos[i].write(90);
      delay(1000);
    }
  }
}
