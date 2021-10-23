#include "Core/Drivers/BLDC/FXBLDCDriverESP32.h"
#include "driver/ledc.h"

uint8   FXBLDCDriverESP32::m_availableChannels[8] = {};
bool   FXBLDCDriverESP32::m_isTimerInitialised = false;

#define BLDC_MIN_PULSE 1000
#define BLDC_MAX_PULSE 2000

FXBLDCDriverESP32::FXBLDCDriverESP32(FXBLDCDriverConfig& config)
    : FXBLDCDriver(config)
    , m_ledcChannel(0)
{
    for (int i = 0; i < 8; i++)
    {
        if (m_availableChannels[i] == 0)
        {
            m_availableChannels[i] = 1;
            m_ledcChannel = i;
            break;
        }
    }

    if (!m_isTimerInitialised)
    {
        ledc_timer_config_t ledcTimer = {};
        ledcTimer.duty_resolution = LEDC_TIMER_11_BIT;
        ledcTimer.freq_hz = 50;
        ledcTimer.speed_mode = LEDC_HIGH_SPEED_MODE;
        ledcTimer.timer_num = LEDC_TIMER_0;
        ledcTimer.clk_cfg = LEDC_AUTO_CLK;

        ledc_timer_config(&ledcTimer);
        m_isTimerInitialised = true;
    }

    ledc_channel_config_t ledcConfig = {};
    ledcConfig.channel = (ledc_channel_t)m_ledcChannel;
    ledcConfig.duty = BLDC_MAX_PULSE;
    ledcConfig.gpio_num = config.PinOut;
    ledcConfig.speed_mode = LEDC_HIGH_SPEED_MODE;
    ledcConfig.timer_sel = LEDC_TIMER_0;

    ledc_channel_config(&ledcConfig);
}

void FXBLDCDriverESP32::SetSpeed(float speed)
{
    uint32 pulseWidth = BLDC_MIN_PULSE + (speed * BLDC_MIN_PULSE);
    pulseWidth = (pulseWidth < BLDC_MIN_PULSE) ? BLDC_MIN_PULSE : (pulseWidth > BLDC_MAX_PULSE) ? BLDC_MAX_PULSE : pulseWidth;
    ledc_set_duty(LEDC_HIGH_SPEED_MODE, (ledc_channel_t)m_ledcChannel, pulseWidth);
    ledc_update_duty(LEDC_HIGH_SPEED_MODE, (ledc_channel_t)m_ledcChannel);
}