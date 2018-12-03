#include "SerialPort.h"
#include "SerialStream.h"
#include <iostream>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <vector>

/**********************VARIABLES********************************/
#define HEIGHT 8
#define WIDTH 8
#define DEPTH1 3
#define DEPTH2 2
double count = 0;
int q1 = 50, q2 = 20, pos = -15;
char ending_character = '.';
char grabbing_character = 'g';
char releasing_character = 'r';
char received_character;

/*************FUNCTION PROTOTYPES***************************/
void  hover_the_box(int row, int column);
void go_down(int row, int column);
void major_task(int from_row,int from_col,int to_row,int to_col);       //pick from one box & drop to another
void wait(void);
void load_all_values(void);
void delay(int time_in_sec);

//rfcomm0 is the required port for serial communication
LibSerial::SerialStream my_serial_stream( "/dev/rfcomm0" );

using std::vector;
vector<vector<vector<vector<int>>>> array4D;

int main()
{
    load_all_values();
    //using namespace std::this_thread; // sleep_for, sleep_until
    //using namespace std::chrono; // nanoseconds, system_clock, seconds

   // std::cout << "Port is connected" << std::endl;

    delay(3);


    major_task(8,1,5,3);

//   major_task(3,2,5,3);
/*    delay(4);
    go_down(5,5);

    my_serial_stream<<releasing_character;
    delay(3);
    hover_the_box(6,5);
    delay(4);
    go_down(6,5);
*/
    //  FOR DISPLAYING THE CONTENTS OF LINES
    /* for(int i=0;i<16;i++)
   {
       for(int j=0;j<3;j++)
       {
           std::cout<<line_1[i][j]<<"\t";

       }
       std::cout<<"\n";
   }*/
    //  FOR DISPLAYING THE CONTENTS OF ARRAY4D
    /*  for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            for (int k = 0; k < DEPTH2; k++)
            {
                for (int l = 0; l < DEPTH1; l++)
                {
                    std::cout << "[";
                    std::cout << array4D[i][j][l][k];
                    std::cout << "] ";
                }
            }
            std::cout << "\t";
        }
        std::cout << "\n";
    }*/

    my_serial_stream.Close();

    return 0;
}

void delay(int time_in_sec)
{
    std::this_thread::sleep_for(std::chrono::nanoseconds(10));
    std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(time_in_sec));

}
void wait(void)
{
    received_character = 0;
	do
	{
		my_serial_stream>>received_character;
        std::cout<<received_character<<std::endl;
	}	while(received_character!='1');
	
}

void hover_the_box(int row, int column)
{
    q1 = array4D[row-1][column-1][0][0];
    q2 = array4D[row-1][column-1][1][0];
    pos = array4D[row-1][column-1][2][0];
     my_serial_stream<<q1<<ending_character<<q2<<ending_character<<pos<<ending_character;
   wait();
    
}

void go_down(int row, int column)
{
    q1 = array4D[row-1][column-1][0][1];
    q2 = array4D[row-1][column-1][1][1];
    pos = array4D[row-1][column-1][2][1];

     my_serial_stream<<q1<<ending_character<<q2<<ending_character<<pos<<ending_character;
     wait();

    // my_serial_stream<<releasing_character;
}

void major_task(int from_row,int from_col,int to_row,int to_col)
{
    int r1 = from_row,c1 = from_col,r2 = to_row,c2 = to_col;
    hover_the_box(r1,c1);
    my_serial_stream<<releasing_character;
    delay(1);
    go_down(r1,c1);
    my_serial_stream<<grabbing_character;
    delay(1);
    hover_the_box(r1,c1);
    hover_the_box(r2,c2);
    go_down(r2,c2);
    delay(1);
    my_serial_stream<<releasing_character;
    hover_the_box(r2,c2);

}

