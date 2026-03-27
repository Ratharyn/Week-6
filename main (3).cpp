//=====[Libraries]=============================================================

#include "smart_home_system.h"

#include "mbed.h"
#include "arm_book_lib.h"

#include "code.h"

#include "user_interface.h"
#include "pc_serial_com.h"
#include "date_and_time.h"
#include "temperature_sensor.h"
#include "gas_sensor.h"
#include "matrix_keypad.h"


#include "date_and_time.h"

#include "display.h"

#include "user_interface.h"

#include "mbed.h"
#include "arm_book_lib.h"

#include "user_interface.h"



//=====[Main function, the program entry point after power on or reset]========


// new variables for system unlocking

bool unlocked = false; 
char codeinput[5]; 
char unlockcode[5] = {'1', '5', '8', '0', '6'}; 
int howmanykeyspressed = 0; 


int main()
{
    smartHomeSystemInit();

    displayCharPositionWrite( 0,0 ); 
    displayStringWrite( "    ENTER CODE      " );
    displayCharPositionWrite( 0,1 ); 
    displayStringWrite( "TO INITIALISE SYSTEM" );
    displayCharPositionWrite( 0,2 ); 
    displayStringWrite( "                    " ); 
    displayCharPositionWrite( 0,3 ); 
    displayStringWrite( "                    " ); 

    while (!unlocked) { 
        char keypad = matrixKeypadUpdate(); 
        
        if (keypad != '\0'){ 
            codeinput[howmanykeyspressed] = keypad;
            displayCharPositionWrite( 7 + howmanykeyspressed, 2 );
            displayStringWrite( "*" );
            howmanykeyspressed++; 

            if (howmanykeyspressed == 5){ 
                unlocked = true; 
                for (int i = 0; i < 5; i++){ 
                    if (codeinput[i] != unlockcode[i]){
                        unlocked = false;
                    }
                }

                if (!unlocked){
                    howmanykeyspressed = 0; 
                    displayCharPositionWrite( 0, 2 ); 
                    displayStringWrite( "                    " );
                }
            }
        }
    
        delay(10); 
    }
    displayCharPositionWrite( 0,0 ); displayStringWrite( "                    " );
    displayCharPositionWrite( 0,1 ); displayStringWrite( "                    " );
    displayCharPositionWrite( 0,2 ); displayStringWrite( "                    " );

    displayCharPositionWrite( 0,0 ); 
    displayStringWrite( "Temperature: " );
    displayCharPositionWrite( 0,1 ); 
    displayStringWrite( "Gas: " );
    displayCharPositionWrite( 0,2 ); 
    displayStringWrite( "Alarm: " );

    while (true) {
        smartHomeSystemUpdate();    
    }
}