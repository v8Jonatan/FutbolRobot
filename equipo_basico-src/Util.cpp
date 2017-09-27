// Util.cpp

#include "stdafx.h"
#include "Util.h"
#include <math.h>
#include "Const.h"
//-----------------------------------------------------------------------------------------------------------------------
// Devuelve el ángulo a girar por un jugador para queda mirando a la posición xf yf.

double CalcularAnguloAGirar2(double x0,double y0, double xf, double yf, double rr) 
{

	double dAnguloEntre2Puntos = CalcularAngulo2Pts(x0, y0, xf, yf);

	
	double dAnguloAGirar = dAnguloEntre2Puntos - rr;

	if (dAnguloAGirar > 180.0)
		dAnguloAGirar = -360.0 + dAnguloAGirar;

	if (dAnguloAGirar < -180.0)
		dAnguloAGirar = 360.0 + dAnguloAGirar;

	
	return dAnguloAGirar;

}

//-------------------------------------------------------------------------------------------
// Calcula el ángulo que hay entre dos puntos.
double CalcularAngulo2Pts2(double x0, double y0, double xf, double yf) 
{

	double dAngulo;
	
	double x = xf - x0;
	double y = yf - y0;

	// Ángulo igual a 0.
	if (((x > 0.0) && (y == 0.0)) || ((x == 0.0) && (y == 0.0))) 
		dAngulo = 0.0;
	
	// Ángulo igual a 90.
	else if ((x == 0.0) && (y > 0.0)) 
		dAngulo = 90.0;
		
	// Ángulo igual a 180.
	else if ((x < 0.0) && (y == 0.0)) 
		dAngulo = 180.0;
		
	// Ángulo igual a 270.
	else if ((x == 0.0) && (y < 0.0)) 
		dAngulo = 270.0;
		
	// Otro valor del ángulo.
	else {
		double dAngRad = atan(fabs(y) / fabs(x));
		double dAngGrados = ((dAngRad * 180.0) / PI);
		
		if ((x < 0.0) && (y > 0.0)) 
			dAngulo = 180.0 - dAngGrados;
		
		else if ((x < 0.0) && (y < 0.0)) 
			dAngulo = 180.0 + dAngGrados;

		else if ((x > 0.0) && (y < 0.0))
			dAngulo = 360.0 - dAngGrados;
		
		else
			dAngulo = dAngGrados;
	}

	return dAngulo;
}

//-------------------------------------------------------------------------------------------
// Deveulve el ángulo en grados pasado como parámetro en radianes.
double DegtwoRad(double dAngGrados)
{
	return dAngGrados * (PI / 180.0);
}

//-------------------------------------------------------------------------------------------
// Deveulve el ángulo en radianes pasado como parámetro en grados.
double RadtwoDeg(double dAngRad)
{
	return dAngRad * (180.0 / PI);
}


//-------------------------------------------------------------------------------------------
// Calcula la distancia entre dos puntos.
double Distancia2(double x0,double y0,double xf,double yf) 
{
	double dist_x = xf - x0;;
	double dist_y = yf - y0;

	return sqrt(((dist_x) * (dist_x)) + ((dist_y) * (dist_y)));	
}

//-------------------------------------------------------------------------------------------
// Devuelve el menor de los dos valores pasados como parámetros.
double Menor(double a, double b)
{
	return a < b ? a : b;
}

//-------------------------------------------------------------------------------------------
// Devuelve el mayor de los dos valores pasados como parámetros.
double Mayor(double a, double b)
{
	return a > b ? a : b;
}

//-------------------------------------------------------------------------------------------
// Devuelve 0 si el número pasado como parámetro es 0, -1 si es negativo, y 1 si es positivo.
int Signo(double n)
{
	return (int)(n == 0 ? 0 : (n / fabs(n)));
}

