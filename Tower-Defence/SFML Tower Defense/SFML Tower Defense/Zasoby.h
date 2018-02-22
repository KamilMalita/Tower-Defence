#pragma once
class Zasoby
{
private:
	int gold;
	int hp;
	int dmg;
	
public:
	void set_gold(int n);
	int get_gold();

	void set_hp(int n);
	int get_hp();

	void set_dmg(int n);
	int get_dmg();

	void atak(Zasoby &temp);
};

