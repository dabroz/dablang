#include "stdafx.h"
#include "dab_header.h"

qneu_Type * tryret(qValue * binop, qneu_Type *v,qneu_Type * tt,const qString & c, const char * dat[], int count, qneu_Type * uptype = 0)
{
	if (v) return v;
	qString xname = binop->name;
	for (int i =0;i<count;i++) 
	{
		if (c==dat[i]) 
		{
			if (uptype)
			{
				if (binop->L()->neu_type != uptype)
				{
					char msg[9999];
					sprintf(msg,"Argument 1 of `%s`: ", xname.c_str());
					qValue * cc = new qConvert(uptype, binop->L(), msg);
					binop->replace_child(binop->L(), cc);
				}
				if (binop->R()->neu_type != uptype)
				{
					char msg[9999];
					sprintf(msg,"Argument 2 of `%s`: ", xname.c_str());
					qValue * cc = new qConvert(uptype, binop->R(), msg);
					binop->replace_child(binop->R(), cc);
				}
			}
			return tt;
		}
	}
	return v;
}

typedef qneu_PrimitiveType qpe;

qneu_Type * upgradebinop(qValue * binop, int LR, qneu_Type * T)
{
	char msg[9999];
	sprintf(msg,"Argument %d of `%s`: ", LR+1, binop->name.c_str());
	qValue * v = (LR==0)?(binop->L()):(binop->R());
	binop->replace_child(v, new qConvert(T, v, msg));
	return T;
}

qneu_Type * boolupgradebinop(qValue * binop, int LR, qneu_Type * T)
{
	upgradebinop(binop,LR,T);
	return qpe::type_bool();
}

qneu_Type * type_for_binop(qValue * binop, const qString & c, const qString & name, qneu_PrimitiveType * L, qneu_PrimitiveType * R)
{
	if (name == "add" || name == "sub" || name == "mul" || name == "div" || name == "or" || name == "and" || name == "min" || name == "max")
	{
		if (0) {}
		else if (L->is_integer() && R->is_float()) return upgradebinop(binop, 0, R);
		else if (L->is_float() && R->is_integer()) return upgradebinop(binop, 1, L);
		else if ((L->is_float() && R->is_float()) ||  (L->is_integer() && R->is_integer()))
		{
			if (0) {}
			else if (L->ssize() < R->ssize()) return upgradebinop(binop, 0, R);
			else if (L->ssize() > R->ssize()) return upgradebinop(binop, 1, L);
			else return L;
		}
	}

	if (name == "lt" || name == "gt")
	{
		if (0) {}
		else if (L->is_integer() && R->is_float()) return boolupgradebinop(binop, 0, R);
		else if (L->is_float() && R->is_integer()) return boolupgradebinop(binop, 1, L);
		else if ((L->is_float() && R->is_float()) ||  (L->is_integer() && R->is_integer()))
		{
			if (0) {}
			else if (L->ssize() < R->ssize()) return boolupgradebinop(binop, 0, R);
			else if (L->ssize() > R->ssize()) return boolupgradebinop(binop, 1, L);
			else return qpe::type_bool();
		}
	}

	if (name == "eq" || name == "neq" || name == "bor"  || name == "band")
	{
		if (0) {}
		else if (L->is_integer() && R->is_float()) return boolupgradebinop(binop, 0, R);
		else if (L->is_float() && R->is_integer()) return boolupgradebinop(binop, 1, L);
		else if ((L->is_float() && R->is_float()) ||  (L->is_integer() && R->is_integer()))
		{
			if (0) {}
			else if (L->ssize() < R->ssize()) return boolupgradebinop(binop, 0, R);
			else if (L->ssize() > R->ssize()) return boolupgradebinop(binop, 1, L);
			else return qpe::type_bool();
		}
		else if (L->is_bool() && R->is_bool()) return L;
		else if (L->is_bool()) return boolupgradebinop(binop, 1, L);
		else if (R->is_bool()) return boolupgradebinop(binop, 0, R);
	}

	qdterror("\n\nNo binop for `%s` `%s`\n\n", name.c_str(), c.c_str());
	return 0;
}

