#ifndef MEGA_SPI_H
#define MEGA_SPI_H

#include <avr/io.h>
#include <avr/interrupt.h>

class MegaSPI {
public:
    MegaSPI();
    void mega_spi_init();
    void mega_spi_transfer(uint8_t data);
    uint8_t mega_spi_receive();
    void enable_spi_interrupts();
    void disable_spi_interrupts();

private:
    void spi_select_device();
    void spi_deselect_device();
};

#endif // MEGA_SPI_H
