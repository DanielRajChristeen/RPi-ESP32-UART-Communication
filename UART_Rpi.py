import serial
import threading

ser = serial.Serial(
    port='/dev/serial0',
    baudrate=9600,
    timeout=0.1
)

print("RPi UART Dual Mode Ready")
print("Type and press Enter")

# ---------- RECEIVE THREAD ----------
def uart_rx():
    while True:
        if ser.in_waiting:
            data = ser.readline().decode(errors='ignore').strip()
            if data:
                print("\nESP32 >>", data)

# Start RX thread
threading.Thread(target=uart_rx, daemon=True).start()

# ---------- TRANSMIT ----------
while True:
    msg = input("RPi >> ")
    ser.write((msg + '\n').encode())
