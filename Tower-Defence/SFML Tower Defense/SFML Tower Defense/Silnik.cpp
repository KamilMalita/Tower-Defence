#include "Silnik.h"
#include <Windows.h>
#include<sstream>
#include<math.h>

Silnik::Silnik(RenderWindow &window,int poziom)
{
	czas_w_grze.x = 0;
	if (!moja_czcionka.loadFromFile("data/myfont.ttf"))
	{
		MessageBox(NULL, "Brak czcionki", "ERROR", NULL);
	}

	//wczytanie tekstur elementow 
	WczytajTextPotw();
	WczytajTextWiezy();
	WczytajTextWiez();
	
	updatemonster = poziom;
	//
	gracz.diff(poziom);
	if (poziom == 2)
		poziom = 1;
	else if(poziom==1)
		poziom = 2;
	speed_resp = poziom * 2;

	//wymuszenie klatek okna na 60
	window.setFramerateLimit(60);

	//START LICZENIA CZASU POTWOROW
	zegar.reset();
	czas_gry.reset(true);

	//czas_gry.restart();
	runEngine(window);
	
}


Silnik::~Silnik()
{
}

void Silnik::runEngine(RenderWindow &window)
{
	int tylkoraz=1;
	Texture tek,tele,spaw;
	tek.loadFromFile("data/mapka.png");
	tekk.setTexture(tek);
	tele.loadFromFile("data/teleport.png");
	teleport.setTexture(tele);
	spaw.loadFromFile("data/spawn.png");
	spawn.setTexture(spaw);
	teleport.move(10, 650);
	spawn.setOrigin(15, 25);
	bool menu = false;

	int wiezza = 0;

	///EDITTTT TUTAJ
	//Napisy pomocnicze w grze
	const int ilosc_wyrazow_w_grze = 11;
	Text tekst[ilosc_wyrazow_w_grze];
	string str_napis[5];
	str_napis[0] = "game";
	str_napis[1] = "time";
	str_napis[2] = "score";
	str_napis[3] = "gold";
	str_napis[4] = "life";
	for (int i = 0; i<ilosc_wyrazow_w_grze; i++)
	{
		tekst[i].setFont(moja_czcionka);
		tekst[i].setCharacterSize(72);
		tekst[i].setFillColor(Color(100, 206, 250, 255));
	}
	
	tekst[0].setPosition(1000, 800);
	tekst[1].setPosition(850, 1000);
	tekst[2].setPosition(1000, 725);
	tekst[3].setPosition(1000, 650);
	
	tekst[4].setCharacterSize(120);
	tekst[5].setCharacterSize(50);
	tekst[6].setCharacterSize(50);
	tekst[5].setString(str_napis[2]);
	tekst[6].setString(str_napis[3]);
	tekst[5].setPosition(1040, 100);
	tekst[6].setPosition(1040, 200);

	tekst[7].setCharacterSize(50);
	tekst[8].setCharacterSize(50);
	tekst[7].setPosition(1040, 150);
	tekst[8].setPosition(1040, 250);

	tekst[9].setCharacterSize(50);
	tekst[10].setCharacterSize(50);
	tekst[9].setPosition(1040, 300);
	tekst[9].setString(str_napis[4]);
	tekst[10].setPosition(1040, 350);
	Vector2f mouse;
	/*w sumie to start gry*/while (!menu)
	{
		tekst[10].setString(toString(gracz.get_hp()));
		tekst[7].setString(toString(gracz.get_score()));
		tekst[8].setString(toString(gracz.get_gold()));


		if (czas_gry.getElapsedTime().asSeconds() < 21 && tylkoraz==1)
		{
			if (czas_gry.getElapsedTime().asSeconds() > 0)
			{
				tekst[4].setString("Do startu " + toString(20-(int)czas_gry.getElapsedTime().asSeconds()) + " s");
				tekst[4].setPosition(200, 350);
				float kolor = tekst[4].getFillColor().a;
				kolor -= 1;
				tekst[4].setFillColor(Color(100, 206, 250, kolor));
			}
		}
		else
		{
			zegar.resume();
			tylkoraz--;
		}
		//POKAZYWANIE CZASU W GRZE
		if (czas_w_grze.x == 1 && czas_w_grze.y % 2 == 0 && tekst[1].getPosition().y != 800)
			tekst[1].move(0, -5);
		if (czas_w_grze.x == 1 && czas_w_grze.y % 2 == 0 && tekst[3].getPosition().x != 800)
			tekst[3].move(-5, 0);
		else if (czas_w_grze.x == 1 && czas_w_grze.y % 2 == 0 && tekst[3].getPosition().y != 725)
			tekst[3].move(0, 5);
		if (czas_gry.getElapsedTime().asSeconds() >= 60)
		{
			//tekst[1].setPosition(850, 800);
			float kolor = tekst[1].getFillColor().g;
			kolor -= 20;
			tekst[1].setFillColor(Color(100, kolor, 250));
			if (czas_w_grze.x % 6 ==0)
				tekst[1].setFillColor(Color(100, 206, 250));
			czas_w_grze.x++;
			czas_gry.reset(true);
		}

		int funny = czas_w_grze.y;
		czas_w_grze.y = (int)czas_gry.getElapsedTime().asSeconds();

		//migotanie sekund
		if (funny < czas_w_grze.y)
		{
			if (int i=(int)czas_gry.getElapsedTime().asSeconds() % 6==0 || czas_gry.getElapsedTime().asSeconds() >  59)
				tekst[0].setFillColor(Color(100, 206, 250));
				//tekst[0].setFillColor(Color(0, 255, 0));
			else 
			{
				float kolor = tekst[0].getFillColor().g;
				kolor -= 20;
				tekst[0].setFillColor(Color(100, kolor, 250));
			}

		}

		tekst[0].setString(toString(czas_w_grze.y) + " s");
		tekst[1].setString(toString(czas_w_grze.x) + " m");
		tekst[2].setString(str_napis[1]);
		tekst[3].setString(str_napis[0]);
		//TU SIE ZACZYNA PRAWDZIWY LAJF
		
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyReleased && event.key.code == Keyboard::P && wiezza == 0)
			{
				if(czas_gry.getElapsedTime().asSeconds()>21 && czas_w_grze.x==0)
				zegar.pause();
				czas_gry.pause();
				if (pause(window) == true)
				{
					czas_gry.resume();
					if (czas_gry.getElapsedTime().asSeconds()>21 && czas_w_grze.x==0)
					zegar.resume();
				}
			}
			if (event.type == Event::KeyReleased && event.key.code == Keyboard::Escape && wiezza == 0)
			{
				if (czas_gry.getElapsedTime().asSeconds()>21 && czas_w_grze.x==0)
					zegar.pause();
				czas_gry.pause();
				if (exit() == true)
					menu = true;
				if (czas_gry.getElapsedTime().asSeconds()>21 && czas_w_grze.x == 0)
					zegar.resume();
				czas_gry.resume();
			}
			else if (event.type == Event::KeyReleased && event.key.code == Keyboard::Escape && wiezza == 1)
			{
				wiezza = 0;
				resetChoose();
			}

			cout << mouse.x << " " << mouse.y << endl;
			
			//////////////////////////////////////////////////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////////////////////////////////////////////////
			for (int i = 0; i < vector_tower.size(); i++)
			{
				Vector2f acc_mouse(Mouse::getPosition() - window.getPosition());
				acc_mouse.y -= 37;
				if (event.type == Event::MouseButtonPressed && event.key.code == Mouse::Right && vector_tower[i].bounds().contains(acc_mouse))
				{
					if (vector_tower[i].get_gold() <= gracz.get_gold())
					{
						if(vector_tower[i].upgrade()==true)
							gracz.set_gold(gracz.get_gold() - vector_tower[i].get_gold());
					}
				}
			}
			//////////////////////////////////////////////////
			//////////////////////////////////////////////////
			if (event.type == Event::MouseButtonPressed && event.key.code == Mouse::Left && wieze.getGlobalBounds().contains(mouse) && wiezza == 1)
			{
				Vector2f acc_mouse(Mouse::getPosition() - window.getPosition());
				acc_mouse.y -= 37;
				if (acc_mouse.x<mouse.x && acc_mouse.x>mouse.x - 73 && acc_mouse.y > mouse.y - 24 && acc_mouse.y < mouse.y + 24)
				{
					wiezza = 0;
					vector_tower.push_back(Tower(tekstura_wiezy, zwykla, mouse));
					//cout << mouse.x << " " << mouse.y << " " << vector_tower[0].getPosition().x << " " << vector_tower[0].getPosition().y << endl;
					gracz.set_gold(gracz.get_gold() - 10);
					resetChoose();
				}
				else if (acc_mouse.x > mouse.x && acc_mouse.x<mouse.x + 73 && acc_mouse.y > mouse.y - 24 && acc_mouse.y < mouse.y + 24)
				{
					wiezza = 0;
					vector_tower.push_back(Tower(tekstura_wiezy, lodowa, mouse));
					gracz.set_gold(gracz.get_gold() - 10);
					resetChoose();
				}
				else
				{
					wiezza = 0;
					resetChoose();
				}
			}
			else if (event.type == Event::MouseButtonPressed && event.key.code == Mouse::Right && wiezza == 1)
			{
				wiezza = 0;
				resetChoose();
			}
			else if (event.type == Event::MouseButtonPressed && event.key.code == Mouse::Left && wiezza == 0)
			{

				if (gracz.get_gold() >= 10)
				{
					Vector2f acc_mouse(Mouse::getPosition() - window.getPosition());
					acc_mouse.y -= 37;
					mouse = acc_mouse;
						if (possible(mouse) == true)
						{
							if (free(mouse) == true)
							{
								if (possible(mouse) == true)
								{
									setChoose(mouse);
									wiezza = 1;
								}
							}
						}
				}
			}
			//////////////////////////////////////
			//////////////////////////////////////	
		}
		
		if (gracz.get_hp() <= 0)
		{
			over(czas_w_grze);
			menu = true;
		}

		//RESPIENIE POTWOROW
		resp_pot();

		//update wszystkich potworow
		
		upd_pot();

		//update wszystkich wiezy
		for (int i = 0; i < vector_tower.size(); i++)
		{
				vector_tower[i].update(vector_monster);
		}
		//rysowanie wszystkich elementow
		window.clear();
		window.draw(tekk);
		for (int i = 0; i < ilosc_wyrazow_w_grze; i++)
		{
			if (i == 4)
				continue;
			window.draw(tekst[i]);
		}
		if (czas_gry.getElapsedTime().asSeconds()<21 && tylkoraz == 1)
			window.draw(tekst[4]);
		RysujWieze(window);
		RysujPotwora(window);
		window.draw(spawn);
		window.draw(teleport);
		window.draw(wieze);
		window.display();
	}
}

