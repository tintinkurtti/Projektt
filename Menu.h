//
// Created by tinti on 2023-10-15.
//

#include <SFML/Graphics.hpp>

#ifndef PROJEKTT_MENU_H
#define PROJEKTT_MENU_H

#pragma once


class Menu {
public:

    /**
     * @brief
     * @param
     * @return
     */
    Menu();

    /**
     * @brief
     * @param
     * @return
     */
    void ShowMenu();

    /**
     * @brief
     * @param
     * @return
     */
    void HideMenu();

    /**
     * @brief
     * @param
     * @return
     */
    bool IsMenuShowing();

    /**
     * @brief
     * @param
     * @return
     */
    sf::Text ReturnText();

    /**
     * @brief
     * @param
     * @return
     */
    sf::RectangleShape ReturnXButton(), ReturnZeroButton();
private:
    bool show_menu = true;
    std::string BaseDirectory = "C:/Users/tinti/CLionProjects/Metodik/Projektt/";
    sf::Font roboto_bold;
    sf::Text play_as, x_text, zero_text;
    sf::RectangleShape x, zero;
    sf::Texture x_texture, zero_texture;

};


#endif //PROJEKTT_MENU_H
