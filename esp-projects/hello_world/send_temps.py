import json
import time
import serial

PORT = "/dev/cu.usbmodem3101"

with serial.Serial(PORT, 115200, timeout=1) as esp:
    time.sleep(2)
    esp.reset_input_buffer()

    print("Sending dummy temperatures. Press Ctrl+C to stop.")

    try:
        while True:
            # Test values only — not actual sensor readings.
            data = {"cpu_c": 55.2, "gpu_c": 48.7}
            message = json.dumps(data) + "\n"

            esp.write(message.encode("utf-8"))
            print("SENT:", message.strip())

            reply = esp.readline().decode("utf-8", errors="replace").strip()
            print("ESP32:", reply or "(no reply)")

            time.sleep(1)

    except KeyboardInterrupt:
        print("\nStopped.")
