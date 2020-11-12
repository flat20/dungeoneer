!INCLUDE <defaults.mak>

TARGET = dungeoneer.exe
SOURCES = launcher/*.cpp
BUILD_DIR = build/
OBJS = $(BUILD_DIR)*.obj

$(TARGET): $(OBJS)
	link /nologo /subsystem:console /DEBUG -OUT:$(TARGET) $(OBJS)

$(OBJS): $(SOURCES)
	cl /nologo /Fo.\$(BUILD_DIR)\ /c /EHsc launcher/$(@B).cpp
# I need to list one set of objects and then extract the .cpp name from that?
# $** to make things done once per entry?
# $<
# cl /nologo /EHsc ^
#      launcher\*.cpp ^
#      -link^
#       /subsystem:console /DEBUG -OUT:dungeoneer.exe
