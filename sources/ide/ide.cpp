#include "stdafx.h"
#include "resource.h"

//#define WXUSINGDLL
#define wxUSE_EXTENDED_RTTI 1

//qValue * compileText(std::map<qString, qString> & filemap);


#ifdef _DEBUG
#pragma comment(lib, "wxbase29ud.lib")
#pragma comment(lib, "wxmsw29ud_core.lib")
#pragma comment(lib, "wxmsw29ud_stc.lib")
#pragma comment(lib, "wxtiffd.lib")
#pragma comment(lib, "wxpngd.lib")
#pragma comment(lib, "wxjpegd.lib")
#pragma comment(lib, "wxscintillad.lib")
#pragma comment(lib, "wxzlibd.lib")
#else
#pragma comment(lib, "wxbase29u.lib")
#pragma comment(lib, "wxmsw29u_core.lib")
#pragma comment(lib, "wxmsw29u_stc.lib")
#pragma comment(lib, "wxtiff.lib")
#pragma comment(lib, "wxpng.lib")
#pragma comment(lib, "wxjpeg.lib")
#pragma comment(lib, "wxscintilla.lib")
#pragma comment(lib, "wxzlib.lib")
#endif
#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "rpcrt4.lib")

class MyApp : public wxApp
{
public:
	virtual bool OnInit();    
};

bool is_whitespace(char c) { return (c==' '||c=='\n'||c=='\r'||c=='\t'); }

qString trim(const qString & s)
{
	int i1 = 0;
	int i2 = s.length();

	while (i1 < s.length() && is_whitespace(s[i1])) i1++;
	while (i2 > 0 && is_whitespace(s[i2 - 1])) i2--;

	if (i2<=i1) return "";

	return s.substr(i1,i2-i1);
}

void AddDef( std::map<qString, qString> & values, const qString & e ) 
{
	qString s = e.substr(e.find("define")+6);
	//replace_all(s, ";", "");
	s = trim(s);

	int i2 = s.length();
	while (!is_whitespace(s[i2-1])) i2--;

	qString key = trim(s.substr(0,i2));
	qString val = trim(s.substr(i2));

	values[key] = val;
}

void AddVar( std::map<qString, qString>& values, const qString & e ) 
{
	qString s = e;
	replace_all(s, "const uint32", "");
	replace_all(s, "=", "");
	replace_all(s, ";", "");
	s = trim(s);

	int i2 = s.length();
	while (!is_whitespace(s[i2-1])) i2--;

	qString key = trim(s.substr(0,i2));
	qString val = trim(s.substr(i2));

	values[key] = val;
}

qString XVal(const qString & vv)
{
	unsigned v = 0;
	if ((vv.length()>=2)  && vv[0]=='0' && (vv[1]=='x' ||vv[1]=='X') && (1 == sscanf(vv.c_str(), "%x", &v))) {}
	else if (1 == sscanf(vv.c_str(), "%d", &v)) {}
	else { v = 0; }

	char msg[128];
	sprintf(msg, "0x%08x", v);
	return msg;
}

qString FixDefsText( const qString & s1 ) 
{
	qString s = s1 + "\n";
	std::vector<qString> ss;

	qString l = "";

	std::map<qString, qString> values;

	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == '\n') { qString ll = trim(l); qdtprintf("'%s' -> '%s'\n", l.c_str(),ll.c_str()); l = ""; if (ll.length()) ss.push_back(ll); }
		else l += s[i];
	}

	for (int i = 0; i < ss.size(); i++)
	{
		const qString & e = ss[i];

		if (e[0] == '#') AddDef(values, e);
		else AddVar(values, e);
	}

	int maxl = 0;
	for (std::map<qString, qString>::iterator it = values.begin(), end = values.end(); it != end; ++it)
	{
		maxl = std::max(maxl, (int)it->first.length());
	}
	qString ret = "";
	qString group = "";
	for (std::map<qString, qString>::iterator it = values.begin(), end = values.end(); it != end; ++it)
	{
		qString agroup = "";
		int iq = it->first.find('_');
		if (iq != qString::npos)
			agroup = it->first.substr(0, iq);

		if (agroup != group) 
		{ 
			if (ret.length()) ret += "\n"; 
			group = agroup; 
		}
		ret += "const uint32 " + it->first + qString(maxl-it->first.length(), ' ') + " = " + XVal(it->second) + ";\n";
	}

	return ret;
}

