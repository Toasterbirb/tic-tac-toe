#pragma once

#include "Board.hpp"
#include "Color.hpp"
#include <string>

class Player
{
public:
	enum PlayerType
	{
		Human, Bot
	};

	Player();
	std::string name;
	Board* board;
	int index;
	Birb::Color color;

	PlayerType type;

	/* Returns true when the move has been finished */
	virtual Birb::Vector2Int MakeMove(Birb::Vector2Int tile = {-1, -1}) = 0;
};
