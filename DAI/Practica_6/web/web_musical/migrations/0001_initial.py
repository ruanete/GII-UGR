# Generated by Django 2.2.7 on 2019-11-17 14:31

from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    initial = True

    dependencies = [
    ]

    operations = [
        migrations.CreateModel(
            name='Grupo',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('nombre', models.CharField(max_length=50)),
                ('fecha_fundacion', models.DateField()),
                ('estilo', models.CharField(max_length=50)),
            ],
        ),
        migrations.CreateModel(
            name='Musico',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('nombre', models.CharField(max_length=50)),
                ('fecha_nacimiento', models.DateField()),
                ('instrumento_principal', models.CharField(max_length=50)),
                ('grupos', models.ManyToManyField(blank=True, to='web_musical.Grupo')),
            ],
        ),
        migrations.CreateModel(
            name='Album',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('titulo', models.CharField(max_length=50)),
                ('distribuidora', models.CharField(max_length=50)),
                ('fecha_lanzamiento', models.DateField()),
                ('grupo', models.ForeignKey(on_delete=django.db.models.deletion.PROTECT, to='web_musical.Grupo')),
            ],
        ),
    ]
