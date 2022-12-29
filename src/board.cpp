#include "Board.hpp"
#include "Vector/Vector2Int.hpp"
#include <vector>

using namespace Birb;

Board::Board()
{}

Board::Board(const Vector2Int& dimensions)
:dimensions(dimensions)
{
	/* Allocate the board tiles */
	tiles = std::vector<std::vector<int>>(dimensions.x);
	for (size_t i = 0; i < tiles.size(); ++i)
		tiles[i] = std::vector<int>(dimensions.y);

	/* Set all tiles to 0 */
	reset();
}

void Board::set_move(Vector2Int tile, int index)
{
	/* Check if the move is legal */
	if (is_legal_move(tile))
		tiles[tile.x][tile.y] = index;
}

bool Board::is_legal_move(Vector2Int tile) const
{
	return (tiles[tile.x][tile.y] == 0);
}

int Board::tile_count() const
{
	return dimensions.x * dimensions.y;
}

int Board::check_win() const
{
	/* FIXME: this only works with the winnin condition
	 * of 3 in a row */

	/* Check vertical lines */
	for (int i = 0; i < dimensions.x; ++i)
	{
		int player = 0;
		int line = 0;
		int counter = 0;
		for (int j = 0; j < dimensions.y; ++j)
		{
			if (player == 0 || counter == 0)
			{
				player = tiles[i][j];

				if (player != 0)
					counter++;
			}
			else if (counter > 0 && tiles[i][j] == player)
			{
				counter++;
			}
			else
			{
				counter = 0;
			}

			if (counter >= 3)
			{
				return player;
			}
		}
	}

	/* Check for horizontal lines */
	for (int i = 0; i < dimensions.y; ++i)
	{
		int player = 0;
		int line = 0;
		int counter = 0;
		for (int j = 0; j < dimensions.x; ++j)
		{
			if (player == 0 || counter == 0)
			{
				player = tiles[j][i];

				if (player != 0)
					counter++;
			}
			else if (counter > 0 && tiles[j][i] == player)
			{
				counter++;
			}
			else
			{
				counter = 0;
			}

			if (counter >= 3)
			{
				return player;
			}
		}
	}

	/* Check for diagonal lines left to right */
	for (int i = 0; i < dimensions.x - 2; ++i)
	{
		for (int j = 0; j < dimensions.y - 2; ++j)
		{
			int player = tiles[i][j];
			if (player == 0)
				continue;

			if (tiles[i + 1][j + 1] == player
				&& tiles[i + 2][j + 2] == player)
			{
				return player;
			}
		}
	}

	/* Check for diagonal lines right to left */
	for (int i = dimensions.x - 1; i > 1; --i)
	{
		for (int j = 0; j < dimensions.y - 2; ++j)
		{
			int player = tiles[i][j];
			if (player == 0)
				continue;

			if (tiles[i - 1][j + 1] == player
				&& tiles[i - 2][j + 2] == player)
			{
				return player;
			}
		}
	}

	return 0;
}

void Board::reset()
{
	/* Set all tiles to zero */
	for (int i = 0; i < dimensions.x; ++i)
		for (int j = 0; j < dimensions.y; ++j)
			tiles[i][j] = 0;
}
