// Util.h
// Funciones utiles.

#ifndef UTIL_H
#define UTIL_H

#include "Strategy.h"

// Devuelve el ángulo a girar por un jugador para queda mirando a la posición xf yf.
double CalcularAnguloAGirar2(double x0,double y0, double xf, double yf, double rr);

// Calcula el ángulo que hay entre dos puntos.
double CalcularAngulo2Pts2(double x0, double y0, double xf, double yf);


// Deveulve el ángulo en grados pasado como parámetro en radianes.
double DegtwoRad (double dAngGrados);

// Deveulve el ángulo en radianes pasado como parámetro en grados.
double RadtwoDeg(double dAngRad);


// Calcula la distancia entre dos puntos.
double Distancia2(double x0,double y0,double xf,double yf);

// Devuelve el menor de los dos valores pasados como parámetros.
double Menor(double a, double b);

// Devuelve el mayor de los dos valores pasados como parámetros.
double Mayor(double a, double b);

// Devuelve 0 si el número pasado como parámetro es 0, -1 si es negativo, y 1 si es positivo.
int Signo(double n);

// Devuelve el número de zona en donde se encuentra el punto pasado como parámetro.
int Zona (double x, double y);

int ZonaReal(double x, double y);



double CalcularAngulo2Pts(double xo, double yo, double xf, double yf);

double Distancia_2Pts(double X1 ,double X2,double Y1, double Y2);
double Angulo_2Pts(double Distancia, double Op);

double Radianes_Grados(double Angulo_R);

double Angulo_girar(double Angulo, double Op, double Ady, double rotation);

double NormalizarAngulo(double angulo);


double degToRad(const double angle);

double radToDeg(const double rad);

double CalcularAnguloAGirar(double xo, double yo, double xf, double yf, double rr);


int sgn(double x) ;

double angleToPoint(double xo, double yo, double xf, double yf);

double CalcularAngulo2Pts180(double xo, double yo, double xf, double yf);

double CalcularAnguloAGirar180(double x0, double y0, double xf, double yf, double rr);


int CercaDe(double dXrobot, double dYrobot, double x, double y, double radio);

double PosPrePelY(double PosX, Environment *env);
double PosPrePelX(double PosY, Environment *env);
double Vel_Ball(Environment *env);
int Velocidad(double Distancia);

void Velocity ( Robot *robot, int vl, int vr );

void Angle( Robot *robot, int desired_angle);

void Position( Robot *robot, double x, double y );
void gotoxy( Robot *robot, double destino_x, double destino_y);

void PredictBall( Environment *env );

enum Orientacion{NOROESTE , NORTE  , NORESTE,
				 OESTE    , CENTER , ESTE,
				 SUROESTE , SUR    , SURESTE};

void IntervenirJugadorPelota(Robot *robot, OpponentRobot *opponent,Environment *env);
bool hayEspacio(OpponentRobot *opponent,Ball *ball,double margen);
double modulo(double nro);
void rodearPelota(Robot *robot,Ball *ball,double distancia,Orientacion orientacion);
void seguirJugador(Robot *sigue,Robot *aSeguir,double distancia,Orientacion orientacion);


#endif // UTIL_H