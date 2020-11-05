#include "diet-ue.h"

#include <HAL\FMemory.inl>

// Some basic "fake" implementations of UE code.
// Saves us the hassle of including the entire UE source code when compiling.

void* FGenericPlatformString::Memcpy(void* Dest, const void* Src, SIZE_T Count)
{
	return FMemory::Memcpy(Dest, Src, Count);
}


//static FMalloc* GMalloc = FPlatformMemory::BaseAllocator();
CORE_API FMalloc*			GMalloc						= nullptr;

void* FMemory::MallocExternal(SIZE_T Count, uint32 Alignment)
{
    return malloc((size_t)Count);
}


void* FMemory::ReallocExternal(void* Original, SIZE_T Count, uint32 Alignment)
{
    free(Original);
    return malloc((size_t)Count);
}

void FMemory::FreeExternal(void* Original)
{
    free(Original);
}

// If possible determine allocated size at address. Let's not.
SIZE_T FMemory::GetAllocSizeExternal(void* Original)
{ 
    return 0;
}


FString FString::ToLower() const &
{
	FString New = *this;
	New.ToLowerInline();
	return New;
}

void FString::ToLowerInline()
{
	const int32 StringLength = Len();
	TCHAR* RawData = Data.GetData();
	for (int32 i = 0; i < StringLength; ++i)
	{
		RawData[i] = FChar::ToLower(RawData[i]);
	}
}


#pragma comment(linker, "/export:?ZeroVector@FVector@@2U1@B")
CORE_API const FVector FVector::ZeroVector(0.0f, 0.0f, 0.0f);
