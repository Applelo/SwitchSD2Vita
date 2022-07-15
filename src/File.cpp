/*
       VitaShell
       Copyright (C) 2015-2016, TheFloW
       This program is free software: you can redistribute it and/or modify
       it under the terms of the GNU General Public License as published by
       the Free Software Foundation, either version 3 of the License, or
       (at your option) any later version.
       This program is distributed in the hope that it will be useful,
       but WITHOUT ANY WARRANTY; without even the implied warranty of
       MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
       GNU General Public License for more details.
       You should have received a copy of the GNU General Public License
       along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
** Converted and add functions with passion by Applelo
*/

#include "../include/File.hh"
#include <strings.h>

File::File(const char* file) { _file = file; }

File::~File() {}

// Setter
void File::setFile(const char* file) { _file = file; }

// Getter
const char* File::getFile() { return _file; }

int File::readFile(void* buf, int size) {
  SceUID fd = sceIoOpen(_file, SCE_O_RDONLY, 0);
  if (fd < 0)
    return fd;

  int read = sceIoRead(fd, buf, size);

  sceIoClose(fd);
  return read;
}

int File::writeFile(const void* buf, int size) {
  SceUID fd = sceIoOpen(_file, SCE_O_WRONLY | SCE_O_CREAT | SCE_O_TRUNC, 0777);
  if (fd < 0)
    return fd;

  int written = sceIoWrite(fd, buf, size);

  sceIoClose(fd);
  return written;
}

int File::checkFileExist() {
  SceIoStat stat;
  memset(&stat, 0, sizeof(SceIoStat));

  return sceIoGetstat(_file, &stat) >= 0;
}

int File::copyFile(const char* dst_path, FileProcessParam* param) {
  // The source and destination paths are identical
  if (strcasecmp(_file, dst_path) == 0) {
    return -1;
  }

  // The destination is a subfolder of the source folder
  int len = strlen(_file);
  if (strncasecmp(_file, dst_path, len) == 0 &&
      (dst_path[len] == '/' || dst_path[len - 1] == '/')) {
    return -2;
  }

  SceUID fdsrc = sceIoOpen(_file, SCE_O_RDONLY, 0);
  if (fdsrc < 0)
    return fdsrc;

  SceUID fddst =
      sceIoOpen(dst_path, SCE_O_WRONLY | SCE_O_CREAT | SCE_O_TRUNC, 0777);
  if (fddst < 0) {
    sceIoClose(fdsrc);
    return fddst;
  }

  void* buf = malloc(TRANSFER_SIZE);

  while (1) {
    int read = sceIoRead(fdsrc, buf, TRANSFER_SIZE);

    if (read < 0) {
      free(buf);

      sceIoClose(fddst);
      sceIoClose(fdsrc);

      sceIoRemove(dst_path);

      return read;
    }

    if (read == 0)
      break;

    int written = sceIoWrite(fddst, buf, read);

    if (written < 0) {
      free(buf);

      sceIoClose(fddst);
      sceIoClose(fdsrc);

      sceIoRemove(dst_path);

      return written;
    }

    if (param) {
      if (param->value)
        (*param->value) += read;

      if (param->SetProgress)
        param->SetProgress(param->value ? *param->value : 0, param->max);

      if (param->cancelHandler && param->cancelHandler()) {
        free(buf);

        sceIoClose(fddst);
        sceIoClose(fdsrc);

        sceIoRemove(dst_path);

        return 0;
      }
    }
  }

  free(buf);

  // Inherit file stat
  SceIoStat stat;
  memset(&stat, 0, sizeof(SceIoStat));
  sceIoGetstatByFd(fdsrc, &stat);
  sceIoChstatByFd(fddst, &stat, 0x3B);

  sceIoClose(fddst);
  sceIoClose(fdsrc);

  return 1;
}

int File::getFileSize() {
  SceUID fd = sceIoOpen(_file, SCE_O_RDONLY, 0);
  if (fd < 0)
    return fd;

  int fileSize = sceIoLseek(fd, 0, SCE_SEEK_END);

  sceIoClose(fd);
  return fileSize;
}

int File::removeFile() {
  int removed = sceIoRemove(_file);
  if (removed < 0)
    return 0;
  return 1;
}

int File::findFileLine(const char* line) {
  int pos_search = 0;
  int pos_text = 0;
  int len_search = strlen(line);
  int len_text = this->getFileSize();
  char text[len_text];
  this->readFile(text, len_text);
  for (pos_text = 0; pos_text < len_text; ++pos_text) {
    if (text[pos_text] == line[pos_search]) {
      pos_search++;
      if (pos_search == len_search) {
        return pos_text;
      }
    } else {
      pos_text -= pos_search;
      pos_search = 0;
    }
  }
  return -1;
}

int File::addFileLine(const char* line, int position) {
  int size = this->getFileSize();
  if (size < 0)
    return 0;
  uint8_t* buffer = (uint8_t*)malloc(size);
  int len = this->readFile(buffer, size);
  buffer[len] = 0;
  std::string the_file = (const char*)buffer;
  free(buffer);
  the_file.insert(position + 1, line);
  int written = this->writeFile(the_file.c_str(), the_file.length());
  if (written < 0)
    return 0;
  return 1;
}
int File::deleteFileLine(const char* line, int position) {
  int size = this->getFileSize();
  int line_lenght = strlen(line);
  if (size < 0)
    return 0;
  uint8_t* buffer = (uint8_t*)malloc(size);
  int len = this->readFile(buffer, size);
  buffer[len] = 0;
  std::string the_file = (const char*)buffer;
  free(buffer);
  the_file.erase(position - line_lenght + 1, line_lenght);
  int written = this->writeFile(the_file.c_str(), the_file.length());
  if (written < 0)
    return 0;

  return 1;
}
