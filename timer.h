#ifndef TIMER_H221
#define TIMER_H221

#include <Windows.h>

typedef struct
{
    LONGLONG frequency;
    LONGLONG start;
    LONGLONG end;
} Timer;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void timer_init(Timer* timer);
void timer_start(Timer* timer);
void timer_stop(Timer* timer);
LONGLONG timer_interval_ticks(Timer* timer);
double timer_interval_seconds(Timer* timer);
double timer_interval_milliseconds(Timer* timer);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // TIMER_H221