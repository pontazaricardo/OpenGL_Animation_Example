#include "dance.h"

static vector<Actor> actor;
vector<Script*> script;
Music music(_MUSIC_FILENAME_);
int flag=0;
int numero=15500;

void init(void) 
{
	actor.push_back(Actor(1));						// Create a male actor
	script.push_back(new Script("actor1.txt"));		// Create his script
	script[0]->Load();								// Load his Script
	
	actor.push_back(Actor(2));						// Create a female actor
	script.push_back(new Script("actor2.txt"));		// Create her script
	script[1]->Load();								// Load her Script

	actor.push_back(Actor(3));						// Create a male actor
	script.push_back(new Script("actor3.txt"));		// Create his script
	script[2]->Load();								// Load his Script
	
	actor.push_back(Actor(4));						// Create a female actor
	script.push_back(new Script("actor4.txt"));		// Create her script
	script[3]->Load();								// Load her Script

	actor.push_back(Actor(5));						// Create a male actor
	script.push_back(new Script("actor5.txt"));		// Create his script
	script[4]->Load();								// Load his Script
	
	actor.push_back(Actor(6));						// Create a female actor
	script.push_back(new Script("actor6.txt"));		// Create her script
	script[5]->Load();								// Load her Script

	actor.push_back(Actor(7));						// Create a male actor
	script.push_back(new Script("actor7.txt"));		// Create his script
	script[6]->Load();								// Load his Script
	
	actor.push_back(Actor(8));						// Create a female actor
	script.push_back(new Script("actor8.txt"));		// Create her script
	script[7]->Load();								// Load her Script

	actor.push_back(Actor(9));						// Create a male actor
	script.push_back(new Script("actor9.txt"));		// Create his script
	script[8]->Load();								// Load his Script
		
	music.Open();									// Initial the music (not yet play)

	glClearColor (0.0, 0.0, 0.0, 0.0);    
	glShadeModel (GL_SMOOTH);

	// OpenGL Set light and material
	GLfloat mat_diffuse[]={0.7,0.7,0.7,1.0};
	GLfloat mat_ambient[]={0.7,0.7,0.7,1.0};
	GLfloat mat_specular[]={1.0,1.0,1.0,1.0};
	GLfloat mat_shininess[]={50.0};
	GLfloat light_ambient[]={0.2,0.2,0.2,1.0};
	GLfloat light_diffuse[]={1.0,1.0,1.0,1.0};
	GLfloat light_position[]={1.0,1.0,1.0,0.0};

	glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
	glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
	glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
	glLightfv(GL_LIGHT0,GL_POSITION,light_position);   
	glLightfv(GL_LIGHT0,GL_AMBIENT,light_ambient);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,light_diffuse);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	
}

//Reshape of the view window
void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
	glMatrixMode (GL_PROJECTION);

	glLoadIdentity ();
	if(!animation.zoom)
		glFrustum(-1.0,1.0,-1.0,1.0,1.2,100.0);
	else
		glFrustum(-1.0,1.0,-1.0,1.0,1.2,50.0);
	glMatrixMode(GL_MODELVIEW);
}


/*This is the baseroom for the models. If want to add extra elements, remember to:
1. Begin with a glPushMatrix();
2. End with a glPopMatrix();

Ex:
	glPushMatrix();
	glColor3f(0.862,0.541,0.07);
	glTranslatef (0.0, -1.5, 0.0);
	glScalef (44.0, 3.0, 44.0);
	glutSolidCube (1.0);
	glPopMatrix();
	glPushMatrix();
	glColor3f(1.0,1.0,0.0);
	glTranslatef (23.5, 7.0, 23.5);
	glScalef (3.0, 20.0, 3.0);
	glutSolidCube (1.0);
	glPopMatrix();

*/
void baseroom(void)
{
	glPushMatrix();    
	glColor3f(1.0,0.0,1.0);
	glTranslatef (0.0, -4.0, 0.0);
	glScalef (50.0, 2.0, 50.0);    
	glutSolidCube (1.0);	
	glPopMatrix();
}

//Display of the view
void display(void)
{
	glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity ();

	// Set viewpoint and direction
	if(!animation.zoom)
		gluLookAt(50*cos(animation.viewAngle),20,50*sin(animation.viewAngle),0.0,0.0,0.0,0.0,1.0,0.0);
	else
		gluLookAt(25*cos(animation.viewAngle),10,25*sin(animation.viewAngle),0.0,10.0,0.0,0.0,1.0,0.0);

	// Set the baseroom
	baseroom();

	// Set the actors
	for(unsigned int i = 0 ; i < actor.size() ; i++){
		actor[i].performPose();
	}

	glutSwapBuffers();
}

//Timer for animation.
void OnTimer1(int value){

	//Animation begings
	if(animation.frameIndex < script[0]->frameNumber()){
		// invoke the next frame
		if (flag==0){
			flag=1;
		}else{
			numero=113;
			flag=0;
		}
		glutTimerFunc(numero, OnTimer1, 1);
		//animation.BackgroundColorEffect();
	}
	//Animation ends
	else												
	{
		//Nothing happens if there is no animation.
	}
	glClearColor (animation.bgColor.r, animation.bgColor.g, animation.bgColor.b, animation.bgColor.a); 
	glutPostRedisplay();	
	return;
}

