#define RXD2 16
#define TXD2 17

String rxBuffer = "";

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);

  Serial.println("ESP32 UART Dual Mode Ready");
  Serial.println("Type in Serial Monitor and press Enter");
}

void loop() {
  // ---------- RECEIVE FROM RPi ----------
  while (Serial2.available()) {
    char c = Serial2.read();
    if (c == '\n') {
      Serial.println("RPi >> " + rxBuffer);
      rxBuffer = "";
    } else {
      rxBuffer += c;
    }
  }

  // ---------- SEND TO RPi ----------
  if (Serial.available()) {
    String msg = Serial.readStringUntil('\n');
    Serial2.println(msg);
  }
}
