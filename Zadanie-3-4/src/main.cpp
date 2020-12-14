#include <avr/io.h>
 int main()
 {
   DDRD&=!(1<<PD1);
   DDRD|=(1<<PD2);
   while(1)
   {
     if(!(PIND&(1<<PD1)))
       PORTD&=!(1<<PD2);
     else
       PORTD|=(1<<PD2);
   }
 }