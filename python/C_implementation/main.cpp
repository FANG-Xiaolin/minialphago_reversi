#include <iostream>
//#include "Board.h"
#include "MonteCarlo.h"
#include <algorithm>

#define MAX_ITER 1000


const clock_t startTime = clock();
const clock_t TIMELIMIT = CLOCKS_PER_SEC;

int myState= 1;//1:black -1:white
using namespace std;


int current_player = 1 ;//1:black -1: white

//compare function for max_element
static bool comp(const TreeNode* s1, const TreeNode* s2){
//    return s1->timesOfWin/s1->totalVisit<s2->timesOfWin/s2->totalVisit;
    return s1->totalVisit<s2->totalVisit;//据说有奇效？
};

int main() {
    Board GameBoard;
    //initial
    GameBoard.initialGame();
    GameBoard.showBoard();



    while(1){
        //current player have valid move
        if (GameBoard.checkHasValidMove()) {
            cout<<endl;
            if (GameBoard.player==1) {
                cout<<"It's black turn"<<endl;
            } else cout<<"It's white turn"<<endl;

            int x,y;
            if (GameBoard.player==myState) {//first turn
                cin>>x>>y;
//                place a piece and check if it is legal
                while(!GameBoard.ProcStep(x,y, false)){
                    cout<<"illegal move"<<endl;
                    cin>>x>>y;
                }
//                cout<<"Monte-Carlo AI1 begin!"<<endl;
//                TreeNode mm2= TreeNode(GameBoard);
//                for (int i = 0; i < 100; ++i) {
//                    mm2.doMove();
//                }
//
//                double  best_value = 0;
//
//                auto bestChoice = std::max_element(mm2.child.begin(), mm2.child.end(),comp);
//
//                best_value = (*bestChoice)->getGrade();
//                cout<<"best win rate 1 :"<<best_value<<"\n";
//
//                GameBoard = (*bestChoice)->tmpBoard;
//
//                cout<<"Monte AI 1 Done!"<<endl;
//
//                GameBoard.player*=-1;//extra change of player for that we use monte-carlo to choose a best child,while the player of child has been changed; double change=>no change

            }else{
                cout<<"Monte-Carlo AI2 begin!"<<endl;

                TreeNode mm= TreeNode(GameBoard);


                for (int i = 0; i < MAX_ITER; ++i) {
                    mm.doMove();
                }

                double  best_value = 0;
                auto iter = mm.child.begin();

                auto bestChoice = std::max_element(mm.child.begin(), mm.child.end(),comp);

                best_value = (*bestChoice)->getGrade();
                cout<<"best win rate 2 :"<<best_value<<"\n";

                GameBoard = (*bestChoice)->tmpBoard;

                cout<<"Monte AI 2 Done!"<<endl;

                GameBoard.player*=-1;//extra change of player for that we use monte-carlo to choose a best child,while the player of child has been changed; double change=>no change

            }


            GameBoard.showBoard();
            cout<<"ply:"<<GameBoard.player<<endl;
            GameBoard.player*=-1;//change player uniformly
        } else{


                cout<<"No legal move. Change color."<<endl;
                GameBoard.player*=-1;
            if (!GameBoard.checkHasValidMove()){//both have no legal move; game end.
                break;
            }
        }

    }
    GameBoard.judge();//judge who wins game
    return 0;
}
