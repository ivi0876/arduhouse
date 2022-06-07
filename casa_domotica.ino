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

  
  lcd.print("Temperature:"); // temperature
  lcd.setCursor(5,2);
  lcd.print("Centigrades"); // centigrade
  
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
  Serial.println("The value of light is: " + porcentaje +"%");

  if(sensorLight<80){
    digitalWrite(lights_ldr,HIGH);
  }
  else{
    digitalWrite(lights_ldr,LOW);
  }
  delay(250);
}



void sensor_temperature(){
//operation to calculate the values ​​in centigrade
  int grados = (analogRead(A1)-104)/2;
  Serial.println("The temperature is: " + grados + "Cº");

  if(grados<15){
    digitalWrite(13,HIGH); //led blue
    digitalWrite(12,LOW);  //led green
    digitalWrite(11,LOW);  //led Red
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
  long duracion, ditancie;
  digitalWrite(trigger,LOW);
  delayMicroseconds(2);
  digitalWrite(trigger,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger,LOW);
  duracion=pulseIn(echo,HIGH);
  //operation to calculate the value in centimeters
  distance = (duracion/2) /29.1;

  if(distance < 9){
    Serial.println("==================================);"
    Serial.println("Garage open");
    servo.write(0);
    servo1.write(150);
    digitalWrite(light_garage,HIGH);
  }
  else if(distance > 9){
    Serial.println("==================================");
    Serial.println("Garage close");
  }
  Serial.println("=====================================");
  Serial.println(distance + " cm");
}
