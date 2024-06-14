from flask import Flask, request, render_template, jsonify
from datetime import datetime

app = Flask(__name__)

sensor_data = {"temp": "", "humidity": ""}  # Menyimpan data sensor sementara

@app.route('/')
def hello_world():
    return render_template('index.html', sensor_data=sensor_data)

@app.route('/api/data', methods=['POST'])
def receive_data():
    if request.method == 'POST':
        try:
            ky = request.headers["X-API-Key"]
        except:
            return "Header Parsing Error"
        if ky == 'SIC45':
            if request.is_json:
                data = request.json
                temp = str(data.get("temp"))
                humidity = str(data.get("humidity"))
                print("Received data - Temperature: {}, Humidity: {}".format(temp, humidity))
                
                # Memperbarui data sensor
                sensor_data['temp'] = temp
                sensor_data['humidity'] = humidity
                
                return jsonify({"status": "success"})
            else:
                return jsonify({"status": "error", "message": "Formatting is not application/json"})
        else:
            return jsonify({"status": "error", "message": "API Key is invalid"})
    else:
        return jsonify({"status": "error", "message": "Method Not Allowed"})
        
if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0')
