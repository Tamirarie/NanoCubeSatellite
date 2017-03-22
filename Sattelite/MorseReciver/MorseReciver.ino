int LDR_Pin = 0; //analog pin 0
int led = 13;

// 10k between GND and A0
// LDR between 5V and A0

#define MORSE_EMPTY   0
// Этими символами мы будем обозначать точки и тире.
#define MORSE_DOT     '.'
#define MORSE_DOT2     '+'
#define MORSE_TIRE    '-'
// Максимальная длина символа азбуки Морзе (в точках и тире)
#define MAX_MORSE_SYMBOL_LENGTH  8
char* morseSymbol[MAX_MORSE_SYMBOL_LENGTH];
unsigned int morseSymbolLen;
char* newMorseSignal; // Новый введенный сигнал - точка или тире.

// Таблица кодов Морзе. N-ный элемент кода соответствует n-ному символу раскладки.
// Table of morse code, n elements
char* code[] = {
  ".-","-...","*--","--*","-**","*","***-","--**","**","*---",
  "-*-","*-**","--","-*","---","*--*","*-*","***","-","**-",
  "**-*","****","-*-*","---*","----","--*-","-*--","-**-","**-**","**--",
  "*-*-",
  "*----","**---","***--","****-","*****","-****","--***","---**","----*","-----",
  "......","*-*-*-","---***","-*-*-","-*--*-","*----*","*-**-*","-****-","-**-*","**--**","--**--",
  "-***-","********","*--*-*","**-*-",
  ""
};

// Кириллическая раскладка.
char* layoutEnglish[] = {
  "a","b","c","d","e","f","g","h","i","j",
  "k","l","m","n","o","p","q","r","s","t",
  "u","v","w","x","y","z","1","2","3","4","5","6","7","8","9","0",
  ".",",",":",";","(","\'","\"","-","/","?","!",
  " *DELIMITER* "," *ERR* ","@"," *END* ",
  ""
  };

char** currentLayout;
char** newLayout;
int counter_high = 0;
int counter_low = 0;
int i;
String ans="";

void setup(){
  Serial.begin(115200);
  Serial4.begin(9600);
  pinMode(led, OUTPUT);  

  morseSymbolLen = 0;
  newMorseSignal = MORSE_EMPTY;
}

void loop(){
   unsigned long ts= micros();
  //while(Serial4.available()==0){}
  while(Serial4.available()>0){
    char c=Serial4.read();
    Serial.print(c);
    ans+=c;
    
  }
// while(micros()-ts<500000){}
  Serial.print("ans is: ");
  Serial.println(ans);
  int LDRReading = analogRead(LDR_Pin); 
  if (LDRReading >= 500){
  counter_high++ ;
   if ( counter_low > 0 ){
  //  Serial.print("Low\t");
 //   Serial.print(counter_low);
//     Serial.print("\n");
   }
   if ( counter_low > 200) {
    //  for (i = 0; i< morseSymbolLen; i++) {
     
   // Serial.print( currentLayout[i]);
    // }
    sendMorseSymbol();
    morseSymbolLen=0;
      Serial.println();
  }
     counter_low=0;
     digitalWrite(led, HIGH);

  
  } else {
//   Serial.print(".");
  counter_low++;
  if ( counter_high > 0 ){
//      Serial.print("High\t");  
//   Serial.print(counter_high);

  }
  if ( (counter_high < 1200 ) &&( counter_high >350)){
//      Serial.print(counter_high);
    Serial.print(".");
    newMorseSignal="*";
    morseSymbol[morseSymbolLen++] = newMorseSignal;
   // currentLayout[morseSymbolLen]=".";
   // morseSymbolLen=morseSymbolLen+1;
  }
  if ( counter_high > 1200 ){
 //         Serial.print(counter_high);
        Serial.print("-");
        newMorseSignal="-";
        morseSymbol[morseSymbolLen++] = newMorseSignal;
       // currentLayout[morseSymbolLen]="-";
       //     morseSymbolLen=morseSymbolLen+1;
  }

      counter_high=0;
      digitalWrite(led, LOW);

  }
}

void sendMorseSymbol() {
  boolean est;
  int i, j;
  est=-1;
  if (morseSymbolLen < 1) {
    return;
  }
 

   Serial.print(morseSymbolLen);
   
      // Символ из таблицы кодов Морзе соответствует введенному символу.
      //  Отправим символ на компьютер.
    String str1;
    String strm;
    str1="";
    for (i=0;i<morseSymbolLen;i++){  
     str1=str1+morseSymbol[i];
    }
   //  Serial.print(code[6]);
     
      
     
      
    for (i=0;i<56;i++){
      String str2(code[i]);
          
      if (str1.compareTo(str2)==0){
        //Serial.print(str1);
       // Serial.print("est");
       Serial.print(str2);
       est=true;
      break;
      }
       }
      if (est!=-1){
      Serial.print(layoutEnglish[i]);
     
    }
      morseSymbolLen = 0;
      return;
   
}

