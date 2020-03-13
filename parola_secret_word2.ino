#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

#define HARDWARE_TYPE MD_MAX72XX::ICSTATION_HW //May need to be FC16_HW or ICSTATION_HW
#define MAX_DEVICES 12
#define CLK_PIN   13
#define DATA_PIN  11
#define CS_PIN    10

#define INT_PIN 2

bool secret_word_display = false;

MD_Parola P = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

uint8_t scrollSpeed = 50;    // default frame delay value
textEffect_t scrollEffect = PA_SCROLL_LEFT;
textPosition_t scrollAlign = PA_LEFT;
uint16_t scrollPause = 2000; // was 2000 in milliseconds

const char* secret_word = "Make"; //was Innovation

char Message[300] = {"Welcome to the Wonder Shelf. Touch oak leaf for secret word. Welcome to the Wonder Shelf. Touch oak leaf for secret word. Welcome to the Wonder Shelf. Touch oak leaf for secret word. Welcome to the Wonder Shelf. Touch oak leaf for secret word."};

void setup()
{
  Serial.begin(57600);
  pinMode(INT_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(INT_PIN),display_secret_word, FALLING);
  P.begin();
  P.displayText(Message, scrollAlign, scrollSpeed, scrollPause, scrollEffect, scrollEffect);
}

void loop()
{
  if(secret_word_display){
    P.displayClear();
    //P.print("Make"); // was Innovation
    //delay(5000);
    P.displayText("The word: Make", PA_LEFT, 50, 0, PA_SCROLL_LEFT, PA_SCROLL_LEFT); //was 5000
    while(!P.displayAnimate()){
      if(P.displayAnimate()){
        break;
      }
      //P.displayReset();
    }
    P.displayClear();
    P.displayText(Message, scrollAlign, scrollSpeed, scrollPause, scrollEffect, scrollEffect);
    secret_word_display = false;
  }
  else{
  if (P.displayAnimate())
  {
    P.displayReset();
  }
  }
}

void display_secret_word(){
  secret_word_display = true;
}
