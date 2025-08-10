#include "buzzer.h"
#include "pico/stdlib.h"

Buzzer::Buzzer(uint pin) : _pin(pin) {
    gpio_init(_pin);
    gpio_set_dir(_pin, GPIO_OUT);
}

void Buzzer::on() {
    gpio_put(_pin, 1);
}

void Buzzer::off() {
    gpio_put(_pin, 0);
}

void Buzzer::beep(uint32_t duration_ms) {
    on();
    sleep_ms(duration_ms);
    off();
}
