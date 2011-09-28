#pragma once

extern IRBuilder<> Builder;

const char * q_yy_buf(void*scanner);
size_t q_yy_pos(void*scanner);

void di_NotifyAboutType(const std::string & name, dt_BaseType * type, dab_Module * module);
qneu_StructType * di_CreateStruct(qStruct * str, dab_Module * module);

void CopyArgumentsToStack(dab_Function & fun);
void GatherVariables(dab_Function & fun);
void ResolveVariables(dab_Function & fun);
void CleanupVariables(dab_Function & fun);
void ResolveTypes(dab_Function & fun);
void BuildFunctions(dab_Function & fun);