#pragma once

#include "Player.hpp"
#include "Random.hpp"
#include "Vector/Vector2Int.hpp"
#include <string>
#include <vector>

class Bot : public Player
{
public:
	Bot();
	Bot(const std::string& name, Board* board, int index, int player_count);
	Birb::Vector2Int MakeMove(Birb::Vector2Int tile) override;

private:
	std::vector<Birb::Vector2Int> find_legal_moves(Board* board);
	Birb::Random rand;
	int player_count;
};
