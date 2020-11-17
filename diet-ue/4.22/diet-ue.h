#pragma once

// Only included so my IDE stops complaining. /FI included at compile time anyway
#include "defines.h"

#include <Version.h>

// Core stuff
#include <UObject\Object.h>
#include <UObject\Class.h>
#include <HAL\ConsoleManager.h>
#include <UObject\UObjectArray.h>
#include <UObject\UObjectIterator.h>

//#include <HAL\UnrealMemory.h>


// Not core
#include <Engine\Engine.h>
#include <Engine\Console.h>
#include <Engine\World.h>
#include <Engine\GameViewportClient.h>

// Console
#include <Engine\LocalPlayer.h>


class UFont : UObject {

};
