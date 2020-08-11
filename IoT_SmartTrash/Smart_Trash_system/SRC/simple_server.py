# step1: import the Flask from flask
from flask import Flask

# step2: create a application server
app = Flask(__name__)

# call the function when server receives
# a request with path = /
@app.route("/")
def welcome_page():
    return "welcome to my server"

# step3: start the application server
app.run()
