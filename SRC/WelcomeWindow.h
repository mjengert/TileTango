#include "GameBoardWindow.h"
using namespace std;
using namespace sf;

struct Images{
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
    }
};

struct WelcomeWindow{
    RenderWindow window;
    Event event;
    Mouse mouse;
    Font font;
    Images images;

    WelcomeWindow(int &width, int &height){
        images.setPositions(width, height);
        window.create(VideoMode(width, height), "Tile Tango");

        while(window.isOpen()){
            while(window.pollEvent(event)){
                if(event.type == Event::Closed){
                    window.close();
                }
                if(event.type == Event::MouseButtonPressed){
                    if(images.EasySprite.getGlobalBounds().contains(mouse.getPosition(window).x,mouse.getPosition(window).y)){
                        cout << "Easy" << endl;
                        window.close();
                        GameWindow gameWindow(width, height);
                    }
                    else if(images.MediumSprite.getGlobalBounds().contains(mouse.getPosition(window).x,mouse.getPosition(window).y)){
                        cout << "Medium" << endl;
                        window.close();
                        GameWindow gameWindow(width, height);
                    }
                    else if(images.HardSprite.getGlobalBounds().contains(mouse.getPosition(window).x,mouse.getPosition(window).y)){
                        cout << "Hard" << endl;
                        window.close();
                        GameWindow gameWindow(width, height);
                    }
                }
            }

            welcomeDipslay(window, images);
        }
    }

    void welcomeDipslay(RenderWindow &window, Images &images){
        window.clear(Color(63, 63, 131));
        window.draw(images.TitleSprite);
        window.draw(images.EasySprite);
        window.draw(images.MediumSprite);
        window.draw(images.HardSprite);
        window.display();
    }
};