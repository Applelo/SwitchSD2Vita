/*
 **
 ** Made by Applelo
 **
 */

#ifndef UTILS_H_
# define UTILS_H_

# include <stdio.h>
# include <stdint.h>
# include <string.h>
# include <math.h>
# include <string>
# include <stdlib.h>
# include <psp2/io/fcntl.h>
# include <psp2/io/stat.h>
# include <psp2/ctrl.h>
# include <psp2/kernel/processmgr.h>
# include <psp2/touch.h>
# include <psp2/sysmodule.h>
# include <ctime>
# include <vector>
# include <iostream>
# include <map>
# include <string>

# include <vita2d.h>

# define lerp(value, from_max, to_max) ((((value*10) * (to_max*10))/(from_max*10))/10)

# define SCREEN_H	544
# define SCREEN_L	960
# define WHITE RGBA8(255, 255, 255, 255)
# define GREEN RGBA8(0, 255, 0, 255)
# define RED RGBA8(255, 0, 0, 255)
# define LIGHT_GREY RGBA8(180, 180, 180, 255)
# define VERSION_NUMBER 1.0

# define BIG_BUFFER_SIZE 16 * 1024 * 1024
# define DIRECTORY_SIZE (4 * 1024)
# define TRANSFER_SIZE (64 * 1024)

typedef struct {
    uint64_t *value;
    uint64_t max;
    void (* SetProgress)(uint64_t value, uint64_t max);
    int (* cancelHandler)();
} FileProcessParam;

#endif /* !UTILS_H_ */
