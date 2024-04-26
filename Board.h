//
// Created by szand on 4/17/2024.
//
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Tile.h"

using namespace std;
#pragma once



class Board{
private:
    int numRows;
    int numCols;

    int height;
    int width;
    vector<vector<Tile*>> tiles;

    int numMines;
    int currMines;

    sf::Sprite faceButton;
    sf::Sprite counter;
    sf::Sprite debugButton;
    sf::Sprite pauseButton;
    sf::Sprite leaderboardButton;
    sf::Sprite timer;
    
public:
    bool gameOver;
    Board();
    Board(int h,int w, int mines);

    int getHeight() const;
    int getWidth() const;


    void setupBoard();

    void mouseClicked(sf::Mouse::Button button, int x, int y);
    bool clearAdjacentEmptyTiles(int x, int y);

    void display(sf::RenderWindow& window) const;
};

