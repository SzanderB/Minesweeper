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
void Tile::setAdjacent(vector<vector<Tile*>>& list, int totRow, int totCol) {
    // check edge cases
    if((row == 0) && (column == 0)){            // Top left corner
        surrounding.push_back(list[1][0]);
        surrounding.push_back(list[1][1]);
        surrounding.push_back(list[0][1]);
    }else if((row == 0) && (column == totCol)){     // Top right corner
        surrounding.push_back(list[totCol-2][0]);
        surrounding.push_back(list[totCol-2][1]);
        surrounding.push_back(list[totCol-1][1]);
    }else if((row == totRow) && (column == 0)){     // Bot left corner
        surrounding.push_back(list[0][totRow-2]);
        surrounding.push_back(list[1][totRow-2]);
        surrounding.push_back(list[1][totRow-1]);
    }else if((row == totRow) && (column == totCol)){        // Bot right corner
        surrounding.push_back(list[totCol-1][totRow-2]);
        surrounding.push_back(list[totCol-2][totRow-1]);
        surrounding.push_back(list[totCol-2][totRow-2]);
    }else if(column == 0){                                  // left wall
        surrounding.push_back(list[0][row-1]);          //top
        surrounding.push_back(list[1][row-1]);          // TR
        surrounding.push_back(list[1][row]);            //right
        surrounding.push_back(list[1][row+1]);          //BR
        surrounding.push_back(list[0][row+1]);          //bottom
    }else if(column == totCol){                             // right wall
        surrounding.push_back(list[totCol][row-1]);     //top
        surrounding.push_back(list[totCol-1][row-1]);   //TL
        surrounding.push_back(list[totCol-1][row]);     //left
        surrounding.push_back(list[totCol-1][row+1]);   //BL
        surrounding.push_back(list[totCol][row+1]);     //bot
    }else if(row == 0){                                     // top wall
        surrounding.push_back(list[column-1][0]);       //left
        surrounding.push_back(list[column-1][1]);       // BL
        surrounding.push_back(list[column][1]);         //bot
        surrounding.push_back(list[column+1][1]);       //BR
        surrounding.push_back(list[column+1][0]);       //right
    }else if(row == totRow){                                // bottom wall
        surrounding.push_back(list[column-1][totRow]);  //left
        surrounding.push_back(list[column-1][totRow-1]);//TL
        surrounding.push_back(list[column][totRow-1]);  //TOP
        surrounding.push_back(list[column+1][totRow-1]);//TR
        surrounding.push_back(list[column+1][totRow]);  //right
    }else{
        surrounding.push_back(list[column][row-1]);     //top
        surrounding.push_back(list[column+1][row-1]);   //TR
        surrounding.push_back(list[column+1][row]);     //Right
        surrounding.push_back(list[column+1][row+1]);   //BR
        surrounding.push_back(list[column][row+1]);     //bot
        surrounding.push_back(list[column-1][row+1]);   //BL
        surrounding.push_back(list[column-1][row]);     //left
        surrounding.push_back(list[column-1][row-1]);   //TL
    }
}
