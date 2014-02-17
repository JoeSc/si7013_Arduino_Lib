#include <si7013.h>
#include <Wire.h>

SI7013 si7013(0x40, 1);

// Print a centi-unit in "float"
void print_float(int tmp)
{
   Serial.print(tmp / 100);
   Serial.print(".");
   Serial.println(tmp - (tmp / 100) * 100);
}

void setup()
{
   Serial.begin(9600);
   Wire.begin();
   si7013.begin();
   Serial.println("si7013 Library Example");
}
   
void loop()
{
   int tmp;
   Serial.print("Humidity = ");
   print_float(si7013.readHumidity());
   Serial.print("Temperature From Humidity Reading = ");
   print_float(si7013.getTempFromHumidity());
   Serial.print("Temperature = ");
   print_float(si7013.readTemperature());
   Serial.println();
   delay(1000);
}

