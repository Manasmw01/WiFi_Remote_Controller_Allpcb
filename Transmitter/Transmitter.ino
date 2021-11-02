
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
const char* ssid = "Manas";
const char* password = "Manas@007";
const char* mqtt_server = "broker.hivemq.com";
int forward = 12;
int backward = 13;
int left = 14;
int right = 16;
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;



#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  display.clearDisplay();

  testscrolltext();    // Draw scrolling text
  pinMode(forward, INPUT);     // Initialize the LED_BUILTIN  pin as an output
  pinMode(backward, INPUT);     // Initialize the LED_BUILTIN  pin as an output
  pinMode(left, INPUT);     // Initialize the LED_BUILTIN  pin as an output
  pinMode(right, INPUT);     // Initialize the LED_BUILTIN  pin as an output
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

}

void loop()
{
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 500) {
    lastMsg = now;
    if (digitalRead(forward) == 0)
    {
      client.publish("inTopicManas", "0");
    }
    else if (digitalRead(backward) == 0)
    {
      client.publish("inTopicManas", "1");
    }
    else if (digitalRead(left) == 0)
    {
      client.publish("inTopicManas", "2");
    }
    else if (digitalRead(right) == 0)
    {
      client.publish("inTopicManas", "3");
    }
    else
    {
      client.publish("inTopicManas", "4");
    }
    //    Serial.print("Publish message: ");
    //    client.publish("outTopicManas", msg);
  }

}

void testscrolltext(void) {
  display.clearDisplay();
  display.setTextSize(1); // Draw 2X-scale text
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println(F("Useless"));
  display.println("");
  display.println("");
  display.println(F("Design"));
  display.println("");
  display.println("");
  display.println(F("Competition"));
  display.display();      // Show initial text
  delay(100);
  display.startscrollright(0x00, 0x17);
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.startscrollleft(0x00, 0x17);
  delay(2000);
  display.stopscroll();
  delay(1000);
}

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
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
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      client.publish("inTopicManas", "hello world");
      client.subscribe("inTopicManas");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}
