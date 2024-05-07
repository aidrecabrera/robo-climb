from flask import Flask, request, render_template
import serial

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def robot_control():
    if request.method == 'POST':
        data = request.json
        command = data.get('command')
        return send_to_serial(command, 'Command')

    elif request.method == 'GET':
        return render_template('main.html')

@app.route('/speed', methods=['POST'])
def set_speed():
    data = request.json
    speed = data.get('speed')
    return send_to_serial(speed, 'Speed')

def send_to_serial(data, data_type):
    try:
        with serial.Serial('COM10', 9600, timeout=1) as ser:
            ser.write(data.encode())
            return f"{data_type} set successfully!", 200
    except serial.SerialException as e:
        return f"Error: Serial port not available. {e}", 500

if __name__ == '__main__':
    try:
        with serial.Serial('COM10', 9600, timeout=1) as ser:
            print("Serial port is available.")
    except serial.SerialException as e:
        print(f"Error: Serial port not available. {e}")
    
    app.run(port=8000)
