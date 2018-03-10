#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include "CBoard.h"
#include "ai.h"
#include "nischal_graphics.h"


using namespace std;
int newposx, newposy,prepsx,prepsy,k;
class board_converter
{
 public:
  void san_to_nischal(const CSquare From,const CSquare To);
  void position_check(int pie);
  void tukrauna(int );
  string nischal_to_san();
  string converter(int _row ,int _col);
   string int_to_str(int num)
  {
    stringstream ss;

    ss << num;

    return ss.str();
  }	
  int array_temp [8][8]={
        {-5,-4,-3,-9,-10,-3,-4,-5},
        {-1,-1,-1,-1,-1,-1,-1,-1},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {5, 4, 3, 9, 10, 3, 4, 5}
 };	
  int to_row,to_col,from_row,from_col,pos_i=0,pos_j=0,x_tukra=0,y_tukra=0;
   
 private:
   
   int from,to;
   string s1,s2;
   
};

template <class T>
void mouse(T &obj, sf::Event &event, sf::RenderWindow &window, sf::Sprite &blue,bool &player_turn, bool &blu, bool &fpress, int posx, int posy, board_converter &b_c,CBoard &board,sf::Sprite &red,bool &redb,sf::Sprite *green,bool &gree)
{
    
    string str,str1,str2,str3,_c,kk;
    int clicked=0;
   
         
    if(!fpress){

                if(event.type == sf::Event::MouseButtonPressed)
                {
                	      
                	      
                        if(obj.s.getGlobalBounds().contains(posx, posy))
                        {
                            fpress=true;
                            blu=true;
                            blue.setPosition(obj.s.getPosition().x, obj.s.getPosition().y);
                            prepsx=(posx-55)/73.625;
                        	prepsy=(posy-55)/73.625;
                        	cout<<prepsx<<" "<<prepsy<<endl;
                            
                        			clicked=b_c.array_temp[prepsy][prepsx];
                        			cout<<"clicked:"<<clicked<<endl;
                        			CMoveList moves;
            						board.find_legal_moves(moves);
            						k=0;
                                for(int i=0;i<moves.size();i++)
                                {
								    b_c.tukrauna(moves[i].m_from);
								   // cout<<b_c.x_tukra<<" "<<b_c.y_tukra<<endl;
								    if((b_c.x_tukra==prepsx)&&(b_c.y_tukra==prepsy))
								    {
								    //	cout<<b_c.x_tukra<<" "<<b_c.y_tukra<<endl;
								    	b_c.tukrauna(moves[i].m_to);
								    	
								    	green[k].setPosition(55+(b_c.x_tukra)*73.625,55+(b_c.y_tukra)*73.625);
								    	k++;
								    	gree=true;
									}
								    
            				    }
									                       	
                            
                        }
                       
                  }
                }
                
                else
                {
                    if(event.type == sf::Event::MouseButtonPressed)
                    {    	
                        str3=b_c.converter(8-prepsy,prepsx+1);
                        newposx=(posx-55)/73.625;
                        newposy=(posy-55)/73.625;
                        
                        cout<<newposx<<" "<<newposy<<endl;
                        
                        obj.Piece::change_coordinate(newposx, newposy);
                        fpress=false;
                        blu=false;
                        gree=false;
                            CMove move;    
							str2=b_c.converter(8-newposy,newposx+1);	    			 
				            str1="move ";
        				    str.append(str1);
							str.append(str3);
							str.append(str2);//b_c.converter(newposy+1,newposx+1);
						//	str="move a2a4";
        				    cout<<str<<endl;
				            if (move.FromString(str.c_str()+5) == NULL)
				            {
				                
				            }
				
				            if (board.IsMoveValid(move))  //From this line code must be changed with graphics
				            {
				                board.make_move(move);
				                bool check = board.isOtherKingInCheck();
				                bool check_other = board.isKingInCheck();
				                board.undo_move(move);
				                redb=false;
				               
				                if (check)
				                {
				                    cout << "White King in CHECK. Play another move." << endl;  
				                    b_c.position_check(10);
				                	red.setPosition(55+b_c.pos_i*73.625,55+b_c.pos_j*73.625 );
				                	redb=true;
				                   // b_c.position_check(10);
				                    cout<<b_c.pos_i<<" "<<b_c.pos_j<<endl;
				                }
				                else {
				                cout << "You move : " << move << std::endl;
				                board.make_move(move);
				                b_c.array_temp[newposy][newposx] = b_c.array_temp[prepsy][prepsx];
				                b_c.array_temp[prepsy][prepsx]=0;
				                setposition(b_c.array_temp);
				                place();
				                if(player_turn)
				                player_turn=false;
				                else
				                player_turn=true;
                                }
                                if(check_other)
				                {
				                	
				                	if(!player_turn)
				                	{
									
				                	cout << "Black kings is in CHECK" << endl;  
				                	b_c.position_check(-10);
				                	red.setPosition(55+b_c.pos_i*73.625,55+b_c.pos_j*73.625 );
				                	redb=true;
				                   }
				                   else 
				                   {
				                   	cout << "white kings is in CHECK" << endl;  
				                	b_c.position_check(10);
				                	red.setPosition(55+b_c.pos_i*73.625,55+b_c.pos_j*73.625 );
				                	redb=true;
								   }
				                  //  cout<<b_c.pos_i<<" "<<b_c.pos_j<<endl;
				                    
								}
				            }
				            else 
				            {
				                cout << "Move " << move << " is not legal." << std::endl;
				                
				            }

                    }
                }
}

