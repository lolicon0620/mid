#include <Wire.h>
#include "SSD1306Wire.h"
#include "pictures.h"
#include "pitches.h"
#define Button_Pin 14
SSD1306Wire  display(0x3c, 21, 22);

void Drawbackground(){
  display.drawXbm(0, 0, bg_width, bg_height, pic[0]);
  display.display();
}//畫出背景
void Drawbb(int b_x,int b_y){
    display.drawXbm(b_x, b_y, battery3_width, battery3_height, pic[2]);
    display.display()
    ;}
    void Drawaa(int b_x,int b_y){
    display.drawXbm(b_x, b_y, battery3_width, battery3_height, pic[1]);
    display.display();
}//畫出角色

int freq = 2000;
int channel = 0;
int resolution = 8;

int tonePin = 12;

int melody[] = {
  NOTE_DS8,0, NOTE_DS8, 0, NOTE_DS8, 0, NOTE_DS8, 0,
  NOTE_DS8,0
};
int noteDurations[] = {
  8, 8, 8, 8, 8, 8, 8, 8, 8, 8
};

unsigned long currentTime = 0, tonePreviousTime = 0, picPreviousTime = 0;
int pauseBetweenNotes = 0;
int noteDuration = 0;
int thisNote = 0;
boolean nextTone = true;
int dropY = battery3_height;
boolean nextPic = true;


void setup() {
   Serial.begin(115200);
   ledcSetup(channel, freq, resolution);
   ledcAttachPin(tonePin, channel);

   //OLED setting
   display.init();
   display.flipScreenVertically();
   display.clear(); //清除螢幕和緩衝區(clear)
   Drawbackground();
}

void loop() {
  //loop迴圈，重複執行不停止
  if (digitalRead(14) == HIGH) {
    Serial.println("Coming");//偵測到有人經過
  Drawbb(0, 0); //畫出角色
  display.clear();
  }
  else
  ledcWriteTone(channel, 0);
   Drawaa(0, 0); //畫出角色
    display.clear();
    //buzzer
        Serial.println(digitalRead(Button_Pin));
    if(nextTone){
      noteDuration = 1300 / noteDurations[thisNote];
      ledcWriteTone(channel, melody[thisNote]);
      pauseBetweenNotes = noteDuration * 1.3;
      nextTone = false;
    }

    //畫出角色與其位置

    currentTime = millis(); //記錄現在時間
    if((currentTime - tonePreviousTime) > noteDuration){
      ledcWriteTone(channel, 0);
    } //buzzer停止播放
    if((currentTime - tonePreviousTime) > (pauseBetweenNotes)){
      nextTone = true;
      thisNote++;
      if(thisNote == 10) thisNote = 0;
      tonePreviousTime = currentTime; 
    } //buzzer播放下一個音
       Drawaa(0,0); //角色每150毫秒移動一次
    
}
