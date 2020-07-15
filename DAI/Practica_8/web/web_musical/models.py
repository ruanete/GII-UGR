from django.db import models
from django.core.serializers.json import DjangoJSONEncoder

class LazyEncoder(DjangoJSONEncoder):
    def default(self, obj):
        if isinstance(obj, YourCustomType):
            return str(obj)
        return super().default(obj)

# Create your models here.
class Grupo(models.Model):
    nombre = models.CharField(max_length=50)
    fecha_fundacion = models.DateField()
    estilo = models.CharField(max_length=50)
    longitud   = models.DecimalField (max_digits=8, decimal_places=3)
    latitud   = models.DecimalField (max_digits=8, decimal_places=3)

    def __str__(self):
        return self.nombre

class Musico(models.Model):
    nombre = models.CharField(max_length=50)
    fecha_nacimiento = models.DateField()
    instrumento_principal = models.CharField(max_length=50)
    grupos = models.ManyToManyField(Grupo, blank=True)

    def __str__(self):
        return self.nombre

class Album(models.Model):
    grupo = models.ForeignKey(Grupo, on_delete=models.PROTECT)
    titulo = models.CharField(max_length=50)
    distribuidora = models.CharField(max_length=50)
    fecha_lanzamiento = models.DateField()

    def __str__(self):
        return self.titulo