/***************************************************************
 * main
 *
 * This is where it all starts!
 ***************************************************************/
int main()
{
    srand(time(0)); // Seed the random number generator.

    CBoard board;
    AI ai(board);
    board_converter b_c;
    setposition(b_c.array_temp);
    bool multiplayer_mode=true;

    place();
    sf::RenderWindow window(sf::VideoMode(700, 700), "SFML works!");
    window.setFramerateLimit(30);
    sf::Event event;
    sf::Texture t;

    t.loadFromFile("images/gameboard.jpg");  // loads board
    sf::Sprite s(t);
    s.setPosition(0,0);

    sf::Texture b;
    b.loadFromFile("images/green.png", sf::IntRect(0,0,73.625,73.625));
    sf::Sprite blue(b);

    sf::Texture r;
    r.loadFromFile("images/red.png", sf::IntRect(0,0,73.625,73.625));
    sf::Sprite red(r);
    sf::Texture g;
    g.loadFromFile("images/blue.png", sf::IntRect(0,0,73.625,73.625));
    sf::Sprite green[10];
    for(int i=0; i<10;i++)
    {
    	green[i]= sf::Sprite(g);
	}
    


     bool fpressp[8]={0,0,0,0,0,0};
     bool fpressh[2]={0,0};
     bool fpressr[2]={0,0};
     bool fpressb[2]={0,0};
     bool fpressq=false;
     bool fpressk=false;
     bool fpresspb[8]={0,0,0,0,0,0};
     bool fpresshb[2]={0,0};
     bool fpressrb[2]={0,0};
     bool fpressbb[2]={0,0};
     bool fpressqb=false;
     bool fpresskb=false;
    bool blu=false;
    bool player_turn=true;
    bool pre =true;
    int in=2;
    int tomove;
    bool redb=false, gree=false;
 


    while (window.isOpen())
    {
        sf::Vector2i pos = sf::Mouse::getPosition(window);
        if(player_turn)
        {
           
            while(window.pollEvent(event))
            {
                if( event.type == sf::Event::Closed )
                window.close();
                for(int i=0; i<pwi; i++)
                mouse(wp[i], event, window,blue, player_turn, blu, fpressp[i], pos.x, pos.y,b_c,board,red,redb,green,gree);
                for(int i=0; i<rwi; i++)
                mouse(wr[i], event, window,blue, player_turn, blu, fpressr[i], pos.x, pos.y,b_c,board,red,redb,green,gree);
                for(int i=0; i<hwi; i++)
                mouse(wh[i], event, window,blue, player_turn, blu, fpressh[i], pos.x, pos.y,b_c,board,red,redb,green,gree);
                for(int i=0; i<bwi; i++)
                mouse(wb[i], event, window,blue, player_turn, blu, fpressb[i], pos.x, pos.y,b_c,board,red,redb,green,gree);
                mouse(wq, event, window,blue, player_turn, blu, fpressq, pos.x, pos.y,b_c,board,red,redb,green,gree);
                mouse(wk, event, window,blue, player_turn, blu, fpressk, pos.x, pos.y,b_c,board,red,redb,green,gree);
            if(!(multiplayer_mode))
                {
				
               if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
       				{				
		                 CMove best_move = ai.find_best_move();

				         cout << "bestmove " << best_move << endl;
				         board.make_move(best_move); 
				         b_c.san_to_nischal(best_move.m_from,best_move.m_to);
				         setposition(b_c.array_temp);
				         place();
				         redb=false;
				           bool check = board.isOtherKingInCheck();
				           bool check_other = board.isKingInCheck();
				               // board.undo_move(move);
				               
				                if (check)
				                {
				                    cout << "Black king is in check. Play another move." << endl;  
				                    //b_c.position_check(-10);
				                   // cout<<b_c.pos_i<<" "<<b_c.pos_j<<endl;
				                }
				                if(check_other)
				                {
				                	cout << "White King is  in CHECK" << endl;  
									b_c.position_check(10);
									red.setPosition(55+b_c.pos_i*73.625,55+b_c.pos_j*73.625 );
				                    //cout<<b_c.pos_i<<" "<<b_c.pos_j<<endl;
				                    redb=true;
				                    string kk;
				                    CMoveList movesss;
				                    board.find_legal_moves(movesss);
				                    
				                   // cout<<board.	
								}
								
				         
       			    }
            	}

            }
        }
        if(!player_turn)
        {
        	
           if(multiplayer_mode)
           {
			//cout<<"Multiplayer_mode"<<endl;
		
			while(window.pollEvent(event))
            {
                if( event.type == sf::Event::Closed )
                window.close();
                for(int i=0; i<pbi; i++)
                mouse(bp[i], event, window,blue, player_turn, blu, fpresspb[i], pos.x, pos.y,b_c,board,red,redb,green,gree);
                for(int i=0; i<rbi; i++)
                mouse(br[i], event, window,blue, player_turn, blu, fpressrb[i], pos.x, pos.y,b_c,board,red,redb,green,gree);
                for(int i=0; i<hbi; i++)
                mouse(bh[i], event, window,blue, player_turn, blu, fpresshb[i], pos.x, pos.y,b_c,board,red,redb,green,gree);
                for(int i=0; i<bbi; i++)
                mouse(bb[i], event, window,blue, player_turn, blu, fpressbb[i], pos.x, pos.y,b_c,board,red,redb,green,gree);
                mouse(bq, event, window,blue, player_turn, blu, fpressqb, pos.x, pos.y,b_c,board,red,redb,green,gree);
                mouse(bk, event, window,blue, player_turn, blu, fpresskb, pos.x, pos.y,b_c,board,red,redb,green,gree);
            }
		   }
            else
            {
			
            in++;
            player_turn = true;
            cout<<"Black to move"<<endl;
           }
             
        }
        window.clear();
        window.draw(s);
        if(blu)
            window.draw(blue);
            if(redb)
            window.draw(red);
            if(gree)
            {
            	for(int i=0; i<k;i++)
            	{
            		window.draw(green[i]);
				}
			}
        
        draw(window);
        window.display();
        
    }  
    return 0;
    //end of while(true)

}
  
    
       

