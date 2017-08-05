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

	int switch_to_ux0();
	int switch_to_uma0();
	int uninstall();

	//Setter
	void setSetup(const Setup setup);

	// Getter
	const Setup getSetup();

	const Setup calcSetup();

};
#endif /* !ENGINE_HH_ */
