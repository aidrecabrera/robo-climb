from flask import Flask, request, render_template
import serial
import logging

app = Flask(__name__)
logging.basicConfig(level=logging.DEBUG)

@app.route('/', methods=['GET', 'POST'])
def robot_control():
    if request.method == 'POST':
        data = request.json
        command = data['command']
        logging.debug(f"Received command: {command}")

        try:
            # Send command to Arduino board via serial communication
            ser = serial.Serial('COM10', 9600, timeout=1)
            logging.debug(f"Sending command: {command.encode()}")
            ser.write(command.encode())
            ser.close()
            logging.debug("Command sent successfully!")
            return "Command sent successfully!", 200
        except Exception as e:
            logging.error("Error: Serial port not available." + str(e))
            return "Error: Serial port not available.", 500

    elif request.method == 'GET':
        return render_template('main.html')

@app.route('/speed', methods=['POST'])
def set_speed():
    if request.method == 'POST':
        data = request.json
        speed = data['speed']
        logging.debug(f"Setting speed: {speed}")

        try:
            # Send speed control command to Arduino board via serial communication
            ser = serial.Serial('COM10', 9600, timeout=1)
            logging.debug(f"Sending speed command: {str(speed).encode()}")
            ser.write(str(speed).encode())
            ser.close()
            logging.debug("Speed set successfully!")
            return "Speed set successfully!", 200
        except Exception as e:
            logging.error("Error: Serial port not available." + str(e))
            return "Error: Serial port not available.", 500

if __name__ == '__main__':
    # Check if serial port is available
    try:
        ser = serial.Serial('COM10', 9600, timeout=1)
        ser.close()
        logging.debug("Serial port is available.")
    except Exception as e:
        logging.error("Error: Serial port not available." + str(e))
    
    app.run(port=8000, debug=True)