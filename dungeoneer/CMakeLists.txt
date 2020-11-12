cmake_minimum_required(VERSION 2.4)

project(dungeoneer)
set(UE4_SDK_DIR "D:/UE_4.22")
set(UE4_INCLUDE_DIR "${UE4_SDK_DIR}/Engine/Source/Runtime")
set(UE4_GENERATED_DIR "${UE4_SDK_DIR}/Engine/Intermediate/Build/Win64/UE4/Inc")

message(STATUS "${MY_VARIABLE}")

#set(CMAKE_CXX_FLAGS "-std=c++14 -Wall ${CMAKE_CXX_FLAGS}")

include_directories(${PROJECT_SOURCE_DIR} ../unrealspy ../diet-ue ../imgui-1.78) # ${WinSDK}
include_directories(${UE4_INCLUDE_DIR}/Core/Public)
include_directories(${UE4_INCLUDE_DIR}/Core/Private)
include_directories(${UE4_INCLUDE_DIR}/CoreUObject/Public)
include_directories(${UE4_INCLUDE_DIR}/Engine/Public)
include_directories(${UE4_INCLUDE_DIR}/Engine/Classes)
include_directories(${UE4_INCLUDE_DIR}/EngineSettings/Classes)
include_directories(${UE4_INCLUDE_DIR}/InputCore/Classes)
include_directories(${UE4_INCLUDE_DIR}/RHI/Public)
include_directories(${UE4_INCLUDE_DIR}/RenderCore/Public)
include_directories(${UE4_INCLUDE_DIR}/SlateCore/Public)
include_directories(${UE4_INCLUDE_DIR}/AssetRegistry/Public)
include_directories(${UE4_INCLUDE_DIR}/ApplicationCore/Public)
#include_directories(${UE4_INCLUDE_DIR}/Renderer/Public)


include_directories(${UE4_GENERATED_DIR}/Engine)
include_directories(${UE4_GENERATED_DIR}/InputCore)
include_directories(${UE4_GENERATED_DIR}/EngineSettings)
include_directories(${UE4_GENERATED_DIR}/SlateCore)
#include_directories(${UE4_GENERATED_DIR}/AssetRegistry)
#include_directories(${UE4_GENERATED_DIR}/Slate)
#include_directories(${UE4_GENERATED_DIR}/AudioPlatformConfiguration)


aux_source_directory(imgui/ SRC_LIST)
aux_source_directory(../imgui-1.78/imgui/ SRC_LIST)

add_library(dungeoneer SHARED dll.cpp ui.cpp ${SRC_LIST} ../diet-ue/impl.cpp)

target_link_libraries(dungeoneer D:/winsdk/Lib/10.0.18362.0/um/x64/d3d11.lib D:/winsdk/Lib/10.0.18362.0/um/x64/d3dcompiler.lib)

#include(GenerateExportHeader)
#generate_export_header(dungeoneer)

# cmake -G "NMake Makefiles" .