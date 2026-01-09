// Codigo del robot con motores moviendose


#include <Servo.h>
#include <IRremote.h>

// states
int state;
int direccion;

enum states {
  INICIO = 0,
  PRUEBA1 = 1,
  PRUEBA2 = 2,
};

enum direcciones {
  RECTO = 0,
  GIRO_DERECHA = 1,
  GIRO_IZQUIERDA = 2,
  GIRO_90_DERECHA = 3,
  GIRO_90_IZQUIERDA = 4,
  RECTO_LARGO = 5,
  PARAR = 6,
  RETROCEDER = 7,
};

// mando
#define CODIGO_BOTON_1 0x2FFA00
#define CODIGO_BOTON_2 0x2EFA20
#define IR_PIN 30

// tiempo antirrebote
unsigned long t_antirrebote = 500;

// ultrasonic sensor cabeza1 (arriba)
#define TRIG1 31
#define ECHO1 29
long distancia_pared;

// ultrasonic sensor cabeza2 (abajo)
#define TRIG2 37
#define ECHO2 35

// servo cabeza1 (arriba)
Servo HeadServo1;
int servo1_angle = 0;

// servo cabeza2 (abajo)
Servo HeadServo2;
int servo2_angle = 0;

// leds
#define LED_AZUL 24
#define LED_AMARILLO 25
#define LED_VERDE 26

// botones
#define BOTON_1 22
#define BOTON_2 23
long interrupcion1_start = 0, interrupcion2_start = 0;

// servos
const int numServos = 6;
const int numMitadServos = 3;
Servo servos[numServos];

// num vueltas
const int vueltas90Derecha = 3;
const int vueltas90Izquierda = 3;
const int vueltasRectoLargo = 5;

// Pines PWM para mover los servos
const int pwmPins[numServos] = {13, 11, 9, 12, 10, 8}; // 13, 11, 9 derecha -> 12, 10, 8 izquierda

// Pines para leer feedback PWM
const int fbPins[numServos] = {7, 5, 3, 6, 4, 2};

// Variables para contar vueltas
float prevAngle[numServos] = {0,0,0,0,0,0};
int vueltas[numServos] = {0,0,0,0,0,0};

// 
bool robot_inicializado = false;
int angle_to_turn = 0;
bool obtacle_detected = false, wall_detected = false, first_time = true;
bool valor_led_amarillo = HIGH;
int led_parpadeo_counter = 0;
unsigned long angulos_laser_check[] = {45, 50, 90, 130, 135};
int wall_counter = 0;
unsigned long time_start_count, prueba1_time_start;
bool esquivar_derecha;


void setup() {
  Serial.begin(9600);

  // estado inicial
  state = INICIO;
  direccion = RECTO;

  // ultrasonic sensor cabeza1 (arriba)
  pinMode(TRIG1, OUTPUT);
  pinMode(ECHO1, INPUT);
  digitalWrite(TRIG1, LOW);

  // ultrasonic sensor cabeza2 (abajo)
  pinMode(TRIG2, OUTPUT);
  pinMode(ECHO2, INPUT);
  digitalWrite(TRIG2, LOW);

  // servo
  HeadServo1.attach(27);
  HeadServo2.attach(33);

  // leds
  pinMode(LED_AZUL, OUTPUT);
  pinMode(LED_AMARILLO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);

  // Inicializar servos
  for(int i=0;i<numServos;i++){
    servos[i].attach(pwmPins[i]);
  }

  // mando
  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);
}


void loop() {
  // posicion de inicio
  if (state == INICIO) {
    if (!robot_inicializado) {
      posicion_de_inicio();

    } else {
      digitalWrite(LED_VERDE, HIGH);
      digitalWrite(LED_AZUL, LOW);
      digitalWrite(LED_AMARILLO, LOW);
      checkbotones();
      checkmando();
      time_start_count = millis();
    } 
    
  // prueba 1 
  } else if (state == PRUEBA1) {
    if (((millis() - prueba1_time_start) / 1000) < 60) {
      prueba1();
    } else {
      direccion = PARAR;
      state = INICIO;
    }

  // prueba 2
  } else if (state == PRUEBA2) {
    prueba2();
  }

  if (direccion == PARAR) {
    controlar_motores();
    checkbotones();
  } 
}  
