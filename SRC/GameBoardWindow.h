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
                }
            }

            GameDisplay();
        }
    }

    void setNumberPositons(int board[3][3], float currentX, float currentY){
        for(int i = 0; i < 3; i++){
            float changingX = currentX;
            for(int j = 0; j < 3; j++){
                if(board[i][j] == 1){
                    images.OneSprite.setPosition(changingX, currentY);
                    window.draw(images.OneSprite);
                }
                else if(board[i][j] == 2){
                    images.TwoSprite.setPosition(changingX, currentY);
                    window.draw(images.TwoSprite);
                }
                else if(board[i][j] == 3){
                    images.ThreeSprite.setPosition(changingX, currentY);
                    window.draw(images.ThreeSprite);
                }
                else if(board[i][j] == 4){
                    images.FourSprite.setPosition(changingX, currentY);
                    window.draw(images.FourSprite);
                }
                else if(board[i][j] == 5){
                    images.FiveSprite.setPosition(changingX, currentY);
                    window.draw(images.FiveSprite);
                }
                else if(board[i][j] == 6){
                    images.SixSprite.setPosition(changingX, currentY);
                    window.draw(images.SixSprite);
                }
                else if(board[i][j] == 7){
                    images.SevenSprite.setPosition(changingX, currentY);
                    window.draw(images.SevenSprite);
                }
                else if(board[i][j] == 8){
                    images.EightSprite.setPosition(changingX, currentY);
                    window.draw(images.EightSprite);
                }
                else if(board[i][j] == 9){
                    images.NineSprite.setPosition(changingX, currentY);
                    window.draw(images.NineSprite);
                }
                changingX += images.OneSprite.getGlobalBounds().getSize().x;
            }
            currentY += images.OneSprite.getGlobalBounds().getSize().y;
        }
    }

    void GameDisplay(){
        window.clear(Color(63, 63, 131));
        window.draw(images.IDASprite);
        window.draw(images.BFSSprite);
        window.draw(images.MainMenuSprite);
        window.draw(images.ScrambleSprite);
        window.draw(images.FastestAlgorithmSprite);
        window.draw(images.SolveSprite);
        setNumberPositons(IDABoard, 140, height / 3.0f);
        setNumberPositons(BFSBoard, width / 2.0f, height / 3.0f);
        window.display();
    }
};