int ZonaReal(double x, double y){

	if ( x > ARCO_LINEA_DE_ATRAS_IZQUIERDA && x < LIMITE_IZQUIERDO_CAMPO 
		&& y > ARCO_LINEA_INFERIOR && y < ARCO_LINEA_SUPERIOR)
		return 1;
	else if ( x < ARCO_LINEA_DE_ATRAS_DERECHA && x > LIMITE_DERECHO_CAMPO 
		&& y > ARCO_LINEA_INFERIOR && y < ARCO_LINEA_SUPERIOR)
		return 10;
	else if ( x > LIMITE_IZQUIERDO_CAMPO && x <  AREA_CHICA_LINEA_IZQUIERDA 
	&& y > AREA_CHICA_LINEA_INFERIOR && y < AREA_CHICA_LINEA_SUPERIOR )
		return 2;
	else if ( x < LIMITE_DERECHO_CAMPO && x >  AREA_CHICA_LINEA_DERECHA
	&& y > AREA_CHICA_LINEA_INFERIOR && y < AREA_CHICA_LINEA_SUPERIOR )
		return 9;
	else if ( x > AREA_CHICA_LINEA_IZQUIERDA && x <  AREA_GRANDE_LINEA_IZQUIERDA 
		&& y > AREA_GRANDE_LINEA_INFERIOR && y < AREA_GRANDE_LINEA_SUPERIOR )
		return 3;
	else if ( x < AREA_CHICA_LINEA_DERECHA && x >  AREA_GRANDE_LINEA_DERECHA
	&& y > AREA_GRANDE_LINEA_INFERIOR && y < AREA_GRANDE_LINEA_SUPERIOR )
		return 8;
	else if ( x > AREA_GRANDE_LINEA_IZQUIERDA && x <  MITAD_DE_CANCHA_IZQUIERDA_EN_X 
		&& y > LIMITE_INFERIOR_CAMPO && y < LIMITE_SUPERIOR_CAMPO )
		return 4;
	else if ( x < AREA_GRANDE_LINEA_DERECHA && x >  MITAD_DE_CANCHA_DERECHA_EN_X
	&& y > LIMITE_INFERIOR_CAMPO && y < LIMITE_SUPERIOR_CAMPO )
		return 7;
	else if ( x > MITAD_DE_CANCHA_IZQUIERDA_EN_X && x <  MITAD_DE_CANCHA_EN_X 
		&& y > LIMITE_INFERIOR_CAMPO && y < LIMITE_SUPERIOR_CAMPO )
		return 5;
	else if ( x < MITAD_DE_CANCHA_DERECHA_EN_X && x >  MITAD_DE_CANCHA_EN_X
	&& y > LIMITE_INFERIOR_CAMPO && y < LIMITE_SUPERIOR_CAMPO )
		return 6;
}

