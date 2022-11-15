#include <FastLED.h>
#define DATA_PIN    7
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS    120
unsigned long timer1=0;
unsigned long timer2=0;
CRGB leds[NUM_LEDS];
void setup() 
{
FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
Serial.begin(9600); // setup serial
}
long sensor_value = 0; //Enter Your threshold value here
long abs_value = 0;
int lit_led=10;
int max_brightness=250;
int min_brightness=150;
int pattern_changer=0;
int digital_val=0;
int start_led=0;
int end_led=59;
int looper=-1;
int changer=0;
int glow1=0;

int arr_R[]={255,2,3,132,252,0,3,252,252};
int arr_G[]={59,252,136,3,3,252,11,3,202};
int arr_B[]={59,236,252,252,227,10,252,3,0};
int total=0;
void loop() 
{
  timer2=millis();
  total=0;  
  if(timer2%1000==0)
  {
    glow1++;
    glow1=glow1%2;
    Serial.println(glow1);
  }
  FastLED.clear();
  if(glow1==0){
    delay(20);
    FastLED.show();
    }

for(int i=0;i<5;i++)  
  {
    sensor_value=digitalRead(6);
    if(sensor_value==0)
      total+=1;
    delay(2);
  }
  //Serial.println(total*total);  
  int abs=total*total;
if(abs>=2)
{

  if(abs_value<=6)
  {
    looper=1;
  }
  else 
  {
    looper=2;
  }

switch(looper)
{
case 1:
{

lit_led=45;
start_led=random(1,NUM_LEDS-lit_led)-1;//outputs randoom num b/w 1 to 30 
for(int i=0;i<lit_led;i++)
{
  if(glow1==0){
  leds[start_led+i]=CRGB(arr_R[changer],arr_G[changer],arr_B[changer]);
  FastLED.setBrightness(min_brightness);
  }
  else
  {
  leds[start_led+i]=CRGB(arr_G[changer],arr_R[changer],arr_B[changer]);
  FastLED.setBrightness(min_brightness);
  }
}
  

}
case 2:
{
lit_led=15;
start_led=random(0,NUM_LEDS-lit_led)-1;
for(int i=0;i<lit_led;i++)
{
  leds[start_led+i]=CRGB(arr_R[changer],arr_G[changer],arr_B[changer]);
  FastLED.setBrightness(max_brightness);
}

}
FastLED.show();
}
}
timer1+=1;
if(timer1>500)
  timer1=0;

if(timer1==500)
{
  //Serial.println(changer);
  timer1=0;
  changer++;
  changer=changer%9;
}
}
//for(int i=0;i<lit_led;i++)
//  {
//  leds[start_led+i]=CRGB(0,0,0);
//  }




