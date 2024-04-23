//
// Created by szand on 4/17/2024.
//
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include "Board.h"
#include "Tile.h"

// Unrelated Functions


//****************************************** Board ***********************************************
//****************** Basic Behaviors *************************
Board::Board(){
    height = 400;
    width = 400;
}

Board::Board(int h,int w, int mines){
    height = h * 32 + 100;
    width = w * 32;
    numMines = mines;

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

