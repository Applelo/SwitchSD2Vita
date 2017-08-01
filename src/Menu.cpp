/*
 **
 ** Made by Applelo
 ** And also MisterAlex (but a little)
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
	vita2d_pgf_draw_text(_pgf, 50, 40, (_selector == 1) ? WHITE : LIGHT_GREY, 1.2, "Switch to ux0:");
	vita2d_pgf_draw_text(_pgf, 50, 80, (_selector == 2) ? WHITE : LIGHT_GREY, 1.2, "Switch to uma0:");
	vita2d_pgf_draw_text(_pgf, 50, 120, (_selector == 3) ? WHITE : LIGHT_GREY, 1.2, "Uninstall");
	vita2d_pgf_draw_text(_pgf, 50, 160, (_selector == 4) ? WHITE : LIGHT_GREY, 1.2, "Exit");
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
