#include <ESP8266WiFi.h>
#include <PubSubClient.h>
const char* ssid = "Manas";
const char* password = "Manas@007";
const char* mqtt_server = "broker.hivemq.com";
int leftmotor1 = 4;
int leftmotor2 = 5;
int rightmotor1 = 2;
int rightmotor2 = 14;
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup_wifi() {

  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  char tempval = (char)payload[0];
  switch (tempval)
  {
    case '0': //Forward
      digitalWrite(LED_BUILTIN, LOW);
      Serial.println("Forward");
      digitalWrite(leftmotor1, HIGH);     
      digitalWrite(leftmotor2, LOW);     
      digitalWrite(rightmotor1, HIGH);   
      digitalWrite(rightmotor2, LOW);     

      break;
    case '1':// Backward
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.println("Backward");
      digitalWrite(leftmotor1, LOW);     
      digitalWrite(leftmotor2, HIGH);    
      digitalWrite(rightmotor1, LOW);     
      digitalWrite(rightmotor2, HIGH);    

      break;
    case '2'://Left
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.println("Left");
      digitalWrite(leftmotor1, HIGH);     
      digitalWrite(leftmotor2, LOW);     
      digitalWrite(rightmotor1, LOW);    
      digitalWrite(rightmotor2, HIGH);   
      break;
    case '3'://Right
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.println("Right");
      digitalWrite(leftmotor1, LOW);     
      digitalWrite(leftmotor2, HIGH);    
      digitalWrite(rightmotor1, HIGH);   
      digitalWrite(rightmotor2, LOW);    
      break;
    case '4'://Stop
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.println("Stop");
      digitalWrite(leftmotor1, LOW);     
      digitalWrite(leftmotor2, LOW);     
      digitalWrite(rightmotor1, LOW);    
      digitalWrite(rightmotor2, LOW);    
      break;
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      client.publish("outTopicManas", "hello world");
      client.subscribe("inTopicManas");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  pinMode(leftmotor1, OUTPUT);   
  pinMode(leftmotor2, OUTPUT);   
  pinMode(rightmotor1, OUTPUT);   
  pinMode(rightmotor2, OUTPUT);     
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    snprintf (msg, 75, "hello world #%ld", value);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("outTopicManas", msg);
  }
}
