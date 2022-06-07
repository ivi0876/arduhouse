//Include the libraries

#include<Servo.h>
#include<LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

//we create name for the servos
Servo servo;
Servo servo1;
// sensor ultrasonic HCSR04
#define trigger 3;
#define echo 4;

const int lights_ldr = 2;
const int light_garage=5;

void setup() {
  
Serial.begin(9600);

lcd.init();

lcd.backlight();

for(int Npin=11; Npin>13; Npin++){
    pinMode(Npin,OUTPUT);    
  }
  pinMode(light_garaje,OUTPUT);
  pinMode(trigger,OUTPUT);
  pinMode(echo,INPUT);

  servo.attach(6);
  servo.attach(7);

  
  lcd.print("Temperatura:"); // temperature
  lcd.setCursor(5,2);
  lcd.print("Centigrados"); // centigrade
  
}

void loop() {
  
   sensor_light();
   sensor_temperature();
   sensor_ultrasonidos();

}

void sensor_light(){
//we read the value from the light sensor, 
//and use MAP to transform the values, between 0 and 100%
  int sensorLight = analogRead(A0);
  delay(250);
  int porcentaje = map(sensorLuz,0,1023,0,100);
  Serial.println("El valor de la luz es: " + porcentaje +"%");

  if(sensorLight<80){
    digitalWrite(luces,HIGH);
  }
  else{
    digitalWrite(luces,LOW);
  }
  delay(250);
}



void sensor_temperature(){
//operation to calculate the values ​​in centigrade
  int grados = (analogRead(A1)-104)/2;
  Serial.println("La temperatura es de: " + grados + "Cº");

  if(grados<15){
    digitalWrite(13,HIGH); //Azul
    digitalWrite(12,LOW);  //Verde
    digitalWrite(11,LOW);  //Rojo
  }
  else if(grados>19 && grados<25){
  
    digitalWrite(13,LOW);
    digitalWrite(12,HIGH);
    digitalWrite(11,LOW);
  }
  
  else if(grados>=26){
  
    digitalWrite(13,LOW);
    digitalWrite(12,LOW);
    digitalWrite(11,HIGH);
  }

  lcd.setCursor(0,2);
  lcd.print(grados);  
  
}


void sensor_ultrasonidos(){
  long duracion, ditancia;
  digitalWrite(trigger,LOW);
  delayMicroseconds(2);
  digitalWrite(trigger,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger,LOW);
  duracion=pulseIn(echo,HIGH);
  //operation to calculate the value in centimeters
  distancia = (duracion/2) /29.1;

  if(distancia < 9){
    Serial.println("==================================);"
    Serial.println("Garaje abierto");
    servo.write(0);
    servo1.write(150);
    digitalWrite(luz_garaje,HIGH);
  }
  else if(distancia > 9){
    Serial.println("==================================");
    Serial.println("Garaje cerrado");
  }
  Serial.println("=====================================");
  Serial.println(distancia + " cm");
}
