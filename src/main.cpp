#include <Arduino.h>
#include <esp32cam.h>
#include <WifiSettings.h>
#include <WebServer.h>

// Using the Grove SDA pin to trigger a ULN2803 driver to light a LED lamp.
#define LED_PIN 12
#define CAMERA_MODEL_M5STACK_PSRAM

WebServer server(80);

static auto hiRes = esp32cam::Resolution::find(1200, 900);

void handlePicture() {
  Serial.println("GET");

  digitalWrite(LED_PIN, HIGH);
  delay(100);

  if (!esp32cam::Camera.changeResolution(hiRes)) {
    Serial.println("SET-HI-RES FAIL");
  }

  auto frame = esp32cam::capture();
  if (frame == nullptr) {
    Serial.println("CAPTURE FAIL");
    server.send(503, "", "");
    digitalWrite(LED_PIN, LOW);
    return;
  }

  digitalWrite(LED_PIN, LOW);

  server.setContentLength(frame->size());
  server.send(200, "image/jpeg");
  WiFiClient client = server.client();
  frame->writeTo(client);  
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println();

  pinMode(LED_PIN, OUTPUT);  

  {
    using namespace esp32cam;
    Config cfg;
    cfg.setPins(pins::M5cameraA);
    cfg.setResolution(hiRes);
    cfg.setBufferCount(1);
    cfg.setJpeg(80);

    bool ok = Camera.begin(cfg);
    Serial.println(ok ? "CAMERA OK" : "CAMERA FAIL");
  }

  WiFi.persistent(false);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
   
  while (WiFi.status() != WL_CONNECTED) {
     Serial.printf("Not connected: %d.\n", WiFi.status());
     delay(500);
  }

  Serial.println("Connected.");
  Serial.println(WiFi.localIP());

  server.on("/", handlePicture);
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
}