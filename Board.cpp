//
// Created by szand on 4/17/2024.
//
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>
#include <sstream>
#include "Board.h"
#include "Tile.h"
#include "TextureManager.h"
using namespace std;
// Unrelated Functions

void setText2(sf::Text &text, float x, float y);
//****************************************** Board ***********************************************
//****************** Basic Behaviors *************************
Board::Board(){
    height = 400;
    width = 400;
}

Board::Board(int h,int w, int mines, string name){
    height = w * 32 + 100;
    width = h * 32;
    numMines = mines;
    numRows = w;
    numCols = h;
    currMines = 0;
    gameOver = false;
    paused = false;
    debug = false;
    seconds =0;
    offset = 0;
    t = chrono::high_resolution_clock::now();
    this->name = name;
    totalFlags = mines;
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

    // set images and locations of each of the buttons
    debugButton.setTexture(TextureManager::GetTexture("debug"));
    debugButton.setPosition((float)numCols * 32 -304, (float)(numRows+0.5) *32);

    faceButton.setTexture(TextureManager::GetTexture("face_happy"));
    faceButton.setPosition((float)numCols/2 * 32 -32, (float)(numRows+0.5) *32);

    leaderboardButton.setTexture(TextureManager::GetTexture("leaderboard"));
    leaderboardButton.setPosition((float)numCols * 32 -176, (float)(numRows+0.5) *32);

    pauseButton.setTexture(TextureManager::GetTexture("pause"));
    pauseButton.setPosition((float)numCols * 32 -240, (float)(numRows+0.5) *32);

    faceButton.setTexture(TextureManager::GetTexture("face_happy"));
    faceButton.setPosition((float)numCols/2 * 32 -32, (float)(numRows+0.5) *32);

    negativeSign.setTexture(TextureManager::GetTexture("digits"));
    negativeSign.setPosition(33-21,(float)(numRows+0.5) *32 + 16);
    negativeSign.setTextureRect(sf::IntRect(21*10,0, 21, 32));

    counterOnes.setTexture(TextureManager::GetTexture("digits"));
    counterOnes.setPosition(33+21*2,(float)(numRows+0.5) *32 + 16);
    counterOnes.setTextureRect(sf::IntRect(21*(totalFlags %10),0, 21, 32));

    counterTens.setTexture(TextureManager::GetTexture("digits"));
    counterTens.setPosition(33+21,(float)(numRows+0.5) *32 + 16);
    counterTens.setTextureRect(sf::IntRect(21*(totalFlags/10),0, 21, 32));

    counterHundos.setTexture(TextureManager::GetTexture("digits"));
    counterHundos.setPosition(33,(float)(numRows+0.5) *32 + 16);
    counterHundos.setTextureRect(sf::IntRect(21*(totalFlags/100),0, 21, 32));

    timerOnes.setTexture(TextureManager::GetTexture("digits"));
    timerOnes.setPosition((float)numCols*32 -54+21,(float)(numRows+0.5) *32 + 16);
    timerOnes.setTextureRect(sf::IntRect(0,0, 21, 32));

    timerTens.setTexture(TextureManager::GetTexture("digits"));
    timerTens.setPosition((float)numCols*32 -54,(float)(numRows+0.5) *32 + 16);
    timerTens.setTextureRect(sf::IntRect(0,0, 21, 32));

    timerHundos.setTexture(TextureManager::GetTexture("digits"));
    timerHundos.setPosition((float)numCols*32 -97+21,(float)(numRows+0.5) *32 + 16);
    timerHundos.setTextureRect(sf::IntRect(0,0, 21, 32));

    timerThous.setTexture(TextureManager::GetTexture("digits"));
    timerThous.setPosition((float)numCols*32 - 97,(float)(numRows+0.5) *32 + 16);
    timerThous.setTextureRect(sf::IntRect(0,0, 21, 32));
}

int Board::getHeight() const{
    return height;
}
int Board::getWidth() const{
    return width;
}
bool Board::isPaused() const{
    return paused;
}

