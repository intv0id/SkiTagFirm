#ifndef FIND_MY_H
#define FIND_MY_H

#include "pico/stdlib.h"
#include "nina_spi.h"

class FindMy {
public:
    FindMy(NINA_SPI &nina);
    bool init();
    void process();
    void update_orientation(float pitch, float roll);

private:
    bool start_advertising();
    bool set_device_name();
    bool add_service();
    bool add_beacon_actions_characteristic();
    bool add_orientation_characteristic();

    NINA_SPI &_nina;
};

#endif // FIND_MY_H
