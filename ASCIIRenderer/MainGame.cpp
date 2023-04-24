#include "ARenderer.h"
#include "ASprites.h"

#pragma comment(lib, "winmm.lib")
#include "windows.h"

#include <iostream>
#include <conio.h>
#include <string>
#include <ctime>

int game() {
	ARender* RA = new ARender(64,32);

	bool play = true;
	int puntaje = 1;

	string assets = "Assets\\";

	//Sound names
	string hit = "Hit.wav";
	string fhit = "Fhit.wav";

	int ps = 1;

	int backcolor = 128;
	//Sprite del fondo
	ASprite* fondo = new ASprite(64, 26, assets + "fondo.txt");
	fondo->setColor(backcolor|14);
	fondo->ypos = 4;

	//Sprites jugables
	ASprite* s1 = new ASprite(7, 1, assets + "ficha.txt");
	s1->setColor(backcolor|15);
	s1->xpos = 25;
	s1->ypos = 27;

	ASprite* b1 = new ASprite(1, 1, assets + "ball.txt");
	b1->setColor(backcolor|4);
	b1->xpos = 31;
	b1->ypos = 26;

	ASprite* c1 = new ASprite(3, 2, assets + "box.txt");
	c1->setColor(backcolor|11);
	c1->xpos = 1;
	c1->ypos = 10;
	

	int dirx = 1; //dirección en x bola
	int diry = -1; //dirección en y bola
	int dirc = 1; //direccion x de caja

	//Limites de la pantalla
	int limtop = 7;
	int limbot = 30;
	int limxl = 2;
	int limxr = 60;

	float cont = 0;
	float speed = 300.0;

	int perf = 0;

	time_t t0;
	t0 = clock();
	time_t t1;
	t1 = clock();

	int f = 0;
	time_t deltatime;
	deltatime = 0.0;
	
	RA->RenderSprite(fondo,0);
	RA->RenderSprite(s1);
	RA->RenderSprite(c1);
	RA->RenderSprite(b1, 2);
	RA->RenderAll();
	
	while (play) {
		//perf++;
		//if (perf > 1000) { 
		//	perf = 0;
		//	RA->RenderAll(); 
		//}
		//Manejar Gameplay y Entrada por teclado
		if (_kbhit()) {
			char tecla = _getch();
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
		//Limpiar la pantalla de los sprites
		RA->CleanScreen();
		//Actualizar los sprites
		RA->RenderSprite(fondo,0);
		RA->RenderSprite(s1);
		RA->RenderSprite(c1,2);
		RA->RenderSprite(b1, 2);

		RA->RendterText(0, 0, "FPS: " + to_string(deltatime), 9);
		RA->RendterText(0, 1, "Puntaje: " + to_string(puntaje), 8);
		RA->RendterText(0, 2, "Speed: " + to_string(speed), 7);

		//Mostrar los cambios
		RA->RenderDiff();

		//Timer
		Sleep(1);
		if (f == 0) {
			f++;
			t0 = clock();
		}
		else {
			if (f == 1) {
				f++;
				t1 = clock();
			}
			else {
				if (f == 2) {
					f = 0;
					deltatime = t1 - t0;
					deltatime = (1.0 / deltatime) * 1000;
				}
			}
		}
		//Mover bola y caja
		cont += 1.0 * deltatime;
		if (cont > speed) {
			cont = 0;
			b1->moveSprite(dirx, diry);
			puntaje++;
			ps = 1;


			if (c1->xpos == limxr) { dirc = -1; }
			if (c1->xpos == limxl) { dirc =  1; }
			c1->moveSprite(dirc, 0);

		}

		//Colision con limites de pantalla
		if (b1->xpos < limxl ) { 
			dirx = 1;
			if (ps == 1) { PlaySound(TEXT("Hit.wav"), NULL, SND_ASYNC); ps = 0; }
		}
		if (b1->xpos > limxr ) {
			dirx = -1;
			if (ps == 1) { PlaySound(TEXT("Hit.wav"), NULL, SND_ASYNC); ps = 0; }
		}
		if (b1->ypos < limtop) {
			diry = 1;
			if (ps == 1) { PlaySound(TEXT("Hit.wav"), NULL, SND_ASYNC); ps = 0; }
		}
		if (b1->ypos > limbot) { 
			b1->xpos = 31;
			b1->ypos = 27;
			dirx = 1;
			diry = -1;
			puntaje -= 100;
			speed -= 25;

			if (ps == 1) { PlaySound(TEXT("Fhit.wav"), NULL, SND_ASYNC); ps = 0; }
		} 

		if (speed == 0) { play = false; }

		//Colision con tabla
		if (s1->collide(b1)){
			puntaje++;
			diry = -1;
			if (s1->collidepos(b1).x < 3) {
				dirx = -2;
			}
			if (s1->collidepos(b1).x > 4) {
				dirx = 2;
			}
			if (ps == 1) { PlaySound(TEXT("Bhit.wav"), NULL, SND_ASYNC); ps = 0; }

		}

		//Colision con caja
		if (c1->collide(b1)) {
			if (diry == 1) { diry = -1; }
			else { diry = 1; }
			puntaje += 100;
			if (ps == 1) { PlaySound(TEXT("Hit.wav"), NULL, SND_ASYNC); ps = 0; }
		}
	}

	RA->RendterText(0, 3, "Puntaje Final: " + to_string(puntaje), 15);
	RA->RenderDiff();

	Sleep(1);

	//Deleting the Renderer
	delete RA;
	delete fondo;
	delete s1;
	delete c1;
	delete b1;

	return puntaje;
}

void menu() {

	bool menu = true;

	string opciones = "";
	int puntos = 0;

	while (menu){

		system("cls");

		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN); //| FOREGROUND_INTENSITY);

		cout << "Bienvenido a HitABox." << endl << endl;
		cout << "Si quieres jugar ingresa -> 'J' o 'j'" << endl;
		cout << "Si quieres salir ingresa -> 'S' o 's'" << endl << endl;
		cout << "El puntaje fue: " << puntos << endl;

		cout << "Inrese una opcion:";
		cin >> opciones;
		cin.get();

		if (opciones == "J" or opciones == "j") {
			system("cls");
			cout << "¡A jugar!" << endl;

			puntos = game();

		}
		if (opciones == "S" or opciones == "s") { menu = false;	}
	}
}


//main
int main() {

	menu();

	return 0;
}