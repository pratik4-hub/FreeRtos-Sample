from flask import Flask,jsonify,request
import mysql.connector
app=Flask(__name__)
@app.route("/",methods=["GET"])
def root():
    return "welcome to the application"

@app.route("/temp", methods=["POST"])
def post_temperature():
    temperature = request.json.get("temp")
    connection = mysql.connector.connect(host="localhost", user="root", password="root", database="desd_project")
    cursor = connection.cursor()
    statement = f"insert into temperatures (temperature_value) values ({temperature})"
    cursor.execute(statement)
    connection.commit()
    cursor.close()
    connection.close()
    return "inserted new temperature"

@app.route("/temp",methods=["GET"])
def get_temperatures():
    connection = mysql.connector.connect(host="localhost",user="root",password="root",database="desd_project")
    cursor = connection.cursor()
    statement = "select * from temperatures"
    cursor.execute(statement)
    data = cursor.fetchall()
    temperatures = []
    for temp in data:
        temperatures.append({
            "id":temp[0],
             "value":temp[1]
        })
    cursor.close()
    connection.close()
    return jsonify(temperatures)

if __name__ == '__main__':
    app.run()