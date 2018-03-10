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
void mouse(T &obj, sf::Event &event, sf::RenderWindow &window, sf::Sprite &blue,bool &player_turn, bool &blu, bool &fpress, int posx, int posy, board_converter &b_c,CBoard &board,sf::Sprite &red,bool &redb,sf::Sprite *green,bool &gree,sf::Music *music)
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
                        			music[2].play();
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
                        music[2].play();
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
				                	music[5].play();
				                	
				                   }
				                   else 
				                   {
				                   	cout << "white kings is in CHECK" << endl;  
				                	b_c.position_check(10);
				                	red.setPosition(55+b_c.pos_i*73.625,55+b_c.pos_j*73.625 );
				                	redb=true;
				                	music[5].play();
								   }
				                  //  cout<<b_c.pos_i<<" "<<b_c.pos_j<<endl;
				                    
								}
				            }
				            else 
				            {
				                cout << "Move " << move << " is not legal." << std::endl;
				                music[3].play();
				                
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
    int in=2,ffg=0;
    int tomove;
    bool redb=false, gree=false;
    int loading=0;
    bool multiplayer_mode;
    sf::RenderWindow windownew(sf::VideoMode(SCRWIDTH, SCRHEIGHT), "AI Chess");
    windownew.setFramerateLimit(30);
  	sf::Event eventnew;

	sf::Texture lex,tex;
	lex.loadFromFile("images/loading1.png");
	tex.loadFromFile("images/9.jpg");

   	sf::IntRect crop(0, 0, 700, 40);
   	sf::Sprite sprite12(lex,crop),s(tex);

  	sf::Music music[7];
	  music[0].openFromFile("Sounds/theme.ogg");
	  music[1].openFromFile("Sounds/menu.wav");
	  music[2].openFromFile("Sounds/click.wav");
	  music[3].openFromFile("Sounds/invalid.wav");
	  music[4].openFromFile("Sounds/eating.wav");
	  music[5].openFromFile("Sounds/checkmate.wav");
	  music[6].openFromFile("Sounds/exit.wav");
	pos11.dis(0,"Play as White",0,255,0,255);
	pos11.dis(1,"Multi Player",0,255,0,255);
	pos11.dis(2,"Credit",0,255,0,255);
	pos11.dis(3,"Exit",0,255,0,255);
 

while (windownew.isOpen())
{
    sf::Vector2i MousePosition = sf::Mouse::getPosition(windownew);

        while (windownew.pollEvent(eventnew))
        {
            if( eventnew.type == sf::Event::Closed )
                windownew.close();
            if((eventnew.type==sf::Event::KeyPressed) and (eventnew.key.code== sf::Keyboard::Escape))
               windownew.close();
                windownew.draw(s);
                if(loading==0)
                {
                    music[0].play();
                    for(int k=0;k<15;k++)
                    {
                        sprite12.setTextureRect(crop);
                        windownew.draw(sprite12);

                        windownew.display();
                        sf::sleep(sf::seconds(0.25));
                    crop.height+=50;
                    }
                    loading=1;

                    windownew.draw(s);
                    SCRHEIGHT=2400; SCRWIDTH=400;
                    loading1.dis(0,"Wait             Loading.....",255,255,255,255);
                    windownew.draw(loading1.temp[0]);
                    windownew.display();

                    windownew.clear();

                    sf::sleep(sf::seconds(1));
                    for(int j=0;j<4;j++)
                    {windownew.draw(s);windownew.draw(pos11.temp[j]);windownew.display();sf::sleep(sf::seconds(1));}

                    cout<<"loading0"<<endl;
                }

                if(loading==1)
                {
                    for(int j=0;j<4;j++)
                    {windownew.draw(pos11.temp[j]);}
                    windownew.display();
                    loading=2;
                    cout<<"loading1"<<endl;
                }

                if(pos11.temp[0].getGlobalBounds().contains(MousePosition.x,MousePosition.y) )//MOUSE FOR PLASY AS WHITE
                {
                    music[1].play();
                    SCRWIDTH=700;SCRHEIGHT=700;
                    for(int j=0;j<10;j++)
                    pos11.temp[j].setString("");

                    pos11.dis(0,"Play as White",255,255,255,255);
                    pos11.dis(1,"Multi Player",0,255,0,255);
                    pos11.dis(2,"Credit",0,255,0,255);
                    pos11.dis(3,"Exit",0,255,0,255);

                    for(int j=0;j<4;j++)
                    {windownew.draw(pos11.temp[j]);}

                    windownew.display();

                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        music[2].play();
                        windownew.clear(sf::Color::Black);

                        multiplayer_mode=false;
                      ffg=1;
                      cout<<"coumputer"<<endl;
                      break;
                    }
                    
 				}
              else if(pos11.temp[1].getGlobalBounds().contains(MousePosition.x,MousePosition.y))//MOUSE FOR Multi Player
              {
                  music[1].play();

                    SCRWIDTH=700;SCRHEIGHT=700;
                    for(int j=0;j<10;j++)
                    pos11.temp[j].setString("");

                    pos11.dis(0,"Play as White",0,255,0,255);
                    pos11.dis(1,"Multi Player",255,255,255,255);
                    pos11.dis(2,"Credit",0,255,0,255);
                    pos11.dis(3,"Exit",0,255,0,255);

                    for(int j=0;j<4;j++)
                    {windownew.draw(pos11.temp[j]);}

                    windownew.display();
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        music[2].play();
                        multiplayer_mode=true;
                        ffg=1;
                        break;
                    }
                    
               }


              else if(pos11.temp[2].getGlobalBounds().contains(MousePosition.x,MousePosition.y))//MOUSE FOR CREDIT
              {
                  music[1].play();
                  SCRWIDTH=700;SCRHEIGHT=700;
                    for(int j=0;j<10;j++)
                    pos11.temp[j].setString("");

                    pos11.dis(0,"Play as White",0,255,0,255);
                    pos11.dis(1,"Multi Player",0,255,0,255);
                    pos11.dis(2,"Credit",255,255,255,255);
                    pos11.dis(3,"Exit",0,255,0,255);

                    for(int j=0;j<4;j++)
                    {windownew.draw(pos11.temp[j]);}

                    windownew.display();
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        music[2].play();
                        SCRWIDTH=200;
                        windownew.clear();

                        for(int j=0;j<10;j++)
                        pos11.temp[j].setString("");

                        pos11.dis(0,"Created By: ",255,255,0,255);
                        pos11.dis(1,"Nischal Maharjan (421)",0,255,0,255);
                        pos11.dis(2,"Sangam Man Buddhacharya (438)",0,255,255,255);
                        pos11.dis(3,"Shiva Bhandari (442)",200,200,255,255);
                        pos11.dis(4,"Sunil Dhakal (447)",255,255,255,255);

                        for(int j=0;j<5;j++)
                        {windownew.draw(s);windownew.draw(pos11.temp[j]);windownew.display();sf::sleep(sf::seconds(2));}
                         for(int j=0;j<5;j++)
                        {windownew.draw(pos11.temp[j]);}
                            windownew.display();
                            ffg=1;
                            break;
                    }
                    
              }
              else if(pos11.temp[3].getGlobalBounds().contains(MousePosition.x,MousePosition.y))//MOUSE FOR EXIT
              {
                  music[1].play();
                  SCRWIDTH=700;SCRHEIGHT=700;
                    for(int j=0;j<10;j++)
                    pos11.temp[j].setString("");

                    pos11.dis(0,"Play as White",0,255,0,255);
                    pos11.dis(1,"Multi Player",0,255,0,255);
                    pos11.dis(2,"Credit",0,255,0,255);
                    pos11.dis(3,"Exit",255,255,255,255);

                    for(int j=0;j<4;j++)
                    {windownew.draw(pos11.temp[j]);}

                    windownew.display();
                  if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        music[2].play();
                        music[6].play();
                        sf::sleep(sf::seconds(2));
                        exit(0);
            
                    }
                    
               }
          }
          if(ffg==1)
		  {
		  	windownew.close();
		  	break;
		}
  }
    
    srand(time(0)); // Seed the random number generator
    CBoard board;
    AI ai(board);
    board_converter b_c;
    setposition(b_c.array_temp);
    place();
    for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			cout<<", "<<b_c.array_temp[i][j];
		}
		cout<<endl;
   }
    sf::Texture t;
    t.loadFromFile("images/gameboard.jpg");  // loads board
    sf::Sprite sboard(t);
    sboard.setPosition(0,0);

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
    sf::RenderWindow window(sf::VideoMode(700, 700), "AI Chess");
    window.setFramerateLimit(30);
    sf::Event event;
     cout<<"I am setting done"<<endl;
     int aaa=0,bbb=0;
     
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
                mouse(wp[i], event, window,blue, player_turn, blu, fpressp[i], pos.x, pos.y,b_c,board,red,redb,green,gree,music);
                for(int i=0; i<rwi; i++)
                mouse(wr[i], event, window,blue, player_turn, blu, fpressr[i], pos.x, pos.y,b_c,board,red,redb,green,gree,music);
                for(int i=0; i<hwi; i++)
                mouse(wh[i], event, window,blue, player_turn, blu, fpressh[i], pos.x, pos.y,b_c,board,red,redb,green,gree,music);
                for(int i=0; i<bwi; i++)
                mouse(wb[i], event, window,blue, player_turn, blu, fpressb[i], pos.x, pos.y,b_c,board,red,redb,green,gree,music);
                mouse(wq, event, window,blue, player_turn, blu, fpressq, pos.x, pos.y,b_c,board,red,redb,green,gree,music);
                mouse(wk, event, window,blue, player_turn, blu, fpressk, pos.x, pos.y,b_c,board,red,redb,green,gree,music);
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

