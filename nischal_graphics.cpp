#include <SFML/Graphics.hpp>
#include<iostream>
#include <time.h>

class Piece{
protected:
    int xcor;
    int ycor;
    int value;
    sf::Texture t;
    friend void setposition(int[8][8]);
    friend void draw(sf::RenderWindow &);  //function to draw pieces

public:
    sf::Sprite s;
    void setSprite()
    {
        s = sf::Sprite(t);
    }
    void place()
    {
        s.setPosition(55+xcor*73.625,55+ycor*73.625);   //sets position according to the value of its coordinates
    }

    };


class Horse:public Piece
{
public:
    Horse(int color)
    {
        if(color == 1){
        t.loadFromFile("images/wknight.png");
        value = 4;
        setSprite();
        }
        if(color == 0){
        t.loadFromFile("images/bknight.png");
        value = -4;
        setSprite();
        }
    }
    void place(){
    Piece::place();
}
};

class King:public Piece
{
public:
    King(int color)
    {
        if(color == 1){
        t.loadFromFile("images/wking.png");
        value = 10;
        setSprite();
        }
        if(color == 0){
        t.loadFromFile("images/bking.png");
        value = -10;
        setSprite();
        }
    }
    void place(){
    Piece::place();
}
};

class Queen:public Piece
{
public:
    Queen(int color)
    {
        if(color == 1){
        t.loadFromFile("images/wqueen.png");
        value = 9;
        setSprite();
        }
        if(color == 0){
        t.loadFromFile("images/bqueen.png");
        value = -9;
        setSprite();
        }
    }
    void place(){
    Piece::place();
}
};

class Rook:public Piece
{
public:
    Rook(int color)
    {
        if(color == 1){
        t.loadFromFile("images/wrook.png");
        value = 5;
        setSprite();
        }
        if(color == 0){
        t.loadFromFile("images/brook.png");
        value = -5;
        setSprite();
        }
    }
    void place(){
    Piece::place();
}
};

class Bishop:public Piece
{
public:
    Bishop(int color)
    {
        if(color == 1){
        t.loadFromFile("images/wbishop.png");
        value = 3;
        setSprite();
        }
        if(color == 0){
        t.loadFromFile("images/bbishop1.png");
        value = -3;
        setSprite();
        }
    }
    void place(){
    Piece::place();
}
};

class Pawn:public Piece
{
public:
    Pawn(int color)
    {
        if(color==1){
        t.loadFromFile("images/wpawn.png");
        value = 1;
        setSprite();
        }
        if(color==0){
        t.loadFromFile("images/bpawn.png");
        value = -1;
        setSprite();
        }
    }
    void place(){
    Piece::place();
}
};





//Global declaration of objects two letters color and type of piece being indicated
    Horse wh[2]{1,1}, bh[2]{0,0};
    King wk(1), bk(0);
    Queen wq(1), bq(0);
    Rook wr[2]{1,1}, br[2]{0,0};
    Bishop wb[2]{1,1}, bb[2]{0,0};
    Pawn wp[8]{1,1,1,1,1,1,1,1}, bp[8]{0,0,0,0,0,0,0,0};
    int rwi=0, rbi=0, pwi=0, pbi=0, hwi=0, hbi=0, bbi=0, bwi=0, qbi=0, qwi=0, kbi=0, kwi=0 ;  //index for no of count of diff pieces

void setposition(int board[8][8])           // sets value of coordinates of pieces according to board matrix
{
   for(int i=0; i<8;i++)
    {
        for(int j=0; j<8;j++)
        {
            switch(board[i][j]){
            case 1:
                wp[pwi].xcor=j;
                wp[pwi].ycor=i;
                pwi++;
                break;
            case -1:
                bp[pbi].xcor=j;
                bp[pbi].ycor=i;
                pbi++;
                break;
            case 5:
                wr[rwi].xcor=j;
                wr[rwi].ycor=i;
                rwi++;
                break;
            case -5:
                br[rbi].xcor=j;
                br[rbi].ycor=i;
                rbi++;
                break;
             case 4:
                wh[hwi].xcor=j;
                wh[hwi].ycor=i;
                hwi++;
                break;
            case -4:
                bh[hbi].xcor=j;
                bh[hbi].ycor=i;
                hbi++;
                break;
            case 3:
                wb[bwi].xcor=j;
                wb[bwi].ycor=i;
                bwi++;
                break;
            case -3:
                bb[bbi].xcor=j;
                bb[bbi].ycor=i;
                bbi++;
                break;
            case 9:
                wq.xcor=j;
                wq.ycor=i;
                qwi++;
                break;
            case -9:
                bq.xcor=j;
                bq.ycor=i;
                qbi++;
                break;
            case 10:
                wk.xcor=j;
                wk.ycor=i;
                kwi++;
                break;
            case -10:
                bk.xcor=j;
                bk.ycor=i;
                kbi++;
                break;
            }
        }
    }
}

void draw(sf::RenderWindow &window)            // places required piece according to coordinates
{
    if(qbi==1) window.draw(bq.s);
    if(qwi==1) window.draw(wq.s);
    if(kbi==1) window.draw(bk.s);
    if(kwi==1) window.draw(wk.s);
    for(int i=0; i<pwi; i++) window.draw(wp[i].s);
    for(int i=0; i<pbi; i++) window.draw(bp[i].s);

    for(int i=0; i<rwi; i++) window.draw(wr[i].s);
    for(int i=0; i<rbi; i++) window.draw(br[i].s);
    for(int i=0; i<hwi; i++) window.draw(wh[i].s);
    for(int i=0; i<hbi; i++) window.draw(bh[i].s);
    for(int i=0; i<bwi; i++) window.draw(wb[i].s);
    for(int i=0; i<bbi; i++) window.draw(bb[i].s);
}

int main()
{
      int board [8][8]={
        -5,-4,-3,-9,-10,-3,0,-5,
        -1,-1,-1,-1,-1,-1,-1,-1,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, -4, 0, 0, 0,
        0, 0, 3, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 1, 1, 1,
        5, 4, 3, 9, 10, 0, 4, 5
    };
    setposition(board);


    sf::RenderWindow window(sf::VideoMode(700, 700), "SFML works!");
    sf::Texture t;

    t.loadFromFile("images/board.jpg");  // loads board
    sf::Sprite s(t);
    s.setPosition(0,0);

             bq.place();
             wq.place();
             wk.place();
             bk.place();
            for(int i=0; i<8; i++)
            {
               wp[i].place();
               bp[i].place();
            }
            for(int i=0; i<2; i++)
            {
               wr[i].place();
               br[i].place();
               wh[i].place();
               bh[i].place();
               wb[i].place();
               bb[i].place();
            }


    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {

            if( event.type == sf::Event::Closed )
                window.close();

                 }


        window.clear();
        window.draw(s);
        draw(window);
        window.display();
    }

    return 0;
}

