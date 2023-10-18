
//Viral Science
//RFID
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>
#include <SoftwareSerial.h>
#include <ThreeWire.h>
#include <RtcDS1302.h>
#include <Keypad.h>
#include <DS3231.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial sim(3, 2);


int state1 = 0;
int state2 = 0; 
int state3 = 0;
int state4 = 0;
int state5 = 0;

#define SS_PIN 10
#define RST_PIN 9
 //define green LED pin
 //define red LED

int buttonPin = 8;
int buttonRead = 1;
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
#define LED_G 13
 #define RST_PIN    2
#define SDA_PIN    10
 #define LED_R 3
 #define BUZZER 6 //buzzer pin

ThreeWire myWire(11, 10, 12);        // DAT, CLK, RST
RtcDS1302<ThreeWire> Rtc(myWire);    // RTC Object


void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  // Push button code
  pinMode(buttonPin, INPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  noTone(BUZZER);

  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522

 lcd.init();
  lcd.backlight();
  lcd.clear();

  Rtc.Begin();

  RtcDateTime currentTime = RtcDateTime(__DATE__ , __TIME__);
  Rtc.SetDateTime(currentTime);

lcd.init();
 
  lcd.backlight();
  lcd.setCursor(0, 0);
  Serial.begin(9600);
  sim.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  
   lcd.setCursor(0, 0);
  lcd.print("    WELCOME    ");
  lcd.setCursor(0, 1);
  lcd.print("TO MY PROJECT");
  delay(4000);
  lcd.clear();

}
void loop() 
{
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("ATTENDANCE SYS : ");
  content.toUpperCase();
  if (content.substring(1) == "F3 68 2B 0E"&& state1 == 0) //change here the UID of the card/cards that you want to give access
  {
    lcd.clear();
    lcd.setCursor(7, 0);
    lcd.print("Manas");
    lcd.setCursor(11, 1);
    delay(2000);
    lcd.print("PRESENT!! ");
    delay(500);
      lcd.print("Time: ");
    state1 = 1;
  
//Card UID: 23 66 A4 A6
    Serial.println("Authorized access");
    Serial.println();
    delay(500);
    digitalWrite(LED_G, HIGH);
    tone(BUZZER, 500);
    delay(300);
    noTone(BUZZER);
//    myServo.write(180);
    delay(5000);
//    myServo.write(0);
    digitalWrite(LED_G, LOW);
  }
 
else if (content.substring(1) == "F3 68 2B 0E" && state1 == 1) //change here the UID of the card/cards that you want to give access
   {
    lcd.clear();
    lcd.setCursor(7, 0);
    lcd.print("Manas");
    lcd.setCursor(11, 1);
 
    delay(2000);
  
    lcd.print("YOU ARE LATE!!");
     delay(500);
      lcd.print("Time: ");
    state1 = 0;
    Serial.println(" ABSENT");
    digitalWrite(LED_R, HIGH);
    tone(BUZZER, 300);
    delay(1000);
    digitalWrite(LED_R, LOW);
    noTone(BUZZER);
   }
    else if (content.substring(1) == "23 66 A4 A6" && state2 == 0) //change here the UID of the card/cards that you want to give access
  { 
    lcd.clear();
    lcd.setCursor(7, 0);
    lcd.print("JUSTUS");
    lcd.setCursor(11, 1);
    delay(2000);
    lcd.print("PRESENT!! ");
    delay(500);
      lcd.print("Time: ");
    state1 = 1;
    Serial.println("Authorized ");
    Serial.println();
    delay(500);
    digitalWrite(LED_G, HIGH);
    tone(BUZZER, 500);
    delay(300);
    noTone(BUZZER);
//    myServo.write(180);
    delay(5000);
//    myServo.write(0);
    digitalWrite(LED_G, LOW);
  }
 
else if (content.substring(1) == "23 66 A4 A6" && state1 == 1) //change here the UID of the card/cards that you want to give access
   {
    lcd.clear();
    lcd.setCursor(7, 0);
    lcd.print("Manas");
    lcd.setCursor(11, 1);
    delay(2000);
    lcd.print("YOU ARE LATE!!");
     delay(500);
      lcd.print("Time: ");
    state1 = 0;
    Serial.println(" Access denied");
    digitalWrite(LED_R, HIGH);
    tone(BUZZER, 300);
    delay(1000);
    digitalWrite(LED_R, LOW);
    noTone(BUZZER);
 }
 }
