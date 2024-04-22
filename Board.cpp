//
// Created by szand on 4/17/2024.
//
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include "Board.h"

// Unrelated Functions


//****************************************** Board ***********************************************
//****************** Basic Behaviors *************************
Board::Board(){
    height = 400;
    width = 400;
}

Board::Board(int h,int w, int mines, map<string, sf::Texture> textures){
    height = h * 32 + 100;
    width = w * 32;
    numMines = mines;

    this->textures = std::move(textures);
    for(int i = 0; i < h*w; i++){
        Tile temp;
        sf::Vector2f topLeft = {static_cast<float>((i*32)%width), static_cast<float>(32*i)/width};
        sf::Vector2f botRight = {topLeft.x + 32, topLeft.y - 32};
        temp.setBounds(topLeft, botRight);
        tiles.push_back(temp);
    }
}
//Copy Constructor
Board::Board(Board& b){
    height = b.getHeight();
    width = b.getWidth();
}

int Board::getHeight() const{
    return height;
}
int Board::getWidth() const{
    return width;
}

// copy assignment operator
Board& Board::operator=(const Board& b){
    if(&b == this)
        return *this;

    height = b.getHeight();
    width = b.getWidth();
    return *this;
}

//Destructor
Board::~Board() = default;

Tile::Tile(){
    texture.loadFromFile("files/images/tile_hidden.png");
    image.setTexture(texture);
    flagged = false;
    hasMine = false;
    revealed = false;
}

void Tile::flag(){
    flagged = !flagged;
}
void Tile::reveal(){

}
bool Tile::isInBounds(sf::Vector2f loc){

}

void Tile::setBounds(sf::Vector2f coords1, sf::Vector2f coords2){
    topLeftCoord = coords1;
    botRightCoord = coords2;
}