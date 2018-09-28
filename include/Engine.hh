/*
**
** Made by Applelo
**
*/

#ifndef ENGINE_HH_
# define ENGINE_HH_

typedef enum Setup {
	NO = 0,
	UX0,
	UMA0,
	XMC0,
	IMC0,
	GRW0
} Setup;

#include <jansson.h>
# include "Utils.h"
# include "File.hh"
#include "Config.hh"

class Engine {
private:
	File* _file;
	Setup _setup;
	Config* _config;

public:
	Engine();
	virtual ~Engine();

	int auto_switch();
	int switch_to(Setup setup);
	void reboot();
	void updateDb(Setup setup);
	int uninstall();

	//Setter
	void setSetup(Setup setup);

	// Getter
	const Setup getSetup();
    std::string getConfigEntryString(Setup setup, int forceMcd = -1);
    std::string getSetupString(Setup setup);

	const Setup calcSetup();
	const bool isOldInstallation();
	void installChangelog();
	void renameTaiUX0Folder(bool status);

    void toggleAddMcdOption();
    bool getAddMcdOption();

};
#endif /* !ENGINE_HH_ */
