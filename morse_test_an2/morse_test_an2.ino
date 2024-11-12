#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 8, 2); /
const int buttonPin = 2; // ボタンが接続されているピン
const int togglePin = 8; // トグルスイッチが接続されているピン
unsigned long pressStartTime;
bool buttonState = false;
String morseCode = "";
unsigned long debounceDelay = 50; // デバウンスのための遅延
unsigned long shortPressDuration = 500; // 短点の基準時間
unsigned long longPressDuration = 1500; // 長点の基準時間
void setup() {
 pinMode(buttonPin, INPUT_PULLUP); // プルアップでボタン接続
 pinMode(togglePin, INPUT_PULLUP); // トグルスイッチもプルアップ
 lcd.begin();
 lcd.backlight();
 lcd.setCursor(0, 0);
 lcd.print("Morse Input");
}
void loop() {
 bool currentButtonState = !digitalRead(buttonPin); // 押されるとLOWになる
 if (currentButtonState && !buttonState) {
   // ボタンが押された瞬間
   pressStartTime = millis();
 } else if (!currentButtonState && buttonState) {
   // ボタンが離された瞬間
   unsigned long pressDuration = millis() - pressStartTime;
   if (pressDuration >= debounceDelay) {
     if (pressDuration < shortPressDuration) {
       // 短い押し（・）
       morseCode += ".";
     } else if (pressDuration >= shortPressDuration && pressDuration < longPressDuration) {
       // 長い押し（－）
       morseCode += "-";
     }
   }
 }
 buttonState = currentButtonState; // ボタンの状態を更新
 // トグルスイッチがONのときにモールス信号を文字に変換してLCDに表示
 if (digitalRead(togglePin) == HIGH) {
   lcd.setCursor(0, 1);
   lcd.print(morseToChar(morseCode)); // モールス信号を文字に変換して表示
   morseCode = ""; // 表示後にモールスコードをリセット
 }
}
// モールス信号を文字に変換する関数
char morseToChar(String code) {
 if (code == ".-") return 'A';
 if (code == "-...") return 'B';
 if (code == "-.-.") return 'C';
 if (code == "-..") return 'D';
 if (code == ".") return 'E';
 if (code == "..-.") return 'F';
 if (code == "--.") return 'G';
 if (code == "....") return 'H';
 if (code == "..") return 'I';
 if (code == ".---") return 'J';
 if (code == "-.-") return 'K';
 if (code == ".-..") return 'L';
 if (code == "--") return 'M';
 if (code == "-.") return 'N';
 if (code == "---") return 'O';
 if (code == ".--.") return 'P';
 if (code == "--.-") return 'Q';
 if (code == ".-.") return 'R';
 if (code == "...") return 'S';
 if (code == "-") return 'T';
 if (code == "..-") return 'U';
 if (code == "...-") return 'V';
 if (code == ".--") return 'W';
 if (code == "-..-") return 'X';
 if (code == "-.--") return 'Y';
 if (code == "--..") return 'Z';
 return '?'; // 不明なコードの場合
}