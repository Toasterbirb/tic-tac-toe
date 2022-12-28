#include <vector>
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include "BotPlayer.hpp"

using namespace Birb;

Bot::Bot() {}

Bot::Bot(const std::string& name, Board* board, int index)
{
	this->name 	= name;
	this->board = board;
	this->index = index;
	this->type 	= Player::PlayerType::Bot;
}

Vector2Int Bot::MakeMove(Vector2Int tile)
{
	/* Ignore the given tile position since the
	 * bot makes up its own mind ;) */

	/* Choose a random legal move for now */

	/* Find all legal moves */
	std::vector<Vector2Int> legal_moves;
	for (int i = 0; i < board->dimensions.x; ++i)
	{
		for (int j = 0; j < board->dimensions.y; ++j)
		{
			Vector2Int pos(i, j);
			if (board->is_legal_move(pos))
				legal_moves.push_back(pos);
		}
	}

	if (legal_moves.size() == 0)
	{
		/* No moves left */
		return { -1, -1 };
	}

	/* Pick a random legal move */
	int sel_tile = rand.RandomInt(0, legal_moves.size() - 1);
	board->tiles[legal_moves[sel_tile].x][legal_moves[sel_tile].y] = this->index;

	return legal_moves[sel_tile];
}
