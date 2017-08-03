
#include <objbase.h>
#include <string>
#include <iostream>

using namespace std;

class Music{
private:
	int	CDDeviceID;
	int	m_nElementID;
	string fname;
	
public:
	Music(char *filename):CDDeviceID(-1), m_nElementID(-1){
		fname = string(filename);
	};
	bool Open(void);
	bool Stop(void);
	bool Close(void);
	bool Play(void);
};