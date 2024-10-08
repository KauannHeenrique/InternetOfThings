#include <Wire.h>
#include <SPI.h>
#include <MFRC522.h>

int sensorState = 0;
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
int buzzerActive = 0; 

int buzzer = 3;
const int pinoBuzzer = 3;


void setup()
{
  pinMode(13, OUTPUT);
  pinMode(2, INPUT);
  pinMode(buzzer, OUTPUT);
  
  Serial.begin(9600);
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
}

void loop()
{
  String content= "";
  byte letter;
  content.toUpperCase();

  do
  {
    sensorState = digitalRead(2);
    if (sensorState == HIGH)
  	{
    tone(buzzer, 100, 1000);
  	delay(3000);
  	noTone(buzzer);
    delay(1000);

  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }

   for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
    }
    
  } while (content.substring(1) != "56 C8 99 AC" );//change here the UID of the card/cards that you want to give access
  

}