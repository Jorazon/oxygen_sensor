#include "delay.h"
#include <unistd.h>

/* milliseconds to microseconds factor */
#define MS_2_US 1000ll

/**
 * @brief Millisecond delay
 */
void delay(int ms) {
    usleep(ms * MS_2_US);
}
