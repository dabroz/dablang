#include "qdt3.h"

Module * TheModule = 0;
ExecutionEngine *TheExecutionEngine = 0;

llvm::Module * CreateModule()
{
	llvm::InitializeNativeTarget();
	
	llvm::LLVMContext &Context = llvm::getGlobalContext();
	llvm::Module * mod = new llvm::Module("QDT Jit", Context);
	std::string ErrStr;
	
	llvm_start_multithreaded();

	llvm::UnsafeFPMath = true;
	llvm::NoInfsFPMath = true;
	llvm::NoNaNsFPMath = true;
	llvm::HonorSignDependentRoundingFPMathOption = false;

	TheModule= mod;

	TheExecutionEngine = EngineBuilder(TheModule).
		setErrorStr(&ErrStr).
		//setOptLevel(CodeGenOpt::Aggressive).
		setOptLevel(CodeGenOpt::None).
		setEngineKind(EngineKind::JIT).		
		create();
		if (!TheExecutionEngine) {
			fprintf(stderr, "Could not create ExecutionEngine: %s\n", ErrStr.c_str());
			exit(1);
		}

		TheExecutionEngine->DisableLazyCompilation(true);

	return mod;
}

Value * Lconstant( float v )
{
	return ConstantFP::get(getGlobalContext(), APFloat(v));
}

Value * Lconstant( int v )
{
	return ConstantInt::get(Type::getInt32Ty(getGlobalContext()), v);
}

Value * Lconstant( bool v )
{
	return ConstantInt::get(Type::getInt1Ty(getGlobalContext()), v);
}

extern std::map<qString, std::vector<qneu_Function *>> functions;

extern std::vector<qDeclare*> llvmglobalvars;

void setFile(const char *name, const qString&body);

#include <windows.h>

LRESULT CALLBACK xxxWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)			
{
	{
		switch (uMsg)
		{
		case WM_KEYDOWN:
		case WM_KEYUP:
		case WM_SYSKEYUP:
		case WM_SYSKEYDOWN:
		case WM_SIZE:
		case WM_QUIT:
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:
		case WM_MBUTTONDOWN:
		case WM_MBUTTONUP:
		case WM_MOUSEMOVE:
			{
				return 0;
			}
			break;
		case WM_CLOSE:
			{
				PostQuitMessage(0);					
				return 0;						
			}
			break;
		default:
			break;
		};
	}

	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

DWORD FilterFunction() 
{ 
	return EXCEPTION_EXECUTE_HANDLER; 
} 

typedef int (*fun)();
int runcode(fun ff)
{
	int i = 0;

	__try 
	{ 
		__try 
		{ 
			i = ff();
		} 
		__finally 
		{ 
		} 
	} 
	__except ( FilterFunction() ) 
	{ 
		DWORD ee = GetExceptionCode();
		if (0) {}
		else if (ee == EXCEPTION_INT_DIVIDE_BY_ZERO) qdtprintf2("\n\nERROR: DIVISION BY 0!\n\n");
		else if (ee == EXCEPTION_ACCESS_VIOLATION) qdtprintf2("\n\nERROR: ACCESS VIOLATION!\n\n");
		else qdtprintf2("\n\nERROR: EXCEPTION!!\n\n");                // this is printed last 
	} 

	return i;
}

Module * globalllvmmodule= 0;

qString RunLLVMBuilding(qValue * prog)
{
	InitializeNativeTarget();
	
	llvm::Module * m = CreateModule();
	globalllvmmodule=m;

	prog->LLVM_prebuild(m);
	prog->LLVM_build(m);

	std::string ErrorInfo;
	std::string Q;
	llvm::raw_string_ostream * ff1 = new llvm::raw_string_ostream(Q);
	llvm::AssemblyAnnotationWriter * Annotator = 0;
	m->print(*ff1, Annotator);
	
	if (ShouldWriteOutput())
		setFile("compile_llvm.txt",Q);

	for (int i =0;i<llvmglobalvars.size();i++) 
	{
		GlobalVariable * gv= (GlobalVariable*)llvmglobalvars[i]->llvmvar;

		llvmglobalvars[i]->dataptr = TheExecutionEngine->getOrEmitGlobalVariable(gv);

		if (llvmglobalvars[i]->pretty_name== "EMPTY_WND_PROC")
		{
			int * pttt = (int*)	llvmglobalvars[i]->dataptr;
			*pttt= (int)xxxWndProc;
		}
	}

	qneu_Function * ff = functions["main"][0];
	fun mainfun = (fun)TheExecutionEngine->getPointerToFunction(ff->llvmd);

	qdtprintf2("Running...\n\n");

	int wynik=runcode(mainfun);

	qdtprintf2("\n\n *** Return value: %d\n", wynik);

	return Q;
}
