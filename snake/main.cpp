#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h> //for Input
using namespace std;

//globla variable
bool gameOver;
int score;
//map variable
const int width = 20;
const int height = 20;
//object position
int headX,headY,fruitX,fruitY;
//snake direction
enum eDirection {STOP=0,LEFT,RIGHT,UP,DOWN};
eDirection dir;
//snake tail
int tailX[100], tailY[100];
int nTail;
//snake speed
int speed = 100;

void Setup(){
    gameOver = false;
    dir = STOP; //snake doesnt move
    //position of the snake
    headX = width/2; //middle of map
    headY = height/2;
    //position of the fruit 
    srand(time(0));
    fruitX = rand() % (width-2)+1; //from 1 to 18
    fruitY = rand() % (height-2)+1; //from 1 to 8
    score = 0;
}
void Draw(){
    system("cls"); //clear terminal
    //draw map/object
    for (int i=0;i<height;i++){
        for (int j=0;j<width;j++){
            //top and bottom border
            if (i==0 || i==height-1){
                cout << "-";
                if (j==width-1){
                    cout << endl;
                }
            }
            //side border
            else if (j==0 || j==width-1){
                cout << "|";
                if (j==width-1){
                    cout << endl;
                }
            }
            //fruit
            else if (j==fruitX && i==fruitY){
                cout << "$";
            }
            //snake head
            else if (j==headX && i==headY){
                cout << "0";
            }
            //empty space
            else{
                //draw tail
                bool pri = false;
                for (int k=0;k<nTail;k++){
                    if (tailX[k] == j && tailY[k] == i){
                        cout << "o";
                        pri = true;
                    }
                }
                if (!pri){
                    cout << " ";
                }
                
            }
        }
    }
    cout << "score: " << score << endl;   
}
void Input(){
    //check keyboard key
    if (_kbhit()){
        //switch snake position
        switch(_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;   
        }
    }
}
void Logic(){
    //tail location
    int prevTailX = tailX[0];
    int prevTailY = tailY[0];
    int prevTailX2, prevTailY2;
    tailX[0] = headX;
    tailY[0] = headY;
    //tail logic 
    for (int i=1;i<nTail;i++){
        prevTailX2 = tailX[i];
        prevTailY2 = tailY[i];
        tailX[i] = prevTailX;
        tailY[i] = prevTailY;
        prevTailX = prevTailX2;
        prevTailY = prevTailY2;
    }
    //snake dir logic
    switch (dir)
    {
    case LEFT:
        headX--;
        break;
    case RIGHT:
        headX++;
        break;
    case UP:
        headY--;
        break;
    case DOWN:
        headY++;
        break;
    default:
        break;
    }
    //End game if head hit border
    if (headX == width-1 || headX == 0 || headY == height-1 || headY == 0){
        gameOver = true;
    }
    //end game if head hit tail
    for (int i=0;i<nTail;i++){
        if (tailX[i] == headX && tailY[i] == headY){
            gameOver = true;
        }
    }
    //increase score if eat fruit
    if (headX == fruitX && headY == fruitY){
        score++;
        //re-rocate the fruit
        srand(time(0));
        fruitX = rand() % (width-2)+1;
        fruitY = rand() % (height-2)+1;
        //increase tail size
        nTail++;
        //increase game speed
        if (speed!=0){
            speed-=5;
        }
    }
}
int main(){
    Setup();

    while(!gameOver){
        Draw();
        Input();
        Logic();
        Sleep(speed);
    }
    return 0;

}