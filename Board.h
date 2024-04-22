//
// Created by szand on 4/17/2024.
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

    sf::Vector2f topLeftCoord;
    sf::Vector2f botRightCoord;
    vector<Tile*> surrounding;


public:
    Tile();

    void setBounds(sf::Vector2f coords1, sf::Vector2f coords2);

    void flag();
    void reveal();
    bool isInBounds(sf::Vector2f loc);
};

class Board{
private:
    int height;
    int width;
    vector<Tile> tiles;
    map<string, sf::Texture> textures;

    int numMines;
public:
    sf::RenderWindow window;        //maybe include this IDK yet


    Board();
    Board(int h,int w, int mines, map<string, sf::Texture> textures);
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

