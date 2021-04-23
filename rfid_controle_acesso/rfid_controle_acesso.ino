#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
#define LED_VERDE 3
#define LED_VERMELHO 2

MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();

  pinMode(LED_VERDE , OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);

  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_VERMELHO, LOW);
}

void loop() {
  if(!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    String conteudo = " ";
    for(byte i = 0; i < rfid.uid.size; i++) {
      Serial.print(rfid.uid.uidByte[i] < 0x10 ? "0" : " ");
      Serial.print(rfid.uid.uidByte[i], HEX);
      conteudo.concat(String(rfid.uid.uidByte[i] < 0x10 ? "0" : " "));
      conteudo.concat(String(rfid.uid.uidByte[i], HEX)); 
    }
    Serial.println();
    conteudo.toUpperCase(); 
    
    if(conteudo.indexOf("47 52 CA 5F") >= 0) {
      digitalWrite(LED_VERMELHO, HIGH);
      delay(200);
      digitalWrite(LED_VERMELHO, LOW);
    }

    if(conteudo.indexOf("22 76 A0 34") >= 0) {
      digitalWrite(LED_VERDE, HIGH);
      delay(200);
      digitalWrite(LED_VERDE, LOW);
    } 
  }
  
  rfid.PICC_HaltA(); 
  rfid.PCD_StopCrypto1();
}
