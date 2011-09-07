#include "qdt3.h"

#include <windows.h> 

HINSTANCE hinst; 

void goIDE() ; 

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int); 
BOOL InitApplication(HINSTANCE); 
BOOL InitInstance(HINSTANCE, int); 
LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM); 
HWND hText=0;

qString dablangstatus = "Dablang JIT init\r\n";

#include <strsafe.h>
void ErrorExit(LPTSTR lpszFunction="") 
{ 
	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;
	DWORD dw = GetLastError();

	if (dw==NO_ERROR) return;

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR) &lpMsgBuf,
		0, NULL );

	lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
		(lstrlen((LPCTSTR)lpMsgBuf)+lstrlen((LPCTSTR)lpszFunction)+40)*sizeof(TCHAR)); 
	StringCchPrintf((LPTSTR)lpDisplayBuf, 
		LocalSize(lpDisplayBuf),
		TEXT("%s failed with error %d: %s\n"), 
		lpszFunction, dw, lpMsgBuf); 
	//MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK); 

	OutputDebugString((LPCTSTR)lpDisplayBuf);

	LocalFree(lpMsgBuf);
	LocalFree(lpDisplayBuf);
	//ExitProcess(dw); 
}


void AddDablangStatus2(const qString & ss)
{
	if (hText==0) return;
	qString ssnl = ss ;

	replace_all(ssnl, "\r", "");
	replace_all(ssnl, "\n", "\r\n");

	dablangstatus+=ssnl;//+"\r\n";
	SetWindowText(hText,dablangstatus.c_str());
	ErrorExit("SetWindowText");
	SendMessage(hText, LOWORD(WM_VSCROLL), SB_BOTTOM, 0);

	static FILE * ff = fopen("testlog.txt", "w");
	fprintf(ff,"%s", ssnl.c_str());
	fflush(ff);
}

void AddDablangStatus(const qString & ss)
{
	AddDablangStatus2(ss+"\r\n");
}

qValue * current_status;

qValue * compileText(std::map<qString, qString> & filemap);

DWORD (WINAPI funll)(LPVOID lpThreadParameter)
{
	qString pp = (const char *)lpThreadParameter;

	SetLastError(0);
	char zzz[400];
	sprintf(zzz,"Will compile %d bytes of code...\n", pp.length());
	AddDablangStatus(zzz);

	std::map<qString, qString> files;
	files["jit.dab"] = pp;
	qValue * cmp = compileText(files);
	current_status = cmp;
	SetLastError(0);

	if (cmp)
	{
		bool runCode(qValue * prog);
		SetLastError(0);
		AddDablangStatus("will run...\n");
		runCode(cmp);
	}
	else AddDablangStatus("No code?\n");

	AddDablangStatus("Did JIT");

	return 3;
}
qString sqzz ;

HANDLE game_thead_id = 0;

