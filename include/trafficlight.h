#ifndef TRAFFICLIGHT_H
#define BIT(pos) (1 << pos) // bit macro
#define EW_DIR 1
#define NS_DIR 0
#define PORTD *(unsigned char*)0x2B
#define PORT_DDRD *(unsigned char*)0x2A
#define PORTB *(unsigned char*)0x25
#define PINB *(unsigned char*)0x23
#define PORT_DDRB *(unsigned char*)0x24
#define LONG_PAUSE 100000000
#define SHORT_PAUSE 1000000
#define NS_GREEN (BIT(2))
#define EW_GREEN (BIT(5))
#define NS_YELLOW (BIT(3))
#define EW_YELLOW (BIT(6))
#define NS_RED (BIT(4))
#define EW_RED (BIT(7))
#define NS_BUTTON (BIT(2))
#define EW_BUTTON (BIT(3))
#define NS_BUTTON_LED (BIT(1))
#define EW_BUTTON_LED (BIT(0))
#define NS_GREEN_ON PORTD = PORTD | NS_GREEN
#define EW_GREEN_ON PORTD = PORTD | EW_GREEN
#define NS_YELLOW_ON PORTD = PORTD | NS_YELLOW
#define EW_YELLOW_ON PORTD = PORTD | EW_YELLOW
#define NS_RED_ON PORTD = PORTD | NS_RED
#define EW_RED_ON PORTD = PORTD | EW_RED
#define NS_BUTTON_LED_ON PORTB = PORTB | NS_BUTTON_LED
#define EW_BUTTON_LED_ON PORTB = PORTB | EW_BUTTON_LED
#define NS_BUTTON_LED_OFF PORTB = PORTB & ~NS_BUTTON_LED
#define EW_BUTTON_LED_OFF PORTB = PORTB & ~EW_BUTTON_LED
#define NS_GREEN_OFF PORTD = PORTD & ~NS_GREEN
#define EW_GREEN_OFF PORTD = PORTD & ~EW_GREEN
#define NS_YELLOW_OFF PORTD = PORTD & ~NS_YELLOW
#define EW_YELLOW_OFF PORTD = PORTD & ~EW_YELLOW
#define NS_RED_OFF PORTD = PORTD & ~NS_RED
#define EW_RED_OFF PORTD = PORTD & ~EW_RED
#define SETUP()                                                                  \
    PORT_DDRD |= NS_GREEN | EW_GREEN | NS_YELLOW | EW_YELLOW | NS_RED | EW_RED; \
    PORT_DDRB |= NS_BUTTON_LED | EW_BUTTON_LED;                                 \
    PORT_DDRB &= ~(NS_BUTTON | EW_BUTTON);                                      \
    NS_RED_ON;                                                                   \
    EW_GREEN_ON;
#endif