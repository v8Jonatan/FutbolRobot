// ZonaJuego.cpp: implementation of the ZonaJuego class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZonaJuego.h"
#include "const.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZonaJuego::ZonaJuego()
{
	//Cargo Zonas Equipo AMARILLO

	this->amarilla = new Area(INICIO_X,FIN_X/2,INICIO_Y,FIN_Y);
	amarilla->setTipoArea(MEDIO_CAMPO);
	
	Area *zonaGolAmarilla = new Area(INICIO_X,AREA_CHICA_LINEA_IZQUIERDA,
									 AREA_CHICA_LINEA_INFERIOR,AREA_CHICA_LINEA_SUPERIOR);
	zonaGolAmarilla->setTipoArea(AREA_GOL);
	
	Area *zonaPenalAmarilla = new Area(INICIO_X,AREA_GRANDE_LINEA_IZQUIERDA,
										AREA_GRANDE_LINEA_INFERIOR,AREA_GRANDE_LINEA_SUPERIOR);

	zonaPenalAmarilla->agregarArea(zonaGolAmarilla);
	zonaPenalAmarilla->setTipoArea(AREA_PENAL);
	
	amarilla->agregarArea(zonaPenalAmarilla);

	//Cargo Zonas Equipo AZUL
	
	this->azul = new Area(FIN_X/2,FIN_X,INICIO_Y,FIN_Y);
	azul->setTipoArea(MEDIO_CAMPO);
	
	Area *zonaGolAzul = new Area(AREA_CHICA_LINEA_DERECHA,FIN_X,
									AREA_CHICA_LINEA_INFERIOR,AREA_GRANDE_LINEA_SUPERIOR);
	zonaGolAzul->setTipoArea(AREA_GOL);
	
	Area *zonaPenalAzul = new Area(AREA_GRANDE_LINEA_DERECHA,FIN_X,
									AREA_GRANDE_LINEA_INFERIOR,AREA_GRANDE_LINEA_SUPERIOR);
	zonaPenalAzul->agregarArea(zonaGolAzul);
	zonaPenalAzul->setTipoArea(AREA_PENAL);
	
	azul->agregarArea(zonaPenalAzul);
	

	//Cargo Zonas cuadrantes (32 cuadrantes de 8 largo x 4 alto)
	cuadrante = new Area(INICIO_X,FIN_X,INICIO_Y,FIN_Y);	
	cuadrante->dividir();
/*	
	vector<Area*>	subAreas = cuadrante->darSubAreas(),
					areaAzul,
					areaAmarillo;
	int i = 0, 
		tam = 0;
	//Divido la zona amarilla 4
	subAreas[0]->subdividir();
	areaAmarillo = subAreas[0]->darSubAreas();

	for(i = 0,tam = areaAmarillo.size(); i < tam; i++)
	{
		areaAmarillo[i]->subdividir();//Divido en 4 cada una de las partes
	}

	//Divido la zona Azul en 4
	subAreas[1]->subdividir();
	areaAzul = subAreas[1]->darSubAreas();
	for(i = 0,tam = areaAzul.size(); i < tam; i++)
	{
		areaAzul[i]->subdividir();//Divido en 4 cada una de las partes
	}
*/	

}

ZonaJuego::~ZonaJuego()
{

}

void ZonaJuego::actualizar()
{
	//todo metodo para actualizar
}

Area* ZonaJuego::darAreaJuegoAzul(){
	return this->azul; 
}

Area* ZonaJuego::darAreaJuegoAmarilla()
{
	return this->amarilla;
}

Area* ZonaJuego::darAreaCuadrante()
{
	return this->cuadrante;
}

Area* ZonaJuego::darArea(double posicion_x,double posicion_y)
{
	if( posicion_x >= (INICIO_X+FIN_X)/2 )
		return azul->darArea(posicion_x,posicion_y);
	else
		return amarilla->darArea(posicion_x,posicion_y);
}

bool ZonaJuego::estoyZonaAmarilla(double posicion_x,double posicion_y)
{	
	return	amarilla->estoyDentroDelArea(posicion_x,posicion_y);
}
bool ZonaJuego::estoyZonaAzul(double posicion_x,double posicion_y)
{	
	return azul->estoyDentroDelArea(posicion_x,posicion_y);
}
bool ZonaJuego::estoyMitadSuperior(double posicion_y)
{	
	return amarilla->mitadSuperior(posicion_y);
}

