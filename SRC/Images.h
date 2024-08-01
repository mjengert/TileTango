#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

struct Images{
    int width, height;

    //========================================= Title Text Variables =========================================//
    Texture TitleTexture;
    Texture StartTexture;
    Texture BFSTexture;
    Texture FastestAlgorithmTexture;
    Texture IDATexture;
    Texture InfoTexture;
    Texture MainMenuTexture;
    Texture ScrambleTexture;
    Texture SolveTexture;

    Sprite TitleSprite;
    Sprite StartSprite;
    Sprite BFSSprite;
    Sprite FastestAlgorithmSprite;
    Sprite IDASprite;
    Sprite InfoSprite;
    Sprite MainMenuSprite;
    Sprite ScrambleSprite;
    Sprite SolveSprite;

    vector<string> Text = {"Title", "Start", "BFS", "Fastest Algorithm",
                           "IDA", "Info", "Main Menu", "Scramble","Solve"};
    vector<Texture*> TextTextures = {&TitleTexture, &StartTexture, &BFSTexture, &FastestAlgorithmTexture,
                                     &IDATexture, &InfoTexture, &MainMenuTexture,
                                     &ScrambleTexture, &SolveTexture};
    vector<Sprite*> TextSprites = {&TitleSprite, &StartSprite, &BFSSprite, &FastestAlgorithmSprite,
                                   &IDASprite, &InfoSprite, &MainMenuSprite,
                                   &ScrambleSprite, &SolveSprite};

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
    Texture TenTexture;
    Texture ElevenTexture;
    Texture TwelveTexture;
    Texture ThirteenTexture;
    Texture FourteenTexture;
    Texture FifteenTexture;

    Sprite OneSprite;
    Sprite TwoSprite;
    Sprite ThreeSprite;
    Sprite FourSprite;
    Sprite FiveSprite;
    Sprite SixSprite;
    Sprite SevenSprite;
    Sprite EightSprite;
    Sprite NineSprite;
    Sprite TenSprite;
    Sprite ElevenSprite;
    Sprite TwelveSprite;
    Sprite ThirteenSprite;
    Sprite FourteenSprite;
    Sprite FifteenSprite;

    vector<Texture*> NumberTextures = {&OneTexture, &TwoTexture, &ThreeTexture, &FourTexture, &FiveTexture, &SixTexture,
                                       &SevenTexture, &EightTexture, &NineTexture, &TenTexture, &ElevenTexture, &TwelveTexture,
                                       &ThirteenTexture, &FourteenTexture, &FifteenTexture};

    vector<Sprite*> NumberSprites = {&OneSprite, &TwoSprite, &ThreeSprite, &FourSprite, &FiveSprite, &SixSprite,
                                     &SevenSprite, &EightSprite, &NineSprite, &TenSprite, &ElevenSprite, &TwelveSprite,
                                     &ThirteenSprite, &FourteenSprite, &FifteenSprite};

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

        //========================================= Sets position of Text Sprites =========================================//
        float current = 140;
        float totalSpace = width - (current * 2);


        TitleSprite.setPosition(width / 2.0f, height / 8.0f);
        StartSprite.setPosition(width / 3.0f, (height / 8.0f) * 5);
        InfoSprite.setPosition((width / 3.0f) * 2, (height / 8.0f) * 5);

        BFSSprite.setPosition((width / 7.0f) * 2 - 70, (height / 8.0f) * 2);
        IDASprite.setPosition((width / 7.0f) * 5 + 70, (height / 8.0f) * 2);
        FastestAlgorithmSprite.setPosition(width / 2.0f, height / 8.0f);

        current = 140;
        totalSpace = width - (current * 2);

        MainMenuSprite.setPosition(current, (height / 8.0f) * 7);
        current += totalSpace / 2.0f;
        ScrambleSprite.setPosition(current, (height / 8.0f) * 7);
        current += totalSpace / 2.0f;
        SolveSprite.setPosition(current, (height / 8.0f) * 7);

    }
};