void board_converter::san_to_nischal(const CSquare From,const CSquare To)
{
    from=From;
    to= To;
	cout<<from<<endl;
	cout<<to<<endl;   
    cout<<array_temp[11-(to/10)][to%10-1];
	array_temp[9-(to/10)][to%10-1]=array_temp[9-(from/10)][from%10-1];
	array_temp[9-(from/10)][from%10-1]=0;
	cout<<array_temp[11-(to/10)][to%10-1];
	to_row =(11-(to/10));
	to_col=(to%10-1);
	from_row=(11-(from/10));
	from_col=(from%10-1);
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			cout<<", "<<array_temp[i][j];
		}
		cout<<endl;
   }
  
}

void board_converter::position_check(int pie)
{ 
    int flag=0;
	for(int i=0;i<8;i++)
	{   
	   cout<<"Debug1"<<endl;
		for(int j=0;j<8;j++)
		{
			cout<<"Debug2"<<endl;
			cout<<array_temp[i][j]<<endl;
			if(array_temp[i][j]==pie)
			{
				pos_i=j;
				pos_j=i;
				flag=1;
				cout<<i<<" "<<j<<endl;
				break;
			
			}
		}
		if(flag==1)break;
		
   }
	 
}

string board_converter::converter(int _row,int _col)
{
	
    string _c;	
    	switch(_col)
    	{
    		case 1:_c="a"; break;
    		case 2:_c="b"; break;
    		case 3:_c="c"; break;
    		case 4:_c="d"; break;
    		case 5:_c="e"; break;
    		case 6:_c="f"; break;
    		case 7:_c="g"; break;
    		case 8:_c="h"; break;
    			
		}
	 s1=_c+int_to_str(_row);
	 cout<<s1<<endl;
	 return s1;
	 
}

void board_converter::tukrauna(int mmm )
{
	y_tukra=(9-(mmm/10));
	x_tukra=((mmm%10)-1);
//	cout<<x_tukra<<"vv "<<y_tukra<<endl;
	}



//string board_converter::nischal_to_san()
//{
//	return s1+s2;
//}
