#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include <TlHelp32.h>


int _tmain(int argc, _TCHAR* argv[])
{
	_TCHAR streamErr[100];
	_TCHAR streamIn0[100];
	_TCHAR streamOut0[100];


	HANDLE hWritePipe0, hReadPipe0;
	SECURITY_ATTRIBUTES saPipe0 = { sizeof(SECURITY_ATTRIBUTES),NULL,TRUE };
	SECURITY_ATTRIBUTES saFileIn0 = { sizeof(SECURITY_ATTRIBUTES),NULL,TRUE };
	HANDLE hFileIn0 = CreateFile(L"In0.txt", GENERIC_READ, NULL,
		&saFileIn0,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFileIn0 == INVALID_HANDLE_VALUE)
	{
		wprintf(L"Could not open file <%s> (error %d)\n", streamIn0, GetLastError());
		getchar();
		return 0;
	}

	SECURITY_ATTRIBUTES saFileErr = { sizeof(SECURITY_ATTRIBUTES),nullptr,TRUE };
	HANDLE hFileErr = CreateFile(L"Errors.txt", GENERIC_WRITE, 0,
		&saFileErr,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (hFileErr == INVALID_HANDLE_VALUE)
	{
		wprintf(L"Could not open file <%s> (error %d)\n", streamErr, GetLastError());
		getchar();
		return 0;
	}

	SECURITY_ATTRIBUTES saFileOut0 = { sizeof(SECURITY_ATTRIBUTES),nullptr,TRUE };
	HANDLE hFileOut0 = CreateFile(L"Out0.txt", GENERIC_WRITE, 0,
		&saFileOut0,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFileOut0 == INVALID_HANDLE_VALUE)
	{
		wprintf(L"Could not open file <%s> (error %d)\n", streamOut0, GetLastError());
		getchar();
		return 0;
	}

	BOOL bPipe0 = CreatePipe(&hReadPipe0, &hWritePipe0, &saPipe0, 0);
	if (!bPipe0)
	{
		wprintf(L"Could not create Pipe (error %d)\n", GetLastError());
		getchar();
		return 0;
	}

	HANDLE hWritePipe1, hReadPipe1;
	SECURITY_ATTRIBUTES saPipe1 = { sizeof(SECURITY_ATTRIBUTES),NULL,TRUE };
	SECURITY_ATTRIBUTES saFileIn1 = { sizeof(SECURITY_ATTRIBUTES),NULL,TRUE };
	HANDLE hFileIn1 = CreateFile(L"In1.txt", GENERIC_READ, 0,
		&saFileIn1,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFileIn1 == INVALID_HANDLE_VALUE)
	{
		wprintf(L"Could not open file <%s> (error %d)\n", streamIn0, GetLastError());
		getchar();
		return 0;
	}

	SECURITY_ATTRIBUTES saFileOut1 = { sizeof(SECURITY_ATTRIBUTES),NULL,TRUE };
	HANDLE hFileOut1 = CreateFile(L"Out1.txt", GENERIC_WRITE, 0,
		&saFileOut1,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFileOut1 == INVALID_HANDLE_VALUE)
	{
		wprintf(L"Could not open file <%s> (error %d)\n", streamOut0, GetLastError());
		getchar();
		return 0;
	}

	BOOL bPipe1 = CreatePipe(&hReadPipe1, &hWritePipe1, &saPipe1, 0);
	if (!bPipe1)
	{
		wprintf(L"Could not create Pipe (error %d)\n", GetLastError());
		getchar();
		return 0;
	}

	HANDLE hWritePipe2, hReadPipe2;
	SECURITY_ATTRIBUTES saPipe2 = { sizeof(SECURITY_ATTRIBUTES),NULL,TRUE };
	SECURITY_ATTRIBUTES saFileIn2 = { sizeof(SECURITY_ATTRIBUTES),NULL,TRUE };
	HANDLE hFileIn2 = CreateFile(L"In2.txt", GENERIC_READ, 0,
		&saFileIn2,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFileIn2 == INVALID_HANDLE_VALUE)
	{
		wprintf(L"Could not open file <%s> (error %d)\n", streamIn0, GetLastError());
		getchar();
		return 0;
	}

	SECURITY_ATTRIBUTES saFileOut2 = { sizeof(SECURITY_ATTRIBUTES),NULL,TRUE };
	HANDLE hFileOut2 = CreateFile(L"Out2.txt", GENERIC_WRITE, 0,
		&saFileOut2,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFileOut2 == INVALID_HANDLE_VALUE)
	{
		wprintf(L"Could not open file <%s> (error %d)\n", streamOut0, GetLastError());
		getchar();
		return 0;
	}


	BOOL bPipe2 = CreatePipe(&hReadPipe2, &hWritePipe2, &saPipe2, 0);
	if (!bPipe2)
	{
		wprintf(L"Could not create Pipe (error %d)\n", GetLastError());
		getchar();
		return 0;
	}

	STARTUPINFO startInfoProcessM, startInfoProcessA, startInfoProcessP, startInfoProcessS;
	PROCESS_INFORMATION processM_Info, processA_Info, processP_Info, processS_Info;


	GetStartupInfo(&startInfoProcessM);
	startInfoProcessM.hStdInput = hFileIn0;
	startInfoProcessM.hStdError = hFileErr;
	startInfoProcessM.hStdOutput = hWritePipe0;
	startInfoProcessM.dwFlags = STARTF_USESTDHANDLES;


	BOOL bPr0 = CreateProcess(L"C:\\Users\\Dima\\gitable\\OS\\windows\\pipe\\M\\cmake-build-debug\\M.exe",
		NULL, NULL,
		NULL, TRUE,
		NULL,
		NULL,
		NULL,
		&startInfoProcessM,
		&processM_Info);
	if (!bPr0)
	{
		wprintf(L"Could not create process <%s>(error %d)\n", GetLastError());
		getchar();
		return 0;
	}
	CloseHandle(hWritePipe0);
	CloseHandle(hFileIn0);

	GetStartupInfo(&startInfoProcessA);
	startInfoProcessA.hStdInput = hReadPipe0;
	startInfoProcessA.hStdError = hFileErr;
	startInfoProcessA.hStdOutput = hWritePipe1;
	startInfoProcessA.dwFlags = STARTF_USESTDHANDLES;

	BOOL bPr1 = CreateProcess(L"C:\\Users\\Dima\\gitable\\OS\\windows\\pipe\\A\\cmake-build-debug\\A.exe",
		NULL, NULL,
		NULL, TRUE,
		0,
		NULL,
		NULL,
		&startInfoProcessA,
		&processA_Info);
	if (!bPr1)
	{
		wprintf(L"Could not create process <%s>(error %d)\n", GetLastError());
		getchar();
		return 0;
	}
	CloseHandle(hWritePipe1);
	CloseHandle(hReadPipe0);

	GetStartupInfo(&startInfoProcessP);
	startInfoProcessP.hStdInput = hReadPipe1;
	startInfoProcessP.hStdError = hFileErr;
	startInfoProcessP.hStdOutput = hWritePipe2;
	startInfoProcessP.dwFlags = STARTF_USESTDHANDLES;

	BOOL bPr2 = CreateProcess(L"C:\\Users\\Dima\\gitable\\OS\\windows\\pipe\\P\\cmake-build-debug\\P.exe",
		NULL, NULL,
		NULL, TRUE,
		0,
		NULL,
		NULL,
		&startInfoProcessP,
		&processP_Info);
	if (!bPr2)
	{
		wprintf(L"Could not create process <%s>(error %d)\n", GetLastError());
		getchar();
		return 0;
	}
	CloseHandle(hWritePipe2);
	CloseHandle(hReadPipe1);



	GetStartupInfo(&startInfoProcessS);
	startInfoProcessS.hStdInput = hReadPipe2;
	startInfoProcessS.hStdError = GetStdHandle(STD_ERROR_HANDLE);
	startInfoProcessS.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	startInfoProcessS.dwFlags = STARTF_USESTDHANDLES;


	BOOL bPr3 = CreateProcess(L"C:\\Users\\Dima\\gitable\\OS\\windows\\pipe\\S\\cmake-build-debug\\S.exe",
		NULL, NULL,
		NULL, TRUE,
		0,
		NULL,
		NULL,
		&startInfoProcessS,
		&processS_Info);
	if (!bPr1)
	{
		wprintf(L"Could not create process <%s>(error %d)\n", GetLastError());
		getchar();
		return 0;
	}
	CloseHandle(hReadPipe2);
	CloseHandle(hFileOut0);
	CloseHandle(hFileErr);

	WaitForSingleObject(processM_Info.hProcess, INFINITE);
	CloseHandle(processM_Info.hProcess);

	WaitForSingleObject(processA_Info.hProcess, INFINITE);
	CloseHandle(processA_Info.hProcess);

	WaitForSingleObject(processP_Info.hProcess, INFINITE);
	CloseHandle(processP_Info.hProcess);

	WaitForSingleObject(processS_Info.hProcess, INFINITE);
	CloseHandle(processS_Info.hProcess);

	getchar();
	return 0;
}
