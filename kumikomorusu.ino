#include <I2CLiquidCrystal.h>
#include <Wire.h>

int morse[5];

// LCD制御用オブジェクト(lcd)の宣言
I2CLiquidCrystal lcd(20, (bool)false);


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


  while(sw==1){
	sw_t++;
	sleepus(100);
  }

  if(sw_t=<3000){
      morse[i]=0;
  }else {
      morse[i]=1;
  }

  i++;
  sw_t=0;

  while(sw==0){
      sw_t++;
	sleepus(100);
  }


  if(sw_t<7000){
      //たけちゃん頑張りポイント

	morse={\0,\0,\0,\0};
  }


}
