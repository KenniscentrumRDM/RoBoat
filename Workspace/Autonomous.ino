enum Steps{
   ST_REST = 0,
   ST_FORWARD = 5,
   ST_TURN = 10,
   ST_BACK = 15  
};

static int step = ST_REST;

void Autonomous_Init(){
  step = ST_REST;
}

void Autonomous_Update(){
  step++;
}

void Autonomous_Motion(){
  if( !State_IsAutonomous() )
    return;
  switch( step ){
    case ST_REST:
      break;
    case ST_FORWARD:
      fadein();
      forw();
      break;
    case ST_TURN:
      Rudder_Right();
      forw();
      break;
    case ST_BACK:
      forw();
      fadeout();
      break;
    default:
      break;
  }
}