//-------------------------------------------------------------------------------------------
// Devuelve el número de zona en donde se encuentra el punto pasado como parámetro.
int Zona (double x, double y) 
{	
	if ((x > LIMITE_IZQUIERDO_CAMPO) && (x < AREA_CHICA_LINEA_IZQUIERDA) && 
		(y > LIMITE_INFERIOR_CAMPO) && (y < AREA_GRANDE_LINEA_INFERIOR))
			return 1;
	else if ((x > AREA_CHICA_LINEA_IZQUIERDA) && (x < AREA_GRANDE_LINEA_IZQUIERDA) && 
		(y > LIMITE_INFERIOR_CAMPO) && (y < AREA_GRANDE_LINEA_INFERIOR))
			return 2;
	else if ((x > AREA_GRANDE_LINEA_IZQUIERDA) && (x < MITAD_DE_CANCHA_EN_X) &&
		(y > LIMITE_INFERIOR_CAMPO) && (y < AREA_GRANDE_LINEA_INFERIOR))
			return 3;
	else if ((x > MITAD_DE_CANCHA_EN_X) && (x < AREA_GRANDE_LINEA_DERECHA) && 
		(y > LIMITE_INFERIOR_CAMPO) && (y < AREA_GRANDE_LINEA_INFERIOR))
			return 4;
	else if ((x > AREA_GRANDE_LINEA_DERECHA) && (x < AREA_CHICA_LINEA_DERECHA) && 
		(y > LIMITE_INFERIOR_CAMPO) && (y < AREA_GRANDE_LINEA_INFERIOR))
			return 5;
	else if ((x > AREA_CHICA_LINEA_DERECHA) && (x < LIMITE_DERECHO_CAMPO) && 
		(y > LIMITE_INFERIOR_CAMPO) && (y < AREA_GRANDE_LINEA_INFERIOR))
			return 6;
	else if ((x > LIMITE_IZQUIERDO_CAMPO) && (x < AREA_CHICA_LINEA_IZQUIERDA) &&
		(y > AREA_GRANDE_LINEA_INFERIOR) && (y < AREA_CHICA_LINEA_INFERIOR))
			return 7;
	else if ((x > AREA_CHICA_LINEA_IZQUIERDA) && (x < AREA_GRANDE_LINEA_IZQUIERDA) && 
		(y > AREA_GRANDE_LINEA_INFERIOR) && (y < AREA_CHICA_LINEA_INFERIOR))
			return 8;
	else if ((x > AREA_GRANDE_LINEA_IZQUIERDA) && (x < MITAD_DE_CANCHA_EN_X) && 
		(y > AREA_GRANDE_LINEA_INFERIOR) && (y < AREA_CHICA_LINEA_INFERIOR))
			return 9;
	else if ((x > MITAD_DE_CANCHA_EN_X) && (x < AREA_GRANDE_LINEA_DERECHA) && 
		(y > AREA_GRANDE_LINEA_INFERIOR) && (y < AREA_CHICA_LINEA_INFERIOR))
			return 10;
	else if ((x > AREA_GRANDE_LINEA_DERECHA) && (x < AREA_CHICA_LINEA_DERECHA) && 
		(y > AREA_GRANDE_LINEA_INFERIOR) && (y < AREA_CHICA_LINEA_INFERIOR))
			return 11;
	else if ((x > AREA_CHICA_LINEA_DERECHA) && (x < LIMITE_DERECHO_CAMPO) && 
		(y > AREA_GRANDE_LINEA_INFERIOR) && (y < AREA_CHICA_LINEA_INFERIOR))
			return 12;
	else if ((x > LIMITE_IZQUIERDO_CAMPO) && (x < AREA_CHICA_LINEA_IZQUIERDA) && 
		(y > AREA_CHICA_LINEA_INFERIOR) && (y < ARCO_LINEA_INFERIOR))
			return 13;
	else if ((x > AREA_CHICA_LINEA_IZQUIERDA) && (x < AREA_GRANDE_LINEA_IZQUIERDA) && 
		(y > AREA_CHICA_LINEA_INFERIOR) && (y < ARCO_LINEA_INFERIOR))
			return 14;
	else if ((x > AREA_GRANDE_LINEA_IZQUIERDA) && (x < MITAD_DE_CANCHA_EN_X) && 
		(y > AREA_CHICA_LINEA_INFERIOR) && (y < ARCO_LINEA_INFERIOR))
			return 15;
	else if ((x > MITAD_DE_CANCHA_EN_X) && (x < AREA_GRANDE_LINEA_DERECHA) && 
		(y > AREA_CHICA_LINEA_INFERIOR) && (y < ARCO_LINEA_INFERIOR))
			return 16;
	else if ((x > AREA_GRANDE_LINEA_DERECHA) && (x < AREA_CHICA_LINEA_DERECHA) && 
		(y > AREA_CHICA_LINEA_INFERIOR) && (y < ARCO_LINEA_INFERIOR))
			return 17;
	else if ((x > AREA_CHICA_LINEA_DERECHA) && (x < LIMITE_DERECHO_CAMPO) && 
		(y > AREA_CHICA_LINEA_INFERIOR) && (y < ARCO_LINEA_INFERIOR))
			return 18;
	else if ((x > ARCO_LINEA_DE_ATRAS_IZQUIERDA) && (x < LIMITE_IZQUIERDO_CAMPO) &&
		(y > ARCO_LINEA_INFERIOR) && (y < MITAD_DE_CANCHA_EN_Y))
			return 19;
	else if ((x > LIMITE_IZQUIERDO_CAMPO) && (x < AREA_CHICA_LINEA_IZQUIERDA) && 
		(y > ARCO_LINEA_INFERIOR) && (y < MITAD_DE_CANCHA_EN_Y))
			return 20;
	else if ((x > AREA_CHICA_LINEA_IZQUIERDA) && (x < AREA_GRANDE_LINEA_IZQUIERDA) && 
		(y > ARCO_LINEA_INFERIOR) && (y < MITAD_DE_CANCHA_EN_Y))
			return 21;
	else if ((x > AREA_GRANDE_LINEA_IZQUIERDA) && (x < MITAD_DE_CANCHA_EN_X) && 
		(y > ARCO_LINEA_INFERIOR) && (y < MITAD_DE_CANCHA_EN_Y))
			return 22;
	else if ((x > MITAD_DE_CANCHA_EN_X) && (x < AREA_GRANDE_LINEA_DERECHA) && 
		(y > ARCO_LINEA_INFERIOR) && (y < MITAD_DE_CANCHA_EN_Y))
			return 23;
	else if ((x > AREA_GRANDE_LINEA_DERECHA) && (x < AREA_CHICA_LINEA_DERECHA) && 
		(y > ARCO_LINEA_INFERIOR) && (y < MITAD_DE_CANCHA_EN_Y))
			return 24;
	else if ((x > AREA_CHICA_LINEA_DERECHA) && (x < LIMITE_DERECHO_CAMPO) && 
		(y > ARCO_LINEA_INFERIOR) && (y < MITAD_DE_CANCHA_EN_Y))
			return 25;
	else if ((x > LIMITE_DERECHO_CAMPO) && (x < ARCO_LINEA_DE_ATRAS_DERECHA) && 
		(y > ARCO_LINEA_INFERIOR) && (y < MITAD_DE_CANCHA_EN_Y))
			return 26;
	else if ((x > ARCO_LINEA_DE_ATRAS_IZQUIERDA) && (x < LIMITE_IZQUIERDO_CAMPO) && 
		(y > MITAD_DE_CANCHA_EN_Y) && (y < ARCO_LINEA_SUPERIOR))
			return 27;
	else if ((x > LIMITE_IZQUIERDO_CAMPO) && (x < AREA_CHICA_LINEA_IZQUIERDA) && 
		(y > MITAD_DE_CANCHA_EN_Y) && (y < ARCO_LINEA_SUPERIOR))
			return 28;
	else if ((x > AREA_CHICA_LINEA_IZQUIERDA) && (x < AREA_GRANDE_LINEA_IZQUIERDA) && 
		(y > MITAD_DE_CANCHA_EN_Y) && (y < ARCO_LINEA_SUPERIOR))
			return 29;
	else if ((x > AREA_GRANDE_LINEA_IZQUIERDA) && (x < MITAD_DE_CANCHA_EN_X) && 
		(y > MITAD_DE_CANCHA_EN_Y) && (y < ARCO_LINEA_SUPERIOR))
			return 30;
	else if ((x > MITAD_DE_CANCHA_EN_X) && (x < AREA_GRANDE_LINEA_DERECHA) &&
		(y > MITAD_DE_CANCHA_EN_Y) && (y < ARCO_LINEA_SUPERIOR))
			return 31;
	else if ((x > AREA_GRANDE_LINEA_DERECHA) && (x < AREA_CHICA_LINEA_DERECHA) && 
		(y > MITAD_DE_CANCHA_EN_Y) && (y < ARCO_LINEA_SUPERIOR))
			return 32;
	else if ((x > AREA_CHICA_LINEA_DERECHA) && (x < LIMITE_DERECHO_CAMPO) &&
		(y > MITAD_DE_CANCHA_EN_Y) && (y < ARCO_LINEA_SUPERIOR))
			return 33;
	else if ((x > LIMITE_DERECHO_CAMPO) && (x < ARCO_LINEA_DE_ATRAS_DERECHA) && 
		(y > MITAD_DE_CANCHA_EN_Y) && (y < ARCO_LINEA_SUPERIOR))
			return 34;
	else if ((x > LIMITE_IZQUIERDO_CAMPO) && (x < AREA_CHICA_LINEA_IZQUIERDA) && 
		(y > ARCO_LINEA_SUPERIOR) && (y < AREA_CHICA_LINEA_SUPERIOR))
			return 35;
	else if ((x > AREA_CHICA_LINEA_IZQUIERDA) && (x < AREA_GRANDE_LINEA_IZQUIERDA) && 
		(y > ARCO_LINEA_SUPERIOR) && (y < AREA_CHICA_LINEA_SUPERIOR))
			return 36;
	else if ((x > AREA_GRANDE_LINEA_IZQUIERDA) && (x < MITAD_DE_CANCHA_EN_X) && 
		(y > ARCO_LINEA_SUPERIOR) && (y < AREA_CHICA_LINEA_SUPERIOR))
			return 37;
	else if ((x > MITAD_DE_CANCHA_EN_X) && (x < AREA_GRANDE_LINEA_DERECHA) && 
		(y > ARCO_LINEA_SUPERIOR) && (y < AREA_CHICA_LINEA_SUPERIOR))
			return 38;
	else if ((x > AREA_GRANDE_LINEA_DERECHA) && (x < AREA_CHICA_LINEA_DERECHA) && 
		(y > ARCO_LINEA_SUPERIOR) && (y < AREA_CHICA_LINEA_SUPERIOR))
			return 39;
	else if ((x > AREA_CHICA_LINEA_DERECHA) && (x < LIMITE_DERECHO_CAMPO) && 
		(y > ARCO_LINEA_SUPERIOR) && (y < AREA_CHICA_LINEA_SUPERIOR))
			return 40;
	else if ((x > LIMITE_IZQUIERDO_CAMPO) && (x < AREA_CHICA_LINEA_IZQUIERDA) && 
		(y > AREA_CHICA_LINEA_SUPERIOR) && (y < AREA_GRANDE_LINEA_SUPERIOR))
			return 41;
	else if ((x > AREA_CHICA_LINEA_IZQUIERDA) && (x < AREA_GRANDE_LINEA_IZQUIERDA) && 
		(y > AREA_CHICA_LINEA_SUPERIOR) && (y < AREA_GRANDE_LINEA_SUPERIOR))
			return 42;
	else if ((x > AREA_GRANDE_LINEA_IZQUIERDA) && (x < MITAD_DE_CANCHA_EN_X) && 
		(y > AREA_CHICA_LINEA_SUPERIOR) && (y < AREA_GRANDE_LINEA_SUPERIOR))
			return 43;
	else if ((x > MITAD_DE_CANCHA_EN_X) && (x < AREA_GRANDE_LINEA_DERECHA) && 
		(y > AREA_CHICA_LINEA_SUPERIOR) && (y < AREA_GRANDE_LINEA_SUPERIOR))
			return 44;
	else if ((x > AREA_GRANDE_LINEA_DERECHA) && (x < AREA_CHICA_LINEA_DERECHA) &&
		(y > AREA_CHICA_LINEA_SUPERIOR) && (y < AREA_GRANDE_LINEA_SUPERIOR))
			return 45;
	else if ((x > AREA_CHICA_LINEA_DERECHA) && (x < LIMITE_DERECHO_CAMPO) && 
		(y > AREA_CHICA_LINEA_SUPERIOR) && (y < AREA_GRANDE_LINEA_SUPERIOR))
			return 46;
	else if ((x > LIMITE_IZQUIERDO_CAMPO) && (x < AREA_CHICA_LINEA_IZQUIERDA) && 
		(y > AREA_GRANDE_LINEA_SUPERIOR) && (y < LIMITE_SUPERIOR_CAMPO))
			return 47;
	else if ((x > AREA_CHICA_LINEA_IZQUIERDA) && (x < AREA_GRANDE_LINEA_IZQUIERDA) && 
		(y > AREA_GRANDE_LINEA_SUPERIOR) && (y < LIMITE_SUPERIOR_CAMPO))
			return 48;
	else if ((x > AREA_GRANDE_LINEA_IZQUIERDA) && (x < MITAD_DE_CANCHA_EN_X) &&
		(y > AREA_GRANDE_LINEA_SUPERIOR) && (y < LIMITE_SUPERIOR_CAMPO))
			return 49;
	else if ((x > MITAD_DE_CANCHA_EN_X) && (x < AREA_GRANDE_LINEA_DERECHA) && 
		(y > AREA_GRANDE_LINEA_SUPERIOR) && (y < LIMITE_SUPERIOR_CAMPO))
			return 50;
	else if ((x > AREA_GRANDE_LINEA_DERECHA) && (x < AREA_CHICA_LINEA_DERECHA) && 
		(y > AREA_GRANDE_LINEA_SUPERIOR) && (y < LIMITE_SUPERIOR_CAMPO))
			return 51;
	else if ((x > AREA_CHICA_LINEA_DERECHA) && (x < LIMITE_DERECHO_CAMPO) && 
		(y > AREA_GRANDE_LINEA_SUPERIOR) && (y < LIMITE_SUPERIOR_CAMPO))
			return 52;
	else
		return 0;
}

