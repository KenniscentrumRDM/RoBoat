#define LED_DISCO 6 //set up disco LED on pint 6
#define LED_ONBOARD 13 //On board LEd is pin 13

int wachttijd = 0;

void LedControl_Init(){
  pinMode( LED_DISCO, OUTPUT );
  pinMode( LED_ONBOARD, OUTPUT);
}

byte LedControl_Disco(){
  return LED_DISCO;
}

byte LedControl_OnBoard(){
  return LED_ONBOARD;
}

void LedControl_Disco( boolean signaal ){ 
  digitalWrite( LED_DISCO, signaal );
}

void LedControl_OnBoard( boolean signaal ){
   digitalWrite( LED_ONBOARD, signaal );
}
