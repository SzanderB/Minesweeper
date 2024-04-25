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

    bool gameOver;

public:

    Board();
    Board(int h,int w, int mines);

    int getHeight() const;
    int getWidth() const;


    void setupBoard();
    //Destructor
    ~Board();

    //****************** Functionalities *************************

    void display(sf::RenderWindow& window);
};

