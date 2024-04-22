#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
//#include "Board.h"

using namespace std;

void setText(sf::Text &text, float x, float y);
vector<int> readConfigFile(const string& fileName);
void loadTextures(map<string, sf::Texture>& m);

int main()
{
    vector<int> inputs = readConfigFile("files/config.cfg");
    sf::RenderWindow welcomeWindow(sf::VideoMode(inputs[0] * 32, inputs[1] * 32 + 100), "Welcome Window");
    sf::Font font;
    if (!font.loadFromFile("files/font.ttf")) {
        return EXIT_FAILURE;
    }
    // create the three spaces that text will be output to the screen
    sf::Text title("WELCOME TO MINESWEEPER!", font, 20);
    sf::Text nameQuestion("Please enter your name:", font, 23);
    sf::Text name("|", font, 11);
    vector<char> nameChars;
    nameChars.push_back('|');
    setText(title, (float) inputs[0] * 32 / 2, (float) inputs[1] * 32 / 2 - 150);
    title.scale(1.5, 1.5);
    setText(nameQuestion, (float) inputs[0] * 32 / 2, (float) inputs[1] * 32 / 2 - 75);
    nameQuestion.scale(0.8,0.8);
    setText(name, (float) inputs[0] * 32 / 2, (float) inputs[1] * 32 / 2 - 45);
    name.scale(3.0,3.0);



    // Start the game loop
    while (welcomeWindow.isOpen())
    {
        // Process events
        sf::Event event;
        while (welcomeWindow.pollEvent(event))
        {
            // Close welcomeWindow: exit
            if (event.type == sf::Event::Closed){
                welcomeWindow.close();
            }
            if(event.type == sf::Event::TextEntered){
                if (event.text.unicode < 128) {
                    char key = static_cast<char>(event.text.unicode);
                    if(isalpha(key) && (nameChars.size() < 11)) {
                        // push back the | character and add the new one
                        nameChars.push_back('|');
                        if(nameChars.size()==2){
                            nameChars[nameChars.size()-1-1] = toupper(key);
                        }else {
                            nameChars[nameChars.size() - 1 - 1] = tolower(key);
                        }
                        // Convert to a string and reset the name screen
                        string temp(nameChars.begin(), nameChars.end());
                        name.setString(temp);
                        setText(name, (float) inputs[0] * 32 / 2, (float) inputs[1] * 32 / 2 - 45);
                    } else if((key == 8) && nameChars.size() > 1){     // BACKSPACE
                        nameChars.pop_back();
                        nameChars.pop_back();
                        nameChars.push_back('|');
                        string temp(nameChars.begin(), nameChars.end());
                        name.setString(temp);
                        setText(name, (float) inputs[0] * 32 / 2, (float) inputs[1] * 32 / 2 - 45);
                    }else if(key == 13 && nameChars.size() > 1){        // Enter key is pressed
                        welcomeWindow.close();
                    }
                }
            }

        }
        // Draw everything
        // Clear screen
        welcomeWindow.clear(sf::Color::Blue);

        // Draw the sprite
        welcomeWindow.draw(title);

        // Draw the string
        welcomeWindow.draw(nameQuestion);

        welcomeWindow.draw(name);

        // Update the welcomeWindow
        welcomeWindow.display();
    }

    // create map of textures
    map<string, sf::Texture> textures;
    loadTextures(textures);
    //Board gameBoard(inputs[0], inputs[1], inputs[2], textures);

    // GAME ACTIVE STATE
    sf::RenderWindow gameWindow(sf::VideoMode(inputs[0] * 32, inputs[1] * 32 + 100), "Game Window");
    // create a mouse to keep track of where it is clicking
    sf::Mouse mouse;


    while(gameWindow.isOpen()){
        // Process events
        sf::Event event;
        while (gameWindow.pollEvent(event)) {
            // Close welcomeWindow: exit
            if (event.type == sf::Event::Closed) {
                gameWindow.close();
            }
        }


        // Draw everything
        // Clear screen
        gameWindow.clear(sf::Color::White);


        // Update the welcomeWindow
        gameWindow.display();
    }

    return EXIT_SUCCESS;
}



/* Reads the configuration file and returns the 3 values in a vector of integers
Inputs: File name
 Outputs: Vector of ints with columns, rows, and then mines
 If file does not open, it will return a vector of 0,0,0
 */
vector<int> readConfigFile(const string& fileName){
    vector<int> temp = {0, 0, 0};
    //Read size in from cfg file
    ifstream sizeStream(fileName);

    if(!sizeStream.is_open()){
        cout << "File not found" << endl;
        return temp;
    }
    string line;
    int columns;
    int rows;
    int mines;
    sizeStream >> line;
    columns = stoi(line);
    sizeStream >> line;
    rows = stoi(line);
    sizeStream >> line;
    mines = stoi(line);
    temp = {columns, rows, mines};
    sizeStream.close();
    return temp;
}

void setText(sf::Text &text, float x, float y){
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,
                   textRect.top + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x, y));
}

void loadTextures(map<string, sf::Texture>& m){
    sf::Texture temp;
    temp.loadFromFile("files/images/debug.png");
    m.emplace("debug", temp);
    temp.loadFromFile("files/images/digits.png");
    m.emplace("digits", temp);
    temp.loadFromFile("files/images/face_happy.png");
    m.emplace("face_happy", temp);
    temp.loadFromFile("files/images/face_lose.png");
    m.emplace("face_lose", temp);
    temp.loadFromFile("files/images/flag.png");
    m.emplace("flag", temp);
    temp.loadFromFile("files/images/leaderboard.png");
    m.emplace("leaderboard", temp);
    temp.loadFromFile("files/images/mine.png");
    m.emplace("mine", temp);
    temp.loadFromFile("files/images/number_1.png");
    m.emplace("number_1", temp);
    temp.loadFromFile("files/images/number_2.png");
    m.emplace("number_2", temp);
    temp.loadFromFile("files/images/number_3.png");
    m.emplace("number_3", temp);
    temp.loadFromFile("files/images/number_4.png");
    m.emplace("number_4", temp);
    temp.loadFromFile("files/images/number_5.png");
    m.emplace("number_5", temp);
    temp.loadFromFile("files/images/number_6.png");
    m.emplace("number_6", temp);
    temp.loadFromFile("files/images/number_7.png");
    m.emplace("number_7", temp);
    temp.loadFromFile("files/images/number_8.png");
    m.emplace("number_8", temp);
    temp.loadFromFile("files/images/pause.png");
    m.emplace("pause", temp);
    temp.loadFromFile("files/images/play.png");
    m.emplace("play", temp);
    temp.loadFromFile("files/images/tile_hidden.png");
    m.emplace("tile_hidden", temp);
    temp.loadFromFile("files/images/tile_revealed.png");
    m.emplace("tile_revealed", temp);
}