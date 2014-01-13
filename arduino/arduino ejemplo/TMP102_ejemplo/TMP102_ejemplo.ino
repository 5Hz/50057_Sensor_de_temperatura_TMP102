//Arduino 1.0+ Only
//Arduino 1.0+ Only

//////////////////////////////////////////////////////////////////
//©2011 bildr
//Released under the MIT License - Please reuse change and share
//Simple code for the TMP102, simply prints temperature via serial
//////////////////////////////////////////////////////////////////

#include <Wire.h>
int direccion = 0x48;
boolean CELSIUS = 0;
boolean FARENHEIT = 1;

class TMP102
{
  public:
  TMP102(int _address); //constructor
  float getTemperature(boolean _scale); //método para seleccionar la escala de temperatura
  private:
  int address; //direccion del sensor
  float celsius; //variable que almacena temperatura en grados centigrados
  float farenheit; //variable para temperatura en grados farenheit
}mySensor(direccion); //se crea un objeto de la clase TMP102

void setup(){
  Serial.begin(9600);
  Wire.begin();
}

void loop(){
  Serial.print("Celsius: ");
  Serial.print(mySensor.getTemperature(CELSIUS)); //solicita la temperatura en celsius al sensor
  Serial.print("\t Fahrenheit: ");
  Serial.println(mySensor.getTemperature(FARENHEIT)); //solicita la temperatura en farenheit al sensor
  delay(200); //alenta las mediciones un poco
}

//*******************************************************************
//constructor de la clase TMP102
TMP102::TMP102(int _address)
{
  address = _address;
  celsius = 0;
  farenheit = 0;
}

//Método para leer temperatura del sensor
float TMP102::getTemperature(boolean _scale)
{
  Wire.requestFrom(TMP102::address,2); 

  byte MSB = Wire.read();
  byte LSB = Wire.read();

  //it's a 12bit int, using two's compliment for negative
  int TemperatureSum = ((MSB << 8) | LSB) >> 4; 

  TMP102::celsius = TemperatureSum*0.0625;
  if(_scale == CELSIUS) return TMP102::celsius;
  else if(_scale == FARENHEIT) return TMP102::farenheit = (1.8 * TMP102::celsius) + 32; 
}

