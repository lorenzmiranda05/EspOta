#include <Arduino.h>
#include <credentials.h>
#include <OTA.h>

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(921600);
  Serial.println("Booting");

  setupOTA(mcuHostName, modSsid, modPassword);
}

int loopCount = 0;

void loop()
{
  ArduinoOTA.handle();
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); // Blink
  Serial.println("Printing from loop.");
  Serial.print("Loop Count: ");
  Serial.println(loopCount);
  loopCount = loopCount + 1;
  delay(5000);
}