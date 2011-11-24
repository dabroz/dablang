#include "stdafx.h"
#include "dab_header.h"
#include "dab_internal.h"

llvm::Value * qConvert::BuildValue()
{
	qString nn = L()->neu_type->mangle() + ">" + neu_type->mangle();

	Value * V = L()->BuildValue();
	Type * DT = neu_type->llvm();

	dt_BaseType * Ltype = L()->neu_type;
	dt_BaseType * Rtype = neu_type;

	qneu_PrimitiveType * LL = dynamic_cast<qneu_PrimitiveType *>(Ltype);
	qneu_PrimitiveType * RR = dynamic_cast<qneu_PrimitiveType *>(Rtype);

	qneu_PointerType * LLptr = dynamic_cast<qneu_PointerType*>(Ltype);
	qneu_PointerType * RRptr = dynamic_cast<qneu_PointerType*>(Rtype);

	if (qneu_ArrayType* LAR = dynamic_cast<qneu_ArrayType*>(Ltype))
	{
		if (RRptr)
		{

			Value * const gepp[2] = {
				Lconstant(0),
				Lconstant(0)
			};

			void llvm_dumpvaluetype(const char * ss,Value * v);
			Value *ret = Builder.CreateGEP(V, llvm::ArrayRef<Value*>(gepp));
			return ret;
		}
	}

	if (qneu_ArrayType* RAR = dynamic_cast<qneu_ArrayType*>(Rtype))
	{

	}

	if (dynamic_cast<qneu_CStringType*>(Ltype))
	{
		if (RRptr) return Builder.CreateBitCast(V, DT);
	}

	if (LLptr && RRptr)
	{
		return Builder.CreateBitCast(V, DT);
	}

	if (LLptr)
	{
		if (RR && RR->is_bool())	return Builder.CreateICmpNE(V, Builder.CreateIntToPtr(Lconstant(0), V->getType()));
		if (RR && RR->is_integer()) return Builder.CreatePtrToInt(V, DT);

	}
	if (RRptr)
	{
		if (LL && LL->is_integer()) return Builder.CreateIntToPtr(V, DT);

	}

	if (dynamic_cast<qneu_CStringType*>(neu_type))
	{
		Type * cst = Type::getInt8PtrTy(getGlobalContext());
		if (LLptr) return Builder.CreateBitCast(V, cst);
		if (LL->is_integer()) return Builder.CreateIntToPtr(V, cst);
	}

	if (LL && RR)
	{
		if (LL->is_integer() && RR->is_integer())
		{
			return Builder.CreateIntCast(V, DT, !RR->is_unsigned());
		}
		else if (LL->is_float() && RR->is_float())
		{
			return Builder.CreateFPCast(V, DT);
		}
		if (LL->is_float() && RR->is_integer())
		{
			if (RR->is_unsigned())
				return Builder.CreateFPToUI(V, DT);
			else 
				return Builder.CreateFPToUI(V, DT);
		}
		else if (LL->is_integer() && RR->is_float())
		{
			if (LL->is_unsigned())
				return Builder.CreateUIToFP(V, DT);
			else 
				return Builder.CreateSIToFP(V, DT);
		}
		else if (LL->is_integer() && RR->is_bool())
		{
			return Builder.CreateICmpNE(V, Builder.CreateIntCast(Lconstant(0), LL->llvm(), !LL->is_unsigned())); 
		}
		else if (LL->is_float() && RR->is_bool())
		{
			return Builder.CreateFCmpONE(V, Lconstant(0.0f));
		}
	}

	qdterror("\n\nbad cast: %s\n\n", nn.c_str());
	return 0;
}

qConvert::qConvert( dt_BaseType * type, qValue * val, const qString &extrainfo )
{
	{
		qString type1 = "[???]", type2 = "[???]", v = "[???]";
		if (val && val->neu_type) type1 = "`" + val->neu_type->name() + "`";
		if (type) type2 = "`" + type->name() + "`";
		if (val) v = "'" + val->dumprawX() + "'";
		//qdtprintf("~convert *%s* (%s -> %s) [%s]\n", extrainfo.c_str(), type1.c_str(), type2.c_str(), v.c_str());
	}

	bool forced=(extrainfo=="!!");

	insert(val);
	loc = val->loc;

	if (!type)
	{
		return;
	}

	if (!forced && !val->neu_type) return;

	neu_type = type;

	if (!forced)
	{
	if (val->neu_type)
		fireError(false, WARNI_IMPLICIT_CONVERT, extrainfo + "Implicit conversion from `" + val->neu_type->name() + "` to `" + type->name() + "`");
	else
		fireError(false, WARNI_IMPLICIT_CONVERT, extrainfo + "Implicit conversion from `[unknown type]` to `" + type->name() + "`");
	}
}

qString qConvert::print( int indent )
{
	if (!neu_type && !L()) return "[SUPER BAD CONVERT]";
	if (!neu_type) return "[BAD CONVERT]" + L()->print(0);
	return "(" + neu_type->name() + ")" + L()->print(0);
}