const int STYLE_ANN = 50;

enum
{
	ID_MAINWIN_QUIT = wxID_HIGHEST + 1,
	ID_TOOLBAR,
	ID_RUN,
	ID_RUNINTERNAL,
	ID_PAUSE,
	ID_STOP,
	ID_COMPILE,
	ID_ERRORS,
	ID_SAVE,
	ID_DEFS,
	ID_MENURUN,
	ID_MENUUPDATE
};

void setFile(const char *name, const qString&body)
{
	// PLACEHOLDER
}

bool runCode(qValue * prog)
{
	// PLACEHOLDER
	return false;
}

void SpawnProcek(qString & ss)
{
	// PLACEHOLDER
}

qValue * compileText(std::map<qString, qString> & filemap)
{
	// PLACEHOLDER
	return 0;
}

void StopProcIfRunning()
{
	// PLACEHOLDER
}

void turboRun( std::string & ll  ) 
{
	SpawnProcek(ll);
}

bool dablangIsProcessRunning()
{
	// PLACEHOLDER
	return false;
}

void SendUpdatesToProcess(const char *txt)
{
	// PLACEHOLDER
}


bool subupdatecompiled(const char *txt, qValue * last)
{
	// PLACEHOLDER
	return false;
}

// TEMPORARY
//extern std::vector<qError> compileErrors;
//std::vector<qError> compileErrors;

extern std::map<qString, std::vector<qneu_Function *>> functions;
std::map<qString, std::vector<qneu_Function *>> functions;

wxBitmap* GetBitmapFromMemory(const char* t_data, const DWORD t_size, int type = wxBITMAP_TYPE_PNG)
{
	wxMemoryInputStream a_is(t_data, t_size);
	return new wxBitmap(wxImage(a_is, type, -1), -1);
}

bool LoadDataFromResource(char*& t_data, DWORD& t_dataSize, int resID, LPWSTR resType = RT_RCDATA)
{
	bool     r_result    = false;
	HGLOBAL  a_resHandle = 0;
	HRSRC    a_resource;

	a_resource = FindResource(0, MAKEINTRESOURCE(resID), resType);

	if (0 != a_resource)
	{
		a_resHandle = LoadResource(NULL, a_resource);
		if (0 != a_resHandle)
		{
			t_data = (char*)LockResource(a_resHandle);
			t_dataSize = SizeofResource(NULL, a_resource);
			r_result = true;
		}
	}

	return r_result;
}

wxBitmap* CreateBitmapFromPngResource(int resID)
{
	char*       a_data      = 0;
	DWORD       a_dataSize  = 0;

	if (LoadDataFromResource(a_data, a_dataSize, resID))
	{
		return GetBitmapFromMemory(a_data, a_dataSize);
	}

	return 0;
}

class MyFrame : public wxFrame
{
public:
	void OnQuit (wxCommandEvent& Event);

	wxToolBar * toolBar;
	wxListCtrl * files;
	wxNotebook * editors; 
	wxNotebook * _tools;
	wxTextCtrl * _output;

	wxListCtrl * _errors;

	int _toolbar_currentX;

	std::vector<wxStyledTextCtrl *> _codes;
	std::vector<wxString> _filenames;
	std::vector<int> _dirtyflag;

	qValue * lastCompile;

	std::string _lastCompileText;


	void OnMenuRunUpdate(wxCommandEvent& Event)
	{
		
		if (!dablangIsProcessRunning()) return;

		int s = editors->GetSelection();

		
		if (subupdatecompiled(_codes[s]->GetText().c_str().AsChar(), lastCompile))
		{
			SendUpdatesToProcess(_codes[s]->GetText().c_str().AsChar());
		}
		else ShowErrors();
	}

