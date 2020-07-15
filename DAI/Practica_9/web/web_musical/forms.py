from django import forms

from .models import Grupo, Musico, Album

class GrupoForm(forms.ModelForm):
    class Meta:
        model = Grupo
        fields = ('nombre', 'fecha_fundacion', 'estilo', 'longitud', 'latitud')

class MusicoForm(forms.ModelForm):
    class Meta:
        model = Musico
        fields = ('nombre', 'fecha_nacimiento', 'instrumento_principal', 'grupos')

class AlbumForm(forms.ModelForm):
    class Meta:
        model = Album
        fields = ('grupo', 'titulo', 'distribuidora', 'fecha_lanzamiento')
