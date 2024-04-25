//
// Created by szand on 4/23/2024.
//
#include "Tile.h"
#include "TextureManager.h"

Tile::Tile(int row, int col){
    image.setTexture(TextureManager::GetTexture("tile_hidden"));
    image.setPosition((float)col * 32,(float)row * 32);
    flagged = false;
    hasMine = false;
    revealed = false;
    this->row = row;
    this->column = col;
    surroundingMines = 0;
}

bool Tile::hasBomb() const{
    return hasMine;
}

void Tile::setMine(){
    hasMine = true;
}
sf::Sprite& Tile::getSprite(){
    return image;
}


void Tile::flag(){
    flagged = !flagged;
    if(flagged) {
        image.setTexture(TextureManager::GetTexture("flag"));
    } else{
        image.setTexture(TextureManager::GetTexture("tile_hidden"));
    }
}
bool Tile::reveal(int x, int y){
    if(hasMine){
        image.setTexture(TextureManager::GetTexture("mine"));
        return true;
    }else{
        if(surroundingMines != 0) {
            string temp = "number_" + to_string(surroundingMines);
            image.setTexture(TextureManager::GetTexture(temp));
        }else{
            image.setTexture(TextureManager::GetTexture("tile_revealed"));
            // need to check the top, right, left, bottom for empty tiles as well

        }
        return false;
    }
}
void Tile::cover(){

}

void Tile::calculateAdjMines(){
    for(int i = 0; i < surrounding.size(); i++){
        if(surrounding[i]->hasBomb()){
            surroundingMines++;
        }
    }
}
// creates the network of mines needed for the game to function properly
void Tile::setAdjacent(vector<vector<Tile*>>& list, int totRow, int totCol) {
    // check edge cases
    if((row == 0) && (column == 0)){            // Top left corner
        surrounding.push_back(list[1][0]);
        surrounding.push_back(list[1][1]);
        surrounding.push_back(list[0][1]);
    }else if((row == 0) && (column == totCol-1)){     // Top right corner
        surrounding.push_back(list[0][totCol-2]);
        surrounding.push_back(list[1][totCol-2]);
        surrounding.push_back(list[1][totCol-1]);
    }else if((row == totRow-1) && (column == 0)){     // Bot left corner
        surrounding.push_back(list[totRow-2][0]);
        surrounding.push_back(list[totRow-2][1]);
        surrounding.push_back(list[totRow-1][1]);
    }else if((row == totRow-1) && (column == totCol-1)){        // Bot right corner
        surrounding.push_back(list[totRow-2][totCol-1]);
        surrounding.push_back(list[totRow-1][totCol-2]);
        surrounding.push_back(list[totRow-2][totCol-2]);
    }else if(column == 0){                                  // left wall
        surrounding.push_back(list[row-1][0]);          //top
        surrounding.push_back(list[row-1][1]);          // TR
        surrounding.push_back(list[row][1]);            //right
        surrounding.push_back(list[row+1][1]);          //BR
        surrounding.push_back(list[row+1][0]);          //bottom
    }else if(column == totCol-1){                             // right wall
        surrounding.push_back(list[row-1][totCol-1]);     //top
        surrounding.push_back(list[row-1][totCol-2]);   //TL
        surrounding.push_back(list[row][totCol-2]);     //left
        surrounding.push_back(list[row+1][totCol-2]);   //BL
        surrounding.push_back(list[row+1][totCol-1]);     //bot
    }else if(row == 0){                                     // top wall
        surrounding.push_back(list[0][column-1]);       //left
        surrounding.push_back(list[1][column-1]);       // BL
        surrounding.push_back(list[1][column]);         //bot
        surrounding.push_back(list[1][column+1]);       //BR
        surrounding.push_back(list[0][column+1]);       //right
    }else if(row == totRow-1){                                // bottom wall
        surrounding.push_back(list[totRow-1][column-1]);  //left
        surrounding.push_back(list[totRow-2][column-1]);//TL
        surrounding.push_back(list[totRow-2][column]);  //TOP
        surrounding.push_back(list[totRow-2][column+1]);//TR
        surrounding.push_back(list[totRow-1][column+1]);  //right
    }else{
        surrounding.push_back(list[row-1][column]);     //top
        surrounding.push_back(list[row-1][column+1]);   //TR
        surrounding.push_back(list[row][column+1]);     //Right
        surrounding.push_back(list[row+1][column+1]);   //BR
        surrounding.push_back(list[row+1][column]);     //bot
        surrounding.push_back(list[row+1][column-1]);   //BL
        surrounding.push_back(list[row][column-1]);     //left
        surrounding.push_back(list[row-1][column-1]);   //TL
    }
}
bool Tile::clearAdjacentEmptyTiles(int x, int y){
    //check top
    
    //check right

    // check left

    // check bottom
}
