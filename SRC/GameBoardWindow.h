#include "Images.h"

struct GameWindow{
    RenderWindow window;
    Event event;
    Mouse mouse;
    Images images;
    int width;
    int height;
    int IDABoard[3][3] = {{1, 2, 3},
                          {4, 5, 6},
                          {7, 8, 9}};

    int BFSBoard[3][3] = {{1, 2, 3},
                          {4, 5, 6},
                          {7, 8, 9}};

    GameWindow(int &width, int &height, Images &images){
        this->width = width;
        this->height = height;
        this->images = images;
        setNumberPositons();
        window.create(VideoMode(width, height), "Tile Tango");

        while(window.isOpen()){
            while(window.pollEvent(event)){
                if(event.type == Event::Closed){
                    window.close();
                }
                if(event.type == Event::MouseButtonPressed){
                    if(images.MainMenuSprite.getGlobalBounds().contains(mouse.getPosition(window).x,mouse.getPosition(window).y)){
                        cout << "Start" << endl;
                    }
                    else if(images.ScrambleSprite.getGlobalBounds().contains(mouse.getPosition(window).x,mouse.getPosition(window).y)){
                        cout << "Scramble" << endl;
                    }
                    else if(images.SolveSprite.getGlobalBounds().contains(mouse.getPosition(window).x,mouse.getPosition(window).y)){
                        cout << "Solve" << endl;
                    }
                    setNumberPositons();
                }
            }

            GameDisplay();
        }
    }

    void setNumberPositons(){
        int currentY = width / 3.0f;

        for(int i = 0; i < 3; i++){
            int currentX = 140;
            for(int j = 0; j < 3; j++){
                if(IDABoard[i][j] == 1){
                    images.OneSprite.setPosition(currentX, currentY);
                }
                else if(IDABoard[i][j] == 2){
                    images.TwoSprite.setPosition(currentX, currentY);
                }
                else if(IDABoard[i][j] == 3){
                    images.ThreeSprite.setPosition(currentX, currentY);
                }
                else if(IDABoard[i][j] == 4){
                    images.FourSprite.setPosition(currentX, currentY);
                }
                else if(IDABoard[i][j] == 5){
                    images.FiveSprite.setPosition(currentX, currentY);
                }
                else if(IDABoard[i][j] == 6){
                    images.SixSprite.setPosition(currentX, currentY);
                }
                else if(IDABoard[i][j] == 7){
                    images.SevenSprite.setPosition(currentX, currentY);
                }
                else if(IDABoard[i][j] == 8){
                    images.EightSprite.setPosition(currentX, currentY);
                }
                else if(IDABoard[i][j] == 9){
                    images.NineSprite.setPosition(currentX, currentY);
                }

                currentX += images.OneSprite.getGlobalBounds().getSize().x;
            }
            currentY += images.OneSprite.getGlobalBounds().getSize().y;
        }
    }

    void GameDisplay(){
        window.clear(Color(63, 63, 131));
        window.draw(images.OneSprite);
        window.draw(images.TwoSprite);
        window.draw(images.ThreeSprite);
        window.draw(images.FourSprite);
        window.draw(images.FiveSprite);
        window.draw(images.SixSprite);
        window.draw(images.SevenSprite);
        window.draw(images.EightSprite);
        window.draw(images.NineSprite);
        window.draw(images.IDASprite);
        window.draw(images.BFSSprite);
        window.draw(images.MainMenuSprite);
        window.draw(images.ScrambleSprite);
        window.draw(images.FastestAlgorithmSprite);
        window.draw(images.SolveSprite);
        window.display();
    }
};