void Silnik::RysujPotwora(RenderWindow &okno)
{
	for (int i = 0; i < vector_monster.size(); i++)
		okno.draw(vector_monster[i]);
}

void Silnik::RysujWieze(RenderWindow &okno)
{
	for (int i = 0; i < vector_tower.size(); i++)
		okno.draw(vector_tower[i]);
}

void Silnik::WczytajTextPotw()
{
	tekstura_potwora = new Texture;
	if (!tekstura_potwora->loadFromFile("data/Sprites/Monster.png"))
	{
		MessageBox(NULL, "Tekstura potwora siê nie wczyta³a", "ERROR", NULL);
		return;
	}
}

void Silnik::WczytajTextWiezy()
{
	tekstura_wiezy = new Texture;
	if (!tekstura_wiezy->loadFromFile("data/Sprites/wieze.png"))
	{
		MessageBox(NULL, "Tekstura potwora siê nie wczyta³a", "ERROR", NULL);
		return;
	}
	
}

void Silnik::WczytajTextWiez()
{
	tekstura_wiez = new Texture;
	if (!tekstura_wiez->loadFromFile("data/Sprites/wybor.png"))
	{
		MessageBox(NULL, "Tekstura potwora siê nie wczyta³a", "ERROR", NULL);
		return;
	}
	wieze.setTexture(*tekstura_wiez);
	wieze.setTextureRect(IntRect(0, 97, 146, 97));
	wieze.setOrigin(73, 48);
}

