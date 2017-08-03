
#define _TIME_INTERVAL_ 113		// time between two frames (milisecons)
#define _START_DELAY_   0		// time delay after animation (music) started
#define _MAX_FRAME_NUM_ 1000	// just for the size of the script
#define _SURROUNDING_START_ 229
#define _MUSIC_FILENAME_ "dance.wav"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "glut.h"
#include <vector>
#include <iostream>

#include "actor.h"
#include "music.h"

using namespace std;

/* Initial the OpenGL environment and all of the objects */
void init(void);

/* this is a callback function invoked when user resize the window */
void reshape(int w, int h);

/* this is a callback function invoked when glutPostRedisplay() is called */
void display(void);

/* this is a callback function invoked when any key is pressed */
void keyboard (unsigned char key, int x, int y);