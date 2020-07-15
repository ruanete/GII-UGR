#./flask/app.py

from flask import Flask, render_template, request
from mandelbrot import pintaMandelbrot
from random import randrange, randint
import svgwrite

app = Flask(__name__)

@app.route('/')
def hello_world():
    return render_template("index.html")

@app.route('/<name>')
def my_view_func(name):
    return name

# http://localhost:8080/mandelbrot?x1=-2&y1=-1&x2=1&y2=1&ancho=230
@app.route('/mandelbrot')
def madelbrot():
    x1 = request.args.get('x1', default = 1, type = float)
    y1 = request.args.get('y1', default = 1, type = float)
    x2 = request.args.get('x2', default = 1, type = float)
    y2 = request.args.get('y2', default = 1, type = float)
    ancho = request.args.get('ancho', default = 1, type = float)
    fichero = 'static/mandelbrot' + str(randrange(10000)) + '.png'
    pintaMandelbrot(float(x1),float(y1),float(x2),float(y2),int(ancho),100,fichero)
    return render_template("mandelbrot.html", fichero=fichero)

@app.route('/dynamicimage')
def dynamicimage():
    ancho = str(randint(80, 90))
    alto = str(randint(100, 110))
    rFill = str(randint(0, 255))
    gFill = str(randint(0, 255))
    bFill = str(randint(0, 255))
    rStroke = str(randint(0, 255))
    gStroke = str(randint(0, 255))
    bStroke = str(randint(0, 255))
    fichero = 'static/dynamicImage' + str(randrange(10000)) + '.svg'
    tipoFigura = randint(0,3)

    dwg = svgwrite.Drawing(filename=fichero, size=("1200px", "800px"))

    if tipoFigura==0:
        dwg.add(dwg.rect(insert=(randint(200, 300), randint(200, 300)), size=(ancho + "px", alto + "px"),stroke_width="1",stroke="rgb(" + rStroke + "," + gStroke + "," + bStroke + ")",fill="rgb(" + rFill + "," + gFill + "," + bFill + ")"))
    elif tipoFigura==1:
        dwg.add(dwg.circle(center=(randint(200, 300), randint(200, 300)),r=(ancho + "px", alto + "px"),stroke_width="1",stroke="rgb(" + rStroke + "," + gStroke + "," + bStroke + ")",fill="rgb(" + rFill + "," + gFill + "," + bFill + ")"))
    else:
        dwg.add(dwg.ellipse(center=(randint(200, 300), randint(200, 300)),r=(ancho + "px", alto + "px"),stroke_width="1",stroke="rgb(" + rStroke + "," + gStroke + "," + bStroke + ")",fill="rgb(" + rFill + "," + gFill + "," + bFill + ")"))

    dwg.save()
    return render_template("dynamicimage.html", fichero=fichero)

@app.errorhandler(404)
def page_not_found(error):
    return 'ESTA PÁGINA NO EXISTE'
