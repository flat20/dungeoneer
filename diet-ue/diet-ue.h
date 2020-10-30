
#include <UObject\Object.h>
#include <UObject\Class.h>
#include <HAL\ConsoleManager.h>
#include <UObject\UObjectArray.h>
#include <UObject\UObjectIterator.h>

//#include <Engine\World.h>
// Try just this one?
//D:\UnrealEngine-4.22\Engine\Source\Runtime\Core\Public\CoreMinimal.h
// UE SDK has generated .h files. Wonder how one can make them.
// D:\UE_4.22\Engine\Intermediate\Build\Win64\UE4\Inc\
//

class AActor : UObject {
	// todo
};

class UFont : UObject {

};

class UConsole : UObject {
};


enum class ESpawnActorCollisionHandlingMethod : uint8
{
	/** Fall back to default settings. */
	Undefined,
	/** Actor will spawn in desired location, regardless of collisions. */
	AlwaysSpawn,
	/** Actor will try to find a nearby non-colliding location (based on shape components), but will always spawn even if one cannot be found. */
	AdjustIfPossibleButAlwaysSpawn,
	/** Actor will try to find a nearby non-colliding location (based on shape components), but will NOT spawn unless one is found. */
	AdjustIfPossibleButDontSpawnIfColliding,
	/** Actor will fail to spawn. */
	DontSpawnIfColliding,
};

struct FActorSpawnParameters
{
	//FActorSpawnParameters();

	/* A name to assign as the Name of the Actor being spawned. If no value is specified, the name of the spawned Actor will be automatically generated using the form [Class]_[Number]. */
	FName Name;

	/* An Actor to use as a template when spawning the new Actor. The spawned Actor will be initialized using the property values of the template Actor. If left NULL the class default object (CDO) will be used to initialize the spawned Actor. */
	AActor* Template;

	/* The Actor that spawned this Actor. (Can be left as NULL). */
	AActor* Owner;

	/* The APawn that is responsible for damage done by the spawned Actor. (Can be left as NULL). */
	//APawn*	Instigator;
	void* Instigator;

	/* The ULevel to spawn the Actor in, i.e. the Outer of the Actor. If left as NULL the Outer of the Owner is used. If the Owner is NULL the persistent level is used. */
	class	ULevel* OverrideLevel;

	/** Method for resolving collisions at the spawn point. Undefined means no override, use the actor's setting. */
	ESpawnActorCollisionHandlingMethod SpawnCollisionHandlingOverride;

private:


	/* Is the actor remotely owned. This should only be set true by the package map when it is creating an actor on a client that was replicated from the server. */
	uint16	bRemoteOwned:1;
	
public:

	bool IsRemoteOwned() const { return bRemoteOwned; }

	/* Determines whether spawning will not fail if certain conditions are not met. If true, spawning will not fail because the class being spawned is `bStatic=true` or because the class of the template Actor is not the same as the class of the Actor being spawned. */
	uint16	bNoFail:1;

	/* Determines whether the construction script will be run. If true, the construction script will not be run on the spawned Actor. Only applicable if the Actor is being spawned from a Blueprint. */
	uint16	bDeferConstruction:1;
	
	/* Determines whether or not the actor may be spawned when running a construction script. If true spawning will fail if a construction script is being run. */
	uint16	bAllowDuringConstructionScript:1;

#if WITH_EDITOR
	/** Determines whether the begin play cycle will run on the spawned actor when in the editor. */
	uint16 bTemporaryEditorActor:1;
#endif
	
	/* Flags used to describe the spawned actor/object instance. */
	EObjectFlags ObjectFlags;		
};


struct UEngine : UObject {
	// This stuff is pretty pointless now because we can just reflection our way
	// to any UObject property, such as the GameViewport
	char unknown[0x748 - sizeof(UObject)];
//	class IEngineLoop* EngineLoop;
	void* EngineLoop;				// At 0x748
	class UGameViewportClient* GameViewport;	// At 0x750

};

namespace diet {
	class FRawObjectIterator : public FUObjectArray::TIterator
	{
	public:
		FRawObjectIterator( const FUObjectArray& InArray, bool bOnlyGCedObjects = false ) : FUObjectArray::TIterator(InArray, bOnlyGCedObjects)
		{
		}

		/**
		 * Iterator dereference
		 * @return	the object pointer pointed at by the iterator
		 */
		FORCEINLINE FUObjectItem* operator*() const
		{
			// casting UObjectBase to UObject for clients
			return GetObject();
		}
		/**
		 * Iterator dereference
		 * @return	the object pointer pointed at by the iterator
		 */
		FORCEINLINE FUObjectItem* operator->() const
		{
			return GetObject();
		}
	};
}