	bool Compile()
	{
		lastCompile = 0;
		std::map<qString, qString> files;

		_lastCompileText = "";

		for (int i = 0; i < _filenames.size(); i++)
		{
			qString s = _codes[i]->GetText().c_str().AsChar();
			_lastCompileText += s+"\n\n";
			files[_filenames[i].c_str().AsChar()] = _codes[i]->GetText().c_str().AsChar();
		}

		//lastCompile = 
		dab_Module * mod = 	dab_CompileFiles(files, 0);

		_compileErrors = mod->_errors;

		bool bb = ShowErrors();

		lastCompile = 0;
		if (!lastCompile || bb) return false;

		return true;
	}

	bool Run(bool internal)
	{
		if (internal) return runCode(lastCompile);
		turboRun(_lastCompileText);

		return true;
	}

	std::vector<qError> _compileErrors;

	bool ShowErrors()
	{
		bool ret = false;

		_errors->DeleteAllItems();

		for (int i = 0; i < _codes.size(); i++)
			_codes[i]->AnnotationClearAll();

		std::map<qString, std::map<int, qString> > annotations;

		std::map<qString, std::map<int, qString> > annotationsStyle;

		std::sort(_compileErrors.begin(), _compileErrors.end());

		for (int i = 0; i < _compileErrors.size(); i++)
		{
			qError & qe = _compileErrors[i];

			_errors->InsertItem(i, "", qe.error?0:1);

			if (qe.error) ret = true;

			wxString ss = wxString::Format("%s C%04d: %s", qe.error?"error":"warning", qe.num, qe.desc.c_str());

			_errors->SetItem(i, 1, wxString::Format(wxT("%d"),i+1)); // num
			_errors->SetItem(i, 2, ss.c_str()); // desc
			_errors->SetItem(i, 3, qe.file.c_str()); // file
			_errors->SetItem(i, 4, wxString::Format(wxT("%d"),qe.line)); // line
			_errors->SetItem(i, 5, wxString::Format(wxT("%d"),qe.start)); // col

			int L = qe.line - 1;
			qString ssR = annotations[qe.file][L];
			bool adden= false;
			if (ssR != "") {ssR += "\n";adden=true;}
			ssR += ss.c_str().AsChar();
			annotations[qe.file][L] = ssR;

			char zz = qe.error?50:51;
			for (int q = 0; q < ss.length()+adden?1:0; q++)
			{
				annotationsStyle[qe.file][L] += zz;
			}
		}

		for (std::map<qString, std::map<int, qString> > ::iterator it = annotations.begin(), e = annotations.end(); it != e; ++it)
		{
			const qString & file = it->first;
			for (std::map<int, qString>::iterator it2 = it->second.begin(), end2 = it->second.end(); it2 != end2; ++it2)
			{
				int line = it2->first;
				qString & text = it2->second;
				qString & styles = annotationsStyle[file][line];

				wxStyledTextCtrl * ed = EditorForCompiled(file);
				//ed->AnnotationSetStyle(it2->first, STYLE_ANN);
				if (!ed) continue;
				if (line<0) line=0;
				ed->AnnotationSetText(line, text.c_str());
				ed->AnnotationSetStyles(line, styles.c_str());				
			}
		}			

		for (int i = 0; i < _codes.size(); i++)
		{
			_codes[i]->AnnotationSetVisible(2);
			_codes[i]->Refresh();
		}

		return ret;
	}

	wxStyledTextCtrl * EditorForCompiled(const qString & f)
	{
		for (int i = 0; i < _filenames.size(); i++)
		{
			if (_filenames[i] == f) return _codes[i];
		}
		return 0;
	}

