#pragma once

#include <fstream>
#include <vector>
#include <string>
#include <windows.h>

using namespace std;

struct Apix {
	int chars = -1;
	int colors = 7;

	bool compare(Apix& a) {
		if (a.chars == chars) {
			if (a.colors == colors) {
				return true;
			}
		}
		return false;
	}
};

struct pos {
	int x = 0;
	int y = 0;
};

class ASprite {
private:
	int sizex = 0;
	int sizey = 0;
	int color = 8;
	vector< vector <Apix> > charmap; //Un vector que contiene los caracteres del sprite y su color en int
	string archivo;

public:
	int xpos = 0;
	int ypos = 0;

	ASprite(int v_sizex, int v_sizey, string archivo);
	Apix getAt(int x, int y);
	pos getPos();
	pos getSize();
	void setColor(int v_color);
	void setColorAt(int x, int y, int v_color);
	void moveSprite(int x, int y);
};