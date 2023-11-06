//Universidad del Valle de Guatemala
//Electrónica Digital 2
//Ingebor Ayleen Rubio Vasquez-19003
//Proyecto 3

//Librerías
#include <Arduino.h>
#include <Temperature_LM75_Derived.h>


//Variables globales
int valorSensor = 0;

Generic_LM75 temperature;

//COnfiguración
void setup()
{
  Serial.begin(115200);
  Serial2.begin(115200);
  Wire.begin();
}

//Loop principal
void loop()
{
  // Obtener los valores de temperatura
  float t = temperature.readTemperatureC();
  //Si no se pudo obtener los valores, mostrar un mensaje de advertencia
  if (isnan(t))
  {
    Serial.println(F("Failed to read from LM75 sensor!"));
    return;
  }

  //Cuando haya comunicaicón serial
  if (Serial2.available() > 0)
  {
    //leer el mensaje proveniente de la Tiva C
    char bufferTiva = Serial2.read();
    //Si este corresponde a la letra m, enviar los datos de temperatura y humedad
    //concatenados en un string separado por una coma
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

}