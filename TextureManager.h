//
// Created by szand on 4/23/2024.
//

#pragma once
#include <iostream>
#include <unordered_map>
#include <SFML/Graphics.hpp>
using namespace std;

class TextureManager{
private:
    static unordered_map<string, sf::Texture> textures;

public:
    // need a load function to get all the textures into the map
    static void LoadTexture(const string& textureName);
    // used in the Board to load the needed textures
    static sf::Texture& GetTexture(const string& textureName);
    //use at end of code
    static void Clear();
};