string Silnik::toString(float liczba)
{
	stringstream ss;
	//ss.precision(2);
	ss << liczba;
	return ss.str();
}

void Silnik::upd_pot()
{
	int i = 0;
	for (auto& v : vector_monster)
	{
		v.update();
		if (v.getStatus() == 1)
		{
			gracz.set_score(gracz.get_score() + v.get_gold());
			gracz.set_gold(gracz.get_gold() + v.get_gold());
			vector_monster.erase(vector_monster.begin() + i);
			i--;
		}
		else if (v.getStatus() == 2)
		{
			gracz.set_hp(gracz.get_hp() - 1);
			vector_monster.erase(vector_monster.begin() + i);
			i--;
		}
		i++;
	}
}

void Silnik::resp_pot()
{
	
	Time czas_dla_potworow= zegar.getElapsedTime();
	if (gracz.get_lvl() == 2)
	{
		if (czas_dla_potworow.asSeconds() > speed_resp)
		{
			vector_monster.push_back(Monster(tekstura_potwora, 10 * czas_w_grze.x + 1 + 2 * czas_w_grze.x*czas_w_grze.x));
			zegar.reset(true);
		}
	}
	else if (gracz.get_lvl() == 1)
	{
		if (czas_dla_potworow.asSeconds() > speed_resp)
		{
			vector_monster.push_back(Monster(tekstura_potwora, 10 * czas_w_grze.x + 1));
			zegar.reset(true);
		}
	}
}

