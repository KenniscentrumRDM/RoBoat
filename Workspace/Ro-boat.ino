//Global variabeles
unsigned int centis = 0; //centi- seconds
byte seconden = 0; //seconds
byte minuten = 0; //minutes
int alarm = 0;

void setup() {

   //Set up Radio Control
   RCP_Init();
   RCD_Init();
   State_Init();
   Autonomous_Init();
   
  //Initialise LEDS
  TopLed_Init();
  LedControl_Init();
  LedControl_Disco( HIGH );
  TopLed_Out( HIGH );  
  LedControl_OnBoard( HIGH );  

  //Let the LEDS blibk for a second
  delay(1000);
  
  TopLed_Out( LOW  );
  LedControl_Disco( LOW );  
  LedControl_OnBoard( LOW );  

  cli();//deactivate interrupts
  tmr0_init();
  sei();//Activate interrupts

//Initialise the motor and rudder control
  Motor_Init();
  Rudder_Init();
}

void loop() {
  State_Control();
  //LedControl_Disco( HIGH );
  delay(100);
}
