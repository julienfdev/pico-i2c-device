#ifndef I2C_DEVICE_H
#define I2C_DEVICE_H
#include "pico/stdlib.h"
#include "hardware/i2c.h"


struct I2CPins {
    uint8_t sda;
    uint8_t scl;
};

class I2CDevice {
  private:
     i2c_inst_t *m_i2c;
     uint8_t m_addr;
     uint8_t m_buffer[256];

  public:
    explicit I2CDevice(const uint8_t addr, i2c_inst_t *i2c = i2c0, const uint baudrate = 100000, const I2CPins pins = { 4, 5 }): m_i2c { i2c }, m_addr { addr }, m_buffer { 0 } {
        i2c_init(i2c, baudrate);
        gpio_set_function(pins.sda, GPIO_FUNC_I2C);
        gpio_set_function(pins.scl, GPIO_FUNC_I2C);
        gpio_pull_up(pins.sda);
        gpio_pull_up(pins.scl);
    }
    I2CDevice(const I2CDevice&) = delete;
    I2CDevice() = delete;

    void write(uint8_t reg, const uint8_t* data, size_t size = 1);
    void read(uint8_t reg, uint8_t* result, size_t size = 1) const;
};
#endif // I2C_DEVICE_H