#ifndef UTIL_H
#define UTIL_H

#include <iostream>

#ifdef VISUAL_STUDIO
#include <windows.h>
#include <conio.h>
#else
#include <unistd.h>     /* usleep */
#include <termios.h>
#include <fcntl.h>
#endif

using namespace std;

#ifndef VISUAL_STUDIO
int _kbhit(void);
#endif

#endif
