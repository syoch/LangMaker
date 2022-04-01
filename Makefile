TARGET	= lm

HEADER	= lang.h
SOURCES	= $(wildcard *.cc)
OBJECTS	= $(SOURCES:.cc=.o)

COMMON		= -O2
CXXFLAGS	= $(COMMON) -std=c++20 
LDFLAGS		= -Wl,--gc-sections

all: $(TARGET)

clean:
	@rm -rf $(TARGET) *.o

re: clean all

debug:
	@$(MAKE) --no-print-directory COMMON="-g -O0" -f $(CURDIR)/Makefile

%.o: %.cc
	@echo $<
	@clang++ $(CXXFLAGS) -c -o $@ $<

$(TARGET): $(OBJECTS)
	@echo linking...
	@clang++ $(LDFLAGS) -o $@ $^