ifeq ($(DIST),)
$(error Error! DIST variable is not set!)
endif

TARGETS := $(filter-out libc/, $(wildcard lib*/))

.PHONY: all install clean

all:
	@for target in $(TARGETS); do \
		echo Entering directory $$target; \
		$(MAKE) --no-print-directory -C $$target all; \
		echo Leaving directory $$target; \
	done

clean:
	@for target in $(TARGETS); do \
		echo Cleaning directory $$target; \
		$(MAKE) --no-print-directory -C $$target clean; \
	done

install: all
	@mkdir -p "$(DIST)/lib"
	@cp -a lib*/*.a "$(DIST)/lib/"
