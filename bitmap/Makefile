# You can change these variables if you want to use a different compiler or debugger
CC = clang
DBG = lldb

# We use .PHONY to tell make to always run these commands even if a file exists
# with the same name in this directory. For more information on .PHONY, see
# https://www.gnu.org/software/make/manual/html_node/Phony-Targets.html
.PHONY: build-main
build-main: build-dir
	$(CC) -Wall -O0 -g -o build/main src/main.c -lm

.PHONY: build
build: build-dir
	$(CC) -Wall -O0 -g -o build/$(target) src/$(target).c -lm

.PHONY: build-dir
build-dir:
	if [ ! -d build ]; then mkdir build; fi

.PHONY: run
run: build-main
	./build/main

.PHONY: watch-run
watch-run: 
	watch -n0.5 -t --color "make run"