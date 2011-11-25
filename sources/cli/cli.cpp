#include "stdafx.h"

qString cli_read_file(const qString & fn)
{
	FILE * f = fopen(fn.c_str(), "rb");
	if (!f) *(int*)0 = 0;

	fseek(f, 0, SEEK_END);
	int l = ftell(f);
	fseek(f, 0, SEEK_SET);

	char * data = new char[l+1];
	fread(data, 1, l, f);
	fclose(f);

	data[l] = 0;

	qString ret = data;

	delete [] data;

	return ret;
}

int main(int argc, char ** argv)
{
	if (argc < 2) return 1;
	std::map<qString, qString> files;
	for (int i = 1; i < argc; i++)
	{
		printf("Compile: `%s`\n", argv[i]);
		files[argv[i]] = cli_read_file(argv[i]);
	}
	printf("----------------\n\n");
	dab_CompileFiles(files, 0);
	return 0;
}
