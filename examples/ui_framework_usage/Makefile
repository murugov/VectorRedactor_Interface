SDK_DIR = $(shell cd ../../SDK && pwd)

RAYLIB_DIR = $(HOME)/raylib/src

all:
	@echo [Building MainPlugin.dylib]
	clang++ -std=c++23 -dynamiclib -undefined dynamic_lookup -Iinclude -I$(SDK_DIR) -ldl -g -Wall -Wextra -o MainPlugin.dylib src/MainPlugin.cpp

	@echo [Building UIWi.so]
	clang++ -std=c++23 -dynamiclib -undefined dynamic_lookup -Iinclude -I$(SDK_DIR) -ldl -g -Wall -Wextra -o UIWi.dylib $(SDK_DIR)/cheets/UIWi/src/UIWi.cpp
		
	@echo [Building Renderer.dylib]
	clang++ -std=c++23 -dynamiclib -undefined dynamic_lookup -Iinclude -I$(SDK_DIR) -I/opt/homebrew/include \
	    -g /opt/homebrew/lib/libraylib.dylib \
	    -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo \
	    -Wall -Wextra -Wl,-rpath,/opt/homebrew/lib -o Renderer.dylib src/Renderer.cpp

	@echo [Building main]
	clang++ -std=c++23 -Iinclude -I$(SDK_DIR) -g -ldl -Wall -Wextra \
		-o main src/Main.cpp ../../SDK/Core/ApplicationCore.cpp

clean:
	rm -rf *.dylib main

.PHONY: all clean
