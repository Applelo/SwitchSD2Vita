/*
 **
 ** Made by Applelo
 **
 */

# include "../include/Engine.hh"


Engine::Engine() {
}

Engine::~Engine() {
}

void Engine::switch_to_ux0() {
	_file = new File("app0:plugins/gamesd_ux0.skprx");
	_file->copyFile("ur0:tai/gamesd_ux0.skprx", NULL);
}

void Engine::switch_to_uma0() {
	_file = new File("app0:plugins/gamesd_uma0.skprx");
	_file->copyFile("ur0:tai/gamesd_uma0.skprx", NULL);

}

void Engine::uninstall() {

	_file = new File("ur0:tai/gamesd_ux0.skprx");
	if (_file->checkFileExist())
		_file->removeFile();

	_file = new File("ur0:tai/gamesd_uma0.skprx");
	if (_file->checkFileExist())
		_file->removeFile();

	//uint8_t *buffer = malloc(BIG_BUFFER_SIZE);

	//_file = new File("ur0:/tai/config.txt");
	//_file->readFile(buffer, BIG_BUFFER_SIZE);

}