//             if(aaa==0)
//             {
//             	cout<<"Black Turn"
//			 }
            
        }
        if(!player_turn)
        { 
           int aaa=0;
        	
           if(multiplayer_mode)
           {
			//cout<<"Multiplayer_mode"<<endl;
		
			while(window.pollEvent(event))
            {
                if( event.type == sf::Event::Closed )
                window.close();
                for(int i=0; i<pbi; i++)
                mouse(bp[i], event, window,blue, player_turn, blu, fpresspb[i], pos.x, pos.y,b_c,board,red,redb,green,gree,music);
                for(int i=0; i<rbi; i++)
                mouse(br[i], event, window,blue, player_turn, blu, fpressrb[i], pos.x, pos.y,b_c,board,red,redb,green,gree,music);
                for(int i=0; i<hbi; i++)
                mouse(bh[i], event, window,blue, player_turn, blu, fpresshb[i], pos.x, pos.y,b_c,board,red,redb,green,gree,music);
                for(int i=0; i<bbi; i++)
                mouse(bb[i], event, window,blue, player_turn, blu, fpressbb[i], pos.x, pos.y,b_c,board,red,redb,green,gree,music);
                mouse(bq, event, window,blue, player_turn, blu, fpressqb, pos.x, pos.y,b_c,board,red,redb,green,gree,music);
                mouse(bk, event, window,blue, player_turn, blu, fpresskb, pos.x, pos.y,b_c,board,red,redb,green,gree,music);
                  
            }
		   }
            else
            {
			
            in++;
            player_turn = true;
            cout<<"Black to move"<<endl;
           }
           if(aaa=0)
           {
           	cout<<"Black Turn"<<endl;
           	aaa=1;
		   }
           
     
        }
        window.clear();
        window.draw(sboard);
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
        
    }  //end of while(true)


    
    return 0;
    

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
