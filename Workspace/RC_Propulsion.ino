#define IN_UP 8
#define IN_DOWN 7

#define MAX_PULSE 40

enum Direction{
  STOP = 0,
  FORWARD = 1,
  BACKWARD = 2
};

static Direction direction = STOP;

static int directionTimer = 0;

void RCP_Init(){
  pinMode( IN_UP, INPUT );
  pinMode( IN_DOWN, INPUT );
}

/**
 * Update the RC through the timer
 */
void RCP_Update(){
  directionTimer++;
}

boolean RCP_Up(){ 
  return digitalRead( IN_UP );
}

boolean RCP_Down(){ 
  return digitalRead( IN_DOWN );
}

int RCP_Direction(){
  if( RCP_Up()){
    direction = FORWARD;
    directionTimer = 0;
  } else if( RCP_Down() ){
    direction = BACKWARD;
    directionTimer = 0;
  }
  else{
    if( directionTimer > MAX_PULSE ){
      direction = STOP;
      directionTimer = 0;
    }
  }
  return direction;
}

/**
 * Returns true if the direction should be forward
 */
boolean RCP_Forward(){
  return ( direction == FORWARD );
}

/**
 * Returns true if the direction should be backward
 */
boolean RCP_Backward(){
  return ( direction == BACKWARD );
}

/**
 * Returns true if the direction should be forward
 */
boolean RCP_Stop(){
  return ( direction == STOP );
}