bool Silnik::possible(Vector2f &mouse)
{
	if (mouse.x < 850 && mouse.y < 150 && mouse.y>80)
	{
		mouse.y = 125;
		return true;
	}
	else if (mouse.x > 990 && mouse.y<640 && mouse.y>40 && mouse.x<1100 )
	{
		mouse.x = 1010;
		return true;
	}
	else if (mouse.y > 260 && mouse.y < 340 && mouse.x>180)
	{
		mouse.y = 310;
		return true;
	}
	else if (mouse.y > 465 && mouse.y < 545 && mouse.x < 820)
	{
		mouse.y = 505;
		return true;
	}
	else if (mouse.y > 650 && mouse.y < 800 && mouse.x > 300 && mouse.x < 1000)
	{
		mouse.y = 695;
		return true;
	}
	else if (mouse.y >= 150 && mouse.y <= 465 && mouse.x < 64)
	{
		mouse.x = 30;
		return true;
	}
}


void Silnik::setChoose(Vector2f mouse)
{
	wieze.move(mouse);
	wieze.setPosition(mouse);
	wieze.setTextureRect(IntRect(0, 0, 146, 97));
}

void Silnik::resetChoose()
{
	
	wieze.move(1400,1400);
	wieze.setPosition(1400,1400);
	wieze.setTextureRect(IntRect(0, 97, 146, 97));
}

bool Silnik::pause(RenderWindow &window)
{
	//RenderWindow win(VideoMode(300, 300), "Pause", Style::None);
	Text tekst;
	tekst.setFont(moja_czcionka);
	tekst.setCharacterSize(72);
	tekst.setFillColor(Color(135, 206, 250, 255));
	tekst.setPosition(270, 400);
	tekst.setString("Press P to unpause");
	Event event;
	while (true)
	{
		
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyReleased && event.key.code == Keyboard::P)
			{
				//win.close();
				return true;
			}
		}
		window.clear();
		window.draw(tekk);
		RysujWieze(window);
		RysujPotwora(window);
		window.draw(spawn);
		window.draw(teleport);
		window.draw(tekst);
		window.display();
	}
}

bool Silnik::free(Vector2f &vek)
{
	int kon, kon2;
	for (int i = 0; i < vector_tower.size(); i++)
	{
		if ((vector_tower[i].getPosition().x - 0.5*vector_tower[i].bounds().width) > vek.x
			&&	(vector_tower[i].getPosition().x -1.5*vector_tower[i].bounds().width) < vek.x
			&& vek.y==vector_tower[i].getPosition().y)
		{
			vek.x = vector_tower[i].getPosition().x - vector_tower[i].bounds().width;
			if (boom(vek) == false)return false;
			return true;
		}
		 if ((vector_tower[i].getPosition().x + 0.5*vector_tower[i].bounds().width) < vek.x
			&& (vector_tower[i].getPosition().x + 1.5*vector_tower[i].bounds().width) > vek.x
			&& vek.y == vector_tower[i].getPosition().y)
		{
			vek.x = vector_tower[i].getPosition().x + vector_tower[i].bounds().width;
			if (boom(vek) == false)
				return false;
			return true;
		}
	}
	boom(vek);
}


