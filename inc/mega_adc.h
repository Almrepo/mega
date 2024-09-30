//Необходимо добавить тип контроллера для настройки режима работы АЦП
#ifndef MEGA_ADC_H
#define MEGA_ADC_H
//#define __AVR_ATmega128__
#include <avr/io.h>
#include <avr/interrupt.h>

class MegaADC {
public:
enum ADCReference {    
    Aref = 0,                                //источник опорного напряжения подключеный к AREF
    AVcc = (1 << REFS0),                    //источник опорного напряжения равный питанию контроллера
    //Internal = (1 << REFS1),             //Резерв
    InternalVCC = (1 << REFS0) | (1 << REFS1) //Внутренний источник опорного напряжения 2.56В
};

enum ADCPrescaler {
    Div2 = (1 << ADPS0),
    Div4 = (1 << ADPS1),
    Div8 = (1 << ADPS0) | (1 << ADPS1),
    Div16 = (1 << ADPS2),
    Div32 = (1 << ADPS0) | (1 << ADPS2),
    Div64 = (1 << ADPS1) | (1 << ADPS2),
    Div128 = (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2)
};
    // Конструктор с инициализацией
  MegaADC(uint8_t channel, ADCReference reference , ADCPrescaler prescaler );


   
    void mega_adc_init(ADCReference reference, ADCPrescaler prescaler);
    void mega_adc_start_conversion();
    uint16_t mega_adc_read_result();
    uint16_t mega_adc_auto_read(uint8_t channel);
    uint16_t mega_adc_manual_read(uint8_t channel); 
    void enable_adc_interrupts();
    void disable_adc_interrupts();
    void enable_adc_auto_mode();
    void disable_adc_auto_mode();
   static volatile uint16_t adcValue; // Для хранения значения АЦП

private:
    void mega_adc_select_channel(uint8_t channel);
    // Номер канала ADC
  uint8_t _channel;
  // Напряжение опорного сигнала
  ADCReference _reference;
  // Предделитель
  ADCPrescaler _prescaler;
};

#endif // MEGA_ADC_H
