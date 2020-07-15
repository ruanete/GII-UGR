from django.shortcuts import render, HttpResponse, redirect, get_object_or_404
from .models import Grupo, Musico, Album
from .forms import GrupoForm, MusicoForm, AlbumForm

# Create your views here.

def index(request):
    return render(request,'index.html')

def grupos(request):
    grupos = Grupo.objects.all()
    context = {
        'grupos': grupos,
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
