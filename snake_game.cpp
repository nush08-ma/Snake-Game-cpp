#include<windows.h>
#include<bits/stdc++.h>
#include<conio.h>              //key press
#include<iostream>

using namespace std;
#define MAX_LENGTH 1000

const char DIR_UP='U';
const char DIR_DOWN='D';
const char DIR_RIG='R';
const char DIR_LEFT='L';

int consoleHeight , consoleWidth ;


void InitScreen(){
    HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole,&csbi);
    consoleHeight=csbi.srWindow.Bottom-csbi.srWindow.Top+1;
    consoleWidth=csbi.srWindow.Right-csbi.srWindow.Left+1;

}

struct Point{
    int xCord;
    int yCord;
    Point(){};
    Point(int x,int y){
        xCord=x;
        yCord=y;
    }
};

class Snake{
    int length;
    char direction;
public:
    Point body[MAX_LENGTH];
    Snake(int x,int y){
        length=1;
        direction=DIR_RIG;
        body[0]=Point(x,y);
    }
    

    int getLength(){
        return length;
    }

    void ChangeDirection(char newdirection){
        if(newdirection==DIR_LEFT && direction!=DIR_RIG){
            direction=newdirection;
        }
        else if(newdirection==DIR_RIG && direction!=DIR_LEFT){
            direction=newdirection;
        }
        else if(newdirection==DIR_UP && direction!=DIR_DOWN){
            direction=newdirection;
        }
        else if(newdirection==DIR_DOWN && direction!=DIR_UP){
            direction=newdirection;
        }
    }

    bool move(Point food){
        for(int i=length-1;i>0;i--){
            body[i]=body[i-1];
        }

        // top most corner of screen is (0,0) relative to which up direction is y-1.
        switch (direction){
            int val;
            case DIR_UP:
                val=body[0].yCord;
                body[0].yCord=val-1;
                break;
            case DIR_DOWN:
                val=body[0].yCord;
                body[0].yCord=val+1;
                break;
            case DIR_RIG:
                val=body[0].xCord;
                body[0].xCord=val+1;
                break;
            case DIR_LEFT:
                val=body[0].xCord;
                body[0].xCord=val-1;
                break;
        }

        // snake bites itself- game over
        for(int i=i;i<length;i++){
            if(body[0].xCord==body[i].xCord && body[0].yCord==body[i].yCord){
                return false;
            }
        }

        // snake eats food 
        if(food.xCord==body[0].xCord && food.yCord==body[0].yCord){
            body[length]= Point(body[length-1].xCord,body[length-1].yCord);
            length++;
        }

        return true;
    }
};

class Board{
    Snake *snake;
    const char SNAKE_BODY='O';
    Point food;
    const char FOOD='#';
    int score;
public :
    Board(){
        spawnfood();
        snake=new Snake(10,10);
        score=0;
    }

    ~Board(){
        delete snake;
    }
    
    int getScore(){
    	return score;
	}

    void spawnfood(){
        int x= rand() % consoleWidth ;                //random number between 0 to 99
        int y= rand() % consoleHeight;
        food=Point(x,y);
    }
    
    void displayscore(){
    	gotoxy(consoleWidth/2 ,0);
    	cout<<"Current Score : "<<score;
	}

    void gotoxy(int x,int y){
        COORD coord;
        coord.X=x;
        coord.Y=y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
    }

    void draw(){
        system("cls");
        for(int i=0;i<snake->getLength();i++){
            gotoxy(snake->body[i].xCord,snake->body[i].yCord);
            cout<<SNAKE_BODY;
        }
        gotoxy(food.xCord,food.yCord);
            cout<<FOOD;
        
        displayscore();
    }

    bool update(){
        bool IsAlive = snake->move(food);
        if (IsAlive==false){
            return false;
        }
        if(food.xCord==snake->body[0].xCord && food.yCord==snake->body[0].yCord){
            score++;
            spawnfood();
        }

        return true;
    }

    void GetInput(){
        if(kbhit){
            int key = getch();
            if(key=='w' || key=='W'){
                snake->ChangeDirection(DIR_UP);
            }
            else if(key=='s' || key=='S'){
                snake->ChangeDirection(DIR_DOWN);
            }
            else if(key=='a' || key=='A'){
                snake->ChangeDirection(DIR_LEFT);
            }
            else if(key=='d' || key=='D'){
                snake->ChangeDirection(DIR_RIG);
            }
        }

    }
};
int main(){
    srand(time(0));
    InitScreen();
    Board *board=new Board();
    while(board->update()){
        board->GetInput();
        board->draw();
        Sleep(1);
    }
    cout<<"\nGAME OVER !!"<<endl;
    cout<<"\nFinal Score is :"<<board->getScore();
    return 0;
}


