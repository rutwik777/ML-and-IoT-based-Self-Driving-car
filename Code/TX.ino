/// * code number 1 for transmitter
//
//****************************
//
//lesson from Dmitry Osipov. http://www.youtube.com/user/d36073?feature=watch
//
//v.01 transmitter Arduino NRF24L01 radio module communication of two Arduino
//
//Version 0.1 2013/07/13
//
//detailed video instructions lay out here
//
//http://www.youtube.com/user/d36073?feature=watch
//
//code number 2 for the receiver http://yadi.sk/d/b2t1JAhT6lgYU
//
//NRF24L01 + 2.4GHz Antenna Wireless Transceiver Module For Microcontr
//
//Arduino №1 receiving data from the series, sends to the radio package,
//
//Arduino # 2 accepts the packet, and sends it back to Arduino # 1.
//
//Arduino # 1 takes the package and sends it back to the series.
//
//that is what they wrote in the series, it should come back.
//
//If you send to the series with Arduino №1 team (1,2,3,4,5) then on Arduino №2
//
//LEDs will turn on and off.
//
//http://arduino.ru/forum/programmirovanie/nrf24l01
//
//* /
//
//// this is a downloaded library
//
////https://github.com/maniacbug/RF24
//
////https://github.com/maniacbug/RF24/archive/master.zip
//
////http://yadi.sk/d/ZvMq19fB6lgPs

#include <SPI.h>

#include "RF24.h"

RF24 radio (5, 10);

byte addresses[][6] = {"1Node","2Node"}; // addresses of the receive and transmit channels

void setup () {

Serial.begin (9600);

radio.begin ();

//radio.setAutoAck(false);

radio.setPALevel(RF24_PA_HIGH);

radio.setDataRate (RF24_250KBPS); // Transmission speed

radio.setChannel (124); // Channel number from 0 to 127

//radio.setRetries (15,15); // Number of attempts and time between attempts

radio.openWritingPipe (addresses[1]); // Open the transmission channel

radio.openReadingPipe (1, addresses[0]); // Open one of the 6 reception channels

radio.startListening (); // Start listening to the broadcast

}

void loop () {

if (Serial.available ()) {

char data [32] = "";

byte i = 0;

while (Serial.available ()) {

data [i] = Serial.read (); // get data from the show.

i ++;

delay (2);

}

data [i] = 0;

radio.stopListening ();

radio.write (& data, 32); // and send them to Arduino №2
Serial.println("Sent: ");
Serial.print(data);
radio.startListening ();

}

if (radio.available ()) {

char data1 [32] = "";

radio.read (& data1, 32); // accept package from Arduino №2
Serial.println("Recieved: ");
Serial.println (data1); // and pass it back to the show

}

}
