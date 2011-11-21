#include "stdafx.h"
#include "dab_header.h"

IRBuilder<> Builder(getGlobalContext());

qneu_PointerType * qneu_PointerType::get(dt_BaseType * basetype, bool ptrconst)
{
	if (ptrconst)
	{
		if (basetype->ptrconsttype == 0)
			basetype->ptrconsttype = new qneu_PointerType(basetype, true);

		return basetype->ptrconsttype;
	}
	else
	{
		if (basetype->ptrtype == 0)
			basetype->ptrtype = new qneu_PointerType(basetype, false);

		return basetype->ptrtype;
	}
}

bool qneu_PrimitiveType::can_cast_to(dt_BaseType * other) const
{
	qneu_PrimitiveType* pother = dynamic_cast<qneu_PrimitiveType*>(other);
	if (!pother) return false;
	if (is_integer() && pother->ptype == TYPE_DOUBLE) return true;
	if (is_integer() && pother->ptype == TYPE_FLOAT) return true;
	if (is_integer() && pother->ptype == TYPE_BOOL) return true;
	if (is_integer() && pother->is_integer()) return true;
	if (ptype == TYPE_FLOAT && pother->ptype == TYPE_BOOL) return true;
	if (ptype == TYPE_FLOAT && pother->ptype == TYPE_DOUBLE) return true;

	int qdtprintf(const char * format, ...);

	qdtprintf2("!! CANNOT CAST primitive `%s` into `%s`\n", name().c_str(), pother->name().c_str());

	return false;
}

llvm::Type * qneu_PointerType::llvm()
{
	Type * basetype = base->llvm();
	if (!basetype)
	{
		basetype = base->llvm();
	}
	return PointerType::getUnqual(basetype);
}

llvm::Type * qneu_PrimitiveType::llvm()
{
	llvm::LLVMContext & c = llvm::getGlobalContext();
	
	switch (ptype)
	{
	case TYPE_INT8:		return Type::getInt8Ty(c);
	case TYPE_INT16:	return Type::getInt16Ty(c);
	case TYPE_INT32:	return Type::getInt32Ty(c);
	case TYPE_INT64:	return Type::getInt64Ty(c);
	case TYPE_UINT8:	return Type::getInt8Ty(c);
	case TYPE_UINT16:	return Type::getInt16Ty(c);
	case TYPE_UINT32:	return Type::getInt32Ty(c);
	case TYPE_UINT64:	return Type::getInt64Ty(c);
	case TYPE_DOUBLE:	return Type::getDoubleTy(c);
	case TYPE_FLOAT:	return Type::getFloatTy(c);
	case TYPE_BOOL:		return Type::getInt1Ty(c);
	case TYPE_FLOAT4:	return VectorType::get(Type::getFloatTy(c), 4);
	default:		return 0;
	}

	return 0;
}

llvm::Type * qneu_StructType::llvm()
{
	if (cachetype) return cachetype;

	std::vector<llvm::Type*> params;
	for (int i = 0; i < members.size(); i++)
	{
		llvm::Type * t = members[i].type->llvm();	
		if (!t)
		{
			t = members[i].type->llvm();
			qdterror("No LLVM type for `%s` member `%s`\n", name().c_str(), members[i].name.c_str());
			return 0;
		}
		params.push_back(t);
	}
	llvm::StructType * t = llvm::StructType::get(llvm::getGlobalContext(), params, false);

	// LLVM 3.0: TheModule->getTypeSymbolTable().insert(this->name(), t);

	cachetype = t;
	return t;
}

dt_BaseType * qneu_StructType::GetTypeFor(qString membname) 
{
	for (int i =0;i<members.size();i++) 
	{
		if (members[i].name == membname) return members[i].type;
	}
	return 0;
}

Value * qneu_StructType::getLllvVariable( qString name, Value * parent )
{
	int index = -1;
	for (int i = 0; i < members.size(); i++)
	{
		if (members[i].name == name) index = i;
	}
	
	Value * const gepp[2] = {
	ConstantInt::get(Type::getInt32Ty(getGlobalContext()), 0), 
	ConstantInt::get(Type::getInt32Ty(getGlobalContext()), index) 
	};
	
	return Builder.CreateGEP(parent, llvm::ArrayRef<Value*>(gepp));
}

dt_BaseType *  qneu_RawType::updateWithType( const qString & newname,dt_BaseType * s )
{
	if (tname == newname && is_const == s->is_const)
	{
		return s;
	}
	return this;
}

bool qneu_PointerType::can_cast_to( dt_BaseType * other ) const
{
	if (other->isPointer()) return true;
	if (other->is_integer()) return true;

	return false;
}

llvm::Type * qneu_ArrayType::llvm()
{
	return ArrayType::get(base->llvm(), size);
}

bool qneu_ArrayType::can_cast_to( dt_BaseType * other ) const
{
	if (other->isPointer()) return true;
	return false;
}

qString qneu_ArrayType::name() const
{
	char msg[2000];
	sprintf(msg, "%s[%d]", base->name().c_str(), size);
	return msg;
}

qString qneu_ArrayType::mangle() const
{
	char msg[2000];
	sprintf(msg, "a%d%s", size, base->mangle().c_str());
	return msg;
}

qneu_ArrayType * qneu_ArrayType::get( dt_BaseType * basetype, qValue * size )
{
	int s = dynamic_cast<qConstant*>(size)->ivalue.x;

	if (basetype->arraytypes[s] == 0)
	{
		qneu_ArrayType * a = new qneu_ArrayType;

		a->base = basetype;
		a->size = s;

		basetype->arraytypes[s] = a;
	}

	return basetype->arraytypes[s];
}

dt_BaseType * dt_BaseType::CreateArray(qValue * size)
{
	return qneu_ArrayType::get(this, size);
}

dt_BaseType * qneu_ArrayType::updateWithType( const qString & newname,dt_BaseType * s )
{
	return base->updateWithType(newname,s)->CreateArray(new qConstant(TYPE_INT32, size));
}

llvm::Value * dt_BaseType::getLllvVariable( qString name, Value * parent )
{
	return 0;
}

dt_BaseType * dt_BaseType ::createPointer()
{
	return qneu_PointerType::get(this, false);
}

dt_BaseType * dt_BaseType ::createConstPointer()
{
	return qneu_PointerType::get(this, true);
}
