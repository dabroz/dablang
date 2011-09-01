#include <typeinfo>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

bool ShouldWriteOutput();

int qdtprintf(const char * format, ...);
int qdtprintf2(const char * format, ...);
void qdterror(const char * format, ...);

void replace_all(std::string &str, const std::string &find_what, const std::string &replace_with);

#include "header.h"
#include "qheader.h"
#include "new_header.h"

