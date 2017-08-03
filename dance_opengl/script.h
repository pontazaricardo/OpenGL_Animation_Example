#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>

#define _TRASH_CAN_SIZE_	512
#define _CONTROLLER_NUM_	32


using namespace std;


class Script{
private:
	/* output file */
	ofstream ofile;
	/* input file */
	ifstream file;
	/* script file name */
	string fname;
	/* usage: script[frame index][controller index]*/
	vector<vector<int>> script;
	
	
public:
	/* Constructor */
	Script(char *filename){	fname = string(filename);	}
	/* Load script from file */
	bool Load();
	/* Append the input frame pose to the script file */
	bool Append2File(vector<int> pose);
	/* get the designated frame as an array */
	vector<int> &getFrame(int frameIdx);
	/* get the designated controller from the designated frame */
	int getController(int frameIdx, int ctrlIdx);
	/* returns total frame number */
	int frameNumber();
	
};


struct myColor{
	float r;
	float g;
	float b;
	float a;
};

class AnimationVariables{
private:
	double cameraSurroundStep;
	vector<pair<int,int>> camSurroundReg;
	vector<pair<int,int>> lightColorReg;
	
	vector<pair<int,int>> zoomReg;
	vector<pair<int,int>> zoomReg1;
	
	
public:
	vector<pair<int,int>> bgColorReg;
	vector<pair<int,int>> bgColorReg1;
	bool isRegisteredFrame(vector<pair<int,int>> reg);

	AnimationVariables();

	int actorIndex;		// index of the actor (who is now being editted)
	int frameIndex;		// index of the current frame
	bool zoom;			// flag for zoom in or zoom out
	bool isColorLight;  // flag for flash kind
	double viewAngle;	// direction of look
	myColor bgColor;	// Background Color
	float ltColor[4];	// Light Color


	void ResetVars();
	void CameraSurroundEffect();
	void BackgroundColorEffect();
	void BackgroundColorEffect1();
	void ZoomEffect();
	void ZoomEffect1();
	void LightEffect();
};

static AnimationVariables animation;
