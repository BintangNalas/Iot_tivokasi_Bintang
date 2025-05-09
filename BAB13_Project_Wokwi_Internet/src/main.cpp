#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"

// Definisi pin dan tipe sensor DHT22
#define DHTPIN 27    
#define DHTTYPE DHT22  

DHT dht(DHTPIN, DHTTYPE);

// Kredensial WiFi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// URL server ngrok (pastikan tidak ada spasi berlebih)
const char* server = "http://86f5-36-73-241-171.ngrok-free.app/api/posts";

// Timer untuk interval pengiriman data
unsigned long previousMillis = 0;
const long interval = 5000;  // 5 detik

void setup() {
  Serial.begin(115200);

  // Hubungkan ke WiFi
  WiFi.begin(ssid, password);
  Serial.print("Menghubungkan ke WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nTerhubung ke WiFi!");

  // Inisialisasi DHT sensor
  dht.begin();
  delay(1000);
}

void loop() {
  unsigned long currentMillis = millis();

  // Kirim data setiap interval 5 detik
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Membaca data dari sensor
    float h = dht.readHumidity();
    float t = dht.readTemperature(); // Celsius

    // Pastikan pembacaan berhasil
    if (isnan(h) || isnan(t)) {
      Serial.println("Gagal membaca data dari sensor DHT!");
      return;
    }

    // Konversi ke integer sebelum mengirimkan data
    int humidity = (int)h;
    int temperature = (int)t;

    // Membuat JSON payload
    String payload = "{\"nama_sensor\":\"Sensor GD\", \"nilai1\":" + String(humidity) + ", \"nilai2\":" + String(temperature) + "}";

    // Debugging: Cek payload sebelum dikirim
    Serial.println("Payload JSON:");
    Serial.println(payload);

    // Inisialisasi HTTP Client
    HTTPClient http;
    http.begin(server);  // Menggunakan HTTP, bukan HTTPS
    http.addHeader("Content-Type", "application/json");

    // Kirim POST request
    int httpResponseCode = http.POST(payload);

    // Menampilkan hasil respons HTTP
    Serial.print("Kode respons HTTP: ");
    Serial.println(httpResponseCode);

    if (httpResponseCode == 200 || httpResponseCode == 201) {
      String response = http.getString();
      Serial.println("Respons dari server:");
      Serial.println(response);
    } else {
      Serial.println("Gagal mengirim data ke server!");
    }

    // Tutup koneksi HTTP
    http.end();
  }
}
