#pragma once

#include "Player.hpp"
#include "Random.hpp"
#include <string>

class Bot : public Player
{
public:
	Bot();
	Bot(const std::string& name, Board* board, int index);
	Birb::Vector2Int MakeMove(Birb::Vector2Int tile) override;

private:
	Birb::Random rand;
};