	void OnErrorClick(wxListEvent & event)
	{
		qError & e = _compileErrors[event.GetIndex()];
		int line = e.line - 1;

		for (int i = 0; i < _filenames.size(); i++)
		{
			if (_filenames[i] == e.file)
			{
				editors->SetSelection(i);
			}
		}
		if (line >= 0)
		EditorForCompiled(e.file)->ScrollToLine(line);
	}

	wxFont & Courier()
	{
		static wxFont * f = 0;
		if (!f)
		{
			HFONT ff = CreateFontA(16, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET,
				OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, (char*)"Courier New");
			wxNativeFontInfo nfi;
			nfi.SetPointSize(10);
			nfi.SetFaceName("Courier New");
			f = new wxFont(nfi, ff);
		}
		return *f;
	}
	void UpdateDirtyMarkers()
	{
		for (int i = 0; i < _filenames.size(); i++)
		{
			editors->SetPageText(i, ((_dirtyflag[i])?("* "):("")) + _filenames[i]);
		}

	}
	void onKeyPress(wxStyledTextEvent& evt)
	{
		wxStyledTextCtrl * ed = dynamic_cast<wxStyledTextCtrl*>(evt.GetEventObject());

		qString sss = evt.GetText().c_str().AsChar();
		int kk = evt.GetKey();

		if (kk == '(')
		{
			int  current = ed->GetCurrentLine();
			wxString line = ed->GetLine(current);			
			int  pos = ed->GetCurrentPos() - ed->PositionFromLine(current);

			int  startword  =  pos -  1;
			while  (startword  >  0  &&  isalnum(line[startword  -  1]))
				startword--;

			qString word = line.substr(startword,pos-startword-1).c_str().AsChar();


			if (functions.count(word))
			{
				qString ss;
				std::vector<qneu_Function *> & funs = functions[word];
				for (int i = 0; i < funs.size(); i++)
				{
					if (i) ss+="\n";
					ss += funs[i]->returntype->name() + " ";
					ss += funs[i]->name;
					ss += "(";
					for (int j = 0; j < funs[i]->args.size(); j++)
					{
						if (j) ss += ", ";
						ss += funs[i]->args[j].type->name() + " ";
						ss += funs[i]->args[j].name;
					}
					ss += ")";
				}
				ed->CallTipShow(ed->GetCurrentPos(), ss.c_str());
			}
		}
		if (kk == ')')
		{
			ed->CallTipCancel();
		}
		if (kk == '}')
		{
			int curLine = ed->GetCurrentLine();
			ed->SetLineIndentation(curLine, std::max(0, ed->GetLineIndentation(curLine) - 4));			
		}
		if  (kk  ==  '\r'  ||  kk  ==  '\n')  
		{
			int curLine = ed->GetCurrentLine();
			int lineLength = ed->GetLineLength(curLine);
			if (curLine > 0 && lineLength <= 2)  
			{
				int prevLineLength = ed->GetLineLength(curLine - 1);			
				wxString line = ed->GetLine(curLine - 1);
				wxString prepend;
				qString qline = line.c_str().AsChar();
				
				for (int i = 0; i < line.length(); i++)
				{
					if (line[i] == ' ' || line[i] == '\t') prepend += line[i];
					else break;
				}
				if (trim(qline) == "{") prepend += "\t";
				
				ed->ReplaceSelection(prepend);
			}
		}
	}

