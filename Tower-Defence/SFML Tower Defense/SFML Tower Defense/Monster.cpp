#include "Monster.h"
#include <Windows.h>
#include <math.h>
#include <iostream>

using namespace sf;
void Monster::CreateText(Texture *texture)
{
	sprite.setTexture(*texture);
	sprite.setTextureRect(IntRect(12, 44, WIELK_MONSTER[0], WIELK_MONSTER[1]));
	sprite.setOrigin(WIELK_MONSTER[0]/2,WIELK_MONSTER[1]/2);
	sprite.setPosition(START_POINT[0], START_POINT[1]);
}
Monster::Monster()
{
	
}
Monster::Monster(Texture *texture,int upgrade)
{
	CreateText(texture);
	

	status = PRAWO;
	
	frame = 0;
	speed = 0.5;
	set_hp(upgrade*5);
	set_gold(5);

	frame = 0;
	slow.reset(true);
	slow.add(seconds(1));
	anim.restart();
}


Monster::~Monster()
{
}

void Monster::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(sprite);
}

void Monster::go()
{
	anim_chodzenia();
	road();
	switch (status)
	{
	case StatusGry::LEWO:
		sprite.move(speed*-1, 0);
		break;
	case StatusGry::PRAWO:
		sprite.move(speed*1, 0);
		break;
	case StatusGry::GORA:
		sprite.move(0, speed*-1);
		break;
	case StatusGry::DOL:
		sprite.move(0, speed*1);
		break;
	}
}

void Monster::update()
{
	
	if(status!=ZGIN)
	{
		if (slow.getElapsedTime().asSeconds() > 1)
			speed = 0.5;
		go();
	}
}

void Monster::anim_chodzenia()
{
	if (anim.getElapsedTime() > seconds(0.2f))
	{
		if (frame < 2 /*liczba klatek animacji*/)
			frame++;
		else
			frame = 0; //zapetlanie animacji

		sprite.setTextureRect(IntRect(12+frame * WIELK_MONSTER[0], 44, WIELK_MONSTER[0], WIELK_MONSTER[1]));
		//x, y, szerokosc, wysokosc
		anim.restart();
	}
}

void Monster::road()
{
	if (sprite.getPosition().x >= 900 && sprite.getPosition().y == 30)
		status = DOL;
	else if (sprite.getPosition().x >= 898 && sprite.getPosition().x <= 902 && sprite.getPosition().y >= 202 && sprite.getPosition().y <=204)
		status = LEWO;
	else if (sprite.getPosition().x <= 100 && sprite.getPosition().y >= 198 && sprite.getPosition().y <=202)
		status = DOL;
	else if (sprite.getPosition().x <= 100 && sprite.getPosition().y >= 398 && sprite.getPosition().y<=402)
		status = PRAWO;
	else if (sprite.getPosition().x <= 902 && sprite.getPosition().x >= 898 && sprite.getPosition().y >= 398 && sprite.getPosition().y <= 402)
		status = DOL;
	else if (sprite.getPosition().x >= 898 && sprite.getPosition().x<=902 && sprite.getPosition().y >= 598 && sprite.getPosition().y <=602)
		status = LEWO;
	else if (sprite.getPosition().x <= 150 && sprite.getPosition().y <= 602 && sprite.getPosition().y >=598)
		status = DOL;
	else if (sprite.getPosition().x <= 150 && sprite.getPosition().y <= 802 && sprite.getPosition().y >=798)
		status = META;
}

int Monster::getStatus()
{
	if (get_hp() <= 0)
		status = ZGIN;
	if (status == ZGIN)
		return 1;
	else if (status == META)
		return 2;
	else return 0;
}

void Monster::hit(int ile)
{
	set_hp(get_hp() - ile);
}
void Monster::freez(float freez)
{
	speed = 0.5 / freez;
	slow.reset(true);
}
FloatRect Monster::bounds()
{
	return sprite.getGlobalBounds();
}

Vector2f Monster::getPosition()
{
	return sprite.getPosition();
}