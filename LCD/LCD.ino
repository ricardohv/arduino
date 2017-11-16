/*
  1602 LCD Keypad Shield Example Code using the LiquidCrystal Library

 Library originally added 18 Apr 2008 by David A. Mellis
 library modified 5 Jul 2009 by Limor Fried
 example added 9 Jul 2009
 by Tom Igoe 
 modified 22 Nov 2010
 by Tom Igoe
 modified Jan 2013 for the 1602 LCD Keypad Shield 
 by Bentley Born

 This example code is in the public domain.

 http://arduino.cc/en/Tutorial/LiquidCrystalDisplay

 */

// include the library code:
#include <LiquidCrystal.h>

int x = 0;
int currx = 1023;
String btnStr = "Presionar boton";

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Valor --> ");
  lcd.print(currx);
  lcd.setCursor(0,1);
  lcd.print(btnStr);
}

void loop() {
  
  x = analogRead(A0); // the buttons are read from the analog0 pin
  
  // Check if x has changed
  if ((x != 1023) && (x != currx)){
  
    //update screen and change currx
    lcd.setCursor(10,0);
    lcd.print("     ");
    lcd.setCursor(10,0);
    lcd.print(x);
    currx = x;
    
    if (currx > 740 && currx < 745){
    
       btnStr="Seleccion";
    
    } else if (currx > 500 && currx < 510){
    
      btnStr="Izquierda";
      
    } else if (currx < 10){
    
      btnStr="Derecha";
      
    } else if (currx > 140 && currx < 150){
    
      btnStr="Arriba";
      
    } else if (currx > 320 && currx < 365){
    
      btnStr="Abajo";
      
    }
    
      //update button pressed
      lcd.setCursor(0,1);
      lcd.print("                ");
      lcd.setCursor(0,1);
      lcd.print(btnStr);
  }
  
  delay(10);
   
}
