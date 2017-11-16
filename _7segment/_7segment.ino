// https://www.sunfounder.com/learn/rfid-kit-v2-0-for-arduino/lesson-20-driving-7-segment-display-by-74hc595-rfid-v2-0-for-arduino.html
// http://www.electrontools.com/Home/WP/2016/03/09/registro-de-desplazamiento-74hc595/
//74HC595
//You should now be able to see the 7-segment display cycle from 0 to F
//Email:support@sunfounder.com
//Website:www.sunfounder.com
//2015.5.7
const int latchPin = 12;//Pin connected to ST_CP of 74HC595
const int clockPin = 8;//Pin connected to SH_CP of 74HC595 
const int dataPin = 11; //Pin connected to DS of 74HC595 
//display 0,1,2,3,4,5,6,7,8,9,A,b,C,d,E,F
int datArray[16] = {252, 96, 218, 242, 102, 182, 190, 224, 254, 246, 238, 62, 156, 122, 158, 142};

const byte numeros[16] = {
                0b11111100, //0
                0b01100000, //1
                0b11011010, //2
                0b11110010, //3
                0b01100110, //4
                0b10110110, //5
                0b10111110, //6
                0b11100000, //7
                0b11111110, //8
                0b11100110, //9
                0b11101110, //A
                0b00111110, //b
                0b10011100, //C
                0b01111010, //d
                0b10011110, //E
                0b10001110  //F
};

const byte celu[16] = {
                0b11111110, //8
                0b00000000, //
                0b11111110, //8
                0b00000000, //
                0b11111110, //8
                0b00000000, //
                0b11111110, //8
                0b00000010, //-
                0b11100110, //9
                0b00000000, //
                0b10111110, //6
                0b00000000, //
                0b10111110, //6
                0b00000000, //
                0b11110010, //3
                0b00000001 //.
};

void setup ()
{
  //set pins to output
  pinMode(latchPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(dataPin,OUTPUT);
}
void loop()
{
  //loop from 0 to 16
  for(int num = 0; num < 16; num++)
  {
    digitalWrite(latchPin,LOW); //ground latchPin and hold low for as long as you are transmitting
//    shiftOut(dataPin,clockPin,MSBFIRST,datArray[num]);
//    shiftOut(dataPin,clockPin,MSBFIRST,numeros[num]);
    shiftOut(dataPin,clockPin,MSBFIRST,celu[num]);
    //return the latch pin high to signal chip that it 
    //no longer needs to listen for information
    digitalWrite(latchPin,HIGH); //pull the latchPin to save the data
    delay(500); //wait for a second
  }
  delay(500);
}
