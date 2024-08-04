#include "GameBoardWindow.h"

struct WelcomeWindow{
    RenderWindow window;
    Event event;
    Mouse mouse;
    Font font;

    // Generates the welcome window
    WelcomeWindow(int &width, int &height){

        // Loads all the images
        Images images(width, height);
        window.create(VideoMode(width, height), "Tile Tango: Welcome");

        while(window.isOpen()){
            while(window.pollEvent(event)){
                if(event.type == Event::Closed){
                    window.close();
                }

                // Checks for if mouse is pressed
                if(event.type == Event::MouseButtonPressed){

                    // Button execution
                    if(images.StartSprite.getGlobalBounds().contains(mouse.getPosition(window).x,mouse.getPosition(window).y)){
                        cout << "Start" << endl;
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
        window.draw(images.StartSprite);
        window.display();
    }
};