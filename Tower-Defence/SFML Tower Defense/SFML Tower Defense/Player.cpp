#include "Player.h"



Player::Player()
{
	set_gold(0);
	set_hp(0);
	set_score(0);
}


Player::~Player()
{
}

void Player::set_score(int n)
{
	score = n;
}

int Player::get_score()
{
	return score;
}

void Player::diff(int n)
{
	if (n == 1)
	{
		set_gold(1000);
		set_hp(300);
		set_lvl(1);
	}
	else
	{
		set_lvl(2);
		set_gold(100);
		set_hp(30);
	}
}

void Player::set_lvl(int lvl)
{
	level = lvl;
}
int Player::get_lvl()
{
	return level;
}