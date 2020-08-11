from flask import Flask, request

app = Flask(__name__)

@app.route("/", methods=["GET", "POST"])
def root():
    if request.method == 'GET':
        return "received get request"
    elif request.method == 'POST':
        return "recevied post request"
    else:
        return "welcome to my IoT frontend"


@app.route("/distance", methods=["GET"])
def get_distance():
    return "sending temperature value"


@app.route("/distance", methods=["POST"])
def post_distance():
    return "inserted into the db"


app.run(port=4000)