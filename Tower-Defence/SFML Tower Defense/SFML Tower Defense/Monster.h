#pragma once
#include <vector>
#include <iostream>
#include "Sys.h"
#include "Zasoby.h"
#include <Chronometer.hpp>
using namespace sftools;
using namespace std;
using namespace sf;
class Monster : public Drawable,public Transformable, public Zasoby
{
	Sprite sprite;
public:
	Monster();
	Monster(Texture *texture,int upgrade);
	~Monster();
	
	Vector2f getPosition();
	FloatRect bounds();

	int getStatus();
	void update();
	void freez(float freez);
	void hit(int ile);
protected:
	enum StatusGry { IDZ, ZGIN,META, LEWO, PRAWO, DOL, GORA };
	
private:
	//elementy zwiazane z ruchem potwora
	Clock anim;
	Chronometer slow;
	size_t frame;

	//status potwora
	StatusGry status;
	float speed;

	//metoda nadpisana do rysowania
	virtual void draw(sf::RenderTarget &target, RenderStates states)const;
	
	//metody u¿ywane w klasie
	void CreateText(Texture *texture);
	void road();
	void go();
	void anim_chodzenia();
};
