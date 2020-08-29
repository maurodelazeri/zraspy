#include <iostream>
#include <gpiod.h>
#include <cstdio>
#include <unistd.h>

#ifndef    CONSUMER
#define    CONSUMER    "Consumer"
#endif

using namespace std;

int main() {

    const char *chipname = "gpiochip0";
    unsigned int ldr = 23;    // GPIO LDR
    unsigned int buzzer = 24;  // GPIO Buzzer
    unsigned int laser = 25;   // GPIO laser

    struct timespec ts = {1, 0};
    struct gpiod_line_event event{};
    struct gpiod_chip *chip;
    struct gpiod_line *line_ldr;
    struct gpiod_line *line_buzzer;
    struct gpiod_line *line_laser;

    int i, ret;

    chip = gpiod_chip_open_by_name(chipname);
    if (!chip) {
        perror("Open chip failed\n");
        ret = -1;
        goto end;
    }

    line_ldr = gpiod_chip_get_line(chip, ldr);
    if (!line_ldr) {
        perror("Get ldr failed\n");
        ret = -1;
        goto close_chip;
    }

    line_buzzer = gpiod_chip_get_line(chip, buzzer);
    if (!line_buzzer) {
        perror("Get buzzer failed\n");
        ret = -1;
        goto close_chip;
    }

    line_laser = gpiod_chip_get_line(chip, laser);
    if (!line_laser) {
        perror("Get laser failed\n");
        ret = -1;
        goto close_chip;
    }

    ret = gpiod_line_request_output(line_buzzer, CONSUMER, 0);
    if (ret < 0) {
        perror("Request line_buzzer as output failed\n");
        goto release_line;
    }

    ret = gpiod_line_request_output(line_laser, CONSUMER, 1);
    if (ret < 0) {
        perror("Request line_laser as output failed\n");
        goto release_line;
    }

    ret = gpiod_line_request_output(line_ldr, CONSUMER, 0);
    if (ret < 0) {
        perror("Request line_ldr as output failed\n");
        goto release_line;
    }

    while (true) {
        ret = gpiod_line_set_value(line_buzzer, 1);
        if (ret < 0) {
            perror("Set line_buzzer output failed\n");
            goto release_line;
        }

        ret = gpiod_line_set_value(line_laser, 1);
        if (ret < 0) {
            perror("Set line_laser output failed\n");
            goto release_line;
        }

        sleep(1);

        ret = gpiod_line_set_value(line_buzzer, 0);
        if (ret < 0) {
            perror("Set line_buzzer output failed\n");
            goto release_line;
        }

        ret = gpiod_line_set_value(line_laser, 0);
        if (ret < 0) {
            perror("Set line_laser output failed\n");
            goto release_line;
        }

        sleep(1);
    }

    sleep(5);

    ret = gpiod_line_set_value(line_buzzer, 0);
    if (ret < 0) {
        perror("Set line output failed\n");
        goto release_line;
    }

//    ret = gpiod_line_request_rising_edge_events(line, CONSUMER);
//    if (ret < 0) {
//        perror("Request event notification failed\n");
//        ret = -1;
//        goto release_line;
//    }

//    /* Notify event up to 20 times */
//    i = 0;
//    while (i <= 20) {
//        ret = gpiod_line_event_wait(line, &ts);
//        if (ret < 0) {
//            perror("Wait event notification failed\n");
//            ret = -1;
//            goto release_line;
//        } else if (ret == 0) {
//                printf("Wait event notification on line #%u timeout\n", line_num);
//                continue;
//            }
//
//            ret = gpiod_line_event_read(line, &event);
//            printf("Get event notification on line #%u %d times\n", line_num, i);
//            if (ret < 0) {
//                perror("Read last event notification failed\n");
//                ret = -1;
//                goto release_line;
//            }
//        sleep(1);
//
//        i++;
//    }

    ret = 0;

    release_line:
    gpiod_line_release(line_ldr);
    gpiod_line_release(line_buzzer);
    gpiod_line_release(line_laser);

    close_chip:
    gpiod_chip_close(chip);
    end:
    return ret;
}