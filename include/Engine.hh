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

# include "Utils.h"
# include "File.hh"

class Engine {
private:
	int _result;
	File* _file;
	Setup _setup;

public:
	Engine();
	virtual ~Engine();

	int auto_switch();
	int switch_to(Setup setup);
	void reboot();
	void updateDb(Setup setup);
	int uninstall();

	//Setter
	void setSetup(const Setup setup);

	// Getter
	const Setup getSetup();
    std::string getConfigEntryString(Setup setup);
    std::string getSetupString(Setup setup);

	const Setup calcSetup();
	const bool isOldInstallation();
	void installChangelog();
	void renameTaiUX0Folder(bool status);

};
#endif /* !ENGINE_HH_ */
