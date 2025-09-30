/*
NRF Transmitter
₹@|<$|n
pin configuration of 
NRF24 to Stm32F103C
NRF24L01 VCC ………………………………………… 3.3V of STM32F103C
NRF24L01 CSN ………………………………………… PA4 of STM32F103C
NRF24L01 MOSI ………………………………………… PA7 of STM32F103C
NRF24L01 GND ………………………………………… GND of STM32F103C
NRF24L01 CE ………………………………………… PB0 of STM32F103C
NRF24L01 SCK ………………………………………… PA5 of STM32F103C
NRF24L01 MISO ………………………………………… PA6 of STM32F103C

*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(PB0, PA4); // CE, CSN on Blue Pill 
const uint64_t address = 0xF0F0F0F0E1LL;
int counter = 0;

void setup() 
{

Serial.begin(9600);
pinMode(PC13, OUTPUT);
delay(100); // Wait 100ms for the nRF24L01+ module to stabilize after power-on.
radio.begin();                  //Starting the Wireless communication
radio.openWritingPipe(address); //Setting the address where we will send the data
radio.setPALevel(RF24_PA_MIN);  //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
radio.stopListening();          //This sets the module as transmitter
}

void loop()
{

//actual tx code
char text[] = " Raksh World";
char str[50];
sprintf(str,"%s %d",text,counter);
radio.write(&str, sizeof(str));  
//Blink code
// /*
digitalWrite(PC13, HIGH);
  delay(500);
  digitalWrite(PC13, LOW);
  delay(500);
  // */
Serial.println(str);
counter++;
delay(200);
}