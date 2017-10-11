// Strategy.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "Strategy.h"

#include "Util.h"
//#include <Util.h>
#include <math.h>
#include "Const.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}



//const double PI = 3.1415923;

char myMessage[200]; //big enough???

void PredictBall ( Environment *env );
void Goalie1 ( Robot *robot, Environment *env );
void Goalie2 ( Robot *robot, Environment *env );
void NearBound2 ( Robot *robot, double vl, double vr, Environment *env );
void Attack2 ( Robot *robot, Environment *env );
void Defend ( Robot *robot, Environment *env, double low, double high );

// by moon at 9/2/2002
void MoonAttack (Robot *robot, Environment *env,int numero);
// just for testing to check whether the &env->opponent works or not
void MoonFollowOpponent (  Robot *robot, OpponentRobot *opponent,Environment * env );

bool estoyMasCercaToXY(Robot *robot, Robot *otro, double x, double y);
bool estoyAbajoXY(Robot *robot,double x,double y);
bool estoyIzquierdaXY(Robot *robot,double x,double y);
void irAlLadoInversoXY(Robot *robot,double x, double y);
void salirDeChoque(Robot *robot,Environment *env);
void salirDeChoque2(Robot *robot,Environment *env);

extern "C" STRATEGY_API void Create ( Environment *env )
{
	// allocate user data and assign to env->userData
	// eg. env->userData = ( void * ) new MyVariables ();
}

extern "C" STRATEGY_API void Destroy ( Environment *env )
{
	// free any user data created in Create ( Environment * )

	// eg. if ( env->userData != NULL ) delete ( MyVariables * ) env->userData;
}

extern "C" STRATEGY_API void Strategy ( Environment *env )
{

	// the below codes are just for demonstration purpose....don't take this seriously please.

	int testInt = 100;
	int k;

	switch (env->gameState)
	{
		case 0:
			// default

			MoonFollowOpponent ( &env->home [1], &env->opponent [2], env );
			MoonFollowOpponent ( &env->home [2], &env->opponent [3],env );
			//MoonFollowOpponent ( &env->home [3], &env->opponent [4] );
			MoonAttack ( &env->home [3], env , 3);
			MoonAttack ( &env->home [4], env , 4);
			Goalie2 ( &env->home [0], env );

			break;

		case FREE_BALL:

			// Follow opponent guy
			MoonFollowOpponent ( &env->home [1], &env->opponent [2],env );
			MoonFollowOpponent ( &env->home [2], &env->opponent [3] ,env);
			//MoonFollowOpponent ( &env->home [3], &env->opponent [4] );

			// attack
			MoonAttack ( &env->home [3], env , 3);
			MoonAttack ( &env->home [4], env , 4);

			// Goal keeper
			Goalie2 ( &env->home [0], env );

			// by moon at 24/03/2002
			// below code will not work.... never try....
			//	env->home[0].pos.x = 50;
			//	env->home[0].pos.y = 0;
			//	env->home[0].rotation = 20.0;

			break;

		case PLACE_KICK:
			//MoonAttack ( &env->home [4], env, 2);
			//Si es menor a 4,se pega al robot :S
			seguirJugador( &env->home[3],&env->home[2],4,NOROESTE);
			seguirJugador( &env->home[4],&env->home[2],4,SUROESTE);

			//rodearPelota (&env->home [4],&env->predictedBall,3,ESTE);
			break;			
		case PENALTY_KICK:
			switch (env->whosBall)
			{
			case ANYONES_BALL:
				MoonAttack ( &env->home [1], env,1 );
				break;
			case BLUE_BALL:
				MoonAttack ( &env->home [4], env,4 );
				break;
			case YELLOW_BALL:
				MoonAttack ( &env->home [0], env,0 );
				break;
			}
			break;

		case FREE_KICK:

			FILE * debugfile; 
			debugfile = fopen("debugfile.txt","a"); 
			
			for (k=0;k<=4;k++) 
				fprintf(debugfile, "robot: %d x: %f y: %f z: %f \n",
					k, env->opponent[k].pos.x, env->opponent[k].pos.y, 
					env->opponent[k].pos.z); 
			
			fclose(debugfile); 

			MoonAttack ( &env->home [0], env, 0 );

			break;

		case GOAL_KICK:
			MoonAttack ( &env->home [0], env,0 );
			break;
  }
}

bool estoyMasCercaToXY(Robot *robot, Robot *otro, double x, double y){
	double robot_distancia = Distancia_2Pts(robot->pos.x, x, robot->pos.y, y);
	double otro_distancia = Distancia_2Pts(otro->pos.x, x, robot->pos.y, y);
	return robot_distancia < otro_distancia;
}
bool estoyAbajoXY(Robot *robot,double x,double y){
	return robot->pos.x > x - 4 && robot->pos.x < x + 4 && robot->pos.y < y;
}

