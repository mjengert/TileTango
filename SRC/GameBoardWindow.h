#include "Images.h"

struct GameWindow{
    RenderWindow window;
    Event event;
    Mouse mouse;

    GameWindow(int &width, int &height, Images &images){
        window.create(VideoMode(width, height), "Tile Tango");

        while(window.isOpen()){
            while(window.pollEvent(event)){
                if(event.type == Event::Closed){
                    window.close();
                }
            }

            GameDisplay();
        }
    }

    void GameDisplay(){
        window.clear(Color(63, 63, 131));
        window.display();
    }
};