void AddNewCode(const char *q)
{
	bool subupdatecompiled(const char *txt, qValue * last);
	if (subupdatecompiled(q, current_status))
	{
		qValue * update_funcs();
		qValue * up = update_funcs();
		((qProgram*)current_status)->AppendProgram((qProgram*)up);
	}
}

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)			
{
	LONG_PTR lp = GetWindowLongPtr(hWnd, GWL_USERDATA);

	switch (uMsg)
	{
	case WM_USER+5:
		{
			return 0;
		}
	case WM_COPYDATA:
	{
	PCOPYDATASTRUCT	pMyCDS = (PCOPYDATASTRUCT) lParam;
		switch( pMyCDS->dwData )
		{
		case 5:
			{

			 sqzz = (const char*)pMyCDS->lpData;

			AddDablangStatus("Will JIT");

			DWORD id;

			game_thead_id = CreateThread(0,0,funll,(LPVOID)sqzz.c_str(),0,(LPDWORD)&id);

			}
			break;
		case 6:
			{
				AddDablangStatus(" *** Dynamic update!");

				SuspendThread(game_thead_id);

				AddNewCode((const char*)pMyCDS->lpData);

				ResumeThread(game_thead_id);

				AddDablangStatus(" *** Dynamic update finished!");
			}
			break;

		}

		return 0;
	}
	case WM_CLOSE:
		{
			TerminateProcess(GetCurrentProcess(),55);
			PostQuitMessage(0);					
			return 0;
		}
	};

	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

int main();

bool procrunn = false;
PROCESS_INFORMATION pinfo;

void SendUpdatesToProcess(const char *txt)
{
	COPYDATASTRUCT MyCDS;

	MyCDS.dwData = 6;         
	MyCDS.cbData = strlen(txt)+1;  
	MyCDS.lpData = (PVOID)txt;        

	HWND qq = FindWindow("JITMainWClass", 0);
	SendMessage(qq, WM_COPYDATA, 0, (LPARAM) (LPVOID) &MyCDS);
}

bool dablangIsProcessRunning() 
{ 
	if (!procrunn) return false;

	DWORD ret;
	GetExitCodeProcess(pinfo.hProcess, &ret);
	return ret == STILL_ACTIVE ; 
}

void StopProcIfRunning()
{
	if (!dablangIsProcessRunning()) { procrunn = false; return;}

	TerminateProcess(pinfo.hProcess ,6);
	procrunn = false;
}

void SpawnProcek(qString & ss)
{
	SetLastError(0);
	ErrorExit("11111");

	ZeroMemory(&pinfo,sizeof(pinfo));
	
	STARTUPINFO si;

	ZeroMemory( &si, sizeof(si) );
	si.cb = sizeof(si);
	ErrorExit("ppx");

#ifdef _DEBUG
	CreateProcess(0, "..\\Debug\\qdt2.exe jit", 0, 0, FALSE, 0, 0, "..\\game", &si, &pinfo);
#else
	CreateProcess(0, "dab.exe jit", 0, 0, FALSE, 0, 0, ".", &si, &pinfo);
#endif

	procrunn=true;
	Sleep(100);

	HWND qq = FindWindow("JITMainWClass", 0);

	ErrorExit("no <JITMainWClass>");

	if (qq)
	{
		qString & sqpl = ss;
		COPYDATASTRUCT MyCDS;

		MyCDS.dwData = 5;         
		MyCDS.cbData = sqpl.length()+1;  
		MyCDS.lpData = (PVOID)sqpl.c_str();   

		SendMessage(qq, WM_COPYDATA, 0, (LPARAM) (LPVOID) &MyCDS);//sqpl.c_str());
		ErrorExit("SendMessage");
		ErrorExit("sleep");
	}
	else
	{
		*(int*)0=0;
	}
}


int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, 
				   LPSTR lpCmdLine, int nCmdShow) 
{ 

	qString sss(lpCmdLine);

#ifdef _DEBUG
	if (sss=="main")
#else
	if (sss=="")
#endif
	{
		goIDE();
		return 0;
	}
	if (sss == "jit")
	{
		MSG msg; 

		if (!InitApplication(hinstance)) 
			return FALSE; 

		if (!InitInstance(hinstance, nCmdShow)) 
			return FALSE; 

		_CrtSetDbgFlag ( 0);

		BOOL fGotMessage;
		while ((fGotMessage = GetMessage(&msg, (HWND) NULL, 0, 0)) != 0 && fGotMessage != -1) 
		{ 
			TranslateMessage(&msg); 
			DispatchMessage(&msg); 
		} 
		return msg.wParam; 
		UNREFERENCED_PARAMETER(lpCmdLine);
	}

	return 0;
} 

BOOL InitApplication(HINSTANCE hinstance) 
{ 
	WNDCLASSEX wcx; 

	ZeroMemory(&wcx, sizeof(wcx));

	wcx.cbSize = sizeof(wcx);          
	wcx.style = CS_HREDRAW | CS_VREDRAW;                    
	wcx.lpfnWndProc = MainWndProc;      
	wcx.cbClsExtra = 0;                
	wcx.cbWndExtra = 0;                
	wcx.hInstance = hinstance;         
	wcx.hIcon = LoadIcon(NULL, IDI_APPLICATION);              
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW);                    
	wcx.hbrBackground =0;
	wcx.lpszClassName = "JITMainWClass";  

	return RegisterClassEx(&wcx); 
} 

BOOL InitInstance(HINSTANCE hinstance, int nCmdShow) 
{ 
	HWND hwnd; 

	hinst = hinstance; 

	int w1 = 700, h1 = 300;
	RECT r;
	r.left = 0; r.top = 0; r.right = w1; r.bottom = h1;
	int style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
	AdjustWindowRectEx(&r, style, 0, 0);

	int w = r.right - r.left;
	int h = r.bottom - r.top;

	hwnd = CreateWindow("JITMainWClass","DABLANG JIT status", style, CW_USEDEFAULT, CW_USEDEFAULT, w, h, (HWND)NULL, (HMENU)NULL, hinstance, (LPVOID)NULL);

	if (!hwnd) return FALSE; 

	hText = CreateWindowEx (WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL, 0, 0, w1, h1, hwnd, NULL, hinstance, NULL);

	SetWindowText(hText,dablangstatus.c_str());

	ShowWindow(hwnd, nCmdShow); 
	UpdateWindow(hwnd); 
	return TRUE; 
}
