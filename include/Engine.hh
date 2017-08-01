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
	File* _file;

public:
	Engine();
	virtual ~Engine();

	void switch_to_ux0();
	void switch_to_uma0();
	void uninstall();



};
#endif /* !ENGINE_HH_ */
