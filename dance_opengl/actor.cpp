#include "actor.h"
#include "glut.h"

Actor::Actor(int app){
	resetPose();
	appearance = app;
	//Head = new Component();
	switch(app){
		case 1:	// Male
			//10.f, 12.5f, 0.f
			crearMale(0.f, 10.f, 0.f, 1.f, 0.772f, 0.478f, 0.0,1.0,0.0, 1.0,0.772,0.478, 1.0,0.772,0.478, 0.0,1.0,0.0,0.0,0.0,1.0,0.0,0.0,1.0,0.0, 0.0, 1.0,1.0, 1.0, 1.0);
			break;
		case 2:	// Female
			//setPositionOffset(-10.f, 11.5f, 0.f);
			crearFemale(-10.f, 50.f, 0.f,1.f, 0.772f, 0.478f,1.0,0.772,0.478,1.0,0.772,0.478,1.0,0.772,0.478,1.0,0.0,0.0,1.0,0.0,0.0,1.0,0.772,0.478,1.0,0.772,0.478,1.0,1.0,1.0);
			break;
		case 3:	// Male
			//10.f, 12.5f, 0.f
			crearMale(0.f, 53.f, 0.f, 1.f, 0.772f, 0.478f, 1.0,1.0,0.0, 1.0,0.772,0.478, 1.0,0.772,0.478, 1.0,1.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0, 0.0, 0.0,1.0, 1.0, 1.0);
			break;
		case 4:	// Female
			//setPositionOffset(-10.f, 11.5f, 0.f);
			crearFemale(-10.f, 50.f, 0.f,1.f, 0.772f, 0.478f,1.0,0.772,0.478,1.0,0.772,0.478,1.0,0.772,0.478,1.0,1.0,0.0,1.0,1.0,0.0,1.0,0.772,0.478,1.0,0.772,0.478,1.0,1.0,1.0);
			break;
		case 5:	// Male
			//10.f, 12.5f, 0.f
			crearMale(0.f, 53.f, 0.f, 1.f, 0.772f, 0.478f, 1.0,1.0,1.0, 1.0,0.772,0.478, 1.0,0.772,0.478, 1.0,1.0,1.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0, 0.0, 0.0,0.0, 0.0, 0.0);
			break;
		case 6:	// Female
			//setPositionOffset(-10.f, 11.5f, 0.f);
			crearFemale(-10.f, 50.f, 0.f,1.f, 0.772f, 0.478f,1.0,0.772,0.478,1.0,0.772,0.478,1.0,0.772,0.478,0.0,0.0,1.0,0.0,0.0,1.0,1.0,0.772,0.478,1.0,0.772,0.478,1.0,1.0,1.0);
			break;
		case 7:	// Male
			//10.f, 12.5f, 0.f
			crearMale(0.f, 53.f, 0.f, 1.f, 0.772f, 0.478f, 1.0,1.0,1.0, 1.0,0.772,0.478, 1.0,0.772,0.478, 1.0,1.0,1.0,0.862,0.541,0.07,0.862,0.541,0.07,0.862,0.541,0.07,0.0, 0.0, 0.0);
			break;
		case 8:	// Female
			//setPositionOffset(-10.f, 11.5f, 0.f);
			crearFemale(-10.f, 50.f, 0.f,1.f, 0.772f, 0.478f,1.0,0.772,0.478,1.0,0.772,0.478,1.0,0.772,0.478,0.0,1.0,0.0,0.0,1.0,0.0,1.0,0.772,0.478,1.0,0.772,0.478,1.0,1.0,0.0);
			break;
		case 9:	// Male
			//10.f, 12.5f, 0.f
			crearMale(0.f, 53.f, 0.f, 1.f, 0.772f, 0.478f, 1.0,1.0,1.0, 1.0,0.772,0.478, 1.0,0.772,0.478,1.0,1.0,1.0,0.0,0.0,1.0,0.0,0.0,1.0,0.0, 0.0, 1.0,1.0, 1.0, 1.0);
			break;
	}
}



void Actor::setPositionOffset(float x, float y, float z){
	PositionOffset[0] = x;
	PositionOffset[1] = y; 
	PositionOffset[2] = z;
}