void qBinOp::subupdateType()
{
	neu_type = 0;

	qneu_Type * LT1 = L()->neu_type;
	qneu_Type * RT1 = R()->neu_type;

	qneu_PrimitiveType * LT = dynamic_cast<qneu_PrimitiveType*>(LT1);
	qneu_PrimitiveType * RT = dynamic_cast<qneu_PrimitiveType*>(RT1);

	if (LT && RT)
	{
		qString LLS = L()->dumprawX();
		qString RRS = R()->dumprawX();

		qString types = LT->mangle() + RT->mangle();

		qString codename = name+"_"+types;

		neu_type = type_for_binop(this, codename, name, LT, RT);
	}

	if (!neu_type)
	{
		char msg[2000];
		sprintf(msg, "Cannot match binary operator `%s` for `%s` and `%s`.", name.c_str(), (LT)?(LT->name().c_str()):"???", (RT)?(RT->name().c_str()):"???");
		fireError(true, ERROR_NO_BINOP, msg);
	}
}

llvm::Value * qBinOp::BuildValue()
{
	qString sL = L()->dumprawX();
	qString sR = R()->dumprawX();

	Value * QL = L()->BuildValue(),
		* QR = R()->BuildValue();
 
	qString codename = name+"_"+L()->neu_type->mangle() + R()->neu_type->mangle();

	qneu_Type * LT1 = L()->neu_type;
	qneu_Type * RT1 = R()->neu_type;

	qneu_PrimitiveType * LT = dynamic_cast<qneu_PrimitiveType*>(LT1);
	qneu_PrimitiveType * RT = dynamic_cast<qneu_PrimitiveType*>(RT1);

	if (LT->is_float())
	{
		if (name == "add")	return Builder.CreateFAdd(QL, QR);
		if (name == "sub")	return Builder.CreateFSub(QL, QR);
		if (name == "mul")	return Builder.CreateFMul(QL, QR);
		if (name == "div")	return Builder.CreateFDiv(QL, QR);
		if (name == "min")	return Builder.CreateSelect(Builder.CreateFCmpOLT(QL, QR), QL, QR);
		if (name == "max")	return Builder.CreateSelect(Builder.CreateFCmpOGT(QL, QR), QL, QR);
		if (name == "lt")	return Builder.CreateFCmpOLT(QL, QR);
		if (name == "gt")	return Builder.CreateFCmpOGT(QL, QR);
		if (name == "eq")	return Builder.CreateFCmpOEQ(QL, QR);
		if (name == "neq")	return Builder.CreateFCmpONE(QL, QR);
	}
	if (LT->is_integer())
	{
		if (name == "add")	return Builder.CreateAdd(QL, QR);
		if (name == "sub")	return Builder.CreateSub(QL, QR);
		if (name == "mul")	return Builder.CreateMul(QL, QR);		
		if (name == "or")	return Builder.CreateOr(QL, QR);
		if (name == "and")	return Builder.CreateAnd(QL, QR);
		if (name == "eq")	return Builder.CreateICmpEQ(QL, QR);
		if (name == "neq")	return Builder.CreateICmpNE(QL, QR);
		
		if (LT->is_unsigned())
		{
			if (name == "div")	return Builder.CreateUDiv(QL, QR);
			if (name == "lt")	return Builder.CreateICmpULT(QL, QR);
			if (name == "gt")	return Builder.CreateICmpUGT(QL, QR);
			if (name == "min")	return Builder.CreateSelect(Builder.CreateICmpULT(QL, QR), QL, QR);
			if (name == "max")	return Builder.CreateSelect(Builder.CreateICmpUGT(QL, QR), QL, QR);
		}
		else
		{
			if (name == "div")	return Builder.CreateSDiv(QL, QR);
			if (name == "lt")	return Builder.CreateICmpSLT(QL, QR);
			if (name == "gt")	return Builder.CreateICmpSGT(QL, QR);
			if (name == "min")	return Builder.CreateSelect(Builder.CreateICmpSLT(QL, QR), QL, QR);
			if (name == "max")	return Builder.CreateSelect(Builder.CreateICmpSGT(QL, QR), QL, QR);
		}
	}
	if (LT->is_bool())
	{
		if (name == "eq")	return Builder.CreateICmpEQ(QL, QR);
		if (name == "neq")	return Builder.CreateICmpNE(QL, QR);
		if (name == "band")	return Builder.CreateAnd(QL, QR);
		if (name == "bor")	return Builder.CreateOr(QL, QR);
	}	
	qdterror("binop 0");
	return 0;
}

qString qBinOp::print( int indent )
{
	if (name == "min" || name == "max")
	{
		return name + "(" + L()->print() + ", " + R()->print() + ")";
	}

	return "(" + L()->print() + " " + binSym(name) + " " + R()->print() + ")";
}

qBinOp::qBinOp( const char * _name, qValue * left, qValue * right )
{
	this->name = _name;
	insert(left);
	insert(right);
}
