/*
NRF Receiver 
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

RF24 radio(PB0, PA4); // CE, CSN on Blue Pill spi1 connection

const uint64_t address = 0xF0F0F0F0E1LL;
int count=0;
int wait=1;
// /*
bool ledState = false;   // Variable to store the current state of the LED (false = off, true = on)
// */
void setup() 
{
Serial.begin(9600);
 
pinMode(PC13, OUTPUT);
/*
radio.powerDown();
delay(500);
radio.powerUp();
delay(500); // Wait 100ms for the nRF24L01+ module to stabilize after power-on.
*/
radio.begin();
delay(500); // Wait 100ms for the nRF24L01+ module to stabilize after power-on.
if (!radio.begin()) {
        Serial.println("FATAL: Radio module not detected or failed initialization.");
        // Blink LED rapidly to indicate failure
        while (1) {
            digitalWrite(PC13, HIGH);
            delay(50);
            digitalWrite(PC13, LOW);
            delay(50);
        }
    }
    // Optional Debugging: Print hardware details
    Serial.println("--- Radio Details ---");
    radio.printDetails(); 
    Serial.println("---------------------");
Serial.print("ADDRESS :");
Serial.println(address);
radio.openReadingPipe(0, address);   //Setting the address at which we will receive the data
radio.setPALevel(RF24_PA_MIN);       //You can set this as minimum or maximum depending on the distance between the transmitter and receiver.
radio.startListening();              //This sets the module as receiver


}
void loop()
{
if (radio.available())              //Looking for the data.
{
  //actual sniffing code
Serial.println("Radio is sniffing");
char text[32] = "";                 //Saving the incoming data
radio.read(&text, sizeof(text));    //Reading the data
Serial.print("Received: ");
Serial.println(text);
// delay(100);
count = 0;
// /*
  // Toggle the LED state
    ledState = !ledState;
    // Write the new LED state to the pin
  digitalWrite(PC13, ledState);
  delay(300); // Short pulse to indicate TX success
  // */
}
// /*
else
  {
  // Serial.println(count);
  delay(100);
    count = count+1;
    wait = wait+1;
    if(wait >= 50) //100 * 30 3000 dealy
    {
    Serial.println("not available");
    delay(50);
  //  count = 0;
    wait = 1;
    }   
    if(count >= 200){
      restartRadio();
      delay(100);
      count = 0;
    }
  }
// */
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
        delay(100);
        radio.setPALevel(RF24_PA_MIN); 
        delay(100);
        
        // For Receiver:
        radio.openReadingPipe(0, address);
        delay(100);
        radio.startListening();
        delay(100);
        
        // For Transmitter:
        // radio.openWritingPipe(address);
        // radio.stopListening();
        
        Serial.println("Radio restart successful.");
    } else {
        Serial.println("Radio restart failed. Check power/connections.");
    }
}