double CalcularAngulo2Pts(double xo, double yo, double xf, double yf)
{
	double dx, dy, alfa, constAngle = 0;

	dx = xf - xo;
	dy = yf - yo;

	if (dx == 0 && dy == 0) {
		alfa = 0;
	}
	else if (dx == 0) {
		if (dy > 0)
			alfa = 90;
		else
			alfa = 270;
	}
	else if (dy == 0) {
		if (dx > 0)
			alfa = 0;
		else
			alfa = 180;
	}
	else {
		alfa = atan(fabs(dy) / fabs(dx));

		alfa = radToDeg(alfa);
		
		if ((dx > 0) && (dy > 0))
			alfa = alfa;
		else if ((dx < 0) && (dy > 0))
			alfa = 180 - alfa;
		else if ((dx < 0) && (dy < 0))
			alfa = 180 + alfa;
		else
			alfa = 360 - alfa;
	}

	return alfa;
}


double NormalizarAngulo(double angulo)
{
	while (angulo >  360) angulo -= 360;
	while (angulo < -360) angulo += 360;
	if (angulo < 0) angulo += 360;

	return angulo;
}


double CalcularAnguloAGirar(double x0, double y0, double xf, double yf, double rr)
{
	
		double Ang2Puntos = CalcularAngulo2Pts(x0, y0, xf, yf);
		double AngAGirar = Ang2Puntos - NormalizarAngulo(rr);
	
		return degToRad(AngAGirar);
}



