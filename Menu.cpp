//
// Created by tinti on 2023-10-15.
//
#include <iostream>
#include "Menu.h"

Menu::Menu() {
    if (!x_texture.loadFromFile(BaseDirectory + "Textures/x_texture.png")){
        std::cout << "X could not be loaded" << std::endl;
    }
    if (!zero_texture.loadFromFile(BaseDirectory + "Textures/zero_texture.png")){
        std::cout << "O could not be loaded" << std::endl;
    }
    if (!roboto_bold.loadFromFile(BaseDirectory + "Fonts/Roboto-Bold.ttf")){
        std::cout << "font could not be loaded" << std::endl;
    }

    play_as = sf::Text("PLAY AS", roboto_bold, 60);
    play_as.setFillColor(sf::Color::Black);
    play_as.setPosition(sf::Vector2f(290, 150));

    x.setSize(sf::Vector2f(90, 90));
    x.setPosition(sf::Vector2f(190, 250));
    x.setTexture(&x_texture);

    zero.setSize(sf::Vector2f(90, 90));
    zero.setPosition(sf::Vector2f(530, 250));
    zero.setTexture(&zero_texture);
}

void Menu::ShowMenu() {
    show_menu = true;
}

void Menu::HideMenu() {
    show_menu = false;
}

bool Menu::IsMenuShowing() {
    return show_menu;
}

sf::Text Menu::ReturnText() {
    return play_as;
}

sf::RectangleShape Menu::ReturnXButton() {
    return x;
}

sf::RectangleShape Menu::ReturnZeroButton() {
    return zero;
}