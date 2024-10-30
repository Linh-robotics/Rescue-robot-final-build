#include <QTRSensors.h>
const int S0 = 2;
const int S1 = 3;
const int S2 = 4;
const int S3 = 5;
const int sensorOut = 8;
const int M1 = 6;
const int M2 = 9;
const int M3 = 10;
const int M4 = 11;
const int L1 = A2;
const int L2 = A3;
const int L3 = A4;
const int L4 = A5;
const int sound1 = A1;

QTRSensors qtr;
const uint8_t SensorCount = 4;
uint16_t sensorValues[SensorCount];


int redPW = 0;
int greenPW = 0;
int bluePW = 0;

int whiteCali[] = {0, 0, 0};
int blackCali[] = {0, 0, 0};

int redValue;
int greenValue;
int blueValue;

int colour;
int LINE = 0;

void setup() {
  pinMode (S0, OUTPUT);
  pinMode (S1, OUTPUT);
  pinMode (S2, OUTPUT);
  pinMode (S3, OUTPUT);
  pinMode (sensorOut, INPUT);
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  Serial.begin(9600);
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(M3, OUTPUT);
  pinMode(M4, OUTPUT);
  pinMode(sound1, INPUT);

  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){A0, A1, A2, A3}, SensorCount);

  calibration();

}

void calibration(){
  delay(1000);
  whiteCali[0] = getRedPW();
  whiteCali[1] = getBluePW();
  whiteCali[2] = getGreenPW();
  delay(1000);
  blackCali[0] = getRedPW();
  blackCali[1] = getBluePW();
  blackCali[2] = getGreenPW();
}
  
void goStraight()  
{
  
  analogWrite(M1, 119);
  digitalWrite(M2, LOW);
  analogWrite(M4, 140);
  digitalWrite(M3, LOW);
  delay(100);
  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
  digitalWrite(M4, LOW);
  digitalWrite(M3, LOW);
  delay(1);
}

void goLeft()  
{
  digitalWrite(M1, 1);
  digitalWrite(M2, LOW);
  digitalWrite(M4, LOW);
  digitalWrite(M3, 5);
  delay(100);
  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
  digitalWrite(M4, LOW);
  digitalWrite(M3, LOW);
  delay(1);
}

void goRight()  
{
  digitalWrite(M1, LOW);
  digitalWrite(M2, 1);
  digitalWrite(M4, 5);
  digitalWrite(M3, LOW);
  delay(100);
  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
  digitalWrite(M4, LOW);
  digitalWrite(M3, LOW);
  delay(1);
}

 int getRedPW(){
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  int PW;
  PW = pulseIn(sensorOut, LOW);
  return PW;
  }

  int getGreenPW(){
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  int PW;
  PW = pulseIn(sensorOut, LOW);
  return PW;
  }
  

  int getBluePW(){
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  int PW;
  PW = pulseIn(sensorOut, LOW);
  return PW;
  }

void loop() {
  //int loud = analogRead(sound1);
  //Serial.print("sound level = ");
  //Serial.println(loud);
  //delay(500);  

  int mostLeft = analogRead(A2);
  int left = analogRead(A3);
  int right = analogRead(A4);
  int mostRight = analogRead(A5);

  if (right > 100 && left > 100){
    goStraight();
  } else if (right > 100 && left < 100){
    goRight();
  } else if (left > 100 && right < 100){
    goLeft();
  }else if (left < 100 && right < 100 && A5 > 100){
    goLeft();
  }else if (left < 100 && right < 100 && A2 > 100){
    goRight();
  }else if (left < 100 && right < 100 && A2 < 100 && A5 <100){
    goLeft();
  }

  redPW = getRedPW();
  //Serial.print("R = ");
  //Serial.print(redPW);
 // Serial.println();
  redValue = map(redPW,whiteCali[0], blackCali[0], 255, 0);
  redValue = constrain(redValue, 0, 255);
  Serial.print("Red = ");
  Serial.print(redValue);
  Serial.println();
  delay(100);

  greenPW = getGreenPW();
  //Serial.print(" G = ");
  //Serial.print(greenPW);
  //Serial.println();
  greenValue = map(greenPW,whiteCali[2], blackCali[2], 255, 0);
  greenValue = constrain(greenValue, 0, 255);
  Serial.print("Green = ");
  Serial.print(greenValue);
  Serial.println();
  delay(100);

  bluePW = getBluePW();
  //Serial.print(" B = ");
  //Serial.print(bluePW);
  //Serial.println();
  blueValue = map(bluePW,whiteCali[1], blackCali[1], 255, 0);
  blueValue = constrain(blueValue, 0, 255);
  Serial.print("Blue = ");
  Serial.print(blueValue);
  Serial.println();
  delay(100);

  if(redValue > greenValue && redValue > blueValue && redValue > 0){
     Serial.println(" - RED detected!");
  }
  if(greenValue > redValue && greenValue > blueValue && greenValue > 0){
    Serial.println(" - GREEN detected!");
  }
  if(blueValue > redValue && blueValue > greenValue && blueValue > 0){
    Serial.println(" - BLUE detected!");
  }
  if(redValue < 10 && greenValue < 10 && blueValue < 10){
    Serial.println(" - BLACK detected!");
  }
  if(redValue > 250 && greenValue > 250 && blueValue > 250){
    Serial.println(" - WHITE detected!");
  }
   if(240<redValue<255 && 210<greenValue<240 && 190<blueValue<210){
    Serial.println(" - YELLOW detected!");
  }
  if(150<redValue<170 && 120<greenValue<145 && 140<blueValue <160){
    Serial.println(" - PURPLE detected!");
  }
 
  // read raw sensor values
  qtr.read(sensorValues);
  // print the sensor values as numbers from 0 to 1023, where 0 means maximum
  // reflectance and 1023 means minimum reflectance
  for (uint8_t i = 0; i < SensorCount; i++)
  {

    Serial.print(sensorValues[i]);

    Serial.print('\t');
}
  Serial.println();
  delay(250);
}

 
