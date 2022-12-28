#pragma once

#include "Vector/Vector2Int.hpp"
#include <vector>

class Board
{
public:
	Board();
	Board(const Birb::Vector2Int& dimensions);

	Birb::Vector2Int dimensions;

	/* The number tells the player who has marked the
	 * tile. 0 means empty */
	std::vector<std::vector<int>> tiles;

	void set_move(Birb::Vector2Int tile, int index);
	bool is_legal_move(Birb::Vector2Int tile) const;
	int tile_count() const;

	int check_win() const;
};