int sgn(double x) 
{
	return x == 0.0 ? 0 : (x < 0.0 ? -1 : 1);
}
////////////////////////////////////////////////////////////////////////////////
//Transformar sexagesimal a radianes.
////////////////////////////////////////////////////////////////////////////////
double degToRad(const double angle)
{
	return angle * (PI/180.0);
}


////////////////////////////////////////////////////////////////////////////////
//Transformar radianes a sexagesimal.
////////////////////////////////////////////////////////////////////////////////
double radToDeg(const double rad)
{
	return rad * (180.0/PI);
}


////////////////////////////////////////////////////////////////////////////////
//Retorna el ángulo que existe entre dos puntos.
////////////////////////////////////////////////////////////////////////////////
double angleToPoint(double xo, double yo, double xf, double yf)
{
	double dx, dy, r, alfa, constAngle = 0;

	dx = xf - xo;
	dy = yf - yo;

	if (dx == 0 && dy == 0)
		alfa = 0;
	else if (dx == 0) {
		if (dy > 0)
			alfa = 90;
		else
			alfa = -90;
	}
	else if (dy == 0) {
		if (dx > 0)
			alfa = 0;
		else
			alfa = 180;
	}
	else {
		if (dx < 0)
			constAngle = 180;
		else if (dy < 0)
			constAngle = 360;

		r = atan(dy / dx);
		alfa = radToDeg(r);
	}

	return alfa + constAngle;
}


