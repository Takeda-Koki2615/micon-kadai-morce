#include <Wire.h>
#include <I2CLiquidCrystal.h>
I2CLiquidCrystal lcd(20, (bool)false);
 
const int buttonPin = 26; // ボタンが接続されているピン
const int togglePin = 7; // トグルスイッチが接続されているピン
unsigned long pressStartTime;
bool buttonState = false;
char morseCode[5];
unsigned long debounceDelay = 30; // デバウンスのための遅延
unsigned long shortoo = 500; // 短点の基準時間
unsigned long longuu = 1500; // 長点の基準時間
 
int anana;
int morseIndex = 0;
int i;
 
void setup() {
  Serial.begin(9600);
 
  pinMode(buttonPin, INPUT);
  pinMode(togglePin, INPUT_PULLUP); // トグルスイッチ
 
  Wire1.setSDA(18);
  Wire1.setSCL(19);
  lcd.setWire(&Wire1);
 
  lcd.begin(8, 2);
  lcd.setCursor(0, 0);
  lcd.print("Morse In");
}
 
void loop() {
  int aho = 0;
 
  int tintin = analogRead(buttonPin);
  if(tintin >= 30){
    anana = false;
  }else{
    anana = true;
  }
 
 bool currentButtonState = anana;//!digitalRead(buttonPin); // 押されるとLOWになる
 
 if (currentButtonState && !buttonState) {
    // ボタンが押された瞬間
    pressStartTime = millis();
 
    while(aho == 0){
      tintin = analogRead(buttonPin);
      if(tintin >= 30){
        currentButtonState = false;
        Serial.println("bbbbbbbbb");
      }else{
        currentButtonState = true;
        Serial.println("jjjjjjjjjjj");
      }
 
      if (currentButtonState && !buttonState) {
        Serial.println("wwwwwwwww");
        // ボタンが離された瞬間
        unsigned long pressDuration = millis() - pressStartTime;
        Serial.print("pressDuration : ");
        Serial.println(pressDuration);
        if (pressDuration >= debounceDelay && morseIndex < 4) {
          for(i = morseIndex; i < morseIndex + 1; ++i) {
            if (pressDuration < shortoo) {
              // 短い押し（・）
              morseCode[i] = '0';
              aho++;
              //Serial.println(i);
            } else if (pressDuration >= shortoo && pressDuration < longuu) {
              // 長い押し（-）
              morseCode[i] = '1';
              aho++;
            }
            morseIndex++;
            morseCode[morseIndex] = '\0';
          }
          Serial.println("grfsg");
        }
        Serial.println("tttttttt");
      }
    }
  }
 
  // トグルスイッチがONのときにモールス信号を文字に変換してLCDに表示
  if (digitalRead(togglePin) == HIGH) {
    morseCode[morseIndex] = '\0';
    lcd.setCursor(0, 1);
    lcd.print(morseToChar(morseCode)); // モールス信号を文字に変換して表示
 
//    Serial.print("morseToChar(morseCode) : ");
//    Serial.println(morseToChar(morseCode));
 
    delay(1500); //1.5秒間表示
    memset(morseCode, 0, sizeof(morseCode)); //配列をリセット
    morseIndex = 0;
    Serial.println("tinkpo");
  }
  lcd.setCursor(0, 1);
  lcd.print("        "); //LCDをリセット
 
  //Serial.println(morseIndex);
}
 
char morseToChar(const char *code) {
  if (strcmp(code, "01") == 0) return 'A';
  if (strcmp(code, "1000") == 0) return 'B';
  if (strcmp(code, "1010") == 0) return 'C';
  if (strcmp(code, "100") == 0) return 'D';
  if (strcmp(code, "0") == 0) return 'E';
  if (strcmp(code, "0010") == 0) return 'F';
  if (strcmp(code, "110") == 0) return 'G';
  if (strcmp(code, "0000") == 0) return 'H';
  if (strcmp(code, "00") == 0) return 'I';
  if (strcmp(code, "0111") == 0) return 'J';
  if (strcmp(code, "101") == 0) return 'K';
  if (strcmp(code, "0100") == 0) return 'L';
  if (strcmp(code, "11") == 0) return 'M';
  if (strcmp(code, "10") == 0) return 'N';
  if (strcmp(code, "111") == 0) return 'O';
  if (strcmp(code, "0110") == 0) return 'P';
  if (strcmp(code, "1101") == 0) return 'Q';
  if (strcmp(code, "010") == 0) return 'R';
  if (strcmp(code, "000") == 0) return 'S';
  if (strcmp(code, "1") == 0) return 'T';
  if (strcmp(code, "001") == 0) return 'U';
  if (strcmp(code, "0001") == 0) return 'V';
  if (strcmp(code, "011") == 0) return 'W';
  if (strcmp(code, "1001") == 0) return 'X';
  if (strcmp(code, "1011") == 0) return 'Y';
  if (strcmp(code, "1100") == 0) return 'Z';
  return '?'; // 不明なコードの場合
}