#include <ESP8266WiFi.h> // Library untuk ESP8266, gunakan ESP32 jika Anda menggunakan modul ESP32
#include <WiFiClient.h>

// Pin definisi
const int sensorPin = A0;    // Pin untuk sensor kelembapan tanah
const int relayPin = D1;     // Pin untuk relay (mengendalikan pompa)

const char* ssid = "Your_WiFi_Name";   // Ganti dengan nama jaringan Wi-Fi Anda
const char* password = "Your_WiFi_Password";   // Ganti dengan password Wi-Fi Anda

WiFiClient client;

// Ambang batas kelembapan tanah (nilai yang akan mengaktifkan pompa)
int threshold = 500;  // Nilai ini bisa disesuaikan dengan sensor kelembapan yang digunakan

void setup() {
  Serial.begin(115200);  // Menginisialisasi serial monitor
  pinMode(relayPin, OUTPUT);  // Mengatur pin relay sebagai output
  digitalWrite(relayPin, LOW);  // Memastikan pompa mati pada awalnya

  // Menghubungkan ke Wi-Fi
  Serial.println();
  Serial.print("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi!");
}

void loop() {
  // Membaca nilai kelembapan tanah dari sensor
  int moistureLevel = analogRead(sensorPin);
  Serial.print("Kelembapan Tanah: ");
  Serial.println(moistureLevel);

  // Jika kelembapan tanah di bawah ambang batas, aktifkan pompa
  if (moistureLevel < threshold) {
    digitalWrite(relayPin, HIGH);  // Menyalakan pompa
    Serial.println("Pompa Menyala!");
  } else {
    digitalWrite(relayPin, LOW);   // Mematikan pompa
    Serial.println("Pompa Mati.");
  }

  delay(5000); // Delay selama 5 detik sebelum membaca kelembapan lagi
}
