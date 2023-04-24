#pragma once

#include <vector>
#include <string>
#include <windows.h>
#include "ASprites.h"

#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80

/*Foreground colors
	FG_BLACK = 0,
	FG_BLUE = 1,
	FG_GREEN = 2,
	FG_CYAN = 3,
	FG_RED = 4,
	FG_MAGENTA = 5,
	FG_BROWN = 6,
	FG_LIGHTGRAY = 7,
	FG_GRAY = 8,
	FG_LIGHTBLUE = 9,
	FG_LIGHTGREEN = 10,
	FG_LIGHTCYAN = 11,
	FG_LIGHTRED = 12,
	FG_LIGHTMAGENTA = 13,
	FG_YELLOW = 14,
	FG_WHITE = 15
  Background colors
	BG_NAVYBLUE = 16,
	BG_GREEN = 32,
	BG_TEAL = 48,
	BG_MAROON = 64,
	BG_PURPLE = 80,
	BG_OLIVE = 96,
	BG_SILVER = 112,
	BG_GRAY = 128,
	BG_BLUE = 144,
	BG_LIME = 160,
	BG_CYAN = 176,
	BG_RED = 192,
	BG_MAGENTA = 208,
	BG_YELLOW = 224,
	BG_WHITE = 240
*/

using namespace std;

struct Apix3 {
	int charf = 0;
	int colorf = 8;
	int charm = -1;
	int colorm = 7;
	int chart = -1;
	int colort = 15;

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
	int color;

	CONSOLE_CURSOR_INFO  cci;

public:
	ARender(int v_sizex, int v_sizey);

	void RenderBase(int x, int y, int v_color, int c);
	void setAt(int x, int y, int capa, char c, int v_color = 7);
	void RendterText(int x, int y, string text, int v_color = 7);
	void RenderAll();
	void resetAt(int x, int y);
	void RenderDiff();//
	void RenderSprite(ASprite* s, int capa = 1); //los sprites tienen que actualizarse cada bucle
	void CleanScreen(); //limpia las capas 1 y 2, donde se imprimen los sprites y efectos
	int getSizeX();
	int getSizeY();

	
	//Posibles funciones del ARenderer
	//Render de lineas, marcando un inicio y un final de linea( horizontales y verticales por ahora)
	//Definir capas dentro de los vectores Capa1 = fondo Capa2 = tablero del juego Capa3 = fichas Capa4 = efectos
	//			en las capas sólo se imprimiría el caracter de la capa más alta, por ejemplo un efecto (ejemplo el cursor) que durase un tiempo

};