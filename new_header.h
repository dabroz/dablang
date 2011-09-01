#pragma once

void debugqv(const char * name, ...);

#define DEBUGQ(...) debugqv(__FUNCTION__, ##__VA_ARGS__,0)

qString binSym(const qString &name);
qValue* qtree_type(qValue * v);

void low_ReplaceForWhile(qValue * program);
void low_UpdateVarReferences(qValue * q);
void low_GetStructs(qValue * tree);
void low_FixReturnConverts(qValue * tree);
void low_MoveDeclarations(qValue * tree);
void low_FindFunctions(qValue * pro);
void low_CheckTypes(qValue * v);

qString  RunLLVMBuilding(qValue * prog);

Value * Lconstant(int v);
Value * Lconstant(float v);
Value * Lconstant(bool v);

#include "qv_instruction.h"
#include "qv_constant.h"
#include "qv_assign.h"
#include "qv_block.h"
#include "qv_constant.h"
#include "qv_sequence.h"
#include "qv_funcall.h"
#include "qv_if.h"
#include "qv_while.h"
#include "qv_binop.h"
#include "qv_identifier.h"
#include "qv_return.h"
#include "qv_for.h"
#include "qv_program.h"
#include "qv_declare.h"
#include "qv_function.h"
#include "qv_struct.h"
#include "qv_member.h"
#include "qv_typeholder.h"
#include "qv_variable.h"
#include "qv_subvariable.h"
#include "qv_convert.h"
#include "qv_nop.h"
#include "qv_stackalloc.h"
#include "qv_externfunc.h"
#include "qv_string.h"
#include "qv_break.h"
#include "qv_pointer.h"
#include "qv_unop.h"
#include "qv_dereference.h"
#include "qv_typedef.h"
#include "qv_array.h"
