#include "i2c_device.h"
#include <cstring>
void I2CInterface::write(const uint8_t addr, const uint8_t reg, const uint8_t *data, const size_t size) {
    m_buffer[0] = reg;
    for (size_t i = 0; i < size; i++) {
        m_buffer[i + 1] = data[i];
    }

    i2c_write_blocking(m_i2c, addr, m_buffer, size + 1, false);

    // wipe buffer
    memset(m_buffer, 0, sizeof(m_buffer));
}
void I2CInterface::read(const uint8_t addr, const uint8_t reg, uint8_t *result, const size_t size) const {
    i2c_write_blocking(m_i2c, addr, &reg, 1, true);
    i2c_read_blocking(m_i2c, addr, result, size, false);
}

void I2CDevice::write(const uint8_t reg, const uint8_t* data, const size_t size) {
    m_i2c.write(m_addr, reg, data, size);
}

void I2CDevice::read(const uint8_t reg, uint8_t* result, const size_t size) const {
    m_i2c.read(m_addr, reg, result, size);
}


