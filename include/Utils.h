/*
 **
 ** Made by Applelo
 **
 */

#ifndef UTILS_H_
# define UTILS_H_

# include <stdio.h>
# include <string.h>
# include <string>
# include <stdlib.h>
# include <psp2/io/fcntl.h>
# include <psp2/io/dirent.h>
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
# define BACKGROUND2 RGBA8(40, 45, 49, 150)
# define VERSION_NUMBER 2.1

//File
# define TRANSFER_SIZE (64 * 1024)
# define SMGR_APP_LOCALIZATION "app0:plugins/storagemgr.skprx"
# define SMGR_LOCALIZATION "ur0:tai/storagemgr.skprx"
# define CONFIG_LOCALIZATION "ur0:tai/config.txt"
# define SMGR_CONFIG_LOCALIZATION "ur0:tai/storage_config.txt"

//Old config defines
# define OLD_UX0_LOCALIZATION "ur0:tai/gamesd_ux0.skprx"
# define OLD_UMA0_LOCALIZATION "ur0:tai/gamesd_uma0.skprx"
# define OLD_OLD_UMA0_LOCALIZATION "ux0:tai/gamesd_uma0.skprx"
# define OLD_CONFIG_LOCALIZATION "ux0:tai/config.txt"

# define CHANGELOG_LOCALIZATION "ux0:app/SWITCHSDV/sce_sys/changeinfo.xml"
# define NEW_CHANGELOG_LOCALIZATION "ux0:patch/SWITCHSDV/sce_sys/changeinfo/changeinfo.xml"

typedef struct {
    uint64_t *value;
    uint64_t max;
    void (* SetProgress)(uint64_t value, uint64_t max);
    int (* cancelHandler)();
} FileProcessParam;

#endif /* !UTILS_H_ */
