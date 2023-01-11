#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <time.h>

using namespace sf;
using namespace std;

enum direction {LEFT, RIGHT, UP, DOWN, NULLL}; //possible directions
enum enemyMode {SCATTER, CHASE, FRIGHTENED}; //different ai modes for enemies

struct enemy{
    direction curDir;
    direction nextDir;
    RectangleShape spr;
    int sizeOfBlocks;
    Vector2f spawnLocation;
    bool isInPath = false;
    bool grey=false;
    Color origColor;

    //enemy movement
    void movement(RectangleShape &player, enemyMode type, RectangleShape &corner1, RectangleShape &corner2, RectangleShape &corner3, RectangleShape &corner4, float speed,
                  vector<RectangleShape> &blockZero, vector<RectangleShape> &blockOne, vector<RectangleShape> &blockTwo, vector<RectangleShape> &blockThree, vector<RectangleShape> &blockFour){
        //fix any offsets, so enemy doesn't go into block, always needs to be in even position
        if(type!=FRIGHTENED){
            if(int(spr.getPosition().x)%int(speed)!=0){
                if(curDir==LEFT){
                    spr.move(1,0);
                }
                if(curDir==RIGHT){
                    spr.move(-1,0);
                }
            }
            if(int(spr.getPosition().y)%int(speed)!=0){
                if(curDir==UP){
                    spr.move(0,1);
                }
                if(curDir==DOWN){
                    spr.move(0,-1);
                }
            }
        }

        for(int i=0;i<blockThree.size();i++){
            if(spr.getPosition()==blockThree[i].getPosition()) grey=true;
        }
        for(int i=0;i<blockTwo.size();i++){
            if(spr.getPosition()==blockTwo[i].getPosition()) grey=false;
        }
        if(!grey){
            if(type==SCATTER){ //if the enemy is on scatter, go through a set rectangular path
                spr.setFillColor(origColor);
                if(isInPath){ //if it's currently in the path, go
                    if(spr.getPosition()==corner1.getPosition()){
                        curDir = RIGHT;
                    }
                    if(spr.getPosition()==corner2.getPosition()){
                        curDir = DOWN;
                    }
                    if(spr.getPosition()==corner3.getPosition()){
                        curDir = LEFT;
                    }
                    if(spr.getPosition()==corner4.getPosition()){
                        curDir = UP;
                    }
                }else{ //if it's not currently in the path, find the path and go to it
                     if(corner1.getPosition().x<spr.getPosition().x&&corner1.getPosition().y<spr.getPosition().y){
                        for(int i = 0; i<blockOne.size(); i++){
                            if(spr.getPosition().x==blockOne[i].getPosition().x&&spr.getPosition().y-sizeOfBlocks==blockOne[i].getPosition().y&&curDir!=UP&&curDir!=DOWN){
                                nextDir=UP;
                            }
                        }
                        for(int i = 0; i<blockTwo.size(); i++){
                            if(spr.getPosition().x==blockTwo[i].getPosition().x&&spr.getPosition().y-sizeOfBlocks==blockTwo[i].getPosition().y&&curDir!=UP&&curDir!=DOWN){
                                nextDir=UP;
                            }
                        }
                        for(int i = 0; i<blockOne.size(); i++){
                            if(spr.getPosition().y==blockOne[i].getPosition().y&&spr.getPosition().x-sizeOfBlocks==blockOne[i].getPosition().x&&curDir!=LEFT&&curDir!=RIGHT){
                                nextDir=LEFT;
                            }
                        }
                        for(int i = 0; i<blockTwo.size(); i++){
                            if(spr.getPosition().y==blockTwo[i].getPosition().y&&spr.getPosition().x-sizeOfBlocks==blockTwo[i].getPosition().x&&curDir!=LEFT&&curDir!=RIGHT){
                                nextDir=LEFT;
                            }
                        }
                    }else if(corner1.getPosition().x<spr.getPosition().x&&corner1.getPosition().y>spr.getPosition().y){
                        for(int i = 0; i<blockOne.size(); i++){
                            if(spr.getPosition().x==blockOne[i].getPosition().x&&spr.getPosition().y+sizeOfBlocks==blockOne[i].getPosition().y&&curDir!=UP&&curDir!=DOWN){
                                nextDir=DOWN;
                            }
                        }
                        for(int i = 0; i<blockTwo.size(); i++){
                            if(spr.getPosition().x==blockTwo[i].getPosition().x&&spr.getPosition().y+sizeOfBlocks==blockTwo[i].getPosition().y&&curDir!=UP&&curDir!=DOWN){
                                nextDir=DOWN;
                            }
                        }
                        for(int i = 0; i<blockOne.size(); i++){
                            if(spr.getPosition().y==blockOne[i].getPosition().y&&spr.getPosition().x-sizeOfBlocks==blockOne[i].getPosition().x&&curDir!=LEFT&&curDir!=RIGHT){
                                nextDir=LEFT;
                            }
                        }
                        for(int i = 0; i<blockTwo.size(); i++){
                            if(spr.getPosition().y==blockTwo[i].getPosition().y&&spr.getPosition().x-sizeOfBlocks==blockTwo[i].getPosition().x&&curDir!=LEFT&&curDir!=RIGHT){
                                nextDir=LEFT;
                            }
                        }
                    }else if(corner1.getPosition().x>spr.getPosition().x&&corner1.getPosition().y<spr.getPosition().y){
                        for(int i = 0; i<blockOne.size(); i++){
                            if(spr.getPosition().x==blockOne[i].getPosition().x&&spr.getPosition().y-sizeOfBlocks==blockOne[i].getPosition().y&&curDir!=UP&&curDir!=DOWN){
                                nextDir=UP;
                            }
                        }
                        for(int i = 0; i<blockTwo.size(); i++){
                            if(spr.getPosition().x==blockTwo[i].getPosition().x&&spr.getPosition().y-sizeOfBlocks==blockTwo[i].getPosition().y&&curDir!=UP&&curDir!=DOWN){
                                nextDir=UP;
                            }
                        }
                        for(int i = 0; i<blockOne.size(); i++){
                            if(spr.getPosition().y==blockOne[i].getPosition().y&&spr.getPosition().x+sizeOfBlocks==blockOne[i].getPosition().x&&curDir!=LEFT&&curDir!=RIGHT){
                                nextDir=RIGHT;
                            }
                        }
                        for(int i = 0; i<blockTwo.size(); i++){
                            if(spr.getPosition().y==blockTwo[i].getPosition().y&&spr.getPosition().x+sizeOfBlocks==blockTwo[i].getPosition().x&&curDir!=LEFT&&curDir!=RIGHT){
                                nextDir=RIGHT;
                            }
                        }
                    }else if(corner1.getPosition().x>spr.getPosition().x&&corner1.getPosition().y>spr.getPosition().y){
                        for(int i = 0; i<blockOne.size(); i++){
                            if(spr.getPosition().x==blockOne[i].getPosition().x&&spr.getPosition().y+sizeOfBlocks==blockOne[i].getPosition().y&&curDir!=UP&&curDir!=DOWN){
                                nextDir=DOWN;
                            }
                        }
                        for(int i = 0; i<blockTwo.size(); i++){
                            if(spr.getPosition().x==blockTwo[i].getPosition().x&&spr.getPosition().y+sizeOfBlocks==blockTwo[i].getPosition().y&&curDir!=UP&&curDir!=DOWN){
                                nextDir=DOWN;
                            }
                        }
                        for(int i = 0; i<blockOne.size(); i++){
                            if(spr.getPosition().y==blockOne[i].getPosition().y&&spr.getPosition().x+sizeOfBlocks==blockOne[i].getPosition().x&&curDir!=LEFT&&curDir!=RIGHT){
                                nextDir=RIGHT;
                            }
                        }
                        for(int i = 0; i<blockTwo.size(); i++){
                            if(spr.getPosition().y==blockTwo[i].getPosition().y&&spr.getPosition().x+sizeOfBlocks==blockTwo[i].getPosition().x&&curDir!=LEFT&&curDir!=RIGHT){
                                nextDir=RIGHT;
                            }
                        }
                    }else if(corner1.getPosition().x==spr.getPosition().x&&curDir!=UP&&curDir!=DOWN){
                        if(corner1.getPosition().y>spr.getPosition().y) nextDir = DOWN;
                        if(corner1.getPosition().y<spr.getPosition().y) nextDir = UP;
                    }else if(corner1.getPosition().y==spr.getPosition().y&&curDir!=LEFT&&curDir!=RIGHT){
                        if(corner1.getPosition().x>spr.getPosition().x) nextDir = RIGHT;
                        if(corner1.getPosition().x<spr.getPosition().x) nextDir = LEFT;
                    }
                    for(int i = 0; i<blockZero.size(); i++){
                        if(curDir==UP){
                            if(spr.getPosition().y-sizeOfBlocks==blockZero[i].getPosition().y&&spr.getPosition().x==blockZero[i].getPosition().x) {
                                for(int i = 0; i<blockOne.size(); i++){
                                    if(spr.getPosition().y==blockOne[i].getPosition().y&&spr.getPosition().x+sizeOfBlocks==blockOne[i].getPosition().x){
                                        curDir=RIGHT;
                                    }else if(spr.getPosition().y==blockOne[i].getPosition().y&&spr.getPosition().x-sizeOfBlocks==blockOne[i].getPosition().x){
                                        curDir=LEFT;
                                    }
                                }
                                for(int i = 0; i<blockTwo.size(); i++){
                                    if(spr.getPosition().y==blockTwo[i].getPosition().y&&spr.getPosition().x+sizeOfBlocks==blockTwo[i].getPosition().x){
                                        curDir=RIGHT;
                                    }else if(spr.getPosition().y==blockTwo[i].getPosition().y&&spr.getPosition().x-sizeOfBlocks==blockTwo[i].getPosition().x){
                                        curDir=LEFT;
                                    }
                                }
                            }
                        }else if(curDir==DOWN){
                            if(spr.getPosition().y+sizeOfBlocks==blockZero[i].getPosition().y&&spr.getPosition().x==blockZero[i].getPosition().x) {
                                for(int i = 0; i<blockOne.size(); i++){
                                    if(spr.getPosition().y==blockOne[i].getPosition().y&&spr.getPosition().x+sizeOfBlocks==blockOne[i].getPosition().x){
                                        curDir=RIGHT;
                                    }else if(spr.getPosition().y==blockOne[i].getPosition().y&&spr.getPosition().x-sizeOfBlocks==blockOne[i].getPosition().x){
                                        curDir=LEFT;
                                    }
                                }
                                for(int i = 0; i<blockTwo.size(); i++){
                                    if(spr.getPosition().y==blockTwo[i].getPosition().y&&spr.getPosition().x+sizeOfBlocks==blockTwo[i].getPosition().x){
                                        curDir=RIGHT;
                                    }else if(spr.getPosition().y==blockTwo[i].getPosition().y&&spr.getPosition().x-sizeOfBlocks==blockTwo[i].getPosition().x){
                                        curDir=LEFT;
                                    }
                                }
                            }
                        }else if(curDir==LEFT){
                            if(spr.getPosition().x-sizeOfBlocks==blockZero[i].getPosition().x&&spr.getPosition().y==blockZero[i].getPosition().y) {
                                for(int i = 0; i<blockOne.size(); i++){
                                    if(spr.getPosition().y+sizeOfBlocks==blockOne[i].getPosition().y&&spr.getPosition().x==blockOne[i].getPosition().x){
                                        curDir=DOWN;
                                    }else if(spr.getPosition().y-sizeOfBlocks==blockOne[i].getPosition().y&&spr.getPosition().x==blockOne[i].getPosition().x){
                                        curDir=UP;
                                    }
                                }
                                for(int i = 0; i<blockTwo.size(); i++){
                                    if(spr.getPosition().y+sizeOfBlocks==blockTwo[i].getPosition().y&&spr.getPosition().x==blockTwo[i].getPosition().x){
                                        curDir=DOWN;
                                    }else if(spr.getPosition().y-sizeOfBlocks==blockTwo[i].getPosition().y&&spr.getPosition().x==blockTwo[i].getPosition().x){
                                        curDir=UP;
                                    }
                                }
                            }
                        }else if(curDir==RIGHT){
                            if(spr.getPosition().x+sizeOfBlocks==blockZero[i].getPosition().x&&spr.getPosition().y==blockZero[i].getPosition().y) {
                                for(int i = 0; i<blockOne.size(); i++){
                                    if(spr.getPosition().y+sizeOfBlocks==blockOne[i].getPosition().y&&spr.getPosition().x==blockOne[i].getPosition().x){
                                        curDir=DOWN;
                                    }else if(spr.getPosition().y-sizeOfBlocks==blockOne[i].getPosition().y&&spr.getPosition().x==blockOne[i].getPosition().x){
                                        curDir=UP;
                                    }
                                }
                                for(int i = 0; i<blockTwo.size(); i++){
                                    if(spr.getPosition().y+sizeOfBlocks==blockTwo[i].getPosition().y&&spr.getPosition().x==blockTwo[i].getPosition().x){
                                        curDir=DOWN;
                                    }else if(spr.getPosition().y-sizeOfBlocks==blockTwo[i].getPosition().y&&spr.getPosition().x==blockTwo[i].getPosition().x){
                                        curDir=UP;
                                    }
                                }
                            }
                        }
                    }
                    if(nextDir==DOWN){
                        for(int i = 0; i<blockOne.size(); i++){
                            if(spr.getPosition().x==blockOne[i].getPosition().x&&spr.getPosition().y+sizeOfBlocks==blockOne[i].getPosition().y){
                                curDir=DOWN;
                                nextDir=NULLL;
                            }
                        }
                        for(int i = 0; i<blockTwo.size(); i++){
                            if(spr.getPosition().x==blockTwo[i].getPosition().x&&spr.getPosition().y+sizeOfBlocks==blockTwo[i].getPosition().y){
                                curDir=DOWN;
                                nextDir=NULLL;
                            }
                        }
                    }else if(nextDir==LEFT){
                        for(int i = 0; i<blockOne.size(); i++){
                            if(spr.getPosition().y==blockOne[i].getPosition().y&&spr.getPosition().x-sizeOfBlocks==blockOne[i].getPosition().x){
                                curDir=LEFT;
                                nextDir=NULLL;
                            }
                        }
                        for(int i = 0; i<blockTwo.size(); i++){
                            if(spr.getPosition().y==blockTwo[i].getPosition().y&&spr.getPosition().x-sizeOfBlocks==blockTwo[i].getPosition().x){
                                curDir=LEFT;
                                nextDir=NULLL;
                            }
                        }
                    }else if(nextDir==UP){
                        for(int i = 0; i<blockOne.size(); i++){
                            if(spr.getPosition().x==blockOne[i].getPosition().x&&spr.getPosition().y-sizeOfBlocks==blockOne[i].getPosition().y){
                                curDir=UP;
                                nextDir=NULLL;
                            }
                        }
                        for(int i = 0; i<blockTwo.size(); i++){
                            if(spr.getPosition().x==blockTwo[i].getPosition().x&&spr.getPosition().y-sizeOfBlocks==blockTwo[i].getPosition().y){
                                curDir=UP;
                                nextDir=NULLL;
                            }
                        }
                    }else if(nextDir==RIGHT){
                        for(int i = 0; i<blockOne.size(); i++){
                            if(spr.getPosition().y==blockOne[i].getPosition().y&&spr.getPosition().x+sizeOfBlocks==blockOne[i].getPosition().x){
                                curDir=RIGHT;
                                nextDir=NULLL;
                            }
                        }
                        for(int i = 0; i<blockTwo.size(); i++){
                            if(spr.getPosition().y==blockTwo[i].getPosition().y&&spr.getPosition().x+sizeOfBlocks==blockTwo[i].getPosition().x){
                                curDir=RIGHT;
                                nextDir=NULLL;
                            }
                        }
                    }
                }
            }else if(type==FRIGHTENED){ //if the enemy should be turning randomly, if player eats big food
                Color dimmed(origColor.r,origColor.g,origColor.b,200);
                spr.setFillColor(dimmed);
                speed*=0.5;
                isInPath=false;

                if(curDir==UP||curDir==DOWN) nextDir=direction(rand() % 1+0);
                if(curDir==LEFT||curDir==RIGHT) nextDir=direction(rand() % 3+2);

                if(nextDir==DOWN){
                    for(int i = 0; i<blockOne.size(); i++){
                        if(spr.getPosition().x==blockOne[i].getPosition().x&&spr.getPosition().y+sizeOfBlocks==blockOne[i].getPosition().y){
                            curDir=DOWN;
                            nextDir=NULLL;
                        }
                    }
                    for(int i = 0; i<blockTwo.size(); i++){
                        if(spr.getPosition().x==blockTwo[i].getPosition().x&&spr.getPosition().y+sizeOfBlocks==blockTwo[i].getPosition().y){
                            curDir=DOWN;
                            nextDir=NULLL;
                        }
                    }
                }else if(nextDir==LEFT){
                    for(int i = 0; i<blockOne.size(); i++){
                        if(spr.getPosition().y==blockOne[i].getPosition().y&&spr.getPosition().x-sizeOfBlocks==blockOne[i].getPosition().x){
                            curDir=LEFT;
                            nextDir=NULLL;
                        }
                    }
                    for(int i = 0; i<blockTwo.size(); i++){
                        if(spr.getPosition().y==blockTwo[i].getPosition().y&&spr.getPosition().x-sizeOfBlocks==blockTwo[i].getPosition().x){
                            curDir=LEFT;
                            nextDir=NULLL;
                        }
                    }
                }else if(nextDir==UP){
                    for(int i = 0; i<blockOne.size(); i++){
                        if(spr.getPosition().x==blockOne[i].getPosition().x&&spr.getPosition().y-sizeOfBlocks==blockOne[i].getPosition().y){
                            curDir=UP;
                            nextDir=NULLL;
                        }
                    }
                    for(int i = 0; i<blockTwo.size(); i++){
                        if(spr.getPosition().x==blockTwo[i].getPosition().x&&spr.getPosition().y-sizeOfBlocks==blockTwo[i].getPosition().y){
                            curDir=UP;
                            nextDir=NULLL;
                        }
                    }
                }else if(nextDir==RIGHT){
                    for(int i = 0; i<blockOne.size(); i++){
                        if(spr.getPosition().y==blockOne[i].getPosition().y&&spr.getPosition().x+sizeOfBlocks==blockOne[i].getPosition().x){
                            curDir=RIGHT;
                            nextDir=NULLL;
                        }
                    }
                    for(int i = 0; i<blockTwo.size(); i++){
                        if(spr.getPosition().y==blockTwo[i].getPosition().y&&spr.getPosition().x+sizeOfBlocks==blockTwo[i].getPosition().x){
                            curDir=RIGHT;
                            nextDir=NULLL;
                        }
                    }
                }
                for(int i = 0; i<blockZero.size(); i++){
                    if(curDir==UP){
                        if(spr.getPosition().y-sizeOfBlocks==blockZero[i].getPosition().y&&spr.getPosition().x==blockZero[i].getPosition().x) curDir=DOWN;
                    }else if(curDir==DOWN){
                        if(spr.getPosition().y+sizeOfBlocks==blockZero[i].getPosition().y&&spr.getPosition().x==blockZero[i].getPosition().x) curDir=UP;
                    }else if(curDir==LEFT){
                        if(spr.getPosition().x-sizeOfBlocks==blockZero[i].getPosition().x&&spr.getPosition().y==blockZero[i].getPosition().y) curDir=RIGHT;
                    }else if(curDir==RIGHT){
                        if(spr.getPosition().x+sizeOfBlocks==blockZero[i].getPosition().x&&spr.getPosition().y==blockZero[i].getPosition().y) curDir=LEFT;
                    }
                }
            }else if(type==CHASE){ //if the enemy should be chasing the player around
                spr.setFillColor(origColor);
                isInPath=false;
                if(player.getPosition().x<spr.getPosition().x&&player.getPosition().y<spr.getPosition().y){
                    for(int i = 0; i<blockOne.size(); i++){
                        if(spr.getPosition().x==blockOne[i].getPosition().x&&spr.getPosition().y-sizeOfBlocks==blockOne[i].getPosition().y&&curDir!=UP&&curDir!=DOWN){
                            nextDir=UP;
                        }
                    }
                    for(int i = 0; i<blockTwo.size(); i++){
                        if(spr.getPosition().x==blockTwo[i].getPosition().x&&spr.getPosition().y-sizeOfBlocks==blockTwo[i].getPosition().y&&curDir!=UP&&curDir!=DOWN){
                            nextDir=UP;
                        }
                    }
                    for(int i = 0; i<blockOne.size(); i++){
                        if(spr.getPosition().y==blockOne[i].getPosition().y&&spr.getPosition().x-sizeOfBlocks==blockOne[i].getPosition().x&&curDir!=LEFT&&curDir!=RIGHT){
                            nextDir=LEFT;
                        }
                    }
                    for(int i = 0; i<blockTwo.size(); i++){
                        if(spr.getPosition().y==blockTwo[i].getPosition().y&&spr.getPosition().x-sizeOfBlocks==blockTwo[i].getPosition().x&&curDir!=LEFT&&curDir!=RIGHT){
                            nextDir=LEFT;
                        }
                    }
                }else if(player.getPosition().x<spr.getPosition().x&&player.getPosition().y>spr.getPosition().y){
                    for(int i = 0; i<blockOne.size(); i++){
                        if(spr.getPosition().x==blockOne[i].getPosition().x&&spr.getPosition().y+sizeOfBlocks==blockOne[i].getPosition().y&&curDir!=UP&&curDir!=DOWN){
                            nextDir=DOWN;
                        }
                    }
                    for(int i = 0; i<blockTwo.size(); i++){
                        if(spr.getPosition().x==blockTwo[i].getPosition().x&&spr.getPosition().y+sizeOfBlocks==blockTwo[i].getPosition().y&&curDir!=UP&&curDir!=DOWN){
                            nextDir=DOWN;
                        }
                    }
                    for(int i = 0; i<blockOne.size(); i++){
                        if(spr.getPosition().y==blockOne[i].getPosition().y&&spr.getPosition().x-sizeOfBlocks==blockOne[i].getPosition().x&&curDir!=LEFT&&curDir!=RIGHT){
                            nextDir=LEFT;
                        }
                    }
                    for(int i = 0; i<blockTwo.size(); i++){
                        if(spr.getPosition().y==blockTwo[i].getPosition().y&&spr.getPosition().x-sizeOfBlocks==blockTwo[i].getPosition().x&&curDir!=LEFT&&curDir!=RIGHT){
                            nextDir=LEFT;
                        }
                    }
                }else if(player.getPosition().x>spr.getPosition().x&&player.getPosition().y<spr.getPosition().y){
                    for(int i = 0; i<blockOne.size(); i++){
                        if(spr.getPosition().x==blockOne[i].getPosition().x&&spr.getPosition().y-sizeOfBlocks==blockOne[i].getPosition().y&&curDir!=UP&&curDir!=DOWN){
                            nextDir=UP;
                        }
                    }
                    for(int i = 0; i<blockTwo.size(); i++){
                        if(spr.getPosition().x==blockTwo[i].getPosition().x&&spr.getPosition().y-sizeOfBlocks==blockTwo[i].getPosition().y&&curDir!=UP&&curDir!=DOWN){
                            nextDir=UP;
                        }
                    }
                    for(int i = 0; i<blockOne.size(); i++){
                        if(spr.getPosition().y==blockOne[i].getPosition().y&&spr.getPosition().x+sizeOfBlocks==blockOne[i].getPosition().x&&curDir!=LEFT&&curDir!=RIGHT){
                            nextDir=RIGHT;
                        }
                    }
                    for(int i = 0; i<blockTwo.size(); i++){
                        if(spr.getPosition().y==blockTwo[i].getPosition().y&&spr.getPosition().x+sizeOfBlocks==blockTwo[i].getPosition().x&&curDir!=LEFT&&curDir!=RIGHT){
                            nextDir=RIGHT;
                        }
                    }
                }else if(player.getPosition().x>spr.getPosition().x&&player.getPosition().y>spr.getPosition().y){
                    for(int i = 0; i<blockOne.size(); i++){
                        if(spr.getPosition().x==blockOne[i].getPosition().x&&spr.getPosition().y+sizeOfBlocks==blockOne[i].getPosition().y&&curDir!=UP&&curDir!=DOWN){
                            nextDir=DOWN;
                        }
                    }
                    for(int i = 0; i<blockTwo.size(); i++){
                        if(spr.getPosition().x==blockTwo[i].getPosition().x&&spr.getPosition().y+sizeOfBlocks==blockTwo[i].getPosition().y&&curDir!=UP&&curDir!=DOWN){
                            nextDir=DOWN;
                        }
                    }
                    for(int i = 0; i<blockOne.size(); i++){
                        if(spr.getPosition().y==blockOne[i].getPosition().y&&spr.getPosition().x+sizeOfBlocks==blockOne[i].getPosition().x&&curDir!=LEFT&&curDir!=RIGHT){
                            nextDir=RIGHT;
                        }
                    }
                    for(int i = 0; i<blockTwo.size(); i++){
                        if(spr.getPosition().y==blockTwo[i].getPosition().y&&spr.getPosition().x+sizeOfBlocks==blockTwo[i].getPosition().x&&curDir!=LEFT&&curDir!=RIGHT){
                            nextDir=RIGHT;
                        }
                    }
                }else if(player.getPosition().x==spr.getPosition().x&&curDir!=UP&&curDir!=DOWN){
                    if(player.getPosition().y>spr.getPosition().y) nextDir = DOWN;
                    if(player.getPosition().y<spr.getPosition().y) nextDir = UP;
                }else if(player.getPosition().y==spr.getPosition().y&&curDir!=LEFT&&curDir!=RIGHT){
                    if(player.getPosition().x>spr.getPosition().x) nextDir = RIGHT;
                    if(player.getPosition().x<spr.getPosition().x) nextDir = LEFT;
                }
                for(int i = 0; i<blockZero.size(); i++){
                    if(curDir==UP){
                        if(spr.getPosition().y-sizeOfBlocks==blockZero[i].getPosition().y&&spr.getPosition().x==blockZero[i].getPosition().x) {
                            for(int i = 0; i<blockOne.size(); i++){
                                if(spr.getPosition().y==blockOne[i].getPosition().y&&spr.getPosition().x+sizeOfBlocks==blockOne[i].getPosition().x){
                                    curDir=RIGHT;
                                }else if(spr.getPosition().y==blockOne[i].getPosition().y&&spr.getPosition().x-sizeOfBlocks==blockOne[i].getPosition().x){
                                    curDir=LEFT;
                                }
                            }
                            for(int i = 0; i<blockTwo.size(); i++){
                                if(spr.getPosition().y==blockTwo[i].getPosition().y&&spr.getPosition().x+sizeOfBlocks==blockTwo[i].getPosition().x){
                                    curDir=RIGHT;
                                }else if(spr.getPosition().y==blockTwo[i].getPosition().y&&spr.getPosition().x-sizeOfBlocks==blockTwo[i].getPosition().x){
                                    curDir=LEFT;
                                }
                            }
                        }
                    }else if(curDir==DOWN){
                        if(spr.getPosition().y+sizeOfBlocks==blockZero[i].getPosition().y&&spr.getPosition().x==blockZero[i].getPosition().x) {
                            for(int i = 0; i<blockOne.size(); i++){
                                if(spr.getPosition().y==blockOne[i].getPosition().y&&spr.getPosition().x+sizeOfBlocks==blockOne[i].getPosition().x){
                                    curDir=RIGHT;
                                }else if(spr.getPosition().y==blockOne[i].getPosition().y&&spr.getPosition().x-sizeOfBlocks==blockOne[i].getPosition().x){
                                    curDir=LEFT;
                                }
                            }
                            for(int i = 0; i<blockTwo.size(); i++){
                                if(spr.getPosition().y==blockTwo[i].getPosition().y&&spr.getPosition().x+sizeOfBlocks==blockTwo[i].getPosition().x){
                                    curDir=RIGHT;
                                }else if(spr.getPosition().y==blockTwo[i].getPosition().y&&spr.getPosition().x-sizeOfBlocks==blockTwo[i].getPosition().x){
                                    curDir=LEFT;
                                }
                            }
                        }
                    }else if(curDir==LEFT){
                        if(spr.getPosition().x-sizeOfBlocks==blockZero[i].getPosition().x&&spr.getPosition().y==blockZero[i].getPosition().y) {
                            for(int i = 0; i<blockOne.size(); i++){
                                if(spr.getPosition().y+sizeOfBlocks==blockOne[i].getPosition().y&&spr.getPosition().x==blockOne[i].getPosition().x){
                                    curDir=DOWN;
                                }else if(spr.getPosition().y-sizeOfBlocks==blockOne[i].getPosition().y&&spr.getPosition().x==blockOne[i].getPosition().x){
                                    curDir=UP;
                                }
                            }
                            for(int i = 0; i<blockTwo.size(); i++){
                                if(spr.getPosition().y+sizeOfBlocks==blockTwo[i].getPosition().y&&spr.getPosition().x==blockTwo[i].getPosition().x){
                                    curDir=DOWN;
                                }else if(spr.getPosition().y-sizeOfBlocks==blockTwo[i].getPosition().y&&spr.getPosition().x==blockTwo[i].getPosition().x){
                                    curDir=UP;
                                }
                            }
                        }
                    }else if(curDir==RIGHT){
                        if(spr.getPosition().x+sizeOfBlocks==blockZero[i].getPosition().x&&spr.getPosition().y==blockZero[i].getPosition().y) {
                            for(int i = 0; i<blockOne.size(); i++){
                                if(spr.getPosition().y+sizeOfBlocks==blockOne[i].getPosition().y&&spr.getPosition().x==blockOne[i].getPosition().x){
                                    curDir=DOWN;
                                }else if(spr.getPosition().y-sizeOfBlocks==blockOne[i].getPosition().y&&spr.getPosition().x==blockOne[i].getPosition().x){
                                    curDir=UP;
                                }
                            }
                            for(int i = 0; i<blockTwo.size(); i++){
                                if(spr.getPosition().y+sizeOfBlocks==blockTwo[i].getPosition().y&&spr.getPosition().x==blockTwo[i].getPosition().x){
                                    curDir=DOWN;
                                }else if(spr.getPosition().y-sizeOfBlocks==blockTwo[i].getPosition().y&&spr.getPosition().x==blockTwo[i].getPosition().x){
                                    curDir=UP;
                                }
                            }
                        }
                    }
                }
                if(nextDir==DOWN){
                    for(int i = 0; i<blockOne.size(); i++){
                        if(spr.getPosition().x==blockOne[i].getPosition().x&&spr.getPosition().y+sizeOfBlocks==blockOne[i].getPosition().y){
                            curDir=DOWN;
                            nextDir=NULLL;
                        }
                    }
                    for(int i = 0; i<blockTwo.size(); i++){
                        if(spr.getPosition().x==blockTwo[i].getPosition().x&&spr.getPosition().y+sizeOfBlocks==blockTwo[i].getPosition().y){
                            curDir=DOWN;
                            nextDir=NULLL;
                        }
                    }
                }else if(nextDir==LEFT){
                    for(int i = 0; i<blockOne.size(); i++){
                        if(spr.getPosition().y==blockOne[i].getPosition().y&&spr.getPosition().x-sizeOfBlocks==blockOne[i].getPosition().x){
                            curDir=LEFT;
                            nextDir=NULLL;
                        }
                    }
                    for(int i = 0; i<blockTwo.size(); i++){
                        if(spr.getPosition().y==blockTwo[i].getPosition().y&&spr.getPosition().x-sizeOfBlocks==blockTwo[i].getPosition().x){
                            curDir=LEFT;
                            nextDir=NULLL;
                        }
                    }
                }else if(nextDir==UP){
                    for(int i = 0; i<blockOne.size(); i++){
                        if(spr.getPosition().x==blockOne[i].getPosition().x&&spr.getPosition().y-sizeOfBlocks==blockOne[i].getPosition().y){
                            curDir=UP;
                            nextDir=NULLL;
                        }
                    }
                    for(int i = 0; i<blockTwo.size(); i++){
                        if(spr.getPosition().x==blockTwo[i].getPosition().x&&spr.getPosition().y-sizeOfBlocks==blockTwo[i].getPosition().y){
                            curDir=UP;
                            nextDir=NULLL;
                        }
                    }
                }else if(nextDir==RIGHT){
                    for(int i = 0; i<blockOne.size(); i++){
                        if(spr.getPosition().y==blockOne[i].getPosition().y&&spr.getPosition().x+sizeOfBlocks==blockOne[i].getPosition().x){
                            curDir=RIGHT;
                            nextDir=NULLL;
                        }
                    }
                    for(int i = 0; i<blockTwo.size(); i++){
                        if(spr.getPosition().y==blockTwo[i].getPosition().y&&spr.getPosition().x+sizeOfBlocks==blockTwo[i].getPosition().x){
                            curDir=RIGHT;
                            nextDir=NULLL;
                        }
                    }
                }
            }

        }
        //if it hits teleportation block, teleport
        if(curDir==RIGHT){
                if(spr.getPosition().x+sizeOfBlocks==blockFour[1].getPosition().x+sizeOfBlocks&&spr.getPosition().y==blockFour[1].getPosition().y){
                        spr.setPosition(blockFour[0].getPosition().x-sizeOfBlocks,blockFour[0].getPosition().y);
                }
            }
        if(curDir==LEFT){
                if(spr.getPosition().x-sizeOfBlocks==blockFour[0].getPosition().x-sizeOfBlocks&&spr.getPosition().y==blockFour[0].getPosition().y){
                    spr.setPosition(blockFour[1].getPosition().x+sizeOfBlocks, blockFour[1].getPosition().y);
                }
            }
        //move according to curDir
        if(curDir==UP){
            spr.move(0,-speed);
            spr.setTextureRect(IntRect(32,32,32,32));
        }else if(curDir==DOWN){
            spr.move(0,speed);
            spr.setTextureRect(IntRect(0,32,32,32));
        }else if(curDir==LEFT){
            spr.move(-speed,0);
            spr.setTextureRect(IntRect(32,0,32,32));
        }else if(curDir==RIGHT){
            spr.move(speed,0);
            spr.setTextureRect(IntRect(0,0,32,32));
        }

        if(spr.getPosition()==corner1.getPosition()||spr.getPosition()==corner2.getPosition()||spr.getPosition()==corner3.getPosition()||spr.getPosition()==corner4.getPosition()){
        isInPath=true;
        }
    }

