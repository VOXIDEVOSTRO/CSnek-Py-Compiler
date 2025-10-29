Ccmp      			:= gcc
CmpFlags  			:= -O2 -Wall -Wextra -std=c11 -Wl,--no-undefined


SnekCompiler     	:= csnekpy


TempBuild 			:= .build
ObjectDirectory   	:= $(TempBuild)/Objects
FinalBuildDirectory := $(TempBuild)/bin
CSource  			:= $(shell find . -type f -name '*.c')
Objects  			:= $(patsubst ./%,%,$(CSource))
Objects  			:= $(patsubst %.c,$(ObjectDirectory)/%.o,$(Objects))
AllBins  			:= $(FinalBuildDirectory)/$(SnekCompiler)

CmpFlags			+= -IIncludes

#Default
.PHONY: All
All: $(AllBins)

$(AllBins): $(Objects) | $(FinalBuildDirectory)
	$(Ccmp) $(CmpFlags) -o $@ $(Objects)
$(ObjectDirectory)/%.o: %.c | $(ObjectDirectory)
	@mkdir -p $(dir $@)
	$(Ccmp) $(CmpFlags) -c $< -o $@
$(ObjectDirectory):
	mkdir -p $@
$(FinalBuildDirectory):
	mkdir -p $@

#Install System wide
Prefix ?= /usr/local
LinuxBin := $(Prefix)/bin

# Override with make InstallLinux Prefix=/usr (or whatever the system wide install path is)

.PHONY: installLinux
installLinux: $(AllBins)
	@mkdir -p $(LinuxBin)
	sudo cp $(AllBins) $(LinuxBin)/$(SnekCompiler)

#Clean
.PHONY: Clean
Clean:
	rm -rf $(TempBuild)