    void onTextChange(wxStyledTextEvent& evt)
	{
		wxStyledTextCtrl * ed = dynamic_cast<wxStyledTextCtrl*>(evt.GetEventObject());

		int f = evt.GetModificationType();
		if (f & (wxSTC_MOD_INSERTTEXT | wxSTC_MOD_DELETETEXT | wxSTC_MOD_CHANGEFOLD))
		{
			for (int i = 0; i < _filenames.size(); i++)
			{
				if (_codes[i] == ed)
				{
					_dirtyflag[i] = true;
				}
			}

			UpdateDirtyMarkers();
		}
	}
	void AddFile(wxString filename)
	{
		wxString ff = filename.substr(2);

		FILE * f = fopen(filename.c_str(), "rb");
		if (!f) *(int*)0 = 0;

		fseek(f, 0, SEEK_END);
		int l = ftell(f);
		fseek(f, 0, SEEK_SET);

		char * data = new char[l];
		fread(data, 1, l, f);
		fclose(f);
		
		wxString txt(data, l);
		delete [] data;

		files->InsertItem(_codes.size(), ff);
		wxStyledTextCtrl * ed = new wxStyledTextCtrl (editors);
		_codes.push_back(ed);
		_filenames.push_back(ff);
		_dirtyflag.push_back(0);
		ed->AppendText(txt);
		editors->AddPage(ed, ff);

		ed->SetLexer(wxSTC_LEX_CPP);

		wxFont ffq = Courier();
		int q = ffq.GetPointSize();
		for (int Nr = 0; Nr < wxSTC_STYLE_LASTPREDEFINED; Nr++)
		{
			ed->StyleSetFont (Nr, ffq);
		}

		ed->StyleSetFont(STYLE_ANN, ffq);
		ed->StyleSetBackground(STYLE_ANN, wxColour(0x9999FF));

		ed->StyleSetFont(STYLE_ANN + 1, ffq);
		ed->StyleSetBackground(STYLE_ANN + 1, wxColour(0xC0FFFF));
		//ed->Indica

		ed->Connect(wxEVT_STC_MODIFIED, wxStyledTextEventHandler(MyFrame::onTextChange), NULL, this);
		ed->Connect(wxEVT_STC_CHARADDED, wxStyledTextEventHandler(MyFrame::onKeyPress), NULL, this);

		wxChar* MyKeyWords = 
			_T("for while if return struct int void float float4 cstring else break true false double int8 int16 int32 int64 uint8 uint16 uint32 uint64 byte typedef const");

		ed->StyleSetForeground(wxSTC_C_COMMENT, wxColor(0,100,0));
		ed->StyleSetForeground(wxSTC_C_COMMENTLINE, wxColor(0,125,0));
		ed->StyleSetForeground(wxSTC_C_STRING, wxColor(128,0,0));
		ed->StyleSetForeground(wxSTC_C_WORD, wxColor(0,0,200));
		ed->SetKeyWords(0,MyKeyWords);

		ed->SetTabWidth (4);
		ed->SetUseTabs (false);
		ed->SetTabIndents (true);
		ed->SetBackSpaceUnIndents (true);
		ed->SetIndent (4);

		ed->SetMarginType(0, wxSTC_MARGIN_NUMBER);
		ed->SetMarginWidth(0, ed->TextWidth(wxSTC_STYLE_LINENUMBER, "_99999"));

		//ed->OnChar
	}

	void ReloadFilesInProject()
	{
		_codes.clear();
		editors->DeleteAllPages();
		files->DeleteAllItems();

		wxString f = wxFindFirstFile("./*.dab");
		while ( !f.empty() )
		{
			AddFile(f);

			f = wxFindNextFile();
		}
	}

	void AddToolbarItem(int id, const char * name, int imgID)
	{		
		wxBitmap * bmp = CreateBitmapFromPngResource(imgID);
		toolBar->AddTool(id, bmp?*bmp:wxNullBitmap, wxNullBitmap, false, _toolbar_currentX, -1, (wxObject *) NULL, name);
		_toolbar_currentX += 16 + 5;
		delete bmp;
	}

