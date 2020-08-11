from flask import Flask, jsonify, request
import mysql.connector

app = Flask(__name__)
@app.route("/", methods=["GET"])
def root():
    return "welcome to the application"


@app.route("/dist", methods=["POST"])
def post_distance():
    temperature = request.json.get("distance")
    connection = mysql.connector.connect(host="localhost", user="root", password="root", database="desd_iot_project")
    cursor = connection.cursor()
    statement = "insert into distances (distance_value) values ({distance})"
    cursor.execute(statement)
    connection.commit()
    cursor.close()
    connection.close()
    return "inserted new distance"


@app.route("/distance", methods=["GET"])
def get_distances():
    connection = mysql.connector.connect(host="localhost", user="root", password="root", database="desd_iot_project")
    cursor = connection.cursor()
    statement = "select * from distances"
    cursor.execute(statement)
    data = cursor.fetchall()
    distances = []
    for distance in data:
        distances.append({
            "id": distance[0],
            "value": distance[1]
        })

    cursor.close()
    connection.close()
    return jsonify(distances)



if __name__ == '__main__' :
    app.run()