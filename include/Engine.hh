/*
**
** Made by Applelo
**
*/

#ifndef ENGINE_HH_
# define ENGINE_HH_

#include <jansson.h>

#include "map"
#include "Utils.h"
#include "File.hh"
#include "Config.hh"

typedef enum Setup {
	NO = 0,
	UX0,
	UMA0,
	XMC0,
	IMC0,
	GRW0
} Setup;

typedef enum Target {
    GCD = 0,
    MCD
} Target;

class Engine {
private:
	File* _file;
    std::map<Target, Setup> _setup;
	Config* _config;

public:
	Engine();
	virtual ~Engine();

	int auto_switch();
	int switch_to(Setup setup);
	void reboot();
	void updateDb(Setup setup);
	int uninstall();


	// Getter
	const Setup getSetup(Target target);
    std::string getConfigEntryString(Setup setup, Target target);
    std::string getSetupString(Setup setup);

	const Setup calcSetup(Target target);
	const bool isOldInstallation();
	void installChangelog();
	void renameTaiUX0Folder(bool status);

    void toggleAddMcdOption();
    bool getAddMcdOption();

};
#endif /* !ENGINE_HH_ */
