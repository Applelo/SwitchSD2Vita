#include "../include/Config.hh"

Config::Config() {
    this->refreshConfigFile();
}

void Config::refreshConfigFile() {
    json_t *json;
    json_error_t error;
    json = json_load_file(APP_CONFIG_LOCALIZATION, 0, &error);

    if(json && json_is_object(json)) {
        _config = json;
    }
    else {
        _config = json_pack("{sb}","addMcd", true);
        json_dump_file(json, APP_CONFIG_LOCALIZATION, 0);
    }

}

void Config::saveConfig() {
    json_dump_file(_config, APP_CONFIG_LOCALIZATION, 0);
}

json_t* Config::getConfig(const char *key) {
    return json_object_get(_config, key);
}

void Config::setConfig(const char *key, json_t* newValue) {
    json_object_set(_config, key, newValue);
};

