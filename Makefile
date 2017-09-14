.PHONY: *

# Defeat make using "tests" as default
all:

%:
	make -C src $@
	make -C tests $@

tests:
	make -C src all
	make -C tests run
