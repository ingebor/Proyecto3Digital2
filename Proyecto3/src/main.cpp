// Universidad del Valle de Guatemala
// Electrónica Digital 2
// Ingebor Ayleen Rubio Vasquez-19003
// Proyecto 3

// Librerías
#include <Arduino.h>
#include <Temperature_LM75_Derived.h>
#include <Adafruit_NeoPixel.h>

#define CIRCLE 25
#define CIRCLE_LEDS 24
#define BRIGHTNESS 255

// Declare objects to control the NeoPixels
Adafruit_NeoPixel circle(CIRCLE_LEDS, CIRCLE, NEO_GRB + NEO_KHZ800);

// Variables globales
int valorSensor = 0;

Generic_LM75 temperature;

// COnfiguración
void setup()
{
  Serial.begin(115200);
  Serial2.begin(115200);
  Wire.begin();
  // Ensure all LED arrays are clear when we start
  circle.begin();
  circle.clear();
  circle.setBrightness(BRIGHTNESS);

  Serial.println("Inicio exitoso!");
}

// Loop principal
void loop()
{
  // Obtener los valores de temperatura
  float t = temperature.readTemperatureC();
  // Si no se pudo obtener los valores, mostrar un mensaje de advertencia
  if (isnan(t))
  {
    Serial.println(F("Failed to read from LM75 sensor!"));
    return;
  }

  // Cuando haya comunicaicón serial
  if (Serial2.available() > 0)
  {
    // leer el mensaje proveniente de la Tiva C
    char bufferTiva = Serial2.read();
    // Si este corresponde a la letra m, enviar los datos de temperatura y humedad
    // concatenados en un string separado por una coma
    // Serial.println("Disponible");
    if (bufferTiva == 'm')
    {
      Serial.println("\nEnviando temperatura");
      Serial.print(F("Temperatura: "));
      Serial.print(t);
      Serial.println(F("°C "));
      String temp = String(t);
      Serial2.println(temp);
      delay(300);
    }
  }

  uint8_t red = 255;
  uint8_t green = 0;
  uint8_t blue = 0;

  // Make the colours change as we go round the circle
  for (int i = 0; i < CIRCLE_LEDS; i++)
  {
    circle.setPixelColor(i, red, green, blue);
    circle.show();
    delay(40);
    blue = blue + 12;
    red = red - 12;
  }

   // Change colours and go round the circle the other way
    red   = 0;
    green = 255;
    blue  = 0;
    circle.clear();

    for (int i = CIRCLE_LEDS - 1; i >= 0; i--) {
        circle.setPixelColor(i, red, green, blue);
        circle.show();
        delay(50);
    }

    // And again
    green = 0;
    blue  = 255;
    circle.clear();

    for (int i = 0; i < CIRCLE_LEDS; i++) {
        circle.setPixelColor(i, red, green, blue);
        circle.show();
        delay(30);
        green += 8;
    }

    // Clear down the circle LEDs and start again
    circle.clear();
    circle.show();

}