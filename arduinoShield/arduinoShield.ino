#include <EEPROM.h>
#include <avr/wdt.h>
#include <MsTimer2.h>
#include <Servo.h>

//객체생성
Servo myservo;

//전역변수
int addr = 0;
int modeNum = 0;
bool delay_count = true;
bool kickCount = true;

int note[] = {2093,2349,2637,2793,3136};

int pos = 0;


void setup(){  
  wdt_enable(WDTO_2S);

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
      //없음
      delay_count = false;
      Serial.println("setup mode 3");
      break;
    case '4':
      pinMode(3, OUTPUT);
      pinMode(5, OUTPUT);
      pinMode(11, OUTPUT); 
      delay_count = false;
      Serial.println("setup mode 4");
      break;
    case '5':
      myservo.attach(9);
      delay_count = false; 
      Serial.println("setup mode 5");
      break;
    case '6': 
      delay_count = false;
      Serial.println("setup mode 6");
      break;
    case '7': 
      //없음
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
        break;
      case '2': 
        Button();
        break;
      case '3': 
        Buzzer();
        break;
      case '4': 
        RGB_LED();
        break;
      case '5': 
        Servo_moter();
        //Serial.println("setup mode 5");
        break;
      case '6': 
        Serial.println("setup mode 6");
        break;
      case '7':
        Var_resistance();
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
  //Serial.println("kick!"); 
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

void Buzzer(){
  int speakerpin = 13;
  int elementCount = sizeof(note) / sizeof(int);
  
  for (int i=0; i < elementCount; i++){
    tone(speakerpin ,note[i],500);
    delay(300);
    wdt_reset();
  }
}

void RGB_LED(){
  digitalWrite(3, HIGH);
  delay(500);
  digitalWrite(3, LOW);
  delay(500);

  digitalWrite(5, HIGH);
  delay(500);
  digitalWrite(5, LOW);
  delay(500);

  digitalWrite(11, HIGH);
  delay(500);
  digitalWrite(11, LOW);
  delay(500);
}

void Servo_moter(){
  for(pos = 0; pos < 180; pos += 1){                                  
    myservo.write(pos);              
    delay(15);                       
  } 
  for(pos = 180; pos>=1; pos-=1)     {                                
    myservo.write(pos);              
    delay(15);                       
  } 
}

void Var_resistance(){
  int analogPin_0 = analogRead(A0);
  int analogPin_1 = analogRead(A1);
  
  Serial.print("Pin A0: ");
  Serial.println(analogPin_0);
  Serial.print("Pin A1: ");
  Serial.println(analogPin_1);
  Serial.print("\n");
  delay(100);
}
