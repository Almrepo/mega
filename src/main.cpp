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

// прерывание по завершению приема. срабатывает, когда в буфер приема данных
// поступает новый символ.(есть непрочитанный символ)
ISR(USART0_RX_vect) {      
  
  //rx_data= UDR0;
  
 }

 // прерывание по завершению передачи.  срабатывает, когда буфер передачи данных и сдвиговый регистр данных пуст 
ISR(USART0_TX_vect) {  
    // static uint8_t i = 0;
    // static char str[] = "0123456789";
    // if (i < sizeof(str)-1) {
    //     UDR0 = str[i++]; // передаем символ
    // }
}

 // прерывание при очистке регистра данных. срабатывает, когда буфер передачи данных пуст(после пересылки байта из регистра данных UDR0 в сдвиговый регистр)
 ISR(USART0_UDRE_vect) {
    // static uint8_t i = 0;
    // static char str[] = "0123456789";
    // if (i < sizeof(str)-1) {
    //     UDR0 = str[i++]; // передаем символ
    // }
 }
