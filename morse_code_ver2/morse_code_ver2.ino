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
 
int morseIndex = 0;
 
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
  int hanntei = analogRead(buttonPin);
  bool currentButtonState = (hanntei < 30); // ボタンが押されているかの判定
 
  // ボタンが押された瞬間
  if (currentButtonState && !buttonState) {
    pressStartTime = millis(); // 押された時間を記録
  }
 
  // ボタンが離された瞬間
  if (!currentButtonState && buttonState) {
    unsigned long pressDuration = millis() - pressStartTime; // 押されていた時間を計算
 
    if (pressDuration >= debounceDelay && morseIndex < 4) {
      if (pressDuration < shortoo) {
        // 短い押し（・）
        morseCode[morseIndex++] = '0';
      } else if (pressDuration >= shortoo && pressDuration < longuu) {
        // 長い押し（-）
        morseCode[morseIndex++] = '1';
      }
      morseCode[morseIndex] = '\0'; // 終端文字を追加
    }
  }
 
  buttonState = currentButtonState; // 現在の状態を保存
 
  // トグルスイッチがONのときにモールス信号を文字に変換してLCDに表示
  if (digitalRead(togglePin) == HIGH && morseIndex > 0) {
    char decodedChar = morseToChar(morseCode); // モールス信号を文字に変換
    lcd.setCursor(0, 1);
    lcd.print(decodedChar); // LCDに表示
 
    delay(1500); // 1.5秒間表示
    memset(morseCode, 0, sizeof(morseCode)); // 配列をリセット
    morseIndex = 0; // インデックスをリセット
  }
 
  lcd.setCursor(0, 1);
  lcd.print("        "); // LCDをリセット
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
}