bool estoyIzquierdaXY(Robot *robot,double x,double y){
	return robot->pos.x > x - 30 && robot->pos.x < y + 30 && robot->pos.x < x;
}
void irAlLadoInversoXY(Robot *robot,double x, double y){
	double pos_x = robot->pos.x;
	double pos_y = robot->pos.y;
		if (pos_x < x){
			//mover a la derecha
				if (pos_y < y - 5 || pos_y > y + 5 ) 
					// voy directo
						Position(robot, x+15, y);
				if(pos_x + 15 >= LIMITE_SUPERIOR_CAMPO)	
					// voy por abajo
					Position(robot, x+15, y);
				else 
					//voy por arriba
					Position(robot, x+15, y);
		}else 
			// mover a la izquierda
			Position(robot, x-15, y);
}

bool estaEnfrentado(double rot,double rot_otro){
	return (fabs(rot) - fabs(rot_otro) < 10); 
}

void salirDeChoque(Robot *robot,Environment *env){
	//CalcularAnguloAGirar2
	//Cerca del robot
	double pos_x, pos_y;
	double angulo;
	double rot_otro,rot;
	bool enfrentado;
	Vector3D pos_otro;
	pos_x = robot->pos.x;
	pos_y = robot->pos.y;
	rot = robot->rotation;
	for(int i = 0 ; i < 5 ; i++){
		pos_otro = env->opponent[i].pos;
		rot_otro = env->opponent[i].rotation;

		if(CercaDe(pos_x,pos_y,pos_otro.x,pos_otro.y,6)){
			//entonces hago algo
			angulo = CalcularAngulo2Pts(pos_x,pos_y,pos_otro.x,pos_otro.y);
			enfrentado=estaEnfrentado(rot,rot_otro);
			if((angulo < 40 || angulo > 320) && enfrentado)
				Position(robot,pos_x-5,pos_y-15);
			else if (angulo > 50 && angulo < 130 && enfrentado)
				Position(robot,pos_x-15,pos_y-5);
			else if (angulo > 140 && angulo < 220 && enfrentado)
				Position(robot,pos_x+5,pos_y+15);
			else if (angulo > 230 && angulo < 310 && enfrentado)
				Position(robot,pos_x-15,pos_y+5);
		}
	}
}

void salirDeChoque2(Robot *robot,Environment *env){
	//CalcularAnguloAGirar2
	//Cerca del robot
	double pos_x, pos_y;
	double angulo;
	double rot_otro,rot;
	bool enfrentado;
	Vector3D pos_otro;
	pos_x = robot->pos.x;
	pos_y = robot->pos.y;
	rot = robot->rotation;
	for(int i = 0 ; i < 5 ; i++){
		pos_otro = env->home[i].pos;
		rot_otro = env->home[i].rotation;
		if (robot->pos.x != env->home[i].pos.x && robot->pos.y != env->home[i].pos.y)
		if(CercaDe(pos_x,pos_y,pos_otro.x,pos_otro.y,5)){
			//entonces hago algo
			angulo = CalcularAngulo2Pts(pos_x,pos_y,pos_otro.x,pos_otro.y);
			enfrentado=estaEnfrentado(rot,rot_otro);
			if((angulo < 40 || angulo > 320) && enfrentado)
				Position(robot,pos_x-5,pos_y-15);
			else if (angulo > 50 && angulo < 130 && enfrentado)
				Position(robot,pos_x-15,pos_y-5);
			else if (angulo > 140 && angulo < 220 && enfrentado)
				Position(robot,pos_x+5,pos_y+15);
			else if (angulo > 230 && angulo < 310 && enfrentado)
				Position(robot,pos_x-15,pos_y+5);
		}
	}
}


