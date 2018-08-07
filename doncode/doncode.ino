#include <WS2811Driver.h>

//Setup 60 GRB LED Strip on Launchpad pin 2
WS2811Driver ledStrip = WS2811Driver(120, 2, NEO_GRB);

volatile int var = 0;
volatile int targets = 0;
volatile int launched = 0;


void setup(void)
{

  uint16_t i;
  
  for(i=0; i<ledStrip.numPixels(); i++)
  {
    ledStrip.setPixelColor(i, 0, 0, 0);
  }
  
  ledStrip.setBrightness(255);      //Set LED strip brightness to max
  
  ledStrip.begin();        // configure P1.6 for output

  pinMode(P1_3, INPUT_PULLUP);
  attachInterrupt(P1_3, cycle, FALLING); // Interrupt is fired whenever button is pressed

  pinMode(P1_4, INPUT_PULLUP);
  attachInterrupt(P1_4, launch, FALLING); // Interrupt is fired whenever button is pressed

  pinMode(P1_5, INPUT_PULLUP);
  attachInterrupt(P1_5, drain, FALLING); // Interrupt is fired whenever button is pressed    

  pinMode(P1_7, INPUT_PULLUP);
  attachInterrupt(P1_7, standups, FALLING); // Interrupt is fired whenever button is pressed    
    

}

void loop() {



 
  switch (var) {
    case 0:   //--------------------------------------------------------PINBALL READY--------------------------------------------------------------//

     //ALL TARGETS
     theaterChaseRainbow(15);
     NEWtheaterChaseRainbow(15);
     break;



      
      //HIGHSCORE
      //bounce(ledStrip.Color(255, 0, 0), 27);
      //INVtheaterChase(ledStrip.Color(255, 51, 51), 64);
      //REVtheaterChase(ledStrip.Color(255, 128, 0), 64);      
      //INVtheaterChase(ledStrip.Color(255, 255, 0), 64);
      //REVtheaterChase(ledStrip.Color(255, 51, 51), 64);
      //REVtheaterChase(ledStrip.Color(255, 255, 0), 64);      
      //INVtheaterChase(ledStrip.Color(255, 128, 0), 64);
      //REVbounce(ledStrip.Color(0, 0, 0), 8);
      //break;
      
      //GAMEOVER
      //theaterChase(ledStrip.Color(255, 0, 0), 8);
      //theaterChase(ledStrip.Color(255, 0, 0), 16);
      //theaterChase(ledStrip.Color(255, 0, 0), 32);
      //theaterChase(ledStrip.Color(255, 0, 0), 64);
      //theaterChase(ledStrip.Color(255, 0, 0), 96);
      //REVtheaterChase(ledStrip.Color(255, 0, 0), 42);
      //INVtheaterChase(ledStrip.Color(255, 0, 0), 42);
      //REVtheaterChase(ledStrip.Color(255, 0, 0), 42);
      //INVtheaterChase(ledStrip.Color(255, 0, 0), 42);
      //REVtheaterChase(ledStrip.Color(255, 0, 0), 42);
      //var = 0;
      //REVcolorWipe(ledStrip.Color(0, 0, 0), 25); // Blank      
      //break;


      //ROLLOVER
      //bounce(ledStrip.Color(0, 0, 255), 1);
      //REVbounce(ledStrip.Color(0, 0, 0), 1);
      //break;
    
      //colorWipe(ledStrip.Color(0, 0, 255), 12); //             #0000FF
      //colorWipe(ledStrip.Color(127, 0, 255), 10); //           #7F00FF
      //colorWipe(ledStrip.Color(0, 0, 0), 8); //                Blank 
      //colorWipe(ledStrip.Color(255, 0, 10), 12); //            #FF0000
      //colorWipe(ledStrip.Color(127, 255, 0), 10); //           #80FF00
      //colorWipe(ledStrip.Color(0, 0, 0), 8); //                Blank
      //colorWipe(ledStrip.Color(0, 255, 0), 12); //             #00FF00
      //colorWipe(ledStrip.Color(0, 255, 127), 10); //           #00FF80
      //colorWipe(ledStrip.Color(0, 0, 0), 8); //                Blank      
      //break;
    case 1:    //--------------------------------------------------------PINBALL DRAINED-------------------------------------------------------//
      theaterChase(ledStrip.Color(127, 250, 255), 8);
      theaterChase(ledStrip.Color(127, 225, 255), 16);
      theaterChase(ledStrip.Color(127, 200, 255), 32);
      theaterChase(ledStrip.Color(127, 175, 255), 64);
      theaterChase(ledStrip.Color(127, 150, 255), 96);
      theaterChase(ledStrip.Color(127, 125, 255), 112);
      theaterChase(ledStrip.Color(127, 100, 255), 120);
      var = 0;
      colorWipe(ledStrip.Color(0, 0, 0), 15); // Blank      
      break;
    case 2:   //--------------------------------------------------------GAME IN-PROGRESS-------------------------------------------------------//  
      if (launched == 1) {
        theaterChaseRainbow(12);
        launched = 0;
      }
      rainbowCycle(1);              
      break;
    case 3:   //--------------------------------------------------------STAND-UP HIT-------------------------------------------------------//
      theaterChase2(ledStrip.Color(0, 0, 255), 50);
      theaterChase2(ledStrip.Color(255, 0, 10), 50);
      theaterChase2(ledStrip.Color(0, 255, 0), 50);
      var = 2;      
      break;            
    default:
      var == 2;   
  }
  
}

