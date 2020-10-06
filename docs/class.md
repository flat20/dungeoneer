// Generated using ReClass 2016

class N00000012;
class N00000022;
class N00000025;
class FUObjectArray;
class N00000037;
class N0000003A;
class N00000041;
class N00000044;
class N0000004F;
class N00000054;
class N00000057;
class N0000005A;
class N0000005D;
class N00000067;
class FUObjectItem;
class N00000073;
class UObject;
class N00000097;
class N0000009D;
class N000000A5;
class N000000A9;
class N000000AD;
class N000000B0;
class N000000BB;
class N000000C8;

class N00000012
{
public:
	__int32 N00000013; //0x0000 
	__int32 N0000001C; //0x0004 
	__int32 N00000014; //0x0008 
	__int32 N0000001F; //0x000C 
	N00000022* N00000015; //0x0010 
	char pad_0x0018[0x28]; //0x0018

}; //Size=0x0040

class N00000022
{
public:
	N00000025* N00000023; //0x0000 

}; //Size=0x0008

class N00000025
{
public:
	char pad_0x0000[0x8]; //0x0000

}; //Size=0x0008

class FUObjectArray
{
public:
	__int32 ObjFirstGCIndex; //0x0000 
	__int32 ObjLastNonGCIndex; //0x0004 
	__int32 MaxObjectsNotConsideredByGC; //0x0008 
	unsigned char OpenForDisregardForGC; //0x000C 
	char pad_0x000D[0x3]; //0x000D
	__int64 TUObjectArrayObjectsPtrPtr; //0x0010 
	__int64 TUObjectArrayPreAllocatedObjectsPtr; //0x0018 
	__int32 TUObjectArrayMaxElements; //0x0020 
	__int32 TUObjectArrayNumElements; //0x0024 
	__int32 TUObjectArrayMaxChunks; //0x0028 
	__int32 TUObjectArrayNumChunks; //0x002C 
	char pad_0x0030[0x10]; //0x0030

}; //Size=0x0040

class N00000037
{
public:
	char pad_0x0000[0x8]; //0x0000

}; //Size=0x0008

class N0000003A
{
public:
	char pad_0x0000[0x8]; //0x0000

}; //Size=0x0008

class N00000041
{
public:
	char pad_0x0000[0x8]; //0x0000

}; //Size=0x0008

class N00000044
{
public:
	char pad_0x0000[0x8]; //0x0000

}; //Size=0x0008

class N0000004F
{
public:
	char pad_0x0000[0x8]; //0x0000

}; //Size=0x0008

class N00000054
{
public:
	char pad_0x0000[0x8]; //0x0000

}; //Size=0x0008

class N00000057
{
public:
	char pad_0x0000[0x8]; //0x0000

}; //Size=0x0008

class N0000005A
{
public:
	char pad_0x0000[0x8]; //0x0000

}; //Size=0x0008

class N0000005D
{
public:
	N00000067 N0000005E[8]; //0x0000 

}; //Size=0x0040

class N00000067
{
public:
	char pad_0x0000[0x8]; //0x0000

}; //Size=0x0008

class FUObjectItem
{
public:
	__int64 UObjectBasePtr; //0x0000 
	__int32 Flags; //0x0008 
	__int32 ClusterRootIndex; //0x000C 
	__int32 SerialNumber; //0x0010 
	DWORD UnknownAlign; //0x0014 
	char pad_0x0018[0x28]; //0x0018

}; //Size=0x0040

class N00000073
{
public:
	char pad_0x0000[0x8]; //0x0000

}; //Size=0x0008

class UObject
{
public:
	virtual void Function0(); //
	virtual void Function1(); //
	virtual void Function2(); //
	virtual void Function3(); //
	virtual void Function4(); //
	virtual void Function5(); //
	virtual void Function6(); //
	virtual void Function7(); //
	virtual void Function8(); //
	virtual void Function9(); //

	__int32 EObjectFlags; //0x0008 
	__int32 InternalIndex; //0x000C 
	N00000097* UClassPrivate; //0x0010 
	__int32 FNameIndex; //0x0018 
	__int32 FNameNumber; //0x001C 
	N0000009D* Outer; //0x0020 
	char pad_0x0028[0x18]; //0x0028

}; //Size=0x0040

class N00000097
{
public:
	char pad_0x0000[0x8]; //0x0000

}; //Size=0x0008

class N0000009D
{
public:
	char pad_0x0000[0x8]; //0x0000

}; //Size=0x0008

class N000000A5
{
public:
	char pad_0x0000[0x8]; //0x0000

}; //Size=0x0008

class N000000A9
{
public:
	char pad_0x0000[0x8]; //0x0000

}; //Size=0x0008

class N000000AD
{
public:
	char pad_0x0000[0x8]; //0x0000

}; //Size=0x0008

class N000000B0
{
public:
	char pad_0x0000[0x8]; //0x0000

}; //Size=0x0008

class N000000BB
{
public:
	N000000C8* HashNext; //0x0000 
	__int32 Index; //0x0008 
	char N000000CB[64]; //0x1BD3E9C0 
	char pad_0x004C[0x7A8]; //0x004C

}; //Size=0x07F4

class N000000C8
{
public:
	char pad_0x0000[0x8]; //0x0000

}; //Size=0x0008