void load_all_values(void)
{
 //keep data for hovering first and then for task
    int line_1[16][3] = { {60,14,46} , {29,12,45},     
                       {62,26,37} , {25,7,36},
                        {50,26,24} , {22,3,24},
                        {49,26,10} , {17,5,10},
                        {47,26,-4} , {18,5,-4},
                        {48,23,-19} ,{17,8,-19},
                        {51,19,-31} , {22,10,-31},
                        {59,11,-43} , {29,12,-43}      
                         };

                    
int line_2[16][3] = {   {58,0,40} , {30,22,40},
                        {52,5,31} , {28,17,31},
                        {53,11,22} , {23,16,22},
                        {53,16,9} , {23,12,9},
                        {60,22,-5} , {20,13,-5},
                        {59,19,-15} , {24,14,-16},
                        {56,12,-26} , {24,17,-26},
                        {58,6,-37} , {27,21,-37}
                    };

int line_3[16][3] = { {51,14,35} , {33,29,34},
                        {52,7,27} , {31,25,27},
                        {51,3,19} , {28,23,19},
                        {50,1,8} , {28,21,8},
                        {55,2,-3} , {28,20,-3},
                        {55,2,-13} , {29,22,-12},
                        {54,5,-22} , {30,24,-22},
                        {54,9,-29} , {34,26,-29}
                    };

int line_4[16][3] = { {62,19,32} , {38,36,31},
                        {62,11,26} , {35,33,25},
                        {68,5,19} , {33,31,17},
                        {71,1,11} , {32,30,9},
                        {68,3,3} , {32,29,0},
                        {70,0,-4} , {33,30,-10},
                        {73,2,-11} , {35,33,-17},
                        {72,12,-21} , {38,35,-24}
                    };

int line_5[16][3] = { {68,26,29} , {45,44,29},
                        {68,20,25} , {42,41,23},
                        {65,20,16} , {40,38,15},
                        {72,20,10} , {40,37,8},
                        {65,17,2} , {39,37,0},
                        {65,16,-5} , {39,37,-6},
                        {62,20,-11} , {42,40,-14},
                        {75,23,-15} , {44,42,-19}
                    };

int line_6[16][3] = { {73,38,26} , {53,52,26},
                        {70,30,22} , {50,49,20},
                        {70,24,17} , {48,47,15},
                        {70,27,9} , {47,45,8},
                        {73,26,4} , {47,45,2},
                        {66,30,-3} , {48,46,-5},
                        {70,26,-9} , {50,48,-12},
                        {74,30,-15} , {53,51,-17}
                    };

int line_7[16][3] = { {77,48,23} , {61,58,23},
                        {76,46,18} , {61,55,18},
                        {74,44,13} , {59,53,13},
                        {72,43,6} , {59,53,6},
                        {71,42,0} , {57,53,0},
                        {70,41,-6} , {58,52,-6},
                        {72,45,-12} , {59,56,-12},
                        {76,49,-18} , {63,59,-18}
                    };

int line_8[16][3] = { {84,69,21} , {73,73,21},
                        {83,64,16} , {71,69,16},
                        {82,61,12} , {68,67,12},
                        {79,58,5} , {66,65,5},
                        {80,56,0} , {68,64,0},
                        {83,56,-5} , {68,66,-5},
                        {83,66,-11} , {70,69,-11},
                        {84,68,-16} , {73,73,-16}
                    };
   

 // Set up sizes. (HEIGHT x WIDTH x DEPTH1 x DEPTH2)
     array4D.resize(HEIGHT);
    for (int i = 0; i < HEIGHT; ++i)
    {
        array4D[i].resize(WIDTH);

        for (int j = 0; j < WIDTH; ++j)
        {
            array4D[i][j].resize(DEPTH1);
            for (int k = 0; k < DEPTH1; ++k)
                array4D[i][j][k].resize(DEPTH2);
        }
    }

    //load all the values to 4D vector

    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            for (int k = 0; k < DEPTH2; k++)
            {
                for (int l = 0; l < DEPTH1; l++)
                {
                    if(i==0)
                      array4D[i][j][l][k] = line_1[(2*j)+k][l];
                      else if(i==1)
                      array4D[i][j][l][k] = line_2[(2*j)+k][l];
                      else if(i==2)
                      array4D[i][j][l][k] = line_3[(2*j)+k][l];
                      else if(i==3)
                      array4D[i][j][l][k] = line_4[(2*j)+k][l];
                      else if(i==4)
                      array4D[i][j][l][k] = line_5[(2*j)+k][l];
                      else if(i==5)
                      array4D[i][j][l][k] = line_6[(2*j)+k][l];
                      else if(i==6)
                      array4D[i][j][l][k] = line_7[(2*j)+k][l];
                      else if(i==7)
                      array4D[i][j][l][k] = line_8[(2*j)+k][l];
                }
            }
        }
    }
}