//////////////////////////////////////////////////////////////////////////////////////////
int CercaDe(double dXrobot, double dYrobot, double x, double y, double radio)
{
	// Dado un punto (x,y) y un radio (inch) devuelve 1 si el robot se encuentra dentro
	// de ese circulo.
	
	double dx = x - dXrobot;
	double dy = y - dYrobot;
	double r = sqrt((dx * dx) + (dy * dy));
	int rta;

	if (r > radio)
	{
		rta = 0;
	}
	else
	{
		rta = 1;
	}

	return rta;
}




double Distancia_2Pts(double X1 ,double X2,double Y1, double Y2){
	double Op, Ady;

	Op = fabs(Y1 - Y2);
	Ady = fabs(X1 - X2);

	double Distancia = (sqrt((Ady * Ady) + (Op * Op)));	

	return Distancia;		
}


////////////////////////////////////////////////////////////////

double Angulo_2Pts(double Distancia, double Op){
	fabs(Op);
	double Angulo = asin(fabs(Op / Distancia));
	
	return Angulo;
}

///////////////////////////////////////////////////////////////

double Radianes_Grados(double Angulo_R){
	double grados = fabs (Angulo_R * 180 / PI);
	
	return grados;
}

///////////////////////////////////////////////////////////////////////////////////////////
// Calcula el angulo de giro para la navegacion de Emiliano
//////////////////////////////////////////////////////////////////////////////////////////

double Angulo_girar(double Angulo, double Op, double Ady, double rotation){


	if ((Ady > 0) && (Op > 0)){
		Angulo = Angulo;
	}
	else if ((Ady > 0) && (Op < 0)){
		Angulo = 0 - Angulo;
	}
	else if ((Ady < 0) && (Op > 0)){
		Angulo = 180 - Angulo;
	}
	else if ((Ady < 0) && (Op < 0)){
		Angulo = -180 + Angulo;
	}
	Angulo = Angulo - rotation;
	
	if(Angulo > 180)
	{
	    Angulo = Angulo - 360; 
	}

	if(Angulo < -180)
	{
		Angulo = 360 + Angulo;
	}
	

	return Angulo;
}


