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
	_mustReboot = false;
	_oldInstall = _engine->isOldInstallation();
	_psvitaType  = sceKernelGetModel();
}

Menu::~Menu() {
}

void Menu::main() {
	std::string action = "";
	int option_position_y = (_engine->getSetup() == UMA0 || _engine->getSetup() == UX0) ? 1 : 0;
	//Display Txt
	for (int i = ((_engine->getSetup() == UMA0 || _engine->getSetup() == UX0) ? 0 : 1); i < _mainMenu.size(); i++) {
		switch (i) {
			case 0:
				vita2d_pgf_draw_textf(_pgf, 50, 40 * (i + option_position_y), (_selector == (i+1)) ? WHITE : LIGHT_GREY, 1.2, "%s (%s)", _mainMenu[i].c_str(), (_engine->getSetup() == UX0) ? "ux0 to uma0" : "uma0 to ux0");
				break;
		    case 1:
            case 2:
            case 3:
            case 4:
            case 5:
				if (_engine->getSetup() == NO) {
					action = _actionSuffix[1] + _mainMenu[i];
				} else {
					action = _actionSuffix[0] + _mainMenu[i];
				}
				vita2d_pgf_draw_textf(_pgf, 50, 40 * (i + option_position_y), (_selector == (i + 1)) ? WHITE : LIGHT_GREY, 1.2, "%s",
									  action.c_str());
				break;
			case 6:
				vita2d_pgf_draw_textf(_pgf, 50, 40 * (i + option_position_y), (_oldInstall) ? ((_selector == (i+1)) ? GREEN : LIGHT_GREEN) : ((_selector == (i+1)) ? WHITE : LIGHT_GREY), 1.2, "%s", _mainMenu[i].c_str());
				break;
			case 7:
				vita2d_pgf_draw_textf(_pgf, 50, 40 * (i + option_position_y), (_mustReboot) ? ((_selector == (i+1)) ? GREEN : LIGHT_GREEN) : ((_selector == (i+1)) ? WHITE : LIGHT_GREY) , 1.2, "%s", std::string (_mainMenu[i] + this->getVitaTypeString()).c_str());
				break;
			case 8:
				vita2d_pgf_draw_textf(_pgf, 50, 40 * (i + option_position_y), (_selector == (i+1)) ? WHITE : LIGHT_GREY, 1.2, "%s", _mainMenu[i].c_str());
				break;
		}
	}
	vita2d_pgf_draw_text(_pgf, 20, (40 * (_selector + option_position_y - 1)), WHITE, 1.2, ">");



	vita2d_pgf_draw_text(_pgf, 50, 420, GREEN, 1.0, std::string ("Installed in " + this->getSetupString(this->_engine->getSetup())).c_str());
    vita2d_pgf_draw_textf(_pgf, 50, 450, (_result) ? GREEN : RED , 1.0, "%s", _log.c_str());
	if (_oldInstall)
		vita2d_pgf_draw_text(_pgf, 50, 500, RED, 1.0, "An old installation detected.\nUse uninstall option to access to new features.");

	vita2d_pgf_draw_text(_pgf, 725, 40, WHITE, 1.3, "Switch SD2Vita");
	vita2d_pgf_draw_textf(_pgf, 820, 80, WHITE, 0.9,"Version %0.1f", VERSION_NUMBER);
	//vita2d_pgf_draw_text(_pgf, 650, 500, WHITE, 1.0, "A Tuxbot123 idea\n\nDeveloped by Applelo");

	//Controls
	_ctrl_press = _ctrl_peek;
	sceCtrlPeekBufferPositive(0, &_ctrl_peek, 1);
	_ctrl_press.buttons = _ctrl_peek.buttons & ~_ctrl_press.buttons;

	if (_ctrl_press.buttons & SCE_CTRL_UP)
		_selector--;
	if (_ctrl_press.buttons & SCE_CTRL_DOWN)
		_selector++;

	if (_selector > _mainMenu.size())
		_selector = ((_engine->getSetup() == UMA0 || _engine->getSetup() == UX0) ? 1 : 2);
	if (_selector < ((_engine->getSetup() == UMA0 || _engine->getSetup() == UX0) ? 1 : 2))
		_selector = _mainMenu.size();

	if (_ctrl_press.buttons & SCE_CTRL_CROSS) {
		switch (_selector) {
			case 1:
				_step = AUTO_SWITCH;
				break;
		  	case 2:
				_step = SWITCH_TO_UX0;
				break;
		  	case 3:
				_step = SWITCH_TO_UMA0;
				break;
			case 4:
				_step = SWITCH_TO_XMC0;
				break;
			case 5:
				_step = SWITCH_TO_IMC0;
				break;
			case 6:
				_step = SWITCH_TO_GRW0;
				break;
		  	case 7:
				_step = UNINSTALL;
				break;
		  	case 8:
				_engine->reboot();
				break;
		  	case 9:
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

void Menu::switch_to(Setup setup) {
	if (_oldInstall)
		_result = 0;
	else
		_result = _engine->switch_to(setup);

	if (_result) {
		_log = "Success to switch to " + this->getSetupString(setup) + ".\nYou must reboot your PSVita to apply change.";
		_mustReboot = true;
	}
	else
		_log = "Fail to switch to " + this->getSetupString(setup) + ".\nUse Uninstall option and retry.";
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

std::string Menu::getSetupString(Setup setup) {
    switch (setup) {
        case UX0:
            return "ux0";
        case UMA0:
            return "uma0";
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

std::string Menu::getVitaTypeString() {
    switch (_psvitaType) {
        case SCE_KERNEL_MODEL_VITATV:
            return "PSVita TV";
        default:
            return "PSVita";
    }
}