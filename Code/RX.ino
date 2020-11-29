/// * code number 2 for the receiver
//
//****************************
//
//lesson from Dmitry Osipov. http://www.youtube.com/user/d36073?feature=watch
//
//v.01 receiver Arduino NRF24L01 radio module communication of two Arduino
//
//Version 0.1 2013/07/13
//
//detailed video instructions lay out here
//
//http://www.youtube.com/user/d36073?feature=watch
//
//NRF24L01 + 2.4GHz Antenna Wireless Transceiver Module For Microcontr
//
////Arduino №1 receiving data from the series, sends to the radio package,
//
//Arduino # 2 accepts the packet, and sends it back to Arduino # 1.
//
//Arduino # 1 takes the package and sends it back to the series.
//
//that is what they wrote in the series, it should come back.
//
////If you send to the series with Arduino №1 team (1,2,3,4,5) then on Arduino №2
//
//LEDs will turn on and off.
//
//http://arduino.ru/forum/programmirovanie/nrf24l01
//
//* /

// this is a downloaded library

//https://github.com/maniacbug/RF24

//https://github.com/maniacbug/RF24/archive/master.zip

//http://yadi.sk/d/ZvMq19fB6lgPs

#include <SPI.h>

#include "RF24.h"

// Set up nRF24L01 radio on SPI bus plus pins 9 & 10

// Contacts from the radio module NRF24L01 connect to pinnam -> Arduino

// SCK -> 13

// MISO -> 12

// MOSI -> 11

// CSN -> 10

// CE -> 9

RF24 radio (5, 10);

// pins where LEDs are connected

int led = 2;

int led1 = 3;

byte addresses[][6] = {"1Node","2Node"}; // addresses of the receive and transmit channels

void setup () {

radio.begin ();

//radio.setAutoAck(false);

radio.setPALevel (RF24_PA_HIGH);

radio.setDataRate (RF24_250KBPS); // Transmission speed

radio.setChannel (124); // Channel number from 0 to 127

radio.setRetries (15,15); // Number of attempts and time between attempts

radio.openWritingPipe (addresses[0]); // Open the transmission channel

radio.openReadingPipe (1, addresses[1]); // Open one of the 6 reception channels

radio.startListening (); // Start listening to the broadcast

pinMode (led1, OUTPUT);

pinMode (led, OUTPUT);

digitalWrite (led, HIGH);

digitalWrite (led1, HIGH);

}

void loop () {

if (radio.available ()) {
  char data [32] = "";
   while (radio.available()) {
    
    radio.read (& data, 32); // accepts package with Arduino №1
    Serial.print("Rxd: ");
    Serial.println(data);
   }


// If the number came 1 turn on the LED

if (data [0] == '8') digitalWrite (led, LOW), digitalWrite (led1, LOW);

if (data [0] == '4') digitalWrite (led, LOW), digitalWrite (led1, HIGH);

if (data [0] == '6') digitalWrite (led, HIGH), digitalWrite (led1, LOW);

if (data [0] == '5') digitalWrite (led, LOW), digitalWrite (led1, LOW);
 

//if (data [0] == '4') digitalWrite (led1, LOW);

//if (data [0] == '5') digitalWrite (led, HIGH), delay (1000), digitalWrite (led, LOW);

radio.stopListening ();

radio.write (& data, 32); // and sends back to Arduino №1

radio.startListening ();

}

}
