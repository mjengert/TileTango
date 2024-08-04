#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

struct Images{
    Clock clock;
    int width, height;
    float angle, speed;

    //========================================= Title Text Variables =========================================//
    Texture TitleTexture;
    Texture StartTexture;
    Texture BFSTexture;
    Texture IDATexture;
    Texture InfoBoxTexture;
    Texture ScrambleTexture;
    Texture SolveTexture;

    Sprite TitleSprite;
    Sprite StartSprite;
    Sprite BFSSprite;
    Sprite IDASprite;
    Sprite InfoBoxSprite;
    Sprite ScrambleSprite;
    Sprite SolveSprite;

    vector<string> Text = {"Title", "Start", "BFS", "IDA", "Info Box", "Scramble","Solve"};
    vector<Texture*> TextTextures = {&TitleTexture, &StartTexture, &BFSTexture,
                                     &IDATexture, &InfoBoxTexture, &ScrambleTexture, &SolveTexture};
    vector<Sprite*> TextSprites = {&TitleSprite, &StartSprite, &BFSSprite,
                                   &IDASprite, &InfoBoxSprite, &ScrambleSprite, &SolveSprite};

    //========================================= Number Variables =========================================//
    Texture OneTexture;
    Texture TwoTexture;
    Texture ThreeTexture;
    Texture FourTexture;
    Texture FiveTexture;
    Texture SixTexture;
    Texture SevenTexture;
    Texture EightTexture;
    Texture NineTexture;

    Sprite OneSprite;
    Sprite TwoSprite;
    Sprite ThreeSprite;
    Sprite FourSprite;
    Sprite FiveSprite;
    Sprite SixSprite;
    Sprite SevenSprite;
    Sprite EightSprite;
    Sprite NineSprite;

    vector<Texture*> NumberTextures = {&OneTexture, &TwoTexture, &ThreeTexture, &FourTexture, &FiveTexture, &SixTexture,
                                       &SevenTexture, &EightTexture, &NineTexture};

    vector<Sprite*> NumberSprites = {&OneSprite, &TwoSprite, &ThreeSprite, &FourSprite, &FiveSprite, &SixSprite,
                                     &SevenSprite, &EightSprite, &NineSprite};

    RectangleShape backgroundBoard;

    //========================================= Flying Variables =========================================//

    Texture Flying1;
    Texture Flying2;
    Texture Flying3;
    Texture Flying4;
    Texture Flying5;
    Texture Flying6;
    Texture Flying7;
    Texture Flying8;

    Sprite FlyingSprite1;
    Sprite FlyingSprite2;
    Sprite FlyingSprite3;
    Sprite FlyingSprite4;
    Sprite FlyingSprite5;
    Sprite FlyingSprite6;
    Sprite FlyingSprite7;
    Sprite FlyingSprite8;

    vector<string> flyingText = {"1", "2", "3", "4", "5", "6", "7", "8"};

    vector<Texture*> FlyingTextures = {&Flying1, &Flying2, &Flying3, &Flying4, &Flying5, &Flying6, &Flying7, &Flying8};

    vector<Sprite*> FlyingSprites = {&FlyingSprite1, &FlyingSprite2, &FlyingSprite3, &FlyingSprite4, &FlyingSprite5,
                                     &FlyingSprite6, &FlyingSprite7, &FlyingSprite8};

    vector<Vector2f> directions;

    string loadFile;

    Images(){
        loadImages();
    };

    Images(int &width, int &height){
        loadImages();
        setPositions(width, height);
    }

    // Loads Textures for Text and numbers
    void loadTextures(){

        // Loads text textures
        for(int i = 0; i < Text.size(); i++){
            loadFile = "../IMAGES/TileTango Text/" + Text[i] + ".png";

            if(!TextTextures[i]->loadFromFile(loadFile)){
                cout << "Error loading " + loadFile << endl;
            }
        }

        // Loads number textures
        for(int i = 0; i < NumberSprites.size(); i++){
            loadFile = "../IMAGES/TileTango Numbers/" + to_string(i+1) + ".png";
            if(!NumberTextures[i]->loadFromFile(loadFile)){
                cout << "Error loading " + loadFile << endl;
            }
        }

        // Loads flying textures
        for(int i = 0; i < FlyingTextures.size(); i++){
            loadFile ="../IMAGES/Flying Objs/" + to_string(i + 1) + ".png";
            if(!FlyingTextures[i]->loadFromFile(loadFile)){
                cout << "Error loading " + loadFile << endl;
            }
        }
    }

