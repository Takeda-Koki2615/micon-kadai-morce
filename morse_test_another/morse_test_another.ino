#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 8, 2); // LCDのI2Cアドレスは0x27。16x2のLCDを仮定。
const int buttonPin = 2; // ボタンが接続されているピン
bool buttonState = false;
unsigned long pressStartTime;
unsigned long debounceDelay = 50; // デバウンス用
unsigned long shortPressDuration = 500; // 短点（・）の基準時間
unsigned long longPressDuration = 1500; // 長点（－）の基準時間
void setup() {
 pinMode(buttonPin, INPUT_PULLUP); // プルアップでボタン接続
 lcd.begin();
 lcd.backlight();
 lcd.setCursor(0, 0);
 lcd.print("Morse Decoder");
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
       lcd.setCursor(0, 1);
       lcd.print(".");
     } else if (pressDuration >= shortPressDuration && pressDuration < longPressDuration) {
       // 長い押し（－）
       lcd.setCursor(0, 1);
       lcd.print("-");
     }
   }
 }
 buttonState = currentButtonState; // ボタンの状態を更新
}