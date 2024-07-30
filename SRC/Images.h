#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

struct Images{
    int width, height;
    Texture TitleTexture;
    Texture EasyTexture;
    Texture MediumTexture;
    Texture HardTexture;
    Texture BFSTexture;
    Texture FastestAlgorithmTexture;
    Texture IDATexture;
    Texture InfoTexture;
    Texture MainMenuTexture;
    Texture ScrambleTexture;
    Texture SolveTexture;

    Sprite TitleSprite;
    Sprite EasySprite;
    Sprite MediumSprite;
    Sprite HardSprite;
    Sprite BFSSprite;
    Sprite FastestAlgorithmSprite;
    Sprite IDASprite;
    Sprite InfoSprite;
    Sprite MainMenuSprite;
    Sprite ScrambleSprite;
    Sprite SolveSprite;

    vector<string> Text = {"Title", "Easy", "Medium", "Hard", "BFS", "Fastest Algorithm",
                           "IDA", "Info", "Main Menu", "Scramble","Solve"};
    vector<Texture*> TextTextures = {&TitleTexture, &EasyTexture, &MediumTexture, &HardTexture,
                                     &BFSTexture, &FastestAlgorithmTexture, &IDATexture, &InfoTexture, &MainMenuTexture,
                                     &ScrambleTexture, &SolveTexture};
    vector<Sprite*> TextSprites = {&TitleSprite, &EasySprite, &MediumSprite, &HardSprite,
                                   &BFSSprite, &FastestAlgorithmSprite, &IDASprite, &InfoSprite,
                                   &MainMenuSprite, &ScrambleSprite, &SolveSprite};
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


        TitleSprite.setPosition(width / 2.0f,height / 2.0f);
        EasySprite.setPosition(current, (height / 3.0f) * 2);
        current += totalSpace / 2.0f;
        MediumSprite.setPosition(current, (height / 3.0f) * 2);
        current += totalSpace / 2.0f;
        HardSprite.setPosition(current, (height / 3.0f) * 2);

        BFSSprite.setPosition((width / 6.0f) * 2, (height / 8.0f) * 2);
        IDASprite.setPosition((width / 6.0f) * 4, (height / 8.0f) * 2);
        FastestAlgorithmSprite.setPosition(width / 2.0f, height / 8.0f);

        current = 140;
        totalSpace = width - (current * 2);

        MainMenuSprite.setPosition(current, (height / 8.0f) * 7);
        current += totalSpace / 3.0f;
        InfoSprite.setPosition(current, (height / 8.0f) * 7);
        current += totalSpace / 3.0f;
        ScrambleSprite.setPosition(current, (height / 8.0f) * 7);
        current += totalSpace / 3.0f;
        SolveSprite.setPosition(current, (height / 8.0f) * 7);

    }
};