    // Loads text and number sprites
    void loadImages(){
        loadTextures();

        // Loads Text Sprite
        for(int i = 0; i < Text.size(); i++){
            TextSprites[i]->setTexture(*TextTextures[i]);
        }

        // Loads number sprites
        for(int i = 0; i < NumberTextures.size(); i++){
            NumberSprites[i]->setTexture(*NumberTextures[i]);
        }

        // loads flying sprites
        for(int i = 0; i < FlyingTextures.size(); i++){
            FlyingSprites[i]->setTexture(*FlyingTextures[i]);
        }

        RectangleShape temp(Vector2f(OneSprite.getGlobalBounds().width * 3, OneSprite.getGlobalBounds().height * 3));
        backgroundBoard = temp;
        backgroundBoard.setOrigin(backgroundBoard.getGlobalBounds().width / 2.0f, backgroundBoard.getGlobalBounds().height / 2.0f);
        backgroundBoard.setFillColor(Color(sf::Color::Transparent));
        backgroundBoard.setOutlineColor(Color(255, 114, 79));
        backgroundBoard.setOutlineThickness(35);

    }

    void setDirections(){
        float deltaTime = clock.restart().asSeconds();
        for(int i = 0; i < FlyingSprites.size(); i++){
            Vector2f position = FlyingSprites[i]->getPosition();
            position += directions[i] * deltaTime;

            // checks window counds and reverse direction if needed
            if(position.x < 0 || position.x + FlyingTextures[i]->getSize().x > width){
                directions[i].x = -directions[i].x;
            }
            if(position.y < 0 || position.y + FlyingTextures[i]->getSize().y > height){
                directions[i].y = -directions[i].y;
            }

            FlyingSprites[i]->setPosition(position);
        }
    }

    // Sets sprite positions
    void setPositions(int &width, int &height){

        // Sets origin of Texts to center
        for(int i = 0; i < Text.size(); i++){
            TextSprites[i]->setOrigin(TextSprites[i]->getGlobalBounds().width / 2.0f, TextSprites[i]->getGlobalBounds().height / 2.0f);
        }

        // Sets origin of numbers to center
        for(int i = 0; i < NumberSprites.size(); i++){
            NumberSprites[i]->setOrigin(NumberSprites[i]->getGlobalBounds().width / 2.0f, NumberSprites[i]->getGlobalBounds().height / 2.0f);
        }

        // Sets origin of flying numbers to center
        for(int i = 0; i < FlyingTextures.size(); i++){
            FlyingSprites[i]->setOrigin(FlyingSprites[i]->getGlobalBounds().width / 2.0f, FlyingSprites[i]->getGlobalBounds().height / 2.0f);
        }

        //========================================= Sets position of Text Sprites =========================================//
        float current = 140;
        float totalSpace = width - (current * 2);


        TitleSprite.setPosition(width / 2.0f, height / 8.0f);
        StartSprite.setPosition(width / 2.0f, (height / 8.0f) * 5);

        BFSSprite.setPosition((width / 7.0f) * 2 - 70, (height / 8.0f) * 2);
        IDASprite.setPosition((width / 7.0f) * 5 + 70, (height / 8.0f) * 2);
        InfoBoxSprite.setPosition(width / 2.0f, height/ 2.0f - 115);

        ScrambleSprite.setPosition((width / 7.0f) * 2 - 70, (height / 8.0f) * 7);
        SolveSprite.setPosition((width / 7.0f) * 5 + 70, (height / 8.0f) * 7);

        for(int i = 0; i < FlyingSprites.size(); i++){
            // sets random position within window bounds
            FlyingSprites[i]->setPosition(rand() % width, rand() % height);

            // sets random movement direction
            angle = (rand() % 360) * 3.14159265358979323846f / 180.0f;
            speed = 100.0f;
            Vector2f direction(cos(angle) * speed, sin(angle) * speed);

            directions.push_back(direction);
        }

    }
};