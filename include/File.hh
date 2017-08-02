/*
**
** Made by Applelo (but a little)
**
*/

#ifndef FILE_HH_
# define FILE_HH_


# include "Utils.h"


class File {
private:
	const char *_file;

public:
	File(const char *file);
	virtual ~File();

	//Setter
	void setFile(const char *file);

	//Getter
	const char *getFile();

	int readFile(void *buf, int size);
	int writeFile(const void *buf, int size);
	int checkFileExist();
	int copyFile(const char *dst_path, FileProcessParam *param);

	int removeFile();


};
#endif /* !FILE_HH_ */
