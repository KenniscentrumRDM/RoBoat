#define IN_LEFT 9
#define IN_RIGHT 10

#define MAX_PULSE 40

enum Steering{
  STRAIGHT = 0,
  LEFT = 1,
  RIGHT = 2,
};
static Steering steering = STRAIGHT;

static int steeringTimer = 0;

void RCD_Init(){
  pinMode( IN_LEFT, INPUT );
  pinMode( IN_RIGHT, INPUT );
}

/**
 * Update the RC through the timer
 */
void RCD_Update(){
  steeringTimer++;  
}

boolean RCD_Left(){ 
  return digitalRead( IN_LEFT );
}

boolean RCD_Right(){ 
  return digitalRead( IN_RIGHT );
}

int RCD_Steering(){
  if( RCD_Left()){
    steering = LEFT;
    steeringTimer = 0;
  } else if( RCD_Right() ){
    steering = RIGHT;
    steeringTimer = 0;
  }
  else{
    if( steeringTimer > MAX_PULSE ){
      steering = STRAIGHT;
      steeringTimer = 0;
    }
  }
  return steering;
}

/**
 * Returns true if the direction should be forward
 */
boolean RCD_LeftTurn(){
  return ( steering == LEFT );
}

/**
 * Returns true if the direction should be backward
 */
boolean RCD_RightTurn(){
  return ( steering == RIGHT  );
}

/**
 * Returns true if the direction should be forward
 */
boolean RCD_Straight(){
  return ( steering == STRAIGHT );
}

