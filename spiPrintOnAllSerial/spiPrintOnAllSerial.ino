/*
  STM32_serial_test

  Use PC13 instead of PIN13 for generic STM32 boards.
  Print on every serial to identify them.

  Led pin
  BluePill  PC13
  MapleMini PB1
  
*/
#define LED PC13 //PC 13 on BluePill, PB1 on Maple Mini

void blink() {
  digitalWrite(LED, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(200);              // wait for a second
  digitalWrite(LED, LOW);    // turn the LED off by making the voltage LOW
  delay(100);              // wait for a second
}

void setup() {
  // initialize pins PC13, as an output.
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
  Serial1.begin(115200);
  Serial2.begin(115200);
  Serial3.begin(115200);
  Serial.println("Hello world this is Serial");
  Serial1.println("Hello world this is Serial1");
  Serial2.println("Hello world this is Serial2");
  Serial3.println("Hello world this is Serial3");

  blink();
}

void loop() {
  blink();              //
  Serial.println("It Works on serial");
  Serial1.println("It Works on serial1");
  Serial2.println("It Works on serial2");
  
}