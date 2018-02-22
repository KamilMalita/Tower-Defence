#include "Tower.h"
#include "Windows.h"
#include <math.h>

void Tower::CreateText(Texture *texture,Vector2f pozycja,int wieza)
{
	if (wieza == zwykla)
	{
		type = zwykla;
		TextBullet();
		sprite.setTexture(*texture);
		sprite.setTextureRect(IntRect(60, 390, 60, 86));
		sprite.setOrigin(39, 48);
		//sprite.setPosition(0,0);
		sprite.move(pozycja);
	}
	else if(wieza==lodowa)
	{
		type = lodowa;
		TextBullet();
		sprite.setTexture(*texture);
		sprite.setTextureRect(IntRect(86, 150, 70, 95));
		sprite.setOrigin(39, 50);
		//sprite.setPosition(0,0);
		sprite.move(pozycja);
	}
}
Tower::Tower()
{
	
	
}
Tower::Tower(Texture *texture,int rodzaj_wiezy, Vector2f pozycja)
{
	if (rodzaj_wiezy == zwykla)
	{
		set_freeze(1);
		set_dmg(2);
		set_gold(10);
		range = 100;
		attackspeed = 3;
		CreateText(texture, pozycja,zwykla);
	}
	if (rodzaj_wiezy == lodowa)
	{
		set_freeze(1.5);
		set_dmg(1);
		set_gold(10);
		range = 100;
		attackspeed = 3;
		CreateText(texture, pozycja,lodowa);
	}
	licznik = 0;
	rangecircle.setRadius(range);
	rangecircle.setPosition(sprite.getPosition());
	rangecircle.setOrigin(100, 100);
	rangecircle.move(0,0);
	rangecircle.setFillColor(Color::Blue);
	//resetowanie timera dla wystrzalow
	wystrzal.restart();
}


Tower::~Tower()
{
}

void Tower::update(vector <Monster> &potwory)
{
	kolizja(potwory);
	if (pociski.size() >= 0)
		update_pociski(potwory);
}


bool Tower::upgrade() 
{
	if (licznik < 5)
	{
		licznik++;
		if (licznik == 5)
		{
			if (type == zwykla)
				sprite.setTextureRect(IntRect(148, 392, 60, 86));
			else if(type==lodowa)
				sprite.setTextureRect(IntRect(181, 150, 70, 95));
		}
		if (type == zwykla)
		{
			set_dmg(1.5*get_dmg());
			range += 0.5*range;
			attackspeed = attackspeed - 0.5;
			set_gold(1.1*get_gold());
			rangecircle.setRadius(range);
			rangecircle.setPosition(sprite.getPosition());
			rangecircle.setOrigin(range, range);
			rangecircle.move(0, 0);
			return true;
		}
		else if (type == lodowa)
		{
			set_freeze(get_freeze() + 0.2);
			set_dmg(1.5*get_dmg());
			range += 0.5*range;
			attackspeed = attackspeed - 0.5;
			set_gold(1.1*get_gold());
			rangecircle.setRadius(range);
			rangecircle.setPosition(sprite.getPosition());
			rangecircle.setOrigin(range, range);
			rangecircle.move(0, 0);
			return true;
		}
	}
	else return false;
}


void Tower::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sprite);
	for (int i = 0; i < pociski.size(); i++)
		pociski[i].draw(target, states);
	//target.draw(rangecircle);
}

bool Tower::kolizja(vector <Monster> &potwor)
{
	
	for (int i = 0; i < potwor.size(); i++)
	{

		Time czy_juz = wystrzal.getElapsedTime();
		if (czy_juz.asSeconds() > attackspeed) {
			if (rangecircle.getGlobalBounds().intersects(potwor[i].bounds()))
			{
				pociski.push_back(Bullet(pocisk, sprite.getPosition() , potwor[i].getPosition(),type));
				wystrzal.restart();
				return true;
			}
		}
	}
	return false;
}

void Tower::update_pociski(vector <Monster> &potwor)
{
	int i = 0;
	for (auto& v : pociski)
	{
		v.update( potwor, get_dmg(),get_freeze() );
		if (v.getStatus() == 1)
		{
			pociski.erase(pociski.begin() + i);
			i--;
		}
		i++;
	}
}

void Tower::TextBullet()
{

	pocisk = new Texture;
	if (!pocisk->loadFromFile("data/Sprites/arrow.png"))
	{
		MessageBox(NULL, "Tekstura potwora siê nie wczyta³a", "ERROR", NULL);
		return;
	}
}

FloatRect Tower::bounds()
{
	return sprite.getGlobalBounds();
}

Vector2f Tower::getPosition()
{
	return sprite.getPosition();
}
void Tower::set_freeze(float fr)
{
	freeze = fr;
}
float Tower::get_freeze()
{
	return freeze;
}