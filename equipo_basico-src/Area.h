// Area.h: interface for the Area class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AREA_H__E0FC582D_5432_4C81_BE39_56A7B9E01BC5__INCLUDED_)
#define AFX_AREA_H__E0FC582D_5432_4C81_BE39_56A7B9E01BC5__INCLUDED_
#include <vector>
#include "Strategy.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

using namespace std;
enum eArea{MEDIO_CAMPO,AREA_PENAL,AREA_GOL,AREA_AZUL,AREA_AMARILLO,INDEFINIDO};

class Area  
{
private:

	eArea enumArea;
	double	inicio_x,
			fin_x,
			inicio_y,
			fin_y;
	std::vector<Area*> subAreas;
	std::vector<OpponentRobot*> oponentes;
	std::vector<Robot*> companeros;
 
public:
	Area();
	Area(double inicio_x,double fin_x,double inicio_y,double fin_y);
	void setTipoArea(eArea area);
	eArea getTipoArea();
	virtual ~Area();
	bool estoyDentroDelArea(double posicion_x,double posicion_y);
	bool mitadSuperior(double posicion_y);
	bool mitadInferior(double posicion_y);
	void agregarArea(Area *area);
	void agregarAreaPuntos(double inicio_x,double fin_x,double inicio_y,double fin_y);
	Area* darArea(double posicion_x,double posicion_y);
	Area* darArea(eArea);
	vector<Area*> darSubAreas();
	
	void update(Environment *env);
	vector<Robot*> darCompaneros();
	vector<OpponentRobot*> darOponente();

	void subdividir();
	void dividir();
};

#endif // !defined(AFX_AREA_H__E0FC582D_5432_4C81_BE39_56A7B9E01BC5__INCLUDED_)
