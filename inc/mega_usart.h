#ifndef MEGA_USART_H
#define MEGA_USART_H

#include <avr/io.h>
#include <avr/interrupt.h>

class MegaUSART {
public:
    MegaUSART(uint8_t _usartNumber, uint32_t _baudRate);
    void mega_usart_init();
    void mega_transmit_char(char c);
    void mega_transmit_string(const char* str);
    char mega_receive_char();
    void enable_rx_interrupt();
    void disable_rx_interrupt();

private:
    uint8_t usartNumber;
    uint32_t baudRate;
};

#endif // MEGA_USART_H
