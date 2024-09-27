#ifndef MEGA_USART_H
#define MEGA_USART_H

#include <avr/io.h>
#include <avr/interrupt.h>

class MegaUSART {
public:
    MegaUSART(uint8_t _usartNumber, uint32_t _baudRate);
    void mega_usart_init();
    void mega_transmit_char(char c);
    void mega_transmit_string(char* str);
    char mega_receive_char();
    char* mega_receive_string(char* buffer, uint8_t size);
    void enable_tx_interrupt();
    void disable_tx_interrupt();
    void enable_rx_interrupt();
    void disable_rx_interrupt();
    void enable_tx_udre_is_empty_interrupt();
    void disable_tx_udre_is_empty_interrupt();
    bool mega_rx_buffer_is_ready();
    bool mega_tx_buffer_is_ready();
    void clear_rx_interrupt_flag();
    void clear_tx_interrupt_flag();

private:
    uint8_t usartNumber;
    uint32_t baudRate;
};

#endif // MEGA_USART_H
