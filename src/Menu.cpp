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
	_log = "";
}

Menu::~Menu() {
}

void Menu::main() {

	//Display Txt
	for (int i = 0; i < _mainMenu.size(); i++)
		vita2d_pgf_draw_textf(_pgf, 50, 40 * (i+1), (_selector == (i+1)) ? WHITE : LIGHT_GREY, 1.2, "%s", _mainMenu[i].c_str());

	vita2d_pgf_draw_text(_pgf, 20, (40 * _selector), WHITE, 1.2, ">");

	vita2d_pgf_draw_textf(_pgf, 50, 300, (_result) ? GREEN : RED , 1.0,"%s", _log);


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

	if (_ctrl_press.buttons & SCE_CTRL_CROSS) {
		switch (_selector) {
	      case 1:
	        _step = SWITCH_TO_UXO;
	        break;

	      case 2:
	        _step = SWITCH_TO_UMAO;
	        break;

	      case 3:
	        _step = UNINSTALL;
	        break;

	       case 4:
	        _step = EXIT;
	        break;
	    }
	}

}

void Menu::switch_to_ux0() {
	_result = _engine->switch_to_ux0();
	if (_result)
		_log = "Success to switch to ux0";
	else
		_log = "Fail to switch to ux0. Use Uninstall option and retry.";

	_step = MAIN;
}

void Menu::switch_to_uma0() {
	_result = _engine->switch_to_uma0();
	if (_result)
		_log = "Success to switch to uma0";
	else
		_log = "Fail to switch to uma0. Use Uninstall option and retry.";
	_step = MAIN;
}

void Menu::uninstall() {
	_result = _engine->uninstall();
	if (_result)
		_log = "Success to uninstall files";
	else
		_log = "Fail to uninstall...";
	_step = MAIN;
}

//Setter
void Menu::setMenu(const Step step) {
	_step = step;
}

// Getter
const Step Menu::getMenu() const {
	return _step;
}
