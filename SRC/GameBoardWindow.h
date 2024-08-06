#include "Images.h"
#include <chrono>
#include <thread>
#include "SlidingBoardGraph.h"

struct GameWindow{
    RenderWindow window;
    Event event;
    Mouse mouse;
    Images images;
    int width;
    int height;

    // Fake generated boards to set up a tile drawing system
    SlidingBoardGraph Graph;
    SlidingBoard* root;
    double IDADuration = 0;
    double BFSDuration = 0;


    // Game window set up
    GameWindow(int &width, int &height, Images &images, SlidingBoardGraph &Graph){
        this->width = width;
        this->height = height;
        this->images = images;
        window.create(VideoMode(width, height), "Tile Tango: Game");
        root = Graph.GetRoot();
        vector<vector<int>> BFSSol;
        vector<vector<int>> IDASol;
        bool solvingState = false;
        bool scrambleState = false;
        bool firstOpen = true;

        while(window.isOpen()){
            while(window.pollEvent(event)){

                if(event.type == Event::Closed){
                    window.close();
                }
                // Button Executions
                if(event.type == Event::MouseButtonPressed){
                    if(images.ScrambleSprite.getGlobalBounds().contains(mouse.getPosition(window).x,mouse.getPosition(window).y)){
                        Graph.GetBoardFromFile("../DATA/AllBoards.txt");
                        root = Graph.GetRoot();
                        cout << "Scramble" << endl;
                        solvingState = false;
                        scrambleState = true;
                    }
                    else if(images.SolveSprite.getGlobalBounds().contains(mouse.getPosition(window).x,mouse.getPosition(window).y)){
                        // solve using IDA*
                        auto IDAStart = chrono::high_resolution_clock::now();
                        IDASol = Graph.IDAStar(root, 0);
                        auto IDAEnd = chrono::high_resolution_clock::now();
                        IDADuration = chrono::duration_cast<chrono::milliseconds>(IDAEnd - IDAStart).count();

                        // solve using BFS
                        auto BFSStart = chrono::high_resolution_clock::now();
                        BFSSol = Graph.BFS(root);
                        auto BFSEnd = chrono::high_resolution_clock::now();
                        BFSDuration = chrono::duration_cast<chrono::milliseconds>(BFSEnd - BFSStart).count();
                        solvingState = true;
                        scrambleState = false;
                    }
                }
            }
            // Once solve button is clicked iterate through solution paths of both algorithms once
            if (solvingState){
                //TEMP DELETE AFTER IDA IMPLEMENTATION
                cout << "solving" << endl;

                // find largest grid vector
                bool BFSIsLower = false;
                int solvingLength = BFSSol.size();
                if (BFSSol.size() < IDASol.size()) {
                    solvingLength = IDASol.size();
                    BFSIsLower = true;
                }

                int IDABoardState[3][3];
                int BFSBoardState[3][3];
                int lowerCount;
                //start looping through each board sprite at 0.025 second intervals
                for (int higherCount = 0; higherCount < solvingLength; higherCount++) {
                    //maintain each index within bounds
                    lowerCount = higherCount;
                    if (BFSIsLower){
                        if(lowerCount >= BFSSol.size()){
                            lowerCount = BFSSol.size()-1;
                        }
                        if (lowerCount < 0){lowerCount = 0;}
                        //update the board array states for each algorithm
                        for (int i = 0; i < 3; i++){
                            for (int j = 0; j < 3; j++){
                                BFSBoardState[i][j] = BFSSol[lowerCount][i*3 + j];
                                IDABoardState[i][j] = IDASol[higherCount][i*3 + j];
                            }
                        }
                    }
                    else{
                        if(lowerCount >= IDASol.size()){
                            lowerCount = IDASol.size()-1;
                        }
                        if (lowerCount < 0) {lowerCount = 0;}
                        //update the board array states for each algorithm
                        for (int i = 0; i < 3; i++){
                            for (int j = 0; j < 3; j++){
                                BFSBoardState[i][j] = BFSSol[higherCount][i*3 + j];
                                IDABoardState[i][j] = IDASol[lowerCount][i*3 + j];
                            }
                        }
                    }
                    //Draw NEW board states
                    GameDisplay(BFSBoardState, IDABoardState);

                    //delay by 0.050 seconds
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                }
                solvingState = false;
            }

            // Prints out the game when scramble button is pressed or window first openned
            if(scrambleState or firstOpen) {
                GameDisplay();
                scrambleState = false;
                firstOpen = false;
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
        setNumberPositons(root->Board, images.IDASprite.getGlobalBounds().left + 55, (images.SolveSprite.getGlobalBounds().top + images.IDASprite.getGlobalBounds().height) / 2.0f);
        setNumberPositons(root->Board, images.BFSSprite.getGlobalBounds().left + 55, (images.SolveSprite.getGlobalBounds().top + images.IDASprite.getGlobalBounds().height) / 2.0f);
        window.display();
    }

    //game display for solving
    void GameDisplay(int BFSboard[3][3], int IDAboard[3][3]){
        window.clear(Color(63, 63, 131));
        window.draw(images.IDASprite);
        window.draw(images.BFSSprite);
        window.draw(images.ScrambleSprite);
        window.draw(images.SolveSprite);
        window.draw(images.InfoBoxSprite);
        setNumberPositons(IDAboard, images.IDASprite.getGlobalBounds().left + 55, (images.SolveSprite.getGlobalBounds().top + images.IDASprite.getGlobalBounds().height) / 2.0f);
        setNumberPositons(BFSboard, images.BFSSprite.getGlobalBounds().left + 55, (images.SolveSprite.getGlobalBounds().top + images.IDASprite.getGlobalBounds().height) / 2.0f);
        window.display();
    }
};