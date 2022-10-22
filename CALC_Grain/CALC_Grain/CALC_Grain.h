
// CALC_Grain.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CCALC_GrainApp:
// See CALC_Grain.cpp for the implementation of this class
//

class CCALC_GrainApp : public CWinApp
{
public:
	CCALC_GrainApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CCALC_GrainApp theApp;