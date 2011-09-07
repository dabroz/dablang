// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "dab_header.h"

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             
#include <windows.h>

#pragma comment (lib, "LLVMAnalysis.lib")
#pragma comment (lib, "LLVMArchive.lib")
#pragma comment (lib, "LLVMAsmParser.lib")
#pragma comment (lib, "LLVMAsmPrinter.lib")
#pragma comment (lib, "LLVMBitReader.lib")
#pragma comment (lib, "LLVMBitWriter.lib")
#pragma comment (lib, "LLVMCodeGen.lib")
#pragma comment (lib, "LLVMCore.lib")
#pragma comment (lib, "LLVMExecutionEngine.lib")
#pragma comment (lib, "LLVMInstCombine.lib")
#pragma comment (lib, "LLVMInstrumentation.lib")
#pragma comment (lib, "LLVMInterpreter.lib")
#pragma comment (lib, "LLVMJIT.lib")
#pragma comment (lib, "LLVMLinker.lib")
#pragma comment (lib, "LLVMMC.lib")
#pragma comment (lib, "LLVMMCDisassembler.lib")
#pragma comment (lib, "LLVMMCJIT.lib")
#pragma comment (lib, "LLVMMCParser.lib")
#pragma comment (lib, "LLVMObject.lib")
#pragma comment (lib, "LLVMRuntimeDyld.lib")
#pragma comment (lib, "LLVMScalarOpts.lib")
#pragma comment (lib, "LLVMSelectionDAG.lib")
#pragma comment (lib, "LLVMSupport.lib")
#pragma comment (lib, "LLVMTarget.lib")
#pragma comment (lib, "LLVMTransformUtils.lib")
#pragma comment (lib, "LLVMX86AsmParser.lib")
#pragma comment (lib, "LLVMX86AsmPrinter.lib")
#pragma comment (lib, "LLVMX86CodeGen.lib")
#pragma comment (lib, "LLVMX86Desc.lib")
#pragma comment (lib, "LLVMX86Disassembler.lib")
#pragma comment (lib, "LLVMX86Info.lib")
#pragma comment (lib, "LLVMX86Utils.lib")
#pragma comment (lib, "LLVMipa.lib")
#pragma comment (lib, "LLVMipo.lib")


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
