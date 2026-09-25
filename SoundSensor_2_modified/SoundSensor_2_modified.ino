// include the library code:
#include <LiquidCrystal.h>
#include <Wire.h>


// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
//const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
const int rs = 7, en = 8, d4 = 10, d5 = 11, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int num_Measure = 128 ; // Set the number of measurements   
int pinSignal = A0; // pin connected to pin O module sound sensor  
int redLed = 5; 
long Sound_signal;    // Store the value read Sound Sensor   
long sum = 0 ; // Store the total value of n measurements   
long level = 0 ; // Store the average value   
int soundlow = 35;
int soundmedium = 120;
int BACKLIGHT_PIN =3;

int buzzerPin = 5;

//#define         MQ_PIN                       (0)     //define which  analog input channel you are going to use
//float           Ro           =  10;                 //Ro is initialized to 10 kilo ohms

void setup() {
  pinMode (pinSignal, INPUT); // Set the signal pin as input   

  //lcd.begin(16,2);  
  //Serial.begin (9600);

  //Serial.print("Begin Test ");
  //lcd.print("Begin Test ");

  Serial.begin(9600);                               //UART  setup, baudrate = 9600bps
  Serial.print("Calibrating...");                
  //Ro = MQCalibration(MQ_PIN);                       //Calibrating the sensor. Please  make sure the sensor is in clean air 
   lcd.begin(16, 2);                                                  //when  you perform the calibration                    
  Serial.print("Calibration  is done..."); 
 
}

void loop() {
  
   for ( int i = 0 ; i <num_Measure; i ++)  
  {  
   Sound_signal = analogRead (pinSignal);  
    sum =sum + Sound_signal;  
  }  
  lcd.clear();

  level = sum / num_Measure; // Calculate the average value   
  Serial.print("Sound Level: ");
  lcd.print("Sound Level= ");
  Serial.println (level-33);  
  lcd.print(level-33);

  if(level-33<soundlow)
  {
    lcd.setCursor(0,2);
    lcd.print("Intensity= Low");
     digitalWrite(redLed,LOW);
  }
  if(level-33>soundlow && level-33<soundmedium)
  {
    lcd.setCursor(0,2);
    lcd.print("Intensity=Medium"); 
     digitalWrite(redLed,LOW); 
  }
  if(level-33>soundmedium)
  {
    lcd.setCursor(0,2);
    lcd.print("Intensity= High");   
    digitalWrite(redLed,HIGH);
    tone(buzzerPin, 784); // F4
    delay(15000); 
    noTone(buzzerPin);
  }
  sum = 0 ; // Reset the sum of the measurement values  
  delay(200);
  lcd.clear();

}
