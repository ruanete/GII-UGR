
all:
	docker-compose up

build:
	docker-compose build

django-startproject:
	sudo docker-compose run web django-admin startproject sitio_web .
	sudo chown -R ${USER}:${USER} .

django-startapp:
	sudo docker-compose run web python manage.py startapp web_musical
	sudo chown -R ${USER}:${USER} .

django-migrate:
	docker-compose run web python manage.py migrate

django-makemigrations:
	docker-compose run web python manage.py makemigrations web_musical

django-createsuperuser:
	docker-compose run web python manage.py createsuperuser
