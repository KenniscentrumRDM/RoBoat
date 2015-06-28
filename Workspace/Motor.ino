#define MOTOR 3
#define MOTOR_RICHTING 12

static int fade = 0;

void Motor_Init(){
  pinMode( MOTOR, OUTPUT);  //Set control pins to be outputs
  pinMode( MOTOR_RICHTING, OUTPUT);
  //analogWrite(MOTOR, 100);  //set both motors to run at (100/255 = 39)% duty cycle (slow)
}

/**
 * Manual control motor controller
 */
static byte mdir = 0;
void Motor_ManualControl(){
  if( !State_IsManual() )
    return;
  byte dir = RCP_Direction();
  if( RCP_Forward() ){
      if( dir != mdir ){
        forw();         //Set Motors to go forward Note : No pwm is defined with the for function, so that fade in and out works
        fadein();       //fade in from 0-255
      }
      forward();      //continue full speed forward
  }else if ( RCP_Backward() ){
     if( dir != mdir ){
       back();         //Set motors to revers. Note : No pwm is defined with the back function, so that fade in and out works
       fadein();       //fade in from 0-255 
     }
    backward();     //full speed backward
  }else if ( RCP_Stop() ){
    stopped();      // stop for 2 seconds
  }
  mdir = dir;
  //Serial.print( dir );
}

/* Let's take a moment to talk about these functions. The forw and back functions are simply designating the direction the motors will turn once they are fed a PWM signal.
If you only call the forw, or back functions, you will not see the motors turn. On a similar note the fade in and out functions will only change PWM, so you need to consider
the direction you were last set to. In the code above, you might have noticed that I called forw and fade in the same grouping. You will want to call a new direction, and then
declare your pwm fade. There is also a stop function. 
*/

void forw() // no pwm defined
{ 
  digitalWrite(MOTOR_RICHTING, HIGH);  //Reverse motor direction, 1 high, 2 low
}

void back() // no pwm defined
{
  digitalWrite(MOTOR_RICHTING, LOW);  //Set motor direction, 1 low, 2 high
}

void forward() //full speed forward
{ 
  digitalWrite(MOTOR_RICHTING, HIGH);  //Reverse motor direction, 1 high, 2 low
  analogWrite(MOTOR, 255);    //set both motors to run at (100/255 = 39)% duty cycle
}

void backward() //full speed backward
{
  digitalWrite(MOTOR_RICHTING, LOW);  //Set motor direction, 1 low, 2 high
  analogWrite(MOTOR, 255);   //set both motors to run at 100% duty cycle (fast)
}

void stopped() //stop
{ 
  digitalWrite(MOTOR_RICHTING, LOW); //Set motor direction, 1 low, 2 high
  analogWrite(MOTOR, 0);    //set both motors to run at 100% duty cycle (fast)
}

void fadein()
{ 
  // fade in from min to max in increments of 5 points:
  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=5) 
  { 
     // sets the value (range from 0 to 255):
    analogWrite(MOTOR, fadeValue);   
    // wait for 30 milliseconds to see the dimming effect    
    delay(30);                            
  } 
}

void fadeout()
{ 
  // fade out from max to min in increments of 5 points:
  for(int fadeValue = 255 ; fadeValue >= 0; fadeValue -=5) 
  { 
    // sets the value (range from 0 to 255):
    analogWrite(MOTOR, fadeValue);
    // wait for 30 milliseconds to see the dimming effect    
    delay(30);  
}
}

void astop()                   //stop motor A
{
  analogWrite(MOTOR, 0);    //set both motors to run at 100% duty cycle (fast)
}