void cycle()                          //CYCLE THROUGH
{
  if (var < 3) {   
    var++; 
  }
  else {
    var = 0;
  }
}

void launch()                   //PINBALL LAUNCHED
{
  var = 2;
  launched = 1;
}


void drain()                //PINBALL DRAINED
{
  var = 1;
}

void standups()          //HIT TARGETS
{
  targets++;
  var = 3;
}




void InOut(uint32_t c, uint8_t wait) {
  if (var == 0) {
     int randNum = random(ledStrip.numPixels());
      for(uint16_t i=randNum; i<ledStrip.numPixels(); i++) {
          ledStrip.setPixelColor(i, c);
          ledStrip.show();
          delay(wait);

    }
  }
}




// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
 
  if (var == 0) {
      for(uint16_t i=0; i<ledStrip.numPixels(); i++) {
          ledStrip.setPixelColor(i, c);
          ledStrip.show();
          delay(wait);
    }
  }
}


void REVcolorWipe(uint32_t c, uint8_t wait) {
  if (var == 0) {
      for(uint16_t i=ledStrip.numPixels(); i>0; i--) {
          ledStrip.setPixelColor(i, c);
          ledStrip.show();
          delay(wait);
    }
  }
}





void REVbounce(uint32_t c, uint8_t wait) {
  int j=ledStrip.numPixels();
int jFlag=60;
  if (var == 0) {
      for(uint16_t i=0; i<ledStrip.numPixels()/2; i++) {
          
          j--;
          
          ledStrip.setPixelColor(i, c);
           ledStrip.show();
          ledStrip.setPixelColor(j, c);
           ledStrip.show();
          if(j==61)
          {
            j=ledStrip.numPixels();
          }
          
        //  ledStrip.show();
          delay(wait);
    }
  }
}



void bounce(uint32_t c, uint8_t wait) {
  
  int j=ledStrip.numPixels()/2;
  int jFlag=0;
  if (var == 0) {
      for(uint16_t i=ledStrip.numPixels()/2; i>0; i--) {
          
          j++;
          
          ledStrip.setPixelColor(i, c);
           ledStrip.show();
          ledStrip.setPixelColor(j, c);
           ledStrip.show();
          if(j==ledStrip.numPixels())
          {
            j=ledStrip.numPixels()/2;
          }
          
        //  ledStrip.show();
          delay(wait);
    }
  }
}





