#include "serial.h"



//rfcomm0 is the required port for serial communication

LibSerial::SerialStream my_serial_stream("/dev/rfcomm0");
using std::vector;
vector<vector<vector<vector<int>>>> array4D;


void serial::delay(int time_in_sec)
{
    std::this_thread::sleep_for(std::chrono::nanoseconds(10));
    std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(time_in_sec));

}
void serial::wait(void)
{
    received_character = 0;
	do
	{
		my_serial_stream>>received_character;
        std::cout<<received_character<<std::endl;
	}	while(received_character!='1');
	
}

void serial::grab(void)
{
     my_serial_stream<<grabbing_character;
     delay(1);
}

void serial::release(void)
{
     my_serial_stream<<releasing_character;
     delay(1);
}

void serial::hover_the_box(int row, int column)
{
    q1 = array4D[row-1][column-1][0][0];
    q2 = array4D[row-1][column-1][1][0];
    pos = array4D[row-1][column-1][2][0];
     my_serial_stream<<q1<<ending_character<<q2<<ending_character<<pos<<ending_character;
   wait();
    
}

void serial::go_down(int row, int column)
{
    q1 = array4D[row-1][column-1][0][1];
    q2 = array4D[row-1][column-1][1][1];
    pos = array4D[row-1][column-1][2][1];

     my_serial_stream<<q1<<ending_character<<q2<<ending_character<<pos<<ending_character;
     wait();

    // my_serial_stream<<releasing_character;
}

void serial::go_home(void)
{
    q1 = 45;                //home position
    q2 = -20;
    pos = 55;
     my_serial_stream<<q1<<ending_character<<q2<<ending_character<<pos<<ending_character;
     wait();
}

void serial::major_task(int from_row,int from_col,int to_row,int to_col,char what_to_do)
{
    int r1 = from_row,c1 = from_col,r2 = to_row,c2 = to_col;
    if(what_to_do)
    {
    hover_the_box(r2,c2);
    release();
    go_down(r2,c2);
    grab();
    hover_the_box(r2,c2);
    go_home();
     release();
    hover_the_box(r1,c1);
    go_down(r1,c1);
    grab();
    hover_the_box(r1,c1);
    hover_the_box(r2,c2);
    go_down(r2,c2);
    release();
    hover_the_box(r2,c2);
    go_home();
    }
    else
    {
    hover_the_box(r1,c1);
    release();
    go_down(r1,c1);
    grab();
    hover_the_box(r1,c1);
    hover_the_box(r2,c2);
    go_down(r2,c2);
    release();
    hover_the_box(r2,c2);
    go_home();
    }

}

void serial::load_all_values(void)
{
 //keep data for hovering first and then for task
    int line_1[16][3] = { {40,5,50} , {22,24,50},     
                        {41,-4,42} , {14,20,42},
                        {45,-17,30} , {10,16,30},
                        {51,-25,13 }, {14,15,13},
                        {56,-25,-4} , {9,14,-4},
                        {49,-20,-20} ,{14,12,-20},
                        {42,-9,-34} , {14,17,-34},
                        {43,0,-44} , {22,17,-44}      
                         };

                    
int line_2[16][3] = {   {41,14,44} , {25,30,44},
                        {42,6,36} , {21,28,36},
                        {40,5,27} , {19,23,27},
                        {47,4,13} , {19,20,13},
                        {40,0,-1} , {17,21,-1},
                        {42,4,-13} , {20,21,-13},
                        {42,7,-24} , {19,27,-24},
                        {46,11,-33} , {23,27,-33}
                    };

int line_3[16][3] = { {48,19,39} , {29,35,39},
                        {45,15,33} , {24,34,33},
                        {47,10,22} , {23,30,22},
                        {45,6,13} , {22,27,13},
                        {41,9,1} , {24,27,1},
                        {40,13,-9} , {23,30,-9},
                        {46,12,-16} , {26,29,-16},
                        {46,11,-23} , {26,31,-23}
                    };

int line_4[16][3] = { {50,29,35} , {36,42,35},
                        {51,25,29} , {31,41,29},
                        {50,18,20} , {31,37,21},
                        {49,20,11} , {28,35,11},
                        {48,18,2} , {28,36,2},
                        {50,20,-7} , {32,35,-7},
                        {50,20,-14} , {31,36,-14},
                        {54,23,-23} , {34,41,-23}
                    };

int line_5[16][3] = { {60,36,32} , {43,49,32},
                        {54,31,26} , {40,45,26},
                        {54,26,18} , {36,41,18},
                        {52,29,10} , {34,42,10},
                        {51,28,4} , {35,42,4},
                        {55,31,-4} , {36,43,-4},
                        {52,31,-13} , {47,45,-13},
                        {58,31,-22} , {41,46,-19}
                    };

int line_6[16][3] = { {62,47,27} , {50,56,27},
                        {57,43,21} , {46,53,22},
                        {58,41,17} , {44,50,17},
                        {57,38,10} , {43,51,10},
                        {58,35,3} , {43,50,3},
                        {55,42,-4} , {44,51,-4},
                        {63,40,-11} , {44,53,-11},
                        {65,46,-18} , {49,57,-18}
                    };

int line_7[16][3] = { {69,53,27} , {54,63,27},
                        {66,52,21} , {52,61,21},
                        {64,49,15} , {50,60,15},
                        {64,44,9} , {52,60,9},
                        {64,45,3} , {50,59,3},
                        {68,48,-3} , {50,59,-3},
                        {67,50,-9} , {54,63,-9},
                        {75,57,-15} , {58,66,-15}
                    };

int line_8[16][3] = { {81,69,24} , {67,76,24},
                        {75,63,19} , {65,74,19},
                        {73,59,15} , {62,70,15},
                        {77,59,8} , {61,70,8},
                        {74,61,2} , {61,71,2},
                        {80,63,-3} , {61,70,-3},
                        {79,64,-8} , {65,73,-8},
                        {83,71,-13} , {69,74,-13}
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