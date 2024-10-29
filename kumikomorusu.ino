#include <I2CLiquidCrystal.h>
#include <Wire.h>

// LCD制御用オブジェクト(lcd)の宣言
I2CLiquidCrystal lcd(20, (bool)false);

//スイッチの0/1判定用外部変数
int t1,t2,t3,t4,t5,t6;

int str=0;

void setup() {
  // LCD制御に使用するピンの設定
  Wire1.setSDA(18);
  Wire1.setSCL(19);
  lcd.setWire(&Wire1);

  // LCDの表示範囲を設定。
  lcd.begin(8, 2); // 8文字x2行

  pinMode(17,INPUT_PULLDOWN);                                        

}

void loop() {
  int sw_t;
  int sw = gpio_get(17); 

  while(1){
    while(sw==1){
      sw_t++;
    }
    if(sw_t=<t1){
      morse[i]=0;
    }else {
      morse[i]=1;
    }
    i++;
    sw_t=0;
    while(sw==0){
      sw_t++;
    }
    if(sw_t>t2){
      break;
    }
  }

}

