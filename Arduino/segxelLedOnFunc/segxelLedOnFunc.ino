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

void panelOff(){
  lc.clearDisplay(0);
  lc.clearDisplay(1);
}

void loop() {
  for(int i=0;i<16;i++){
    for(int j=0;j<8;j++){
      ledOn(i,j, true);
      delay(30);
    }
  }
  delay(1000);
  for(int i=0;i<8;i++){
    for(int j=0;j<16;j++){
      ledOn(j,i, false);
      delay(30);
    }
  }
}
