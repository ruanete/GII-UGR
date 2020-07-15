#./flask/app.py

from flask import Flask, render_template, request, session, redirect, url_for
from pickleshare import *

app = Flask(__name__)

app.secret_key = '8rx9eRnpcvdcvRfzcwpNF4Y6ZOfTbxL1'
db = PickleShareDB('miBD')

@app.errorhandler(404)
def page_not_found(error):
    return 'ESTA PÁGINA NO EXISTE'

@app.route('/')
def index():
    return render_template("index.html")

@app.route('/works')
def works():
    return render_template("works.html")

@app.route('/contact')
def contact():
    return render_template("contact.html")

@app.route('/signup')
def signup():
    return render_template("signup.html")

@app.route('/userprofile')
def userprofile():
    return render_template("user_profile.html", db=db)

@app.route('/login', methods=['POST'])
def login():
    user=request.form['username']
    password=request.form['password']
    if user in db and password==db[user]:
        session["username"] = user
        session["urls"] = []

    return redirect(url_for("index"))

@app.route("/logout")
def logout():
    session.clear()
    return redirect(url_for("index"))

@app.route('/registerprocess', methods=['POST'])
def register_process(methods=['POST']):
    if "username" in session:
        user=request.form['username']
        password=request.form['password']
        db.pop(db[session["username"]], None)
        db[user] = password
        session.clear()
        session["username"] = user
        session["urls"] = []
    else:
        user=request.form['username']
        password=request.form['password']
        db[user] = password
        session["username"] = user
        session["urls"] = []

    return redirect(url_for("index"))

@app.after_request
def store_visted_urls(self):
    if "username" in session and request.method == "GET" and self.mimetype == "text/html":
        try:
            session["urls"].append(request.url)
            if(len(session["urls"])) > 3:
                session["urls"].pop(0)
            session.modified = True
        except:
            session["urls"] = [request.path]

    return self
