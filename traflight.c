#define NS_GREEN 4
#define NS_YELLOW 8
#define NS_RED 16
#define EW_GREEN 32
#define EW_YELLOW 64
#define EW_RED 128

void setup()
{
  DDRD = NS_RED | EW_GREEN | EW_YELLOW | EW_RED | NS_GREEN | NS_YELLOW;
}

void loop()
{
         for (long i = 0; i < 100000; i++)
    {
    PORTD = NS_RED | EW_GREEN;
    }
    //delay
    for (long i = 0; i < 100000; i++)
    {
        PORTD = NS_YELLOW | NS_RED | EW_YELLOW;
    }

    for (long i = 0; i < 500000; i++)
    {
    PORTD = NS_GREEN | EW_RED;
    }

     for (long i = 0; i < 100000; i++)
    {
    PORTD = NS_YELLOW | EW_RED | EW_YELLOW;
    }
}