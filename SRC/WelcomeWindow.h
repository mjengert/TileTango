#include "GameBoardWindow.h"

struct WelcomeWindow{
    RenderWindow window;
    Event event;
    Mouse mouse;
    Font font;

    WelcomeWindow(int &width, int &height){
        Images images(width, height);
        window.create(VideoMode(width, height), "Tile Tango");

        while(window.isOpen()){
            while(window.pollEvent(event)){
                if(event.type == Event::Closed){
                    window.close();
                }
                if(event.type == Event::MouseButtonPressed){
                    if(images.StartSprite.getGlobalBounds().contains(mouse.getPosition(window).x,mouse.getPosition(window).y)){
                        cout << "Start" << endl;
                        window.close();
                        GameWindow gameWindow(width, height, images);
                    }
                    else if(images.InfoSprite.getGlobalBounds().contains(mouse.getPosition(window).x,mouse.getPosition(window).y)){
                        GameWindow gameWindow(width, height, images);
                    }
                }
            }

            welcomeDipslay(window, images);
        }
    }

    void welcomeDipslay(RenderWindow &window, Images &images){
        window.clear(Color(63, 63, 131));
        window.draw(images.TitleSprite);
        window.draw(images.StartSprite);
        window.draw(images.InfoSprite);
        window.display();
    }
};