void Actor::resetPose(){
	
	this->Torso.resetPose();
	this->LForeArm.resetPose();
	this->LUpperArm.resetPose();
	this->RUpperArm.resetPose();
	this->RForeArm.resetPose();
	this->LThigh.resetPose();
	this->LLowerLeg.resetPose();
	this->RThigh.resetPose();
	this->RLowerLeg.resetPose();
	this->LThenar.resetPose();
	this->RThenar.resetPose();
}


void Actor::performPose(){
	glPushMatrix();   
		glTranslatef (PositionOffset[0], PositionOffset[1], PositionOffset[2]);     //	Actor Offset
		glTranslatef (Torso.Offset[0], Torso.Offset[1], Torso.Offset[2]);			//	Torso Translate
		Torso.RotateByPivot();		//	Torso Rotate

		//	Head
		glPushMatrix();					
			Head.ScaleTransColor();
			glutSolidSphere (Head.Size,10,10);	
		glPopMatrix();

		//	Bottom
		glPushMatrix();					
			Bottom.ScaleTransColor();
			glutSolidCube (Bottom.Size);	
		glPopMatrix();
		if(appearance == 2){
			glPushMatrix();					
				FBottom.ScaleTransColor();
				glutSolidSphere (FBottom.Size,10,10);	
			glPopMatrix();
		}

		//	Chest
		glPushMatrix();					
			Chest.ScaleTransColor();
			glutSolidCube (Chest.Size);	
		glPopMatrix();

		//	Right Arm
		glPushMatrix();					
			RUpperArm.RotateByPivot();		//	Right Upper Arm Rotate
			glPushMatrix();						//	Right Upper Arm
				RUpperArm.ScaleTransColor();	
				glutSolidCube (RUpperArm.Size);	
			glPopMatrix();
			RForeArm.RotateByPivot();	//	Right Fore Arm Rotate
			glPushMatrix();					//	Right Fore Arm
				RForeArm.ScaleTransColor();
				glutSolidCube (RForeArm.Size);	
			glPopMatrix();
			glPushMatrix();                //	Right Fist
				RFist.ScaleTransColor();
				glutSolidSphere (RFist.Size,10,10);	
			glPopMatrix();
		glPopMatrix();

		//	Left Arm
		glPushMatrix();					
			LUpperArm.RotateByPivot();		//	Left Upper Arm Rotate
			glPushMatrix();						//	Left Upper Arm
				LUpperArm.ScaleTransColor();	
				glutSolidCube (LUpperArm.Size);	
			glPopMatrix();
			LForeArm.RotateByPivot();	//	Left Fore Arm Rotate
			glPushMatrix();					//	Left Fore Arm
				LForeArm.ScaleTransColor();
				glutSolidCube (LForeArm.Size);	
			glPopMatrix();
			glPushMatrix();                //	Left Fist
				LFist.ScaleTransColor();
				glutSolidSphere (LFist.Size,10,10);	
			glPopMatrix();
		glPopMatrix();

		//	Right Leg
		glPushMatrix();					
			RThigh.RotateByPivot();		//	Right Thigh Rotate
			glPushMatrix();						//	Right Thigh
				RThigh.ScaleTransColor();	
				glutSolidCube (RThigh.Size);	
			glPopMatrix();
			RLowerLeg.RotateByPivot();	//	Right Lower Leg Rotate
			glPushMatrix();					//	Right Lower Leg
				RLowerLeg.ScaleTransColor();
				glutSolidCube (RLowerLeg.Size);	
			glPopMatrix();
			RThenar.RotateByPivot();	//	Right Fist Rotate
			glPushMatrix();                //	Right Fist
				RThenar.ScaleTransColor();
				glutSolidCube (RThenar.Size);
			glPopMatrix();
		glPopMatrix();

		//	Left Leg
		glPushMatrix();					
			LThigh.RotateByPivot();		//	Left Thigh Rotate
			glPushMatrix();						//	Left Thigh
				LThigh.ScaleTransColor();	
				glutSolidCube (LThigh.Size);	
			glPopMatrix();
			LLowerLeg.RotateByPivot();	//	Left Lower Leg Rotate
			glPushMatrix();					//	Left Lower Leg
				LLowerLeg.ScaleTransColor();
				glutSolidCube (LLowerLeg.Size);	
			glPopMatrix();
			LThenar.RotateByPivot();	//	Left Fist Rotate
			glPushMatrix();                //	Left Fist
				LThenar.ScaleTransColor();
				glutSolidCube (LThenar.Size);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}


