#define LED_TOP 5 //Output PortD pin 5

/**
 * Initialise the Top LED
 */
void TopLed_Init(){
  pinMode( LED_TOP, OUTPUT);
}

/**
 * Update the top led through the timer interrupt
 */
static boolean led_on = false;
void TopLed_Update(){
  byte status = State_GetState();
  switch( status ){
    case AUTONOMOUS:
      if(( counter % AUTO_BLINK ) == 0 ) 
        led_on = !led_on;
     break;
    case BLOCKED:
      if(( counter % BLOCK_BLINK ) == 0) 
        led_on = !led_on;
      break;
    default:
      led_on = true; 
  }
  TopLed_Out( led_on );
}

byte TopLed_TOP(){
  return LED_TOP;
}

void TopLed_Out( boolean signaal ){
   digitalWrite( LED_TOP, signaal );
}
