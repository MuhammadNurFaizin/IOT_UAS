#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// =================================
// Define your sensor pin in here
#define lamp1 D1
#define lamp2 D2
#define lamp3 D3
#define lamp4 D4
//====================================

// Configure for wifi connection
const char *wlanName = "F3IAN";
const char *wlanPassword = "bismillah";

// Delay or millis
unsigned long lastMsg = 0;

// Define configure for mqtt broker
const char *brokerAddress = "broker.sinaungoding.com";

// Declare instance for wificlient
WiFiClient espClient;
PubSubClient client(espClient);

// mqtt callbacrk
void callback(char *topic, byte *payload, unsigned int length);

// function for mqtt if disconnected will reconnect
void reconnect()
{
  // Reconnect if connection lost...
  Serial.println("In Reconnect....");

  while (!client.connected())
  {
    Serial.print("Attempting mqtt connection....");
    if (client.connect("lampard"))
    {
      Serial.println("Connected");
      client.subscribe("street_lamp");
    }
    else
    {
      Serial.print("failed,");
      // Show state mqtt broker
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

// Broker callback
void callback(char *topic, byte *payload, unsigned int length)
{
  String tempPayload;
  for (int i = 0; i < length; i++)
  {
    // Store payload to tempPayload
    tempPayload += (char)payload[i];
  }
  if (tempPayload == "lamp1/on")
  {
    Serial.println("==================");
    Serial.println("Lamp-1 Status: ON");
    Serial.println("Topic Message " + tempPayload);
    Serial.println("==================");
    pinMode(lamp1, OUTPUT);
  }
  if (tempPayload == "lamp1/off")
  {
    Serial.println("==================");
    Serial.println("Lamp-1 Status: OFF");
    Serial.println("Topic Message " + tempPayload);
    Serial.println("==================");
    pinMode(lamp1, INPUT);
  }
  if (tempPayload == "lamp2/on")
  {
    Serial.println("==================");
    Serial.println("Lamp-2 Status: ON");
    Serial.println("Topic Message " + tempPayload);
    Serial.println("==================");
    pinMode(lamp2, OUTPUT);
  }
  if (tempPayload == "lamp2/off")
  {
    Serial.println("==================");
    Serial.println("Lamp-2 Status: OFF");
    Serial.println("Topic Message " + tempPayload);
    Serial.println("==================");
    pinMode(lamp2, INPUT);
  }
  if (tempPayload == "lamp3/on")
  {
    Serial.println("==================");
    Serial.println("Lamp-3 Status: ON");
    Serial.println("Topic Message " + tempPayload);
    Serial.println("==================");
    pinMode(lamp3, OUTPUT);
  }
  if (tempPayload == "lamp3/off")
  {
    Serial.println("==================");
    Serial.println("Lamp-3 Status: OFF");
    Serial.println("Topic Message " + tempPayload);
    Serial.println("==================");
    pinMode(lamp3, INPUT);
  }
  // Validation if empty request
  if (tempPayload == "")
  {
    Serial.println("==================");
    Serial.println("Topic Message message not found");
    Serial.println("==================");
  }
}

void setup()
{

  Serial.begin(9600);
  

  // Declare wifi config
  WiFi.begin(wlanName, wlanPassword);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print("#");
  }
  Serial.println("");
  Serial.println("Connected");

  // Set server broker
  client.setServer(brokerAddress, 1883);
  client.setCallback(callback);
}

void loop()
{
  if (!client.connected())
  {
    reconnect();
  }
  client.loop();

  // Delay
  unsigned long now = millis();
  if (now - lastMsg > 5000)
  {
    lastMsg = now;

    // Logic for turn on lamp
    // Comment saja jika lampu nggak mau mati
  }
}