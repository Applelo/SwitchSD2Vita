/*
 **
 ** Made by MisterAlex
 ** And also Applelo (but a little)
 **
 */

# include "../include/Engine.hh"


Engine::Engine() {
}

Engine::~Engine() {
}

void Engine::switch_to_ux0() {

}

void Engine::switch_to_uma0() {

}

void Engine::uninstall() {

	_file = new File("ur0:tai/gamesd_ux0.skprx");
	if (_file->checkFileExist())
		_file->removeFile();

	_file = new File("ur0:tai/gamesd_uma0.skprx");
	if (_file->checkFileExist())
		_file->removeFile();

	_file = new File("ur0:/tai/config.txt");

}
