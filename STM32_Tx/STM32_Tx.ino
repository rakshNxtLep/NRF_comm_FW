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
/*
radio.powerDown();
delay(500);
radio.powerUp();
delay(500); // Wait 100ms for the nRF24L01+ module to stabilize after power-on.
*/
radio.begin();
delay(500); // Wait 100ms for the nRF24L01+ module to stabilize after power-on.       
           //Starting the Wireless communication
           if (!radio.begin()) {
            Serial.println("FATAL: Radio module not detected or failed initialization.");
            restartRadio();
        // Blink LED rapidly to indicate failure
        while (1) {
            digitalWrite(PC13, HIGH);
            delay(50);
            digitalWrite(PC13, LOW);
            delay(50);
        }


           }
radio.openWritingPipe(address); //Setting the address where we will send the data
delay(100);
radio.setPALevel(RF24_PA_MIN);  //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
delay(500);
radio.stopListening();          //This sets the module as transmitter
delay(500);
}

void loop()
{

//actual tx code
char text[] = " Raksh World";
char str[50];
sprintf(str,"%s %d",text,counter);
radio.write(&str, sizeof(str)); 
bool success = radio.write(&str, sizeof(str)); 

if (success) {
      // Blink HIGH briefly on success
        digitalWrite(PC13, LOW);
        delay(500); // Short pulse to indicate TX success
        digitalWrite(PC13, HIGH);
      
        Serial.print("TX Success: ");
        Serial.println(str);
        delay(100); 
    } 
    else {
      // Blink LOW briefly on failure (or maybe a longer pulse for attention)
        // Since PC13 is active LOW on Blue Pill, this LOW indicates the LED is OFF.
        // Let's use a specific blink pattern for failure.
        digitalWrite(PC13, LOW);
        delay(1000); // Long pulse to indicate TX success
        digitalWrite(PC13, HIGH);

        Serial.print("TX Failed: ");
        Serial.println(str);
        delay(100); 
    }

//Blink code
/*
digitalWrite(PC13, HIGH);
  delay(500);
  digitalWrite(PC13, LOW);
  delay(500);
  */
// Serial.println(str);
counter++;
// ---  Main Loop Delay / Rate Control ---
    // This delay controls how often a transmission attempt is made.
    // Use this to space out your transmissions, e.g., once every 1 second.
delay(200);
}

void restartRadio() {
    Serial.println("Attempting software radio restart...");
    
    // 1. Power down the radio gracefully
    radio.powerDown();
    delay(500); // Give it time to fully shut down

    // 2. Power up the radio
    radio.powerUp();
    delay(50); // Wait for the chip to stabilize internally

    // 3. Re-initialize the radio (Crucial steps from setup)
    if (radio.begin()) {
        radio.setDataRate(RF24_1MBPS); 
        delay(50);
        radio.setPALevel(RF24_PA_MIN); 
        delay(50);
        // For Receiver:
        // radio.openReadingPipe(0, address);
        // radio.startListening();
        
        // For Transmitter:
        radio.openWritingPipe(address);
        delay(50);
        radio.stopListening();
        delay(50);
        
        
        Serial.println("Radio restart successful.");
        delay(10);
    } else {
        Serial.println("Radio restart failed. Check power/connections.");
        delay(10);
    }
}