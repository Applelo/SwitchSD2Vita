/*
 **
 ** Made by Applelo
 **
 */

#include "../include/Engine.hh"

Engine::Engine() {
  _setup[GCD] = this->calcSetup(GCD);
  _setup[MCD] = this->calcSetup(MCD);
  _config = new Config();
}

Engine::~Engine() {}

int Engine::auto_switch() {
  if (_setup[GCD] == UMA0) {
    return this->switch_to(UX0);
  } else {
    return this->switch_to(UMA0);
  }
}

int Engine::switch_to(Setup setup) {

  std::string old_config_entry;
  std::string new_config_entry = this->getConfigEntryString(setup, GCD) + "\n";
  if (getAddMcdOption()) {
    new_config_entry += this->getConfigEntryString(setup, MCD) + "\n";
    _setup[MCD] = setup != UX0 ? UX0 : UMA0;

  } else {
    _setup[MCD] = NO;
  }

  this->renameTaiUX0Folder(true);

  // check and copy Storage Mgr plugin
  _file = new File(SMGR_LOCALIZATION);
  if (!_file->checkFileExist()) {

    // copy SMGR plugin
    File *smgr_app_localization = new File(SMGR_APP_LOCALIZATION);
    if (smgr_app_localization->checkFileExist()) {
      int result = smgr_app_localization->copyFile(SMGR_LOCALIZATION, NULL);
      if (!result) {
        return 0;
      }
    } else {
      return 0;
    }
    delete smgr_app_localization;
  }
  delete _file;

  // add plugin line if it doesn't set
  _file = new File(CONFIG_LOCALIZATION);
  if (_file->findFileLine("*KERNEL") < 0) {
    return 0;
  }
  if (_file->findFileLine("\n" SMGR_LOCALIZATION) < 0) {
    _file->addFileLine("\n" SMGR_LOCALIZATION, _file->findFileLine("*KERNEL"));
  }
  delete _file;

  // update smgr config file
  _file = new File(SMGR_CONFIG_LOCALIZATION);
  if (!_file->checkFileExist()) {
    _file->writeFile("", 1); // create file if it doesn't exist
  }

  if (_setup[GCD] != NO) {
    old_config_entry = this->getConfigEntryString(_setup[GCD], GCD) + "\n";
    int find_line = _file->findFileLine(old_config_entry.c_str());
    if (find_line > -1) {
      _file->deleteFileLine(old_config_entry.c_str(), find_line);
    }

    old_config_entry = this->getConfigEntryString(_setup[GCD], MCD) + "\n";
    find_line = _file->findFileLine(old_config_entry.c_str());
    if (find_line > -1) {
      _file->deleteFileLine(old_config_entry.c_str(), find_line);
    }
  }

  _file->addFileLine(new_config_entry.c_str(), -1);
  delete _file;

  // update database on switch
  this->updateDb(_setup[GCD]);

  _setup[GCD] = setup;
  return 1;
}

int Engine::uninstall() {

  int find_line;

  // Remove StorageMgrPlugin in config plugin
  _file = new File(CONFIG_LOCALIZATION);
  find_line = _file->findFileLine("\n" SMGR_LOCALIZATION);
  if (find_line > -1) {
    _file->deleteFileLine("\n" SMGR_LOCALIZATION, find_line);
  }
  delete _file;

  // remove storage mgr plugin
  _file = new File(SMGR_LOCALIZATION);
  if (_file->checkFileExist()) {
    _file->removeFile();
  }
  delete _file;

  // remove storage mgr config
  _file = new File(SMGR_CONFIG_LOCALIZATION);
  if (_file->checkFileExist()) {
    _file->removeFile();
  }
  delete _file;

  this->renameTaiUX0Folder(false);

  // Uninstall old installation
  if (this->isOldInstallation()) {

    // Uninstall old installation
    _file = new File(CONFIG_LOCALIZATION);
    find_line = _file->findFileLine("\n" OLD_UX0_LOCALIZATION);
    if (find_line > -1) {
      _file->deleteFileLine("\n" OLD_UX0_LOCALIZATION, find_line);
    }
    delete _file;

    _file = new File(OLD_UX0_LOCALIZATION);
    if (_file->checkFileExist()) {
      _file->removeFile();
    }
    delete _file;

    _file = new File(CONFIG_LOCALIZATION);
    find_line = _file->findFileLine("\n" OLD_UMA0_LOCALIZATION);
    if (find_line > -1) {
      _file->deleteFileLine("\n" OLD_UMA0_LOCALIZATION, find_line);
    }
    delete _file;

    _file = new File(OLD_UMA0_LOCALIZATION);
    if (_file->checkFileExist()) {
      _file->removeFile();
    }
    delete _file;

    // Uninstall old old installation
    _file = new File(OLD_CONFIG_LOCALIZATION);
    find_line = _file->findFileLine("\n" OLD_OLD_UMA0_LOCALIZATION);
    if (find_line > -1) {
      _file->deleteFileLine("\n" OLD_OLD_UMA0_LOCALIZATION, find_line);
    }
    delete _file;

    _file = new File(OLD_OLD_UMA0_LOCALIZATION);
    if (_file->checkFileExist()) {
      _file->removeFile();
    }
    delete _file;
  }

  _setup[GCD] = NO;
  _setup[MCD] = NO;
  return 1;
}

