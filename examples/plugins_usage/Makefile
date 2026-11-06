CURRENT_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

SDK_DIR = $(abspath $(CURRENT_DIR)../../SDK)

RAYLIB_DIR = $(HOME)/raylib/src

all:
	@echo [Building MainPlugin.dylib]
	clang++ -std=c++23 -dynamiclib -undefined dynamic_lookup -Iinclude -I$(SDK_DIR) -ldl -g -Wall -Wextra -o MainPlugin.dylib src/MainPlugin.cpp

	@echo [Building Renderer.dylib]
	clang++ -std=c++23 -dynamiclib -undefined dynamic_lookup -Iinclude -I$(SDK_DIR) -I/opt/homebrew/include \
	    -g /opt/homebrew/lib/libraylib.dylib \
	    -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo \
	    -Wall -Wextra -Wl,-rpath,/opt/homebrew/lib -o Renderer.dylib src/Renderer.cpp

	@echo [Building main]
	clang++ -std=c++23 -Iinclude -I$(SDK_DIR) -g -ldl -Wall -Wextra \
		-o main src/Main.cpp $(SDK_DIR)/Core/ApplicationCore.cpp

clean:
	rm -rf *.dylib main

.PHONY: all clean