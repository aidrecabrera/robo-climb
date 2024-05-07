import time
import serial

# Define the serial port and baud rate
serial_port = 'COM10'  # Change this to the appropriate serial port
baud_rate = 9600

try:
    # Open the serial port
    ser = serial.Serial(serial_port, baud_rate, timeout=1)
    print(f"Serial port {serial_port} opened successfully.")

    # Wait for a moment to let the Arduino board initialize
    time.sleep(2)

    # Send a command to the Arduino
    command = 'L'  # Example command (change as needed)
    ser.write(command.encode())
    print(f"Command '{command}' sent to the Arduino.")

    # Close the serial port
    ser.close()
    print("Serial port closed.")

except Exception as e:
    print(f"Error: {e}")
