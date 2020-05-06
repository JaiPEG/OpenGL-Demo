#include "timer.h"

#include <Windows.h>

void timer_init(Timer* timer)
{
    LARGE_INTEGER largeInt;
    
    if (timer)
    {
        timer->start = 0;
        timer->end = 0;

        if (QueryPerformanceFrequency(&largeInt));
        {
            timer->frequency = largeInt.QuadPart;
        }
    }
}

void timer_start(Timer* timer)
{
    LARGE_INTEGER largeInt;

    if (QueryPerformanceCounter(&largeInt))
    {
        timer->start = largeInt.QuadPart;
    }
}

void timer_stop(Timer* timer)
{
    LARGE_INTEGER largeInt;

    if (QueryPerformanceCounter(&largeInt))
    {
        timer->end = largeInt.QuadPart;
    }
}

LONGLONG timer_interval_ticks(Timer* timer)
{
    return timer->end - timer->start;
}

double timer_interval_seconds(Timer* timer)
{
    return (double)(timer->end - timer->start) / (double)timer->frequency;
}

double timer_interval_milliseconds(Timer* timer)
{
    return (double)(timer->end - timer->start) / (double)timer->frequency * 1000.0;
}