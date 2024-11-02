#include <WiFi.h>

NetworkServer server = NetworkServer(80);

void setup() {
  Serial.begin(115200);

  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);

  WiFi.begin("Wifi", "Password"); //change wifi name and pass word

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting...");
  }

  server.begin();
  Serial.println("Connected");
  Serial.println(WiFi.localIP());
}

void loop() {

  NetworkClient client = server.accept();

  if (client) {

    String requestText = "";

    while (client.connected()) {
      if (client.available()) { 
        char c = client.read();
        requestText += c;

        if (c == '\n') {
          Serial.println(requestText);

          if (requestText.startsWith("GET /?status=1")) {
            digitalWrite(13, HIGH);
          } else {
            digitalWrite(13, LOW);
          }

          break;
        }
      }
    }
    client.stop();
  }
}
