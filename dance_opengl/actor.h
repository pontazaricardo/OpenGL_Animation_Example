#include <vector>
#include "script.h"

using namespace std;


class Component{
public:
	/*
	 *	Member Attributes
	 */
	float Offset[3];
	float Pivot[3];
	int Rotate[3];
	
	float Size;
	float Color[3];
	float Scale[3];
	

	/*
	 *	Member Functions
	 */

	/*Constructor*/
	Component();
	/* Set the rotation angles */
	void setRotate(int x, int y, int z);
	/* Set the offset of this component respect to the root (mother component) */
	void setOffset(float x, float y, float z);
	/* Set the rotation pivot */
	void setPivot(float x, float y, float z);
	/* Set the size of this component */
	void setSize(float s);
	/* Set the color of this component */
	void setColor(float r, float g, float b);
	/* Set the scale of this component */
	void setScale(float x, float y, float z);
	/* reset the pose */
	void resetPose();
	/* apply rotation matrix with the setted pivot */
	void RotateByPivot();			
	/* apply scale -> translate -> color matrices */
	void ScaleTransColor();

	
};

static Component Head;

class Actor{
public:
	/* Constructor.		Actor appearance: 1 = male, 2 = female */
	Actor(int appearance = 1);
	
	/* Set the Starting Position  */
	void setPositionOffset(float x, float y, float z);
	/* Get the current pose , return as an array */
	vector<int> getPose();
	/* Set the current pose to the input parameter pose */
	void setPose(vector<int> &pose);
	/* Reset the current pose to the initial pose */
	void resetPose();
	/* Draw the actor using OpenGL with his/her current pose performed */
	void performPose();
	
	

	// Starting Position
	float PositionOffset[3] ;

	// Appearance: 1 = Male, 2 = Female
	int appearance;
	// Components that have no controller
	//Component Head;
	Component Bottom, Chest, LFist, RFist;
	Component FBottom;

	// Components that do have a controller
	Component Torso;
	Component LUpperArm, LForeArm, RUpperArm, RForeArm;
	Component LThigh, LLowerLeg, RThigh, RLowerLeg;
	Component LThenar, RThenar;	

	void crearMale(float x, float y, float z, float head1, float head2, float head3, float upperArm1, float upperArm2, float upperArm3, float foreArm1, float foreArm2, float foreArm3, float fist1, float fist2, float fist3, float chest1, float chest2, float chest3, float bottom1, float bottom2, float bottom3, float tight1, float tight2, float tight3, float lowerLeg1, float lowerLeg2, float lowerLeg3, float thenar1, float thenar2, float thenar3);
	void crearFemale(float x, float y, float z, float head1, float head2, float head3, float upperArm1, float upperArm2, float upperArm3, float foreArm1, float foreArm2, float foreArm3, float fist1, float fist2, float fist3, float chest1, float chest2, float chest3, float bottom1, float bottom2, float bottom3, float tight1, float tight2, float tight3, float lowerLeg1, float lowerLeg2, float lowerLeg3, float thenar1, float thenar2, float thenar3);
	static void cambiarColorRopa(int numero);
};