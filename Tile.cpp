//
// Created by szand on 4/23/2024.
//
#include "Tile.h"
#include "TextureManager.h"

Tile::Tile(int row, int col){
    image.setTexture(TextureManager::GetTexture("tile_hidden"));
    image.setPosition(col * 32,row * 32);
    flagged = false;
    hasMine = false;
    revealed = false;
    this->row = row;
    this->column = col;
    surroundingMines = 0;
}

void Tile::flag(){
    flagged = !flagged;
    if(flagged) {
        image.setTexture(TextureManager::GetTexture("flag"));
    } else{
        image.setTexture(TextureManager::GetTexture("tile_hidden"));
    }
}
void Tile::reveal(){
    if(hasMine){
        image.setTexture(TextureManager::GetTexture("mine"));
    }else{

    }
}
void Tile::cover(){

}

void Tile::calculateAdjMines(){
    for(int i = 0; i < surrounding.size(); i++){
        if(surrounding[i]->hasMine){
            surroundingMines++;
        }
    }
}
// creates the network of mines needed for the game to function properly
void Tile::setAdjacent(vector<vector<Tile*>>& list){

}
