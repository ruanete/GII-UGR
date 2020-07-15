from django.shortcuts import render, HttpResponse, redirect, get_object_or_404
from .models import Grupo, Musico, Album, LazyEncoder
from .forms import GrupoForm, MusicoForm, AlbumForm
from math import ceil
from django.core import serializers
from django.http import JsonResponse
import json
from django.core.serializers import serialize

ITEMS_POR_PAGINAS = 3

def index(request):
    return render(request,'index.html')

def grupos(request):
    grupos = Grupo.objects.all()
    total_paginas = range(1, ceil(len(grupos) / ITEMS_POR_PAGINAS) + 1)
    context = {
        'grupos': grupos,
        'total_paginas': total_paginas
    }
    return render(request,'grupos.html', context)

def grupos_pagina(request, page):
    numero_pagina = page
    tam_grupo = Grupo.objects.count()
    limite_inferior = ((numero_pagina-1) * ITEMS_POR_PAGINAS)
    grupos = Grupo.objects.all()[limite_inferior:limite_inferior+ITEMS_POR_PAGINAS]
    total_paginas = range(1, ceil(tam_grupo / ITEMS_POR_PAGINAS) + 1)
    context = {
        'grupos': grupos,
        'total_paginas': total_paginas,
        'pagina_actual': numero_pagina
    }
    return render(request,'grupos.html', context)

def musicos(request):
    musicos = Musico.objects.all()
    context = {
        'musicos': musicos,
    }
    return render(request,'musicos.html', context)

def albums(request):
    albums = Album.objects.all()
    context = {
        'albums': albums,
    }
    return render(request,'albums.html', context)

def grupos_new(request):
    if request.method == "POST":
        form = GrupoForm(request.POST)
        if form.is_valid():
            grupo = form.save(commit=False)
            grupo.save()
            return redirect('grupos')
    else:
        form = GrupoForm()
    return render(request,'grupos_forms.html', {'form': form})

def musicos_new(request):
    if request.method == "POST":
        form = MusicoForm(request.POST)
        if form.is_valid():
            musico = form.save(commit=False)
            musico.save()
            form.save_m2m()
            return redirect('musicos')
    else:
        form = MusicoForm()
    return render(request,'musicos_forms.html', {'form': form})

def albums_new(request):
    if request.method == "POST":
        form = AlbumForm(request.POST)
        if form.is_valid():
            album = form.save(commit=False)
            album.save()
            return redirect('albums')
    else:
        form = AlbumForm()
    return render(request,'albums_forms.html', {'form': form})

def grupos_edit(request, pk):
    grupo = get_object_or_404(Grupo, pk=pk)
    if request.method == "POST":
        form = GrupoForm(request.POST, instance=grupo)
        if form.is_valid():
            grupo = form.save(commit=False)
            grupo.save()
            return redirect('grupos')
    else:
        form = GrupoForm(instance=grupo)
    return render(request,'grupos_forms.html', {'form': form})

def musicos_edit(request, pk):
    musico = get_object_or_404(Musico, pk=pk)
    if request.method == "POST":
        form = MusicoForm(request.POST, instance=musico)
        if form.is_valid():
            musico = form.save(commit=False)
            musico.save()
            form.save_m2m()
            return redirect('musicos')
    else:
        form = MusicoForm(instance=musico)
    return render(request,'musicos_forms.html', {'form': form})

def albums_edit(request, pk):
    album = get_object_or_404(Album, pk=pk)
    if request.method == "POST":
        form = AlbumForm(request.POST, instance=album)
        if form.is_valid():
            album = form.save(commit=False)
            album.save()
            return redirect('albums')
    else:
        form = AlbumForm(instance=album)
    return render(request,'albums_forms.html', {'form': form})

def grupos_delete(request, pk):
    grupo = get_object_or_404(Grupo, pk=pk)
    grupo.delete()
    return redirect('grupos')

def musicos_delete(request, pk):
    musico = get_object_or_404(Musico, pk=pk)
    musico.delete()
    return redirect('musicos')

def albums_delete(request, pk):
    album = get_object_or_404(Album, pk=pk)
    album.delete()
    return redirect('albums')

def get_grupos_limit(request):
    numero_pagina = int(request.GET.get('numero_pagina'))
    tam_grupo = Grupo.objects.count()
    limite_inferior = ((numero_pagina-1) * ITEMS_POR_PAGINAS)
    grupos = Grupo.objects.all()[limite_inferior:limite_inferior+ITEMS_POR_PAGINAS]
    grupos_json = serializers.serialize('json', grupos)
    grupos_json = json.loads(grupos_json)
    return JsonResponse(grupos_json, safe=False)

def get_grupos_count(request):
    tam_grupo = Grupo.objects.count()
    return HttpResponse(tam_grupo, content_type='application/json')

def get_database_count(request):
    tam_grupo = Grupo.objects.count()
    tam_album = Album.objects.count()
    tam_musico = Musico.objects.count()
    response = { 'grupo' : tam_grupo, 'album' : tam_album, 'musico' : tam_musico}
    return JsonResponse(response, safe=False)
