/*
 **
 ** Made by Applelo
 **
 */

#include "../include/Menu.hh"

Menu::Menu() {
	_pgf = vita2d_load_default_pgf();
	_engine = new Engine();
	_engine->installChangelog();
	_step = MAIN;
	_selector = ((_engine->getSetup() == NO) ? 2 : 1);
	_log = "";
	_mustReboot = false;
	_oldInstall = _engine->isOldInstallation();
}

Menu::~Menu() {
}

void Menu::main() {
	std::string action = "";
	//Display Txt
	for (int i = ((_engine->getSetup() == NO) ? 1 : 0); i < _mainMenu.size(); i++) {
		switch (i) {
			case 0:
				vita2d_pgf_draw_textf(_pgf, 50, 40 * (i+1), (_selector == (i+1)) ? WHITE : LIGHT_GREY, 1.2, "%s (%s)", _mainMenu[i].c_str(), (_engine->getSetup() == UX0) ? "ux0 to uma0" : "uma0 to ux0");
				break;
		    case 1:
            case 2:
				if (_engine->getSetup() == NO) {
					action = _actionSuffix[1] + _mainMenu[i];
				} else {
					action = _actionSuffix[0] + _mainMenu[i];
				}
				vita2d_pgf_draw_textf(_pgf, 50, 40 * (i + 1), (_selector == (i + 1)) ? WHITE : LIGHT_GREY, 1.2, "%s",
									  action.c_str());
				break;
			case 3:
				vita2d_pgf_draw_textf(_pgf, 50, 40 * (i+1), (_oldInstall) ? ((_selector == (i+1)) ? GREEN : LIGHT_GREEN) : ((_selector == (i+1)) ? WHITE : LIGHT_GREY), 1.2, "%s", _mainMenu[i].c_str());
				break;
			case 4:
				vita2d_pgf_draw_textf(_pgf, 50, 40 * (i+1), (_mustReboot) ? ((_selector == (i+1)) ? GREEN : LIGHT_GREEN) : ((_selector == (i+1)) ? WHITE : LIGHT_GREY) , 1.2, "%s", _mainMenu[i].c_str());
				break;
			default:
				vita2d_pgf_draw_textf(_pgf, 50, 40 * (i+1), (_selector == (i+1)) ? WHITE : LIGHT_GREY, 1.2, "%s", _mainMenu[i].c_str());
				break;
		}
	}
	vita2d_pgf_draw_text(_pgf, 20, (40 * _selector), WHITE, 1.2, ">");

	vita2d_pgf_draw_textf(_pgf, 50, 300, (_result) ? GREEN : RED , 1.0, "%s", _log);

	switch (_engine->getSetup()) {
		case Setup::UX0:
			vita2d_pgf_draw_text(_pgf, 50, 450, GREEN, 1.0, "Installed in ux0:");
			break;
		case Setup::UMA0:
			vita2d_pgf_draw_text(_pgf, 50, 450, GREEN, 1.0, "Installed in uma0:");
			break;
        case Setup::XMC0:
            vita2d_pgf_draw_text(_pgf, 50, 450, GREEN, 1.0, "Installed in xmc0:");
            break;
        case Setup::IMC0:
            vita2d_pgf_draw_text(_pgf, 50, 450, GREEN, 1.0, "Installed in imc0:");
            break;
        case Setup::GRW0:
            vita2d_pgf_draw_text(_pgf, 50, 450, GREEN, 1.0, "Installed in grw0:");
            break;
		default:
			vita2d_pgf_draw_text(_pgf, 50, 450, WHITE, 1.0, "Not installed");
			break;
	}

	if (_oldInstall)
		vita2d_pgf_draw_text(_pgf, 50, 500, RED, 1.0, "An old installation detected.\nUse uninstall option to access to new features.");

	vita2d_pgf_draw_text(_pgf, 650, 450, WHITE, 1.3, "Switch SD2Vita");
	vita2d_pgf_draw_textf(_pgf, 850, 450, WHITE, 0.9,"%0.1f", VERSION_NUMBER);
	vita2d_pgf_draw_text(_pgf, 650, 500, WHITE, 1.0, "A Tuxbot123 idea\n\nDeveloped by Applelo & Yosh");

	//Controls
	_ctrl_press = _ctrl_peek;
	sceCtrlPeekBufferPositive(0, &_ctrl_peek, 1);
	_ctrl_press.buttons = _ctrl_peek.buttons & ~_ctrl_press.buttons;

	if (_ctrl_press.buttons & SCE_CTRL_UP)
		_selector--;
	if (_ctrl_press.buttons & SCE_CTRL_DOWN)
		_selector++;

	if (_selector > _mainMenu.size())
		_selector = ((_engine->getSetup() == NO) ? 2 : 1);
	if (_selector < ((_engine->getSetup() == NO) ? 2 : 1))
		_selector = _mainMenu.size();

	if (_ctrl_press.buttons & SCE_CTRL_CROSS) {
		switch (_selector) {
		  case 1:
			_step = AUTO_SWITCH;
			break;

		  case 2:
			_step = SWITCH_TO_UXO;
			break;

		  case 3:
			_step = SWITCH_TO_UMAO;
			break;

		  case 4:
			_step = UNINSTALL;
			break;

		  case 5:
			_engine->reboot();
			break;

		  case 6:
			_step = EXIT;
			break;
		}
	}

}

void Menu::auto_switch() {
	if (_oldInstall)
		_result = 0;
	else
		_result = _engine->auto_switch();

	if (_result == 1) {
		_log = "Sucess to switch !.\nYou must reboot your PSVita to apply change.";
	}
	else
		_log = "Fail to switch.\nUse uninstall option and retry.";

	_step = MAIN;
}

void Menu::switch_to_ux0() {
	if (_oldInstall)
		_result = 0;
	else
		_result = _engine->switch_to(UX0);

	if (_result) {
		_log = "Success to switch to ux0.\nYou must reboot your PSVita to apply change.";
		_mustReboot = true;
	}
	else
		_log = "Fail to switch to ux0.\nUse Uninstall option and retry.";

	_step = MAIN;
}

void Menu::switch_to_uma0() {
	if (_oldInstall)
		_result = 0;
	else
		_result = _engine->switch_to(UMA0);

	if (_result) {
		_log = "Success to switch to uma0.\nYou must reboot your PSVita to apply change.";
		_mustReboot = true;
	}
	else
		_log = "Fail to switch to uma0.\nUse Uninstall option and retry.";
	_step = MAIN;
}

void Menu::uninstall() {
	_result = _engine->uninstall();
	if (_result) {
		_log = "Success to uninstall files.\nYou must reboot your PSVita to apply change.";
		_mustReboot = true;
	}
	else
		_log = "Fail to uninstall...";
	if (_oldInstall)
		_oldInstall = _engine->isOldInstallation();
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
