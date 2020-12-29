/*
  This is a simple example show the Heltec.LoRa recived data in OLED.

  The onboard OLED display is SSD1306 driver and I2C interface. In order to make the
  OLED correctly operation, you should output a high-low-high(1-0-1) signal by soft-
  ware to OLED's reset pin, the low-level signal at least 5ms.

  OLED pins to ESP32 GPIOs via this connecthin:
  OLED_SDA -- GPIO4
  OLED_SCL -- GPIO15
  OLED_RST -- GPIO16
  
  by Aaron.Lee from HelTec AutoMation, ChengDu, China
  成都惠利特自动化科技有限公司
  www.heltec.cn
  
  this project also realess in GitHub:
  https://github.com/Heltec-Aaron-Lee/WiFi_Kit_series
*/
#include "heltec.h"
#include "images.h"

#define BAND 915E6 //you can set band here directly,e.g. 868E6,915E6
String rssi = "RSSI --";
String packSize = "--";
String packet;
String rx_str;
String displayStatus = "Display is on";

// -------------------------------
// AWS and Wifi modules
//#include <AWS_IOT.h>

#include <WiFi.h>

// Initialize AWS
AWS_IOT aws;

// Wifi Setup
char WIFI_SSID[] = "Abebe25";
char WIFI_PASSWORD[] = "Ethiopia";

// AWS Setup
char HOST_ADDRESS[] = "a28vigmgj5655d-ats.iot.us-east-1.amazonaws.com";
char CLIENT_ID[] = "ESP32BOARDFIRSTATTEMPTBYMEGULOABEBE";
char TOPIC_NAME[] = "iot/topic";

int status = WL_IDLE_STATUS;
int tick = 0, msgCount = 0, msgReceived = 0;
char dataPayload[512];
char payload[512];
char rcvdPayload[512];
int count = 0;

// AWS Callback function
void mySubCallBackHandler(char *topicName, int payloadLen, char *payLoad)
{
  strncpy(rcvdPayload, payLoad, payloadLen);
  rcvdPayload[payloadLen] = 0;
  msgReceived = 1;
}
// -------------------------------

void setup()
{
  initializationLogo();

  // -------------------------------
  //  Set up wifi connection
  delay(2000);

  //  Establish wifi connection
  while (status != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(WIFI_SSID);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    // wait 5 seconds for connection:
    delay(5000);
  }

  Serial.println("Connected to wifi");

  Serial.println("Attempting to connect to AWS...");

  // Establish connection to aws
  if (aws.connect(HOST_ADDRESS, CLIENT_ID) == 0)
  {
    Serial.println("Connected to AWS");
    delay(1000);

    if (0 == aws.subscribe(TOPIC_NAME, mySubCallBackHandler))
    {
      Serial.println("Subscribe Successfull");
    }
    else
    {
      Serial.println("Subscribe Failed, Check the Thing Name and Certificates");
      while (1)
        ;
    }
  }
  else
  {
    Serial.println("AWS connection failed, Check the HOST Address");
    while (1)
      ;
  }

  delay(2000);

  // -------------------------------
}

void loop()
{
  rx_str = receiveLoRa();
  rssi = rssiValue();
  OLED_ON_OFF(rx_str);

  Heltec.display->clear();
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_10);
  //OLED(0,0,"RSSI: " + rssi);
  //OLED(50,0,"Bytes: "+ packSize);
  //OLED(0,8,"Received string: "+ rx_str);
  OLED(0, 0, "Received string: " + rx_str);
  Heltec.display->display();

  // -------------------------------
  // Send data to AWS
  Serial.println("Sending data to AWS:");
  Serial.println(rx_str);
  sprintf(dataPayload, "{\"id\":\"%d\", \"data\":\"%s\"}", count, rx_str);
  count++;
  aws.publish(TOPIC_NAME, dataPayload);
  delay(1000);

  // -------------------------------
}

void initializationLogo()
{
  //WIFI Kit series V1 not support Vext control
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Heltec.Heltec.Heltec.LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /*long BAND*/);
  Heltec.display->init();
  Heltec.display->flipScreenVertically();
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->clear();
  Heltec.display->drawXbm(0, 5, logo_width, logo_height, logo_bits);
  Heltec.display->display();
  delay(1500);
  Heltec.display->clear();
  Heltec.display->drawString(0, 0, "Heltec.LoRa Initial success!");
  Heltec.display->drawString(0, 10, "Wait for incoming data...");
  Heltec.display->display();
  delay(1000);
  LoRa.receive();
}

String receiveLoRa()
{
  int packetSize = LoRa.parsePacket();
  if (packetSize)
  {
    packet = "";
    packSize = String(packetSize, DEC);
    for (int i = 0; i < packetSize; i++)
    {
      packet += (char)LoRa.read();
    }
  }
  return packet;
}

String rssiValue()
{
  return String(LoRa.packetRssi(), DEC);
}

void OLED(int horizontal, int vertical, String text)
{
  Heltec.display->drawString(horizontal, vertical, text);
}

void OLED_ON_OFF(String rx_str)
{
  if (rx_str == "ledoff")
  {
    Heltec.display->sleep(); //OLED sleep
    Heltec.VextON();
    digitalWrite(LED, LOW);
    displayStatus = "Display is off";
    Serial.println(displayStatus);
  }
  else if (rx_str == "ledon")
  {
    Heltec.VextOFF();
    Heltec.display->wakeup();
    digitalWrite(LED, HIGH);
    displayStatus = "Display is on";
    Serial.println(displayStatus);
  }
  else
  {
    Serial.println(displayStatus);
  }
}

double ReadVoltage(byte pin)
{
  double reading = analogRead(pin); // Reference voltage is 3v3 so maximum reading is 3v3 = 4095 in range 0 to 4095
  if (reading < 1 || reading >= 4095)
    //return 0;
    // return -0.000000000009824 * pow(reading,3) + 0.000000016557283 * pow(reading,2) + 0.000854596860691 * reading + 0.065440348345433;
    return -0.000000000000016 * pow(reading, 4) + 0.000000000118171 * pow(reading, 3) - 0.000000301211691 * pow(reading, 2) + 0.001109019271794 * reading + 0.034143524634089;
} // Added an improved polynomial, use either, comment out as required

//See more APIs about ADC here: https://github.com/Heltec-Aaron-Lee/WiFi_Kit_series/blob/master/esp32/cores/esp32/esp32-hal-adc.h

/* ADC readings v voltage
 *  y = -0.000000000009824x3 + 0.000000016557283x2 + 0.000854596860691x + 0.065440348345433
 // Polynomial curve match, based on raw data thus:
 *   464     0.5
 *  1088     1.0
 *  1707     1.5
 *  2331     2.0
 *  2951     2.5 
 *  3775     3.0
 *  
 */
