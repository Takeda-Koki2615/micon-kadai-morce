#include <I2CLiquidCrystal.h>
#include <Wire.h>
 
#define T1 200  // 「トン」の時間 (ミリ秒)
#define T2 600  // 「ツー」の時間 (ミリ秒)
 
int morse[5];  // モールス符号の配列
int i = 0;      // 配列のインデックス
 
// LCD制御用オブジェクト(lcd)の宣言
I2CLiquidCrystal lcd(20, (bool)false);
 
void setup() {
  // LCD制御に使用するピンの設定
  Wire1.setSDA(18);
  Wire1.setSCL(19);
  lcd.setWire(&Wire1);
 
  // LCDの表示範囲を設定
  lcd.begin(8, 2); // 8文字x2行
 
  
 
  pinMode(17, INPUT_PULLDOWN);  // ボタンの入力設定
}
 
void loop() {
  int sw_t = 0;
  int sw_t2 = 0;
  int sw = digitalRead(17); // ボタンの状態を読み取る
 
  // ボタンが押されている間にトンまたはツーをカウント
  while (sw == HIGH) {
    sw_t++;
    delay(10);  // 10msごとにカウントアップ
    sw = digitalRead(17);  // ボタン状態を更新
  }
 
  while(i > 0 && sw == LOW) {
    sw_t2++;
    delay(10);
    sw = digitalRead(17);
  }
  // 取得した「トン」や「ツー」の長さを判断
  if (sw_t > 0) {
    if (sw_t < T1) {
      morse[i] = 0;  // 「トン」を記録
    } else if (sw_t >= T1) {
      morse[i] = 1;  // 「ツー」を記録
    }
    i++;
  }
 
 
  // モールス符号が完成したら、復号する
  if (i > 0 && sw_t2 > 2000) {  // 2秒間の無操作後に復号
    String code = "";
    for (int j = 0; j < i; j++) {
      code += String(morse[j]);
    }
    char decodedChar = decodeMorse(code);
    // LCDに結果を表示
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Decoded: ");
    lcd.print(decodedChar);
 
    // 配列をリセット
    i = 0;
    memset(morse, 0, sizeof(morse));
  }
}
 
// モールス符号を復号する関数
char decodeMorse(String code) {
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
  return '?';  // 未知の符号の場合
}