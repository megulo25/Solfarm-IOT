/*
  This is a simple example show the Heltec.LoRa sended data in OLED.

  The onboard OLED display is SSD1306 driver and I2C interface. In order to make the
  OLED correctly operation, you should output a high-low-high(1-0-1) signal by soft-
  ware to OLED's reset pin, the low-level signal at least 5ms.

  OLED pins to ESP32 GPIOs via this connecthin:
  OLED_SDA -- GPIO4
  OLED_SCL -- GPIO15
  OLED_RST -- GPIO16
  
  by Aaron.Lee from HelTec AutoMation, ChengDu, China
  成都惠利特自动化科技有限公司
  https://heltec.org
  
  this project also realess in GitHub:
  https://github.com/Heltec-Aaron-Lee/WiFi_Kit_series
*/

#include "heltec.h"
#include "images.h"
#define BAND    915E6  //you can set band here directly,e.g. 868E6,915E6
String rssi = "RSSI --";
String packSize = "--";
String packet ;
String tx_str;
String receiveSerialMonitorString();

double moisture;
double voltage;
void setup()
{
  Serial.begin(115200);
  initializationLogo();
}

void loop()
{ 
  moisture = analogRead(13);
  //tx_str = receiveSerialMonitorString();
  tx_str = moisture; 
  transmitLoRa(tx_str);   
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
  Heltec.display->clear();
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawString(0, 0, "Sending String: ");
  //Heltec.display->drawString(0, 8, "Sending String: ");
  Heltec.display->drawString(72, 0, tx_str);
  //Heltec.display->drawString(0, tx_str.toInt(), tx_str);
  Heltec.display->display();
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

String receiveSerialMonitorString()
{
  //String tx_str;
  if(Serial.available())
  {
   tx_str = Serial.readStringUntil('\n'); //store string from serial monitor to "tx_str" string
  }
  return tx_str;
}
