#include "../include/Config.hh"

Config::Config() { this->refreshConfigFile(); }

void Config::refreshConfigFile() {
  json_t *json;
  json_error_t error;
  json = json_load_file(APP_CONFIG_LOCALIZATION, 0, &error);

  if (json && json_is_object(json)) {
    _config = json;
  } else {
    _config =
        json_pack("{s:I, s:b}", "version", VERSION_NUMBER, "addMcd", true);
    saveConfig();
  }
}

void Config::saveConfig() {
  // need to add the folder before save the file to the right localization
  sceIoMkdir("ux0:data/SwitchSD2Vita", 0777);
  json_dump_file(_config, "ux0:data/SwitchSD2Vita/config.json", 0);
}

json_t *Config::getConfig(const char *key) {
  return json_object_get(_config, key);
}

void Config::setConfig(const char *key, json_t *newValue) {
  json_object_set(_config, key, newValue);
};
