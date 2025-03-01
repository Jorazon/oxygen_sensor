#include <signal.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

#include "EOxygenSensor.h"
#include "delay.h"

#define ESC "\033"

void handle(int signum);

int file;

int main(int argc, char *argv[]) {
    /* set signal handler */
    struct sigaction action;
    memset(&action, 0, sizeof(action));
    action.sa_handler = handle;
    sigaction(SIGTERM, &action, NULL);
    sigaction(SIGINT, &action, NULL);
    
    printf(ESC"[?25l"); /* hide cursor */
    
    /* open I2C file */
    char filename[20];
    snprintf(filename, 19, "/dev/i2c-%d", I2C_PORT);
    file = open(filename, O_RDWR);
    if (file < 0) {
        fprintf(stderr, "Failed to open I2C file %s! %s\n", filename, strerror(errno));
        exit(1);
    }
    
    /* set I2C address */
    if (ioctl(file, I2C_SLAVE, E_OXYGEN_ADDRESS_0) < 0) {
        fprintf(stderr, "Failed to connect to I2C device at address %#02x! %s\n", E_OXYGEN_ADDRESS_0, strerror(errno));
        exit(1);
    }
    
    /* calibrate sensor */
    if (argc > 1 && strcmp(argv[1], "-c")) {
        printf("O2 sensor calibrating...\r");
        fflush(stdout);
        if (!calibration_20_9(file)) {
            fprintf(stderr, "O2 sensor calibration failed! %s\n", strerror(errno));
            exit(1);
        } else {
            printf("O2 sensor calibrated for an ambient O2 concentration of 20.90%% Vol\n");
        }
    }
    
    /* read and print concentration */
    printf(ESC"7"); /* save cursor position */
    for(;;) {
        printf(ESC"8"); /* restore cursor position */
        //dumpROM(file);
        printf("\rO2: %6.2f%% Vol"ESC"[0K", readOxygenConcentration(file));
        fflush(stdout);
        delay(500);
    }
    
    printf(ESC"[?25h\n"); /* show cursor */
    
    return 0;
}

/* candle termination signals */
void handle(int signum) {
    (void)signum;
    printf(ESC"[?25h\n"); /* show cursor */
    exit(0);
}
