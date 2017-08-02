/*
**
** Made by Applelo
**
*/

#include "Engine.hh"

#ifndef MENU_HH_
# define MENU_HH_

typedef enum Step {
	MAIN = 0,
	SWITCH_TO_UXO,
	SWITCH_TO_UMAO,
	UNINSTALL,
	EXIT
} Step;



class Menu {
private:
	std::vector<std::string> _mainMenu = {
		"Switch to ux0",
		"Switch to uma0",
		"Uninstall",
		"Exit"
	};
	Step _step;
	SceCtrlData _ctrl_peek;
	SceCtrlData _ctrl_press;
	vita2d_pgf *_pgf;
	Engine* _engine;
	int _selector;
	int _result;
	char const *_log;


public:
	Menu();
	virtual ~Menu();

	//Getter
	const Step getMenu() const;

	//Setter
	void setMenu(const Step step);

	//Display Menu
	void main();
	void switch_to_ux0();
	void switch_to_uma0();
	void uninstall();

};

#endif /* !MENU_HH_ */
