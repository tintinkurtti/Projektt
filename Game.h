//
// Created by tinti on 2023-10-12.
//

#include <SFML/Graphics.hpp>

#ifndef PROJEKTT_GAME_H
#define PROJEKTT_GAME_H

enum class Placement{
    BOT, PLAYER, DRAW, EMPTY
};

/**
 * @brief The main game class
 * @details The main game class creates the playing grid
 * and handles the placement of the player and the bot opponent.
 */

class Game {
public:
    /**
     * @brief Default-constructor for the game
     */
    Game();

    /**
     * @brief Function that actually runs the game.
     * @details Function that draws the grid
     * and runs the while-loop that calls the other in-game functions.
     */
    void Start();

    /**
     * @brief Checks for mouse input while in the menu.
     * @details Checks if the X or O is chosen for the player.
     */
    void CheckMouseInputInMenu();

    /**
     * @brief Checks for mouse input in the game.
     * @details Places a playermark on the position that the player clicks.
     */
    void CheckMouseInputInGame();

    /**
     * @brief Checks if the left mouse-button is pressed.
     * @details Checks if the left mouse-button is pressed
     * and calls for one of the functions above based on the current game state.
     */
    void CheckMouseInput();

    /**
     * @brief Handles events during running game.
     * @details Handles if the game closes, a keye is pressed or if a mouse-button is pressed
     */
    void HandleEvent();

    /**
     * @brief A simple bot that places the mark at a randomized position
     */
    void Bot();

    /**
     * @brief Function that resets the playing grid and returns to the menu.
     */
    void ResetGame();

    /**
     * @brief Checks if there is a winner
     * @details Checks if there is a winner and prints the outcome.
     * Then resets the game and returns to the menu.
     */
    void SetWinner(int winner);

    /**
     * @brief Checks if the game is still on
     * @param winner The int corresponding to the bot or the player or if it is a draw.
     */
    int GameIsOn(const int board[3][3]);

    /**
     * @brief Checks if there are 3 in a row horizontally.
     * @return
     */
    int CheckHorizontal(const int board[3][3]);

    /**
     * @brief Checks if there are 3 in a row for one diagonal
     * @return Returns the int corresponding to the winner or if there is a draw.
     */
    int CheckFirstDiagonal(const int board[3][3]);

    /**
     * @brief Checks if there are 3 in a row for the second diagonal
     * @return Returns the int corresponding to the winner or if there is a draw.
     */
    int CheckSecondDiagonal(const int board[3][3]);

    /**
     * @brief Checks if there are 3 in a row vertically
     * @return Returns the int corresponding to the winner or if there is a draw.
     */
    int CheckVertical(const int board[3][3]);

    /**
     * @brief Checks if there is 3 in a row by calling the functions above
     * @return Returns the int corresponding to the winner or if there is a draw.
     */
    int Winner();
private:
    sf::RenderWindow game;
    std::string BaseDirectory = "C:/Users/tinti/CLionProjects/Metodik/Projektt/";
    sf::Texture field, x_texture, zero_texture;
    sf::Texture player_mark, enemy_mark;
    sf::Font roboto_bold;
    sf::Sprite board_sprite;
    sf::Text game_status;
    sf::FloatRect gs_bounds;

    sf::RectangleShape square[3][3];

    sf::Event event{};

    int matrix[3][3]{};
};


#endif //PROJEKTT_GAME_H