void Actor::setPose(vector<int> &pose){
	int i, j = 0;

	for(i=0 ; i<3; ++i) { Torso.Offset[i]		= pose[j++]; }
	for(i=0 ; i<3; ++i) { Torso.Rotate[i]		= pose[j++]; }
	for(i=0 ; i<3; ++i) { RUpperArm.Rotate[i]	= pose[j++]; }
	for(i=0 ; i<3; ++i) { RForeArm.Rotate[i]	= pose[j++]; }
	for(i=0 ; i<3; ++i) { LUpperArm.Rotate[i]	= pose[j++]; }
	for(i=0 ; i<3; ++i) { LForeArm.Rotate[i]	= pose[j++]; }
	for(i=0 ; i<3; ++i) { RThigh.Rotate[i]		= pose[j++]; }
	for(i=0 ; i<3; ++i) { RLowerLeg.Rotate[i]	= pose[j++]; }
	for(i=0 ; i<3; ++i) { LThigh.Rotate[i]		= pose[j++]; }
	for(i=0 ; i<3; ++i) { LLowerLeg.Rotate[i]	= pose[j++]; }

	RThenar.Rotate[0] = pose[j++];
	LThenar.Rotate[0] = pose[j++];
}

vector<int> Actor::getPose(){
	vector<int> pose;
	int i;
	for(i=0 ; i<3; ++i) { pose.push_back(Torso.Offset[i]);		}
	for(i=0 ; i<3; ++i) { pose.push_back(Torso.Rotate[i]);		}
	for(i=0 ; i<3; ++i) { pose.push_back(RUpperArm.Rotate[i]);	}
	for(i=0 ; i<3; ++i) { pose.push_back(RForeArm.Rotate[i]);	}
	for(i=0 ; i<3; ++i) { pose.push_back(LUpperArm.Rotate[i]);	}
	for(i=0 ; i<3; ++i) { pose.push_back(LForeArm.Rotate[i]);	}
	for(i=0 ; i<3; ++i) { pose.push_back(RThigh.Rotate[i]);		}
	for(i=0 ; i<3; ++i) { pose.push_back(RLowerLeg.Rotate[i]);	}
	for(i=0 ; i<3; ++i) { pose.push_back(LThigh.Rotate[i]);		}
	for(i=0 ; i<3; ++i) { pose.push_back(LLowerLeg.Rotate[i]);	}

	pose.push_back(RThenar.Rotate[0]);
	pose.push_back(LThenar.Rotate[0]);
	return pose;
}
Component::Component(){
	setRotate(0.f, 0.f, 0.f);
	setOffset(0.f, 0.f, 0.f);
	setPivot(0.f, 0.f, 0.f);
	setSize(1);
	setColor(1.f, 1.f, 1.f);
	setScale(1.f, 1.f, 1.f);
}
void Component::setRotate(int x, int y, int z){
	Rotate[0] = x;
	Rotate[1] = y;
	Rotate[2] = z;
}
void Component::setOffset(float x, float y, float z){
	Offset[0] = x;
	Offset[1] = y;
	Offset[2] = z;
}
void Component::setPivot(float x, float y, float z){
	Pivot[0] = x;
	Pivot[1] = y;
	Pivot[2] = z;
}
void Component::setSize(float s) { Size = s; }
void Component::setColor(float r, float g, float b){
	Color[0] = r;
	Color[1] = g;
	Color[2] = b;
}
void Component::setScale(float x, float y, float z){
	Scale[0] = x;
	Scale[1] = y;
	Scale[2] = z;
}
void Component::resetPose(){
	this->setRotate(0.f, 0.f, 0.f);
}
void Component::RotateByPivot(){
	glTranslatef (Pivot[0], Pivot[1], Pivot[2]);
	glRotatef ((GLfloat) Rotate[0], 1.0, 0.0, 0.0); 
	glRotatef ((GLfloat) Rotate[1], 0.0, 1.0, 0.0);
	glRotatef ((GLfloat) Rotate[2], 0.0, 0.0, 1.0);
	glTranslatef (-Pivot[0], -Pivot[1], -Pivot[2]);
}
void Component::ScaleTransColor(){
	glColor3f(Color[0], Color[1], Color[2]);   
	glTranslatef (Offset[0], Offset[1], Offset[2]);
	glScalef (Scale[0], Scale[1], Scale[2]);   
}

