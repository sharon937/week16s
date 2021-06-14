#define NOTE_C3  131
#define NOTE_D3  147
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_G3  196
#define NOTE_A3  220
#define NOTE_B3  247
#define NOTE_C4  262

int latchPin = 8;
int clockPin = 12;
int dataPin = 11;
int melody[]={
  NOTE_E3,NOTE_E3,NOTE_E3, 0,NOTE_E3, NOTE_E3,NOTE_E3, 0,NOTE_E3, 0,NOTE_G3, NOTE_C3,NOTE_D3, NOTE_E3
};
int notedurations[] = {
 4,4,4,4,4,4,4,4,4,4,4,4,4
};
int thisnote = -1,noteduration = 0;
long previoustime = 0,
     presenttime = 0,
     pausebetweennote = 0;
     
void setup() {
  pinMode(latchPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(dataPin,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(2,INPUT_PULLUP);
  }
  
void checktoplay(){
  presenttime = millis();
  if(presenttime - previoustime >= pausebetweennote){
    thisnote += 1;
    if(thisnote >= 13){
      thisnote = -1;
      pausebetweennote = 100;
      previoustime = millis();
    }else{
      noteduration = 500 / notedurations[thisnote];
      tone(9, melody[thisnote], noteduration);
      pausebetweennote = noteduration * 1.2;
      previoustime = millis();
    }
  }
}

byte colDataMatrix[8] = {
   B11111110,
   B11111101,
   B11111011,
   B11110111,
   B11101111,
   B11011111,
   B10111111,
   B01111111
};
byte rowDataMatrix[8] = {
   B00011000,
   B00111100,
   B01111110,
   B00111100,
   B01111110,
   B11111111,
   B00011000,
   B00011000
};
byte rowDataMatrix2[8] = {
   B10000001,
   B01000010,
   B00100100,
   B00011000,
   B00011000,
   B00100100,
   B01000010,
   B10000001
};

byte buttonprevious = 1,buttonpresent = 1 ,pattern = 0;

void loop() {
   buttonpresent = digitalRead(2);
  if(buttonpresent ==0 && buttonprevious == 1){
    pattern++;
    if(pattern>1)
      pattern = 0;
  }
  if(pattern ==0){
    for(int i = 0; i < 8 ; i++){
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, colDataMatrix[i]);
    shiftOut(dataPin, clockPin, MSBFIRST, rowDataMatrix[i]);
    digitalWrite(latchPin,HIGH);
    checktoplay();
    delay(1);
    }
  }
  if(pattern == 1){
      for(int i = 0; i < 8 ; i++){
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, colDataMatrix[i]);
    shiftOut(dataPin, clockPin, MSBFIRST, rowDataMatrix2[i]);
    digitalWrite(latchPin,HIGH);
    checktoplay();
    delay(1);
      }
  }
    delay(2);
    buttonprevious = buttonpresent ;
}