void OnTimer(int value)
{
	/* animation playing */
	if(animation.frameIndex < script[0]->frameNumber()){
		// invoke the next frame
		glutTimerFunc(_TIME_INTERVAL_, OnTimer, 1);

		// load the Current Frame Pose from the scripts to the actors  
		for(unsigned int i = 0 ; i < actor.size(); i++){
			actor[i].setPose(script[i]->getFrame(animation.frameIndex));
		}

		// set the effects
		animation.BackgroundColorEffect();
		animation.BackgroundColorEffect1();
		
		animation.CameraSurroundEffect();
		//animation.LightEffect();
		animation.ZoomEffect();
		animation.ZoomEffect1();

		animation.frameIndex++;

	}
	/* animation ends */
	else												
	{
		animation.ResetVars();
		music.Stop();
		
		for(unsigned int i = 0 ; i < actor.size(); i++){
			actor[i].resetPose();
		}
	}
	
	glLightfv(GL_LIGHT0, GL_DIFFUSE, animation.ltColor);
	glClearColor (animation.bgColor.r, animation.bgColor.g, animation.bgColor.b, animation.bgColor.a); 
	glutPostRedisplay();	
	return;
}

//Keyboard controls
/* NOTES:
1.	The original animation has 9 players. These can be added or removed easily, but if wanted to be modified, check the actor1.txt, ..., actor9.txt files 
	(they contain the coordinates of all the 3D objects in each frame of the animation).
2.	If you want to modify the way how one of the players move, modify the code in this function. 
3.	At the moment, any movement of the keyboard will affect all the players. If you want to modify an specific player, change the code
		for(contador=0;contador<9;contador++){
			actor[contador].Torso.Offset[0] += 1;
		}
	To
		actor[actorIdx].Torso.Offset[0] += 1;
	The way how to determine the index of each player is given in
		case '1': animation.actorIndex = 0;    break;
		case '2': animation.actorIndex = 1;    break;
		case '[': animation.actorIndex = 2;    break;
		case '{': animation.actorIndex = 3;    break;
		case ']': animation.actorIndex = 4;    break;
		case '}': animation.actorIndex = 5;    break;
		case '-': animation.actorIndex = 6;    break;
		case '_': animation.actorIndex = 7;    break;
		case '+': animation.actorIndex = 8;    break;
4. IMPORTANT: These are the keyboard controls:
	Animation:
		'=': Start the animation.
		';': Display the next frame pose
		':': Display the previous frame pose
		'/': Set the current status as a new key frame, and append the corresponding parameters to the original animation script.

	Body:
		'q': Move body along x-axis
		'a': Move body along y-axis
		'z': Move body along z-axis
		'w': Rotate body around x-axis
		's': Rotate body around y-axis
		'x': Rotate body around z-axis'
	Left Arm:
		'3': Rotate left upper arm around x-axis
		'4': Rotate left upper arm around y-axis
		'5': Rotate left upper arm around z-axis
		'e': Rotate left lower arm around x-axis
		'r': Rotate left lower arm around y-axis
		't': Rotate left lower arm around z-axis
	Right Arm:
		'd': Rotate right upper arm around x-axis
		'f': Rotate right upper arm around y-axis
		'g': Rotate right upper arm around z-axis
		'c': Rotate right lower arm around x-axis
		'v': Rotate right lower arm around y-axis
		'b': Rotate right lower arm around z-axis
	Left Leg:
		'6': Rotate left upper leg around x-axis
		'7': Rotate left upper leg around y-axis
		'8': Rotate left upper leg around z-axis
		'y': Rotate left lower leg around x-axis
		'u': Rotate left lower leg around y-axis
		'i': Rotate left lower leg around z-axis
	Right Leg:
		'h': Rotate right upper leg around x-axis
		'j': Rotate right upper leg around y-axis
		'k': Rotate right upper leg around z-axis
		'n': Rotate right lower leg around x-axis
		'm': Rotate right lower leg around y-axis
		',': Rotate right lower leg around z-axis
	Instep:
		'o': Rotate left instep
		'p': Rotate right instep
5.	By pressing and holding SHIFT while pressing the translation or rotation keys, the object will move in the opposite direction.
*/
void keyboard (unsigned char key, int x, int y)
{
	int actorIdx = animation.actorIndex;
	int contador=0;
	switch (key) {
		case '1': animation.actorIndex = 0;    break;
		case '2': animation.actorIndex = 1;    break;
		case '[': animation.actorIndex = 2;    break;
		case '{': animation.actorIndex = 3;    break;
		case ']': animation.actorIndex = 4;    break;
		case '}': animation.actorIndex = 5;    break;
		case '-': animation.actorIndex = 6;    break;
		case '_': animation.actorIndex = 7;    break;
		case '+': animation.actorIndex = 8;    break;

	/*	//EXAMPLE OF BODY TRANSLATION IN AN AXIS FOR ONE PLAYER
		case 'q':actor[actorIdx].Torso.Offset[0] += 1;		break;	 // x+
		case 'Q':actor[actorIdx].Torso.Offset[0] -= 1;		break;	 // x-
		case 'a':actor[actorIdx].Torso.Offset[1] += 1;		break;	 // y+
		case 'A':actor[actorIdx].Torso.Offset[1] -= 1;		break;	 // y-
		case 'z':actor[actorIdx].Torso.Offset[2] += 1;		break;	 // z+
		case 'Z':actor[actorIdx].Torso.Offset[2] -= 1;		break;	 // z-

		//EXAMPLE OF BODY ROTATION FOR ONE PLAYER
		case 'w': (actor[actorIdx].Torso.Rotate[0] += 5) %= 360;	break; // x+
		case 'W': (actor[actorIdx].Torso.Rotate[0] -= 5) %= 360;	break; // x-
		case 's': (actor[actorIdx].Torso.Rotate[1] += 5) %= 360;	break; // y+
		case 'S': (actor[actorIdx].Torso.Rotate[1] -= 5) %= 360;	break; // y-
		case 'x': (actor[actorIdx].Torso.Rotate[2] += 5) %= 360;	break; // z+
		case 'X': (actor[actorIdx].Torso.Rotate[2] -= 5) %= 360;	break; // z-
	*/

		//Body translation
		case 'q':for(contador=0;contador<9;contador++){
					actor[contador].Torso.Offset[0] += 1;
				}
				break;	 // x+
		case 'Q':for(contador=0;contador<9;contador++){
					actor[contador].Torso.Offset[0] -= 1;
				 }		
				 break;	 // x-
		case 'a':for(contador=0;contador<9;contador++){
					actor[contador].Torso.Offset[1] += 1;	
				 }	
				 break;	 // y+
		case 'A':for(contador=0;contador<9;contador++){
					actor[contador].Torso.Offset[1] -= 1;
				 }
				 break;	 // y-
		case 'z':for(contador=0;contador<9;contador++){
					actor[contador].Torso.Offset[2] += 1;	
				 }
				 break;	 // z+
		case 'Z':for(contador=0;contador<9;contador++){
					actor[contador].Torso.Offset[2] -= 1;	
				 }
				 break;	 // z-

		//Body Rotation
		case 'w': for(contador=0;contador<9;contador++){
					(actor[contador].Torso.Rotate[0] += 5) %= 360;	
				  }
				  break; // x+
		case 'W': for(contador=0;contador<9;contador++){
					(actor[contador].Torso.Rotate[0] -= 5) %= 360;	
				  }
				  break; // x-
		case 's': for(contador=0;contador<9;contador++){
					(actor[contador].Torso.Rotate[1] += 5) %= 360;	
				  }
				  break; // y+
		case 'S': for(contador=0;contador<9;contador++){
					(actor[contador].Torso.Rotate[1] -= 5) %= 360;
				  }
				  break; // y-
		case 'x': for(contador=0;contador<9;contador++){
					(actor[contador].Torso.Rotate[2] += 5) %= 360;	
				  }
				  break; // z+
		case 'X': for(contador=0;contador<9;contador++){
					(actor[contador].Torso.Rotate[2] -= 5) %= 360;
				  }
				  break; // z-

		/* //Uncomment for modifying ONE PLAYER only - one leg or one arm at a given time
		
		// Right Upper Arm Rotate
		case '3': (actor[actorIdx].RUpperArm.Rotate[0] += 5) %= 360;	break; // x+
		case '#': (actor[actorIdx].RUpperArm.Rotate[0] -= 5) %= 360;	break; // x-
		case '4': (actor[actorIdx].RUpperArm.Rotate[1] += 5) %= 360;	break; // y+
		case '$': (actor[actorIdx].RUpperArm.Rotate[1] -= 5) %= 360;	break; // y-
		case '5': (actor[actorIdx].RUpperArm.Rotate[2] += 5) %= 360;	break; // z+
		case '%': (actor[actorIdx].RUpperArm.Rotate[2] -= 5) %= 360;	break; // z-

		//Right Fore Arm Rotate
		case 'e': (actor[actorIdx].RForeArm.Rotate[0] += 5) %= 360;	break; // x+
		case 'E': (actor[actorIdx].RForeArm.Rotate[0] -= 5) %= 360;	break; // x-
		case 'r': (actor[actorIdx].RForeArm.Rotate[1] += 5) %= 360;	break; // y+
		case 'R': (actor[actorIdx].RForeArm.Rotate[1] -= 5) %= 360;	break; // y-
		case 't': (actor[actorIdx].RForeArm.Rotate[2] += 5) %= 360;	break; // z+
		case 'T': (actor[actorIdx].RForeArm.Rotate[2] -= 5) %= 360;	break; // z-

		//Left Upper Arm Rotate
		case 'd': (actor[actorIdx].LUpperArm.Rotate[0] += 5) %= 360;	break; // x+
		case 'D': (actor[actorIdx].LUpperArm.Rotate[0] -= 5) %= 360;	break; // x-
		case 'f': (actor[actorIdx].LUpperArm.Rotate[1] += 5) %= 360;	break; // y+
		case 'F': (actor[actorIdx].LUpperArm.Rotate[1] -= 5) %= 360;	break; // y-
		case 'g': (actor[actorIdx].LUpperArm.Rotate[2] += 5) %= 360;	break; // z+
		case 'G': (actor[actorIdx].LUpperArm.Rotate[2] -= 5) %= 360;	break; // z-

		//Left Fore Arm Rotate
		case 'c': (actor[actorIdx].LForeArm.Rotate[0] += 5) %= 360;	break; // x+
		case 'C': (actor[actorIdx].LForeArm.Rotate[0] -= 5) %= 360;	break; // x-
		case 'v': (actor[actorIdx].LForeArm.Rotate[1] += 5) %= 360;	break; // y+
		case 'V': (actor[actorIdx].LForeArm.Rotate[1] -= 5) %= 360;	break; // y-
		case 'b': (actor[actorIdx].LForeArm.Rotate[2] += 5) %= 360;	break; // z+
		case 'B': (actor[actorIdx].LForeArm.Rotate[2] -= 5) %= 360;	break; // z-

		//Right Thigh Rotate
		case '6': (actor[actorIdx].RThigh.Rotate[0] += 5) %= 360;	break; // x+
		case '^': (actor[actorIdx].RThigh.Rotate[0] -= 5) %= 360;	break; // x-
		case '7': (actor[actorIdx].RThigh.Rotate[1] += 5) %= 360;	break; // y+
		case '&': (actor[actorIdx].RThigh.Rotate[1] -= 5) %= 360;	break; // y-
		case '8': (actor[actorIdx].RThigh.Rotate[2] += 5) %= 360;	break; // z+
		case '*': (actor[actorIdx].RThigh.Rotate[2] -= 5) %= 360;	break; // z-

		//Right Thigh Rotate
		case 'y': (actor[actorIdx].RLowerLeg.Rotate[0] += 5) %= 360;	break; // x+
		case 'Y': (actor[actorIdx].RLowerLeg.Rotate[0] -= 5) %= 360;	break; // x-
		case 'u': (actor[actorIdx].RLowerLeg.Rotate[1] += 5) %= 360;	break; // y+
		case 'U': (actor[actorIdx].RLowerLeg.Rotate[1] -= 5) %= 360;	break; // y-
		case 'i': (actor[actorIdx].RLowerLeg.Rotate[2] += 5) %= 360;	break; // z+
		case 'I': (actor[actorIdx].RLowerLeg.Rotate[2] -= 5) %= 360;	break; // z-

		//Left Thigh Rotate
		case 'h': (actor[actorIdx].LThigh.Rotate[0] += 5) %= 360;	break; // x+
		case 'H': (actor[actorIdx].LThigh.Rotate[0] -= 5) %= 360;	break; // x-
		case 'j': (actor[actorIdx].LThigh.Rotate[1] += 5) %= 360;	break; // y+
		case 'J': (actor[actorIdx].LThigh.Rotate[1] -= 5) %= 360;	break; // y-
		case 'k': (actor[actorIdx].LThigh.Rotate[2] += 5) %= 360;	break; // z+
		case 'K': (actor[actorIdx].LThigh.Rotate[2] -= 5) %= 360;	break; // z-

		//Left Thigh Rotate
		case 'n': (actor[actorIdx].LLowerLeg.Rotate[0] += 5) %= 360;	break; // x+
		case 'N': (actor[actorIdx].LLowerLeg.Rotate[0] -= 5) %= 360;	break; // x-
		case 'm': (actor[actorIdx].LLowerLeg.Rotate[1] += 5) %= 360;	break; // y+
		case 'M': (actor[actorIdx].LLowerLeg.Rotate[1] -= 5) %= 360;	break; // y-
		case ',': (actor[actorIdx].LLowerLeg.Rotate[2] += 5) %= 360;	break; // z+
		case '<': (actor[actorIdx].LLowerLeg.Rotate[2] -= 5) %= 360;	break; // z-
		*/
		
		/* //Uncomment for modifying ONE PLAYER only - both legs or both arms at the same time
		
		//Right Upper Arm Rotate
		case '3':	(actor[actorIdx].RUpperArm.Rotate[0] += 5) %= 360;	//3
					(actor[actorIdx].LUpperArm.Rotate[0] += 5) %= 360;	//d
					break; // x+
		case '#':	(actor[actorIdx].RUpperArm.Rotate[0] -= 5) %= 360;	//-3
					(actor[actorIdx].LUpperArm.Rotate[0] -= 5) %= 360;	//-d
					break; // x-
		case '4':	(actor[actorIdx].RUpperArm.Rotate[1] += 5) %= 360;	//4
					(actor[actorIdx].LUpperArm.Rotate[1] -= 5) %= 360;	//-f
					break; // y+
		case '$':	(actor[actorIdx].RUpperArm.Rotate[1] -= 5) %= 360;	//-4
					(actor[actorIdx].LUpperArm.Rotate[1] += 5) %= 360;	//f
					break; // y-
		case '5':	(actor[actorIdx].RUpperArm.Rotate[2] += 5) %= 360;	//5
					(actor[actorIdx].LUpperArm.Rotate[2] -= 5) %= 360;	//-g
					break; // z+
		case '%':	(actor[actorIdx].RUpperArm.Rotate[2] -= 5) %= 360;	//-5
					(actor[actorIdx].LUpperArm.Rotate[2] += 5) %= 360;	//g
					break; // z-

		//Right Fore Arm Rotate
		case 'e':	(actor[actorIdx].RForeArm.Rotate[0] += 5) %= 360;	//e
					(actor[actorIdx].LForeArm.Rotate[0] += 5) %= 360;	//c
					break; // x+
		case 'E':	(actor[actorIdx].RForeArm.Rotate[0] -= 5) %= 360;	//-e
					(actor[actorIdx].LForeArm.Rotate[0] -= 5) %= 360;	//-c
					break; // x-
		case 'r':	(actor[actorIdx].RForeArm.Rotate[1] += 5) %= 360;	//r
					(actor[actorIdx].LForeArm.Rotate[1] -= 5) %= 360;	//-v
					break; // y+
		case 'R':	(actor[actorIdx].RForeArm.Rotate[1] -= 5) %= 360;	//-r
					(actor[actorIdx].LForeArm.Rotate[1] += 5) %= 360;	//v
					break; // y-
		case 't':	(actor[actorIdx].RForeArm.Rotate[2] += 5) %= 360;	//t
					(actor[actorIdx].LForeArm.Rotate[2] -= 5) %= 360;	//-b
					break; // z+
		case 'T':	(actor[actorIdx].RForeArm.Rotate[2] -= 5) %= 360;	//-t
					(actor[actorIdx].LForeArm.Rotate[2] += 5) %= 360;	//b
					break; // z-

		//Left Upper Arm Rotate
		case 'd':	(actor[actorIdx].LUpperArm.Rotate[0] += 5) %= 360;	//d
					(actor[actorIdx].RUpperArm.Rotate[0] += 5) %= 360;	//3
					break; // x+
		case 'D':	(actor[actorIdx].LUpperArm.Rotate[0] -= 5) %= 360;	//-d
					(actor[actorIdx].RUpperArm.Rotate[0] -= 5) %= 360;	//-3
					break; // x-
		case 'f':	(actor[actorIdx].LUpperArm.Rotate[1] += 5) %= 360;	//f
					(actor[actorIdx].RUpperArm.Rotate[1] -= 5) %= 360;	//-4
					break; // y+
		case 'F':	(actor[actorIdx].LUpperArm.Rotate[1] -= 5) %= 360;	//-f
					(actor[actorIdx].RUpperArm.Rotate[1] += 5) %= 360;	//4
					break; // y-
		case 'g':	(actor[actorIdx].LUpperArm.Rotate[2] += 5) %= 360;	//g
					(actor[actorIdx].RUpperArm.Rotate[2] -= 5) %= 360;	//-5
					break; // z+
		case 'G':	(actor[actorIdx].LUpperArm.Rotate[2] -= 5) %= 360;	//-g
					(actor[actorIdx].RUpperArm.Rotate[2] += 5) %= 360;	//5
					break; // z-

		//Left Fore Arm Rotate
		case 'c':	(actor[actorIdx].LForeArm.Rotate[0] += 5) %= 360; //c
					(actor[actorIdx].RForeArm.Rotate[0] += 5) %= 360;	//e
					break; // x+
		case 'C':	(actor[actorIdx].LForeArm.Rotate[0] -= 5) %= 360;	//-c
					(actor[actorIdx].RForeArm.Rotate[0] -= 5) %= 360;	//-e
					break; // x-
		case 'v':	(actor[actorIdx].LForeArm.Rotate[1] += 5) %= 360;	//v
					(actor[actorIdx].RForeArm.Rotate[1] -= 5) %= 360;	//-r
					break; // y+
		case 'V':	(actor[actorIdx].LForeArm.Rotate[1] -= 5) %= 360;	//-v
					(actor[actorIdx].RForeArm.Rotate[1] += 5) %= 360;	//r
					break; // y-
		case 'b':	(actor[actorIdx].LForeArm.Rotate[2] += 5) %= 360;	//b
					(actor[actorIdx].RForeArm.Rotate[2] -= 5) %= 360;	//-t
					break; // z+
		case 'B':	(actor[actorIdx].LForeArm.Rotate[2] -= 5) %= 360;	//-b
					(actor[actorIdx].RForeArm.Rotate[2] += 5) %= 360;	//t
					break; // z-

		//Right Thigh Rotate
		case '6':	(actor[actorIdx].RThigh.Rotate[0] += 5) %= 360;	//6
					(actor[actorIdx].LThigh.Rotate[0] += 5) %= 360;	//h
					break; // x+
		case '^':	(actor[actorIdx].RThigh.Rotate[0] -= 5) %= 360;	//-6
					(actor[actorIdx].LThigh.Rotate[0] -= 5) %= 360;	//-h
					break; // x-
		case '7':	(actor[actorIdx].RThigh.Rotate[1] += 5) %= 360;	//7
					(actor[actorIdx].LThigh.Rotate[1] -= 5) %= 360;	//-j
					break; // y+
		case '&':	(actor[actorIdx].RThigh.Rotate[1] -= 5) %= 360;	//-7
					(actor[actorIdx].LThigh.Rotate[1] += 5) %= 360;	//j
					break; // y-
		case '8':	(actor[actorIdx].RThigh.Rotate[2] += 5) %= 360;	//8
					(actor[actorIdx].LThigh.Rotate[2] -= 5) %= 360;	//-k
					break; // z+
		case '*':	(actor[actorIdx].RThigh.Rotate[2] -= 5) %= 360;	//-8
					(actor[actorIdx].LThigh.Rotate[2] += 5) %= 360;	//k
					break; // z-

		//Right Thigh Rotate
		case 'y':	(actor[actorIdx].RLowerLeg.Rotate[0] += 5) %= 360;	//y
					(actor[actorIdx].LLowerLeg.Rotate[0] += 5) %= 360;	//n
					break; // x+
		case 'Y':	(actor[actorIdx].RLowerLeg.Rotate[0] -= 5) %= 360;	//-y
					(actor[actorIdx].LLowerLeg.Rotate[0] -= 5) %= 360;	//-n
					break; // x-
		case 'u':	(actor[actorIdx].RLowerLeg.Rotate[1] += 5) %= 360;	//u
					(actor[actorIdx].LLowerLeg.Rotate[1] -= 5) %= 360;	//-m
					break; // y+
		case 'U':	(actor[actorIdx].RLowerLeg.Rotate[1] -= 5) %= 360;	//-u
					(actor[actorIdx].LLowerLeg.Rotate[1] += 5) %= 360;	//m
					break; // y-
		case 'i':	(actor[actorIdx].RLowerLeg.Rotate[2] += 5) %= 360;	//i
					(actor[actorIdx].LLowerLeg.Rotate[2] -= 5) %= 360;	//-,
					break; // z+
		case 'I':	(actor[actorIdx].RLowerLeg.Rotate[2] -= 5) %= 360;	//-i
					(actor[actorIdx].LLowerLeg.Rotate[2] += 5) %= 360;	//,
					break; // z-

		//Left Thigh Rotate
		case 'h':	(actor[actorIdx].LThigh.Rotate[0] += 5) %= 360;	//h
					(actor[actorIdx].RThigh.Rotate[0] += 5) %= 360;	//6
					break; // x+
		case 'H':	(actor[actorIdx].LThigh.Rotate[0] -= 5) %= 360;	//-h
					(actor[actorIdx].RThigh.Rotate[0] -= 5) %= 360;	//-6
					break; // x-
		case 'j':	(actor[actorIdx].LThigh.Rotate[1] += 5) %= 360;	//j
					(actor[actorIdx].RThigh.Rotate[1] -= 5) %= 360;	//-7
					break; // y+
		case 'J':	(actor[actorIdx].LThigh.Rotate[1] -= 5) %= 360;	//-j
					(actor[actorIdx].RThigh.Rotate[1] += 5) %= 360;	//7
					break; // y-
		case 'k':	(actor[actorIdx].LThigh.Rotate[2] += 5) %= 360;	//k
					(actor[actorIdx].RThigh.Rotate[2] -= 5) %= 360;	//-8
					break; // z+
		case 'K':	(actor[actorIdx].LThigh.Rotate[2] -= 5) %= 360;	//-k
					(actor[actorIdx].RThigh.Rotate[2] += 5) %= 360;	//8
					break; // z-

		//Left Thigh Rotate
		case 'n':	(actor[actorIdx].LLowerLeg.Rotate[0] += 5) %= 360;	//n
					(actor[actorIdx].RLowerLeg.Rotate[0] += 5) %= 360;	//y
					break; // x+
		case 'N':	(actor[actorIdx].LLowerLeg.Rotate[0] -= 5) %= 360;	//-n
					(actor[actorIdx].RLowerLeg.Rotate[0] -= 5) %= 360;	//-y
					break; // x-
		case 'm':	(actor[actorIdx].LLowerLeg.Rotate[1] += 5) %= 360;	//m
					(actor[actorIdx].RLowerLeg.Rotate[1] -= 5) %= 360;	//-u
					break; // y+
		case 'M':	(actor[actorIdx].LLowerLeg.Rotate[1] -= 5) %= 360;	//-m
					(actor[actorIdx].RLowerLeg.Rotate[1] += 5) %= 360;	//u
					break; // y-
		case ',':	(actor[actorIdx].LLowerLeg.Rotate[2] += 5) %= 360;	//,
					(actor[actorIdx].RLowerLeg.Rotate[2] -= 5) %= 360;	//-i
					break; // z+
		case '<':	(actor[actorIdx].LLowerLeg.Rotate[2] -= 5) %= 360;	//-,
					(actor[actorIdx].RLowerLeg.Rotate[2] += 5) %= 360;	//i
					break; // z-
		*/

		//  Move ALL THE PLAYERS limps at the same time - simetrical dance
		//	Right Upper Arm Rotate
		case '3':	for(contador=0;contador<9;contador++){
						(actor[contador].RUpperArm.Rotate[0] += 5) %= 360;	//3
						//(actor[contador].LUpperArm.Rotate[0] += 5) %= 360;	//d	
						////(actor[contador].LUpperArm.Rotate[0] -= 5) %= 360;	//-d
					}
					break; // x+
		case '#':	for(contador=0;contador<9;contador++){
						(actor[contador].RUpperArm.Rotate[0] -= 5) %= 360;	//-3
						//(actor[contador].LUpperArm.Rotate[0] -= 5) %= 360;	//-d
						////(actor[contador].LUpperArm.Rotate[0] += 5) %= 360;	//d	
					}
					break; // x-
		case '4':	for(contador=0;contador<9;contador++){
						(actor[contador].RUpperArm.Rotate[1] += 5) %= 360;	//4
						////(actor[contador].LUpperArm.Rotate[1] -= 5) %= 360;	//-f
					}
					break; // y+
		case '$':	for(contador=0;contador<9;contador++){
						(actor[contador].RUpperArm.Rotate[1] -= 5) %= 360;	//-4
						////(actor[contador].LUpperArm.Rotate[1] += 5) %= 360;	//f
					}
					break; // y-
		case '5':	for(contador=0;contador<9;contador++){
						(actor[contador].RUpperArm.Rotate[2] += 5) %= 360;	//5
						////(actor[contador].LUpperArm.Rotate[2] -= 5) %= 360;	//-g
					}
					break; // z+
		case '%':	for(contador=0;contador<9;contador++){
						(actor[contador].RUpperArm.Rotate[2] -= 5) %= 360;	//-5
						////(actor[contador].LUpperArm.Rotate[2] += 5) %= 360;	//g
					}
					break; // z-

		// Right Fore Arm Rotate
		case 'e':	for(contador=0;contador<9;contador++){
						(actor[contador].RForeArm.Rotate[0] += 5) %= 360;	//e
						////(actor[contador].LForeArm.Rotate[0] += 5) %= 360;	//c
					}
					break; // x+
		case 'E':	for(contador=0;contador<9;contador++){
						(actor[contador].RForeArm.Rotate[0] -= 5) %= 360;	//-e
						////(actor[contador].LForeArm.Rotate[0] -= 5) %= 360;	//-c
					}
					break; // x-
		case 'r':	for(contador=0;contador<9;contador++){
						(actor[contador].RForeArm.Rotate[1] += 5) %= 360;	//r
						////(actor[contador].LForeArm.Rotate[1] -= 5) %= 360;	//-v
					}
					break; // y+
		case 'R':	for(contador=0;contador<9;contador++){
						(actor[contador].RForeArm.Rotate[1] -= 5) %= 360;	//-r
						////(actor[contador].LForeArm.Rotate[1] += 5) %= 360;	//v
					}
					break; // y-
		case 't':	for(contador=0;contador<9;contador++){
						(actor[contador].RForeArm.Rotate[2] += 5) %= 360;	//t
						////(actor[contador].LForeArm.Rotate[2] -= 5) %= 360;	//-b
					}
					break; // z+
		case 'T':	for(contador=0;contador<9;contador++){
						(actor[contador].RForeArm.Rotate[2] -= 5) %= 360;	//-t
						////(actor[contador].LForeArm.Rotate[2] += 5) %= 360;	//b
					}
					break; // z-

		// Left Upper Arm Rotate
		case 'd':	for(contador=0;contador<9;contador++){
						(actor[contador].LUpperArm.Rotate[0] += 5) %= 360;	//d
						//(actor[contador].RUpperArm.Rotate[0] += 5) %= 360;	//3
						////(actor[contador].RUpperArm.Rotate[0] -= 5) %= 360;	//-3
					}
					break; // x+
		case 'D':	for(contador=0;contador<9;contador++){
						(actor[contador].LUpperArm.Rotate[0] -= 5) %= 360;	//-d
						//(actor[contador].RUpperArm.Rotate[0] -= 5) %= 360;	//-3
						////(actor[contador].RUpperArm.Rotate[0] += 5) %= 360;	//3
					}
					break; // x-
		case 'f':	for(contador=0;contador<9;contador++){
						(actor[contador].LUpperArm.Rotate[1] += 5) %= 360;	//f
						////(actor[contador].RUpperArm.Rotate[1] -= 5) %= 360;	//-4
					}
					break; // y+
		case 'F':	for(contador=0;contador<9;contador++){
						(actor[contador].LUpperArm.Rotate[1] -= 5) %= 360;	//-f
						////(actor[contador].RUpperArm.Rotate[1] += 5) %= 360;	//4
					}
					break; // y-
		case 'g':	for(contador=0;contador<9;contador++){
						(actor[contador].LUpperArm.Rotate[2] += 5) %= 360;	//g
					////	(actor[contador].RUpperArm.Rotate[2] -= 5) %= 360;	//-5
					}
					break; // z+
		case 'G':	for(contador=0;contador<9;contador++){
						(actor[contador].LUpperArm.Rotate[2] -= 5) %= 360;	//-g
						////(actor[contador].RUpperArm.Rotate[2] += 5) %= 360;	//5
					}
					break; // z-

		// Left Fore Arm Rotate
		case 'c':	for(contador=0;contador<9;contador++){
						(actor[contador].LForeArm.Rotate[0] += 5) %= 360; //c
					////	(actor[contador].RForeArm.Rotate[0] += 5) %= 360;	//e
					}
					break; // x+
		case 'C':	for(contador=0;contador<9;contador++){
						(actor[contador].LForeArm.Rotate[0] -= 5) %= 360;	//-c
						////(actor[contador].RForeArm.Rotate[0] -= 5) %= 360;	//-e
					}
					break; // x-
		case 'v':	for(contador=0;contador<9;contador++){
						(actor[contador].LForeArm.Rotate[1] += 5) %= 360;	//v
					////	(actor[contador].RForeArm.Rotate[1] -= 5) %= 360;	//-r
					}
					break; // y+
		case 'V':	for(contador=0;contador<9;contador++){
						(actor[contador].LForeArm.Rotate[1] -= 5) %= 360;	//-v
						////(actor[contador].RForeArm.Rotate[1] += 5) %= 360;	//r
					}
					break; // y-
		case 'b':	for(contador=0;contador<9;contador++){
						(actor[contador].LForeArm.Rotate[2] += 5) %= 360;	//b
						////(actor[contador].RForeArm.Rotate[2] -= 5) %= 360;	//-t
					}
					break; // z+
		case 'B':	for(contador=0;contador<9;contador++){
						(actor[contador].LForeArm.Rotate[2] -= 5) %= 360;	//-b
						////(actor[contador].RForeArm.Rotate[2] += 5) %= 360;	//t
					}
					break; // z-

		// Right Thigh Rotate
		case '6':	for(contador=0;contador<9;contador++){
						(actor[contador].RThigh.Rotate[0] += 5) %= 360;	//6
//						(actor[contador].LThigh.Rotate[0] += 5) %= 360;	//h
					}
					break; // x+
		case '^':	for(contador=0;contador<9;contador++){
						(actor[contador].RThigh.Rotate[0] -= 5) %= 360;	//-6
//						(actor[contador].LThigh.Rotate[0] -= 5) %= 360;	//-h
					}
					break; // x-
		case '7':	for(contador=0;contador<9;contador++){
						(actor[contador].RThigh.Rotate[1] += 5) %= 360;	//7
//						(actor[contador].LThigh.Rotate[1] -= 5) %= 360;	//-j
					}
					break; // y+
		case '&':	for(contador=0;contador<9;contador++){
						(actor[contador].RThigh.Rotate[1] -= 5) %= 360;	//-7
//						(actor[contador].LThigh.Rotate[1] += 5) %= 360;	//j
					}
					break; // y-
		case '8':	for(contador=0;contador<9;contador++){
						(actor[contador].RThigh.Rotate[2] += 5) %= 360;	//8
//						(actor[contador].LThigh.Rotate[2] -= 5) %= 360;	//-k
					}
					break; // z+
		case '*':	for(contador=0;contador<9;contador++){
						(actor[contador].RThigh.Rotate[2] -= 5) %= 360;	//-8
//						(actor[contador].LThigh.Rotate[2] += 5) %= 360;	//k
					}
					break; // z-

		// Right Thigh Rotate
		case 'y':	for(contador=0;contador<9;contador++){
						(actor[contador].RLowerLeg.Rotate[0] += 5) %= 360;	//y
//						(actor[contador].LLowerLeg.Rotate[0] += 5) %= 360;	//n
					}
					break; // x+
		case 'Y':	for(contador=0;contador<9;contador++){
						(actor[contador].RLowerLeg.Rotate[0] -= 5) %= 360;	//-y
//						(actor[contador].LLowerLeg.Rotate[0] -= 5) %= 360;	//-n
					}
					break; // x-
		case 'u':	for(contador=0;contador<9;contador++){
						(actor[contador].RLowerLeg.Rotate[1] += 5) %= 360;	//u
//						(actor[contador].LLowerLeg.Rotate[1] -= 5) %= 360;	//-m
					}
					break; // y+
		case 'U':	for(contador=0;contador<9;contador++){
						(actor[contador].RLowerLeg.Rotate[1] -= 5) %= 360;	//-u
//						(actor[contador].LLowerLeg.Rotate[1] += 5) %= 360;	//m
					}
					break; // y-
		case 'i':	for(contador=0;contador<9;contador++){
						(actor[contador].RLowerLeg.Rotate[2] += 5) %= 360;	//i
//						(actor[contador].LLowerLeg.Rotate[2] -= 5) %= 360;	//-,
					}
					break; // z+
		case 'I':	for(contador=0;contador<9;contador++){
						(actor[contador].RLowerLeg.Rotate[2] -= 5) %= 360;	//-i
//						(actor[contador].LLowerLeg.Rotate[2] += 5) %= 360;	//,
					}
					break; // z-

		// Left Thigh Rotate
		case 'h':	for(contador=0;contador<9;contador++){
						(actor[contador].LThigh.Rotate[0] += 5) %= 360;	//h
//						(actor[contador].RThigh.Rotate[0] += 5) %= 360;	//6
					}
					break; // x+
		case 'H':	for(contador=0;contador<9;contador++){
						(actor[contador].LThigh.Rotate[0] -= 5) %= 360;	//-h
//						(actor[contador].RThigh.Rotate[0] -= 5) %= 360;	//-6
					}
					break; // x-
		case 'j':	for(contador=0;contador<9;contador++){
						(actor[contador].LThigh.Rotate[1] += 5) %= 360;	//j
//						(actor[contador].RThigh.Rotate[1] -= 5) %= 360;	//-7
					}
					break; // y+
		case 'J':	for(contador=0;contador<9;contador++){
						(actor[contador].LThigh.Rotate[1] -= 5) %= 360;	//-j
//						(actor[contador].RThigh.Rotate[1] += 5) %= 360;	//7
					}
					break; // y-
		case 'k':	for(contador=0;contador<9;contador++){
						(actor[contador].LThigh.Rotate[2] += 5) %= 360;	//k
//						(actor[contador].RThigh.Rotate[2] -= 5) %= 360;	//-8
					}
					break; // z+
		case 'K':	for(contador=0;contador<9;contador++){
						(actor[contador].LThigh.Rotate[2] -= 5) %= 360;	//-k
//						(actor[contador].RThigh.Rotate[2] += 5) %= 360;	//8
					}
					break; // z-

		// Left Thigh Rotate
		case 'n':	for(contador=0;contador<9;contador++){
						(actor[contador].LLowerLeg.Rotate[0] += 5) %= 360;	//n
//						(actor[contador].RLowerLeg.Rotate[0] += 5) %= 360;	//y
					}
					break; // x+
		case 'N':	for(contador=0;contador<9;contador++){
						(actor[contador].LLowerLeg.Rotate[0] -= 5) %= 360;	//-n
//						(actor[contador].RLowerLeg.Rotate[0] -= 5) %= 360;	//-y
					}
					break; // x-
		case 'm':	for(contador=0;contador<9;contador++){
						(actor[contador].LLowerLeg.Rotate[1] += 5) %= 360;	//m
//						(actor[contador].RLowerLeg.Rotate[1] -= 5) %= 360;	//-u
					}
					break; // y+
		case 'M':	for(contador=0;contador<9;contador++){
						(actor[contador].LLowerLeg.Rotate[1] -= 5) %= 360;	//-m
//						(actor[contador].RLowerLeg.Rotate[1] += 5) %= 360;	//u
					}
					break; // y-
		case ',':	for(contador=0;contador<9;contador++){
						(actor[contador].LLowerLeg.Rotate[2] += 5) %= 360;	//,
//						(actor[contador].RLowerLeg.Rotate[2] -= 5) %= 360;	//-i
					}
					break; // z+
		case '<':	for(contador=0;contador<9;contador++){
						(actor[contador].LLowerLeg.Rotate[2] -= 5) %= 360;	//-,
//						(actor[contador].RLowerLeg.Rotate[2] += 5) %= 360;	//i
					}
					break; // z-


		// Right Thenar Rotate
		case 'o': (actor[actorIdx].RThenar.Rotate[0] += 5) %= 360;	break; // +
		case 'O': (actor[actorIdx].RThenar.Rotate[0] -= 5) %= 360;	break; // -

		// Left Thenar Rotate
		case 'p': (actor[actorIdx].LThenar.Rotate[0] += 5) %= 360;	break; // +
		case 'P': (actor[actorIdx].LThenar.Rotate[0] -= 5) %= 360;	break; // -

		//	Viewing Angle
		case '.': animation.viewAngle += 0.314;	break;
		case '>': animation.viewAngle -= 0.314;	break;

		//	Display next frame
		case ';':	
			if(animation.frameIndex+1 < script[0]->frameNumber())	animation.frameIndex++;
			for(unsigned int i = 0 ; i < actor.size(); i++){
				actor[i].setPose(script[i]->getFrame(animation.frameIndex));
			}
			break;

		//	Display previous frame
		case ':':
			if(animation.frameIndex-1 < script[0]->frameNumber())	animation.frameIndex--;
			for(unsigned int i = 0 ; i < actor.size(); i++){
				actor[i].setPose(script[i]->getFrame(animation.frameIndex));
			}
			break;
		 

		// Append the current pose to the script
		case '/':	
			for(unsigned int i = 0 ; i < script.size() ; i++){
			  script[i]->Append2File(actor[i].getPose());
			}
			break;

		// Start the animation
		case '=':
			music.Play();
			glutTimerFunc(_START_DELAY_, OnTimer, 1);
			//glutTimerFunc(_START_DELAY_, OnTimer1, 1);
			break;

		case 27:
			music.Close();
			exit(0);
			break;

		default:
			break;
	}
	glutPostRedisplay();
}

