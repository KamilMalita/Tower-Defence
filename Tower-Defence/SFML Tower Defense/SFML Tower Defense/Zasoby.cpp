#include "Zasoby.h"

#include <iostream>
using namespace std;

int Zasoby::get_dmg()
{
	return dmg;
}

int Zasoby::get_hp()
{
	return hp;
}

int Zasoby::get_gold()
{
	return gold;
}

void Zasoby::atak(Zasoby &temp)
{
	temp.hp = temp.hp - temp.dmg;
	cout << "Wywolano ZASOBY ATAK";
}

void Zasoby::set_gold(int n)
{
	gold = n;
}

void Zasoby::set_hp(int n)
{
	hp = n;
}

void Zasoby::set_dmg(int n)
{
	dmg = n;
}