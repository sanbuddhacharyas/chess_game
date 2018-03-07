#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include "CBoard.h"
#include "ai.h"
#include "nischal_graphics.h"

using namespace std;
class board_converter
{
 public:
  void san_to_nischal(const CSquare From,const CSquare To);
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
    srand(time(0)); // Seed the random number generator.

    CBoard board;
    AI ai(board);
    board_converter b_c;
    
     


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


    while (true)
    {


        while(window.isOpen())
		 
	 {  
	    setposition(b_c.array_temp);
        sf::Event event;
        while (window.pollEvent(event))
        {

            if( event.type == sf::Event::Closed )
                window.close();

        }
       window.clear();//clears the windows
	   window.draw(s);//draw the board
	   draw(window); // draw all the pieces in the board
	   window.display();
			
        //cout << "Input command : ";
        // Read input from player
        string str,str1,str2;
        getline(cin, str);
        cout << endl;
        str1="move ";
        
        str = str1+ b_c.converter(2,5)+b_c.converter(4,5);// concatenating string  from- to in chess notation
     
        // Parse input from player
        if (cin.eof() || str == "quit")
        {
            exit(1);
        }

        if (str.compare(0, 5, "move ") == 0)
        {
            CMove move;

            if (move.FromString(str.c_str()+5) == NULL)
            {
                // Could not parse move.
                cout << "Try again. Use long notation, e.g. e2e4" <<endl;
                continue; // Go back to beginning
            }

            if (board.IsMoveValid(move))  //From this line code must be changed with graphics
            {
                board.make_move(move);
                bool check = board.isOtherKingInCheck();
                board.undo_move(move);
                if (check)
                {
                    cout << "You are in CHECK. Play another move." << endl;
                    continue;
                }

                cout << "You move : " << move << std::endl;
                board.make_move(move);
               // setposition(b_c.array_temp); 
		       /*
		           Matrix board for graphics is to be remake
		           b_c.arrray_temp[][]=b_c.array_temp[][];
		       */
                window.clear();
		        window.draw(s);
		        draw(window);
		        window.display();
            }
            else 
            {
                cout << "Move " << move << " is not legal." << std::endl;
                continue;
            }
        } // end of "move "

        else if (str.compare(0, 2, "go") == 0)
        {
            CMove best_move = ai.find_best_move();

            cout << "bestmove " << best_move << endl;

            board.make_move(best_move);
            
            b_c.san_to_nischal(best_move.m_from,best_move.m_to);
           // setposition(b_c.array_temp);
            window.clear();
	        window.draw(s);
	        draw(window);
	        window.display();
          
            
        } // end of "go"

        else if (str == "show")
        {
            CMoveList moves;
            board.find_legal_moves(moves);

            //            std::cout << moves.ToShortString() << std::endl;
            cout << moves << endl;
        }

        else 
        {
            cout << "Unknown command" << endl;
            cout << "Valid commands are: quit, move, go, show" << endl;
        }
   
      } // end of while (true)
   
   } //end of window open

    return 0;
  
    
       
} // end of int main()
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
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			cout<<", "<<array_temp[i][j];
		}
		cout<<endl;
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
	 return s1;
	 
}

//string board_converter::nischal_to_san()
//{
//	return s1+s2;
//}
