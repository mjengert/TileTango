#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

struct welcomeWindow{
    RenderWindow window;
    Font font;
    Text titleMessage;
    Text welcomeMessage;
    RectangleShape titleBox;
    RectangleShape easyBox;
    RectangleShape mediumBox;
    RectangleShape hardBox;
    Mouse mouse;
    vector<RectangleShape*> buttons;
    Text easy;
    Text medium;
    Text hard;
    vector<Text*> buttonTexts;
    Event event;
    float totalButtonTextWidth;
    float totalButtonSpacing;
    float spacingBetweenButtons;
    int width;
    int height;

    welcomeWindow(int &width, int &height){
        this->width = width;
        this->height = height;

        // Creates window
        window.create(VideoMode(width, height), "Tile Tango");

        // Creates the font
        if(!font.loadFromFile("files/OleoScript-Regular.ttf")){
            cout << "failed to load font." << endl;
        }

        createTitleMessage();
        titleBox = createTitleBox(titleMessage, 10.0f);
        createWelcomeMessage();
        createButtonText();
        createRectangleButton(easy, easyBox);
        createRectangleButton(medium, mediumBox);
        createRectangleButton(hard, hardBox);

        while(window.isOpen()){

            while(window.pollEvent(event)){
                if(event.type == Event::Closed){
                    window.close();
                }
                else if(event.type == Event::MouseButtonPressed){
                    if(easyBox.getGlobalBounds().contains(mouse.getPosition(window).x,mouse.getPosition(window).y)){
                        cout << "easy" << endl;
                    }
                    else if(mediumBox.getGlobalBounds().contains(mouse.getPosition(window).x,mouse.getPosition(window).y)){
                        cout << "medium" << endl;
                    }
                    else if(hardBox.getGlobalBounds().contains(mouse.getPosition(window).x,mouse.getPosition(window).y)){
                        cout << "hard" << endl;
                    }
                    else if(welcomeMessage.getGlobalBounds().contains(mouse.getPosition(window).x,mouse.getPosition(window).y)){
                        cout << "suffer" << endl;
                    }
                }
            }

            welcomeDipslay();
        }
    }

    void setTextFont(Text& text, Font &font, int size, Color color, string message){
        text.setFont(font);
        text.setString(message);
        text.setCharacterSize(size);
        text.setFillColor(color);
    }

    void createTitleMessage(){
        setTextFont(titleMessage, font, 50, Color::White, "Tile Tango");

        // Center text
        FloatRect textRect = titleMessage.getLocalBounds();
        titleMessage.setOrigin(textRect.left + textRect.width/2.0f, textRect.top+textRect.height/2.0f);
        titleMessage.setPosition(window.getSize().x/2.0f, (window.getSize().y/2.0f)-150);
    }

    RectangleShape createTitleBox(Text &text, float padding = 10.0f){
        FloatRect  textRect = text.getLocalBounds();
        RectangleShape titleBox(Vector2f(textRect.width + 2 * padding, textRect.height + 2 * padding));
        titleBox.setFillColor(Color::Green);
        titleBox.setOutlineThickness(5);
        titleBox.setOutlineColor(Color::Black);

        titleBox.setOrigin(titleBox.getSize().x/2.0f, titleBox.getSize().y/2.0f);
        titleBox.setPosition(window.getSize().x/2.0f, (window.getSize().y/2.0f)-150);
        return titleBox;
    }

    void createWelcomeMessage(){
        setTextFont(welcomeMessage, font, 20, Color::White, "Select how you want to suffer!");

        // Center text
        FloatRect textRect = welcomeMessage.getGlobalBounds();
        welcomeMessage.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
        welcomeMessage.setPosition(window.getSize().x/2.0f, (window.getSize().y/2.0f)-75);
    }

    void createRectangleButton(Text &text, RectangleShape &button, float padding = 10.0f){
        FloatRect  textRect = text.getLocalBounds();
        RectangleShape newButton(Vector2f(textRect.width + 2 * padding, textRect.height + 2 * padding));
        newButton.setFillColor(Color::Green);
        newButton.setOutlineThickness(5);
        newButton.setOutlineColor(Color::Black);

        newButton.setOrigin(newButton.getSize().x/2.0f, newButton.getSize().y/2.0f);
        newButton.setPosition(text.getPosition().x,text.getPosition().y);

        button = newButton;
    }

    void createButtonText(){
        totalButtonTextWidth = 0;
        buttonTexts.push_back(&easy);
        buttonTexts.push_back(&medium);
        buttonTexts.push_back(&hard);

        //------------------------------ SETTING UP TEXT ------------------------------//
        for(auto &text : buttonTexts){
            setTextFont(*text, font, 30, Color::White, "");
        }

        easy.setString("Easy");
        medium.setString("Medium");
        hard.setString("Hard");

        //------------------------------ POSITIONING TEXT ------------------------------//
        totalButtonSpacing = width - totalButtonTextWidth - easy.getLocalBounds().width;
        spacingBetweenButtons = totalButtonSpacing / 3;
        float currentX = easy.getLocalBounds().width;

        for(auto &text : buttonTexts){
            FloatRect textRect = text->getLocalBounds();
            text->setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
            text->setPosition(currentX, height / 2);
            currentX += textRect.width + spacingBetweenButtons;
        }
    }

    void welcomeDipslay(){
        window.clear(Color(26, 26, 119));
        window.draw(titleBox);
        window.draw(titleMessage);
        window.draw(welcomeMessage);
        window.draw(easyBox);
        window.draw(mediumBox);
        window.draw(hardBox);
        window.draw(easy);
        window.draw(medium);
        window.draw(hard);
        window.display();
    }
};