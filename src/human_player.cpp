#include "HumanPlayer.hpp"

using namespace Birb;

Human::Human() {}

Human::Human(const std::string& name, Board* board, int index)
{
	this->name 	= name;
	this->board = board;
	this->index = index;
	this->type 	= Player::PlayerType::Human;
}

Vector2Int Human::MakeMove(Vector2Int tile)
{
	/* Player hasn't made up their mind yet */
	if (tile == Vector2Int( -1, -1 ))
		return { -1, -1 };

	/* Check if the move is legal */
	if (!board->is_legal_move(tile))
		return { -1, -1 };

	/* Set the move */
	board->tiles[tile.x][tile.y] = this->index;

	return tile;
}
