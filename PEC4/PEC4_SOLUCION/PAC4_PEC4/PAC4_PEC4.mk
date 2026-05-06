##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=PAC4_PEC4
ConfigurationName      :=Debug
WorkspaceConfiguration := $(ConfigurationName)
WorkspacePath          :=/home/uoc/Documents/PAC4_PEC4_20252
ProjectPath            :=/home/uoc/Documents/PAC4_PEC4_20252/PAC4_PEC4
IntermediateDirectory  :=../build-$(ConfigurationName)/PAC4_PEC4
OutDir                 :=../build-$(ConfigurationName)/PAC4_PEC4
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=uoc
Date                   :=04/08/26
CodeLitePath           :=/home/uoc/.codelite
LinkerName             :=g++
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=../build-$(ConfigurationName)/bin/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :=$(IntermediateDirectory)/ObjectsList.txt
PCHCompileFlags        :=
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=../build-$(ConfigurationName)/PAC4_PEC4/main.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: MakeIntermediateDirs $(OutputFile)

$(OutputFile): ../build-$(ConfigurationName)/PAC4_PEC4/.d $(Objects) 
	@mkdir -p "../build-$(ConfigurationName)/PAC4_PEC4"
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@mkdir -p "../build-$(ConfigurationName)/PAC4_PEC4"
	@mkdir -p ""../build-$(ConfigurationName)/bin""

../build-$(ConfigurationName)/PAC4_PEC4/.d:
	@mkdir -p "../build-$(ConfigurationName)/PAC4_PEC4"

PreBuild:


##
## Objects
##
../build-$(ConfigurationName)/PAC4_PEC4/main.c$(ObjectSuffix): main.c ../build-$(ConfigurationName)/PAC4_PEC4/main.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/uoc/Documents/PAC4_PEC4_20252/PAC4_PEC4/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/PAC4_PEC4/main.c$(DependSuffix): main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/PAC4_PEC4/main.c$(ObjectSuffix) -MF../build-$(ConfigurationName)/PAC4_PEC4/main.c$(DependSuffix) -MM main.c

../build-$(ConfigurationName)/PAC4_PEC4/main.c$(PreprocessSuffix): main.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/PAC4_PEC4/main.c$(PreprocessSuffix) main.c


-include ../build-$(ConfigurationName)/PAC4_PEC4//*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r $(IntermediateDirectory)


