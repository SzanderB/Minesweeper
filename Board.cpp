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
        int y = rand() % numCols;

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

void Board::display(sf::RenderWindow& window) const{
    for(int x = 0; x < numRows; x++){
        for(int y = 0; y < numCols; y++){
            window.draw(tiles[x][y]->getBackground());
            window.draw(tiles[x][y]->getSprite());
        }
    }
}
void Board::mouseClicked(sf::Mouse::Button button, int x, int y){
    // decide whether its on the board or not
    if(y > height-100){
        // bottom of the board

    }else if(!gameOver){
        // ON THE BOARD
        int indexX = y/32;
        int indexY = x/32;
        // check left or right click
        if(button == sf::Mouse::Button::Left){
            int temp = tiles[indexX][indexY]->reveal();
            if(temp == 0){
                gameOver = true;
            }else if(temp == 2) {
                clearAdjacentEmptyTiles(indexX, indexY);
            }
        }else if(button == sf::Mouse::Button::Right){
            tiles[indexX][indexY]->flag();
        }

    }
}
bool Board::clearAdjacentEmptyTiles(int x, int y){
    vector<Tile*> temp = tiles[x][y]->getSurrounding();

    for(int i = 0; i < temp.size(); i++) {
        if(temp[i]->reveal() == 2){
            clearAdjacentEmptyTiles(temp[i]->getX(), temp[i]->getY());
        }
    }
}
