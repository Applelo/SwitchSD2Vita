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
    if (_setup == UMA0)
        return this->switch_to(UX0);
    else
        return this->switch_to(UMA0);
}


int Engine::switch_to(Setup mount_point) {


}



int Engine::uninstall() {

	//Remove StorageMgrPlugin
    _file = new File(CONFIG_LOCALIZATION);
    if (_file->findFileLine("\n" SMGR_LOCALIZATION) > 0) {
        _file->deleteFileLine("\n" SMGR_LOCALIZATION, _file->findFileLine("\n" SMGR_LOCALIZATION));
    }
    delete _file;

    _file = new File(SMGR_LOCALIZATION);
    if (_file->checkFileExist()) {
        _file->removeFile();
    }
    delete _file;

    this->renameTaiUX0Folder(false);


    //Uninstall old installation
	_file = new File(CONFIG_LOCALIZATION);
	if (_file->findFileLine("\n" OLD_UX0_LOCALIZATION) > 0) {
		_file->deleteFileLine("\n" OLD_UX0_LOCALIZATION, _file->findFileLine("\n" OLD_UX0_LOCALIZATION));
    }
    delete _file;

    _file = new File(OLD_UX0_LOCALIZATION);
    if (_file->checkFileExist()) {
        _file->removeFile();
    }
    delete _file;

	_file = new File(CONFIG_LOCALIZATION);
	if (_file->findFileLine("\n" OLD_UMA0_LOCALIZATION) > 0) {
		_file->deleteFileLine("\n" OLD_UMA0_LOCALIZATION, _file->findFileLine("\n" OLD_UMA0_LOCALIZATION));
    }
	delete _file;

    _file = new File(OLD_UMA0_LOCALIZATION);
    if (_file->checkFileExist()) {
        _file->removeFile();
    }
    delete _file;

	//Uninstall old old installation
	if (this->isOldInstallation()) {
		_file = new File(OLD_CONFIG_LOCALIZATION);
		if (_file->findFileLine("\n" OLD_OLD_UMA0_LOCALIZATION) > 0)
			_file->deleteFileLine("\n" OLD_OLD_UMA0_LOCALIZATION, _file->findFileLine("\n" OLD_OLD_UMA0_LOCALIZATION));
		delete _file;
		_file = new File(OLD_OLD_UMA0_LOCALIZATION);
		if (_file->checkFileExist())
			_file->removeFile();
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

const Setup Engine::calcSetup() {
	_setup = NO;


	return _setup;
}

const bool Engine::isOldInstallation() {

	_file = new File(OLD_UMA0_LOCALIZATION);
	if (_file->checkFileExist())
		return true;
	delete _file;

    _file = new File(OLD_UX0_LOCALIZATION);
    if (_file->checkFileExist())
        return true;
    delete _file;

    _file = new File(OLD_OLD_UMA0_LOCALIZATION);
    if (_file->checkFileExist())
        return true;
    delete _file;


	_file = new File(OLD_CONFIG_LOCALIZATION);
	if (_file->checkFileExist() && _file->findFileLine(OLD_UMA0_LOCALIZATION) > 0)
		return true;
	delete _file;


	return false;
}

void Engine::reboot() {
	scePowerRequestColdReset();
}

void Engine::installChangelog() {
	sceIoMkdir("ux0:patch/SWITCHSDV/", 0777);//Create folders for if it doesn't exist
	sceIoMkdir("ux0:patch/SWITCHSDV/sce_sys/", 0777);
	sceIoMkdir("ux0:patch/SWITCHSDV/sce_sys/changeinfo", 0777);

	_file = new File(CHANGELOG_LOCALIZATION);
	_file->copyFile(NEW_CHANGELOG_LOCALIZATION, NULL);
	delete _file;
}

void Engine::renameTaiUX0Folder(bool status) {
    if (status) {
        _file = new File("ux0:/tai");
        if (_file->checkFileExist())
            sceIoRename("ux0:/tai", "ux0:/taiOld");
    }
    else {
        _file = new File("ux0:/taiOld");
        if (_file->checkFileExist())
            sceIoRename("ux0:/taiOld", "ux0:/tai");
    }
    delete _file;
}