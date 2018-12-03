#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<iostream>
#include<stdlib.h>
#include<string>
#include <sstream>

class Piece{
protected:
    int xcor;
    int ycor;
    int value;
    sf::Texture t;
    friend void setposition(int[8][8]);
    friend void draw(sf::RenderWindow &);  //function to draw pieces4

public:
    sf::Sprite s;
    void change_coordinate(int x, int y)
    {
        xcor=x;
        ycor=y;
    }
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
        t.loadFromFile("images/wknight.PNG");
        value = 4;
        setSprite();
        }
        if(color == 0){
        t.loadFromFile("images/bknight.PNG");
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
        t.loadFromFile("images/wking.PNG");
        value = 10;
        setSprite();
        }
        if(color == 0){
        t.loadFromFile("images/bking.PNG");
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
        t.loadFromFile("images/wqueen.PNG");
        value = 9;
        setSprite();
        }
        if(color == 0){
        t.loadFromFile("images/bqueen.PNG");
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
        t.loadFromFile("images/wrook.PNG");
        value = 5;
        setSprite();
        }
        if(color == 0){
        t.loadFromFile("images/brook.PNG");
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
        t.loadFromFile("images/wbishop.PNG");
        value = 3;
        setSprite();
        }
        if(color == 0){
        t.loadFromFile("images/bbishop.PNG");
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
        t.loadFromFile("images/wpawn.PNG");
        value = 1;
        setSprite();
        }
        if(color==0){
        t.loadFromFile("images/bpawn.PNG");
        value = -1;
        setSprite();
        }
    }
    void place(){
    Piece::place();
}
};

int SCRWIDTH=700,SCRHEIGHT=700;

class setpos
{
public:

  void dis(int i,std::string c,int R,int G,int B,int A)
    {

        font1.loadFromFile("Best.TTF");

        temp[i].setString(c);
        temp[i].setFont(font1);
        temp[i].setCharacterSize(40);
        temp[i].setPosition(sf::Vector2f(SCRWIDTH/3.0f,(SCRHEIGHT/4.0f)+i*60));
        temp[i].setStyle(sf::Text::Italic);
        temp[i].setOutlineThickness(2);
        temp[i].setOutlineColor(sf::Color::Blue);
        temp[i].setFillColor(sf::Color(R,G,B,A));
    }

    private:
    sf::Font font1;

    public:
    sf::Text temp[10];
}pos11,loading1;





//Global declaration of objects two letters color and type of piece being indicated
    Horse wh[2]{1,1}, bh[2]{0,0};
    King wk(1), bk(0);
    Queen wq(1), bq(0);
    Rook wr[2]{1,1}, br[2]{0,0};
    Bishop wb[2]{1,1}, bb[2]{0,0};
    Pawn wp[8]{1,1,1,1,1,1,1,1}, bp[8]{0,0,0,0,0,0,0,0};
    int rwi, rbi, pwi, pbi, hwi, hbi, bbi, bwi, qbi, qwi, kbi, kwi ;  //index for no of count of diff pieces

void setposition(int board[8][8])           // sets value of coordinates of pieces according to board matrix
{
    rwi=0; rbi=0; pwi=0; pbi=0; hwi=0; hbi=0; bbi=0; bwi=0; qbi=0; qwi=0; kbi=0; kwi=0 ;
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

void place()
{
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


}

















