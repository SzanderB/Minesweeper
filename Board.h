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
    int height;
    int width;
    vector<vector<Tile*>> tiles;
    map<string, sf::Texture> textures;

    int numMines;
    int currMines;


public:
    sf::RenderWindow window;        //maybe include this IDK yet


    Board();
    Board(int h,int w, int mines);
    //Copy Constructor
    Board(Board& b);

    int getHeight() const;
    int getWidth() const;

    // copy assignment operator
    Board& operator=(const Board& b);
    //Destructor
    ~Board();

    //****************** Functionalities *************************

    void display();
};

