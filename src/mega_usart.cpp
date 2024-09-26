#include "mega_usart.h"

MegaUSART::MegaUSART(uint8_t _usartNumber, uint32_t _baudRate) 
    : usartNumber(_usartNumber), baudRate(_baudRate) {
    mega_usart_init();
}

void MegaUSART::mega_usart_init() {
    uint16_t ubrr = F_CPU / 16 / baudRate - 1;

    switch (usartNumber) {
        case 0:
            UCSR0B = (1 << RXEN0) | (1 << TXEN0); // Включаем приемник и передатчик
            UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8 бит данных, 1 стоп-бит, без четности
            UBRR0H = (ubrr >> 8);
            UBRR0L = ubrr;
            break;
        case 1:
            UCSR1B = (1 << RXEN1) | (1 << TXEN1);
            UCSR1C = (1 << UCSZ11) | (1 << UCSZ10);
            UBRR1H = (ubrr >> 8);
            UBRR1L = ubrr;
            break;
        // case 2:
        //     UCSR2B = (1 << RXEN2) | (1 << TXEN2);
        //     UCSR2C = (1 << UCSZ21) | (1 << UCSZ20);
        //     UBRR2H = (ubrr >> 8);
        //     UBRR2L = ubrr;
        //     break;
        // case 3:
        //     UCSR3B = (1 << RXEN3) | (1 << TXEN3);
        //     UCSR3C = (1 << UCSZ31) | (1 << UCSZ30);
        //     UBRR3H = (ubrr >> 8);
        //     UBRR3L = ubrr;
        //     break;
         default:
            // Обработка некорректного номера USART
             break;
    }
}

void MegaUSART::mega_transmit_char(char c) {
    switch (usartNumber) {
        case 0:
            while (!(UCSR0A & (1 << UDRE0)));
            UDR0 = c;
            break;
        case 1:
            while (!(UCSR1A & (1 << UDRE1)));
            UDR1 = c;
            break;
        // case 2:
        //     while (!(UCSR2A & (1 << UDRE2)));
        //     UDR2 = c;
        //     break;
        // case 3:
        //     while (!(UCSR3A & (1 << UDRE3)));
        //     UDR3 = c;
        //     break;
    }
}

void MegaUSART::mega_transmit_string(const char* str) {
    
    while (*str != '\0') {
        mega_transmit_char(*str); // Передаем каждый символ
        str++; // Переходим к следующему символу
    }
}


char MegaUSART::mega_receive_char() {
    switch (usartNumber) {
        case 0:
            while (!(UCSR0A & (1 << RXC0)));
            return UDR0;
        case 1:
            while (!(UCSR1A & (1 << RXC1)));
            return UDR1;
        // case 2:
        //     while (!(UCSR2A & (1 << RXC2)));
        //     return UDR2;
        // case 3:
        //     while (!(UCSR3A & (1 << RXC3)));
        //     return UDR3;
        default:
            return '\0';
    }
}

// Функция приема строки
// Возвращает указатель на буфер, если он не равен NULL,
// иначе - NULL
// size - максимальное количество символов, которое может быть принято
// (не учитывая символы конца строки)
// buffer - указатель на буфер, в который будет принята строка
// Функция может быть прервана, если будет получен символ конца строки (\n или \r)
/////////////example////////////////////////
//char buffer[100];
//mega_receive_string(buffer, sizeof(buffer));
////////////////////////////////////////////
char* MegaUSART::mega_receive_string(char* buffer, uint8_t size) {
    uint8_t i = 0;
    while (i < size - 1 && mega_rx_data_is_ready()) {
        // получаем символ
        char c = mega_receive_char();
        // если это символ конца строки, то выходим из цикла
        if (c == '\n' || c == '\r') break;
        // иначе, добавляем символ в буфер
        buffer[i] = c;
        i++;
    }
    // добавляем символ конца строки
    buffer[i] = '\0';
    // возвращаем указатель на буфер, если он не равен NULL
    return buffer;
}

void MegaUSART::enable_rx_interrupt() {
    switch (usartNumber) {
        case 0:
            UCSR0B |= (1 << RXCIE0); // Включаем прерывание по приему
            break;
        case 1:
            UCSR1B |= (1 << RXCIE1);
            break;
        // case 2:
        //     UCSR2B |= (1 << RXCIE2);
        //     break;
        // case 3:
        //     UCSR3B |= (1 << RXCIE3);
            break;
    }
}

void MegaUSART::disable_rx_interrupt() {
    switch (usartNumber) {
        case 0:
            UCSR0B &= ~(1 << RXCIE0); // Отключаем прерывание по приему
            break;
        case 1:
            UCSR1B &= ~(1 << RXCIE1);
            break;
        // case 2:
        //     UCSR2B &= ~(1 << RXCIE2);
        //     break;
        // case 3:
        //     UCSR3B &= ~(1 << RXCIE3);
        //     break;
    }
}

// Прерывание по приему данных
// ISR(USART_RX_vect) {
//     // Передаем полученный символ в обработчик
//     // Здесь можно вызвать метод onReceive() соответствующего экземпляра класса
// }

// Проверка готовности приема данных
// Возвращает true, если есть новый символ в регистре UDR0
bool MegaUSART::mega_rx_data_is_ready() {

    return(UCSR0A & (1 << RXC0));
}
void MegaUSART::clear_rx_interrupt_flag() {
    UCSR0A &= ~(1 << RXC0);
}
void MegaUSART::clear_tx_interrupt_flag() {
    UCSR0A &= ~(1 << TXC0);
}