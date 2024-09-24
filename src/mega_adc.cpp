#include "mega_adc.h"

volatile uint16_t MegaADC::adcValue = 0;

MegaADC::MegaADC() {
    mega_adc_init();
}

void MegaADC::mega_adc_init() {
    ADMUX = (1 << REFS0); // Используем AVcc в качестве опорного напряжения
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Включаем АЦП и устанавливаем делитель
}

uint16_t MegaADC::mega_adc_read(uint8_t channel) {
    select_adc_channel(channel);
    ADCSRA |= (1 << ADSC); // Запускаем преобразование
    while (ADCSRA & (1 << ADSC)); // Ждем завершения преобразования
    return ADC; // Возвращаем результат
}

void MegaADC::select_adc_channel(uint8_t channel) {
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F); // Устанавливаем номер канала
}

void MegaADC::enable_adc_interrupts() {
    ADCSRA |= (1 << ADIE); // Включаем прерывание по завершению преобразования
}

void MegaADC::disable_adc_interrupts() {
    ADCSRA &= ~(1 << ADIE); // Отключаем прерывание
}

// Обработчик прерывания для АЦП
ISR(ADC_vect) {
    MegaADC::adcValue = ADC; // Сохраняем значение АЦП
}
