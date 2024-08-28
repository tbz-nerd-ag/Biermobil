#include <ESP8266WiFi.h>           // Include the Wi-Fi library (need Arduino Uno WiFi Dev Ed library installed)
#include <ArduinoMqttClient.h>     // Include the ArduinoMqtt library (need ArduinoMqttClient installed)

WiFiClient wifiClient;              // Creates a WifiClient
MqttClient mqttClient(wifiClient);  // Creates a MqttClient which uses the WifiClient

const char* ssid     = "wifi";                            // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "12345678";                            // The password of the Wi-Fi network

const char broker[] = "test.mosquitto.org";   // The adress of the Mqtt you want to connect to 
const char topic[]  = "";                     // The name of the topic you want to sent the message in

const char message1[] = "1";                // The message you want to sent
const char message2[] = "2";                // The message you want to sent
const char message3[] = "3";                // The message you want to sent
const char message4[] = "4";                // The message you want to sent
const char message5[] = "5";                // The message you want to sent
const char message6[] = "6";                // The message you want to sent
const char message7[] = "7";                // The message you want to sent
const char message8[] = "8";                // The message you want to sent

const char topic2[] = "materna2";   // Reconnect message

const int port = 1883;         // Sets the port for the Mqtt

const int pin1 = D2;     // The pin the first relay of the joystick is connected to
const int pin2 = D3;     // The pin the second relay of the joystick is connected to
const int pin3 = D4;     // The pin the third relay of the joystick is connected to
const int pin4 = D5;     // The pin the fourth relay of the joystick is connected to

unsigned long previousMillis = 0;   // Creates a variable which saves the last time a message was sent 

void setup()    // Getts executed when the script starts 
{
  pinMode(pin1, INPUT);       // declare the first relay of the joystick as an input
  pinMode(pin2, INPUT);       // declare the second relay of the joystick as an input
  pinMode(pin3, INPUT);       // declare the third relay of the joystick as an input
  pinMode(pin4, INPUT);       // declare the fourth relay of the joystick as an input

  Serial.begin(9600);               // Start the Serial communication to send messages to the computer
  delay(3000);                      // Wait for 1 second
  Serial.println("Starting...");    // Communicate to the computer that the script is starting
  
  WiFi.begin(ssid, password);       // Connect to the network with the SSID and the password
  Serial.print("Connecting to ");   // Communicate to the computer that the Arbuino is attempting to connecting to (SSID)
  Serial.print(ssid);               // Communicate to the computer which SSID (name) the network has
  Serial.println(" ...");           // Communicate to the computer that the Arbuino is still attempting to connect

  while (WiFi.status() != WL_CONNECTED)   // Wait for the WiFi to connect
  { 
    delay(1000);            // Wait 1 second
    Serial.print(".");      // Communicate to the computer that the Arbuino is still attempting to connect
    delay(350);             // Wait 1 second
    Serial.print(".");      // Communicate to the computer that the Arbuino is still attempting to connect
    delay(350);             // Wait 1 second
    Serial.print(".");      // Communicate to the computer that the Arbuino is still attempting to connect
    delay(350);             // Wait 1 second
    Serial.println(".");    // Communicate to the computer that the Arbuino is still attempting to connect
  }

  Serial.println('\n');                         // Creates a Line spacing
  Serial.println("Connection established!");    // Communicate to the computer that the Arduino is connected to the netwerk   
  Serial.print("IP address:\t");                // Communicate to the computer the IP adress from the netwerk
  Serial.println(WiFi.localIP());               // Send the IP address of the ESP8266 to the computer
  Serial.println('\n');                         // Creates a Line spacing

  Serial.print("Attempting to connect to the MQTT broker: ");   // Communicate to the computer that the arduino is attempting to connect to the Mqtt
  Serial.println(broker);                                       // Communicate to the computer the adress of the Mqtt

  if (!mqttClient.connect(broker, port))    // if the connection fails communicate to the computer which error has been detected
    {
    Serial.print("MQTT connection failed! Error code = ");    // Communicate to the computer that the connection has failed
    Serial.println(mqttClient.connectError());                // Communicate to the computer the error code
    
    if (!mqttClient.connect(broker, port))    // if it still doesn't work repeat
   
    Serial.print("MQTT connection failed! Error code = ");    // Communicate to the computer that the connection has failed
    Serial.println(mqttClient.connectError());                // Communicate to the computer the error code
    } 
    
    Serial.println("You're connected to the MQTT broker!");   // Communicate to the computer that the Arduino has conneted to the Mqtt
    Serial.println('\n');                                     // Creates a Line spacing
}

