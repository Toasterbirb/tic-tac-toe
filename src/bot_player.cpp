#include "Vector/Vector2Int.hpp"
#include <vector>
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include "BotPlayer.hpp"

using namespace Birb;

Bot::Bot() {}

Bot::Bot(const std::string& name, Board* board, int index, int player_count)
{
	this->name 	= name;
	this->board = board;
	this->index = index;
	this->type 	= Player::PlayerType::Bot;
	this->player_count = player_count;
}

Vector2Int Bot::MakeMove(Vector2Int tile)
{
	/* Ignore the given tile position since the
	 * bot makes up its own mind ;) */

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

	/* Go trough all of the legal moves */
	int sel_tile = -1;
	for (size_t i = 0; i < legal_moves.size(); ++i)
	{
		/* Create a copy of the current board */
		Board temp_board = *board;

		/* Try a move */
		temp_board.set_move(legal_moves[i], this->index);

		/* Check if the move would result in a win */
		int winner = temp_board.check_win();

		/* Check if the bot was a winner */
		if (winner == this->index)
		{
			sel_tile = i;
			break;
		}
	}

	/* Find any winning moves that other players might have and
	 * make sure to block them */
	if (sel_tile == -1)
	{
		for (int j = 1; j < player_count; ++j)
		{
			for (size_t i = 0; i < legal_moves.size(); ++i)
			{
				/* Create a copy of the current board */
				Board temp_board = *board;

				/* Try a move */
				temp_board.set_move(legal_moves[i], j);

				/* Check if the move would result in a win */
				int winner = temp_board.check_win();

				/* Check if the player was a winner */
				if (winner == j)
				{
					sel_tile = i;
				}
			}
		}
	}

	/* Pick a random legal move if no good moves were found */
	if (sel_tile == -1)
		sel_tile = rand.RandomInt(0, legal_moves.size() - 1);

	board->set_move(legal_moves[sel_tile], index);
	return legal_moves[sel_tile];
}
