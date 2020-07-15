#./flask/app.py

from flask import Flask, render_template, request, session, redirect, url_for
from pymongo import MongoClient
from pickleshare import *
from bson.objectid import ObjectId

app = Flask(__name__)

#mongorestore --drop -d <database-name> <dir-of-backup-files>
#db.blog_posts.insert({"PostTitle" : "Primer post de Ruanete", "PostText" : "Esto es el primer post que voy a escribir."})
app.secret_key = '8rx9eRnpcvdcvRfzcwpNF4Y6ZOfTbxL1'
db = PickleShareDB('miBD')
client = MongoClient("mongo", 27017) # Conectar al servicio (docker) "mongo" en su puerto estandar
dbMongo = client.SampleCollections        # Elegimos la base de datos de ejemplo

@app.errorhandler(404)
def page_not_found(error):
    return 'ESTA PÁGINA NO EXISTE'

@app.route('/')
def index():
    vector = {}
    for post in dbMongo.blog_posts.find():
        postValue = []
        postValue.append(post['PostTitle'])
        postValue.append(post['PostText'])
        vector[str(post['_id'])] = postValue
    return render_template("index.html", blogPosts=vector)

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

@app.route('/createpost', methods=['GET'])
def createpost():
    key = request.args.get("PostKey")
    title = request.args.get("PostTitle")
    text = request.args.get("PostText")

    if key and title and text:
        return render_template("create_post.html", PostKey=key, PostTitle=title, PostText=text)
    else:
        return render_template("create_post.html")

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

@app.route('/search', methods=['GET'])
def search():
    if request.args.get('search', None):
        search = request.args['search']
    else:
        search = ''

    vector = {}
    for post in dbMongo.blog_posts.find({'PostTitle': {'$regex': search}}):
        postValue = []
        postValue.append(post['PostTitle'])
        postValue.append(post['PostText'])
        vector[str(post['_id'])] = postValue
    return render_template("search.html", blogPosts=vector)

@app.route('/createpostprocess', methods=['POST'])
def create_post_process(methods=['POST']):
    key_post=request.form['key_post']
    title_post=request.form['title_post']
    text_post=request.form['text_post']

    if key_post:
        if not title_post or not text_post:
            return redirect(url_for("index"))
        else:
            new_post = {"$set": { "PostTitle" : title_post, "PostText" : text_post } }
            dbMongo.blog_posts.update_one({'_id': ObjectId(key_post)}, new_post)
            return redirect(url_for("index"))
    else:
        if not title_post or not text_post:
            return render_template("create_post.html")
        else:
            new_post = { "PostTitle" : title_post, "PostText" : text_post }
            dbMongo.blog_posts.insert_one(new_post)
            return redirect(url_for("index"))

@app.route('/deletepost/<post_id>')
def delete_post(post_id):
    dbMongo.blog_posts.delete_one({'_id': ObjectId(post_id)})
    return redirect(url_for("index"))

@app.route('/editpost/<post_id>')
def edit_post(post_id):
    key = ""
    title = ""
    text = ""
    for post in dbMongo.blog_posts.find({'_id': ObjectId(post_id)}):
        key = str(post['_id'])
        title = post['PostTitle']
        text = post['PostText']

    return redirect(url_for("createpost", PostKey=key, PostTitle=title, PostText=text))