    bool colWithPlayer(RectangleShape &player, enemyMode type, int &score, int &activeEnemies){
        if(type!=FRIGHTENED){ //if collides while not frightened
            if(spr.getGlobalBounds().intersects(player.getGlobalBounds())){
                return true;
            }
        }else if(spr.getGlobalBounds().intersects(player.getGlobalBounds())){ //if it is frightened, reset enemy, and score player 1000 points
             restart();
             score+=1000;
             //activeEnemies--;
        }
        return false;
    }

    void restart(){
        spr.setPosition(spawnLocation);
        curDir=NULLL;
    }

    enemy(Vector2f p, Color c, direction d, direction n, int s, Texture &tyler){ //initialize location, direction, color, speed, and random seed
        spr.setSize(Vector2f(s,s));
        spr.setPosition(p);
        spawnLocation = p;
        spr.setFillColor(c);
        origColor=c;
        spr.setTexture(&tyler);
        spr.setTextureRect(IntRect(0,0,32,32));
        curDir = d;
        nextDir = n;
        sizeOfBlocks=s;
        srand(time(NULL));
    }
};


int main()
{
    RenderWindow window(VideoMode(768, 640), "SFML works!");
    window.setFramerateLimit(60);

    int sizeOfBlocks=32; //size of each tile
    int blocksPerX=window.getSize().x/sizeOfBlocks; //how many tiles on screen on x
    int blocksPerY=window.getSize().y/sizeOfBlocks; //how many tiles on screen on y
    vector<int> matrix = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, //Map creation
                          0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,0,
                          0,5,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,5,0,
                          0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,0,
                          0,1,0,0,1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,1,0,0,1,0,
                          0,1,1,1,1,0,0,0,1,1,1,0,0,1,1,1,0,0,0,1,1,1,1,0,
                          0,0,0,0,1,0,0,0,0,0,2,0,0,2,0,0,0,0,0,1,0,0,0,0,
                          0,0,0,0,1,0,0,0,2,2,2,2,2,2,2,2,0,0,0,1,0,0,0,0,
                          0,0,0,0,1,0,0,0,2,0,0,3,3,0,0,2,0,0,0,1,0,0,0,0,
                          4,2,2,2,1,2,2,2,2,0,3,3,3,3,0,2,2,2,2,1,2,2,2,4,
                          0,0,0,0,1,0,0,0,2,0,3,3,3,3,0,2,0,0,0,1,0,0,0,0,
                          0,0,0,0,1,0,0,0,2,0,0,0,0,0,0,2,0,0,0,1,0,0,0,0,
                          0,0,0,0,1,0,0,0,2,2,2,2,2,2,2,2,0,0,0,1,0,0,0,0,
                          0,0,0,0,1,0,0,0,0,0,2,0,0,2,0,0,0,0,0,1,0,0,0,0,
                          0,0,0,0,1,0,0,0,1,1,1,1,1,1,1,1,0,0,0,1,0,0,0,0,
                          0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,
                          0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,0,
                          0,5,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,5,0,
                          0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,0,
                          0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    vector<RectangleShape> blockZero; //background tile (no allowed to move on)
    vector<RectangleShape> blockOne; //tile with food spawning on them (allowed to move on)
    vector<RectangleShape> blockTwo; //tile with no food (allowed to move on)
    vector<RectangleShape> blockThree; //tile for ghost house (no allowed to move on)
    vector<RectangleShape> blockFour; //tile for teleportation
    vector<RectangleShape> blockFive; //tile to spawn big food
    for(int i=0;i<matrix.size();i++){ //Create the tiles according to positioning on tile map above
        RectangleShape temp; //temporary rectangle to push to a vector
        temp.setSize(Vector2f(sizeOfBlocks,sizeOfBlocks));
        double tempX=0;
        double tempY=0;

        for(int j=0; j<=i; j++){
            if(j%blocksPerX==0&&j>0){ //check for row change
                tempX=0;
                tempY+=sizeOfBlocks;
            }else if(j!=0){ //add to x
                tempX+=sizeOfBlocks;
            }
        }
        temp.setPosition(tempX,tempY); //set position to appropriate position on map
        if(matrix[i]==0){ //if value in map is 0, add to first tiles
            temp.setFillColor(Color::Blue);
            blockZero.push_back(temp);
        }
        if(matrix[i]==1){ //if value in map is 1, add to second tiles
            temp.setFillColor(Color::Black);
            blockOne.push_back(temp);
        }
        if(matrix[i]==2){ //if value in map is 2, add to third tiles
            temp.setFillColor(Color::Black);
            blockTwo.push_back(temp);
        }
        if(matrix[i]==3){ //if value in map is 3, add to fourth tiles
            temp.setFillColor(Color(56,56,56));
            blockThree.push_back(temp);
        }
        if(matrix[i]==4){ //if value in map is 4, add to fourth tiles
            temp.setFillColor(Color::White);
            blockFour.push_back(temp);
        }
        if(matrix[i]==5){ //if value in map is 5, add to fifth tiles, and first for detection
            temp.setFillColor(Color::Black);
            blockFive.push_back(temp);
            blockOne.push_back(temp);
        }
    }

    int lives = 0;

    Texture tyler;
    tyler.loadFromFile("tyler.png");

    restart: //if you lose, reload game
    vector<enemy> enemies; //vector for 4 enemies, and push back with certain colors and positions
    enemies.push_back(enemy(blockTwo[6].getPosition(), Color::Red, RIGHT, DOWN, sizeOfBlocks, tyler));
    enemies.push_back(enemy(blockThree[4].getPosition(), Color::Cyan, NULLL, NULLL, sizeOfBlocks, tyler));
    enemies.push_back(enemy(blockThree[3].getPosition(), Color::Magenta, NULLL, NULLL, sizeOfBlocks, tyler));
    enemies.push_back(enemy(blockThree[7].getPosition(), Color::Green, NULLL, NULLL, sizeOfBlocks, tyler));


    enemyMode curMode = SCATTER; //initially on SCATTER mode
    int activeEnemies = 1; //start with one enemy
    int level = 0; //start on level 0
    int scatterLength = 7; //how long to scatter for initially
    int chaseLength = 20; //how long to chase for initially
    Clock c1; //clock to time scatter and chase lengths
    Clock c2; //clock for frightened

    Texture ram;
    ram.loadFromFile("ram.png");

    RectangleShape spawnBlock = blockOne[0]; //player's spawn
    RectangleShape player; //player rectangle
    player.setSize(Vector2f(sizeOfBlocks,sizeOfBlocks));
    //player.setFillColor(Color::Yellow);
    player.setPosition(spawnBlock.getPosition()); //start in top left
    player.setTexture(&ram);
    player.setTextureRect(IntRect(0,0,32,32));

    direction curPlayerDir = RIGHT; //begin going right
    direction nextPlayerDir = NULLL; //no button has been pressed yet

    int playerSpeed = 2; //speed of player, and enemies


    int score = 0; //score

    bool levelUp=false; //if in level up mode, which will be used to pause game

    vector<CircleShape> foodsLocations; //locations of small foods to store in memory
    vector<CircleShape> foods; //locations of small foods to use in game

    vector<CircleShape> bigFoodsLocations; //locations of big foods to store in memory
    vector<CircleShape> bigFoods; //locations of big foods to use in game

    for(int i=0;i<blockFive.size();i++){ //put a big food one block fives
        CircleShape temp(sizeOfBlocks/3);
        temp.setOrigin(temp.getRadius(),temp.getRadius());
        temp.setPosition(blockFive[i].getPosition().x+sizeOfBlocks/2, blockFive[i].getPosition().y+sizeOfBlocks/2);
        temp.setFillColor(Color::White);
        bigFoodsLocations.push_back(temp);
    }

    for(int i=0;i<blockOne.size();i++){ //put a small food on block ones
        CircleShape temp(sizeOfBlocks/8);
        temp.setOrigin(temp.getRadius(),temp.getRadius());
        temp.setPosition(blockOne[i].getPosition().x+sizeOfBlocks/2, blockOne[i].getPosition().y+sizeOfBlocks/2);
        temp.setFillColor(Color::White);
        foodsLocations.push_back(temp);
    }

    foods=foodsLocations;
    bigFoods=bigFoodsLocations;

    //font
    Font font;
    font.loadFromFile("font.ttf");

    //lives font
    Text livesT;
    livesT.setFont(font);
    livesT.setCharacterSize(32);
    livesT.setFillColor(Color::Red);
    livesT.setPosition(6,0);
    livesT.setString(to_string(lives));

    //score text
    Text scoreT;
    scoreT.setFont(font);
    scoreT.setCharacterSize(32);
    scoreT.setFillColor(Color::Yellow);

    //level up text
    Text levelUpT;
    levelUpT.setFont(font);
    levelUpT.setCharacterSize(48);
    levelUpT.setString("Hit Enter To Continue");
    levelUpT.setOrigin(levelUpT.getGlobalBounds().width/2,levelUpT.getGlobalBounds().height/2);
    levelUpT.setPosition(window.getSize().x/2,window.getSize().y/2);
    levelUpT.setFillColor(Color::Yellow);

    //game over and start text
    Text gameOver;
    gameOver.setFont(font);
    gameOver.setCharacterSize(48);
    gameOver.setString("Hit Enter To Start");
    gameOver.setOrigin(gameOver.getGlobalBounds().width/2,gameOver.getGlobalBounds().height/2);
    gameOver.setPosition(window.getSize().x/2,window.getSize().y/2);
    gameOver.setFillColor(Color::Yellow);

    if(window.isOpen()) { //if on game over, don't open new window, and reset lives
        goto enterWindow;
    }

    while (window.isOpen())
    {
        enterWindow:
        Event event;
        while (window.pollEvent(event)){
            if (event.type == Event::Closed)
                window.close();
        }
        if(lives>0){
            if(!levelUp){ //if not on level up
                //update score text and location
                scoreT.setString(to_string(score));
                scoreT.setOrigin(scoreT.getGlobalBounds().width/2,0);
                scoreT.setPosition(window.getSize().x/2,0);

                if(activeEnemies>=2&&enemies[1].grey){
                        enemies[1].curDir=UP;
                    }
                    if(activeEnemies>=3&&enemies[2].grey){
                        enemies[2].curDir=UP;
                    }
                    if(activeEnemies>=4&&enemies[3].grey){
                        enemies[3].curDir=UP;
                    }

                if(curMode!=FRIGHTENED){

                    if(c1.getElapsedTime().asSeconds()<scatterLength){ //if less than scatter time, put in scatter mode
                        curMode = SCATTER;
                    }
                    if(c1.getElapsedTime().asSeconds()>=scatterLength){ //if greater, put in chase
                        curMode = CHASE;
                    }
                    if(c1.getElapsedTime().asSeconds()>=chaseLength+scatterLength){ //if done, restart clock, add an enemy in
                        c1.restart();
                        if(activeEnemies<4) activeEnemies++;

                    }
                }else{
                    if(c2.getElapsedTime().asSeconds()>=5){
                        curMode=SCATTER;
                    }
                }
                enemies[0].movement(player, curMode, blockOne[10], blockOne[19], blockOne[45], blockOne[36], playerSpeed, blockZero, blockOne, blockTwo, blockThree, blockFour); //move enemy1
                enemies[1].movement(player, curMode, blockOne[96], blockOne[105], blockOne[131], blockOne[122], playerSpeed, blockZero, blockOne, blockTwo, blockThree, blockFour); //move enemy2
                enemies[2].movement(player, curMode, blockOne[106], blockOne[115], blockOne[141], blockOne[132], playerSpeed, blockZero, blockOne, blockTwo, blockThree, blockFour); //move enemy3
                enemies[3].movement(player, curMode, blockOne[0], blockOne[9], blockOne[26], blockOne[35], playerSpeed, blockZero, blockOne, blockTwo, blockThree, blockFour); //move enemy4

                for(int i=0;i<enemies.size();i++){ //check collisions with each enemy
                    if(enemies[i].colWithPlayer(player, curMode, score, activeEnemies)){ //if it collides, and is not in frightened mode
                        lives--; //lose a life
                        livesT.setString(to_string(lives));
                        player.setPosition(spawnBlock.getPosition()); //reset location
                        curPlayerDir = RIGHT; //reset direction
                        activeEnemies=1; //reset enemies
                        c1.restart(); //reset clock
                        for(int j=0;j<enemies.size();j++) enemies[j].restart(); //reset clock
                    }
                }

                //move player according to current direction
                if(curPlayerDir==UP){
                    player.move(0,-playerSpeed);
                    player.setTextureRect(IntRect(32,32,32,32));
                }else if(curPlayerDir==DOWN){
                    player.move(0,playerSpeed);
                    player.setTextureRect(IntRect(0,32,32,32));
                }else if(curPlayerDir==LEFT){
                    player.move(-playerSpeed,0);
                    player.setTextureRect(IntRect(32,0,32,32));
                }else if(curPlayerDir==RIGHT){
                    player.move(playerSpeed,0);
                    player.setTextureRect(IntRect(0,0,32,32));
                }

                //if a button is pressed, set the next direction to appropriate key
                if(Keyboard::isKeyPressed(Keyboard::W)){
                    nextPlayerDir = UP;
                }else if(Keyboard::isKeyPressed(Keyboard::S)){
                    nextPlayerDir = DOWN;
                }else if(Keyboard::isKeyPressed(Keyboard::A)){
                    nextPlayerDir = LEFT;
                }else if(Keyboard::isKeyPressed(Keyboard::D)){
                    nextPlayerDir = RIGHT;
                }

                //if player eats food, delete food, increase score
                for(int i=0;i<foods.size();i++){
                    if(player.getGlobalBounds().intersects(foods[i].getGlobalBounds())){
                        foods.erase(foods.begin()+i);
                        score+=10;
                    }
                }
                //if player eats big food, delete big food, increase score
                for(int i=0;i<bigFoods.size();i++){
                    if(player.getGlobalBounds().intersects(bigFoods[i].getGlobalBounds())){
                        bigFoods.erase(bigFoods.begin()+i);
                        score+=990;
                        c2.restart();
                        curMode = FRIGHTENED;
                    }
                }

                //once there is no more food, go to next level
                if(foods.size()==0&&bigFoods.size()==0){
                    level++;
                    player.setPosition(spawnBlock.getPosition());
                    curPlayerDir = RIGHT;
                    activeEnemies=1;
                    c1.restart();
                    foods=foodsLocations;
                    bigFoods=bigFoodsLocations;
                    for(int j=0;j<enemies.size();j++) enemies[j].restart();
                    if(level%2==0){
                        if(scatterLength>1){
                            scatterLength-=2;
                            chaseLength+=2;
                        }else{
                            scatterLength=0;
                            chaseLength+=1;
                        }
                    }
                    if(level==3){
                        playerSpeed*=2;
                    }
                    levelUp=true; //pause the game
                }

                //check if it's possible to turn to the next direction
                if(nextPlayerDir==DOWN){
                    for(int i = 0; i<blockOne.size(); i++){
                        if(player.getPosition().x==blockOne[i].getPosition().x&&player.getPosition().y+sizeOfBlocks==blockOne[i].getPosition().y){
                            curPlayerDir=DOWN;
                            nextPlayerDir=NULLL;
                        }
                    }
                    for(int i = 0; i<blockTwo.size(); i++){
                        if(player.getPosition().x==blockTwo[i].getPosition().x&&player.getPosition().y+sizeOfBlocks==blockTwo[i].getPosition().y){
                            curPlayerDir=DOWN;
                            nextPlayerDir=NULLL;
                        }
                    }
                }else if(nextPlayerDir==LEFT){
                    for(int i = 0; i<blockOne.size(); i++){
                        if(player.getPosition().y==blockOne[i].getPosition().y&&player.getPosition().x-sizeOfBlocks==blockOne[i].getPosition().x){
                            curPlayerDir=LEFT;
                            nextPlayerDir=NULLL;
                        }
                    }
                    for(int i = 0; i<blockTwo.size(); i++){
                        if(player.getPosition().y==blockTwo[i].getPosition().y&&player.getPosition().x-sizeOfBlocks==blockTwo[i].getPosition().x){
                            curPlayerDir=LEFT;
                            nextPlayerDir=NULLL;
                        }
                    }
                }else if(nextPlayerDir==UP){
                    for(int i = 0; i<blockOne.size(); i++){
                        if(player.getPosition().x==blockOne[i].getPosition().x&&player.getPosition().y-sizeOfBlocks==blockOne[i].getPosition().y){
                            curPlayerDir=UP;
                            nextPlayerDir=NULLL;
                        }
                    }
                    for(int i = 0; i<blockTwo.size(); i++){
                        if(player.getPosition().x==blockTwo[i].getPosition().x&&player.getPosition().y-sizeOfBlocks==blockTwo[i].getPosition().y){
                            curPlayerDir=UP;
                            nextPlayerDir=NULLL;
                        }
                    }
                }else if(nextPlayerDir==RIGHT){
                    for(int i = 0; i<blockOne.size(); i++){
                        if(player.getPosition().y==blockOne[i].getPosition().y&&player.getPosition().x+sizeOfBlocks==blockOne[i].getPosition().x){
                            curPlayerDir=RIGHT;
                            nextPlayerDir=NULLL;
                        }
                    }
                    for(int i = 0; i<blockTwo.size(); i++){
                        if(player.getPosition().y==blockTwo[i].getPosition().y&&player.getPosition().x+sizeOfBlocks==blockTwo[i].getPosition().x){
                            curPlayerDir=RIGHT;
                            nextPlayerDir=NULLL;
                        }
                    }
                }

                //if there is a wall, turn around
                for(int i = 0; i<blockZero.size(); i++){
                        if(curPlayerDir==UP){
                            if(player.getPosition().y-sizeOfBlocks==blockZero[i].getPosition().y&&player.getPosition().x==blockZero[i].getPosition().x) curPlayerDir=DOWN;
                        }else if(curPlayerDir==DOWN){
                            if(player.getPosition().y+sizeOfBlocks==blockZero[i].getPosition().y&&player.getPosition().x==blockZero[i].getPosition().x) curPlayerDir=UP;
                        }else if(curPlayerDir==LEFT){
                            if(player.getPosition().x-sizeOfBlocks==blockZero[i].getPosition().x&&player.getPosition().y==blockZero[i].getPosition().y) curPlayerDir=RIGHT;
                        }else if(curPlayerDir==RIGHT){
                            if(player.getPosition().x+sizeOfBlocks==blockZero[i].getPosition().x&&player.getPosition().y==blockZero[i].getPosition().y) curPlayerDir=LEFT;
                        }
                }

                //if it hits teleportation block, teleport
                if(curPlayerDir==RIGHT){
                    if(player.getPosition().x+sizeOfBlocks==blockFour[1].getPosition().x+sizeOfBlocks&&player.getPosition().y==blockFour[1].getPosition().y){
                            player.setPosition(blockFour[0].getPosition().x-sizeOfBlocks,blockFour[0].getPosition().y);
                    }
                }
                if(curPlayerDir==LEFT){
                    if(player.getPosition().x-sizeOfBlocks==blockFour[0].getPosition().x-sizeOfBlocks&&player.getPosition().y==blockFour[0].getPosition().y){
                        player.setPosition(blockFour[1].getPosition().x+sizeOfBlocks, blockFour[1].getPosition().y);
                    }
                }

            }else if(levelUp){ //if on level screen, wait for enter key
                if(Keyboard::isKeyPressed(Keyboard::Enter)){
                    levelUp=false;
                }
            }
        }else{
            if(Keyboard::isKeyPressed(Keyboard::Enter)){
                lives=3;
                livesT.setString(to_string(lives));
                goto restart; //if no lives, and you hit enter, go to restart
            }
        }

        window.clear();
        for(int i=0; i<blockZero.size(); i++)window.draw(blockZero[i]);
        for(int i=0; i<blockOne.size(); i++)window.draw(blockOne[i]);
        for(int i=0; i<blockTwo.size(); i++)window.draw(blockTwo[i]);
        for(int i=0; i<blockThree.size(); i++)window.draw(blockThree[i]);
        for(int i=0; i<blockFour.size(); i++)window.draw(blockFour[i]);
        if(lives>0){
            for(int i=0; i<foods.size(); i++)window.draw(foods[i]);
            for(int i=0; i<bigFoods.size(); i++)window.draw(bigFoods[i]);
            for(int i=0; i<enemies.size(); i++)window.draw(enemies[i].spr);
        }else{
            window.draw(gameOver);
        }
        window.draw(scoreT);
        window.draw(player);
        window.draw(livesT);
        if(levelUp) window.draw(levelUpT); //display level up text if on level up screen
        window.display();
    }
}

