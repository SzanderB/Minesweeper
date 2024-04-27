//
// Created by szand on 4/17/2024.
//
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Tile.h"

using namespace std;
#pragma once



class Board{
private:

    int numRows;
    int numCols;

    int height;
    int width;
    vector<vector<Tile*>> tiles;

    int numMines;
    int currMines;

    sf::Sprite faceButton;
    sf::Sprite negativeSign;
    sf::Sprite counterOnes;
    sf::Sprite counterTens;
    sf::Sprite counterHundos;
    sf::Sprite debugButton;
    sf::Sprite pauseButton;
    sf::Sprite leaderboardButton;
    sf::Sprite timerOnes;
    sf::Sprite timerTens;
    sf::Sprite timerHundos;
    sf::Sprite timerThous;

    volatile bool paused;
    volatile bool debug;
    string name;

public:
    int totalFlags;
    chrono::time_point<chrono::high_resolution_clock> t;
    chrono::time_point<chrono::high_resolution_clock> pauseStart;
    long offset;
    long seconds;
    bool gameOver;
    Board();
    Board(int h,int w, int mines, string name);

    int getHeight() const;
    int getWidth() const;
    bool isPaused() const;

    void setupBoard();
    void showMines();
    void mouseClicked(sf::Mouse::Button button, int x, int y);
    bool clearAdjacentEmptyTiles(int x, int y);

    void display(sf::RenderWindow& window) const;
    void updateTimer(long sec);

    bool checkWin();
    void win();

    void openLeaderboard();
};

