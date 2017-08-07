# OpenGL_Animation_Example

This is a project that shows how to use OpenGL to make some dancing animations in c++.

## Libraries and IDE

### Libraries

In order for the project to work, it is necessary to include the following files in the same folder as the generated executable:
1. glut32.dll
2. glut32.lib
3. glut.h
If you want to install the *glut* library in your computer (instead of having it locally for this one project), please refer to the OpenGL docummentation.

### IDE

This project works with Visual Studio 2015. If you want to use a newer version of Visual Studio, just migrate/upgrade the project the first time you open it.

## Controls

In order to control (each of the 9) 3D generated player, here is a list of all the controls of each part of them:
```
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
```

## Notes

There are some important notes:
1.	The original animation has 9 players. These can be added or removed easily, but if wanted to be modified, check the *actor1.txt, ..., actor9.txt* files (they contain the coordinates of all the 3D objects in each frame of the animation).
2.	If you want to modify the way how one of the players move, modify the code in 
```c++
void keyboard (unsigned char key, int x, int y)
```
function in the **dance.cpp** file
3.	At the moment, any movement of the keyboard will affect all the players. If you want to modify an specific player, change the code
```c++
for(contador=0;contador<9;contador++){
	actor[contador].Torso.Offset[0] += 1;
}
```
To
```c++	
actor[actorIdx].Torso.Offset[0] += 1;
```
The way how to determine the index of each player is given in
```c++
case '1': animation.actorIndex = 0;    break;
case '2': animation.actorIndex = 1;    break;
case '[': animation.actorIndex = 2;    break;
case '{': animation.actorIndex = 3;    break;
case ']': animation.actorIndex = 4;    break;
case '}': animation.actorIndex = 5;    break;
case '-': animation.actorIndex = 6;    break;
case '_': animation.actorIndex = 7;    break;
case '+': animation.actorIndex = 8;    break;
```
4.	By pressing and holding **SHIFT** while pressing the translation or rotation keys, the object will move in the opposite direction.

## Music

## Execution

In order to execute it, just run the project. To initiate the animation:
1. Click on the generated window (the one with the 3D character).
2. Type the *equal* key ('=') in your keyboard.

