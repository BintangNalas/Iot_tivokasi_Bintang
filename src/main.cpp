#include <Arduino.h>

int lampuMerah = 26;  // GPIO untuk lampu merah
int lampuKuning = 33; // GPIO untuk lampu kuning
int lampuHijau = 25;  // GPIO untuk lampu hijau

void setup()
{
  Serial.begin(115200);
  Serial.println("ESP32 Traffic Light Simulation");

  pinMode(lampuMerah, OUTPUT);
  pinMode(lampuKuning, OUTPUT);
  pinMode(lampuHijau, OUTPUT);
}

void loop()
{
  // Lampu Merah ON
  digitalWrite(lampuMerah, HIGH);
  digitalWrite(lampuKuning, LOW);
  digitalWrite(lampuHijau, LOW);
  Serial.println("Lampu Merah: ON");
  delay(2000); // Lampu merah menyala selama 5 detik

  // Lampu Kuning ON
  digitalWrite(lampuMerah, LOW);
  digitalWrite(lampuKuning, HIGH);
  digitalWrite(lampuHijau, LOW);
  Serial.println("Lampu Kuning: ON");
  delay(2000); // Lampu kuning menyala selama 2 detik

  // Lampu Hijau ON
  digitalWrite(lampuMerah, LOW);
  digitalWrite(lampuKuning, LOW);
  digitalWrite(lampuHijau, HIGH);
  Serial.println("Lampu Hijau: ON");
  delay(2000); // Lampu hijau menyala selama 5 detik
}
