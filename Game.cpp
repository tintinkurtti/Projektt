//
// Created by tinti on 2023-10-12.
//
#include <iostream>
#include "Game.h"
#include "Menu.h"

Menu menu;

Game::Game(){
    if (!field.loadFromFile(BaseDirectory + "Textures/field.png")){
        std::cout << "field could not be loaded" << std::endl;
        exit(0);
    }
    if (!x_texture.loadFromFile(BaseDirectory + "Textures/x_texture.png")){
        std::cout << "X could not be loaded" << std::endl;
        exit(0);
    }
    if (!zero_texture.loadFromFile(BaseDirectory + "Textures/zero_texture.png")){
        std::cout << "O could not be loaded" << std::endl;
        exit(0);
    }

    if (!roboto_bold.loadFromFile(BaseDirectory + "Fonts/Roboto-Bold.ttf")){
        std::cout << "font could not be loaded" << std::endl;
        exit(0);
    }
    board_sprite.setTexture(field);
    board_sprite.setPosition(sf::Vector2f(95,75));
}


void Game::Start(){
    game.create(sf::VideoMode(800, 800), "Tic Tac Toe");
    game.setFramerateLimit(30);

    for (int i = 1, x = 0; i <= 3; i++, x += 140){
        for (int j = 1, y = 0; j <= 3; j++, y += 120){
            square[i-1][j-1].setSize(sf::Vector2f(170,170));
            square[i-1][j-1].setPosition(sf::Vector2f(95*j+y, 75*i+x));
            matrix[i-1][j-1] = -1;
        }
    }

    while(game.isOpen()){
        HandleEvent();
        game.clear(sf::Color::White);


        if(menu.IsMenuShowing()){
            game.draw(game_status);
            game.draw(menu.ReturnText());
            game.draw(menu.ReturnXButton());
            game.draw(menu.ReturnZeroButton());

        }
        else {
            game.draw(board_sprite);
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    game.draw(square[i][j]);
                }
            }
        }
        game.display();
    }
}
void Game::CheckMouseInputInMenu() {
    if(menu.ReturnXButton().getGlobalBounds().contains(sf::Mouse::getPosition(game).x, sf::Mouse::getPosition(game).y)){
        menu.HideMenu();
        player_mark = x_texture;
        enemy_mark = zero_texture;
    }
    if(menu.ReturnZeroButton().getGlobalBounds().contains(sf::Mouse::getPosition(game).x, sf::Mouse::getPosition(game).y)){
        menu.HideMenu();
        player_mark = zero_texture;
        enemy_mark = x_texture;
    }
}
void Game::CheckMouseInputInGame() {
    for(int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (square[i][j].getGlobalBounds().contains(sf::Mouse::getPosition(game).x, sf::Mouse::getPosition(game).y)) {
                if (matrix[i][j] == -1) {
                    matrix[i][j] = 0;
                    square[i][j].setTexture(&player_mark);
                    SetWinner(Winner());
                    Bot();
                    SetWinner(Winner());
                    break;
                }
            }
        }
    }
}

void Game::CheckMouseInput(){
    if(event.mouseButton.button == sf::Mouse::Left){
        if (menu.IsMenuShowing()){
            CheckMouseInputInMenu();
        }
        else{
            CheckMouseInputInGame();
        }
    }
}

void Game::HandleEvent(){
    while (game.pollEvent(event)){
        switch (event.type) {
            case sf::Event::Closed:{
                game.close();
                break;
            }
            case sf::Event::KeyPressed:{
                if(event.key.code == sf::Keyboard::R){
                    ResetGame();
                }
                break;
            }
            case sf::Event::MouseButtonPressed:{
                CheckMouseInput();
                break;
            }
            default:
                break;
        }
    }
}

