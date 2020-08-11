from flask import Flask,request,jsonify
app=Flask(__name__)
distance_values=[]
@app.route("/",methods=["GET"])
def root():
    return "<h1>Welcome to my application</h1>"
@app.route('/dist',methods=["GET"])
def get_distance():
    print(distance_values)
    return jsonify(distance_values)

@app.route('/dist',methods=["POST"])
def post_distance():
    print(f"distance : {request.json.get('dist')}")
    return "post distance"
if __name__ =='__main':
    app.run(debug=True)