#include <Wire.h>
#include <I2CLiquidCrystal.h>
I2CLiquidCrystal lcd(20, (bool)false);

const int buttonPin = 26; // ボタンが接続されているピン
const int togglePin = 7; // トグルスイッチが接続されているピン
unsigned long pressStartTime;
bool buttonState = false;
String morseCode = "";
unsigned long debounceDelay = 50; // デバウンスのための遅延
unsigned long shortoo = 500; // 短点の基準時間
unsigned long longuu = 1500; // 長点の基準時間

int anana;

void setup() {
 Serial.begin(9600);

 pinMode(buttonPin, INPUT); // プルアップでボタン接続
 pinMode(togglePin, INPUT_PULLUP); // トグルスイッチもプルアップ

  Wire1.setSDA(18);
  Wire1.setSCL(19);
  lcd.setWire(&Wire1);

 lcd.begin(8, 2);
 //lcd.backlight();
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
 if (currentButtonState && buttonState) {
   // ボタンが押された瞬間
   pressStartTime = millis();

   while(aho == 1){
     buttonState = currentButtonState; // ボタンの状態を更新
    if (currentButtonState && !buttonState) {
    // ボタンが離された瞬間
    unsigned long pressDuration = millis() - pressStartTime;
    Serial.print("pressDuration : ");
    Serial.println(pressDuration);
      if (pressDuration >= debounceDelay) {
        if (pressDuration < shortoo) {
         // 短い押し（・）
         morseCode += ".";
         aho++;
        } else if (pressDuration >= shortoo && pressDuration < longuu) {
         // 長い押し（－）
         morseCode += "-";
         aho++;
        }
      }
    }
   }
 }
 /*
   }
  } else if (!currentButtonState && !buttonState) {
   // ボタンが離された瞬間
   unsigned long pressDuration = millis() - pressStartTime;
   Serial.print("pressDuration : ");
   Serial.println(pressDuration);
   if (pressDuration >= debounceDelay) {
     if (pressDuration < shortoo) {
       // 短い押し（・）
       morseCode += ".";
     } else if (pressDuration >= shortoo && pressDuration < longuu) {
       // 長い押し（－）
       morseCode += "-";
     }
   }
 }
 */
 buttonState = currentButtonState; // ボタンの状態を更新
 // トグルスイッチがONのときにモールス信号を文字に変換してLCDに表示
 if (digitalRead(togglePin) == HIGH) {
   lcd.setCursor(0, 1);
   lcd.print(morseToChar(morseCode)); // モールス信号を文字に変換して表示

    Serial.print("morseToChar(morseCode) : ");
    Serial.println(morseToChar(morseCode));

   delay(1000);
   morseCode = ""; // 表示後にモールスコードをリセット
   Serial.println("tinkpo");
 }


}
// モールス信号を文字に変換する関数
char morseToChar(String code) {
 if (morseCode == ".-") return 'A';
 if (morseCode == "-...") return 'B';
 if (morseCode == "-.-.") return 'C';
 if (morseCode == "-..") return 'D';
 if (morseCode == ".") return 'E';
 if (morseCode == "..-.") return 'F';
 if (morseCode == "--.") return 'G';
 if (morseCode == "....") return 'H';
 if (morseCode == "..") return 'I';
 if (morseCode == ".---") return 'J';
 if (morseCode == "-.-") return 'K';
 if (morseCode == ".-..") return 'L';
 if (morseCode == "--") return 'M';
 if (morseCode == "-.") return 'N';
 if (morseCode == "---") return 'O';
 if (morseCode == ".--.") return 'P';
 if (morseCode == "--.-") return 'Q';
 if (morseCode == ".-.") return 'R';
 if (morseCode == "...") return 'S';
 if (morseCode == "-") return 'T';
 if (morseCode == "..-") return 'U';
 if (morseCode == "...-") return 'V';
 if (morseCode == ".--") return 'W';
 if (morseCode == "-..-") return 'X';
 if (morseCode == "-.--") return 'Y';
 if (morseCode == "--..") return 'Z';
 return '?'; // 不明なコードの場合
}