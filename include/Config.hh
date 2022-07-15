#ifndef SWITCH_SD2VITA_CONFIG_HH
#define SWITCH_SD2VITA_CONFIG_HH

#include "../include/Utils.h"
#include "string"
#include <jansson.h>

class Config {
private:
  json_t *_config;
  void refreshConfigFile();

public:
  Config();

  void saveConfig();
  json_t *getConfig(const char *key);
  void setConfig(const char *key, json_t *newValue);
};

#endif // SWITCH_SD2VITA_CONFIG_HH
