#include "Utils/FXUtils.h"

#ifdef FALCONX_ESP_IDF
#include "esp_timer.h"
#include <unistd.h>
#endif

int64 FX_GetMicros()
{
#ifdef FALCONX_ESP_IDF
    return esp_timer_get_time();
#endif
}

void FX_Sleep(int32 ms)
{
#ifdef FALCONX_ESP_IDF
    usleep(ms * 1000);
#endif
}
