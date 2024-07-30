#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

struct GameWindow{
    RenderWindow window;
    Event event;
    Mouse mouse;

    GameWindow(int &width, int &height){
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