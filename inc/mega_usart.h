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
    char* mega_receive_string(char* buffer, uint8_t size);
    void enable_rx_interrupt();
    void disable_rx_interrupt();
    bool mega_rx_data_is_ready();
    void clear_rx_interrupt_flag();
    void clear_tx_interrupt_flag();

private:
    uint8_t usartNumber;
    uint32_t baudRate;
};

#endif // MEGA_USART_H