double CalcularAngulo2Pts180(double xo, double yo, double xf, double yf)
{
	double dx, dy, alfa, constAngle = 0;

	dx = xf - xo;
	dy = yf - yo;

	if (dx == 0 && dy == 0) {
		alfa = 0;
	}
	else if (dx == 0) {
		if (dy > 0)
			alfa = 90;
		else
			alfa = -90;
	}
	else if (dy == 0) {
		if (dx > 0)
			alfa = 0;
		else
			alfa = 180;
	}
	else {
		alfa = atan(fabs(dy) / fabs(dx));

		alfa = radToDeg(alfa);
		
		if ((dx > 0) && (dy > 0))
			alfa = alfa;
		else if ((dx < 0) && (dy > 0))
			alfa = 180 - alfa;
		else if ((dx < 0) && (dy < 0))
			alfa = -180 + alfa;
		else
			alfa = (-1) * alfa;
	}

	return alfa;
}


double CalcularAnguloAGirar180(double x0, double y0, double xf, double yf, double rr)
{
	
		double Ang2Puntos = CalcularAngulo2Pts180(x0, y0, xf, yf);
		double AngAGirar = Ang2Puntos - rr;

		if (AngAGirar < -180)
			AngAGirar = 360 + AngAGirar;

		if (AngAGirar > 180)
			AngAGirar = AngAGirar - 360;
	
		return AngAGirar;
}


// _______ Ultra Prediccion en Y _________

double PosPrePelY(double PosX, Environment *env){

	double DistX = env->currentBall.pos.x - env->lastBall.pos.x;	
	double DistY = env->currentBall.pos.y - env->lastBall.pos.y;
	double Pendiente = DistY / DistX;
	double Ordenada = env->currentBall.pos.y - (Pendiente * env->currentBall.pos.x);
	double PosY = (Pendiente * PosX) + Ordenada;	
	double Vel_Pel = Vel_Ball(env);
	
	if ( (Vel_Pel < 18) || ((env->currentBall.pos.y < PosY) && (DistY < 0)) || ((env->currentBall.pos.y > PosY) && (DistY > 0)) ){
		PosY = env->currentBall.pos.y;
	}

	return PosY;
}

// _______ Ultra Prediccion en X _________

double PosPrePelX(double PosY, Environment *env){

	double DistX = env->currentBall.pos.x - env->lastBall.pos.x;	
	double DistY = env->currentBall.pos.y - env->lastBall.pos.y;
	double Pendiente = DistY / DistX;
	double Ordenada = env->currentBall.pos.y - (Pendiente * env->currentBall.pos.x);
	double PosX = (PosY - Ordenada) / Pendiente ;	
	double Vel_Pel = Vel_Ball(env);
	
	if ((Vel_Pel < 18) || ((env->currentBall.pos.y < PosY) && (DistY < 0)) || ((env->currentBall.pos.y > PosY) && (DistY > 0)) ){
		PosX = env->currentBall.pos.x;
	}	
		
	return PosX;
}

// Velocidad de la pelota
double Vel_Ball(Environment *env){
	double Y2 = env->currentBall.pos.y;
	double X2 = env->currentBall.pos.x;
	double X1 = env->lastBall.pos.x;
	double Y1 = env->lastBall.pos.y;
	double Distancia = Distancia_2Pts(X1 ,X2, Y1, Y2);
	double Vel_Pel = fabs(Distancia / 0.01);
	return Vel_Pel;
}


int Velocidad(double Distancia){
	int Velocidad;
	if (Distancia > 13) {
			Velocidad = 100; // 100;
	}
	else if (Distancia > 10) {
		Velocidad = 80; // 80;
	}
	else if (Distancia > 7) {
		Velocidad = 70; // 70;
	}
	else if (Distancia > 6) {
		Velocidad = 50; // 50
	}		
	else if (Distancia > 1) {
		Velocidad = 30; //30;
	}/*
	else if (Distancia > 1) {
		Velocidad = 8;
	}
	else if (Distancia > 0.5) {
		Velocidad = 4;
	}*/
	else  {
		Velocidad = 5; // 0
	}
	return Velocidad;
}

void Velocity ( Robot *robot, int vl, int vr )
{
	robot->velocityLeft = vl;
	robot->velocityRight = vr;
}

// robot soccer system p329
void Angle ( Robot *robot, int desired_angle)
{
	int theta_e, vl, vr;
	theta_e = desired_angle - (int)robot->rotation;
	
	while (theta_e > 180) theta_e -= 360;
	while (theta_e < -180) theta_e += 360;

	if (theta_e < -90) theta_e += 180;
	
	else if (theta_e > 90) theta_e -= 180;

	if (abs(theta_e) > 50) 
	{
		vl = (int)(-9./90.0 * (double) theta_e);
		vr = (int)(9./90.0 * (double)theta_e);
	}
	else if (abs(theta_e) > 20)
	{
		vl = (int)(-11.0/90.0 * (double)theta_e);
		vr = (int)(11.0/90.0 * (double)theta_e);
	}
	Velocity (robot, vl, vr);
}

