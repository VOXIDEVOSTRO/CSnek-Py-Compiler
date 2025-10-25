Ccmp      			:= gcc
CmpFlags  			:= -O2 -Wall -Wextra -std=c11


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
.PHONY: installLinux
InstallLinux: $(AllBins)
	sudo cp $(AllBins) /usr/local/bin/$(SnekCompiler)

#Clean
.PHONY: Clean
Clean:
	rm -rf $(TempBuild)