void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  if (var == 0) {
    for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
      if (var == 0) {
        for(i=0; i< ledStrip.numPixels(); i++) {
          ledStrip.setPixelColor(i, Wheel(((i * 256 / ledStrip.numPixels()) + j) & 255));
        }
        ledStrip.show();
        delay(wait);
      }
    }
  } 
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  if (var == 0 || var == 2) {
    for (int j=0; j<5; j++) {  //do 10 cycles of chasing
      for (int q=0; q < 3; q++) {
        for (int i=0; i < ledStrip.numPixels(); i=i+3) {
          ledStrip.setPixelColor(i+q, c);    //turn every third pixel on
        }
        ledStrip.show();
     
        delay(wait);
     
        for (int i=0; i < ledStrip.numPixels(); i=i+3) {
          ledStrip.setPixelColor(i+q, 0);        //turn every third pixel off
        }
      }
    }
  }
}


void REVtheaterChase(uint32_t c, uint8_t wait) {
  if (var == 0 || var == 2) {
    for (int j=0; j<5; j++) {  //do 10 cycles of chasing
      for (int q=0; q < 3; q++) {
        for (int i=0; i < ledStrip.numPixels(); i=i+3) {
          ledStrip.setPixelColor(i+q, c);    //turn every third pixel on
        }
        ledStrip.show();
     
        delay(wait);
     
        for (int i=0; i < ledStrip.numPixels(); i=i+3) {
          ledStrip.setPixelColor(i+q, 0);        //turn every third pixel off
          if (j=5)
          i++;
        }
      }
    }
  }
  
}


void INVtheaterChase(uint32_t c, uint8_t wait) {
  if (var == 0 || var == 2) {
    for (int j=0; j<5; j++) {  //do 10 cycles of chasing
      for (int q=0; q < 3; q++) {
        for (int i=0; i < ledStrip.numPixels(); i=i+3) {
          ledStrip.setPixelColor(i+q, c);    //turn every third pixel on
        }
        ledStrip.show();
     
        delay(wait);
     
        for (int i=0; i < ledStrip.numPixels(); i=i+3) {
          ledStrip.setPixelColor(i+q, 0);        //turn every third pixel off
          if (j=5)
          i--;
        }
      }
    }
  }
  
}







//2 Theatre-style crawling lights.
void theaterChase2(uint32_t c, uint8_t wait) {
  if (var == 3) {
    for (int j=0; j<5; j++) {  //do 10 cycles of chasing
      for (int q=0; q < 3; q++) {
        for (int i=0; i < ledStrip.numPixels(); i=i+3) {
          ledStrip.setPixelColor(i+q, c);    //turn every third pixel on
        }
        ledStrip.show();
     
        delay(wait);
     
        for (int i=0; i < ledStrip.numPixels(); i=i+3) {
          ledStrip.setPixelColor(i+q, 0);        //turn every third pixel off
        }
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  if (var == 0) {
    for (int j=0; j < 10; j++) {     // cycle all 256 colors in the wheel      >>>>CHANGED from 256<<<<
      if (var == 0) {
        for (int q=0; q < 5; q++) {                                //    CHANGED from q < 3
            for (int i=0; i < ledStrip.numPixels(); i=i+5) {      //    CHANGED from i + 3
              ledStrip.setPixelColor(i+q, Wheel( (i+j) % 256));    //turn every third pixel on
            }
            ledStrip.show();
       
            delay(wait);
       
            for (int i=0; i < ledStrip.numPixels(); i=i+5) {     //    CHANGED from i + 3
              ledStrip.setPixelColor(i+q, 0);        //turn every third pixel off
            }
          
        }
      }
    }
  }
}


void NEWtheaterChaseRainbow(uint8_t wait) {
  if (var == 0) {
    for (int j=0; j < 10; j++) {     // cycle all 256 colors in the wheel      >>>>CHANGED from 256<<<<
      if (var == 0) {
        //for (int q=0; q < 5; q++) {                                //    CHANGED from q < 3
            for (int i=0; i < ledStrip.numPixels(); i++) {      //    CHANGED from i + 3
              ledStrip.setPixelColor(i, Wheel( (i+j) % 256));    //turn every third pixel on
            
            }
            ledStrip.show();
            
            delay(wait);
       
            for (int i=0; i < ledStrip.numPixels(); i++) {     //    CHANGED from i + 3
              ledStrip.setPixelColor(i, 0);        //turn every third pixel off
            }
          ledStrip.show();
          delay(wait);
        }
      }
    }
  }
//}






uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return ledStrip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return ledStrip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return ledStrip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