void Actor::cambiarColorRopa(int numero){
	if(!(animation.isRegisteredFrame(animation.bgColorReg))){
		if (numero==1){
		numero=0;
		Head.setColor(1.f, 0.772f, 0.478f);
	}else{
		numero=1;
		Head.setColor(0.f,0.f,0.f);
	}
	//animation.BackgroundColorEffect();
	}
	glutTimerFunc(100,Actor::cambiarColorRopa,numero);
    glutPostRedisplay();
}


void Actor::crearMale(float x, float y, float z, float head1, float head2, float head3, float upperArm1, float upperArm2, float upperArm3, float foreArm1, float foreArm2, float foreArm3, float fist1, float fist2, float fist3, float chest1, float chest2, float chest3, float bottom1, float bottom2, float bottom3, float tight1, float tight2, float tight3, float lowerLeg1, float lowerLeg2, float lowerLeg3, float thenar1, float thenar2, float thenar3){
			setPositionOffset(x,y,z);
			//glutTimerFunc(100,cambiarColorRopa,0);
			//	Head
			//Head.setColor(1.f, 0.772f, 0.478f);
			Head.setColor(head1, head2, head3);
			Head.setOffset(0.0, 3.5, 0.0);
			Head.setSize(1.2f);
			
			//	Bottom
			//Bottom.setColor(0.0,1.0,0.0); 
			Bottom.setColor(bottom1, bottom2, bottom3); 
			Bottom.setOffset(0.0, -3.0, 0.0);
			Bottom.setScale(3.0, 3.0, 2.0);
			Bottom.setSize(1.f);
			
			//	Chest
			//Chest.setColor(1.0,1.0,1.0);
			Chest.setColor(chest1, chest2, chest3);
			Chest.setScale(3.0, 3.0, 2.0);  
			Chest.setSize(1.f);
			
			//	Right Upper Arm
			RUpperArm.setPivot(-2.5, 1.0, 0.0); 
//			RUpperArm.setColor(1.0,1.0,1.0);
			RUpperArm.setColor(upperArm1, upperArm2, upperArm3);
			RUpperArm.setOffset(-2.5, 0.0, 0.0);
			RUpperArm.setScale(1.2, 3.0, 1.2);    
			RUpperArm.setSize(1.0);	
			
			//	Right Fore Arm
			RForeArm.setPivot(-2.5, -2.0, 0.0); 
			//RForeArm.setColor(1.0,0.772,0.478);
			RForeArm.setColor(foreArm1, foreArm2, foreArm3);
			RForeArm.setOffset(-2.5, -3.0, 0.0);
			RForeArm.setScale(1.0, 3.0, 1.0);     
			RForeArm.setSize(1.0);	
			
			// Right Fist
			//RFist.setColor(1.0,0.772,0.478);
			RFist.setColor(fist1, fist2, fist3);
			RFist.setOffset(-2.5, -5.0, 0.0);         
			RFist.setSize(0.8);
			
			//	Left Upper Arm
			LUpperArm.setPivot(2.5, 1.0, 0.0); 
			//LUpperArm.setColor(1.0,1.0,1.0);   
			LUpperArm.setColor(upperArm1, upperArm2, upperArm3);   
			LUpperArm.setOffset(2.5, 0.0, 0.0);
			LUpperArm.setScale(1.2, 3.0, 1.2);    
			LUpperArm.setSize(1.0);	
			
			//	Left Fore Arm
			LForeArm.setPivot(2.5, -2.0, 0.0); 
			//LForeArm.setColor(1.0,0.772,0.478);
			LForeArm.setColor(foreArm1, foreArm2, foreArm3);
			LForeArm.setOffset(2.5, -3.0, 0.0);
			LForeArm.setScale(1.0, 3.0, 1.0);     
			LForeArm.setSize(1.0);	
			
			//	Left Fist
			//LFist.setColor(1.0,0.772,0.478);
			LFist.setColor(fist1, fist2, fist3);
			LFist.setOffset(2.5, -5.0, 0.0);         
			LFist.setSize(0.8);

			//	Right Thigh
			RThigh.setPivot(-1.0, -4.0, 0.0); 
			//RThigh.setColor(0.0,1.0,0.0);
			RThigh.setColor(tight1, tight2, tight3);
			RThigh.setOffset(-1.0, -6.25, 0.0);
			RThigh.setScale(1.5, 3.5, 2.0);    
			RThigh.setSize(1.0);	
			
			// Right Lower Leg
			RLowerLeg.setPivot(-1.0, -7.0, 0.0); 
//			RLowerLeg.setColor(0.0, 0.0, 0.0);   
			RLowerLeg.setColor(lowerLeg1, lowerLeg2, lowerLeg3);   
			RLowerLeg.setOffset(-1.0, -9.75, 0.0);
			RLowerLeg.setScale(1.5, 3.5, 2.0);   
			RLowerLeg.setSize(1.0);	

			// Right Thenar
			RThenar.setPivot(-1.0, -12.0, 0.5);
//			RThenar.setColor(0.0, 0.0, 0.0);   
			RThenar.setColor(thenar1, thenar2, thenar3);   
			RThenar.setOffset(-1.0, -12.0, -0.5);
			RThenar.setScale(1.5, 1.0, 3.0);  
			RThenar.setSize(1.0);

			// Left Thigh
			LThigh.setPivot(1.0, -4.0, 0.0); 
//			LThigh.setColor(0.0,0.0,0.0);
			LThigh.setColor(tight1, tight2, tight3);
			LThigh.setOffset(1.0, -6.25, 0.0);
			LThigh.setScale(1.5, 3.5, 2.0);    
			LThigh.setSize(1.0);	
			
			// Left Lower Leg
			LLowerLeg.setPivot(1.0, -7.0, 0.0); 
//			LLowerLeg.setColor(0.0, 1.0, 0.0);   
			LLowerLeg.setColor(lowerLeg1, lowerLeg2, lowerLeg3);   
			LLowerLeg.setOffset(1.0, -9.75, 0.0);
			LLowerLeg.setScale(1.5, 3.5, 2.0);   
			LLowerLeg.setSize(1.0);	

			//	Left Thenar
			LThenar.setPivot(1.0, -12.0, 0.5);
//			LThenar.setColor(0.0, 0.0, 0.0);   
			LThenar.setColor(thenar1, thenar2, thenar3);   
			LThenar.setOffset(1.0, -12.0, -0.5);
			LThenar.setScale(1.5, 1.0, 3.0);  
			LThenar.setSize(1.0);
}

