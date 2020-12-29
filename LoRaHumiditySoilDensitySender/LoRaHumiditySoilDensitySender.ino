/*
  This is a simple example show the Heltec.LoRa sended data in displaySensorDataToOLED.

  The onboard displaySensorDataToOLED display is SSD1306 driver and I2C interface. In order to make the
  displaySensorDataToOLED correctly operation, you should output a high-low-high(1-0-1) signal by soft-
  ware to displaySensorDataToOLED's reset pin, the low-level signal at least 5ms.

  displaySensorDataToOLED pins to ESP32 GPIOs via this connecthin:
  displaySensorDataToOLED_SDA -- GPIO4
  displaySensorDataToOLED_SCL -- GPIO15
  displaySensorDataToOLED_RST -- GPIO16
  
  by Aaron.Lee from HelTec AutoMation, ChengDu, China
  成都惠利特自动化科技有限公司
  https://heltec.org
  
  this project also realess in GitHub:
  https://github.com/Heltec-Aaron-Lee/WiFi_Kit_series
*/
#include "DHT.h"
#include "heltec.h"
#include "images.h"
#define BAND    915E6  //you can set band here directly,e.g. 868E6,915E6
#define DHTPIN 0
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
String rssi = "RSSI --";
String packSize = "--";
String packet ;
String tx_str;
String receivedisplaySensorDataToSerialMonitorString();

float moisture;
float humidity;
float celsius;
float fahrenheit;
float fahrenheitHeatIndex;
float celsiusHeatIndex;
double light;
double voltage;
void setup()
{
  Serial.begin(115200);
  dht.begin();
  initializationLogo();
}

void loop()
{ 
  

  humidity = dht.readHumidity();
  celsius = dht.readTemperature();  // Read temperature as Celsius (the default)
  fahrenheit = dht.readTemperature(true);  // Read temperature as Fahrenheit (isFahrenheit = true)
  fahrenheitHeatIndex = dht.computeHeatIndex(fahrenheit, humidity); // Compute heat index in Fahrenheit (the default)
  celsiusHeatIndex = dht.computeHeatIndex(celsius, humidity, false);  // Compute heat index in Celsius (isFahreheit = false)
  moisture = analogRead(13);
  light = analogRead(12);

  displaySensorDataToOLED();
  displaySensorDataToSerialMonitor();

  
  
  
  //tx_str = receivedisplaySensorDataToSerialMonitorString(); 


  //****************  start transmitting lora data**********************************
  tx_str = humidity; 
  transmitLoRa(tx_str);
  tx_str = celsius; 
  transmitLoRa(tx_str);
  tx_str = fahrenheit; 
  transmitLoRa(tx_str);
  tx_str = fahrenheitHeatIndex; 
  transmitLoRa(tx_str);
  tx_str = celsiusHeatIndex; 
  transmitLoRa(tx_str);
  tx_str = moisture; 
  transmitLoRa(tx_str);
  tx_str = light; 
  transmitLoRa(tx_str);
  //****************  end transmitting lora data************************************
  blinkOnboardLed(10,10);             
}

void initializationLogo()
{
   //WIFI Kit series V1 not support Vext control
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Heltec.Heltec.Heltec.LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /*long BAND*/);
  Heltec.display->init();
  Heltec.display->flipScreenVertically();  
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->clear();
  Heltec.display->drawXbm(0,5,logo_width,logo_height,logo_bits);
  Heltec.display->display();
  delay(1500);
  Heltec.display->clear();
  Heltec.display->drawString(0, 0, "Heltec.LoRa Initial success!");
  Heltec.display->display();
  delay(1000);
}

void transmitLoRa(String tx_str)
{

  // send packet
  LoRa.beginPacket();
  
/*
 * LoRa.setTxPower(txPower,RFOUT_pin);
 * txPower -- 0 ~ 20
 * RFOUT_pin could be RF_PACONFIG_PASELECT_PABOOST or RF_PACONFIG_PASELECT_RFO
 *   - RF_PACONFIG_PASELECT_PABOOST -- LoRa single output via PABOOST, maximum output 20dBm
 *   - RF_PACONFIG_PASELECT_RFO     -- LoRa single output via RFO_HF / RFO_LF, maximum output 14dBm
*/
  LoRa.setTxPower(14,RF_PACONFIG_PASELECT_PABOOST);
  LoRa.print(tx_str);
  LoRa.endPacket();

   
}

void blinkOnboardLed(int ON,int OFF)
{
  digitalWrite(LED, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(ON);                       // wait for a second
  digitalWrite(LED, LOW);    // turn the LED off by making the voltage LOW
  delay(OFF); 
}

String receivedisplaySensorDataToSerialMonitorString()
{
  //String tx_str;
  if(Serial.available())
  {
   tx_str = Serial.readStringUntil('\n'); //store string from serial monitor to "tx_str" string
  }
  return tx_str;
}

void displaySensorDataToOLED()
{
  Heltec.display->clear();
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawString(0, 0, "humidity: ");
  Heltec.display->drawString(72, 0, String(humidity));
  Heltec.display->drawString(0, 8, "celsius: ");
  Heltec.display->drawString(72, 8, String(celsius));
  Heltec.display->drawString(0, 16, "fahrenheit: ");
  Heltec.display->drawString(72, 16, String(fahrenheit));
  Heltec.display->drawString(0, 24, "f heat index: ");
  Heltec.display->drawString(72, 24, String(fahrenheitHeatIndex));
  Heltec.display->drawString(0, 32, "c heat index: ");
  Heltec.display->drawString(72, 32, String(celsiusHeatIndex));
  Heltec.display->drawString(0, 40, "moisture: ");
  Heltec.display->drawString(72, 40, String(moisture));
  Heltec.display->drawString(0, 48, "light: ");
  Heltec.display->drawString(72, 48, String(light));
  //Heltec.display->drawString(0, tx_str.toInt(), tx_str);
  Heltec.display->display();
}

void displaySensorDataToSerialMonitor()
{
  Serial.print(F("Humidity: "));
  Serial.print(humidity);
  Serial.print(F("%  Temperature: "));
  Serial.print(celsius);
  Serial.print(F("°C "));
  Serial.print(fahrenheit);
  Serial.print(F("°F  Heat index: "));
  Serial.print(celsiusHeatIndex);
  Serial.print(F("°C "));
  Serial.print(fahrenheitHeatIndex);
  Serial.print(F("°F"));
  Serial.print(" Moisture: ");
  Serial.print(moisture);
  Serial.print(" Light: ");
  Serial.println(light);
}
