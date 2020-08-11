from flask import Flask,jsonify,request
import mysql.connector
app=Flask(__name__)
@app.route("/",methods=["GET"])
def root():
    return "<h1>Welcome to Internet of Animal Health Things(IoAHT) Web Page!</h1>"
############################################################humidity####################################################
@app.route("/humidity", methods=["POST"])
def post_humidity():
    humidity = request.json.get("humidity")
    connection = mysql.connector.connect(host="localhost", user="root", password="Gyrfalcons@22", database="IoAHT")
    cursor = connection.cursor()
    statement = f"insert into humidity (humidity_readings) values ({humidity})"
    cursor.execute(statement)
    connection.commit()
    cursor.close()
    connection.close()
    return "<h4>inserted new humidity reading</h4>"

@app.route("/humidity",methods=["GET"])
def get_humidity():
    connection = mysql.connector.connect(host="localhost",user="root",password="Gyrfalcons@22",database="IoAHT")
    cursor = connection.cursor()
    statement = "select * from humidity"
    cursor.execute(statement)
    data = cursor.fetchall()
    humidities = []
    for humidity in data:
        humidities.append({
            "id":humidity[0],
             "Humidity":humidity[1]
        })
    cursor.close()
    connection.close()
    return jsonify(humidities)
####################################################temperature########################################################

@app.route("/temp", methods=["POST"])
def post_temp():
    temp = request.json.get("temp")
    connection = mysql.connector.connect(host="localhost", user="root", password="Gyrfalcons@22", database="IoAHT")
    cursor = connection.cursor()
    statement = f"insert into temperature (temp_readings) values ({temp})"
    cursor.execute(statement)
    connection.commit()
    cursor.close()
    connection.close()
    return "<h4>inserted new temp</h4>"

@app.route("/temp",methods=["GET"])
def get_distances():
    connection = mysql.connector.connect(host="localhost",user="root",password="Gyrfalcons@22",database="IoAHT")
    cursor = connection.cursor()
    statement = "select * from temperature"
    cursor.execute(statement)
    data = cursor.fetchall()
    temperatures = []
    for temp in data:
        temperatures.append({
            "id":temp[0],
             "Temperature":temp[1]
        })
    cursor.close()
    connection.close()
    return jsonify(temperatures)

###############################################Pressure#############################################################
@app.route("/pressure", methods=["POST"])
def post_pressure():
    pressure = request.json.get("pressure")
    connection = mysql.connector.connect(host="localhost", user="root", password="Gyrfalcons@22", database="IoAHT")
    cursor = connection.cursor()
    statement = f"insert into pressure (pressure_readings) values ({pressure})"
    cursor.execute(statement)
    connection.commit()
    cursor.close()
    connection.close()
    return "<h4>inserted new pressure</h4>"

@app.route("/pressure",methods=["GET"])
def get_pressure():
    connection = mysql.connector.connect(host="localhost",user="root",password="Gyrfalcons@22",database="IoAHT")
    cursor = connection.cursor()
    statement = "select * from pressure"
    cursor.execute(statement)
    data = cursor.fetchall()
    pressures = []
    for press in data:
        pressures.append({
            "id":press[0],
             "pressure":press[1]
        })
    cursor.close()
    connection.close()
    return jsonify(pressures)

###############################################Heart Pulses################################################################

@app.route("/hp", methods=["POST"])
def post_hp():
    hp = request.json.get("hp")
    connection = mysql.connector.connect(host="localhost", user="root", password="Gyrfalcons@22", database="IoAHT")
    cursor = connection.cursor()
    statement = f"insert into pulses (pulse_readings) values ({hp})"
    cursor.execute(statement)
    connection.commit()
    cursor.close()
    connection.close()
    return "inserted new pulse"

@app.route("/hp",methods=["GET"])
def get_hp():
    connection = mysql.connector.connect(host="localhost",user="root",password="Gyrfalcons@22",database="IoAHT")
    cursor = connection.cursor()
    statement = "select * from pulses"
    cursor.execute(statement)
    data = cursor.fetchall()
    pulses = []
    for hp in data:
        pulses.append({
            "id":hp[0],
             "PulseRate":hp[1]
        })
    cursor.close()
    connection.close()
    return jsonify(pulses)
#################################################Gases###################################################################


@app.route("/gases", methods=["POST"])
def post_gases():
    gases = request.json.get("gases")
    connection = mysql.connector.connect(host="localhost", user="root", password="Gyrfalcons@22", database="IoAHT")
    cursor = connection.cursor()
    statement = f"insert into gases (gas_readings) values ({gases})"
    cursor.execute(statement)
    connection.commit()
    cursor.close()
    connection.close()
    return "inserted new gases"

@app.route("/gases",methods=["GET"])
def get_gases():
    connection = mysql.connector.connect(host="localhost",user="root",password="Gyrfalcons@22",database="IoAHT")
    cursor = connection.cursor()
    statement = "select * from gases"
    cursor.execute(statement)
    data = cursor.fetchall()
    gases = []
    for gas in data:
        gases.append({
            "id":gas[0],
             "GasReading":gas[1]
        })
    cursor.close()
    connection.close()
    return jsonify(gases)

###############################################Exit#####################################################################
if __name__ == '__main__':
    app.run(port=5000, host='0.0.0.0', debug=True)