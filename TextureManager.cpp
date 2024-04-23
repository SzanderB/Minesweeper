//
// Created by szand on 4/23/2024.
//
#include <iostream>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
using namespace std;

// need a load function to get all the textures into the map
void TextureManager::LoadTexture(const string& textureName){
    // start of path is the same for everything
    string pathBeginning = "files/images/";
    //ending of path is same
    string extension = ".png";
    // use loadFromFile and emplace to put it in map
    sf::Texture temp;
    temp.loadFromFile(pathBeginning+textureName+extension);
    textures.emplace(textureName, temp);
}
// used in the Board to load the needed textures
sf::Texture& TextureManager::GetTexture(const string& textureName){
    // check to see if the texture has been loaded yet
        // load it and return it
    if(textures.find(textureName) == textures.end()){
        LoadTexture(textureName);
    }
    // if its in the map, return it
    return textures.at(textureName);
}
//use at end of code
void TextureManager::Clear(){
    textures.clear();
}