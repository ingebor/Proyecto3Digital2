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
uint8_t red = 0;
uint8_t green = 0;
uint8_t blue = 0;

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
  red = 0;
  green = 255;
  blue = 0;
  circle.clear();

  for (int i = CIRCLE_LEDS - 1; i >= 0; i--)
  {
    circle.setPixelColor(i, red, green, blue);
    circle.show();
    delay(50);
  }
}

// Loop principal
void loop()
{
  // Obtener los valores de temperatura
  float t = temperature.readTemperatureC();
  // Si no se pudo obtener los valores, mostrar un mensaje de advertencia
  if (isnan(t))
  {
    Serial.println(F("No se pudo leer del sensor LM75!"));
    return;
  }

  // Cuando haya comunicaicón serial
  if (Serial2.available() > 0)
  {
    // leer el mensaje proveniente de la Tiva C
    char bufferTiva = Serial2.read();
    // Si este corresponde a la letra m, enviar los datos de temperatura
    if (bufferTiva == 'm')
    {
      red = 255;
      green = 0;
      blue = 0;
      circle.clear();
      //Iluminar en circulo
      for (int i = 0; i < CIRCLE_LEDS; i++)
      {
        //Mostrar colores correspondientes en neopixel
        circle.setPixelColor(i, red, green, blue);
        circle.show();
        delay(40);
        blue = blue + 12;
        red = red - 12;
      }
      delay(1000);
      circle.clear();
      circle.show();
      Serial.println("\nEnviando temperatura");
      Serial.print(F("Temperatura: "));
      Serial.print(t);
      Serial.println(F("°C "));
      String temp = String(t);
      Serial2.println(temp);
      if(t>27.90){
        red = 255;
        green = 0;
        blue = 0;
        circle.clear();
        for (int i = CIRCLE_LEDS - 1; i >= 0; i--)
        {
          circle.setPixelColor(i, red, green, blue);
          circle.show();
          delay(50);
        }
      }
      else if(t<27.9 && t>26.9){
        red = 0;
        green = 255;
        blue = 0;
        circle.clear();
        for (int i = CIRCLE_LEDS - 1; i >= 0; i--)
        {
          circle.setPixelColor(i, red, green, blue);
          circle.show();
          delay(50);
        }
      }
      else if(t<26.9){
        red = 0;
        green = 0;
        blue = 200;
        circle.clear();
        for (int i = CIRCLE_LEDS - 1; i >= 0; i--)
        {
          circle.setPixelColor(i, red, green, blue);
          circle.show();
          delay(50);
        }
      }
      circle.show();
      delay(300);
    }
    //Si guardan los datos en la SD, se recibe el valor x
    //en ese caso, iluminar del color correspondiente
    if (bufferTiva == 'x')
    {
      red = 200;
      green = 0;
      blue = 200;
      circle.clear();
      //Iluminar en circulo
      for (int i = 0; i < CIRCLE_LEDS; i++)
      {
        circle.setPixelColor(i, red, green, blue);
        circle.show();
        delay(30);
        green += 8;
      }
      delay(1000);
      // Clear down the circle LEDs and start again
      circle.show();
    }
  }

}