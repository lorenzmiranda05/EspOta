#include <Arduino.h>
#include <credentials.h>
#include <ESP8266WiFi.h>

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(921600);
  Serial.println("Booting");
  WiFi.begin(modSsid, modPassword);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); // Blink
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}

int loopCount = 0;

void loop()
{
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  Serial.println("Printing from loop.");
  Serial.print("Loop Count: ");
  Serial.println(loopCount);
  loopCount = loopCount + 1;
  delay(5000);
}