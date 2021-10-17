#include "Core/Drivers/I2C/FXI2CDriverESP32.h"

FXI2CDriverESP32::FXI2CDriverESP32(FXI2CDriverESP32Config& config)
    : m_config(config)
    , m_communicationAddress(0)
{
    i2c_config_t i2cConfig = {};
    i2cConfig.mode = m_config.m_mode == EFXI2CMode::Master ? I2C_MODE_MASTER : I2C_MODE_SLAVE;
    i2cConfig.sda_io_num = m_config.m_sdaPin;
    i2cConfig.sda_pullup_en = m_config.m_enableSdaPullup ? GPIO_PULLUP_ENABLE : GPIO_PULLUP_DISABLE;
    i2cConfig.scl_io_num = m_config.m_sclPin;
    i2cConfig.scl_pullup_en = m_config.m_enableSclPullup ? GPIO_PULLUP_ENABLE : GPIO_PULLUP_DISABLE;

    if (m_config.m_mode == EFXI2CMode::Master)
    {
        i2cConfig.master.clk_speed = m_config.m_clockSpeed;
    }

    ESP_ERROR_CHECK(i2c_param_config(m_config.m_i2cPort, &i2cConfig));
    ESP_ERROR_CHECK(i2c_driver_install(m_config.m_i2cPort, i2cConfig.mode, 0, 0, 0));
}


FXI2CDriverESP32::~FXI2CDriverESP32()
{
    i2c_driver_delete(m_config.m_i2cPort);
}

void FXI2CDriverESP32::StartWrite(uint16 deviceAddress, EFXI2CAck i2cAck /*= EFXI2CAck::Ack*/)
{
    m_command = i2c_cmd_link_create();
    i2c_master_start(m_command);
    i2c_master_write_byte(m_command, (deviceAddress << 1) | I2C_MASTER_WRITE, 1);
}

void FXI2CDriverESP32::StartRead(uint16 deviceAddress, uint8 readAddress, EFXI2CAck i2cAck /*= EFXI2CAck::Ack*/)
{
    // First Tell the device we want to read from this address
    m_command = i2c_cmd_link_create();
    i2c_master_start(m_command);
    i2c_master_write_byte(m_command, (deviceAddress << 1) | I2C_MASTER_WRITE, 1);
    i2c_master_write_byte(m_command, readAddress, 1);
    i2c_master_stop(m_command);
    esp_err_t i2c_ret = i2c_master_cmd_begin(m_config.m_i2cPort, m_command, 100 / portTICK_RATE_MS);
    i2c_cmd_link_delete(m_command);
    if (i2c_ret != ESP_OK)
    {
        return;
    }

    // Setup the read command
    m_command = i2c_cmd_link_create();
    i2c_master_start(m_command);
    i2c_master_write_byte(m_command, (deviceAddress << 1) | I2C_MASTER_READ, 1);
}

void FXI2CDriverESP32::Write(uint8 data, EFXI2CAck i2cAck /*= EFXI2CAck::Ack*/)
{
    i2c_master_write_byte(m_command, data, i2cAck == EFXI2CAck::Ack ? true : false);
}

void FXI2CDriverESP32::Read(uint8 data, EFXI2CAck i2cAck /*= EFXI2CAck::Nack*/)
{
    i2c_master_read_byte(m_command, &data, (i2c_ack_type_t)0x2);
}

void FXI2CDriverESP32::Write(uint8* data, uint32 dataLength, EFXI2CAck i2cAck /*= FXI2CAck::Ack*/)
{
    i2c_master_write(m_command, data, dataLength, i2cAck == EFXI2CAck::Ack ? true : false);
}

void FXI2CDriverESP32::Read(uint8* data, uint32 dataLength, EFXI2CAck i2cAck /*= FXI2CAck::Nack*/)
{
    i2c_master_read(m_command, data, dataLength, (i2c_ack_type_t)0x2);
}

EFXI2CReturn FXI2CDriverESP32::End()
{
    i2c_master_stop(m_command);
    esp_err_t i2c_ret = i2c_master_cmd_begin(m_config.m_i2cPort, m_command, 100 / portTICK_RATE_MS);
    i2c_cmd_link_delete(m_command);
    m_command = NULL;

    switch (i2c_ret)
    {
    case ESP_OK:
        return EFXI2CReturn::Success;
    case ESP_FAIL:
    case ESP_ERR_INVALID_ARG:
    case ESP_ERR_INVALID_STATE:
        return EFXI2CReturn::Failed;
    case ESP_ERR_TIMEOUT:
        return EFXI2CReturn::Timeout;
    default:
        return EFXI2CReturn::Failed;
    }
}