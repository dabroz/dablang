#pragma once

#ifdef DABCORE_EXPORTS
#define DABCORE_API __declspec(dllexport)
#else
#define DABCORE_API __declspec(dllimport)
#endif

/*
// This class is exported from the dab-core.dll
class DABCORE_API Cdabcore {
public:
	Cdabcore(void);
	// TODO: add your methods here.
};

extern DABCORE_API int ndabcore;

DABCORE_API int fndabcore(void);
*/