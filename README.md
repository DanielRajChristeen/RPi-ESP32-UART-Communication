# 🔌 RPi–ESP32 UART Communication

A beginner-friendly project demonstrating **bidirectional UART communication** between a **Raspberry Pi 4B** and an **ESP32 Dev Kit V1** using standard serial interfaces.

This repository focuses on **clarity, correctness, and fundamentals**, making it ideal for students, hobbyists, and early-stage embedded engineers.

---

## 📌 Project Objective

The goal of this project is to:

* Establish **reliable UART communication** between Raspberry Pi and ESP32
* Send and receive **human-readable strings** in real time
* Understand practical UART wiring, configuration, and debugging

This setup forms the backbone for many embedded and IoT systems.

---

## 🧰 Hardware Requirements

* Raspberry Pi 4B
* ESP32 Dev Kit V1
* USB cable (ESP32 power & programming)
* Jumper wires
* **Common Ground connection (mandatory)**

---

## 🔗 UART Wiring Connections

| ESP32        | Raspberry Pi | Function      |
| ------------ | ------------ | ------------- |
| TX2 (GPIO17) | RX (GPIO15)  | ESP32 → RPi   |
| RX2 (GPIO16) | TX (GPIO14)  | RPi → ESP32   |
| GND          | GND          | Common Ground |

> ⚠️ **Important**
> A missing common ground will result in corrupted or no data.

---

## ⚙️ UART Configuration

Both devices must share the same UART parameters:

* Baud Rate: **9600**
* Data Bits: **8**
* Parity: **None**
* Stop Bits: **1**

---

## 🧠 Software Architecture

### Raspberry Pi (Thonny IDE)

* Uses `pyserial`
* Runs in **dual mode**

  * Main thread → transmit user input
  * Background thread → receive ESP32 data

### ESP32 (Arduino IDE)

* Uses **hardware UART (`Serial2`)**
* Listens continuously for incoming messages
* Responds with acknowledgements

---

## 🐍 Raspberry Pi Code (Python)

**File:** `UART_Rpi.py`

Key concepts:

* Serial port configuration
* Non-blocking UART reads
* Threaded receive handler

```python
import serial
import threading

ser = serial.Serial(
    port='/dev/serial0',
    baudrate=9600,
    timeout=0.1
)

print("RPi UART Ready")
print("Type a message and press Enter")

def uart_rx():
    while True:
        if ser.in_waiting:
            data = ser.readline().decode(errors='ignore').strip()
            if data:
                print("\nESP32 >>", data)

threading.Thread(target=uart_rx, daemon=True).start()

while True:
    msg = input("RPi >> ")
    ser.write((msg + '\n').encode())
```

---

## 🔥 ESP32 Code (Arduino)

**File:** `UART_Rpi.ino`

Key concepts:

* Hardware UART initialization
* String-based serial handling
* Bidirectional communication

```cpp
void setup() {
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, 16, 17);
  Serial.println("ESP32 UART Ready");
}

void loop() {
  if (Serial2.available()) {
    String data = Serial2.readStringUntil('\n');
    Serial.println("RPi >> " + data);
    Serial2.println("Received: " + data);
  }
}
```

---

## ▶️ How to Run

### Raspberry Pi Setup

```bash
sudo apt update
sudo apt install python3-serial
sudo python3 UART_Rpi.py
```

### ESP32 Setup

1. Open Arduino IDE
2. Select **ESP32 Dev Module**
3. Upload `UART_Rpi.ino`
4. Open Serial Monitor (9600 baud)

---

## ✅ Expected Output

**Raspberry Pi Terminal**

```
RPi >> hello
ESP32 >> Received: hello
```

**ESP32 Serial Monitor**

```
RPi >> hello
```

This confirms **successful bidirectional UART communication**.

---

## 🧪 Common Issues & Troubleshooting

| Issue              | Cause         | Solution                  |
| ------------------ | ------------- | ------------------------- |
| No data            | Missing GND   | Connect common ground     |
| Garbage characters | Baud mismatch | Match UART settings       |
| I/O error          | UART disabled | Enable via `raspi-config` |
| Blocking input     | No timeout    | Use non-blocking reads    |

---

## 🎯 Learning Outcomes

* UART protocol fundamentals
* Hardware vs software serial
* Embedded system debugging
* Python threading for I/O
* Real-world serial communication reliability

---

## 🚀 Possible Extensions

* Send sensor data from ESP32 to RPi
* Control ESP32 GPIO from Raspberry Pi
* Increase baud rate
* Add packet framing or checksum
* Integrate with IoT dashboards

---

## 📜 License

MIT License — free to use, modify, and distribute.

---
