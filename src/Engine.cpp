/*
 **
 ** Made by Applelo
 **
 */

# include "../include/Engine.hh"


Engine::Engine() {
	_setup = this->calcSetup();
}

Engine::~Engine() {
}

int Engine::switch_to_ux0() {
	//remove old installation if exist
	_file = new File(UMA0_LOCALIZATION);
	if (_file->checkFileExist())
		_file->removeFile();
	_file = new File(UMA0_CONFIG_LOCALIZATION);
	if (_file->findFileLine(UMA0_LOCALIZATION) > 0)
		_file->deleteFileLine("\nur0:tai/gamesd_uma0.skprx", _file->findFileLine("\nur0:tai/gamesd_uma0.skprx"));
	sceKernelDelayThread(10000);

	//copy ux0 plugin
	_file = new File(UX0_APP_LOCALIZATION);

	if (_file->checkFileExist()) {
		_result = _file->copyFile(UX0_LOCALIZATION, NULL);
		if (!_result)
			return 0;
	}
	else {
		return 0;
	}
	sceKernelDelayThread(10000);

	_file = new File(UX0_CONFIG_LOCALIZATION);
	if (_file->findFileLine("*KERNEL") < 0)
		return 0;
	if (_file->findFileLine(UX0_LOCALIZATION) > 0)
		return 0;

	_file->addFileLine("\nur0:tai/gamesd_ux0.skprx", _file->findFileLine("*KERNEL"));
	sceKernelDelayThread(10000);
	_setup = UX0;
	return 1;
}

int Engine::switch_to_uma0() {
	//remove old installation if exist
	_file = new File(UX0_LOCALIZATION);
	if (_file->checkFileExist())
		_file->removeFile();
	_file = new File(UX0_CONFIG_LOCALIZATION);
	if (_file->findFileLine(UX0_LOCALIZATION) > 0)
		_file->deleteFileLine("\nur0:tai/gamesd_ux0.skprx", _file->findFileLine("\nur0:tai/gamesd_ux0.skprx"));

	sceKernelDelayThread(10000);
	//copy uma0 plugin
	_file = new File(UMA0_APP_LOCALIZATION);

	if (_file->checkFileExist()) {
		_result = _file->copyFile(UMA0_LOCALIZATION, NULL);
		if (!_result)
			return 0;
	}
	else {
		return 0;
	}
	sceKernelDelayThread(10000);

	_file = new File(UMA0_CONFIG_LOCALIZATION);
	if (_file->findFileLine("*KERNEL") < 0)
		return 0;
	if (_file->findFileLine(UMA0_LOCALIZATION) > 0)
		return 0;

	_file->addFileLine("\nur0:tai/gamesd_uma0.skprx", _file->findFileLine("*KERNEL"));
	sceKernelDelayThread(10000);
	_setup = UMA0;
	return 1;
}

int Engine::uninstall() {
	//Remove plugin
	_file = new File(UX0_LOCALIZATION);
	if (_file->checkFileExist())
		_file->removeFile();
	_file = new File(UX0_CONFIG_LOCALIZATION);
	if (_file->findFileLine(UX0_LOCALIZATION) > 0)
		_file->deleteFileLine("\nur0:tai/gamesd_ux0.skprx", _file->findFileLine("\nur0:tai/gamesd_ux0.skprx"));

	sceKernelDelayThread(10000);

	_file = new File(UMA0_LOCALIZATION);
	if (_file->checkFileExist())
		_file->removeFile();
	_file = new File(UMA0_CONFIG_LOCALIZATION);
	if (_file->findFileLine(UMA0_LOCALIZATION) > 0)
		_file->deleteFileLine("\nur0:tai/gamesd_uma0.skprx", _file->findFileLine("\nur0:tai/gamesd_uma0.skprx"));

	sceKernelDelayThread(10000);
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

	_file = new File(UX0_LOCALIZATION);
	if (_file->checkFileExist())
		_setup = UX0;
	_file = new File(UMA0_LOCALIZATION);
	if (_file->checkFileExist())
		_setup = UMA0;

	return _setup;
}
