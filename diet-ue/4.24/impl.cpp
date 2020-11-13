#include "diet-ue.h"

//#include <HAL\FMemory.inl>

void* FGenericPlatformString::Memcpy(void* Dest, const void* Src, SIZE_T Count)
{
	return memcpy(Dest, Src, Count);
}


void *FMemory::Realloc(void* Original, SIZE_T Count, uint32 Alignment) {
	return realloc(Original, Count);
}
void FMemory::Free(void *Original) {
	if (Original == nullptr) {
		return;
	}

	free(Original);
}

SIZE_T FMemory::QuantizeSize(SIZE_T Count, uint32 Alignment) {
	return Count;
}


namespace UE4Delegates_Private
{
	TAtomic<uint64> GNextID(1);
}

uint64 FDelegateHandle::GenerateNewID()
{
	// Just increment a counter to generate an ID.
	uint64 Result = ++UE4Delegates_Private::GNextID;

	// Check for the next-to-impossible event that we wrap round to 0, because we reserve 0 for null delegates.
	if (Result == 0)
	{
		// Increment it again - it might not be zero, so don't just assign it to 1.
		Result = ++UE4Delegates_Private::GNextID;
	}

	return Result;
}
