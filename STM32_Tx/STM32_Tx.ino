#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>  //need to add library in your

RF24 radio(PB0, PA4);  // CE, CSN on Blue Pill
const uint64_t address = 0xF0F0F0F0E1LL;
int counter = 0;

void setup() {
  Serial.begin(9600);
  radio.begin();                   //Starting the Wireless communication
  radio.openWritingPipe(address);  //Setting the address where we will send the data
  radio.setPALevel(RF24_PA_MIN);   //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.stopListening();           //This sets the module as transmitter
}

void loop() {
  char text[] = " Raksh World";
  char str[50];
  sprintf(str, "%s %d", text, counter);
  radio.write(&str, sizeof(str));

  Serial.println(str);
  counter++;
  delay(2000);
}