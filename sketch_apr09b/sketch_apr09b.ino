#include <EEPROM.h>
#include <avr/wdt.h>
#include <MsTimer2.h>

int addr = 0;
int modeNum = 0;
bool delay_count = true;
bool kickCount = true;

int note[] = {2093,2349,2637,2793,3136,3520,3951,4186};


void setup(){  
  wdt_enable(WDTO_1S);

  MsTimer2::set(500, kickWD);
  MsTimer2::start(); 
  
  Serial.begin(9600);
  Serial.println("Serial Port Connected!");
  
  modeNum = EEPROM.read(addr);
  
  switch(modeNum){
    case '1':
      pinMode(6, OUTPUT);
      pinMode(7, OUTPUT);
      pinMode(8, OUTPUT);
      pinMode(12, OUTPUT);
      delay_count = false;
      Serial.println("setup mode 1");
      break;
    case '2':
      pinMode(6, OUTPUT);
      pinMode(12, OUTPUT);
      pinMode(2, INPUT);
      pinMode(4, INPUT);
      digitalWrite(6, HIGH);
      digitalWrite(12, HIGH);
      delay_count = false;
      Serial.println("setup mode 2");
      break;
    case '3':
      delay_count = false;
      Serial.println("setup mode 3");
      break;
    case '4': 
      delay_count = false;
      Serial.println("setup mode 4");
      break;
    case '5':
      delay_count = false; 
      Serial.println("setup mode 5");
      break;
    case '6': 
      delay_count = false;
      Serial.println("setup mode 6");
      break;
    case '7': 
      delay_count = false;
      Serial.println("setup mode 7");
      break;
    case '8': 
      delay_count = false;
      Serial.println("setup mode 8");
      break;
    case '9': 
      delay_count = false;
      Serial.println("setup mode 9");
      break;
    case 'a': 
      delay_count = false;
      Serial.println("setup mode a");
      break;
    case 'b': 
      delay_count = false;
      Serial.println("setup mode b");
      break;
    case 'x': 
      delay_count = false;
      break;
    default:
      break;   
  }
}
 
void loop(){
  if (delay_count == true){
    Serial.println("wait.....");
    delay(1000);
  } else {
    switch(modeNum){
      case '1':
        LED_Blink();
        //Serial.println("loop mode 1");
        break;
      case '2': 
        Button();
        //Serial.println("setup mode 2");
        break;
      case '3': 
        Serial.println("setup mode 3");
        break;
      case '4': 
        Serial.println("setup mode 4");
        break;
      case '5': 
        Serial.println("setup mode 5");
        break;
      case '6': 
        Serial.println("setup mode 6");
        break;
      case '7': 
        Serial.println("setup mode 7");
        break;
      case '8': 
        Serial.println("setup mode 8");
        break;
      case '9': 
        Serial.println("setup mode 9");
        break;
      case 'a': 
        Serial.println("setup mode a");
        break;
      case 'b': 
        Serial.println("setup mode b");
        break;
      case 'x':
        Serial.println("--------------------");
        Serial.println("1. LED");
        Serial.println("2. 버튼");
        Serial.println("3. 부저");
        Serial.println("4. RGB LED");
        Serial.println("5. 서보모터");
        Serial.println("6. DC 모터");
        Serial.println("7. 가변저항");
        Serial.println("8. 조도센서");
        Serial.println("9. 거리센서");
        Serial.println("a. 압력센서");
        Serial.println("b. 온도센서");
        Serial.println("--------------------");     
        modeNum = '0';
        break;
      case '0':
        break;
      default:
        break;   
    }
  }
}
/* 시리얼 수신 ISR */
void serialEvent(){
  int incomingByte = 0;
  
  do{
    delay(2);
    incomingByte = Serial.read();
    if (incomingByte != '\n'){
      modeNum = incomingByte;
      EEPROM.write(addr, modeNum);
    }
    //Serial.print((char)incomingByte);
  }while(incomingByte != '\n');
  
  delay_count = true;
  kickCount = false;
}

void kickWD(){
  //Serial.println("500"); 
  if (kickCount == true){
    wdt_reset();
  } else {
    Serial.println("Restarted arduino board"); 
    delay(1);
  }
}

void LED_Blink(){
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(12, HIGH);
  delay(1000);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(12, LOW);
  delay(1000);
}

void Button(){
  int readValue1 = digitalRead(2);
  int readValue2 = digitalRead(4);

  if(readValue1 == HIGH){
    digitalWrite(12, HIGH);
  }
  if(readValue1 == LOW){
    digitalWrite(12, LOW);
  }
  if(readValue2 == HIGH){
    digitalWrite(6, HIGH);
  }
  if(readValue2 == LOW){
    digitalWrite(6, LOW);
  }
}
