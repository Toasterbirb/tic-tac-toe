#include <vector>
#include "BotPlayer.hpp"
#include "Player.hpp"
#include "Birb2D.hpp"
#include "Board.hpp"
#include "HumanPlayer.hpp"
#pragma GCC diagnostic ignored "-Wunused-parameter"


using namespace Birb;

/* Function declarations */
static void start(Game& game);
static void input(Game& game);
static void update(Game& game);
static void render(Game& game);
static void post_render();
static void cleanup();

/* Game variables */
bool game_over = false;
Board board;
int current_player = 0;
std::vector<Player*> players;

Human human("Player", &board, 1);
//Human human2("Player 2", &board, 2);
Bot bot("Mr. Robot", &board, 2);

Vector2Int human_move = { -1, -1 };

Scene board_scene;
#define TILE_SIZE 128
Color tile_colors[2] = {
	Colors::Nord::PolarNight::nord1,
	Colors::Nord::PolarNight::nord2
};
std::vector<std::vector<Entity>> board_tile_entities;

int main(void)
{
	Game::WindowOpts window_options;
	window_options.title 				= "Game";
	window_options.window_dimensions 	= { 1280, 720 };
	window_options.refresh_rate 		= 75;
	window_options.resizable 			= false;

	Game game_loop(window_options, start, input, update, render);

	/* Optional extra functions */
	game_loop.post_render = post_render;
	game_loop.cleanup = cleanup;

	/* Start the game loop */
	game_loop.Start();

	return 0;
}

/* start() is called before the game loop starts.
 * Useful for doing stuff that will only run once before
 * the game starts */
void start(Game& game)
{
	//Splash splash(*game.window);
	//splash.Run();

	/* Create the board */
	board = Board({ 9, 5 });

	/* Initialize the players */
	players = std::vector<Player*>(2);
	players[0] = &human;
	players[1] = &bot;

	players[0]->color = Colors::Nord::Aurora::nord14;
	players[1]->color = Colors::Nord::Aurora::nord12;

	/* Create the visual board tiles */
	board_tile_entities = std::vector<std::vector<Entity>>(board.dimensions.x);
	int cur_color = 0;
	for (int i = 0; i < board.dimensions.x; ++i)
	{
		for (int j = 0; j < board.dimensions.y; ++j)
		{
			Rect tile_rect(i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE);
			Entity board_tile("Board tile", tile_rect, 1);
			board_tile.rect.color = tile_colors[cur_color];

			board_tile_entities[i].push_back(board_tile);

			if (cur_color == 0)
				cur_color = 1;
			else
				cur_color = 0;
		}
	}

	/* Add the board tile entities to the board scene */
	for (size_t i = 0; i < board_tile_entities.size(); ++i)
		for (size_t j = 0; j < board_tile_entities[i].size(); ++j)
			board_scene.AddObject(&board_tile_entities[i][j]);
}

/* input() is called at the beginning of the frame
 * before update(). Behind the curtains it does input
 * polling etc. and then passes the SDL_Event into
 * this function */
void input(Game& game)
{
	if (players[current_player]->type == Player::PlayerType::Human
			&& game.window->isMouseDown())
	{
		/* Figure out what tile was clicked, if any */
		bool result_found = false;
		for (int i = 0; i < board.dimensions.x; ++i)
		{
			for (int j = 0; j < board.dimensions.y; ++j)
			{
				if (game.window->CursorInRect(board_tile_entities[i][j].rect))
				{
					human_move = Vector2Int(i, j);
					result_found = true;
					std::cout << "Picked tile: " << human_move << std::endl;
					break;
				}
			}

			if (result_found)
				break;
		}
	}
}

/* update() is called after input has been handled and
 * before the frame gets rendered. Its useful for any game
 * logic that needs to be updated before rendering */
void update(Game& game)
{
	/* Make move */
	if (!game_over)
	{
		Vector2Int move_result = players[current_player]->MakeMove(human_move);
		if (move_result != Vector2Int( -1, -1 ))
		{
			/* Set new tile color */
			board_tile_entities[move_result.x][move_result.y].rect.color = players[current_player]->color;
			
			/* Reset the move */
			human_move = { -1, -1 };

			/* Check for winning condition */
			int winner = board.check_win();
			if (winner != 0)
			{
				std::cout << "Player '" << players[winner - 1]->name << "' has won!" << std::endl;
				game_over = true;
			}

			/* Give the turn to the next player */
			current_player++;
		}


		if (current_player >= 2)
			current_player = 0;
	}
}

/* render() is called after update() has been finished.
 * Before it gets called, the window will be cleared and
 * after the function has finished running, the rendered frame
 * will be presented */
void render(Game& game)
{
	/* Draw the backgaround */
	Render::DrawRect(Rect(0, 0, game.window->dimensions.x, game.window->dimensions.y, Colors::Nord::PolarNight::nord0));

	board_scene.Render();
}

/* post_render() will be called after rendering has finished
 * and the timestep stalling has started. On non-windows systems
 * this function call will be done on a separate thread, so you
 * could use it to do some extra preparations for the next frame
 * while the main thread is sitting around doing nothing
 * and waiting to maintain the correct frame rate */
void post_render()
{

}

/* cleanup() gets called after the game loop has finished running
 * and the application is getting closed. This is useful for doing any
 * cleanup that is necessary, like freeing heap allocations etc. */
void cleanup()
{

}
