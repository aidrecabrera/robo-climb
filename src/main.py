from flask import Flask, request, render_template, jsonify
import serial
import os

app = Flask(__name__)

# Default COM port and baud rate
COM_PORT = os.getenv('COM_PORT', 'COM1')
BAUD_RATE = 9600

# Serial port object
serial_conn = None

def init_serial_connection():
    global serial_conn
    try:
        serial_conn = serial.Serial(COM_PORT, BAUD_RATE, timeout=1)
        print(f"Connected to {COM_PORT} at {BAUD_RATE} baud.")
    except serial.SerialException as e:
        print(f"Error: Could not open serial port {COM_PORT}. {e}")

@app.route('/', methods=['GET', 'POST'])
def robot_control():
    if request.method == 'POST':
        data = request.json
        command = data.get('command')
        print(f"Command received: {command}")
        return send_to_serial(f"{command}\n", 'Command')

    elif request.method == 'GET':
        return render_template('main.html')

@app.route('/speed', methods=['POST'])
def set_speed():
    data = request.json
    speed = data.get('speed')
    print(f"Speed received: {speed}")
    return send_to_serial(f"SP{speed}\n", 'Speed')

@app.route('/set_com_port', methods=['POST'])
def set_com_port():
    global COM_PORT, serial_conn
    data = request.json
    new_com_port = data.get('com_port')
    if new_com_port:
        COM_PORT = new_com_port
        if serial_conn and serial_conn.is_open:
            serial_conn.close()
        init_serial_connection()
        print(f"COM port changed to {COM_PORT}")
        return jsonify({"message": f"COM port changed to {COM_PORT}"}), 200
    return jsonify({"error": "Invalid COM port"}), 400

def send_to_serial(data, data_type):
    global serial_conn
    if serial_conn and serial_conn.is_open:
        try:
            serial_conn.write(data.encode())
            print(f"{data_type} set successfully: {data.strip()}")
            return f"{data_type} set successfully!", 200
        except serial.SerialException as e:
            print(f"Error: Serial write failed. {e}")
            return f"Error: Serial write failed. {e}", 500
    else:
        print(f"Error: Serial port {COM_PORT} is not open.")
        return f"Error: Serial port {COM_PORT} is not open.", 500

if __name__ == '__main__':
    init_serial_connection()
    app.run(port=8000)
