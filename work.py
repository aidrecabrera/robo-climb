from flask import Flask, request, render_template
import serial

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def robot_control():
    if request.method == 'POST':
        data = request.json
        command = data['command']
        print(f"Received command: {command}")

        try:
            # Send command to Arduino board via serial communication
            ser = serial.Serial('COM5', 9600, timeout=1)
            ser.write(command.encode())
            ser.close()
            return "Command sent successfully!", 200
        except Exception as e:
            print("Error: Serial port not available." + str(e))
            return "Error: Serial port not available.", 500

    elif request.method == 'GET':
        return render_template('main.html')

@app.route('/speed', methods=['POST'])
def set_speed():
    if request.method == 'POST':
        data = request.json
        speed = data['speed']
        print(f"Setting speed: {speed}")

        try:
            # Send speed control command to Arduino board via serial communication
            ser = serial.Serial('COM5', 9600, timeout=1)
            ser.write(str(speed).encode())
            ser.close()
            return "Speed set successfully!", 200
        except Exception as e:
            print("Error: Serial port not available." + str(e))
            return "Error: Serial port not available.", 500

if __name__ == '__main__':
    # Check if serial port is available
    try:
        ser = serial.Serial('COM5', 9600, timeout=1)
        ser.close()
        print("Serial port is available.")
    except Exception as e:
        print("Error: Serial port not available." + str(e))
    
    app.run(port=8000)
