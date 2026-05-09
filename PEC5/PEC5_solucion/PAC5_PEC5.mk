##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=PAC5_PEC5
ConfigurationName      :=Debug
WorkspaceConfiguration := $(ConfigurationName)
WorkspacePath          :=/home/uoc/Documents/PAC5_PEC5_20252
ProjectPath            :=/home/uoc/Documents/PAC5_PEC5_20252/PAC5_PEC5
IntermediateDirectory  :=../build-$(ConfigurationName)/PAC5_PEC5
OutDir                 :=../build-$(ConfigurationName)/PAC5_PEC5
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=uoc
Date                   :=04/28/26
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
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)./include 
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
Objects0=../build-$(ConfigurationName)/PAC5_PEC5/src_order.c$(ObjectSuffix) ../build-$(ConfigurationName)/PAC5_PEC5/src_main.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: MakeIntermediateDirs $(OutputFile)

$(OutputFile): ../build-$(ConfigurationName)/PAC5_PEC5/.d $(Objects) 
	@mkdir -p "../build-$(ConfigurationName)/PAC5_PEC5"
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@mkdir -p "../build-$(ConfigurationName)/PAC5_PEC5"
	@mkdir -p ""../build-$(ConfigurationName)/bin""

../build-$(ConfigurationName)/PAC5_PEC5/.d:
	@mkdir -p "../build-$(ConfigurationName)/PAC5_PEC5"

PreBuild:


##
## Objects
##
../build-$(ConfigurationName)/PAC5_PEC5/src_order.c$(ObjectSuffix): src/order.c ../build-$(ConfigurationName)/PAC5_PEC5/src_order.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/uoc/Documents/PAC5_PEC5_20252/PAC5_PEC5/src/order.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_order.c$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/PAC5_PEC5/src_order.c$(DependSuffix): src/order.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/PAC5_PEC5/src_order.c$(ObjectSuffix) -MF../build-$(ConfigurationName)/PAC5_PEC5/src_order.c$(DependSuffix) -MM src/order.c

../build-$(ConfigurationName)/PAC5_PEC5/src_order.c$(PreprocessSuffix): src/order.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/PAC5_PEC5/src_order.c$(PreprocessSuffix) src/order.c

../build-$(ConfigurationName)/PAC5_PEC5/src_main.c$(ObjectSuffix): src/main.c ../build-$(ConfigurationName)/PAC5_PEC5/src_main.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/uoc/Documents/PAC5_PEC5_20252/PAC5_PEC5/src/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_main.c$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/PAC5_PEC5/src_main.c$(DependSuffix): src/main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/PAC5_PEC5/src_main.c$(ObjectSuffix) -MF../build-$(ConfigurationName)/PAC5_PEC5/src_main.c$(DependSuffix) -MM src/main.c

../build-$(ConfigurationName)/PAC5_PEC5/src_main.c$(PreprocessSuffix): src/main.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/PAC5_PEC5/src_main.c$(PreprocessSuffix) src/main.c


-include ../build-$(ConfigurationName)/PAC5_PEC5//*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r $(IntermediateDirectory)


