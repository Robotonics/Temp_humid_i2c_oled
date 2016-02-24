#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include "Adafruit_DHT.h"
#include "math.h"

#define DHTPIN 2
#define DHTTYPE DHT11
#define OLED_RESET D4

Adafruit_SSD1306 display(OLED_RESET);
DHT dht(DHTPIN, DHTTYPE);
void setup()   {
  Serial.begin(9600);
  dht.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
}

void loop() {
// Wait a while between measurements.
	delay(20000);
  float h = dht.getHumidity();
  float t = dht.getTempCelcius();
  int i = int(t + 0.5); // convert float to integer with 2 dec place.
  int j = int(h + 0.5);  // convert as above
  Serial.print("Humid: ");
	Serial.print(j);
	Serial.print("% - ");
	Serial.print("Temp: ");
	Serial.print(i);
	Serial.print("*C ");
	Serial.println(Time.timeStr()); // print out full date and time to serial
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  String timer=Time.format(Time.now(), " %I:%M%p"); // format time to hours and minutes only
  display.println(timer); // display time i.e 07:15PM
  display.println("");
  display.print("Temp: ");
  display.print(i);
  display.println("C");
  display.print("Humid:");
  display.print(j);
  display.print("%");
  display.display();
	Spark.publish("Temperature",String(i));  // This will publish Temperature reading to the dashboard
	Spark.publish("Humidity",String(j));			// This will publish Humidity Data to the particle dashboard.
}
