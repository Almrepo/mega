#include "mega_spi.h"

MegaSPI::MegaSPI() {
    mega_spi_init();
}

void MegaSPI::mega_spi_init() {
    DDRB |= (1 << PB3) | (1 << PB5); // MOSI и SCK
    DDRB &= ~(1 << PB4); // MISO

    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0); // Включаем SPI, режим Master, предделитель 16
}

void MegaSPI::mega_spi_transfer(uint8_t data) {
    spi_select_device(); // Выбираем устройство
    SPDR = data; // Записываем данные в регистр передачи
    while (!(SPSR & (1 << SPIF))); // Ждем завершения передачи
    spi_deselect_device(); // Отменяем выбор устройства
}

uint8_t MegaSPI::mega_spi_receive() {
    spi_select_device(); // Выбираем устройство
    SPDR = 0xFF; // Отправляем любой байт для генерации тактового сигнала
    while (!(SPSR & (1 << SPIF))); // Ждем завершения передачи
    uint8_t receivedData = SPDR; // Читаем полученные данные
    spi_deselect_device(); // Отменяем выбор устройства
    return receivedData;
}

void MegaSPI::spi_select_device() {
    PORTB &= ~(1 << PB2); // Предполагаем, что PB2 - это SS пин для выбора устройства
}

void MegaSPI::spi_deselect_device() {
    PORTB |= (1 << PB2); // Отменяем выбор устройства
}

// Обработчик прерывания для SPI (например, для передачи данных)
ISR(SPI_STC_vect) {
    // Здесь можно обработать данные, полученные через SPI, если нужно.
}
