#include "../include/quienesquien.h"
#include <sstream>
#include <iostream>
#include <iterator>
#include <math.h>
#include <algorithm>
#include <cctype>
#include <stdio.h>
#include <string.h>

QuienEsQuien::QuienEsQuien(){
	;
}

QuienEsQuien::QuienEsQuien(const QuienEsQuien &quienEsQuien){
	personajes = quienEsQuien.personajes;
	atributos = quienEsQuien.atributos;
	tablero = quienEsQuien.tablero;
	arbol = quienEsQuien.arbol;
}

QuienEsQuien& QuienEsQuien::operator= (const QuienEsQuien &quienEsQuien){
	if(&quienEsQuien != this){
		this->limpiar();
		personajes=quienEsQuien.personajes;
		atributos=quienEsQuien.atributos;
		tablero=quienEsQuien.tablero;
		arbol=quienEsQuien.arbol;
		jugada_actual=quienEsQuien.jugada_actual;
	}
	return *this;
}

QuienEsQuien::~QuienEsQuien(){
	this->limpiar();
}

void QuienEsQuien::limpiar(){
	personajes.clear();
	atributos.clear();
	tablero.clear();
	arbol.clear();
	jugada_actual.remove();
}

template <typename T>
std::ostream& operator<< (std::ostream& out, const std::vector<T>& v) {
  if ( !v.empty() ) {
    out << '[';
    std::copy (v.begin(), v.end(), std::ostream_iterator<T>(out, ", "));
    out << "\b\b]";
  }
  return out;
}

void QuienEsQuien::mostrar_estructuras_leidas(){
	cout << "personajes: "<< (this->personajes) << endl;
	cout << "atributos:  "<< (this->atributos)  << endl;
	cout << "tablero:    "<< endl;


	// Escribe la cabecera del tablero
	for(vector<string>::iterator it_atributos = this->atributos.begin();
		it_atributos != this->atributos.end();
		it_atributos++){
		cout << *it_atributos << "\t";
	}
	cout <<endl;

	int indice_personaje = 0;
	for(vector<vector<bool>>::iterator it_tablero_atributos = tablero.begin();
		it_tablero_atributos!= tablero.end();
		it_tablero_atributos++){

		string personaje = this->personajes[indice_personaje];
		int indice_atributo = 0;
		for(vector<bool>::iterator it_atributos_personaje = (*it_tablero_atributos).begin();
			it_atributos_personaje != (*it_tablero_atributos).end();
			it_atributos_personaje++){

			cout << *it_atributos_personaje<<"\t";

			indice_atributo++;
		}

		cout << personaje << endl;

		indice_personaje++;
	}

}

/**
  * @brief Devuelve una copia de la cadena original sin las subcadenas no deseadas.
  *
  * @param cadena_original Cadena de la que se eliminan las subcadenas no deseadas.
  * @param cadena_a_eliminar Subcadena que se busca y se elimina.
  *
  * @return Copia de la cadena original sin las subcadenas no deseadas.
  */
string limpiar_string(string cadena_original,string cadena_a_eliminar){
	string linea(cadena_original);

	while(linea.find_first_of(cadena_a_eliminar) != std::string::npos){
		linea.erase(linea.find_first_of(cadena_a_eliminar),cadena_a_eliminar.length());
	}

	return linea;
}

istream& operator >> (istream& is, QuienEsQuien &quienEsQuien) {
	quienEsQuien.limpiar();

  	if(is.good()){
  		string linea;
    	getline(is, linea, '\n');

    	linea = limpiar_string(linea,"\r");

    	while(linea.find('\t') != string::npos ){
    		string atributo = linea.substr(0,linea.find('\t'));
			quienEsQuien.atributos.push_back(atributo);
    		linea = linea.erase(0,linea.find('\t')+1);
    	}

		assert(linea ==  "Nombre personaje");
	}

    while( is.good() ) {
    	string linea;
    	getline(is, linea, '\n');
    	linea = limpiar_string(linea,"\r");

    	//Si la linea contiene algo extrae el personaje. Si no lo es, la ignora.
    	if(linea != ""){;
	    	vector<bool> atributos_personaje;

	    	int indice_atributo=0;
	    	while(linea.find('\t') != string::npos){
	    		string valor = linea.substr(0,linea.find('\t'));

	    		assert(valor == "0" || valor == "1");

	    		bool valor_atributo = valor == "1";

	    		atributos_personaje.push_back(valor_atributo);

	    		linea = linea.erase(0,linea.find('\t')+1);
	    		indice_atributo++;
			}

			string nombre_personaje = linea;

	    	quienEsQuien.personajes.push_back(nombre_personaje);
	    	quienEsQuien.tablero.push_back(atributos_personaje);
	    }
  	}

	return is;
}

