#include "nina_spi.h"
#include <string.h>
#include "pico/stdlib.h"

#define NINA_SPI_START_CMD 0x01
#define NINA_SPI_END_CMD   0xEE

NINA_SPI::NINA_SPI(spi_inst_t *spi, uint miso_pin, uint mosi_pin, uint sck_pin, uint cs_pin)
    : _spi(spi), _cs_pin(cs_pin), _rx_buffer_pos(0) {
    spi_init(_spi, 1000 * 1000); // 1MHz
    gpio_set_function(miso_pin, GPIO_FUNC_SPI);
    gpio_set_function(mosi_pin, GPIO_FUNC_SPI);
    gpio_set_function(sck_pin, GPIO_FUNC_SPI);

    gpio_init(_cs_pin);
    gpio_set_dir(_cs_pin, GPIO_OUT);
    gpio_put(_cs_pin, 1);
}

void NINA_SPI::cs_select() {
    gpio_put(_cs_pin, 0);
}

void NINA_SPI::cs_deselect() {
    gpio_put(_cs_pin, 1);
}

bool NINA_SPI::init() {
    // Check for module presence by sending a basic AT command
    char response[32];
    return send_command("AT", response, sizeof(response));
}

bool NINA_SPI::send_command(const char *command, char *response, uint32_t response_len, uint32_t timeout_ms) {
    cs_select();

    // Send command
    spi_write_blocking(_spi, (const uint8_t *)command, strlen(command));
    spi_write_blocking(_spi, (const uint8_t *)"\\r\\n", 2);

    cs_deselect();

    // Wait for response
    if (wait_for_response(timeout_ms)) {
        int bytes_read = read_response(response, response_len);
        if (bytes_read > 0) {
            // Check for "OK" in the response
            return strstr(response, "OK") != NULL;
        }
    }

    return false;
}

int NINA_SPI::read_response(char *buffer, uint32_t len, uint32_t timeout_ms) {
    absolute_time_t timeout_time = make_timeout_time_ms(timeout_ms);
    uint32_t pos = 0;

    while (get_absolute_time() < timeout_time && pos < len - 1) {
        cs_select();
        int bytes_read = spi_read_blocking(_spi, 0, (uint8_t *)&buffer[pos], 1);
        cs_deselect();

        if (bytes_read > 0) {
            pos += bytes_read;
        }
    }

    buffer[pos] = '\\0';
    return pos;
}


bool NINA_SPI::wait_for_response(uint32_t timeout_ms) {
    // This is a simplified implementation. A real implementation would use interrupts
    // or a separate thread to handle asynchronous responses from the NINA module.
    // For now, we will just poll for data.
    absolute_time_t timeout_time = make_timeout_time_ms(timeout_ms);
    uint8_t dummy_read;
    int bytes_read;

    while (get_absolute_time() < timeout_time) {
        cs_select();
        bytes_read = spi_read_blocking(_spi, 0, &dummy_read, 1);
        cs_deselect();
        if (bytes_read > 0) {
            return true;
        }
        sleep_ms(1);
    }

    return false;
}