// Getter
const Setup Engine::getSetup(Target target) { return _setup[target]; }

std::string Engine::getConfigEntryString(Setup setup, Target target) {
  if (target == GCD) {
    return "GCD=" + this->getSetupString(setup);
  } else {
    if (setup != UX0) {
      return "MCD=" + this->getSetupString(UX0);
    }

    return "MCD=" + this->getSetupString(UMA0);
  }
}

std::string Engine::getSetupString(Setup setup) {

  switch (setup) {
  case UMA0:
    return "uma0";
  case UX0:
    return "ux0";
  case XMC0:
    return "xmc0";
  case IMC0:
    return "imc0";
  case GRW0:
    return "grw0";
  default:
    return "";
  }
}

const Setup Engine::calcSetup(Target target) {
  Setup setup = NO;
  _file = new File(SMGR_CONFIG_LOCALIZATION);
  if (!_file->checkFileExist()) {
    delete _file;
    return setup;
  }

  std::string target_name = target == GCD ? "GCD" : "MCD";

  if (_file->findFileLine(std::string(target_name + "=uma0").c_str()) > -1) {
    setup = UMA0;
  } else if (_file->findFileLine(std::string(target_name + "=ux0").c_str()) >
             -1) {
    setup = UX0;
  } else if (_file->findFileLine(std::string(target_name + "=xmc0").c_str()) >
             -1) {
    setup = XMC0;
  } else if (_file->findFileLine(std::string(target_name + "=imc0").c_str()) >
             -1) {
    setup = IMC0;
  } else if (_file->findFileLine(std::string(target_name + "=grw0").c_str()) >
             -1) {
    setup = GRW0;
  }
  delete _file;

  return setup;
}

const bool Engine::isOldInstallation() {

  _file = new File(OLD_UX0_LOCALIZATION);
  if (_file->checkFileExist()) {
    return true;
  }
  delete _file;

  _file = new File(OLD_UMA0_LOCALIZATION);
  if (_file->checkFileExist()) {
    return true;
  }
  delete _file;

  _file = new File(OLD_OLD_UMA0_LOCALIZATION);
  if (_file->checkFileExist()) {
    return true;
  }
  delete _file;

  _file = new File(OLD_CONFIG_LOCALIZATION);
  if (_file->checkFileExist() &&
      _file->findFileLine(OLD_OLD_UMA0_LOCALIZATION) > 0) {
    return true;
  }
  delete _file;

  return false;
}

void Engine::reboot() { scePowerRequestColdReset(); }

void Engine::updateDb(Setup setup) {
  std::string id_dat_path = this->getSetupString(setup) + ":/id.dat";
  File *id_dat_file = new File(id_dat_path.c_str());
  if (id_dat_file->checkFileExist()) {
    id_dat_file->removeFile();
  }
  delete id_dat_file;
}

void Engine::installChangelog() {
  sceIoMkdir("ux0:patch/SWITCHSDV/", 0777); // Create folders if it doesn't
                                            // exist
  sceIoMkdir("ux0:patch/SWITCHSDV/sce_sys/", 0777);
  sceIoMkdir("ux0:patch/SWITCHSDV/sce_sys/changeinfo", 0777);

  _file = new File(CHANGELOG_LOCALIZATION);
  _file->copyFile(NEW_CHANGELOG_LOCALIZATION, NULL);
  delete _file;
}

void Engine::renameTaiUX0Folder(bool status) {

  SceUID folder;

  if (status) {

    folder = sceIoDopen("ux0:/tai");
    if (folder > -1) {
      sceIoRename("ux0:/tai", "ux0:/taiOld");
    }
    sceIoDclose(folder);

  } else {

    folder = sceIoDopen("ux0:/taiOld");
    if (folder > -1) {
      sceIoRename("ux0:/taiOld", "ux0:/tai");
    }
    sceIoDclose(folder);
  }
}

void Engine::toggleAddMcdOption() {
  if (json_is_true(_config->getConfig("addMcd"))) {
    _config->setConfig("addMcd", json_false());
  } else {
    _config->setConfig("addMcd", json_true());
  }
  _config->saveConfig();
}

bool Engine::getAddMcdOption() {
  return json_is_true(_config->getConfig("addMcd"));
}