void Actor::crearFemale(float x, float y, float z, float head1, float head2, float head3, float upperArm1, float upperArm2, float upperArm3, float foreArm1, float foreArm2, float foreArm3, float fist1, float fist2, float fist3, float chest1, float chest2, float chest3, float bottom1, float bottom2, float bottom3, float tight1, float tight2, float tight3, float lowerLeg1, float lowerLeg2, float lowerLeg3, float thenar1, float thenar2, float thenar3){
			setPositionOffset(x,y,z);
			
			// Head
			//Head.setColor(1.f, 0.772f, 0.478f);
			Head.setColor(head1, head2, head3);
			Head.setOffset(0.0, 2.7, 0.0);
			Head.setSize(1.0f);
			
			// Bottom
			//Bottom.setColor(1.0,0.0,0.0); 
			Bottom.setColor(bottom1, bottom2, bottom3); 
			Bottom.setOffset(0.0, -2.625, 0.0);
			Bottom.setScale(2.2, 2.625, 1.6); 
			Bottom.setSize(1.f);
			//FBottom.setColor(1.0,0.0,0.0);
			FBottom.setColor(bottom1, bottom2, bottom3);
			FBottom.setOffset(0.0, -4.2, 0.0);  
			FBottom.setSize(0.7f);
			
			// Chest
			//Chest.setColor(1.0,0.0,0.0);
			Chest.setColor(chest1, chest2, chest3);
			Chest.setScale(2.625, 2.625, 1.8);    
			Chest.setSize(1.f);
			
			// Right Upper Arm
			RUpperArm.setPivot(-2.0, 1.0, 0.0); 
			//RUpperArm.setColor(1.0,0.772,0.478);   
			RUpperArm.setColor(upperArm1, upperArm2, upperArm3);   
			RUpperArm.setOffset(-2.0, 0.0, 0.0);
			RUpperArm.setScale(0.8, 2.625, 1.0);  
			RUpperArm.setSize(1.0);	
			
			// Right Fore Arm
			RForeArm.setPivot(-2.0, -2.0, 0.0); 
//			RForeArm.setColor(1.0,0.772,0.478);
			RForeArm.setColor(foreArm1, foreArm2, foreArm3);
			RForeArm.setOffset(-2.0, -2.625, 0.0);
			RForeArm.setScale(0.7, 2.625, 0.9);     
			RForeArm.setSize(1.0);	
			
			// Right Fist
//			RFist.setColor(1.0,0.772,0.478);
			RFist.setColor(fist1, fist2, fist3);
			RFist.setOffset(-2.0, -5.0, 0.0);         
			RFist.setSize(0.7);
			
			// Left Upper Arm
			LUpperArm.setPivot(2.0, 1.0, 0.0); 
			//LUpperArm.setColor(1.0,0.772,0.478);
			LUpperArm.setColor(upperArm1, upperArm2, upperArm3);
			LUpperArm.setOffset(2.0, 0.0, 0.0);
			LUpperArm.setScale(0.8, 2.625, 1.0);    
			LUpperArm.setSize(1.0);	
			
			// Left Fore Arm
			LForeArm.setPivot(2.0, -2.0, 0.0); 
			//LForeArm.setColor(1.0,0.772,0.478);
			LForeArm.setColor(foreArm1, foreArm2, foreArm3);
			LForeArm.setOffset(2.0, -2.625, 0.0);
			LForeArm.setScale(0.7, 2.625, 0.9);     
			LForeArm.setSize(1.0);	
			
			// Left Fist
			//LFist.setColor(1.0,0.772,0.478);
			LFist.setColor(fist1, fist2, fist3);
			LFist.setOffset(2.0, -5.0, 0.0);         
			LFist.setSize(0.7);

			// Right Thigh
			RThigh.setPivot(-1.0, -4.0, 0.0); 
		//	RThigh.setColor(1.0,0.772,0.478);
			RThigh.setColor(tight1, tight2, tight3);
			RThigh.setOffset(-0.9, -5.5, 0.0);
			RThigh.setScale (1.2, 3.0, 1.6);  
			RThigh.setSize(1.0);	
			
			// Right Lower Leg
			RLowerLeg.setPivot(-1.0, -7.0, 0.0); 
			//RLowerLeg.setColor(1.0,0.772,0.478); 
			RLowerLeg.setColor(lowerLeg1, lowerLeg2, lowerLeg3); 
			RLowerLeg.setOffset(-0.9, -8.5, 0.0);
			RLowerLeg.setScale(1.0, 3.0, 1.4);   
			RLowerLeg.setSize(1.0);	

			// Right Thenar
			RThenar.setPivot(-1.0, -10.5, 0.0);
			//RThenar.setColor(1.0,1.0,0.0);
			RThenar.setColor(thenar1, thenar2, thenar3);
			RThenar.setOffset(-0.9, -11.0, -0.55);
			RThenar.setScale(1.0, 1.0, 2.5);
			RThenar.setSize(1.0);

			// Left Thigh
			LThigh.setPivot(1.0, -4.0, 0.0); 
			//LThigh.setColor(1.0,0.772,0.478);
			LThigh.setColor(tight1, tight2, tight3);
			LThigh.setOffset(0.9, -5.5, 0.0);
			LThigh.setScale (1.2, 3.0, 1.6);  
			LThigh.setSize(1.0);	
			
			// Left Lower Leg
			LLowerLeg.setPivot(1.0, -7.0, 0.0); 
			//LLowerLeg.setColor(1.0,0.772,0.478); 
			LLowerLeg.setColor(lowerLeg1, lowerLeg2, lowerLeg3); 
			LLowerLeg.setOffset(0.9, -8.5, 0.0);
			LLowerLeg.setScale(1.0, 3.0, 1.4);   
			LLowerLeg.setSize(1.0);	

			// Left Thenar
			LThenar.setPivot(1.0, -10.5, 0.0);
			//LThenar.setColor(1.0,1.0,0.0);
			LThenar.setColor(thenar1, thenar2, thenar3);
			LThenar.setOffset(0.9, -11.0, -0.55);
			LThenar.setScale(1.0, 1.0, 2.5);
			LThenar.setSize(1.0);
}

