/*
 * LED test SEGXEL
 *  
 *  CHIP 0
 *  
 *    00  00  00  00  00  00  00  00
 *  01  01  01  01  01  01  01  01
 *    02  02  02  02  02  02  02  02  
 *  03  03  03  03  03  03  03  03
 *    04  04  04  04  04  04  04  04  
 *  05  05  05  05  05  05  05  05  
 *    06  06  06  06  06  06  06  06
 *  07  07  07  07  07  07  07  07  
 *    15  15  15  15  xx  15  15  15
 *  08  08  08  08  08  08  08  08  
 *    09  09  09  09  09  09  09  09
 *  10  10  10  10  10  10  10  10  
 *    11  11  11  11  11  11  11  11
 *  12  12  12  12  12  12  12  12  
 *    13  13  13  13  13  13  13  13
 *  14  14  14  14  14  14  14  14  
 *  
 *  THe LED on chip 1, line 0, column 4 is misplaced.
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

void loop() { 
  lines();
}