void Position( Robot *robot, double x, double y )
{
	int desired_angle = 0, theta_e = 0, d_angle = 0, vl, vr, vc = 70;

	double dx, dy, d_e, Ka = 10.0 / 90.0;
	dx = x - robot->pos.x;
	dy = y - robot->pos.y;

	d_e = sqrt(dx * dx + dy * dy);
	if (dx == 0 && dy == 0)
		desired_angle = 90;
	else
		desired_angle = (int)(180. / PI * atan2((double)(dy), (double)(dx)));
	theta_e = desired_angle - (int)robot->rotation;
	
	while (theta_e > 180) theta_e -= 360;
	while (theta_e < -180) theta_e += 360;

	if (d_e > 100.) 
		Ka = 17. / 90.;
	else if (d_e > 50)
		Ka = 19. / 90.;
	else if (d_e > 30)
		Ka = 21. / 90.;
	else if (d_e > 20)
		Ka = 23. / 90.;
	else 
		Ka = 25. / 90.;
	
	if (theta_e > 95 || theta_e < -95)
	{
		theta_e += 180;
		
		if (theta_e > 180) 
			theta_e -= 360;
		if (theta_e > 80)
			theta_e = 80;
		if (theta_e < -80)
			theta_e = -80;
		if (d_e < 5.0 && abs(theta_e) < 40)
			Ka = 0.1;
		vr = (int)(-vc * (1.0 / (1.0 + exp(-3.0 * d_e)) - 0.3) + Ka * theta_e);
		vl = (int)(-vc * (1.0 / (1.0 + exp(-3.0 * d_e)) - 0.3) - Ka * theta_e);
	}
	
	else if (theta_e < 85 && theta_e > -85)
	{
		if (d_e < 5.0 && abs(theta_e) < 40)
			Ka = 0.1;
		vr = (int)( vc * (1.0 / (1.0 + exp(-3.0 * d_e)) - 0.3) + Ka * theta_e);
		vl = (int)( vc * (1.0 / (1.0 + exp(-3.0 * d_e)) - 0.3) - Ka * theta_e);
	}
	else
	{
		vr = (int)(+.17 * theta_e);
		vl = (int)(-.17 * theta_e);
	}
	Velocity(robot, vl, vr);
}

void gotoxy(Robot *robot, double destino_x, double destino_y)
{
	Position( Robot *robot, destino_x, destino_y );
}


void PredictBall ( Environment *env )
{
	double dx = env->currentBall.pos.x - env->lastBall.pos.x;
	double dy = env->currentBall.pos.y - env->lastBall.pos.y;
	env->predictedBall.pos.x = env->currentBall.pos.x + dx;
	env->predictedBall.pos.y = env->currentBall.pos.y + dy;
}

void IntervenirJugadorPelota(Robot *robot, OpponentRobot *opponent,Environment *env)
{
	//Verificar si hay espacio para posicionar nuestro robot , entre el oponente y la pelota
	double margen = 5.0;
	if(hayEspacio(opponent,&env->currentBall,margen))
	{
		//calculo la distancia media en x e y
		double x = (opponent->pos.x + env->currentBall.pos.x)/2;
		double y = (opponent->pos.y + env->currentBall.pos.y)/2;
		Position(robot,x,y);
	}
}

void rodearPelota((Robot *robot,Ball *ball,double distancia,Orientacion orientacion))
{
	double x = (ball->pos.x+margen < 93 )?ball->pos.x+margen:ball->pos.x;
	double y = (ball->pos.y+margen < 73 )?ball->pos.y+margen:ball->pos.y;
	
	Position(robot, ball->pos.x+margen, robot->pos.y+margen);
}

void seguirJugador(Robot *sigue,Robot *aSeguir,double distancia,Orientacion orientacion)
{
	
}

bool hayEspacio(OpponentRobot *opponent,Ball *ball,double margen)
{
	//Verificar si hay espacio para posicionar nuestro robot , entre el oponente y la pelota
	double distancia_x = modulo(opponent->pos.x - ball->pos.x); 
	double distancia_y = modulo(opponent->pos.y - ball->pos.y);

	return	distancia_x > margen && distancia_y > margen;
}

double modulo(double nro)
{
	//Si el numero es negativo , lo convierte en positivo
	//si el numero es positivo , lo deja positivo
	return (nro >= 0)nro :nro*-1;
}

