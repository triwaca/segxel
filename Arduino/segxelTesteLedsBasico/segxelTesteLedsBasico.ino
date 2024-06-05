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
  lc.setIntensity(0,1);
  lc.setIntensity(1,5);
  lc.clearDisplay(0);
  lc.clearDisplay(1);
}

void single() {
  for(int row=0;row<8;row++) {
    for(int col=0;col<8;col++) {
      delay(delaytime);
      lc.setLed(0,row,col,true);
      delay(delaytime);
      for(int i=0;i<col;i++) {
        lc.setLed(0,row,col,false);
        delay(delaytime);
        lc.setLed(0,row,col,true);
        delay(delaytime);
      }
    }
  }
  for(int row=0;row<8;row++) {
    for(int col=0;col<8;col++) {
      delay(delaytime);
      lc.setLed(1,row,col,true);
      delay(delaytime);
      for(int i=0;i<col;i++) {
        lc.setLed(1,row,col,false);
        delay(delaytime);
        lc.setLed(1,row,col,true);
        delay(delaytime);
      }
    }
  }
}

void loop() { 
  //writeArduinoOnMatrix();
  //rows();
  //columns();
  single();
  delay(5000);
  lc.clearDisplay(0);
  lc.clearDisplay(1);
}
