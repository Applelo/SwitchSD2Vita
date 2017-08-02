/*
 **
 ** Made by Applelo
 **
 */

#include "../include/Menu.hh"

Menu::Menu() {
	_pgf = vita2d_load_default_pgf();
	_engine = new Engine();
	_step = MAIN;
	_selector = 1;
}

Menu::~Menu() {
}

void Menu::main() {

	//Display Txt
	for (int i = 0; i < _mainMenu.size(); i++) {
		vita2d_pgf_draw_textf(_pgf, 50, 40 * (i+1), (_selector == (i+1)) ? WHITE : LIGHT_GREY, 1.2, "%s", _mainMenu[i].c_str());
		if (_ctrl_press.buttons & SCE_CTRL_CROSS)
			_step = (Step) i;
	}

	vita2d_pgf_draw_text(_pgf, 20, (40 * _selector), WHITE, 1.2, ">");

	vita2d_pgf_draw_text(_pgf, 700, 450, WHITE, 1.3, "Switch SD2Vita");
	vita2d_pgf_draw_textf(_pgf, 900, 450, WHITE, 0.9,"%0.2f", VERSION_NUMBER);
	vita2d_pgf_draw_text(_pgf, 740, 500, WHITE, 1.0, "A Tuxbot123 idea\n\nDeveloped by Applelo");

	//Controls
	_ctrl_press = _ctrl_peek;
	sceCtrlPeekBufferPositive(0, &_ctrl_peek, 1);
	_ctrl_press.buttons = _ctrl_peek.buttons & ~_ctrl_press.buttons;

	if (_ctrl_press.buttons & SCE_CTRL_UP)
		_selector--;
	if (_ctrl_press.buttons & SCE_CTRL_DOWN)
		_selector++;

	if (_selector > 4)
		_selector = 1;
	if (_selector < 1)
		_selector = 4;

}

void Menu::switch_to_ux0() {

}

void Menu::switch_to_uma0() {

}

void Menu::uninstall() {

}

//Setter
void Menu::setMenu(const Step step) {
	_step = step;
}

// Getter
const Step Menu::getMenu() const {
	return _step;
}
