
MAKE_PATH:=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
PROJECT_PATH = $(shell dirname ${PWD})

export PROJECT_NAME = $(shell basename $(PROJECT_PATH))
export PROJECT_VERSION = $(shell git describe --tags | head -n1)

DOXYGEN_CMD = doxygen
FILES = $(shell find .. -name "*.h") 
FILES += $(shell find . -name "*.md")
DEPS = Doxyfile.cfg DoxygenLayout.xml $(FILES)

all: $(DEPS)
	$(DOXYGEN_CMD) Doxyfile.cfg

vars:
	@echo PROJECT_NAME: $(PROJECT_NAME)
	@echo PROJECT_VERSION: $(PROJECT_VERSION)
	@echo PROJECT_PATH:$(PROJECT_PATH)
	@echo MAKE_PATH:$(MAKE_PATH)
	@echo DEPS:$(DEPS)

clean:
	@echo Cleaning output
	@rm -fr $(MAKE_PATH)/output
	@mkdir -p $(MAKE_PATH)/output