bool Silnik::boom(Vector2f wek)
{
	for (int k = 0; k < vector_tower.size(); k++)
	{
		if (vector_tower[k].bounds().contains(wek))
			return false;
	}
	return true;
}

void Silnik::over(Vector2i czas)
{
	Texture teks;
	teks.loadFromFile("data/over.png");
	Sprite *tek = new Sprite;
	tek->setTexture(teks);
	RenderWindow win(VideoMode(600, 450), "Pause", Style::Close);
	Text tekst[6];
	for (int i = 0; i <= 5; i++)
	{
		tekst[i].setFont(moja_czcionka);
		tekst[i].setCharacterSize(50);
		tekst[i].setFillColor(Color(100, 206, 250, 255));
	}
	tekst[0].setFillColor(Color::Black);
	tekst[0].setCharacterSize(60);
	tekst[0].setPosition(30, 50);
	tekst[0].setString("congratulations");
	tekst[1].setPosition(360, 250);
	tekst[1].setString(toString(czas.x)+" : "+toString(czas.y));
	tekst[2].setPosition(270, 200);
	tekst[2].setString("Time in Game");
	tekst[3].setPosition(79,250);
	tekst[3].setString("Level");
	if (gracz.get_lvl() == 1)
	{
		tekst[4].setPosition(87, 305);
		tekst[4].setString("Easy");
	}
	else if (gracz.get_lvl() == 2)
	{
		tekst[4].setPosition(87, 305);
		tekst[4].setString("Hard");
	}
	tekst[5].setPosition(150, 360);
	tekst[5].setString("Back to Menu");
	Event event;
	while (true)
	{
		Vector2f mouse(Mouse::getPosition() - win.getPosition());
		mouse += {0, -37};
		while (win.pollEvent(event))
		{
			if (event.type == Event::KeyReleased && event.key.code == Keyboard::P)
			{
				win.close();
				return;
			}
			if (tekst[5].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				win.close();
				return;
			}
		}
			if (tekst[5].getGlobalBounds().contains(mouse))
				tekst[5].setFillColor(Color(135, 206, 100, 255));
			else tekst[5].setFillColor(Color(100, 150, 250, 255));
		win.clear();
		win.draw(*tek);
		for (int i = 0; i <= 5; i++)
		{
			win.draw(tekst[i]);
		}
		win.display();
	}
}

bool Silnik::exit()
{
	Texture teks;
	teks.loadFromFile("data/over.png");
	Sprite *tek = new Sprite;
	tek->setTexture(teks);
	RenderWindow win(VideoMode(600, 450), "Pause", Style::Close);
	Event event;
	Text tekst[3];
	for (int i = 0; i <= 2; i++)
	{
		tekst[i].setFont(moja_czcionka);
		tekst[i].setCharacterSize(50);
		tekst[i].setFillColor(Color(100, 206, 250, 255));
	}
	tekst[0].setPosition(275, 205);
	tekst[0].setString("resume");
	tekst[1].setPosition(305, 300);
	tekst[1].setString("exit");
	tekst[2].setFillColor(Color::Black);
	tekst[2].setCharacterSize(60);
	tekst[2].setPosition(20, 50);
	tekst[2].setString("do you Want Exit?");
	while (true)
	{
		Vector2f mouse(Mouse::getPosition() - win.getPosition());
		mouse += {0, -37};
		while (win.pollEvent(event))
		{
			if (tekst[0].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				win.close();
				return false;
			}
			else if (tekst[1].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				win.close();
				return true;
			}
		}
		for (int i = 0; i < 2; i++)
		{
			if (tekst[i].getGlobalBounds().contains(mouse))
				tekst[i].setFillColor(Color(135, 206, 100, 255));
			else tekst[i].setFillColor(Color(100, 206, 250, 255));
		}
		win.clear();
		win.draw(*tek);
		for (int i = 0; i < 3; i++)
		{
			win.draw(tekst[i]);
		}
		win.display();
	}
}