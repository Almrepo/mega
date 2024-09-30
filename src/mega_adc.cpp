#include "mega_adc.h"

volatile uint16_t MegaADC::adcValue = 0;

// Конструктор класса MegaADC с инициализацией

MegaADC::MegaADC(uint8_t channel, ADCReference reference, ADCPrescaler prescaler) :
  _channel(channel), _reference(reference), _prescaler(prescaler) {

  // Настройка АЦП при создании объекта
  mega_adc_init(_reference, _prescaler);
}


void MegaADC::mega_adc_init(ADCReference reference, ADCPrescaler prescaler) {
   ADMUX = (reference) | (_channel << MUX0);  // Выбор канала и опорного напряжения
  ADCSRA = (prescaler) | (1 << ADEN); // Включение АЦП, установка предделителя
}

   
void MegaADC::enable_adc_auto_mode() {
    // Включение автоматического запуска преобразования после завершения
    #if defined(__AVR_ATmega8__) || defined(__AVR_ATmega128__)
      ADCSRA |= (1 << ADFR); // В ATmega8 и ATmega128 бит ADFR 
    #else 
      ADCSRA |= (1 << ADATE); // В остальных микроконтроллерах бит ADATE 
    #endif
  }
   // Отключение непрерывного режима
  void MegaADC::disable_adc_auto_mode() {
    // Отключение автоматического запуска преобразования после завершения
    #if defined(__AVR_ATmega8__) || defined(__AVR_ATmega128__)
      ADCSRA &= ~(1 << ADFR); // В ATmega8 и ATmega128 бит ADFR 
    #else 
      ADCSRA &= ~(1 << ADATE); // В остальных микроконтроллерах бит ADATE 
    #endif
  }
  // Запуск преобразования АЦП
void MegaADC::mega_adc_start_conversion() {
  // Запуск преобразования
  ADCSRA |= (1 << ADSC); // Установка бита ADSC
}
// Получение результата преобразования
uint16_t MegaADC::mega_adc_read_result() {
  // Ожидание завершения преобразования
  while (!(ADCSRA & (1 << ADIF))); // Ожидание установки бита ADIF 

  // Сброс флага завершения преобразования
  ADCSRA |= (1 << ADIF); // Сброс бита ADIF

  // Возвращение результата преобразования
  return ADC; // Возвращение значения из регистра ADC
}
uint16_t MegaADC::mega_adc_manual_read(uint8_t channel) {
    mega_adc_select_channel(channel);
    mega_adc_start_conversion();
    return mega_adc_read_result();
}
uint16_t MegaADC::mega_adc_auto_read(uint8_t channel) {
    mega_adc_select_channel(channel);
    enable_adc_auto_mode();
    while (!(ADCSRA & (1 << ADIF))); // Ожидание завершения преобразования
    return ADC; // Возвращаем результат преобразования
}
void MegaADC::mega_adc_select_channel(uint8_t channel) {
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
