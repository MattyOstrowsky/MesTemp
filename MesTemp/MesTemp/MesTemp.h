
// MesTemp.h : main header file for the MesTemp application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMesTempApp:
// See MesTemp.cpp for the implementation of this class
//

class CMesTempApp : public CWinApp
{
public:
	CMesTempApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	UINT  m_nAppLook;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMesTempApp theApp;
