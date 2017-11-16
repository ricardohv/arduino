/*

http://osoyoo.com/2014/12/08/decode-infrared-remote-controller-with-ir-receiver-vs1838b/

Codigos HEX de control MACs

ARRIBA 5656481C
ABAJO CD2F8CC0
IZQ DF96D4
DER F813E99E
PLAY 5F565CB8
MENU FC3A874
*/

#include <IRremote.h>
int input_pin = 8; //set D10 as input signal pin
IRrecv irrecv(input_pin);
decode_results signals;
void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // enable input from IR receiver
}
void loop() {
if (irrecv.decode(&signals)) {
    Serial.println(signals.value, HEX);
    irrecv.resume(); // get the next signal
  }
}
