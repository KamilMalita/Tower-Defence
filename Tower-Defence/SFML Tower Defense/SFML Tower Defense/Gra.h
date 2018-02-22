#pragma once
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <string>
#include "Silnik.h"
#include "Sys.h"
using namespace std;
using namespace sf;
class Gra
{
	Event event;
	Text tekst[2];
	Font moja_czcionka;
	void single(int poziom);
	void menu();
public:
	Gra();
	~Gra();
	void trudnosc();
	void startGra();
protected:
	enum TrybGry {MENU, GRA_LATWA,GRA_TRUDNA, KONIEC_GRY, KONIEC};
	TrybGry tryb;
};

