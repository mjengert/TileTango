#include "Images.h"

struct GameWindow{
    RenderWindow window;
    Event event;
    Mouse mouse;
    Images images;
    int width;
    int height;

    // Fake generated boards to set up a tile drawing system
    int IDABoard[3][3] = {{1, 2, 3},
                          {4, 2, 6},
                          {7, 8, 9}};

    int BFSBoard[3][3] = {{1, 2, 3},
                          {4, 2, 6},
                          {7, 8, 9}};

    // Game window set up
    GameWindow(int &width, int &height, Images &images){
        this->width = width;
        this->height = height;
        this->images = images;
        window.create(VideoMode(width, height), "Tile Tango: Game");

        while(window.isOpen()){
            while(window.pollEvent(event)){

                if(event.type == Event::Closed){
                    window.close();
                }

                // Button Executions
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

                    // Need to add button executions
                }
            }

            // Prints out the game
            GameDisplay();
        }
    }

    // Sets up the number tiles based on the board input
    void setNumberPositons(int board[3][3], float currentX, float currentY){

        images.backgroundBoard.setPosition(currentX + (images.OneSprite.getGlobalBounds().width * (3/4.0f)), currentY + (images.OneSprite.getGlobalBounds().height * (3/4.0f)));
        window.draw(images.backgroundBoard);

        for(int i = 0; i < 3; i++){ // Goes through every row

            // resets X position to keep rows in line
            float changingX = currentX;

            for(int j = 0; j < 3; j++){ // Goes through every column
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
//                else if(board[i][j] == 9){
//                    images.NineSprite.setPosition(changingX, currentY);
//                    window.draw(images.NineSprite);
//                }

                // Adjusts x position so each column is right next to the other
                changingX += images.OneSprite.getGlobalBounds().getSize().x;
            }
            // Adjusts y position so each row is on top of one another
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
        setNumberPositons(IDABoard, images.IDASprite.getGlobalBounds().left + 55, (images.MainMenuSprite.getGlobalBounds().top + images.IDASprite.getGlobalBounds().height) / 2.0f);
        setNumberPositons(BFSBoard, images.BFSSprite.getGlobalBounds().left + 55, (images.MainMenuSprite.getGlobalBounds().top + images.IDASprite.getGlobalBounds().height) / 2.0f);
        window.display();
    }
};