	MyFrame() : wxFrame (NULL, -1, wxT("Dablang IDE"), wxPoint(300,100), wxSize(1100,700))
	{
		wxMenu* fileMenu = new wxMenu;
		wxMenuBar* menuBar = new wxMenuBar;

		fileMenu->Append(ID_SAVE, wxT("Save\tCtrl-S"));
		fileMenu->Append(ID_MENURUN, wxT("Run\tF5"));
		fileMenu->Append(ID_MENUUPDATE, wxT("Update this module\tF8"));
		fileMenu->Append (ID_MAINWIN_QUIT, wxT("&Quit"));
		menuBar->Append (fileMenu, wxT("&File"));
		SetMenuBar (menuBar);

		CreateStatusBar (2);
		SetStatusText (wxT("Hello!"));

		CreateToolBar(wxNO_BORDER|wxHORIZONTAL|wxTB_FLAT, ID_TOOLBAR);

		GetToolBar()->SetMargins( 2, 2 );

		wxBitmap* toolBarBitmaps[9];

		toolBar = GetToolBar();

		wxInitAllImageHandlers();

		_toolbar_currentX = 5;
		AddToolbarItem(wxID_NEW,		"New file",			IDX_NEW);
		AddToolbarItem(wxID_OPEN,		"Open file",		IDX_OPEN);
		AddToolbarItem(wxID_SAVE,		"Save file",		IDX_SAVE);
		toolBar->AddSeparator();
		AddToolbarItem(wxID_CUT,		"Cut",				IDX_CUT);
		AddToolbarItem(wxID_COPY,		"Copy",				IDX_COPY);
		AddToolbarItem(wxID_PASTE,		"Paste",			IDX_PASTE);
		toolBar->AddSeparator();
		AddToolbarItem(ID_DEFS,			"Fix definitions",	IDX_DEFS);
		toolBar->AddSeparator();
		AddToolbarItem(ID_COMPILE,		"Compile",			IDX_COMPILE);
		AddToolbarItem(ID_RUN,			"Run",				IDX_PLAY);
		AddToolbarItem(ID_RUNINTERNAL,	"Run internally",	IDX_PLAY_INTERNAL);
		AddToolbarItem(ID_PAUSE,		"Pause",			IDX_PAUSE);
		AddToolbarItem(ID_STOP,			"Stop",				IDX_STOP);

		toolBar->Realize();

		wxSplitterWindow * _splitglobal = new wxSplitterWindow(this, -1);
		wxSplitterWindow * _split = new wxSplitterWindow(_splitglobal, -1);


		editors = new wxNotebook(_split, wxID_ANY, wxDefaultPosition, wxDefaultSize);

		files = new wxListCtrl(_split, wxID_ANY, wxDefaultPosition, wxDefaultSize, /*wxLC_HRULES|wxLC_VRULES|*/wxLC_REPORT); 

		files->InsertColumn(0, "File");		

		_split->SplitVertically(editors, files);

		_tools = new wxNotebook(_splitglobal, wxID_ANY, wxDefaultPosition, wxDefaultSize);

		_errors = new wxListCtrl(_tools, ID_ERRORS, wxDefaultPosition, wxDefaultSize, /*wxLC_HRULES|wxLC_VRULES|*/wxLC_REPORT|wxLC_SINGLE_SEL); 
		_errors->InsertColumn(0, "");
		_errors->InsertColumn(1, "");
		_errors->InsertColumn(2, "Description");
		_errors->InsertColumn(3, "File");
		_errors->InsertColumn(4, "Line");
		_errors->InsertColumn(5, "Column");

		wxImageList * il = new wxImageList(16, 16);
		wxBitmap * b1 = CreateBitmapFromPngResource(IDX_IC_ERROR);
		wxBitmap * b2 = CreateBitmapFromPngResource(IDX_IC_WARNING);
		il->Add(*b1);
		il->Add(*b2);
		delete b1;
		delete b2;
		_errors->AssignImageList(il, wxIMAGE_LIST_SMALL); 

		_errors->SetColumnWidth(0, 25);
		_errors->SetColumnWidth(1, 35);
		_errors->SetColumnWidth(2, 600);
		_errors->SetColumnWidth(3, 150);

		_tools->AddPage(_errors, "Error List");

		_output = new wxTextCtrl(_tools, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_PROCESS_ENTER|wxTE_PROCESS_TAB|wxTE_RICH);
		
		_output->SetFont(Courier());
		_tools->AddPage(_output, "Output");

		_splitglobal->SplitHorizontally(_split, _tools);

		ReloadFilesInProject();

		_splitglobal->SetSashPosition(400);

		_splitglobal->SetSashGravity(1);

		_split->SetSashPosition(-200);
		_split->SetMinimumPaneSize(200);
		_split->SetSashGravity(1);
		_split->UpdateSize();
		_split->SetSashPosition(-200);
		_split->UpdateSize();
	}

