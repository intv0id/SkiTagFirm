#ifndef BUZZER_H
#define BUZZER_H

#include "pico/stdlib.h"

class Buzzer {
public:
    Buzzer(uint pin);
    void on();
    void off();
    void beep(uint32_t duration_ms);

private:
    uint _pin;
};

#endif // BUZZER_H
