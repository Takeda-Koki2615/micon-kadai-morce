#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCDの初期化（I2Cアドレス0x27を使用）
LiquidCrystal_I2C lcd(20, (bool)false);
 

// モールス符号を記録するための変数
String morseCode = "";
int lastClockTime = 0;
bool isDot = false; // トンかツーかのフラグ


void setup() {
  pinMode(clockPin, INPUT);
  lcd.begin(8, 2);
  lcd.setCursor(0,0);
  lcd.print("Morse Decoder");


}

 
void loop() {
  for(int i = 0; i < 8; i++;) {
    char str[9];
    sprintf(str, "%d", sw_t);
  }
  if (digitalRead(clockPin) == HIGH) {
    if (millis() - lastClockTime > 100) { 
      lastClockTime = millis();

 

      // トンかツーかを判定
      if (isDot) {
        morseCode += "0";
      } else {
        morseCode += "1";
      }
      isDot = !isDot; // トンとツーを交互に
    }
  }

 

  // モールス符号が完成したら復号する
  if (morseCode.length() > 0 && millis() - lastClockTime > 2000) { // 2秒以上の間隔で文字の入力が終了
    char decodedChar = decodeMorse(morseCode);
    lcd.clear();
    lcd.print(str);
    lcd.print(decodedChar);
    morseCode = ""; // モールス符号をリセット
  }


}

 

// モールス符号を復号する関数
int decodeMorse(String code) {
  if (code == "01") return 'A';
  if (code == "1000") return 'B';
  if (code == "1010") return 'C';
  if (code == "100") return 'D';
  if (code == "0") return 'E';
  if (code == "0010") return 'F';
  if (code == "110") return 'G';
  if (code == "0000") return 'H';
  if (code == "00") return 'I';
  if (code == "0111") return 'J';
  if (code == "101") return 'K';
  if (code == "0100") return 'L';
  if (code == "11") return 'M';
  if (code == "10") return 'N';
  if (code == "111") return 'O';
  if (code == "0110") return 'P';
  if (code == "1101") return 'Q';
  if (code == "010") return 'R';
  if (code == "000") return 'S';
  if (code == "1") return 'T';
  if (code == "001") return 'U';
  if (code == "0001") return 'V';
  if (code == "011") return 'W';
  if (code == "1001") return 'X';
  if (code == "1011") return 'Y';
  if (code == "1100") return 'Z';
  return '?'; // 未知の符号の場合
}

