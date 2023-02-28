#include <SoftwareSerial.h>
#include <TinyGPSPlus.h>


SoftwareSerial gpsSerial(33, 26); //rx,tx
TinyGPSPlus gps; // create gps object

//#if defined(ESP32)
#include <WiFi.h>
#include <FirebaseESP32.h>
//#elif defined(ESP8266)
//#include <ESP8266WiFi.h>
//#include <FirebaseESP8266.h>
//#endif


#define FIREBASE_HOST "gps-tracking-esp32-1e43e-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "QOsOx4Rhsba3iG2qVerTJvaDO91Thqh5HblKftgQ"
#define WIFI_SSID "iPhone1"   //iPhone1
#define WIFI_PASSWORD "123456789"  //123456789

int led = 2 ;
//Define FirebaseESP8266 data object
FirebaseData firebaseData;

FirebaseJson json;

//-----------------------------------------------------------------------------------


void setup()
{

  Serial.begin(9600);
  gpsSerial.begin(9600); // connect gps sensor
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  digitalWrite(led, HIGH);

  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Serial.println("Connecting Firebase.....");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  Serial.println("Firebase OK.");
}

void loop()
{

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    digitalWrite(led, LOW);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    delay(300);

  }
  digitalWrite(led, HIGH);
  unsigned long chars;
  unsigned short sentences, failed;
  while (gpsSerial.available() > 0)
  {
    char c = gpsSerial.read();
    Serial.print(c); // uncomment this line if you want to see the GPS data flowing
    if (gps.encode(c))
    {

      if (gps.location.isValid()) {
        Serial.print(gps.location.lat(), 6);
        Serial.print(F(","));
        Serial.print(gps.location.lng(), 6);


        if (Firebase.setFloat(firebaseData, "/GPS/latitude", gps.location.lat()))
        {
          print_ok();
        }
        else
        {
          print_fail();
        }
        //-------------------------------------------------------------
        if (Firebase.setFloat(firebaseData, "/GPS/longitude", gps.location.lng()))
        {
          print_ok();
        }
        else
        {
          print_fail();
        }
      }

    }
  }


}

void print_ok()
{
  Serial.println("------------------------------------");
  Serial.println("OK");
  Serial.println("PATH: " + firebaseData.dataPath());
  Serial.println("TYPE: " + firebaseData.dataType());
  Serial.println("ETag: " + firebaseData.ETag());
  Serial.println("------------------------------------");
  Serial.println();
  delay(300);
}


void print_fail()
{
  Serial.println("------------------------------------");
  Serial.println("FAILED");
  Serial.println("REASON: " + firebaseData.errorReason());
  Serial.println("------------------------------------");
  Serial.println();
}