void MoonAttack ( Robot *robot, Environment *env,int numero )
{
	numero = numero == 3? 4: 3;
	int zonaPelota;
	//Velocity (robot, 127, 127);
	//Angle (robot, 45);
	PredictBall ( env );
	double ball_x = env->currentBall.pos.x;
	double ball_y = env->currentBall.pos.y;
	zonaPelota = ZonaReal(ball_x,ball_y);
	//Position(robot, env->predictedBall.pos.x, env->predictedBall.pos.y);
	//if (robot->pos.y > ball_y - 8 && robot->pos.y < ball_y + 8){
	if (zonaPelota == 8 || zonaPelota == 9)
	{
		if (robot->pos.x != env->home[4].pos.x && robot->pos.y != env->home[4].pos.y) 
			Position(robot, 66.0, 30.0);
		else
			Position(robot, 66.0, 55.0);
	}
	else
	{
		if (estoyMasCercaToXY(robot, &env->home[numero],ball_x,ball_y)){
			zonaPelota = Zona(ball_x,ball_y);
			if(zonaPelota == 1 || zonaPelota == 2 || zonaPelota == 7 || zonaPelota == 8 ){
				if (estoyAbajoXY(robot,ball_x,ball_y))
					Position(robot, env->predictedBall.pos.x ,env->predictedBall.pos.y);
				else
					Position(robot, env->predictedBall.pos.x ,env->currentBall.pos.y - 15);
			}
			else if(ZonaReal(ball_x,ball_y) > 6){
				if (estoyIzquierdaXY(robot,ball_x,ball_y))
					Position(robot, env->predictedBall.pos.x + 15 ,env->currentBall.pos.y - 15);
				else
					Position(robot, env->predictedBall.pos.x ,env->predictedBall.pos.y);
			}
			else
				Position(robot, env->predictedBall.pos.x ,env->predictedBall.pos.y);
		}
		else
		{
			if (ZonaReal(ball_x,ball_y) < 3 ) // si esta en el area chica pegale a la pelota
				Position(robot, env->predictedBall.pos.x ,env->predictedBall.pos.y);
			else // despues sera seguir al otro 
				Position(robot, env->predictedBall.pos.x + 10,env->predictedBall.pos.y);
		}
	}
	
	// Position(robot, 0.0, 0.0);
	if ( (ZonaReal(ball_x,ball_y) > 3 && ZonaReal(robot->pos.x,robot->pos.x) > 3)
		|| (ZonaReal(ball_x,ball_y) < 8 && ZonaReal(robot->pos.x,robot->pos.x) < 8)){
			salirDeChoque(robot, env);
			salirDeChoque2(robot,env);
	}
	NearBound2(robot,robot->velocityLeft,robot->velocityRight,env);

}

//agregado para que sigan la pelota cuando pasa la mitad de cancha
void MoonFollowOpponent ( Robot *robot, OpponentRobot *opponent ,Environment *env)
{
	PredictBall ( env );
	double ball_x = env->currentBall.pos.x;
	double ball_y = env->currentBall.pos.y;

	if (ZonaReal(ball_x, ball_y) > 6)
		Position(robot, env->predictedBall.pos.x, env->predictedBall.pos.y);
	else{
		if (robot->pos.x != env->home[1].pos.x && robot->pos.y != env->home[1].pos.y) 
			Position(robot, POS_DEFENSOR_PASIVO_X, POS_DEFENSOR_PASIVO_UNO_Y);
		else
			Position(robot, POS_DEFENSOR_PASIVO_X, POS_DEFENSOR_PASIVO_DOS_Y);
	}
		
}

void Goalie2 ( Robot *robot, Environment *env )
{
	PredictBall(env);
	int zona = ZonaReal(env->predictedBall.pos.x, env->predictedBall.pos.y);
	if(zona == 9 || zona == 8)
		Position(robot, env->predictedBall.pos.x, env->predictedBall.pos.y);
	else
		Position(robot, 90.7 , 42.2 );
}

void Goalie1 ( Robot *robot, Environment *env )
{
	double velocityLeft = 0, velocityRight = 0;
	
	double Tx = env->goalBounds.right - env->currentBall.pos.x;
	double Ty = env->fieldBounds.top - env->currentBall.pos.y;

	double Ax = env->goalBounds.right - robot->pos.x;
	double Ay = env->fieldBounds.top - robot->pos.y;

	if ( Ay > Ty + 0.9 && Ay > 27 )
	{
		velocityLeft = -100;
		velocityRight = -100;
	}

	if ( Ay > Ty - 0.9 && Ay < 43 )
	{
		velocityLeft = 100;
		velocityRight = 100;
	}

	if ( Ay < 27 )
	{
		velocityLeft = 100;
		velocityRight = 100;
	}

	if ( Ay > 43 )
	{
		velocityLeft = -100;
		velocityRight = -100;
	}

	double Tr = robot->rotation;
	if ( Tr < 0.001 )
		Tr = Tr + 360;
	if ( Tr > 360.001 )
		Tr = Tr - 360;
	if ( Tr > 270.5 )
		velocityRight = velocityRight + fabs ( Tr - 270 );
	else if ( Tr < 269.5 )
		velocityLeft = velocityLeft + fabs ( Tr - 270 );

	robot->velocityLeft = velocityLeft;
	robot->velocityRight = velocityRight;
}