ostream& operator << (ostream& os, const QuienEsQuien &quienEsQuien){

	//Escribimos la cabecera, que contiene los atributos y al final una columna para el nombre
	for(vector<string>::const_iterator it_atributos = quienEsQuien.atributos.begin();
		it_atributos != quienEsQuien.atributos.end();
		it_atributos++){

		os  << *it_atributos << "\t";
	}
	os << "Nombre personaje" << endl;

	//Rellenamos con ceros y unos cada l�nea y al final ponemos el nombre del personaje.
	for(int indice_personaje=0;indice_personaje<quienEsQuien.personajes.size();indice_personaje++){
		for(int indice_atributo=0;indice_atributo<quienEsQuien.atributos.size();indice_atributo++){

			os  << quienEsQuien.tablero[indice_personaje][indice_atributo] << "\t";
		}
		os  << quienEsQuien.personajes[indice_personaje] << endl;
	}

	return os;
}

/**
  * @brief Convierte un n�mero a un vector de bool que corresponde
  *        con su representaci�n en binario con un numero de digitos
  *        fijo.
  *
  * @param n N�mero a convertir en binario.
  * @param digitos N�mero de d�gitos de la representaci�n binaria.
  *
  * @return Vector de booleanos con la representaci�n en binario de @e n
  *      con el n�mero de elementos especificado por @e digitos.

  */
vector<bool> convertir_a_vector_bool(int n, int digitos) {
  vector<bool> ret;
  while(n) {
    if (n&1){
      ret.push_back(true);
    } else{
      ret.push_back(false);
    }
    n>>=1;
  }

  while(ret.size()<digitos){
  	ret.push_back(false);
  }

  reverse(ret.begin(),ret.end());
  return ret;
}

//SON OPTIMIZAR DIFERENTES PARA BUSCAR LA SOLUCIÓN QUE FUNCIONABA

/*void optimizar_arbol(bintree<Pregunta>& arbol, bintree<Pregunta>::node raiz){
	bintree<Pregunta> arbol_aux, subarbol;

	if(arbol.empty() || raiz.null() || raiz.left().null() && raiz.right().null()){
		return;
	}else if(raiz.left().null() && !raiz.right().null()){
		arbol.prune_right(raiz,subarbol);

		if(!subarbol.root().left().null() && subarbol.root().right().null()){
			arbol_aux.assign_subtree(subarbol,subarbol.root().left());
			arbol.insert_left(raiz.parent(),arbol_aux);
		}else if(!subarbol.root().right().null() && subarbol.root().left().null()){
			arbol_aux.assign_subtree(subarbol,subarbol.root().right());
			arbol.insert_left(raiz.parent(),arbol_aux);
		}else{
			arbol_aux.assign_subtree(subarbol,subarbol.root());
			arbol.insert_left(raiz.parent(),arbol_aux);
		}

		if(!raiz.null())
			optimizar_arbol(arbol, raiz);
	}else if(raiz.right().null() && !raiz.left().null()){
		arbol.prune_left(raiz,subarbol);

		if(!subarbol.root().left().null() && subarbol.root().right().null()){
			arbol_aux.assign_subtree(subarbol,subarbol.root().left());
			arbol.insert_right(raiz.parent(),arbol_aux);
		}else if(!subarbol.root().right().null() && subarbol.root().left().null()){
			arbol_aux.assign_subtree(subarbol,subarbol.root().right());
			arbol.insert_right(raiz.parent(),arbol_aux);
		}else{
			arbol_aux.assign_subtree(subarbol,subarbol.root());
			arbol.insert_right(raiz.parent(),arbol_aux);
		}

		if(!raiz.null())
			optimizar_arbol(arbol, raiz);
	}else if(!raiz.right().null() && !raiz.left().null()){
		optimizar_arbol(arbol, raiz.right());
		optimizar_arbol(arbol, raiz.left());
	}
}*/

/*void optimizar_arbol(bintree<Pregunta>& arbol, bintree<Pregunta>::node raiz){
	bintree<Pregunta> subarbol;

	if(!raiz.null()){
		if(!raiz.right().null() && raiz.left().null()){
			arbol.prune_right(raiz,subarbol);
			arbol.insert_left(raiz.parent(), subarbol);
		}

		if(!raiz.left().null() && raiz.right().null()){
			arbol.prune_left(raiz,subarbol);
			arbol.insert_right(raiz.parent(), subarbol);
		}
		optimizar_arbol(arbol,raiz.right());
		optimizar_arbol(arbol,raiz.left());
	}
}*/

