#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include "ASprites.h"

#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80

using namespace std;

struct Apix3 {
	int charf = 0;
	int colorf = 7;
	int charm = -1;
	int colorm = 7;
	int chart = -1;
	int colort = 7;

	bool compare(Apix3 &a) {
		if (a.charf == charf){
			if (a.colorf == colorf) {
				if (a.charm == charm) {
					if (a.colorm == colorm) {
						if (a.chart == chart) {
							if (a.colort == colort) {
								return true;
							}
						}
					}
				}
			}
		}
		return false;
	}
};

class ARender {
private:
	vector< vector<Apix3> > screen; //Only for render
	vector< vector<Apix3> > charmap; //For optimize the render and for use in gameplay
	int sizex = 64;
	int sizey = 20;


	HANDLE hCon;
	COORD dwPos;
	//DWORD color;
	CONSOLE_CURSOR_INFO  cci;

public:
	ARender(int v_sizex, int v_sizey);

	void RenderBase(int x, int y, int v_color, int c);
	void setAt(int x, int y, int capa, char c, int v_color = 7);
	void RenderAll();
	void resetAt(int x, int y);
	void RenderDiff();
	void RenderSprite(ASprite* s, int capa = 1); //los sprites tienen que actualizarse cada bucle
	void CleanScreen(); //limpia las capas 1 y 2, donde se imprimen los sprites y efectos
	int getSizeX();
	int getSizeY();

	
	//Posibles funciones del ARenderer
	//Render de lineas, marcando un inicio y un final de linea( horizontales y verticales por ahora)
	//Definir capas dentro de los vectores Capa1 = fondo Capa2 = tablero del juego Capa3 = fichas Capa4 = efectos
	//			en las capas sólo se imprimiría el caracter de la capa más alta, por ejemplo un efecto (ejemplo el cursor) que durase un tiempo

};