void loop()   // Getts executed every tick
{
    unsigned long currentMillis = millis();       // Get the current "time" in millis
  
    mqttClient.poll();                        // Eliminates the need for message consumers to periodically check (simply eliminates all connections to reduce network traffic) 

    int relay1_state = digitalRead(pin1);   // Save if the first relay oif the Joystick is HIGH or LOW
    int relay2_state = digitalRead(pin2);   // Save if the second relay oif the Joystick is HIGH or LOW 
    int relay3_state = digitalRead(pin3);   // Save if the third relay oif the Joystick is HIGH or LOW 
    int relay4_state = digitalRead(pin4);   // Save if the fourth relay oif the Joystick is HIGH or LOW  

    control();

 /*if (currentMillis - previousMillis >= 30000)    // Checks if a keep alive message is needed
    {
    Serial.print("Reconnect to the MQTT broker: ");    // Communicate to the computer that the Arduino is sending a keep alive message
    Serial.println(broker);                            // Communicate to the computer the name of the broker
    Serial.println("Reconnected");                     // Communicate to the computer that the Arduino is sending a keep alive message 
    mqttClient.beginMessage(topic2);                   // Communicate to the Mqtt the topic
    mqttClient.print("Reconnected");                   // Communicate to the Mqtt which message was sent
    mqttClient.endMessage();                           // Ends the message and sent it completly
    Serial.println('\n');                              // Creates a line space
    
    }*/
}

void control()
{
  mqttClient.poll();                        // Eliminates the need for message consumers to periodically check (simply eliminates all connections to reduce network traffic)
  
  if (relay1_state == LOW)   // Checks if the first relay is HIGH 
  {
     mqttClient.beginMessage(topic);   // Communicate to the Mqtt the topic
     mqttClient.print(message1);        // Communicate to the Mqtt which message was sent
     mqttClient.endMessage();          // Ends the message and sent it completly
 }
 if (relay2_state == LOW)   // Checks if the second relay is HIGH 
  {
     mqttClient.beginMessage(topic);   // Communicate to the Mqtt the topic
     mqttClient.print(message2);        // Communicate to the Mqtt which message was sent
     mqttClient.endMessage();          // Ends the message and sent it completly
 }
 if (relay3_state == LOW)   // Checks if the third relay is HIGH 
  {
     mqttClient.beginMessage(topic);   // Communicate to the Mqtt the topic
     mqttClient.print(message3);        // Communicate to the Mqtt which message was sent
     mqttClient.endMessage();          // Ends the message and sent it completly
 }
 if (relay4_state == LOW)   // Checks if the fourth relay is HIGH 
  {
     mqttClient.beginMessage(topic);   // Communicate to the Mqtt the topic
     mqttClient.print(message4);        // Communicate to the Mqtt which message was sent
     mqttClient.endMessage();          // Ends the message and sent it completly
 }
 if (relay1_state && relay2_state == LOW)   // Checks if the first and second relay is HIGH 
  {
     mqttClient.beginMessage(topic);   // Communicate to the Mqtt the topic
     mqttClient.print(message5);        // Communicate to the Mqtt which message was sent
     mqttClient.endMessage();          // Ends the message and sent it completly
 }
 if (relay2_state && relay3_state == LOW)   // Checks if the second and third relay is HIGH 
  {
     mqttClient.beginMessage(topic);   // Communicate to the Mqtt the topic
     mqttClient.print(message6);        // Communicate to the Mqtt which message was sent
     mqttClient.endMessage();          // Ends the message and sent it completly
 }
 if (relay3_state && relay4_state == LOW)   // Checks if the third and fourth relay is HIGH 
  {
     mqttClient.beginMessage(topic);   // Communicate to the Mqtt the topic
     mqttClient.print(message7);        // Communicate to the Mqtt which message was sent
     mqttClient.endMessage();          // Ends the message and sent it completly
 }
 if (relay4_state && relay1_state == LOW)   // Checks if the fourth and first relay is HIGH 
  {
     mqttClient.beginMessage(topic);   // Communicate to the Mqtt the topic
     mqttClient.print(message8);        // Communicate to the Mqtt which message was sent
     mqttClient.endMessage();          // Ends the message and sent it completly
 }
}
