#pragma once

#include "Monster.h"
#include "Sys.h"

using namespace std;
using namespace sf;
class Bullet:public Drawable,Transformable
{
public:
	//metody uzywane na zewnatrz
	Bullet();
	Bullet(Texture *tekstura, Vector2f pozycja, Vector2f enemy, int rodzaje_wiez);
	~Bullet();

	void update( vector <Monster> &potwor, int dmg, float freez);
	int getStatus();
	virtual void draw(RenderTarget &target, RenderStates states) const override;
private:
	Sprite sprite;
	//XY wektor zainicjowany tym gdzie leci pocisk
	Vector2f XY;

	//wiadomo
	enum StatusNaboju { LECI, TRAFIL };
	StatusNaboju status;
	
	//metody u¿ywane w klasie
	void fire();
	bool wall();
};

