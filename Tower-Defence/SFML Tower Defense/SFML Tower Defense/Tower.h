#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>
#include "Zasoby.h"
#include "Sys.h"
#include "Monster.h"
#include "Bullet.h"
using namespace sf;
using namespace std;
class Tower:public Zasoby, public Drawable, public Transformable
{
private:
	int licznik;
	//zegal odliczajacy czas strzelania
	Clock wystrzal; 

	//atrybuty
	int range;
	float attackspeed;

	//zwiazane z pociskami i strzelaniem
	void update_pociski(vector <Monster> &potwor);
	vector<Bullet> pociski;

	//metoda do kontruktora ustawiajaca sprite, rangecircle-kolowyzasieg
	void CreateText(Texture *texture, Vector2f pozycja,int wieza);
	Sprite sprite;
	CircleShape rangecircle;

	int type;
	float freeze;

	//wczytanie tekstury pocisku,zmienna pocisku
	void TextBullet();
	Texture *pocisk;

	//metoda sprawdza czy potwor w zasiegu
	bool kolizja(vector <Monster> &potwor);
public:
	void set_freeze(float fr);
	float get_freeze();
	//jedyne metody mozliwe do uzycia z zewnatrz
	Tower(Texture *texture,int rodzaj_wiezy,Vector2f pozycja);
	Tower();
	~Tower();
	
	Vector2f getPosition();
	FloatRect bounds();
	bool upgrade();
	void update(vector <Monster> &potwor);
	virtual void draw(RenderTarget &target, RenderStates states) const override;
};

