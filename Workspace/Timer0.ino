//Constants
#define CMR_SECONDE 100 //optellen tot 10 om elke seconde over te lopen
#define CMR_MINUUT 5901 //optellen tot 609 om elke minuut over te lopen

static byte secondCounter = 0;        //De seconds counter
static unsigned int minuteCounter = 0; //De 16-bits minute counter

//Initialise timer 0;
void tmr0_init(){
  TCCR0A = 0;   // TCCR0A register = 0
  TCCR0B = 0;   // TCCR0B as well
  TCNT0  = 0;   // Reset the counter
  OCR0A = 156;  // CMR = 156
  TCCR0A |= (1 << WGM01); //CTC mode
  TCCR0B |= (1 << CS02) | (1 << CS00);//Prescaler = 1024   
  TIMSK0 |= (1 << OCIE0A); // Activate interrupt Timer 0
}

/**
 * Respond to an interrupt of timer 0
 */
ISR(TIMER0_COMPA_vect){//timer0 interrupt
  RCP_Update();
  RCD_Update();
  State_Update();
  TopLed_Update();
 
  centis++;
  secondCounter++; //count up every interrupt
  minuteCounter++; // count up every interrupt
  
  //Monitor_Puls();
  if( secondCounter == CMR_SECONDE ){
    Autonomous_Update();
    secondCounter = 0;
    seconden = ( ++seconden ) % 60;
  }
  if( minuteCounter == CMR_MINUUT ){
    minuteCounter = 0;
    minuten = ( ++minuten ) % 60;
  }
}
