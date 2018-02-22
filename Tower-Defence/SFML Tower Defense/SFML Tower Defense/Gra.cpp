#include "Gra.h"

Gra::Gra()
{
	
	tryb = KONIEC;
	if (!moja_czcionka.loadFromFile("data/myfont.ttf"))
	{
		MessageBox(NULL, "Brak czcionki", "ERROR", NULL);
	}
	tryb = MENU;
}


Gra::~Gra()
{
}

void Gra::startGra()
{
	while (tryb != KONIEC)
	{
		switch (tryb)
		{
		case TrybGry::MENU:
			menu();
			break;
		case TrybGry::GRA_LATWA:
			single(1);
			break;
		case TrybGry::GRA_TRUDNA:
			single(2);
			break;
		}
	}
}

void Gra::menu()
{
	RenderWindow okno(VideoMode(WINDOW_X, WINDOW_Y), "TOWER DEFENSE", Style::Close);
	Texture tek;
	tek.loadFromFile("data/krzeslo.png");
	Sprite tekk;
	tekk.setTexture(tek);
	Text tytul("Tower Defense", moja_czcionka, 150);
	tytul.setStyle(Text::Bold);
	tytul.setFillColor(Color::Black);
	tytul.setPosition(WINDOW_X / 2 - tytul.getGlobalBounds().width / 2, 50);
	const int ilosc_wyrazow_w_menu = 2;
	//Text tekst[ilosc_wyrazow_w_menu];
	string wyrazy_w_menu[] = { "Play!","Exit" };
	for (int i = 0; i < ilosc_wyrazow_w_menu; i++)
	{
		tekst[i].setFont(moja_czcionka);
		tekst[i].setCharacterSize(65);
		tekst[i].setString(wyrazy_w_menu[i]);
		tekst[i].setPosition((WINDOW_X / 2 - tekst[i].getGlobalBounds().width / 2), 375 + 1.5*i * 120);
	}
	int graj = 2;
	while (tryb == MENU)
	{
		Vector2f ifwindow{ 20,20 };
		Vector2f mouse(Mouse::getPosition()-okno.getPosition());
		mouse += {0, -37};
		
		while (okno.pollEvent(event))
		{
			if (graj == 2 && ((event.type == Event::Closed || event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) ||
				(tekst[1].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)))
				tryb = KONIEC;
			else if ((graj == 2 && tekst[0].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left))
			{
				graj = 1;
				trudnosc();
			}
			else if ((graj == 1 && tekst[0].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left))
			{
				graj = 0;
				tryb=GRA_LATWA;
			}
			else if ((graj == 1 && tekst[1].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left))
			{
				graj = 0;
				tryb = GRA_TRUDNA;
			}
		}
		for (int i = 0; i < ilosc_wyrazow_w_menu; i++)
		{
			if (tekst[i].getGlobalBounds().contains(mouse))
				tekst[i].setFillColor(Color(135, 206, 100, 255));
			else tekst[i].setFillColor(Color(100, 206, 250, 255));
		}
		okno.clear();
		okno.draw(tekk);
		okno.draw(tytul);
		for (int i = 0; i < ilosc_wyrazow_w_menu; i++)
			okno.draw(tekst[i]);
		okno.display();
	}
}

void Gra::trudnosc()
{
	Vector2f posun{ 20,0 };
	tekst[0].setPosition(tekst[0].getPosition() + posun);
	tekst[0].setString("Easy");
	tekst[1].setString("Hard");
}

void Gra::single(int poziom)
	{
	RenderWindow okno1(VideoMode(WINDOW_X, WINDOW_Y), "TOWER DEFENSE", Style::Close);
	Silnik silnik(okno1,poziom);
	menu();
	tryb = MENU;
	}