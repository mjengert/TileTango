#include "GameBoardWindow.h"
using namespace std;
using namespace sf;

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
                    if(images.EasySprite.getGlobalBounds().contains(mouse.getPosition(window).x,mouse.getPosition(window).y)){
                        cout << "Easy" << endl;
                        window.close();
                        GameWindow gameWindow(width, height, images);
                    }
                    else if(images.MediumSprite.getGlobalBounds().contains(mouse.getPosition(window).x,mouse.getPosition(window).y)){
                        cout << "Medium" << endl;
                        window.close();
                        GameWindow gameWindow(width, height, images);
                    }
                    else if(images.HardSprite.getGlobalBounds().contains(mouse.getPosition(window).x,mouse.getPosition(window).y)){
                        cout << "Hard" << endl;
                        window.close();
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
        window.draw(images.EasySprite);
        window.draw(images.MediumSprite);
        window.draw(images.HardSprite);
        window.display();
    }
};