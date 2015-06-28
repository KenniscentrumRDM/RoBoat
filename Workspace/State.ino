#define BLOCK_BLINK 5
#define AUTO_BLINK 10

#define BLOCK_TIME 80

enum State{
   MANUAL,
   BLOCKED,
   AUTONOMOUS  
};
static State state = MANUAL;

enum Control{
  INIT,
  START,
  COMPLETED  
};
static Control control;

static int counter;
static int downKeyTeller = 0;

void State_Init(){
  state = MANUAL;
  control = INIT;
  counter = 0;
}

/**
 * Update the RC through the timer interrupt
 */
static State prevState;
void State_Update(){
  counter++;
  downKeyTeller++;
  switch( control ){
    case INIT:
      if( RCP_Down()){
        downKeyTeller = 0;
        prevState = state;
        state = BLOCKED;
        control = START;
      }
      break;
    case START:
      if( downKeyTeller > BLOCK_TIME ){
        state = prevState;
        downKeyTeller = 0;
        control = COMPLETED;
        break;
      }
      if( RCP_Up() ){
        switch( prevState ){
          case MANUAL:
             state = AUTONOMOUS;
             break;
          case AUTONOMOUS:
            state = MANUAL;
            break;
         }
         control = COMPLETED;
      }
       break;
    default:
      if( !RCP_Down())
        control = INIT;
      break;
  }
}

/**
 * Control the state
 */
void State_Control(){
  switch( state  ){
    case MANUAL:
      Motor_ManualControl();
      Rudder_ManualControl();
      break;
    case AUTONOMOUS:
      Autonomous_Motion();
      break;
    default:
      break;
  }
}

byte State_GetState(){
  return state;
}

boolean State_IsBlocked(){
  return state == BLOCKED;
}

boolean State_IsManual(){
  return state == MANUAL;
}

boolean State_IsAutonomous(){
  return state == AUTONOMOUS;
}

