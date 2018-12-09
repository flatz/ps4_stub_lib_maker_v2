ifeq ($(TAUON_SDK_DIR),)
$(error Error! TAUON_SDK_DIR variable is not set!)
endif

TARGETS := lib

DIST = $(TAUON_SDK_DIR)
export DIST

.PHONY: all clean install install-headers

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

install: install-headers
	@mkdir -p "$(DIST)/lib"
	@for target in $(TARGETS); do \
		echo Installing $$target; \
		$(MAKE) --no-print-directory -C $$target install; \
	done

install-headers:
	@mkdir -p "$(DIST)/include"
	@cp -r include/* "$(DIST)/include/"