void optimizar_arbol(bintree<Pregunta>& arbol, bintree<Pregunta>::node raiz){
	bintree<Pregunta> arbol_aux, subarbol;

	if(arbol.empty() || raiz.null() || raiz.left().null() && raiz.right().null()){
		return;
	}else if(raiz.left().null() && !raiz.right().null()){
		arbol.prune_right(raiz,subarbol);

		if(!subarbol.root().left().null() && subarbol.root().right().null()){
			arbol.replace_subtree(raiz,subarbol,subarbol.root().left());
		}else if(!subarbol.root().right().null() && subarbol.root().left().null()){
			arbol.replace_subtree(raiz,subarbol,subarbol.root().right());
		}else{
			arbol.replace_subtree(raiz,subarbol,subarbol.root());
		}

		if(!raiz.null())
			optimizar_arbol(arbol, raiz);
	}else if(raiz.right().null() && !raiz.left().null()){
		arbol.prune_left(raiz,subarbol);

		if(!subarbol.root().left().null() && subarbol.root().right().null()){
			arbol.replace_subtree(raiz,subarbol,subarbol.root().left());
		}else if(!subarbol.root().right().null() && subarbol.root().left().null()){
			arbol.replace_subtree(raiz,subarbol,subarbol.root().right());
		}else{
			arbol.replace_subtree(raiz,subarbol,subarbol.root());
		}

		if(!raiz.null())
			optimizar_arbol(arbol, raiz);
	}else if(!raiz.right().null() && !raiz.left().null()){
		optimizar_arbol(arbol, raiz.right());
		optimizar_arbol(arbol, raiz.left());
	}
}

bintree<Pregunta> QuienEsQuien::crear_arbol()
{
	int jaux=0;
	Pregunta p;
	Pregunta aux;
	bintree<Pregunta> arbol, arbol_aux;
	bintree<Pregunta>::node n;
	char a;

	for(int i=0;i<personajes.size();++i){
		for(int j=0;j<atributos.size()+1;++j){
			if(arbol.empty()){
				p.set_pregunta(atributos[0],personajes.size());
				bintree<Pregunta> a(p);
				arbol=a;
				n=arbol.root();
			}else if(j>0 && j<atributos.size() && tablero[i][j-1]==1){
				if (!n.left().null()){
					n = n.left();
					p = *n;
					p.set_num_personajes(p.obtener_num_personajes()+1);
					*n = p;
				}else{
					p.set_pregunta(atributos[j],1);
					arbol.insert_left(n, p);
					n = n.left();
				}
			}else if(j>0 && j<atributos.size() && tablero[i][j-1]==0){
				if (!n.right().null()){
					n = n.right();
					p = *n;
					p.set_num_personajes(p.obtener_num_personajes()+1);
					*n = p;
				}else{
					p.set_pregunta(atributos[j],1);
					arbol.insert_right(n, p);
					n = n.right();
				}
			}
			jaux=j;
		}

		aux.set_pregunta(personajes[i],1);
		if(tablero[i][atributos.size()-1]==1){
			arbol.insert_left(n, aux);
		}else{
			arbol.insert_right(n, aux);
		}

		n = arbol.root();
	}

	return arbol;
}

void QuienEsQuien::usar_arbol(bintree<Pregunta> arbol_nuevo){
	arbol = arbol_nuevo;
}

void QuienEsQuien::iniciar_juego(){
	string respuesta;
	jugada_actual = arbol.root();
	bool izq=false, dch=false;
	Pregunta p;
	p = *jugada_actual;
	set<string> personajes_levantados;
	set<string>::iterator it;

	cout << "--------COMIENZA EL JUEGO--------" << endl;

	while(!p.es_personaje()){
		cout << "Los personajes aún levantados: ";
		personajes_levantados = informacion_jugada(jugada_actual);
		for(it=personajes_levantados.begin();it!=personajes_levantados.end();++it){
			cout << *it << " ";
		}
		cout << endl;

		do{
			cout << "¿" << p.obtener_pregunta() << "?" << endl;
			cin >> respuesta;

			for(int i = 0; i < respuesta.length(); i++)
	    	respuesta[i] = tolower(respuesta[i]);

			if(strcmp(respuesta.c_str(), "si")==0)
				izq = true;
			else if(strcmp(respuesta.c_str(), "no")==0)
				dch = true;

		}while(izq==false && dch==false);

		if(izq==true){
			jugada_actual = jugada_actual.left();
		}else if(dch==true){
			jugada_actual = jugada_actual.right();
		}

		p=*jugada_actual;
		izq=false;
		dch=false;
	}
	cout << "¡Ya lo se! Tu personaje es " << p.obtener_personaje() << endl;
	cout << "--------FINALIZA EL JUEGO--------" << endl;
}

