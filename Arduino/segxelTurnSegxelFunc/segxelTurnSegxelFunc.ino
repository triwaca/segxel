/*
 * LED test SEGXEL
 * 
 *  Funcion ledOn can turn any LED correctly on the matrix
 *  Example turn ON every led on crescent order
 *  
 */

#include "LedControl.h"

/*
 pin 12 is connected to the DataIn 
 pin 11 is connected to the CLK 
 pin 10 is connected to LOAD 
 We have only a single MAX72XX.
 */
LedControl lc=LedControl(12,11,10,2);

unsigned long delaytime=10;

void setup() {
   int devices=lc.getDeviceCount();
  for(int address=0;address<devices;address++) {
    lc.shutdown(address,false);
    lc.setIntensity(address,8);
    lc.clearDisplay(address);
  }
  lc.shutdown(0,false);
  lc.shutdown(1,false);
  lc.setIntensity(0,5);
  lc.setIntensity(1,5);
  lc.clearDisplay(0);
  lc.clearDisplay(1);
}

void lines(){
  // Show lines scanning from top to bottom
  for(int line=0;line<8;line++){
    for(int column=0;column<8;column++){
      lc.setLed(0,line,column,true);
    }
    delay(50);
    lc.clearDisplay(0);
  }
  for(int column=0;column<8;column++){
    lc.setLed(1,0,column,true);
  }
  delay(50);
  lc.clearDisplay(1);
  for(int line=7;line>0;line--){
    for(int column=0;column<8;column++){
      lc.setLed(1,line,column,true);
    }
    delay(50);
    lc.clearDisplay(1);
  }
}

void ledOn(int lin, int col, bool value){
  /* 
  
  var lin goes from 0 to 15
  var col goes from 0 to 7 

   */
  if(lin<8){
    lc.setLed(0,lin,7-col,value);
  } else if(lin==8){
    if(col==4){
      //não faz nada | led posicionado errado
    } else if(col==0){
      ledOn(8,8, value); //bug no led
    } else {
      lc.setLed(1,0,col-1,value);
    }
  } else {
    lc.setLed(1,16-lin,col,value);
  }
}

void clearDisplay(){
  lc.clearDisplay(0);
  lc.clearDisplay(1);
}

void turnSegxelOn(int x, int y, bool h, bool v){
  ledOn(y*2,x,h);
  ledOn(y*2+1,x,v);
}

void printNumber(int x, int y, int number){
  switch(number){
    case 1:
      turnSegxelOn(x,y,0,1);
      turnSegxelOn(x+1,y,0,0);
      turnSegxelOn(x,y+1,0,1);
      turnSegxelOn(x+1,y+1,0,0);
      turnSegxelOn(x,y+2,0,0);
      break;
    case 2:
      turnSegxelOn(x,y,1,0);
      turnSegxelOn(x+1,y,0,1);
      turnSegxelOn(x,y+1,1,1);
      turnSegxelOn(x+1,y+1,0,0);
      turnSegxelOn(x,y+2,1,0);
      break;
    case 3:
      turnSegxelOn(x,y,1,0);
      turnSegxelOn(x+1,y,0,1);
      turnSegxelOn(x,y+1,1,0);
      turnSegxelOn(x+1,y+1,0,1);
      turnSegxelOn(x,y+2,1,0);
      break;
    case 4:
      turnSegxelOn(x,y,0,1);
      turnSegxelOn(x+1,y,0,1);
      turnSegxelOn(x,y+1,1,0);
      turnSegxelOn(x+1,y+1,0,1);
      turnSegxelOn(x,y+2,0,0);
      break;
    case 5:
      turnSegxelOn(x,y,1,1);
      turnSegxelOn(x+1,y,0,0);
      turnSegxelOn(x,y+1,1,0);
      turnSegxelOn(x+1,y+1,0,1);
      turnSegxelOn(x,y+2,1,0);
      break;
    case 6:
      turnSegxelOn(x,y,1,1);
      turnSegxelOn(x+1,y,0,0);
      turnSegxelOn(x,y+1,1,1);
      turnSegxelOn(x+1,y+1,0,1);
      turnSegxelOn(x,y+2,1,0);
      break;
    case 7:
      turnSegxelOn(x,y,1,0);
      turnSegxelOn(x+1,y,0,1);
      turnSegxelOn(x,y+1,0,0);
      turnSegxelOn(x+1,y+1,0,1);
      turnSegxelOn(x,y+2,0,0);
      break;
    case 8:
      turnSegxelOn(x,y,1,1);
      turnSegxelOn(x+1,y,0,1);
      turnSegxelOn(x,y+1,1,1);
      turnSegxelOn(x+1,y+1,0,1);
      turnSegxelOn(x,y+2,1,0);
      break;
    case 9:
      turnSegxelOn(x,y,1,1);
      turnSegxelOn(x+1,y,0,1);
      turnSegxelOn(x,y+1,1,0);
      turnSegxelOn(x+1,y+1,0,1);
      turnSegxelOn(x,y+2,1,0);
      break;
    case 0:
      turnSegxelOn(x,y,1,1);
      turnSegxelOn(x+1,y,0,1);
      turnSegxelOn(x,y+1,0,1);
      turnSegxelOn(x+1,y+1,0,1);
      turnSegxelOn(x,y+2,1,0);
      break;
  }

}

void loop() {
  for(int i=0;i<10;i++){
    printNumber(1,1,i);
    delay(500);
  }
  clearDisplay();
  for(int i=0;i<10;i++){
    printNumber(0,0,random(10));
    printNumber(2,0,random(10));
    printNumber(4,0,random(10));
    printNumber(6,0,random(10));
    printNumber(0,5,random(10));
    printNumber(2,5,random(10));
    printNumber(4,5,random(10));
    printNumber(6,5,random(10));
    delay(500);
  }
  clearDisplay();
}
