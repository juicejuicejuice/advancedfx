#pragma once

#include "WrpGlobals.h"
#include "WrpConsole.h"
#include "CamIO.h"
#include <shared/CamPath.h>

class Hook_VClient_RenderView;

// global singelton instance:
extern Hook_VClient_RenderView g_Hook_VClient_RenderView;


// Hook_VClient_RenderView /////////////////////////////////////////////////////

class Hook_VClient_RenderView
{
public:
	CamPath m_CamPath;

	float GameCameraOrigin[3] = { 0.0f, 0.0f, 0.0f };
	float GameCameraAngles[3] = { 0.0f, 0.0f, 0.0f };
	float GameCameraFov = 90.0f;

	double LastCameraOrigin[3];
	double LastCameraAngles[3];
	double LastCameraFov;
	int LastWidth = 1280;
	int LastHeight = 720;

	bool handleZoomEnabled;
	double handleZoomMinUnzoomedFov;

	Hook_VClient_RenderView();
	~Hook_VClient_RenderView();

	bool ExportBegin(wchar_t const *fileName, double frameTime);
	void ExportEnd();

	bool GetFovOverride(double &outValue);

	void FovOverride(double value);
	void FovDefault();

	float GetCurTime();

	float GetImportBasteTime();

	bool ImportBegin(wchar_t const *fileName);
	void ImportEnd();

	bool ImportToCamPath(bool adjustInterp, double fov);

	void Install(WrpGlobals * globals);
	WrpGlobals * GetGlobals();

	bool IsInstalled(void);

	void OnAdjustEngineViewport(int& x, int& y, int& width, int& height)
	{
		LastWidth = width;
		LastHeight = height;
	}

	void OnViewOverride(float &Tx, float &Ty, float &Tz, float &Rx, float &Ry, float &Rz, float &Fov);

	void SetImportBaseTime(float value);

	void Console_CamIO(IWrpCommandArgs * args);

private:
	bool m_Export;
	bool m_FovOverride;
	double m_FovValue;
	WrpGlobals * m_Globals;
	bool m_Import;
	float m_ImportBaseTime;
	bool m_IsInstalled;

	CamExport * m_CamExport = 0;
	CamImport * m_CamImport = 0;
};

