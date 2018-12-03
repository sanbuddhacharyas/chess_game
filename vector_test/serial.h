

#ifndef _serial_
#define _serial_

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


/*************FUNCTION PROTOTYPES***************************/
 
class ser
{
    private:   
       
        double count = 0;
        int q1 = 50, q2 = 20, pos = -15;
        char ending_character = '.';
        char grabbing_character = 'g';
        char releasing_character = 'r';
        char received_character;

    public:
        
        void  hover_the_box(int row, int column);
        void go_down(int row, int column);
        void major_task(int from_row,int from_col,int to_row,int to_col);       //pick from one box & drop to another
        void wait(void);
        void load_all_values(void);
        void delay(int time_in_sec);

};
   


#endif