/*
**
** Made by MisterAlex
** And also Applelo (but a little)
**
*/

#ifndef ENGINE_HH_
# define ENGINE_HH_


# include "Utils.h"
# include "File.hh"

class Engine {
private:
	int _result;
	File* _file;

public:
	Engine();
	virtual ~Engine();

	int switch_to_ux0();
	int switch_to_uma0();
	int uninstall();

};
#endif /* !ENGINE_HH_ */
