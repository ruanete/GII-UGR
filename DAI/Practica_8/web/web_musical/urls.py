# web_musical/urls.py

from django.conf.urls import url
from django.urls import path

from . import views

urlpatterns = [
  url(r'^$', views.index, name='index'),
  path('api/database/count/', views.get_database_count, name='get_database_count'),
  path('api/grupos/', views.get_grupos_limit, name='get_grupos_limit'),
  path('api/grupos/count/', views.get_grupos_count, name='get_grupos_count'),
  path('grupos/<int:page>/', views.grupos_pagina, name='grupos_pagina'),
  path('grupos/delete/<int:pk>/', views.grupos_delete, name='grupos_delete'),
  path('grupos/edit/<int:pk>/', views.grupos_edit, name='grupos_edit'),
  url('grupos/new/', views.grupos_new, name='grupos_new'),
  url('grupos/', views.grupos, name='grupos'),
  path('musicos/delete/<int:pk>/', views.musicos_delete, name='musicos_delete'),
  path('musicos/edit/<int:pk>/', views.musicos_edit, name='musicos_edit'),
  url('musicos/new/', views.musicos_new, name='musicos_new'),
  url('musicos/', views.musicos, name='musicos'),
  path('albums/delete/<int:pk>/', views.albums_delete, name='albums_delete'),
  path('albums/edit/<int:pk>/', views.albums_edit, name='albums_edit'),
  url('albums/new/', views.albums_new, name='albums_new'),
  url('albums/', views.albums, name='albums')
]