	void updateOutput(const qString & s)
	{
		_output->AppendText(s.c_str());
	}
	void clearOutput()
	{
		_output->Clear();
	}

	void OnToolCompile(wxCommandEvent& event)
	{
		if (Compile())
		{
			SetStatusText("Build successful!");
		}
		else
		{
			SetStatusText("Build failed!");
		}		
	}

	void OnToolRunInternal(wxCommandEvent& event)
	{
		Subrun(true);
	}

	void OnToolRun(wxCommandEvent& event)
	{
		Subrun(false);		
	}

	void Subrun(bool internal)
	{
		bool dablangIsProcessRunning();
		if (dablangIsProcessRunning())
		{
			if (wxNO == wxMessageBox("Application is already running. Do you want to restart it?", "Dablang IDE", wxYES_NO | wxCENTRE | wxICON_EXCLAMATION))
				return;
			else
			{  StopProcIfRunning(); }
		}
		if (Compile())
		{
			clearOutput();
			Run(internal);
		}
	}

	void OnMenuRun(wxCommandEvent& Event)
	{
		Subrun(false);			
	}
	
	void OnMenuSave (wxCommandEvent& Event)
	{
		OnToolSave(wxCommandEvent());
	}

	void OnToolStop(wxCommandEvent& event) { void StopProcIfRunning(); StopProcIfRunning(); }

	void OnToolDefs(wxCommandEvent& event)
	{
		int s = editors->GetSelection();

		_codes[s]->SetText(FixDefsText(_codes[s]->GetText().c_str().AsChar()).c_str());
	}

	void OnToolSave(wxCommandEvent& event)
	{
		int s = editors->GetSelection();

		wxString body = _codes[s]->GetText();
		wxString fn = _filenames[s];

		_dirtyflag[s] = 0;

		UpdateDirtyMarkers();

		setFile(fn.c_str().AsChar(), body.c_str().AsChar());
	}

	DECLARE_EVENT_TABLE()
};
void MyFrame::OnQuit (wxCommandEvent& WXUNUSED(Event))
{
	Close (true);
}

IMPLEMENT_APP_NO_MAIN(MyApp)
BEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_MENU(ID_SAVE, MyFrame::OnMenuSave)
EVT_MENU(ID_MENURUN, MyFrame::OnMenuRun)
EVT_MENU(ID_MENUUPDATE, MyFrame::OnMenuRunUpdate)
EVT_MENU(ID_MAINWIN_QUIT, MyFrame::OnQuit)
EVT_TOOL(ID_COMPILE, MyFrame::OnToolCompile)
EVT_TOOL(ID_RUN, MyFrame::OnToolRun)
EVT_TOOL(ID_DEFS, MyFrame::OnToolDefs)
EVT_TOOL(ID_RUNINTERNAL, MyFrame::OnToolRunInternal)
EVT_TOOL(ID_STOP, MyFrame::OnToolStop)
EVT_TOOL(wxID_SAVE, MyFrame::OnToolSave)
EVT_LIST_ITEM_ACTIVATED(ID_ERRORS, MyFrame::OnErrorClick)
END_EVENT_TABLE()

MyFrame * frame = 0;

void clearOutput()
{
	frame->clearOutput();
}
void updateOutput(const qString & s)
{
	if (frame)
	frame->updateOutput(s);
}

bool MyApp::OnInit()
{
	frame = new MyFrame;
	frame->Show();

	_CrtSetDbgFlag (0);

	return true;
}

void goIDE() { wxEntry(0,0); }

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) 
{
	goIDE();
	return 0;
}
