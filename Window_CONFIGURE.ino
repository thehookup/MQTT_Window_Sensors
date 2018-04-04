//#include <SPI.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>

//USER CONFIGURED SECTION START//
const char* ssid = "YOUR_WIRELESS_SSID";
const char* password = "YOUR_WIRELESS_SSID";
const char* mqtt_server = "YOUR_MQTT_SERVER_ADDRESS";
const int mqtt_port = YOUR_MQTT_SERVER_PORT;
const char *mqtt_user = "YOUR_MQTT_USERNAME";
const char *mqtt_pass = "YOUR_MQTT_PASSWORD";
const char *mqtt_client_name = "PICK_UNIQUE_WINDOW_NAME"; // Client connections cant have the same connection name
const char *mqtt_topic = "PICK_UNIQUE_WINDOW_TOPIC";
//USER CONFIGURED SECTION END//

WiFiClient espClient;
PubSubClient client(espClient); 

// Variables
bool boot = true;


//Functions

void setup_wifi() 
{
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
    {
    delay(500);
    }
}

void reconnect() 
{
  while (!client.connected()) 
  {
      if (client.connect(mqtt_client_name, mqtt_user, mqtt_pass, mqtt_topic, 0, 0, "closed")) 
      {
        if(boot == true)
        {
          client.publish(mqtt_topic,"open");
          boot = false;
        }
      } 
      else 
      {
        ESP.restart();
      }
  }
}

void setup() {
  // GPIO Pin Setup
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
}

void loop() 
{
  
  if (boot == true) 
  {
    reconnect();
  }
  else
  {
  ESP.deepSleep(2000000000);
  }
}


