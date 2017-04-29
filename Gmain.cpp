/* =======================================
Main function of the Gesture  
Procedures::
1- Calling intiallize Fn. 
2- Calling Getdata Fn. 
3- Calling Action Fn. (Not finished yet)  
==========================================
*/
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "Glib.h"
using namespace std;

int main(int argc, char const *argv[])
{	//intializing Fn;
	Gsetup();
    usleep(100000);
    while(1)
    //Getdata Fn
        Gdata();

    return 0;
}


