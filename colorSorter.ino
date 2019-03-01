#include <Servo.h>

#define S0 2
#define S1 3
#define S2 4
#define S3 5
#define sensorOut 6

Servo topServo;
Servo bottomServo;

int frequency = 0;
int color=0;

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  
  // Setting frequency-scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  
  topServo.attach(7);
  bottomServo.attach(8);
  
  Serial.begin(9600);
}

void loop() {
  topServo.write(100);
  delay(2000);
  
  for(int i = 100; i > 40; i--) {
    topServo.write(i);
    delay(5);
  }
  delay(1000);
  
  color = readColor();
  delay(10);  
  
  switch (color) {
    case 1:
    bottomServo.write(90);
    break;
    
    case 2:
    bottomServo.write(110);
    break;
    
    case 3:
    bottomServo.write(130);
    break;
    
    case 4:
    bottomServo.write(150);
    break;
    
    case 5:
    bottomServo.write(180);
    break;
    
    case 0:
    break;
  }
  delay(300);
  
  for(int i = 40; i > 9; i--) {
    topServo.write(i);
    delay(5);
  } 
  delay(200);
  
  for(int i = 9; i < 100; i++) {
    topServo.write(i);
    delay(2);
  }
  color=0;
}

int readColor() {
  color = 0;
  // Setting red filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int R = frequency;
  
  // Printing the value on the serial monitor
  Serial.print("R= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(50);
  
  // Setting Green filtered photodiodes to be read
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int G = frequency;
  
  // Printing the value on the serial monitor
  Serial.print("G= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(50);
  
  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int B = frequency;
  
  // Printing the value on the serial monitor
  Serial.print("B= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.println("  ");
  delay(50);
  
  if(R>225 && R<245 && G>205 && G<220 && B<130 && B>118){
    color = 1; // Blue
  }
  if(R>159 && R<175 && G<275 && G>260 && B<195 && G>180){
    color = 2; // Red
  }
  if(R<140 && R>120 && G<175 && G>155 && B>160 && B<179){
    color = 3; // Yellow
  }
  if(R>185 && R<202 && G<195 && G>178 && B<165 && B>150){
    color = 4; // Green
  }
  if(R<155 && R>135 && G<230 && G>199 && B>159 && B<180){
    color = 5; // Orange
  }
  delay(1000);
  
  //In case the sensor doesn't detect the color on the first attempt
  if (color) return color;  
  else return readColor(); 
}
