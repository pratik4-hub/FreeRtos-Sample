from flask import Flask,jsonify,request
import mysql.connector
app=Flask(__name__)
@app.route("/",methods=["GET"])
def root():
    return "welcome to the application"
##########################################Dist-1############################################################
@app.route("/dist1", methods=["POST"])
def post_distance():
    distance1 = request.json.get("dist1")
    connection = mysql.connector.connect(host="localhost", user="root", password="root", database="WMSystem")
    cursor = connection.cursor()
    statement = f"insert into distances (Dustbin_A) values ({distance1})"
    cursor.execute(statement)
    connection.commit()
    cursor.close()
    connection.close()
    return "inserted new distance1"

@app.route("/dist1",methods=["GET"])
def get_distances():
    connection = mysql.connector.connect(host="localhost",user="root",password="root",database="WMSystem")
    cursor = connection.cursor()
    statement = "select * from distances"
    cursor.execute(statement)
    data = cursor.fetchall()
    distances1 = []
    for dist1 in data:
        distances1.append({
            "id":dist1[0],
             "value":dist1[1]
        })
    cursor.close()
    connection.close()
    return jsonify(distances1)
########################################Dist-2###################################################################

@app.route("/dist2", methods=["POST"])
def post_distance1():
    distance2 = request.json.get("dist2")
    connection = mysql.connector.connect(host="localhost", user="root", password="root", database="WMSystem")
    cursor = connection.cursor()
    statement = f"insert into distances (Dustbin_B) values ({distance2})"
    cursor.execute(statement)
    connection.commit()
    cursor.close()
    connection.close()
    return "inserted new distance2"

@app.route("/dist2",methods=["GET"])
def get_distances1():
    connection = mysql.connector.connect(host="localhost",user="root",password="root",database="WMSystem")
    cursor = connection.cursor()
    statement = "select * from distances"
    cursor.execute(statement)
    data = cursor.fetchall()
    distances2 = []
    for dist2 in data:
        distances2.append({
            "id":dist2[0],
             "value":dist2[1]
        })
    cursor.close()
    connection.close()
    return jsonify(distances2)

##################################################END######################################################
if __name__ == '__main__':
    app.run(port=5000, host='172.18.4.145', debug=True)