#pragma once

#define PRIMTYPE static qneu_PrimitiveType * ret = new qneu_PrimitiveType

class qneu_PrimitiveType : public qneu_Type
{
public:
	qneu_Type * constversion;

	int ptype;
	qString pname;
	qString pmangle;
	virtual qString name() const { return pname; }
	virtual bool isPrimitive() const { return true; }
	virtual qString mangle() const { return pmangle; }

	static qneu_PrimitiveType * type_int()    { return type_int32(); }

	virtual qneu_Type * CreateConst() { return constversion; }

	static qneu_PrimitiveType * consttype_double()  { PRIMTYPE(TYPE_DOUBLE,	"const_double", "Cl"); return ret; }
	static qneu_PrimitiveType * consttype_float()   { PRIMTYPE(TYPE_FLOAT,	"const_float", "Cf"); return ret; }
	static qneu_PrimitiveType * consttype_float4()  { PRIMTYPE(TYPE_FLOAT4,	"const_float4", "CF4"); return ret; }
	static qneu_PrimitiveType * consttype_bool()	{ PRIMTYPE(TYPE_BOOL,	"const_bool", "Cb"); return ret; }

	static qneu_PrimitiveType * type_double()  { PRIMTYPE(TYPE_DOUBLE,	"double", "l", consttype_double()); return ret; }
	static qneu_PrimitiveType * type_float()   { PRIMTYPE(TYPE_FLOAT,	"float", "f", consttype_float()); return ret; }
	static qneu_PrimitiveType * type_float4()  { PRIMTYPE(TYPE_FLOAT4,	"float4", "F4", consttype_float4()); return ret; }
	static qneu_PrimitiveType * type_bool()	   { PRIMTYPE(TYPE_BOOL,	"bool", "b", consttype_bool()); return ret; }

	static qneu_PrimitiveType * consttype_int8()    { PRIMTYPE(TYPE_INT8,	"const_int8",  "Ci1"); return ret; }
	static qneu_PrimitiveType * consttype_int16()   { PRIMTYPE(TYPE_INT16,	"const_int16", "Ci2"); return ret; }
	static qneu_PrimitiveType * consttype_int32()   { PRIMTYPE(TYPE_INT32,	"const_int32", "Ci4"); return ret; }
	static qneu_PrimitiveType * consttype_int64()   { PRIMTYPE(TYPE_INT64,	"const_int64", "Ci8"); return ret; }

	static qneu_PrimitiveType * consttype_uint8()   { PRIMTYPE(TYPE_UINT8,	"const_uint8",  "Cu1"); return ret; }
	static qneu_PrimitiveType * consttype_uint16()  { PRIMTYPE(TYPE_UINT16,	"const_uint16", "Cu2"); return ret; }
	static qneu_PrimitiveType * consttype_uint32()  { PRIMTYPE(TYPE_UINT32,	"const_uint32", "Cu4"); return ret; }
	static qneu_PrimitiveType * consttype_uint64()  { PRIMTYPE(TYPE_UINT64,	"const_uint64", "Cu8"); return ret; }

	static qneu_PrimitiveType * type_int8()    { PRIMTYPE(TYPE_INT8,	"int8",  "i1", consttype_int8()); return ret; }
	static qneu_PrimitiveType * type_int16()   { PRIMTYPE(TYPE_INT16,	"int16", "i2", consttype_int16()); return ret; }
	static qneu_PrimitiveType * type_int32()   { PRIMTYPE(TYPE_INT32,	"int32", "i4", consttype_int32()); return ret; }
	static qneu_PrimitiveType * type_int64()   { PRIMTYPE(TYPE_INT64,	"int64", "i8", consttype_int64()); return ret; }

	static qneu_PrimitiveType * type_uint8()   { PRIMTYPE(TYPE_UINT8,	"uint8",  "u1", consttype_uint8()); return ret; }
	static qneu_PrimitiveType * type_uint16()  { PRIMTYPE(TYPE_UINT16,	"uint16", "u2", consttype_uint16()); return ret; }
	static qneu_PrimitiveType * type_uint32()  { PRIMTYPE(TYPE_UINT32,	"uint32", "u4", consttype_uint32()); return ret; }
	static qneu_PrimitiveType * type_uint64()  { PRIMTYPE(TYPE_UINT64,	"uint64", "u8", consttype_uint64()); return ret; }

	virtual bool is_integer() const { return ptype >= TYPE_INT8 && ptype <= TYPE_UINT64; }

	virtual bool is_float() const { return ptype == TYPE_FLOAT || ptype == TYPE_DOUBLE; }
	virtual bool is_bool() const { return ptype == TYPE_BOOL; }

	virtual bool is_unsigned() const { return is_integer() && (ptype >= TYPE_UINT8 && ptype <= TYPE_UINT64); }
	virtual int ssize() const
	{
		switch(ptype)
		{
		case TYPE_BOOL: return 1;

		case TYPE_INT8:
		case TYPE_UINT8:
			return 8;

		case TYPE_INT16:
		case TYPE_UINT16:
			return 16;

		case TYPE_FLOAT:
		case TYPE_INT32:
		case TYPE_UINT32:
			return 32;

		case TYPE_INT64:
		case TYPE_UINT64:
		case TYPE_DOUBLE:
			return 64;

		case TYPE_FLOAT4:
			return 128;

		default:
			return -1;
		}
	}

	virtual bool can_cast_to(qneu_Type * other) const;

	virtual llvm::Type * llvm();
private:
	qneu_PrimitiveType(int type, const char * xname, const char * xmangle, qneu_Type * constrv = 0)
	{
		ptype = type; pname = xname; pmangle = xmangle; constversion = constrv;
		if (!constrv) is_const = true;
	}
};
