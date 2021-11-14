#include "pitches.h"
#define Button_Pin1 33 //遊戲按鈕
#define Button_Pin2 14  //開始按鈕1
#define Button_Pin3 25  //開始按鈕2
#include <Wire.h>               // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306Wire.h"        // legacy: #include "SSD1306.h"
SSD1306Wire display(0x3c, 21, 22);
int freq = 2000;
int channel = 0;
int resolution = 8;

int tonePin = 12; //蜂鳴器
unsigned long starttime; //紀錄遊戲開始的時間
unsigned long finishtimeplayer; //紀錄遊戲結束的時間
unsigned long nowtime=0; 
unsigned long time1p; //1P的時間
unsigned long time2p; //2P的時間
unsigned long timeplayer; //紀錄玩家的時間
bool btnPressed1 =false;
bool btnPressed2 =false;
bool btnPressed3 =false;
int g1=0;
int g2=0;
void setup() {
  Serial.begin(9600);
  ledcSetup(channel, freq, resolution);
  ledcAttachPin(tonePin, channel);
  pinMode(Button_Pin1, INPUT);
  pinMode(Button_Pin2, INPUT);
  pinMode(Button_Pin3, INPUT);
  pinMode(27, OUTPUT);
  pinMode(26, OUTPUT);

  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
}

void loop(){
  if(digitalRead(Button_Pin2) == HIGH && btnPressed1 == false){
    int delaytime =  random(1,4);
    delaytime =delaytime*1000;
    delay(delaytime); 
    ledcWriteTone(channel,NOTE_E5);
    starttime = millis();
    g1=1;//g1=1遊戲開始
    btnPressed1 = true;
  }
  //偵測當按鈕放開(LOW),設定btnPressed為否
  else if(digitalRead(Button_Pin2) == LOW && btnPressed1 == true){
    btnPressed1 = false;
  }
  if(digitalRead(Button_Pin3) == HIGH && btnPressed2 == false){
    int delaytime =  random(1,4);
    delaytime =delaytime*1000;
    delay(delaytime); 
    ledcWriteTone(channel,NOTE_E5);
    starttime = millis();
    g2=1;//g2=1遊戲開始
    btnPressed2 = true;
  }
  //偵測當按鈕放開(LOW),設定btnPressed為否
  else if(digitalRead(Button_Pin3) == LOW && btnPressed2 == true){
    btnPressed2 = false;
  }
  while(g1==1){

    if(digitalRead(Button_Pin1) == HIGH){
    finishtimeplayer = millis();    
    timeplayer=finishtimeplayer-starttime;
    ledcWriteTone(0,0);
    time1p = timeplayer;
    g1=0;}
    }
  while(g2==1){    
    if(digitalRead(Button_Pin1) == HIGH){
    finishtimeplayer = millis();    
    timeplayer=finishtimeplayer-starttime;
    ledcWriteTone(0,0);
    time2p = timeplayer;
    g2=0;}
    }
if(time2p!=0&&time1p!=0&&g2==0&&g1==0){
  display.clear();
  String stringOne = String(time1p, DEC);
  String stringtwo = String(time2p, DEC);
  display.drawString(0, 0, "time1p");
  display.drawString(60,0 , stringOne);
  display.drawString(70, 11, "milliseconds");
  display.drawString(0, 22, "time2p");
  display.drawString(60,22 , stringtwo);
  display.drawString(70, 33, "milliseconds");
  if(time2p>time1p){display.drawString(0, 44, "1p WIN!!!");}
  if(time2p<time1p){display.drawString(0, 44, "2p WIN!!!");}
  display.display();

  }
}
