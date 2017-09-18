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
	UMA0
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
	int switch_to_ux0();
	int switch_to_uma0();
	void reboot();
	int uninstall();

	//Setter
	void setSetup(const Setup setup);

	// Getter
	const Setup getSetup();

	const Setup calcSetup();
	const bool isOldInstallation();
	void installChangelog();
	void renameTaiUX0Folder(bool status);

};
#endif /* !ENGINE_HH_ */
