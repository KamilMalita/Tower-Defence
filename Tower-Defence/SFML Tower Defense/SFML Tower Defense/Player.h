#pragma once
#include "Zasoby.h"
class Player :
	public Zasoby
{
	int score;
	int level;
	void set_lvl(int lvl);
public:
	int get_lvl();
	void set_score(int n);
	int get_score();
	Player();
	~Player();
	void diff(int n);
};

