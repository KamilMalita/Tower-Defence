#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Monster.h"
#include <iostream>
using namespace std;
using namespace sf;
class Wave:public Monster, public Drawable
{
	Texture *tekstura_potwora;
	vector <Monster> potwory;
	void WczytajTextPotw();
	Clock zegar;
	int licznik;
public:
	virtual void draw(sf::RenderTarget &, sf::RenderStates) const;
	bool wave_spawn();

	Wave();
	~Wave();

	void Numer1();
	void Numer1Wys(RenderWindow &okno);
};

