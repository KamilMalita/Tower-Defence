#pragma once

#include "Player.h"
#include "Tower.h"
#include "Monster.h"
#include "Sys.h"
#include <Chronometer.hpp>

using namespace sftools;
class Silnik
{
public:
	Silnik(RenderWindow &win,int poziom);
	~Silnik();
	void runEngine(RenderWindow &window);
private:
	bool boom(Vector2f wek);
	Sprite teleport,tekk,spawn;
	bool free(Vector2f &vek);
	bool possible(Vector2f &vek);

	//elementy wspierajace wyglad
	string toString(float liczba);
	Font moja_czcionka;

	//Elementy wspieraj¹ce gre
	Vector2i czas_w_grze;
	Chronometer czas_gry;
	Mutex mutex;

	//vektory elementow w grze
	vector<Monster> vector_monster;
	vector<Tower> vector_tower;
	Player gracz;
	void upd_pot();
	void resp_pot();

	//Rysowanie elementow
	void RysujPotwora(RenderWindow &window);
	void RysujWieze(RenderWindow &okno);

	//tekstury elementow
	void WczytajTextPotw();
	void WczytajTextWiezy();
	void WczytajTextWiez();
	Texture *tekstura_potwora, *tekstura_wiezy, *tekstura_wiez;
	Sprite wieze;

	Chronometer zegar;
	int speed_resp;
	int updatemonster;

	void setChoose(Vector2f mouse);
	void resetChoose();

	bool pause(RenderWindow &window);
	void over(Vector2i czas);
	bool exit();
};