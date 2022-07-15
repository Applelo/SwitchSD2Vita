/*
**
** Made by Applelo
**
*/

#include "Engine.hh"
#include <stdio.h>

#ifndef MENU_HH_
#define MENU_HH_

typedef enum Step {
  MAIN = 0,
  SWITCH_TO_UX0,
  SWITCH_TO_UMA0,
  SWITCH_TO_XMC0,
  SWITCH_TO_IMC0,
  SWITCH_TO_GRW0,
  UNINSTALL,
  EXIT,
  AUTO_SWITCH
} Step;

class Menu {
private:
  std::vector<std::string> _mainMenu = {"Auto switch",
                                        "to ux0",
                                        "to uma0",
                                        "to xmc0",
                                        "to imc0",
                                        "to grw0",
                                        "MCD config compatibility",
                                        "Uninstall",
                                        "Reboot your",
                                        "Exit"};
  std::vector<std::string> _actionSuffix = {"Switch", "Install"};
  Step _step;
  SceCtrlData _ctrl_peek;
  SceCtrlData _ctrl_press;
  vita2d_pgf *_pgf;
  Engine *_engine;
  int _selector;
  int _result;
  std::string _log;
  bool _mustReboot;
  bool _oldInstall;
  int _psvitaType;
  int _optionPositionY;

public:
  Menu();
  virtual ~Menu();

  // Getter
  const Step getMenu() const;
  std::string getVitaTypeString();

  // Display Menu
  void main();
  void auto_switch();
  void switch_to(Setup setup);
  void uninstall();
};

#endif /* !MENU_HH_ */