void Board::setupBoard(){
    t = chrono::high_resolution_clock::now();
    pauseStart = chrono::high_resolution_clock::now();
    offset = 0;
    seconds = 0;
    gameOver = false;
    currMines = 0;
    totalFlags = numMines;
    for(int x = 0; x < numRows; x++){
        for(int y = 0; y < numCols; y++){
            delete tiles[x][y];
        }
    }

    for(int x = 0; x < numRows; x++){
        for(int y = 0; y < numCols; y++){
            Tile *temp = new Tile(x,y);
            tiles[x][y] = temp;
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

    // set images and locations of each of the buttons
    debugButton.setTexture(TextureManager::GetTexture("debug"));
    debugButton.setPosition((float)numCols * 32 -304, (float)(numRows+0.5) *32);

    faceButton.setTexture(TextureManager::GetTexture("face_happy"));
    faceButton.setPosition((float)numCols/2 * 32 -32, (float)(numRows+0.5) *32);

    leaderboardButton.setTexture(TextureManager::GetTexture("leaderboard"));
    leaderboardButton.setPosition((float)numCols * 32 -176, (float)(numRows+0.5) *32);

    pauseButton.setTexture(TextureManager::GetTexture("pause"));
    pauseButton.setPosition((float)numCols * 32 -240, (float)(numRows+0.5) *32);

    faceButton.setTexture(TextureManager::GetTexture("face_happy"));
    faceButton.setPosition((float)numCols/2 * 32 -32, (float)(numRows+0.5) *32);

    negativeSign.setTexture(TextureManager::GetTexture("digits"));
    negativeSign.setPosition(33-21,(float)(numRows+0.5) *32 + 16);
    negativeSign.setTextureRect(sf::IntRect(21*9,0, 21, 32));

    counterOnes.setTexture(TextureManager::GetTexture("digits"));
    counterOnes.setPosition(33+21*2,(float)(numRows+0.5) *32 + 16);
    counterOnes.setTextureRect(sf::IntRect(21*(totalFlags %10),0, 21, 32));

    counterTens.setTexture(TextureManager::GetTexture("digits"));
    counterTens.setPosition(33+21,(float)(numRows+0.5) *32 + 16);
    counterTens.setTextureRect(sf::IntRect(21*(totalFlags/10),0, 21, 32));

    counterHundos.setTexture(TextureManager::GetTexture("digits"));
    counterHundos.setPosition(33,(float)(numRows+0.5) *32 + 16);
    counterHundos.setTextureRect(sf::IntRect(21*(totalFlags/100),0, 21, 32));

    timerOnes.setTexture(TextureManager::GetTexture("digits"));
    timerOnes.setPosition((float)numCols*32 -54+21,(float)(numRows+0.5) *32 + 16);
    timerOnes.setTextureRect(sf::IntRect(0,0, 21, 32));

    timerTens.setTexture(TextureManager::GetTexture("digits"));
    timerTens.setPosition((float)numCols*32 -54,(float)(numRows+0.5) *32 + 16);
    timerTens.setTextureRect(sf::IntRect(0,0, 21, 32));

    timerHundos.setTexture(TextureManager::GetTexture("digits"));
    timerHundos.setPosition((float)numCols*32 -97+21,(float)(numRows+0.5) *32 + 16);
    timerHundos.setTextureRect(sf::IntRect(0,0, 21, 32));

    timerThous.setTexture(TextureManager::GetTexture("digits"));
    timerThous.setPosition((float)numCols*32 - 97,(float)(numRows+0.5) *32 + 16);
    timerThous.setTextureRect(sf::IntRect(0,0, 21, 32));
}

void Board::display(sf::RenderWindow& window) const{
    for(int x = 0; x < numRows; x++){
        for(int y = 0; y < numCols; y++){
            window.draw(tiles[x][y]->getBackground());
            window.draw(tiles[x][y]->getSprite());
        }
    }
    window.draw(counterOnes);
    window.draw(counterTens);
    window.draw(counterHundos);

    window.draw(timerOnes);
    window.draw(timerTens);
    window.draw(timerHundos);
    window.draw(timerThous);

    window.draw(debugButton);
    window.draw(leaderboardButton);
    window.draw(pauseButton);
    window.draw(faceButton);
    if(totalFlags < 0){
        window.draw(negativeSign);
    }
}
void Board::mouseClicked(sf::Mouse::Button button, int x, int y){
    // decide whether its on the board or not
    if(y > height-100){
        // bottom of the board
        if(!gameOver) {
            if (debugButton.getGlobalBounds().contains(x, y)) {
                debug = !debug;
                showMines();
            } else if (pauseButton.getGlobalBounds().contains(x, y)) {
                paused = !paused;
                if (paused) {
                    pauseButton.setTexture(TextureManager::GetTexture("play"));
                } else {
                    pauseButton.setTexture(TextureManager::GetTexture("pause"));
                }
            }
        }
        if(faceButton.getGlobalBounds().contains(x,y)){
            setupBoard();
        }else if(leaderboardButton.getGlobalBounds().contains(x,y)){
            openLeaderboard();
        }
    }else if(!gameOver && !paused){
        // ON THE BOARD
        int indexX = y/32;
        int indexY = x/32;
        // check left or right click
        if(button == sf::Mouse::Button::Left){
            int temp = tiles[indexX][indexY]->reveal();
            if(temp == 0){
                gameOver = true;
                faceButton.setTexture(TextureManager::GetTexture("face_lose"));
            }else if(temp == 2) {
                clearAdjacentEmptyTiles(indexX, indexY);
            }
        }else if(button == sf::Mouse::Button::Right){
            int temp = tiles[indexX][indexY]->flag();
            if(temp == 0){
                totalFlags--;
            }else if(temp ==1){
                totalFlags++;
            }
            counterOnes.setTexture(TextureManager::GetTexture("digits"));
            counterOnes.setPosition(33+21*2,(float)(numRows+0.5) *32 + 16);
            counterOnes.setTextureRect(sf::IntRect(21*abs(totalFlags %10),0, 21, 32));

            counterTens.setTexture(TextureManager::GetTexture("digits"));
            counterTens.setPosition(33+21,(float)(numRows+0.5) *32 + 16);
            counterTens.setTextureRect(sf::IntRect(21*abs(totalFlags/10),0, 21, 32));

            counterHundos.setTexture(TextureManager::GetTexture("digits"));
            counterHundos.setPosition(33,(float)(numRows+0.5) *32 + 16);
            counterHundos.setTextureRect(sf::IntRect(21*abs(totalFlags/100),0, 21, 32));
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
void Board::updateTimer(long sec){
    timerOnes.setTextureRect(sf::IntRect(21* (sec % 10),0, 21, 32));
    timerTens.setTextureRect(sf::IntRect(21* (sec%60 / 10),0, 21, 32));
    timerHundos.setTextureRect(sf::IntRect(21* (sec/60 % 10),0, 21, 32));
    timerThous.setTextureRect(sf::IntRect(21* (sec/60 / 10),0, 21, 32));
}

void Board::showMines(){
    if(debug){
        for(int x = 0; x < numRows; x++){
            for(int y = 0; y < numCols; y++){
                if(tiles[x][y]->hasBomb()){
                    tiles[x][y]->getSprite().setTexture(TextureManager::GetTexture("mine"));
                }
            }
        }
    }else {
        for(int x = 0; x < numRows; x++){
            for(int y = 0; y < numCols; y++){
                if(tiles[x][y]->hasBomb()){
                    tiles[x][y]->getSprite().setTexture(TextureManager::GetTexture("tile_hidden"));
                }
            }
        }
    }
}

bool Board::checkWin(){
    for(int x = 0; x < numRows; x++){
        for(int y = 0; y < numCols; y++){
            if(!tiles[x][y]->hasBomb() && !tiles[x][y]->isRevealed()){
                return false;
            }
        }
    }
    return true;
}
void Board::win(){
    gameOver = true;
    faceButton.setTexture(TextureManager::GetTexture("face_win"));
    for(int x = 0; x < numRows; x++){
        for(int y = 0; y < numCols; y++){
            if(tiles[x][y]->hasBomb()){
                tiles[x][y]->getSprite().setTexture(TextureManager::GetTexture("flag"));
            }
        }
    }
    totalFlags = 0;
    counterOnes.setTexture(TextureManager::GetTexture("digits"));
    counterOnes.setPosition(33+21*2,(float)(numRows+0.5) *32 + 16);
    counterOnes.setTextureRect(sf::IntRect(21*abs(totalFlags %10),0, 21, 32));

    counterTens.setTexture(TextureManager::GetTexture("digits"));
    counterTens.setPosition(33+21,(float)(numRows+0.5) *32 + 16);
    counterTens.setTextureRect(sf::IntRect(21*abs(totalFlags/10),0, 21, 32));

    counterHundos.setTexture(TextureManager::GetTexture("digits"));
    counterHundos.setPosition(33,(float)(numRows+0.5) *32 + 16);
    counterHundos.setTextureRect(sf::IntRect(21*abs(totalFlags/100),0, 21, 32));

}

void Board::openLeaderboard(){
    int widthTemp = numRows*16 + 50;
    int heightTemp = numCols*16;

    sf::RenderWindow leaderboard(sf::VideoMode(widthTemp, heightTemp), "Leaderboard");
    sf::Font font;
    !font.loadFromFile("files/font.ttf");

    volatile bool didSwitch = false;

    sf::Text title("LEADERBOARD", font, 20);
    title.setStyle(sf::Text::Bold | sf::Text::Underlined);
    setText2(title, (float) widthTemp/2, (float) heightTemp/2-120);

    //read in the values
    string leaderboardInfo[5][2];
    ifstream sizeStream("files/leaderboard.txt");
    for(int i = 0; i< 5; i++){
        string temp;
        getline(sizeStream, temp);
        istringstream stringstream(temp);
        for(int j = 0; j < 2; j++){
            getline(stringstream,leaderboardInfo[i][j], ',');
        }
        leaderboardInfo[i][1] = leaderboardInfo[i][1].substr(1);
    }
    if(checkWin()) {
        string copyLeaderboardInfo[5][2];
        for (int i = 0; i < 5; i++) {
            copyLeaderboardInfo[i][0] = leaderboardInfo[i][0];
            copyLeaderboardInfo[i][1] = leaderboardInfo[i][1];
        }
        int times[5];
        for (int i = 0; i < 5; i++) {
            int minutes = stoi(leaderboardInfo[i][0].substr(0, 2));
            int secs = stoi(leaderboardInfo[i][0].substr(3, 2));
            int total = minutes * 60 + secs;


            int minutesTemp = seconds / 60;
            int secondsTemp = seconds % 60;
            string time;
            if (minutesTemp > 9 && secondsTemp > 9) {
                time = to_string(seconds / 60) + ':' + to_string(seconds % 60);
            } else if((minutesTemp <= 9 && secondsTemp > 9)){
                time = '0' + to_string(seconds / 60) + ':' + to_string(seconds % 60);
            }else if((minutesTemp > 9 && secondsTemp <= 9)){
                time =  to_string(seconds / 60) + ':' + '0' + to_string(seconds % 60);
            }else{
                time =  '0' + to_string(seconds / 60) + ':' + '0' + to_string(seconds % 60);
            }



            if (seconds < total && !didSwitch) {
                didSwitch = true;
                if (i != 4) {
                    leaderboardInfo[i][1] = name + "*";

                    leaderboardInfo[i][0] = time;
                    for (int j = i + 1; j < 5; j++) {
                        leaderboardInfo[j][0] = copyLeaderboardInfo[j - 1][0];
                        leaderboardInfo[j][1] = copyLeaderboardInfo[j - 1][1];
                    }
                }else {
                    leaderboardInfo[4][0] = time;
                    leaderboardInfo[4][1] = name + "*";
                }
            }
        }
    }
    sizeStream.close();

    ofstream output("files/leaderboard.txt", ios_base::trunc);
    string temp = "1.\t" + leaderboardInfo[0][0] + "\t" + leaderboardInfo[0][1];
    sf::Text first(temp, font, 18);
    title.setStyle(sf::Text::Bold);
    setText2(first, (float) widthTemp/2, (float) heightTemp/2+20);


    temp = "2.\t" + leaderboardInfo[1][0] + "\t" + leaderboardInfo[1][1];
    sf::Text second(temp, font, 18);
    title.setStyle(sf::Text::Bold);
    setText2(second, (float) widthTemp/2, (float) heightTemp/2+40);

    temp = "3.\t" + leaderboardInfo[2][0] + "\t" + leaderboardInfo[2][1];
    sf::Text third(temp, font, 18);
    title.setStyle(sf::Text::Bold);
    setText2(third, (float) widthTemp/2, (float) heightTemp/2+60);

    temp = "4.\t" + leaderboardInfo[3][0] + "\t" + leaderboardInfo[3][1];
    sf::Text fourth(temp, font, 18);
    title.setStyle(sf::Text::Bold);
    setText2(fourth, (float) widthTemp/2, (float) heightTemp/2+80);

    temp = "5.\t" + leaderboardInfo[4][0] + "\t" + leaderboardInfo[4][1];
    sf::Text fifth(temp, font, 18);
    title.setStyle(sf::Text::Bold);
    setText2(fifth, (float) widthTemp/2, (float) heightTemp/2+100);

    for(int i = 0; i < 5; i++){
        output << leaderboardInfo[i][0] + ", " + leaderboardInfo[i][1] << endl;
    }
    while (leaderboard.isOpen()) {
        // Process events
        sf::Event event;
        while (leaderboard.pollEvent(event)) {
            // Close welcomeWindow: exit
            if (event.type == sf::Event::Closed) {
                leaderboard.close();
            }
        }
        // Clear screen
        leaderboard.clear(sf::Color::Blue);

        // Draw the sprite
        leaderboard.draw(title);

        leaderboard.draw(first);
        leaderboard.draw(second);
        leaderboard.draw(third);
        leaderboard.draw(fourth);
        leaderboard.draw(fifth);

        // Update the welcomeWindow
        leaderboard.display();
    }
}

void setText2(sf::Text &text, float x, float y){
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,
                   textRect.top + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x, y));
}