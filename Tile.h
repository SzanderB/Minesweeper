//
// Created by szand on 4/23/2024.
//
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace std;
#pragma once

class Tile{
private:
    sf::Sprite image;
    sf::Texture texture;

    bool flagged;
    bool hasMine;
    bool revealed;

    int row;
    int column;
    // the order will be top, TR, right, BR, bottom, BL, left, TL
    vector<Tile*> surrounding;
    int surroundingMines;

public:
    Tile(int row, int col);

    void flag();
    void cover();
    void reveal();
    void calculateAdjMines();
    void setAdjacent(vector<vector<Tile*>>& list, int totRow, int totCol);
};