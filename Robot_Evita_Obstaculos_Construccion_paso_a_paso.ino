#include <AsyncSonarLib.h> //Libreria para <<sensor>>
#include <Config.h>
#include <Servo.h> //Libreria para <<servmotor>>
#include <AFMotor.h> // Libreria del <<Motor Shield Adafruit>>


/* 
Programa: Robot Evita Obstaculos - Construccion paso a paso
Autor:	Humberto Higinio
Web: www.humbertohiginio.com
Canal de Youtube: https://www.youtube.com/user/HHSolis
Video Exclusivo para mi canal de Youtube
Todos los Derechos Reservados - 2016
Código de Dominio Público
Descarga la libreria desde https://learn.adafruit.com/adafruit-motor-shield/library-install
*/



#define DisparoPin 12 // Definimos los pines del sensor de ultra sonido // Seria el cable Azul del Trig

#define EcoPin 13 // Definimos los pines del sensor de ultra sonido // Seria el cable Morado del Eco

AF_DCMotor motor1(1,MOTOR12_64KHZ); // Seteamos la frecuencia de PWM de los motores

AF_DCMotor motor2(2,MOTOR12_8KHZ); // Para motores 1 y 2 puede ser 64, 8, 2 y 1KHZ

// Para motores 3 y 4 solo se esta disponible 64, 8 y 1KHZ. En este caso Oscar, no se pone motor 3 y 4 porque solo tenemos dos motores, recuerdalo.
 
Servo servomotorIzq; //Mano izquierda
Servo servomotorDer; //Mano derecha

void setup() {
  
Serial.begin(9600); // Empezamos la comunicacion serial  
 
pinMode(DisparoPin, OUTPUT); // Setemos el Pin de trigger como salida (Pin que envia las ondas sonoras)

pinMode(EcoPin, INPUT); // Setemos el Pin de Eco como entrada (Pin que recibe las ondas sonoras)

motor1.setSpeed(255); // Establecemos la velocidad de los motores, entre 0-255
motor2.setSpeed (255);  

servomotorIzq.attach(9); //pin digital de izquierdo 
servomotorDer.attach(8); //pin digital derecho
}
 
void loop() {

//Los servos inician con las manos hacia enfrente, posición incial
servomotorIzq.write(0); //era cero
delay(10000);
servomotorDer.write(180);
delay(3000);

long duration, distance; // Creamos 2 variables de tamaño extendido para almacenar numeros
  
digitalWrite(DisparoPin, LOW); // Enviamos a bajo el Pin de Trigger
  
delayMicroseconds(2); // Un delays es requerido para que la operacion del sensor se complete
  
digitalWrite(DisparoPin, HIGH); // Enviamos a alto el Pin de Trigger

delayMicroseconds(10); // Mantenemos en alto el Pin de Trigger por 10 us esto es necesario
  
digitalWrite(DisparoPin, LOW); // Enviamos a bajo el Pin de Trigger
  
duration = pulseIn(EcoPin, HIGH); // Calculamos la duracion del Pulso
  
distance = (duration/2) / 29.1; // Convertimos la distancia en centimetros (velocidad Sonido 340m/s o 29.1 us x cm. Se divide entre dos (../2), porque el trigger manda la señal (una), y regresa la señal al Eco (2),...es decir, toma dos distancias, y cuando ya regrese, queda una por recorrer antes de tomar la decisión
  

if (distance < 25) {  // Si la distancia al objeto es menor a 25 cm Gire a la izquierda
    
motor1.run(FORWARD);  // Avanzo el motor1 - motor de la derecha
    
motor2.run (BACKWARD); // Giro en sentido inverso el motor2 - motor de la izquierda
    
delay (1000); // Establecemos el tiempo de giro a la izquierda.  Aqui son de tiempo: mil milisegundos, es decir, un segundo.

// Las opciones son FORWARD, BACKWARD, RELEASE (DETENER)

//Los servos suben sus manos
servomotorIzq.write(90);
delay(1000);
servomotorDer.write(90);
delay(1000);

}
  

else {
   
delay (15); // Seteamos un delay para estabilizar los motores
   
motor1.run(FORWARD); // Si no hay objetos detectados, avance hacia adelante   
   
motor2.run(FORWARD);  
 
//Vuelve a poner sus manos en posición inicial
servomotorIzq.write(90);
delay(1000);
servomotorDer.write(180);
delay(1000);
}  
  
 
}
