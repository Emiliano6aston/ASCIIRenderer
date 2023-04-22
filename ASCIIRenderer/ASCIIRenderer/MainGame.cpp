#include "ARenderer.h"
#include "ASprites.h"

#include <stdio.h>
#include <conio.h>

int main() {
	ARender* RA = new ARender(32,16);

	bool play = true;

	int control = 0;
	int next = 30;

	ASprite* fondo = new ASprite(32, 16, "fondo.txt");
	fondo->setColor(127);
	ASprite* s1 = new ASprite(3, 1, "ficha.txt");
	s1->setColor(200);
	s1->xpos = 28;
	s1->ypos = 8;
	
	RA->RenderSprite(fondo,0);
	RA->RenderSprite(s1);
	RA->RenderAll();
	

	while (play) {
		//Rendering function
		RA->CleanScreen();
//		RA->RenderSprite(fondo,0);
		RA->RenderSprite(s1);
		RA->RenderDiff();
		//RA->RenderAll();
		//Handle Input and Gameplay

		if (_kbhit()) {
			char tecla = _getch();
			//Mover cursor
			if (tecla == ARRIBA) {
				s1->moveSprite(0,-1);
			}
			if (tecla == ABAJO) {
				s1->moveSprite(0, 1);
			}
			if (tecla == IZQUIERDA) {
				s1->moveSprite(-1, 0);
			}
			if (tecla == DERECHA) {
				s1->moveSprite(1, 0);
			}

			if (tecla == (char)27) {
				play = false;
			}
		}
	}

	//Deleting the Renderer
	delete RA;
	delete s1;
	delete fondo;

	return 0;
}