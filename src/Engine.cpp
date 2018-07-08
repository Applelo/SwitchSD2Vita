/*
 **
 ** Made by Applelo and Yosh (aka wth)
 **
 */

# include "../include/Engine.hh"

Engine::Engine() {
	_setup = this->calcSetup();
}

Engine::~Engine() {
}

int Engine::auto_switch() {
    if (_setup == UMA0) {
        return this->switch_to(UX0);
    }
    else {
        return this->switch_to(UMA0);
    }
}


int Engine::switch_to(Setup setup) {

    std::string old_config_entry = "";
    std::string new_config_entry = this->getSetupString(setup) + "\n";
    if (_setup != NO) {
        old_config_entry = this->getSetupString(_setup) + "\n";
    }

    this->renameTaiUX0Folder(true);


    //check and copy Storage Mgr plugin
    _file = new File(SMGR_LOCALIZATION);
    if (!_file->checkFileExist()) {

        //copy SMGR plugin
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


    //add plugin line if it doesn't set
    _file = new File(CONFIG_LOCALIZATION);
    if (_file->findFileLine("*KERNEL") < 0) {
        return 0;
    }
    if (_file->findFileLine("\n" SMGR_LOCALIZATION) < 0) {
        _file->addFileLine("\n" SMGR_LOCALIZATION, _file->findFileLine("*KERNEL"));
    }
    delete _file;

    //update smgr config file
    _file = new File(SMGR_CONFIG_LOCALIZATION);
    if (!_file->checkFileExist()) {
        _file->writeFile("", 1);//create file if it doesn't exist
    }

    if (_setup != NO) {
        int find_line = _file->findFileLine(old_config_entry.c_str());
        if (find_line > -1) {
            _file->deleteFileLine(old_config_entry.c_str(), find_line);
        }
    }

    _file->addFileLine(new_config_entry.c_str(), -1);
    delete _file;


    //update database on switch
   this->updateDb();


    _setup = setup;
    return 1;
}


int Engine::uninstall() {

    int find_line;

	//Remove StorageMgrPlugin in config plugin
    _file = new File(CONFIG_LOCALIZATION);
    find_line = _file->findFileLine("\n" SMGR_LOCALIZATION);
    if (find_line > -1) {
        _file->deleteFileLine("\n" SMGR_LOCALIZATION, find_line);
    }
    delete _file;

    //remove storage mgr plugin
    _file = new File(SMGR_LOCALIZATION);
    if (_file->checkFileExist()) {
        _file->removeFile();
    }
    delete _file;

    //remove storage mgr config
    _file = new File(SMGR_CONFIG_LOCALIZATION);
    if (_file->checkFileExist()) {
        _file->removeFile();
    }
    delete _file;

    this->renameTaiUX0Folder(false);


	//Uninstall old installation
	if (this->isOldInstallation()) {

        //Uninstall old installation
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

        //Uninstall old old installation
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

	_setup = NO;
	return 1;
}

//Setter
void Engine::setSetup(const Setup setup) {
	_setup = setup;
}

//Getter
const Setup Engine::getSetup() {
	return _setup;
}

std::string Engine::getSetupString(Setup setup) {
    std::string gcd = "GCD=";
    std::string mount_point;
    std::string config_entry;

    switch (setup) {
        case UMA0:
            mount_point = "uma0";
            break;
        case UX0 :
            mount_point = "ux0";
            break;
        case XMC0 :
            mount_point = "xmc0";
            break;
        case IMC0 :
            mount_point = "imc0";
            break;
        case GRW0 :
            mount_point = "grw0";
            break;
        default:
            return "";
    }

    config_entry = gcd + mount_point;
    return config_entry;
}

const Setup Engine::calcSetup() {
	Setup setup = NO;

    _file = new File(SMGR_CONFIG_LOCALIZATION);
    if (!_file->checkFileExist()) {
        delete _file;
        return setup;
    }

    if (_file->findFileLine("GCD=uma0") > -1) {
        setup = UMA0;
    }
    else if (_file->findFileLine("GCD=ux0") > -1) {
        setup = UX0;
    }
    else if (_file->findFileLine("GCD=xmc0") > -1) {
        setup = XMC0;
    }
    else if (_file->findFileLine("GCD=imc0") > -1) {
        setup = IMC0;
    }
    else if (_file->findFileLine("GCD=grw0") > -1) {
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
	if (_file->checkFileExist() && _file->findFileLine(OLD_OLD_UMA0_LOCALIZATION) > 0) {
        return true;
    }
	delete _file;


	return false;
}

void Engine::reboot() {
	scePowerRequestColdReset();
}

void Engine::updateDb() {
    switch (_setup) {
        case UX0:
            sceIoRemove("uma0:/id.dat");
            break;
        case UMA0:
            sceIoRemove("ux0:/id.dat");
            break;
    }
}

void Engine::installChangelog() {
	sceIoMkdir("ux0:patch/SWITCHSDV/", 0777);//Create folders if it doesn't exist
	sceIoMkdir("ux0:patch/SWITCHSDV/sce_sys/", 0777);
	sceIoMkdir("ux0:patch/SWITCHSDV/sce_sys/changeinfo", 0777);

	_file = new File(CHANGELOG_LOCALIZATION);
	_file->copyFile(NEW_CHANGELOG_LOCALIZATION, NULL);
	delete _file;
}

void Engine::renameTaiUX0Folder(bool status) {

    //prevent h-encore problem with old Switch SDVita version
    SceUID folder = sceIoDopen("ux0:/taiOld");
    if (folder > -1) {
        sceIoRmdir("ux0:/taiOld");
    }
    sceIoDclose(folder);

    
    if (status) {

        folder = sceIoDopen("ux0:/tai");
        if (folder > -1) {
            sceIoRename("ux0:/tai", "ux0:/taiOld");
        }
        sceIoDclose(folder);

    }
    else {

        folder = sceIoDopen("ux0:/taiOld");
        if (folder > -1) {
            sceIoRename("ux0:/taiOld", "ux0:/tai");
        }
        sceIoDclose(folder);

    }

}