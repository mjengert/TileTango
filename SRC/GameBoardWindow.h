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