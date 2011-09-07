// Dab IDE

#include <wx/wx.h>

#include <wx/splitter.h>
#include <wx/listctrl.h>
#include <wx/notebook.h>
#include <wx/fontutil.h>
#include <wx/stc/stc.h>

#include <typeinfo>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <map>
#include <vector>
#include <string>
#include <assert.h>
#include <algorithm>

using namespace std;

namespace llvm
{
	class Module;
	class Value;
	class Function;
	class Type;
};

#include "dab_header.h"
