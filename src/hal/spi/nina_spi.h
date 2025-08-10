#ifndef NINA_SPI_H
#define NINA_SPI_H

#include "pico/stdlib.h"
#include "hardware/spi.h"

#define NINA_SPI_BUFFER_SIZE 256

class NINA_SPI {
public:
    NINA_SPI(spi_inst_t *spi, uint miso_pin, uint mosi_pin, uint sck_pin, uint cs_pin);
    bool init();
    bool send_command(const char *command, char *response, uint32_t response_len, uint32_t timeout_ms = 1000);
    int read_response(char *buffer, uint32_t len, uint32_t timeout_ms = 1000);

private:
    void cs_select();
    void cs_deselect();
    bool wait_for_response(uint32_t timeout_ms);

    spi_inst_t *_spi;
    uint _cs_pin;
    char _rx_buffer[NINA_SPI_BUFFER_SIZE];
    volatile uint32_t _rx_buffer_pos;
};

#endif // NINA_SPI_H
