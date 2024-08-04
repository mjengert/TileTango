#include "Images.h"
#include "SlidingBoardGraph.h"

struct GameWindow{
    RenderWindow window;
    Event event;
    Mouse mouse;
    Images images;
    int width;
    int height;



    // Fake generated boards to set up a tile drawing system
    SlidingBoard* root;
    int IDABoard[3][3];
    int BFSBoard[3][3];

    // Game window set up
    GameWindow(int &width, int &height, Images &images, SlidingBoardGraph &Graph){
        this->width = width;
        this->height = height;
        this->images = images;
        window.create(VideoMode(width, height), "Tile Tango: Game");
        Graph.GetBoardFromFile("../DATA/AllBoards.txt");
        generatingGraph(Graph.GetRoot());

        while(window.isOpen()){
            while(window.pollEvent(event)){

                if(event.type == Event::Closed){
                    window.close();
                }

                // Button Executions
                if(event.type == Event::MouseButtonPressed){
                    if(images.ScrambleSprite.getGlobalBounds().contains(mouse.getPosition(window).x,mouse.getPosition(window).y)){
                        Graph.GetBoardFromFile("../DATA/AllBoards.txt");
                        generatingGraph(Graph.GetRoot());
                    }
                    else if(images.SolveSprite.getGlobalBounds().contains(mouse.getPosition(window).x,mouse.getPosition(window).y)){
                        Graph.GetAllMoves(root, 0);
                        cout << "Solve" << endl;
                    }

                    // Need to add button executions
                }
            }

            // Prints out the game
            GameDisplay();
        }
    }

    void generatingGraph(SlidingBoard* root){
        this->root = root;
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                IDABoard[i][j] = root->Board[i][j];
                BFSBoard[i][j] = root->Board[i][j];
            }
        }
    }

    // Sets up the number tiles based on the board input
    void setNumberPositons(int board[3][3], float currentX, float currentY){

        images.backgroundBoard.setPosition(currentX + (images.OneSprite.getGlobalBounds().getSize().x), currentY + (images.OneSprite.getGlobalBounds().getSize().y));
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
        window.draw(images.ScrambleSprite);
        window.draw(images.SolveSprite);
        window.draw(images.InfoBoxSprite);
        setNumberPositons(IDABoard, images.IDASprite.getGlobalBounds().left + 55, (images.SolveSprite.getGlobalBounds().top + images.IDASprite.getGlobalBounds().height) / 2.0f);
        setNumberPositons(BFSBoard, images.BFSSprite.getGlobalBounds().left + 55, (images.SolveSprite.getGlobalBounds().top + images.IDASprite.getGlobalBounds().height) / 2.0f);
        window.display();
    }
};