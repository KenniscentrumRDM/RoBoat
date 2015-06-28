#include <Servo.h>

#define ROER 2 //input 2
#define MAX_ANGLE 17 //maximum turn of the angle

Servo roer;

int angle;

void Rudder_Init(){
   //Activeer roer
  roer.attach( ROER );
  angle = 0;
}

/**
 * Manual control motor controller
 */
void Rudder_ManualControl(){
  if( !State_IsManual() )
    return;
  byte dir = RCD_Steering();
  if( RCD_Left() ){
    Rudder_Right();
  }else if ( RCD_Right() ){
     Rudder_Left();
  }else if ( RCD_Straight() ){
    Rudder_Straight(); //reset
  }
  roer.write( MAX_ANGLE + angle );
}

void Rudder_Right(){
  if( angle < MAX_ANGLE )
     angle++;
  roer.write( MAX_ANGLE + angle );
}

void Rudder_Left(){
  if( angle > 0 )
     angle--;
  roer.write( MAX_ANGLE + angle );
}

void Rudder_Straight(){
  roer.write( MAX_ANGLE );  
}

void Rudder_Manual(){
    //roer.write(angle);
  //angle++;
  //angle = angle % 35;
  //delay(1000);
  //LedAansturing_OnBoard( LOW );  
}

