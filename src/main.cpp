#include "main.h"
 MegaUSART usart0(0, 9600);
 char rx_data = '0';
 
int main () {

    sei();
   
    usart0.enable_rx_interrupt();

   
    while (1) {
       
       usart0.mega_transmit_string("Hello World!\r\n");
       _delay_ms(1000);
        usart0.mega_transmit_char(rx_data);
       usart0.mega_transmit_char('\n');
    }
    return 0;
}
ISR(USART0_RX_vect) {      
  
  rx_data= UDR0;
  
 }