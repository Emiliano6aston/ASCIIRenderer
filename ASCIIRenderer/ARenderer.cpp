#include <vector>
#include <string>
#include <windows.h>
#include "ARenderer.h"

using namespace std;

ARender::ARender(int v_sizex, int v_sizey) {
	
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);

	sizex = v_sizex;
	sizey = v_sizey;

	int relleno = 32;

	for (int y = 0; y < sizey; y++) {
		vector<Apix3> fila;
		for (int x = 0; x < sizex; x++) {
			Apix3 ap;
			ap.charf = relleno;
			fila.push_back(ap);
		}
		charmap.push_back(fila);
	}

	screen = charmap;
}

int ARender::getSizeX() { return sizex; }

int ARender::getSizeY() { return sizey; }

void ARender::RenderBase(int x, int y, int v_color, int c) {
	

	GetConsoleCursorInfo(hCon, &cci);
	cci.dwSize = 100;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(hCon, &cci);

	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hCon, dwPos);

	color = v_color;
	SetConsoleTextAttribute(hCon, color);
	printf("%c", (char)c);

	dwPos.X = sizex;
	dwPos.Y = sizey;
	SetConsoleCursorPosition(hCon, dwPos);

	color = 7;
	SetConsoleTextAttribute(hCon, color);
}

void ARender::RenderAll() {

	for (int y = 0; y < sizey; y++) {
		for (int x = 0; x < sizex; x++) {

			Apix3 ap = screen[y][x];

			int c = 0;
			int color = 127;

			if (ap.chart != -1) {
				c = ap.chart;
				color = ap.colort;
			}
			else {
				if (ap.charm != -1){
					c = ap.charm;
					color = ap.colorm;
				}
				else {
					c = ap.charf;
					color = ap.colorf;
				}
			}

			RenderBase(x, y, color, c);

		}
	}
}

void ARender::setAt(int x, int y, int capa, char c, int v_color) {

	if (x > -1 and x < sizex and y > -1 and y < sizey) {
		if (capa == 0) {
			charmap[y][x].colorf = v_color;
			charmap[y][x].charf = (int)c;
		}
		if (capa == 1) {
			charmap[y][x].colorm = v_color;
			charmap[y][x].charm = (int)c;
		}
		if (capa == 2) {
			charmap[y][x].colort = v_color;
			charmap[y][x].chart = (int)c;
		}
		
	}
}
void ARender::RendterText(int x, int y, string text, int v_color) {

	for (int i = 0; i < text.size(); i++) {
		setAt(x + i, y, 2, text[i], v_color);
	}

}

//Limpia los caracteres de las capas mid y top, dejando sólo el fondo. Para reemplazar el fondo hay que usar RenderAll.
void ARender::resetAt(int x, int y) {

	if (x > -1 and x < sizex and y > -1 and y < sizey) {
		charmap[y][x].charm = -1;
		charmap[y][x].chart = -1;
	}
}

void ARender::CleanScreen() {

	for (int y = 0; y < sizey; y++) {
		for (int x = 0; x < sizex; x++) {

			charmap[y][x].charm = -1;
			charmap[y][x].chart = -1;
		}
	}
}

void ARender::RenderDiff() {

	for (int y = 0; y < sizey; y++) {
		for (int x = 0; x < sizex; x++) {

			Apix3 aps = screen[y][x];
			Apix3 ap = charmap[y][x];

			if (!ap.compare(aps)) {
				screen[y][x] = ap;

				int c = 0;
				int color = 127;

				if (ap.chart != -1) {
					c = ap.chart;
					color = ap.colort;
				}
				else {
					if (ap.charm != -1){
						c = ap.charm;
						color = ap.colorm;
					}
					else {
						c = ap.charf;
						color = ap.colorf;
					}
				}
				RenderBase(x, y, color, c);
			}
		}
	}
} 

void ARender::RenderSprite(ASprite* s, int capa) {

	pos size = s->getSize();
	int x = s->xpos;
	int y = s->ypos;
	int sx = 0;
	int sy = 0;

	for (int j = y; j < (y  + size.y); j++) {
		int sx = 0;
		for (int i = x; i < (x + size.x); i++) {
			if (i >= 0 and j >= 0 and i < sizex and j < sizey and sx < size.x and sy < size.y) {
				Apix a = s->getAt(sx, sy);
				if (capa == 2) {
					charmap[j][i].chart = a.chars;
					charmap[j][i].colort = a.colors;
				}
				else {
					if (capa == 1) {
						charmap[j][i].charm = a.chars;
						charmap[j][i].colorm = a.colors;
					}
					else {
						charmap[j][i].charf = a.chars;
						charmap[j][i].colorf = a.colors;
					}
				}
				sx++;
			}
		}
		sy++;
	}
}
