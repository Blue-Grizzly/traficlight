#include <avr/io.h>
#include <avr/interrupt.h>
#include "./include/trafficlight.h"

void timer1_init() {
  // Set Timer1 to CTC mode
  TCCR1B |= (1 << WGM12);
  // Set prescaler to 64
  TCCR1B |= (1 << CS11) | (1 << CS10);
  
  TIMSK1 |= (1 << OCIE1A);

  OCR1A = LONG_PAUSE; // 15624 per 1 second delay with 16MHz clock and prescaler 64 (Based on the formula: OCR1A = (16*10^6) / (64*1) - 1. And a prayer to the omnissiah)
}

void timer1_start() {
  TCNT1 = 0;
  TCCR1B |= (1 << CS11) | (1 << CS10); // Start timer with prescaler 64
}

void timer1_stop() {
  TCCR1B &= ~((1 << CS11) | (1 << CS10)); 
}


void delay(long int amount) {
  timer1_init();
  timer1_start();
  
  while (amount > 0) {
    if (PINB & NS_BUTTON && !(PORTD & NS_GREEN) && amount == LONG_PAUSE) {
      NS_BUTTON_LED_ON;
      amount = SHORT_PAUSE;
    } else if (PORTD & NS_GREEN) {
      NS_BUTTON_LED_OFF;
    }
    
    if (PINB & EW_BUTTON && !(PORTD & EW_GREEN) && amount == LONG_PAUSE) {
      EW_BUTTON_LED_ON;
      amount = SHORT_PAUSE;
    } else if (PORTD & EW_GREEN) {
      EW_BUTTON_LED_OFF;
    }
    
    // Wait for timer overflow or compare match
    while (!(TIFR1 & (1 << OCF1A)));
    TIFR1 |= (1 << OCF1A); // Clear the compare match flag
    amount--;
  }
  
  timer1_stop();
}

void cycle_red(int dir) {
  if(dir == EW_DIR){
    EW_GREEN_OFF;          
    EW_YELLOW_ON;          
    delay(SHORT_PAUSE);    
    EW_YELLOW_OFF;         
    EW_RED_ON;
  } else {
    NS_GREEN_OFF;          
    NS_YELLOW_ON;          
    delay(SHORT_PAUSE);    
    NS_YELLOW_OFF;         
    NS_RED_ON;
  }
}

void cycle_green(int dir) {
  if(dir == EW_DIR){
    EW_YELLOW_ON;            
    delay(SHORT_PAUSE);      
    EW_RED_OFF;              
    EW_YELLOW_OFF;           
    EW_GREEN_ON;
  } else {
    NS_YELLOW_ON;            
    delay(SHORT_PAUSE);      
    NS_RED_OFF;              
    NS_YELLOW_OFF;           
    NS_GREEN_ON;
  }
}

int main(){
  SETUP();
  while (1) {
    delay(LONG_PAUSE);
    
    cycle_red(EW_DIR);
    
    delay(SHORT_PAUSE);
    
    cycle_green(NS_DIR);

    delay(LONG_PAUSE);

    cycle_red(NS_DIR);
    
    delay(SHORT_PAUSE);
    
    cycle_green(EW_DIR);
  }
  return 0;
}