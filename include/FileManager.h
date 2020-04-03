#ifndef FILEMANAGER_H
#define FILEMANAGER_H

int ReadFromFile(const char *fileName, char *string, int strSize);
int WriteFromFile(const char *fileName, char *string);

#endif