void Game::Bot(){
    bool isPlaced = false;
    while (!isPlaced) {
        int x = rand() % 3;
        int y = rand() % 3;
        if (matrix[x][y] == -1) {
            matrix[x][y] = 1;
            square[x][y].setTexture(&enemy_mark);
            isPlaced = true;
        }
    }
}

void Game::ResetGame(){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            matrix[i][j] = -1, square[i][j].setTexture(nullptr);
        }
    }
    menu.ShowMenu();
}
void Game::SetWinner(int winner){
    if (winner == -1){
        return;
    }
    if (winner == 0){
        game_status = sf::Text("Du har vunnit!", roboto_bold, 30);
    }
    else if (winner == 1){
        game_status = sf::Text("Du har förlorat!", roboto_bold, 30);
    }
    else if (winner == 2){
        game_status = sf::Text("Oavgjort!", roboto_bold, 30);
    }
    gs_bounds = game_status.getLocalBounds();
    game_status.setOrigin(gs_bounds.left + gs_bounds.width / 2.0f, gs_bounds.top + gs_bounds.height / 2.0f);
    game_status.setPosition(sf::Vector2f(400, 400));
    game_status.setFillColor(sf::Color::Black);
    menu.ShowMenu();
    ResetGame();
}

int Game::GameIsOn(const int board[3][3]) {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++){
            if(board[i][j] == -1){
                return -1;
            }
        }
    }
    return 2;
}

int Game::CheckHorizontal(const int board[3][3]){
    int sum_player, sum_enemy;
    for (int i = 0; i < 3; i++){
        sum_enemy = sum_player = 0;
        for (int j = 0; j < 3; j++){
            if(board[i][j] == 0) {
                sum_player++;
            }
            if(board[i][j] == 1){
                sum_enemy++;
            }
        }
        if(sum_enemy == 3){
            return 1;
        }
        if(sum_player == 3){
            return 0;
        }
    }
    return 2;
}

int Game::CheckFirstDiagonal(const int board[3][3]){
    int sum_player = 0, sum_enemy = 0;
    for (int i = 0; i < 3; i++){

        if(board[i][i] == 0) {
            sum_player++;
        }
        if(board[i][i] == 1){
            sum_enemy++;
        }
    }
    if(sum_enemy == 3){
        return 1;
    }
    if(sum_player == 3) {
        return 0;
    }
    return 2;
}

int Game::CheckSecondDiagonal(const int board[3][3]){
    int sum_player = 0, sum_enemy = 0;
    for (int i = 0; i < 3; i++){

        if(board[i][2-i] == 0) {
            sum_player++;
        }
        if(board[i][2-i] == 1){
            sum_enemy++;
        }
    }
    if(sum_enemy == 3){
        return 1;
    }
    if(sum_player == 3) {
        return 0;
    }
    return 2;
}
int Game::CheckVertical(const int board[3][3]){
    int sum_player, sum_enemy;
    for (int i = 0; i < 3; i++){
        sum_enemy = sum_player = 0;
        for (int j = 0; j < 3; j++){
            if(board[j][i] == 0) {
                sum_player++;
            }
            if(board[j][i] == 1){
                sum_enemy++;
            }
        }
        if(sum_enemy == 3){
            return 1;
        }
        if(sum_player == 3){
            return 0;
        }
    }
    return 2;
}

int Game::Winner(){

    int horizontal_data = CheckHorizontal(matrix);
    int first_diagonal_data = CheckFirstDiagonal(matrix);
    int second_diagonal_data = CheckSecondDiagonal(matrix);
    int vertical_data = CheckVertical(matrix);

    if (horizontal_data == 0 || first_diagonal_data == 0 || second_diagonal_data == 0 || vertical_data == 0){
        return 0;
    }

    if (horizontal_data == 1 || first_diagonal_data == 1 || second_diagonal_data == 1 || vertical_data == 1){
        return 1;
    }

    int game_is_on = GameIsOn(matrix);
    if (game_is_on == -1){
        return -1;
    }

    return 2; // oavgjort

}
