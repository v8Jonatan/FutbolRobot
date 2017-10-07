// Area.cpp: implementation of the Area class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Area.h"
#include <vector>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Area::Area()
{
	
}
Area::Area(double inicio_x,double fin_x,double inicio_y,double fin_y)
{
	this->inicio_x = inicio_x;
	this->fin_x	= fin_x;	
	this->inicio_y = inicio_y;
	this->fin_y = fin_y;
	this->enumArea = INDEFINIDO;
	subAreas.reserve(4);
	
}

Area::~Area()
{

}

bool Area::estoyDentroDelArea(double posicion_x,double posicion_y)
{
	//Si posicion_x esta comprendido entre inicio_x y fin_x , esta dentro del eje x
	//Si posicion_y esta comprendido entre inicio_y y fin_y , esta dentro del eje y
	return ( posicion_x >= inicio_x && posicion_x <= fin_x ) &&
		   ( posicion_y >= inicio_y	&& posicion_y <= fin_y );	
}

bool Area::mitadInferior(double posicion_y)
{
	return posicion_y <=((inicio_y + fin_y)/2);
}

bool Area::mitadSuperior(double posicion_y)
{
	return posicion_y >= ((inicio_y+fin_y)/2);
}


void Area::agregarAreaPuntos(double inicio_x,double fin_x,double inicio_y,double fin_y)
{
	
	Area * a = new Area(inicio_x,fin_x,inicio_y,fin_y);
	subAreas.push_back(a);

}

void Area::agregarArea(Area *area)
{
	subAreas.push_back(area);
}

Area* Area::darArea(eArea area)
{
	if(enumArea == area)
		return this;
	else
	{
		int i = 0,
			tam = subAreas.size();
		while( i<tam && !subAreas[i]->darArea(area))
		{
			i++;
		}

		if(i<tam)
			return subAreas[i]->darArea(area);
		else
			return NULL;
	}
}

Area* Area::darArea(double posicion_x,double posicion_y)
{
		int i = 0,
			tam = subAreas.size();
		while( i<tam && !subAreas[i]->estoyDentroDelArea(posicion_x,posicion_y))
		{
			i++;
		}

		if(i<tam)
			return subAreas[i];
		else
			return (estoyDentroDelArea(posicion_x,posicion_y))?this:NULL;
}

eArea Area::getTipoArea()
{
	return this->enumArea;
}

void Area::setTipoArea(eArea area)
{
	this->enumArea = area;
}

void Area::subdividir()
{
	double	incremento_x = (this->fin_x - this->inicio_x)/2;
	double	incremento_y = (this->fin_y - this->inicio_y)/2;
	
	//Esquina Sup Izquierda
	this->agregarAreaPuntos(inicio_x,incremento_x,inicio_y,incremento_y);
	//Esquina Sup Derecha
	this->agregarAreaPuntos(incremento_x,fin_x,inicio_y,incremento_y);
	//Esquina Inf Izquierda
	this->agregarAreaPuntos(inicio_x,incremento_x,incremento_y,fin_y);
	//Esquina Inf Derecha
	this->agregarAreaPuntos(incremento_x,fin_x,incremento_y,fin_y);
}

void Area::dividir()
{	
	double	incremento_x = (this->fin_x - this->inicio_x)/2;
	this->agregarAreaPuntos(inicio_x,incremento_x,inicio_y,fin_y);
	this->agregarAreaPuntos(incremento_x,fin_x,inicio_y,fin_y);
}

vector<Area*> Area::darSubAreas()
{
	return subAreas;
}

void Area::update(Environment *env)
{
	//VERIFICO SI MIS COMPANEROS ESTAN EN EL AREA
	companeros.clear();
	
	int i = 0,
		tam = 5;

	for(i = 0; i<tam; i++)
	{
		if(this->darArea(env->home[i].pos.x,env->home[i].pos.y)==this)
		{
				this->companeros.push_back( &env->home[i] );
		}
	}
	//VERIFICO SI MIS OPONENTES ESTAN EN EL AREA
	oponentes.clear();

	for( i = 0; i<tam; i++)
	{
		if(this->darArea(env->opponent[i].pos.x,env->opponent[i].pos.y)==this)
		{
				this->oponentes.push_back( &env->opponent[i] );
		}
	}
	//TODO MODIFICAR , AGREGAR 2 FUNCIONES 
}
vector<Robot*> Area::darCompaneros(){
	return this->companeros;
}

vector<OpponentRobot*> Area::darOponente(){
	return this->oponentes;
}
