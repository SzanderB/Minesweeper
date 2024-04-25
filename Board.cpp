//
// Created by szand on 4/17/2024.
//
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <random>
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
    numRows = w;
    numCols = h;
    currMines = 0;
    gameOver = false;

    for(int x = 0; x < numRows; x++){
        vector<Tile*> *temp = new vector<Tile*>;
        tiles.push_back(*temp);
        for(int y = 0; y < numCols; y++){
            Tile *temp = new Tile(x,y);
            tiles[x].push_back(temp);

        }
    }

    while(currMines < numMines){
        // get a random x/y
        int x = rand() % numRows;
        cout  << x << ", ";
        int y = rand() % numCols;
        cout  << y << endl;

        // check if there is a bomb there
        if(tiles[x][y]->hasBomb()){         //if it does, skip to the next iteration
            continue;
        }
        //if it doesnt have a bomb, add one
        tiles[x][y]->setMine();
        currMines++;
    }

    for(int x = 0; x < numRows; x++){
        for(int y = 0; y < numCols; y++){
            tiles[x][y]->setAdjacent(tiles, numRows, numCols);
            cout << "Done" << endl;
            tiles[x][y]->calculateAdjMines();
        }
    }
}

int Board::getHeight() const{
    return height;
}
int Board::getWidth() const{
    return width;
}


void Board::setupBoard(){
    for(int x = 0; x < numRows; x++){
        for(int y = 0; y < numCols; y++){
            delete tiles[x][y];
        }
    }
    for(int x = 0; x < numRows; x++){
        for(int y = 0; y < numCols; y++){
            tiles[x].push_back(new Tile(x,y));
        }
    }

    while(currMines < numMines){
        // get a random x/y
        int x = rand() % numCols;
        int y = rand() % numRows;
        // check if there is a bomb there
        if(tiles[x][y]->hasBomb()){         //if it does, skip to the next iteration
            continue;
        }
        //if it doesnt have a bomb, add one
        tiles[x][y]->setMine();
        currMines++;
    }

    for(int x = 0; x < numRows; x++){
        for(int y = 0; y < numCols; y++){
            tiles[x][y]->setAdjacent(tiles, numRows, numCols);
            tiles[x][y]->calculateAdjMines();
        }
    }
}

//Destructor
Board::~Board(){
    for(int x = 0; x < numRows; x++){
        for(int y = 0; y < numCols; y++){
            delete tiles[x][y];
        }
    }
}


void Board::display(sf::RenderWindow& window){
    for(int x = 0; x < numRows; x++){
        for(int y = 0; y < numCols; y++){
            window.draw(tiles[x][y]->getSprite());
        }
    }
}
