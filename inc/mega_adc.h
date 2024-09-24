#ifndef MEGA_ADC_H
#define MEGA_ADC_H

#include <avr/io.h>
#include <avr/interrupt.h>

class MegaADC {
public:
    MegaADC();
    void mega_adc_init();
    uint16_t mega_adc_read(uint8_t channel);
    void enable_adc_interrupts();
    void disable_adc_interrupts();
    
    static volatile uint16_t adcValue; // Для хранения значения АЦП

private:
    void select_adc_channel(uint8_t channel);
};

#endif // MEGA_ADC_H
