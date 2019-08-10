#include <iostream>
#include<bits/stdc++.h>
#include<conio.h>
#include<time.h>
#include<windows.h>
using namespace std;

enum edirection{
    stop=0,
    leftt=1,
    upleft=2,downleft=3,
    rightt=4,
    upright=5,downright=6

};
class cball{
private:
    int x,y; //pos of ball
    int origx,origy;
    edirection dir;

public:
    cball(int posx,int posy){
        origx=posx;
        origy=posy;
        x=posx;
        y=posy;
        dir=stop;
    }

    void reset(){
        x=origx;
        y=origy;
        dir=stop;
    }

    void changedir(edirection d){
        dir=d;
    }
    void randomdir(){
        dir=(edirection)((rand()%6)+1);
    }
    inline int getx(){
        return x;
    }
    inline int gety(){
        return y;
    }
    inline edirection getdir(){
        return dir;
    }

    void move(){
        switch(dir){
            case stop:
                break;
            case leftt:
                x--;
                break;
            case rightt:
                x++;
                break;
            case upleft:
                x--;y--;
                break;
            case downleft:
                x--;y++;
                break;
            case upright:
                x++;y--;
                break;
            case downright:
                x++;y++;
                break;
            default:
                break;
        }
    }

    friend ostream & operator<<(ostream & o,cball c){
        o << "Ball [" << c.x << "," << c.y << "][" << c.dir<< "]";
        return o;
    }
};

class cpaddle{

private:
    int x,y;
    int origx,origy;
public:
    cpaddle(){
        x=y=0;

    }
    cpaddle(int posx,int posy) : cpaddle(){
        origx=posx;
        origy=posy;
        x=posx;
        y=posy;


    }

    inline void resett(){
        x=origx;
        y=origy;

    }

    inline int getx(){return x;}
    inline int gety(){return y;}
    inline void moveup(){y--;}
    inline void movedown(){y++;}
    friend ostream & operator<<(ostream & o,cpaddle c){
        o << "Paddle [" << c.x << "," << c.y << "]";
        return o;
    }


};

class cgameManager{
private:
    int width,height;
    int score1,score2;
    char up1,up2,down1,down2;
    bool quit;
    cball *ball;
    cpaddle *player1,*player2;

public:
    cgameManager(int w,int hgt){
        srand(time(NULL));
        quit=false;
        up1='w';up2='i';
        down1='s';down2='k';
        score1=score2=0;
        width=w;
        height=hgt;
        ball = new cball(w/2,hgt/2);
        player1=new cpaddle(1,hgt/2 -3);//paddle 4 ka h
        player2=new cpaddle(w-2,hgt/2 -3);//paddle 4 ka h
    }

    ~cgameManager(){
        delete ball,player1,player2;

    }


    void scoreup(cpaddle *player){
        if (player == player1)
            score1++;
        else if (player == player2)
            score2++;

        ball->reset();
        player1->resett();
        player2->resett();
    }

    void draw(){
        system("cls");
        for(int i=0;i<width+1;i++){
            cout<<"\xB2";
        }

        for(int i=0;i<height;i++){
            for(int j=0;j<width;j++){
                int ballx=ball->getx();
                int bally=ball->gety();
                int player1x=player1->getx();
                int player2x=player2->getx();
                int player2y=player2->gety();
                int player1y=player1->gety();
                if(j==0){
                    cout<<"\xB2";

                }

                if(ballx==j && bally==i){
                    cout<<"0";
                }
                else if(player1x==j && player1y==i){
                    cout<<"\xBA";
                }
                else if(player1x==j && player1y==i+1){
                    cout<<"\xBA";
                }else if(player1x==j && player1y==i+2){
                    cout<<"\xBA";
                }else if(player1x==j && player1y==i+3){
                    cout<<"\xBA";
                }
                else if(player2x==j && player2y==i){
                    cout<<"\xBA";
                }

                else if(player2x==j && player2y==i+1){
                    cout<<"\xBA";
                }
                else if(player2x==j && player2y==i+2){
                    cout<<"\xBA";
                }
                else if(player2x==j && player2y==i+3){
                    cout<<"\xBA";
                }
                else{
                    cout<<" ";

                }


                if(j==width-1){
                    cout<<"\xB2";
                }
            }
            cout<<endl;
        }

        for(int i=0;i<width+2;i++){
            cout<<"\xB2";
        }


        cout<<endl<<"Score 1 is"<<score1<<"Score 2 is"<<score2<<endl;
    }

    void input(){
        ball->move();
        int ballx=ball->getx();
        int bally=ball->gety();
        int player1x=player1->getx();
        int player2x=player2->getx();
        int player2y=player2->gety();
        int player1y=player1->gety();

        if(_kbhit()){

            char current=_getch();
            if(current==up1){
                if(player1y>0){
                    player1->moveup();
                }
            }
            if(current==up2){
                if(player2y>0){
                    player2->moveup();
                }
            }
            if(current==down1){
                if(player1y+4<height){
                    player1->movedown();
                }
            }

            if(current==down2){
                if(player2y+4<height){
                    player2->movedown();
                }
            }
            if(ball->getdir()==stop){
                ball->randomdir();
            }
            if(current='q'){
                quit=true;
            }

        }

    }

    void logic(){
        int ballx=ball->getx();
        int bally=ball->gety();
        int player1x=player1->getx();
        int player2x=player2->getx();
        int player2y=player2->gety();
        int player1y=player1->gety();
        //left waala paddle ju hai
        for(int i=0;i<4;i++){
            if(ballx==player1x+1){
                if(bally==player1y+i){
                    //ball->changedir((edirection)(rand()%3 +4));
                    ball->changedir((edirection)((rand() % 3) + 4));
                }
            }
        }

        //right
        for(int i=0;i<4;i++){
            if(ballx==player2x-1){
                if(bally==player2y+i){
                   // ball->changedir((edirection)(rand%3 +1));
                    ball->changedir((edirection)((rand() % 3) + 1));
                }
            }
        }


        if(bally==height-1){ //bottom wall
            ball->changedir(ball->getdir()==downright? upright : upleft);
        }

        if(bally==0){ //top wall
            ball->changedir(ball->getdir()==upright? downright : downleft);
        }

        if(ballx==width-1){
            scoreup(player1);
        }

        if(ballx==0){
            scoreup(player2);
        }



    }

    void run(){
        while(!quit){
            draw();
            input();
            logic();
        }
    }
};
int main()
{
   /* cpaddle c(0,0);
    cout<<c<<endl;
    c.movedown();

    c.movedown();
    cout<<c<<endl;
    c.moveup();
    cout<<c<<endl;
*/
    cgameManager c(40,20);
    c.run();

    return 0;
}
