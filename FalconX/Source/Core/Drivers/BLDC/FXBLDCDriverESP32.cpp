#include "Core/Drivers/BLDC/FXBLDCDriverESP32.h"
#include "driver/ledc.h"

uint8   FXBLDCDriverESP32::m_availableChannels[8] = {};
bool   FXBLDCDriverESP32::m_isTimerInitialised = false;

#define BLDC_MIN_PULSE 1000
#define BLDC_MAX_PULSE 2000
#define BLDC_MAX_RESOLUTION 16383

FXBLDCDriverESP32::FXBLDCDriverESP32(FXBLDCDriverConfig& config)
    : FXBLDCDriver(config)
    , m_ledcChannel(0)
    , m_minPercentageValue(0)
    , m_maxPercentageValue(0)
    , m_percentageValueRange(0)
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
        ledcTimer.duty_resolution = LEDC_TIMER_14_BIT;
        ledcTimer.freq_hz = 50;
        ledcTimer.speed_mode = LEDC_HIGH_SPEED_MODE;
        ledcTimer.timer_num = LEDC_TIMER_0;
        ledcTimer.clk_cfg = LEDC_AUTO_CLK;

        ledc_timer_config(&ledcTimer);
        m_isTimerInitialised = true;
    }

    m_minPercentageValue = 0.05f * BLDC_MAX_RESOLUTION; // 5%
    m_maxPercentageValue = 0.1f * BLDC_MAX_RESOLUTION;  // 10%
    m_percentageValueRange = m_maxPercentageValue - m_minPercentageValue;

    ledc_channel_config_t ledcConfig = {};
    ledcConfig.channel = (ledc_channel_t)m_ledcChannel;
    ledcConfig.duty = m_maxPercentageValue;
    ledcConfig.gpio_num = config.PinOut;
    ledcConfig.speed_mode = LEDC_HIGH_SPEED_MODE;
    ledcConfig.timer_sel = LEDC_TIMER_0;

    ledc_channel_config(&ledcConfig);
}

void FXBLDCDriverESP32::SetSpeed(float speed)
{
    float pulseWidth = m_minPercentageValue + (speed * m_percentageValueRange);
    pulseWidth = (pulseWidth < m_minPercentageValue) ? m_minPercentageValue : (pulseWidth > m_maxPercentageValue) ? m_maxPercentageValue : pulseWidth;
    printf("BLDC Value : %d\n", (uint32)pulseWidth);
    ledc_set_duty(LEDC_HIGH_SPEED_MODE, (ledc_channel_t)m_ledcChannel, (uint32)pulseWidth);
    ledc_update_duty(LEDC_HIGH_SPEED_MODE, (ledc_channel_t)m_ledcChannel);
}