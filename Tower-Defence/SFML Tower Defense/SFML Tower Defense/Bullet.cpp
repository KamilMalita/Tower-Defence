#include "Bullet.h"
#include <math.h>

#define M_PI 3.14159265358979323846

Bullet::Bullet(Texture *tekstura, Vector2f pozycja, Vector2f enemy, int rodzaje_wiez)
{
	//obliczanie rotacji dla strzaly w kierunku przeciwnika
	Vector2f norm = enemy - pozycja;
	float rot = atan2(norm.y, norm.x);
	rot = rot * 180.f / M_PI;
	rot += 90;

	//inicjacja statusu
	status = LECI;

	//ustawienie atrybutów sprite
	if (rodzaje_wiez == zwykla)
	{
		sprite.setTexture(*tekstura);
		sprite.setTextureRect(IntRect(0, 0, 16, 48));
		sprite.setOrigin(8, 24);
		sprite.setRotation(rot);
		sprite.setPosition(pozycja);
	}
	else if (rodzaje_wiez == lodowa)
	{
		sprite.setTexture(*tekstura);
		sprite.setTextureRect(IntRect(23, 0, 36, 41));
		sprite.setOrigin(8, 24);
		sprite.setRotation(rot);
		sprite.setPosition(pozycja);
	}
	//ustawienie kierunku lotu pocisku
	XY={ 10.f *(sin(sprite.getRotation() * 3.14f / 180.f)), 10.f *(-cos(sprite.getRotation() * 3.14f / 180.f)) };
}

Bullet::Bullet()
{
}
Bullet::~Bullet()
{
}

void Bullet::fire()
{
	sprite.move(XY.x, XY.y);
}

void Bullet::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sprite);
}

void Bullet::update(vector <Monster> &potwor, int dmg,float freez)
{
	if (wall() == true) return;
	for (int i = 0; i < potwor.size(); i++)
	{
		if (sprite.getGlobalBounds().intersects(potwor[i].bounds()))
		{
			potwor[i].freez(freez);
			potwor[i].hit(dmg);
			status = TRAFIL;
			return;
		}
	}
	fire();
}

int Bullet::getStatus()
{
	return status;
}

bool Bullet::wall()
{
	if (sprite.getPosition().x > WINDOW_X || sprite.getPosition().x<0 ||
		sprite.getPosition().y>WINDOW_Y || sprite.getPosition().y < 0)
	{
		status = TRAFIL;
		return true;
	}
	else return false;
}