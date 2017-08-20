/*
 **
 ** Made by Applelo
 **
 */

#ifndef UTILS_H_
# define UTILS_H_

//# include <debugnet.h>
# include <stdio.h>
# include <string.h>
# include <string>
# include <stdlib.h>
# include <psp2/io/fcntl.h>
# include <psp2/io/stat.h>
# include <psp2/ctrl.h>
# include <psp2/kernel/processmgr.h>
# include <psp2/power.h>
# include <vector>
# include <string>

# include <vita2d.h>

# define SCREEN_L	960
# define SCREEN_H	544
# define WHITE RGBA8(255, 255, 255, 255)
# define GREEN RGBA8(0, 255, 0, 255)
# define LIGHT_GREEN RGBA8(50, 205, 50, 255)
# define RED RGBA8(255, 0, 0, 255)
# define LIGHT_GREY RGBA8(180, 180, 180, 255)
# define BACKGROUND RGBA8(36, 41, 45, 255)
# define VERSION_NUMBER 1.0

//File
# define TRANSFER_SIZE (64 * 1024)
# define UMA0_APP_LOCALIZATION "app0:plugins/gamesd_uma0.skprx"
# define UX0_APP_LOCALIZATION "app0:plugins/gamesd_ux0.skprx"
# define UMA0_LOCALIZATION "ur0:tai/gamesd_uma0.skprx"
# define UX0_LOCALIZATION "ur0:tai/gamesd_ux0.skprx"
//# define UMA0_CONFIG_LOCALIZATION "ux0:tai/config.txt"
# define UMA0_CONFIG_LOCALIZATION "ur0:tai/config.txt"
# define UX0_CONFIG_LOCALIZATION "ur0:tai/config.txt"

//debugnet
//#define IP_SERVER "192.168.0.26"
//#define PORT_SERVER 18194

typedef struct {
    uint64_t *value;
    uint64_t max;
    void (* SetProgress)(uint64_t value, uint64_t max);
    int (* cancelHandler)();
} FileProcessParam;

#endif /* !UTILS_H_ */
