#include <WiFi.h>

#include <WebServer.h>



// ใส่ Wi-Fi SSID และ Password ของคุณที่นี่

const char* ssid = "xxx";

const char* password = "xxxxxxx";



// ตั้งขาที่ใช้ควบคุม LED

const int ledPin = 4;



// สร้าง Web Server ที่พอร์ต 80

WebServer server(80);



// สร้าง HTML สำหรับเว็บควบคุม

String htmlPage() {

  String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'>";

  html += "<title>AllneweStep ESP32-C3 Web Control</title>";

  html += "<style>button{padding:50%;font-size:240px;margin:10px;}</style></head><body>";

  html += "<h1>AllneweStep ESP32-C3 Web Control</h1>";

  html += "<form action='/on'><button>เปิด</button></form>";

  html += "<form action='/off'><button>ปิด</button></form>";

  html += "</body></html>";

  return html;

}



// ฟังก์ชัน: เมื่อเข้าหน้า root

void handleRoot() {

  server.send(200, "text/html", htmlPage());

}



// ฟังก์ชัน: เปิดไฟ

void handleOn() {

  digitalWrite(ledPin, 1);

  server.send(200, "text/html", htmlPage());

}



// ฟังก์ชัน: ปิดไฟ

void handleOff() {

  digitalWrite(ledPin, 0);

  server.send(200, "text/html", htmlPage());

}



void setup() {

  Serial.begin(115200);

  delay(1000);



  pinMode(ledPin, OUTPUT);
  pinMode(8, OUTPUT);

  digitalWrite(ledPin, 0);
  digitalWrite(8,0);




  Serial.println("เชื่อมต่อ Wi-Fi...");

  WiFi.begin(ssid, password);



  // รอจนกว่าจะเชื่อมต่อ Wi-Fi ได้

  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(8, 0);

    delay(250);

    Serial.print(".");
    digitalWrite(8,1);
    delay(250);

  }

  Serial.println("\nเชื่อมต่อแล้ว!");
  digitalWrite(8,1);

  Serial.println("IP Address: ");

  Serial.println(WiFi.localIP());



  // ตั้งค่าหน้าเว็บ

  server.on("/", handleRoot);

  server.on("/on", handleOn);

  server.on("/off", handleOff);



  server.begin();

  Serial.println("HTTP server เริ่มทำงานแล้ว");

}



void loop() {

  server.handleClient();

}