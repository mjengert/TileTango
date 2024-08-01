#include "Images.h"

struct GameWindow{
    RenderWindow window;
    Event event;
    Mouse mouse;
    Images images;

    GameWindow(int &width, int &height, Images &images){
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

    void GameDisplay(){
        window.clear(Color(63, 63, 131));
        window.draw(images.BFSSprite);
        window.draw(images.IDASprite);
        window.draw(images.MainMenuSprite);
        window.draw(images.ScrambleSprite);
        window.draw(images.FastestAlgorithmSprite);
        window.draw(images.SolveSprite);
        window.display();
    }
};