#pragma once

#include <vector>
#include <string>

struct AddressLookup
{
    // FThing()
	// {
	// }

    AddressLookup(const char* opcodes)
		: Opcodes(opcodes)
	{
	}

    const char *Opcodes;
    uintptr_t Address;
};

struct Functions
{
	static const AddressLookup FName_GetNames;
};

// Can be defined in CPP, different per SDK
const AddressLookup Functions::FName_GetNames("48 83 EC 28 ?? ?? ?? ?? ?? ?? ?? 48 85 C0 ?? ?? B9 08 08 00 00 48 89 5C 24 20");


struct Bla {
    typedef void (_stdcall *tBla) (int value);

    Bla(const char *opcodes) : Opcodes(opcodes)
    {        
    }

    const char *Opcodes;
    uintptr_t Address;

    tBla GetFunc() {
        return (tBla)Address;
    };
};

// Do we want to inherit like this? The final function
// shouldn't really care where it came from.
// On the other hand, we want to define them neatly.

// So we can pass this in to our pattern finding code
struct SomeStuff {
    const char *Opcodes;
};

// And this we can use to get the function
template<typename T>
struct XBla : SomeStuff {
    //typedef T;

    XBla(const char *InOpcodes) : Opcodes(InOpcodes)
    {        
    }

//    const char *Opcodes;
    T Function;

    // T GetFunc() {
    //     return (T)Address;
    // };
};

    // Some defaults for us.
    std::vector<AddressLookup> defaultFunctions = {Functions::FName_GetNames};

template <typename T> void f(T);
template <> void f<int>(int);

template <typename T>
void GetFunc() {

}

void MyTestCode() {

//    static const Bla apa("123");

    static const XBla<void (_stdcall *) (int value)> apa("123");
    static const XBla<int (_stdcall *) (const char *str)> Newest("123");
    apa.Function(23);
    Newest.Function("hej");

    //using ::f;
    //f(2,3);
    //using Vector = ::f<int,int>;
    //GetFunc<Functions::FName_GetNames>()
}