bool ZonaJuego::estoyMitadSuperior(Ball *pelota){
	return estoyMitadSuperior(pelota->pos.y);
}
bool ZonaJuego::estoyMitadSuperior(OpponentRobot *oponente){
	return estoyMitadSuperior(oponente->pos.y);
}
bool ZonaJuego::estoyMitadSuperior(Robot *jugador){
	return estoyMitadSuperior(jugador->pos.y);
}


bool ZonaJuego::estoyMitadInferior(double posicion_y)
{
	return amarilla->mitadInferior(posicion_y);
}

bool ZonaJuego::estoyMitadInferior(Ball *pelota){
	return estoyMitadInferior(pelota->pos.y);
}
bool ZonaJuego::estoyMitadInferior(OpponentRobot *oponente){
	return estoyMitadInferior(oponente->pos.y);
}
bool ZonaJuego::estoyMitadInferior(Robot *jugador){
	return estoyMitadInferior(jugador->pos.y);
}

bool ZonaJuego::estoyEnArea(double posicion_x,double posicion_y,eArea area)
{
	if(estoyZonaAmarilla(posicion_x,posicion_y))
	{
          Area * aux = amarilla->darArea(posicion_x,posicion_y);
		  
		  if(aux == NULL)
			  return false;
			  
		  return aux->getTipoArea() == area;
	}
	else
	{
		  Area * aux = azul->darArea(posicion_x,posicion_y);
		  
		  if(aux == NULL)
			  return false;
		  
		  return aux->getTipoArea()==area;
	}
}


bool ZonaJuego::estoyEnAreaAmarilla(eArea area,Ball *pelota){

	double pos_x = pelota->pos.x ,
		   pos_y = pelota->pos.y;

	return amarilla->estoyDentroDelArea(area,pos_x,pos_y);
}

bool ZonaJuego::estoyEnAreaAmarilla(eArea area,OpponentRobot *oponente){
	double pos_x = oponente->pos.x ,
		   pos_y = oponente->pos.y;

	return amarilla->estoyDentroDelArea(area,pos_x,pos_y);
}

bool ZonaJuego::estoyEnAreaAmarilla(eArea area,Robot *jugador){
	double pos_x = jugador->pos.x ,
		   pos_y = jugador->pos.y;

	return amarilla->estoyDentroDelArea(area,pos_x,pos_y);
}
	
bool ZonaJuego::estoyEnAreaAzul(eArea area,Ball * pelota){
	double pos_x = pelota->pos.x ,
		   pos_y = pelota->pos.y;

	return azul->estoyDentroDelArea(area,pos_x,pos_y);
}

bool ZonaJuego::estoyEnAreaAzul(eArea area,OpponentRobot *oponente){
	double pos_x = oponente->pos.x ,
		   pos_y = oponente->pos.y;

	return azul->estoyDentroDelArea(area,pos_x,pos_y);
}

bool ZonaJuego::estoyEnAreaAzul(eArea area,Robot *jugador){
	double pos_x = jugador->pos.x ,
		   pos_y = jugador->pos.y;

	return azul->estoyDentroDelArea(area,pos_x,pos_y);

}



	
bool ZonaJuego::hayMasDe3Jugadores(double posicion_x,double posicion_y)
{
	Area * area;
	if(estoyZonaAmarilla(posicion_x,posicion_y))
		area = amarilla->darArea(posicion_x,posicion_y);
	else	
		area = azul->darArea(posicion_x,posicion_y);
	
	//return area->darCompaneros().size()>=3;
	return false;

}

bool hayMasDe3JugadoresAzul(eArea area)
{
	//TODO IMPLEMENTAR 
return false;
}
bool hayMasDe3JugadoresAmarillo(eArea area)
{
	//TODO IMPLEMENTAR
	return false;
}
	
bool hayMasDe2Jugadores(double posicion_x,double posicion_y);
bool hayMasDe2JugadoresAzul(eArea area);
bool hayMasDe2JugadoresAmarillo(eArea area);


