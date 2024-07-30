#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

struct Images{
    int width, height;
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
    string loadFile;

    Images(){
        loadImages();
    };

    Images(int &width, int &height){
        loadImages();
        setPositions(width, height);
    }

    void loadTextures(){
        for(int i = 0; i < Text.size(); i++){
            loadFile = "../IMAGES/TileTango Text/" + Text[i] + ".png";

            if(!TextTextures[i]->loadFromFile(loadFile)){
                cout << "Error loading " + loadFile << endl;
            }
        }
    }

    void loadImages(){
        loadTextures();
        for(int i = 0; i < Text.size(); i++){
            TextSprites[i]->setTexture(*TextTextures[i]);
        }

    }

    void setPositions(int &width, int &height){
        for(int i = 0; i < Text.size(); i++){
            TextSprites[i]->setOrigin(TextSprites[i]->getGlobalBounds().width / 2.0f, TextSprites[i]->getGlobalBounds().height / 2.0f);
        }

        float current = 140;
        float totalSpace = width - (current * 2);


        TitleSprite.setPosition(width / 2.0f, height / 8.0f);
        StartSprite.setPosition(width / 2.0f, (height / 8.0f) * 3);
        InfoSprite.setPosition(width / 2.0f, (height / 8.0f) * 5);

        BFSSprite.setPosition((width / 6.0f) * 2, (height / 8.0f) * 2);
        IDASprite.setPosition((width / 6.0f) * 4, (height / 8.0f) * 2);
        FastestAlgorithmSprite.setPosition(width / 2.0f, height / 8.0f);

        current = 140;
        totalSpace = width - (current * 2);

        MainMenuSprite.setPosition(current, (height / 8.0f) * 7);
        current += totalSpace / 3.0f;
        ScrambleSprite.setPosition(current, (height / 8.0f) * 7);
        current += totalSpace / 3.0f;
        SolveSprite.setPosition(current, (height / 8.0f) * 7);

    }
};