#include "music.h"

bool Music::Open(void)
{
	DWORD dwReturn;
	MCI_OPEN_PARMS mciOpenParms;
	//MCI_SET_PARMS mciSetParms;

	// Open wave play device
	mciOpenParms.lpstrDeviceType=(LPSTR)MCI_DEVTYPE_WAVEFORM_AUDIO;
	dwReturn = mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_TYPE|MCI_OPEN_TYPE_ID|MCI_WAIT, (DWORD)(LPVOID)&mciOpenParms);
	CDDeviceID = mciOpenParms.wDeviceID;

	return FALSE;
}

bool Music::Stop(void)
{
	DWORD dwReturn;

	dwReturn=mciSendCommand(CDDeviceID, MCI_STOP, 0, NULL);
	if (dwReturn)
		return dwReturn;
	else 
		return FALSE;
}

bool Music::Close(void)
{
	DWORD dwReturn;

	dwReturn=mciSendCommand(CDDeviceID, MCI_CLOSE, 0, NULL);
	if (dwReturn)
		return dwReturn;
	else 
		return FALSE;
}

bool Music::Play(void)
{
	DWORD dwReturn;
	MCI_PLAY_PARMS mciPlayParms;

	//for wave play
	MCI_OPEN_PARMS mciOpenParms;	
	mciOpenParms.lpstrElementName = fname.c_str();
	dwReturn = mciSendCommand(CDDeviceID,MCI_OPEN, MCI_OPEN_ELEMENT, (DWORD)(LPVOID)&mciOpenParms);
	m_nElementID = mciOpenParms.wDeviceID;
	dwReturn = mciSendCommand(m_nElementID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlayParms);

	return FALSE;
}