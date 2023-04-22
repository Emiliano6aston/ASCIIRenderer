#include <fstream>
#include <vector>
#include <string>
#include "ASprites.h"

using namespace std;

ASprite::ASprite(int v_sizex, int v_sizey, string v_archivo) {
	sizex = v_sizex;
	sizey = v_sizey;

	archivo = v_archivo;
	
	ifstream File;
	string linea;
	File.open(archivo);

	for (int y = 0; y < sizey; y++) {
		getline(File, linea);
		vector < Apix > lin;
		for (int x = 0; x < sizex; x++) {
			Apix ap;
			if ((int)linea[x] > 32) {
				ap.chars = (int)linea[x];
			}
			else {
				ap.chars = -1;
			}
			ap.colors = color;
			lin.push_back(ap);
		}
		charmap.push_back(lin);
	}
	File.close();
}

Apix ASprite::getAt(int x, int y) {
	if (x > -1 and x < sizex and y > -1 and y < sizey) {
		return charmap[y][x];
	}
}

pos ASprite::getPos() {

	pos psprite;
	psprite.x = xpos;
	psprite.y = ypos;

	return psprite;
}

pos ASprite::getSize() {

	pos size;
	size.x = sizex;
	size.y = sizey;

	return size;
}

void ASprite::setColor(int v_color) {
	for (int y = 0; y < sizey; y++) {
		for (int x = 0; x < sizex; x++) {
			charmap[y][x].colors = v_color;
		}
	}
}

void ASprite::setColorAt(int x, int y, int v_color) {
	if (x > -1 and y > -1 and x < sizex and y < sizey) {
		if (v_color > 0 and v_color < 255) {
			charmap[y][x].colors = v_color;
		}
	}
}

void ASprite::moveSprite(int x, int y) {

	xpos += x;
	ypos += y;
}