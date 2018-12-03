
#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include "CBoard.h"
#include "ai.h"
#include "nischal_graphics.h"
#include "opencv.h"
#include "serial.h"



using namespace std;
int newposx, newposy,prepsx,prepsy,k;

void display_Menu1()
{
    pos11.dis(0,"Play as White",0,255,0,255);
    pos11.dis(1,"Multi Player",0,255,0,255);
    pos11.dis(2,"Credit",0,255,0,255);
    pos11.dis(3,"Exit",0,255,0,255);
}

class board_converter
{
 public:
  void san_to_nischal(const CSquare From,const CSquare To,int& k);
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



/***************************************************************
 * main
 *
 * This is where it all starts!
 ***************************************************************/
int main()
{
    int x,y,wid,heg;
   //detectchessboard();
    chess_read();
    calibration();
    crop(x,y,wid,heg);
    Rect tocrop(x,y,wid,heg);
    int ffg;
    bool multiplayer_mode;
   
    bool blu=false;
    bool player_turn=true;

    bool redb=false, gree=false;
    int loading=0;

    int premove=0,postmove=0;
    cv::VideoCapture capVideo;
	capVideo.open("http://192.168.43.1:8080/video?x.mjpeg");
    serial s1;
    s1.load_all_values();
    //load_all_values();

   
    //using std::vector;
    //vector<vector<vector<vector<int>>>> array4D;

	cv::Mat imgFrame1;
	cv::Mat imgFrame2;
	Mat find_blobs;
    cv::Point centroid;
    if (!capVideo.isOpened()) {                                                
		std::cout << "\nerror reading video file" << std::endl << std::endl;     
		return(0);                                                             
	}
    else
    {
        cout<<"\nVideo File read sucessfully"<<endl;
    }

    //capVideo.read(imgFrame1);
	//capVideo.read(imgFrame2);
    capVideo.read(imgFrame2);
    sf::RenderWindow windownew(sf::VideoMode(SCRWIDTH, SCRHEIGHT), "AI Chess");
    windownew.setFramerateLimit(30);
  	sf::Event eventnew;

	sf::Texture lex,tex;
	lex.loadFromFile("images/loading1.png");
	tex.loadFromFile("images/9.jpg");

   	sf::IntRect crop(0, 0, 700, 40);
   	sf::Sprite sprite12(lex,crop),s(tex);

  	sf::Music music[12];
	  music[0].openFromFile("Sounds/theme.ogg");
	  music[1].openFromFile("Sounds/menu.wav");
	  music[2].openFromFile("Sounds/click.wav");
	  music[3].openFromFile("Sounds/Invalid_Move.wav");
	  music[4].openFromFile("Sounds/eating.wav");
	  music[5].openFromFile("Sounds/check_mate.wav");
	  music[6].openFromFile("Sounds/exit.wav");
	  music[7].openFromFile("Sounds/pieces_click.wav");
      music[8].openFromFile("Sounds/your_turn.wav");
      music[9].openFromFile("Sounds/Invalid_Move.wav");
      music[10].openFromFile("Sounds/Check_warning.wav");
      music[11].openFromFile("Sounds/check.wav");
   
	  
	//void display_Menu1();
    display_Menu1();
 
/*
while (windownew.isOpen())
{
   // cout<<"i am running"<<endl;
    sf::Vector2i MousePosition = sf::Mouse::getPosition(windownew);

        while (windownew.pollEvent(eventnew))
        {
            if( eventnew.type == sf::Event::Closed )
                {
				windownew.close();exit(-1);
				}
            if((eventnew.type==sf::Event::KeyPressed) and (eventnew.key.code== sf::Keyboard::Escape))
               {
			   windownew.close();
			   exit(-1);
				}		
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

                    
                }Artificial Intelligence: A Modern Approach (3rd Edition

                if(loading==1)
                {
                    for(int j=0;j<4;j++)
                    {windownew.draw(pos11.temp[j]);}
                    windownew.display();
                    loading=2;
                    
                }

                if(pos11.temp[0].getGlobalBounds().contains(MousePosition.x,MousePosition.y) )//MOUSE FOR PLASY AS WHITE
                {
                    music[1].play();
                    SCRWIDTH=700;SCRHEIGHT=700;
                    for(int j=0;j<10;j++)
                    pos11.temp[j].setString("");

                    display_Menu1();
                    pos11.dis(0,"Play as White",255,255,255,255);

                    for(int j=0;j<4;j++)
                    {windownew.draw(pos11.temp[j]);}

                    windownew.display();

                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        music[2].play();
                        windownew.clear(sf::Color::Black);

                        multiplayer_mode=false;
                      ffg=1;
                      cout<<"computer"<<endl;
                      //break;
                    }
                    
 				}
              else if(pos11.temp[1].getGlobalBounds().contains(MousePosition.x,MousePosition.y))//MOUSE FOR Multi Player
              {
                  music[1].play();

                    SCRWIDTH=700;SCRHEIGHT=700;
                    for(int j=0;j<10;j++)
                    pos11.temp[j].setString("");

                    display_Menu1();
                    pos11.dis(1,"Multi Player",255,255,255,255);

                    for(int j=0;j<4;j++)
                    {windownew.draw(pos11.temp[j]);}

                    windownew.display();
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        music[2].play();
                        multiplayer_mode=true;
                        ffg=1;
                        //break;
                        
                    }
                    
               }


              else if(pos11.temp[2].getGlobalBounds().contains(MousePosition.x,MousePosition.y))//MOUSE FOR CREDIT
              {
                  music[1].play();
                  SCRWIDTH=700;SCRHEIGHT=700;
                    for(int j=0;j<10;j++)
                    pos11.temp[j].setString("");

                    display_Menu1();
                    pos11.dis(2,"Credit",255,255,255,255);

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
                            //ffg=1;
                            sf::sleep(sf::seconds(1));
                            //break;
                    }
                    
              }
              else if(pos11.temp[3].getGlobalBounds().contains(MousePosition.x,MousePosition.y))//MOUSE FOR EXIT
              {
                  music[1].play();
                  SCRWIDTH=700;SCRHEIGHT=700;
                    for(int j=0;j<10;j++)
                    pos11.temp[j].setString("");

                    display_Menu1();
                    pos11.dis(3,"Exit",255,255,255,255);

                    for(int j=0;j<4;j++)
                    {windownew.draw(pos11.temp[j]);}

                    windownew.display();
                  if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        music[2].play();
                        music[6].play();
                        sf::sleep(sf::seconds(2));
                        windownew.close();
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
*/
    
    capVideo.read(imgFrame2);
   
    bool san=true;
    srand(time(0)); // Seed the random number generator
    CBoard board;
    AI ai(board);
    board_converter b_c;
    setposition(b_c.array_temp);
    //Rect tocrop(2*x[1][1]-x[1][2]-15,2*y[1][1]-y[2][1]-15,((2*x[7][7]-x[7][6])-(2*x[1][1]-x[1][2]))+20,((2*y[7][7]-y[6][7])-(2*y[1][1]-y[2][1]))+20);
    place();
    sf::Texture t;
    t.loadFromFile("images/gameboard.jpg");  // loads board
    sf::Sprite sboard(t);
    sboard.setPosition(0,0);

    sf::Texture b;
    b.loadFromFile("images/green.PNG", sf::IntRect(0,0,73.625,73.625));
    sf::Sprite blue(b);

    sf::Texture r;
    r.loadFromFile("images/red.PNG", sf::IntRect(0,0,73.625,73.625));
    sf::Sprite red(r);
    sf::Texture g;
    g.loadFromFile("images/blue.PNG", sf::IntRect(0,0,73.625,73.625));
    sf::Sprite green[10];
    for(int i=0; i<10;i++)
    {
    	green[i]= sf::Sprite(g);
	}
    sf::RenderWindow window(sf::VideoMode(700, 700), "AI Chess");
    window.setFramerateLimit(30);
    sf::Event event;
    //int aaa=0,bbb=0;
    capVideo.read(imgFrame2);
    window.clear();
    window.draw(sboard);
    draw(window);
    window.display();
   
    while (window.isOpen())
    {  
       
        sf::Vector2i pos = sf::Mouse::getPosition(window);


        if(player_turn)
        {
               
            while(window.pollEvent(event))
            { 
                if( event.type == sf::Event::Closed )
                window.close();


            }

           		//capVideo.read(imgFrame2);
                
                CMove best_move = ai.find_best_move();

                cout << "bestmove " << best_move << endl;
                board.make_move(best_move); 
                b_c.san_to_nischal(best_move.m_from,best_move.m_to,k);
                setposition(b_c.array_temp);
                place();
                capVideo.read(imgFrame2);
                redb=false;
                bool check = board.isOtherKingInCheck();
                bool check_other = board.isKingInCheck();
                player_turn = false;

                b_c.tukrauna(best_move.m_to);
                green[0].setPosition(55+(b_c.x_tukra)*73.625,55+(b_c.y_tukra)*73.625);
                gree=true;

                b_c.tukrauna(best_move.m_from);
                blue.setPosition(55+(b_c.x_tukra)*73.625,55+(b_c.y_tukra)*73.625);
                blu=true;
                                                
                if (check)
                {
                     
                     cout << "Our King is in check play other moves" << endl;  
                }

                if(check_other)
                {
                
                    windownew.clear();
                    //music[11].play();
                    sf::sleep(sf::seconds(1));
                    for(int j=0;j<4;j++)
                    {windownew.draw(s);windownew.draw(pos11.temp[j]);windownew.display();sf::sleep(sf::seconds(1));}
                    cout << "Black king is in check" << endl;  
                    b_c.position_check(-10);
                    red.setPosition(55+b_c.pos_i*73.625,55+b_c.pos_j*73.625 );
                    redb=true;
                    string kk;
                    CMoveList movesss;
                    board.find_legal_moves(movesss); 
                                            	
                }			


                  //Dawadi's code is waiting
                //In this portion dawadi's code will send array matix in steps and then microcontroller will return ok signal then only loop terminates
                //(8-(int)(best_move.m_from/10)),(int)(best_move.m_from%10),(8-(int)(best_move.m_to/10)),(int)(best_move.m_to%10)
                cout<<"frome:"<<best_move.m_from<<best_move.m_to<<endl;
                //capVideo.read(imgFrame2);
                cout<<"Value of k:"<<k<<endl;
                if(!k)
                    s1.major_task((int)(best_move.m_from/10)-1,(int)(best_move.m_from%10),(int)(best_move.m_to/10)-1,(int)(best_move.m_to%10),NORMAL);
                else
                    s1.major_task((int)(best_move.m_from/10)-1,(int)(best_move.m_from%10),(int)(best_move.m_to/10)-1,(int)(best_move.m_to%10),KILL);   
                //s1.major_task(2,5,4,5);

                if(check_other)
                    music[11].play();

                
                window.clear();
                window.draw(sboard);
                if(blu)
                    window.draw(blue);
                if(redb)
                    window.draw(red);
                if(gree)
                {
                    for(int i=0; i<1;i++)
                    {
                        window.draw(green[i]);
                    }
                }
                
                draw(window);
                window.display();

            capVideo.open("http://192.168.43.1:8080/video?x.mjpeg"); 
            for(int i=0;i<8;i++)   
            {
                if(!capVideo.read(imgFrame2))
                {
                    cout<<"Note captured"<<endl;
                } 

            } 

            imgFrame2 = imgFrame2(tocrop);
           
            
     
        }

       
        if(!player_turn)
        { 
             //Image Processing code in this  section
              string str,str1,str2,str3,_c,kk;
             // in this place we can also replace by code of button
           
           if(san)
           {
               music[8].play();
               cout<<"motion_detected"<<endl;
               motion_detect(capVideo);

           }
        
                capVideo.read(imgFrame1);
                imgFrame1 = imgFrame1(tocrop);
            
                cout<<"i am here"<<endl;
               // imshow("imgFrame1",imgFrame1);
                //imshow("imgFrame2",imgFrame2);
                //waitKey(0);
                    
                if(Detect_moves(imgFrame1,imgFrame2,centroid))
                {
                    
                    cout<<"i am in loop"<<endl;
                    
                    cout<<"Centroid"<<centroid<<endl;
                    premove = find_move(centroid);
                    cout<<"premoves:"<<premove<<endl;
                    
                   if(Detect_moves(imgFrame2,imgFrame1,centroid))
                    {
                        san = true;
                       //cout<<"i am in post loop"<<endl;    
                        postmove = find_move(centroid);

                        prepsx  =  int(premove/10);
                        prepsy  = (premove%10);

                        newposx = int(postmove/10);
                        newposy = (postmove % 10);

                        str3=b_c.converter(9-prepsy,prepsx);
                        music[7].play();
                        cout<<"newposx:"<<newposx<<" "<<"newposy:"<<newposy<<endl;
                    
                        blu=false;
                        gree=false;
                        CMove move;    
                        str2=b_c.converter(9-newposy,newposx);	    			 
                        str1="move ";
                        str.append(str1);
                        str.append(str3);
                        str.append(str2);
                        cout<<"STRING:"<<str<<endl;
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
                                cout << "Your are in check play another move." << endl;  
                                music[10].play();

                                motion_detect(capVideo);
                                for(int i=0;i<15;i++)   
                                {
                                    if(!capVideo.read(imgFrame2))
                                    {
                                        cout<<"Note captured"<<endl;
                                    } 

                                } 
                                imgFrame2 = imgFrame2(tocrop);
                            
                                san = true;
                            
                                cout<<b_c.pos_i<<" "<<b_c.pos_j<<endl;
                            }

        
                            else 
                            {
                                cout << "You move : " << move << std::endl;
                                b_c.tukrauna(move.m_to);
                                green[0].setPosition(55+(b_c.x_tukra)*73.625,55+(b_c.y_tukra)*73.625);
						        gree=true;
                                 b_c.tukrauna(move.m_from);
                                blue.setPosition(55+(b_c.x_tukra)*73.625,55+(b_c.y_tukra)*73.625);
						        blu=true;
                                board.make_move(move);
                                b_c.array_temp[newposy-1][newposx-1] = b_c.array_temp[prepsy-1][prepsx-1];
                                b_c.array_temp[prepsy-1][prepsx-1]=0;
                                setposition(b_c.array_temp);
                                place();
                                if(player_turn)
                                {
                                    player_turn=false;
                                    cout<<"Black Turn"<<endl;
                                }				                
                                else
                                {
                                    player_turn=true;
                                    cout<<"white Turn"<<endl;
                                }
                                
                            
                            }
                            
                            if(check_other)
                            {
        
                                cout << "white kings is in CHECK" << endl;  
                                b_c.position_check(10);
                                red.setPosition(55+b_c.pos_i*73.625,55+b_c.pos_j*73.625 );
                                redb=true;
                               music[5].play();
                                
                            }
                        }
                        else 
                        {
                            cout << "Move " << move << " is not legal." << std::endl;
                             music[9].play();
                        

                            window.clear();
                            window.draw(sboard);
                            if(blu)
                                window.draw(blue);
                                if(redb)
                                window.draw(red);
                                if(gree)
                                {
                                    for(int i=0; i<1;i++)
                                    {
                                        window.draw(green[i]);
                                    }
                                }
                            
                            draw(window);
                            window.display();  
                            
                            motion_detect(capVideo);
                            for(int i=0;i<15;i++)   
                            {
                                if(!capVideo.read(imgFrame2))
                                {
                                    cout<<"Note captured"<<endl;
                                } 

                            } 
                            imgFrame2 = imgFrame2(tocrop);
                        
                                san = true;
                                    
                         }

                    }
                     else
                    {
                        san = false;
                        cout<<"loop 2nd"<<endl;
                    }
                    

                }
                else
                {
                      san = false;
                      player_turn=false;
                      
                }

            window.clear();
            window.draw(sboard);
            if(blu)
                window.draw(blue);
                if(redb)
                window.draw(red);
                if(gree)
                {
                    for(int i=0; i<1;i++)
                    {
                        window.draw(green[i]);
                    }
                }
            
            draw(window);
            window.display();  
            blu=false;
            gree=false;
            
        } 
        
    }  //end of while(true)

     // my_serial_stream.Close();
     
      return 0;

  
}
  
    
       

void board_converter::san_to_nischal(const CSquare From,const CSquare To,int& k)
{
    from=From;
    to= To;
	cout<<from<<endl;
	cout<<to<<endl;   
    cout<<array_temp[11-(to/10)][to%10-1];
    k = array_temp[9-(to/10)][to%10-1];
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
}