void Attack2 ( Robot *robot, Environment *env )
{
	Vector3D t = env->currentBall.pos;
	double r = robot->rotation;
	if ( r < 0 ) r += 360;
	if ( r > 360 ) r -= 360;
	double vl = 0, vr = 0;

	if ( t.y > env->fieldBounds.top - 2.5 ) t.y = env->fieldBounds.top - 2.5;
	if ( t.y < env->fieldBounds.bottom + 2.5 ) t.y = env->fieldBounds.bottom + 2.5;
	if ( t.x > env->fieldBounds.right - 3 ) t.x = env->fieldBounds.right - 3;
	if ( t.x < env->fieldBounds.left + 3 ) t.x = env->fieldBounds.left + 3;

	double dx = robot->pos.x - t.x;
	double dy = robot->pos.y - t.y;

	double dxAdjusted = dx;
	double angleToPoint = 0;

	if ( fabs ( robot->pos.y - t.y ) > 7 || t.x > robot->pos.x )
		dxAdjusted -= 5;

	if ( dxAdjusted == 0 )
	{
		if ( dy > 0 )
			angleToPoint = 270;
		else
			angleToPoint = 90;
	}
	else if ( dy == 0 )
	{
		if ( dxAdjusted > 0 )
			angleToPoint = 360;
		else
			angleToPoint = 180;
		
	}
	else
		angleToPoint = atan ( fabs ( dy / dx ) ) * 180.0 / PI;

	if ( dxAdjusted > 0 )
	{
		if ( dy > 0 )
			angleToPoint -= 180;
		else if ( dy < 0 )
			angleToPoint = 180 - angleToPoint;
	}
	if ( dxAdjusted < 0 )
	{
		if ( dy > 0 )
			angleToPoint = - angleToPoint;
		else if ( dy < 0 )
			angleToPoint = 90 - angleToPoint;
	}

	if ( angleToPoint < 0 ) angleToPoint = angleToPoint + 360;
	if ( angleToPoint > 360 ) angleToPoint = angleToPoint - 360;
	if ( angleToPoint > 360 ) angleToPoint = angleToPoint - 360;

	double c = r;

	double angleDiff = fabs ( r - angleToPoint );

	if ( angleDiff < 40 )
	{
		vl = 100;
		vr = 100;
		if ( c > angleToPoint )
			vl -= 10;
		if ( c < angleToPoint )
			vr -= 10;
	}
	else
	{
		if ( r > angleToPoint )
		{
			if ( angleDiff > 180 )
				vl += 360 - angleDiff;
			else
				vr += angleDiff;
		}
		if ( r < angleToPoint )
		{
			if ( angleDiff > 180 )
				vr += 360 - angleDiff;
			else
				vl += angleDiff;
		}
	}

	NearBound2 ( robot, vl, vr, env );
}

void NearBound2 ( Robot *robot, double vl, double vr, Environment *env )
{
	//Vector3D t = env->currentBall.pos;

	Vector3D a = robot->pos;
	double r = robot->rotation;

	if ( a.y > env->fieldBounds.top - 15 && r > 45 && r < 130 )
	{
		if ( vl > 0 )
			vl /= 3;
		if ( vr > 0 )
			vr /= 3;
	}

	if ( a.y < env->fieldBounds.bottom + 15 && r < -45 && r > -130 )
	{
		if ( vl > 0 ) vl /= 3;
		if ( vr > 0 ) vr /= 3;
	}

	if ( a.x > env->fieldBounds.right - 10 )
	{
		if ( vl > 0 )
			vl /= 2;
		if ( vr > 0 )
			vr /= 2;
	}

	if ( a.x < env->fieldBounds.left + 10 )
	{
		if ( vl > 0 )
			vl /= 2;
		if ( vr > 0 )
			vr /= 2;
	}

	robot->velocityLeft = vl;
	robot->velocityRight = vr;
}

void Defend ( Robot *robot, Environment *env, double low, double high )
{
	double vl = 0, vr = 0;
	Vector3D z = env->currentBall.pos;

	double Tx = env->goalBounds.right - z.x;
	double Ty = env->fieldBounds.top - z.y;
	Vector3D a = robot->pos;
	a.x = env->goalBounds.right - a.x;
	a.y = env->fieldBounds.top - a.y;

	if ( a.y > Ty + 0.9 && a.y > low )
	{
		vl = -100;
		vr = -100;
	}
	if ( a.y < Ty - 0.9 && a.y < high )
	{
		vl = 100;
		vr = 100;
	}
	if ( a.y < low )
	{
		vl = 100;
		vr = 100;
	}
	if ( a.y > high )
	{
		vl = -100;
		vr = -100;
	}

	double Tr = robot->rotation;

	if ( Tr < 0.001 )
		Tr += 360;
	if ( Tr > 360.001 )
		Tr -= 360;
	if ( Tr > 270.5 )
		vr += fabs ( Tr - 270 );
	else if ( Tr < 269.5 )
		vl += fabs ( Tr - 270 );

	NearBound2 ( robot, vl ,vr, env );
}