set<string> QuienEsQuien::informacion_jugada(bintree<Pregunta>::node jugada_actual){
	set<string> personajes_levantados;
	bintree<Pregunta>::level_iterator it;
	bintree<Pregunta> a;
	bintree<Pregunta>::node n;
	Pregunta p;

	a.assign_subtree(arbol,jugada_actual);

	for(it=a.begin_level();it!=a.end_level();++it){
		n=*it;
		p=*n;

		if(p.es_personaje())
			personajes_levantados.insert(p.obtener_personaje());
	}

	return personajes_levantados;
}

void escribir_esquema_arbol(ostream& ss,
					  const bintree<Pregunta>& a,
		    		  bintree<Pregunta>::node n,
					  string& pre){
	if (n.null()){
	    ss << pre << "-- x" << endl;
	} else {
	    ss << pre << "-- " << (*n) << endl;
	    if ( !n.right().null() || !n.left().null()) {// Si no es una hoja
			pre += "   |";
	    	escribir_esquema_arbol(ss,a, n.right(), pre);
	     	pre.replace(pre.size()-4, 4, "    ");
	      	escribir_esquema_arbol (ss,a, n.left(), pre);
	      	pre.erase(pre.size()-4, 4);
	    }
  	}
}

void QuienEsQuien::escribir_arbol_completo() const{
	string pre = "";
	escribir_esquema_arbol(cout,this->arbol,this->arbol.root(),pre);
}

void QuienEsQuien::eliminar_nodos_redundantes(){
	optimizar_arbol(arbol, arbol.root());
}

float QuienEsQuien::profundidad_promedio_hojas(){
	float total=0.0;
	cout << endl;
	bintree<Pregunta>::level_iterator it;
	vector<Pregunta> nodos;
	vector<Pregunta>::iterator i;
	Pregunta p;
	float contador=0, nivel=0, total_niveles=0;

	for(it=arbol.begin_level();it!=arbol.end_level();++it){
		nodos.push_back(*it);
	}

	for(int i=0;i<nodos.size();i++){
		p=nodos[i];

		if(i>(pow(2,nivel))){
			nivel++;
			//cout << "NIVEL: " << nivel << endl;
		}

		//cout << "NODO: " << p << endl;

		if(p.es_personaje()){
			//cout << "Ha encontrado personaje. Nivel: " << nivel << endl;
			total_niveles += nivel;
		}
		//cout << "-------------" << endl;
	}
 	p=*arbol.root();
	//4 el arbol no optimizado
	//2.4 el arbol ya optimizado
	//
	//16/6=2.67 el arbol ya optimizado el tablero num-per6

	return total_niveles;//p.obtener_num_personajes();
}

/**
 * @brief Genera numero enteros positivos aleatorios en el rango [min,max).
**/

int generaEntero(int min, int max){
    int tam= max -min;
    return ((rand()%tam)+min);
}

void QuienEsQuien::tablero_aleatorio(int numero_de_personajes){
	srand(0);

	this->limpiar();

	float log_2_numero_de_personajes = log(numero_de_personajes)/log(2);

	int numero_de_atributos = ceil(log_2_numero_de_personajes);

	cout << "Petici�n para generar "<< numero_de_personajes<<" personajes ";
	cout << "con "<<numero_de_atributos<< " atributos"<<endl;
	cout << "Paso 1: generar "<< pow(2,numero_de_atributos) << " personajes"<<endl;

	//Fase 1: completar el tablero con todos los personajes posibles
	//Completo el tablero y los nombres de personajes a la vez
	for(int indice_personaje=0;indice_personaje< pow(2,numero_de_atributos);indice_personaje++){
		vector<bool> atributos_personaje = convertir_a_vector_bool(indice_personaje,numero_de_atributos);
		string nombre_personaje = "Personaje_"+to_string(indice_personaje);

		this->personajes.push_back(nombre_personaje);
		this->tablero.push_back(atributos_personaje);
	}

	// Completo los nombres de los atributos.
	for(int indice_atributo=0;indice_atributo<numero_de_atributos;indice_atributo++){
		string nombre_atributo = "Atr_"+to_string(indice_atributo);
		this->atributos.push_back(nombre_atributo);
	}

	cout << "Paso 2: eliminar "<< (pow(2,numero_de_atributos)-numero_de_personajes) << " personajes"<<endl;
	//Fase 2. Borrar personajes aleatoriamente hasta que quedan solo los que hemos pedido.
	while(personajes.size()>numero_de_personajes){
		int personaje_a_eliminar = generaEntero(0,personajes.size());

		personajes.erase(personajes.begin()+personaje_a_eliminar);
		tablero.erase(tablero.begin()+personaje_a_eliminar);
	}
}
