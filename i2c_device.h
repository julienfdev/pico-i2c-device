#ifndef I2C_DEVICE_H
#define I2C_DEVICE_H
#include "pico/stdlib.h"
#include "hardware/i2c.h"


struct I2CPins {
    uint8_t sda;
    uint8_t scl;
};

class I2CInterface {
private:
    i2c_inst_t *m_i2c;
    uint8_t m_buffer[256];
public:
    explicit I2CInterface(i2c_inst_t *i2c = i2c0, const uint baudrate = 100000, const I2CPins pins = { 4, 5 }): m_i2c { i2c }, m_buffer { 0 } {
        i2c_init(i2c, baudrate);
        gpio_set_function(pins.sda, GPIO_FUNC_I2C);
        gpio_set_function(pins.scl, GPIO_FUNC_I2C);
        gpio_pull_up(pins.sda);
        gpio_pull_up(pins.scl);
    }

    void write(uint8_t addr, uint8_t reg, const uint8_t* data, size_t size = 1);
    void read(uint8_t addr, uint8_t reg, uint8_t* result, size_t size = 1) const;
};

class I2CDevice {
  private:
     uint8_t m_addr;
     I2CInterface m_i2c;

  public:
    explicit I2CDevice(const uint8_t addr, i2c_inst_t *i2c = i2c0, const uint baudrate = 100000, const I2CPins pins = { 4, 5 }): m_addr { addr } {
        m_i2c = I2CInterface(i2c, baudrate, pins);
    }
    I2CDevice(const I2CDevice&) = delete;
    I2CDevice() = delete;

    void write(uint8_t reg, const uint8_t* data, size_t size = 1);
    void read(uint8_t reg, uint8_t* result, size_t size = 1) const;
};
#endif // I2C_DEVICE_H