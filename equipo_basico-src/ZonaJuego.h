// ZonaJuego.h: interface for the ZonaJuego class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZONAJUEGO_H__61BDD4F8_A9B4_40B0_8497_7C557FF3BFC5__INCLUDED_)
#define AFX_ZONAJUEGO_H__61BDD4F8_A9B4_40B0_8497_7C557FF3BFC5__INCLUDED_
#include "Area.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ZonaJuego  
{

private:
	Area *azul;
	Area *amarilla;
	Area *cuadrante;

public:
	ZonaJuego();
	void actualizar();
	Area* darAreaJuegoAzul();
	Area* darAreaJuegoAmarilla();
	Area* darAreaCuadrante();

	Area* darArea(double posicion_x,double posicion_y);

	bool estoyZonaAmarilla(double posicion_x,double posicion_y);
	bool estoyZonaAzul(double posicion_x,double posicion_y);
	bool estoyMitadSuperior(double posicion_y);
	bool estoyMitadInferior(double posicion_y);
	bool estoyEnArea(double posicion_x,double posicion_y,eArea area);
	
	bool hayMasDe3Jugadores(double posicion_x,double posicion_y);
	bool hayMasDe3JugadoresAzul(eArea area);
	bool hayMasDe3JugadoresAmarillo(eArea area);
	
	bool hayMasDe2Jugadores(double posicion_x,double posicion_y);
	bool hayMasDe2JugadoresAzul(eArea area);
	bool hayMasDe2JugadoresAmarillo(eArea area);

	
	virtual ~ZonaJuego();

};

#endif // !defined(AFX_ZONAJUEGO_H__61BDD4F8_A9B4_40B0_8497_7C557FF3BFC5__INCLUDED_)
