#include <Wire.h>
#include <SPI.h>
#include <SharpIR.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define BME_SCK 13    //from here
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10
#define SEALEVELPRESSURE_HPA (1013.25)  //to here BME280 Sensor pin config
Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI for BME280 Sensor

#define ir A0  //ir: the pin where your Sharp IR sensor is attached
#define model 20150  //IR sensor model
SharpIR SharpIR(ir, model);

void setup() {
  Serial.begin(9600);
  bool status;

  status = bme.begin();
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");

  }
  Serial.println(" 1 for BME280 Sensor Values \n 2 to stop program \n 3 for Sharp IR sensor values \n");
}

char rx_byte = 0;

void loop() {

  if (Serial.available() > 0) {

    rx_byte = Serial.read();
    //Serial.println(rx_byte);

    if (rx_byte == '1') {
      bmeSensor();

    }
    else if (rx_byte == '2') {
      stopLoop();
    }
    else if (rx_byte == '3') {
      sharpSensor();
    }
    else {
      Serial.print("");
    }


  }
  delay(500);
}

void bmeSensor() {
  while (1) {
    Serial.print("Temp: ");
    Serial.print(bme.readTemperature());
    Serial.print("*C\t");
    Serial.print("Pressure: ");
    Serial.print(bme.readPressure() / 100.0F);
    Serial.print("hPa\t");
    Serial.print("Humidity: ");
    Serial.print(bme.readHumidity());
    Serial.print("%\t");
    Serial.print("Altitude: ");
    Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
    Serial.println("m");
    delay(500);
    loop();
  }
  

}
void stopLoop() {
  for (;;) {
    loop();
  }


}

void sharpSensor() {
  while (1) {
    unsigned long pepe1 = millis(); // takes the time before the loop on the library begins
    int dis = SharpIR.distance(); // this returns the distance to the object you're measuring
    Serial.print("Mean distance: ");  // returns it to the serial monitor
    Serial.print(dis);
    Serial.print("\t");
    unsigned long pepe2 = millis() - pepe1; // the following gives you the time taken to get the measurement
    Serial.print("Time taken (ms): ");
    Serial.println(pepe2);
    delay(500);
    loop();
  }
  
}
