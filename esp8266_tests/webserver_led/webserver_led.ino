#include <ESP8266WiFi.h>

 char* ssid = "your_wifi_network";
 char* pass = "your_password";

// specify the port to listen - 80
WiFiServer server(80);
int ledPin = 13;

void setup() {

  // prepare GPIO
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  Serial.begin(115200);
  delay(2000);
  Serial.println("Starting...");

  // Connect to WiFi network
  Serial.println("Trying to connect...");

  WiFi.begin(ssid, pass);
  
  //attempt to connect to Wifi network, checking status
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(5000); 
    Serial.print("Trying... status: ")   ;
    Serial.print(WiFi.status());
    Serial.println("");
  }

  Serial.println("Connected!!! CurrentIP: ");
  Serial.print(WiFi.localIP());
  Serial.println("");

  Serial.println("Server start");
  server.begin();
}

void loop() {

  WiFiClient client = server.available();

  // Check if a client has connected
  if (!client) {
    return;
  }

  Serial.println("New request");

  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  // match the request
  int state = matchRequest(req);

  //set GPIO according to the request
  digitalWrite(ledPin, state);
  client.flush();

  client.print(getHtmlResponse(state));
  delay(1);
  Serial.println("Client disonnected");
}

//parse the request ex. http://192.168.1.1/led/1
int matchRequest(String req) {

  if (req.indexOf("/led/1") != -1) {
    return 1;
  }

  if (req.indexOf("/led/0") != -1) {
    return 0;
  }

}

//return html response
String getHtmlResponse(int state) {

  String s = "<html>GPIO is ";
  s += (state) ? "HIGH" : "LOW";
  s += "</html>\n";
  return s;
}

