#include "Wave.h"
#include <Windows.h>


Wave::Wave()
{
	WczytajTextPotw();
	zegar.restart();
	licznik = 0;
}


Wave::~Wave()
{
}

void Wave::WczytajTextPotw()
{
	tekstura_potwora = new Texture;
	if (!tekstura_potwora->loadFromFile("data/Sprites/champion.png"))
	{
		MessageBox(NULL, "Tekstura potwora siê nie wczyta³a", "ERROR", NULL);
		return;
	}
}

void Wave::Numer1()
{
	if (licznik < 10)
	{
		Time czas_dla_potworow = zegar.getElapsedTime();
		if (czas_dla_potworow.asSeconds() > 1)
		{
			potwory.push_back(Monster(tekstura_potwora));
			zegar.restart();
		}
		licznik++;
	}
	int i = 0;
	for (auto& v : potwory)
	{
		v.update();
		if (v.getStatus() == false)
		{
			potwory.erase(potwory.begin() + i);
			i--;
		}
		i++;
	}
}


void Wave::Numer1Wys(RenderWindow &okno)
{
	for (int i = 0; i < potwory.size(); i++)
		okno.draw(potwory[i]);
}

void Wave::draw(sf::RenderTarget &target, sf::RenderStates state) const {
	
	for (int i = 0; i < potwory.size(); i++)
		target.draw(potwory[i]);
}
