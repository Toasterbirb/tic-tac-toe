#pragma once

#include "Player.hpp"
#include <string>

class Human : public Player
{
public:
	Human();
	Human(const std::string& name, Board* board, int index);
	Birb::Vector2Int MakeMove(Birb::Vector2Int tile) override;
};
