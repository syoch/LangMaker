TARGET	= lm

BUILD		= build
INCLUDE	= include
SOURCE	= src

CXXFLAGS	= $(INCLUDES) -g -O1 -std=c++20
LDFLAGS		= -Wl,--gc-sections

%.o: %.cc
	@echo $(notdir $<)
	@$(CC) -MP -MMD -MF $*.d $(CXXFLAGS) -c -o $@ $<

ifneq ($(notdir $(CURDIR)),$(BUILD))

export OUTPUT		= $(CURDIR)/$(TARGET)
export INCLUDES	= $(foreach dir,$(INCLUDE),-I$(dir))
export VPATH		= $(SOURCE)

CXXFILES	= $(foreach dir,$(SOURCE),$(notdir $(wildcard $(dir)/*.cc)))

export OBJECTS	= \
	$(CXXFILES:.cc=.o)

all: $(BUILD)

$(BUILD):
	@[ -d $@ ] || mkdir -p $@
	@$(MAKE) --no-print-directory -C $@ -f $(CURDIR)/Makefile

clean:
	@rm -rf build
	@rm -f $(TARGET)

re: clean all

.PHONY: $(BUILD)

else

DEPENDS	= $(OBJECTS:.o=.d)

$(OUTPUT): $(OBJECTS)
	@echo linking...
	@$(CC) $(LDFLAGS) -o $@ $^

-include $(DEPENDS)

endif