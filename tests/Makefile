TESTS = check_linkedlist check_hashmap
CFLAGS += -Wall -Werror -lcheck -lm

.PHONY: all run

all: $(TESTS)

check_linkedlist: ../src/linkedlist.o

check_hashmap: ../src/linkedlist.o ../src/hashmap.o

run: $(TESTS)
	@for binary in $(TESTS); do\
		./$$binary; \
	done

clean:
	rm -rf $(TESTS)
