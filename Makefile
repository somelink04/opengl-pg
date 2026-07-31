main: obj/glad.o lib/libglfw3.a main.c 
	gcc -o main main.c obj/glad.o -Ivendor/glad/include -Ivendor/glfw/include -Llib -l:libglfw3.a -lm

GLFW_BUILD=.glfw_build

lib/libglfw3.a: lib
	cmake -S vendor/glfw/ -B $(GLFW_BUILD) -D GLFW_BUILD_WAYLAND=0
	cmake --build $(GLFW_BUILD)/src
	mv $(GLFW_BUILD)/src/libglfw3.a ./lib

obj/glad.o: obj vendor/glad/src/gl.c vendor/glad/include/glad/gl.h
	gcc -o obj/glad.o -c -Ivendor/glad/include vendor/glad/src/gl.c

obj:
	mkdir -p obj

lib:
	mkdir -p lib

.PHONY: clean
clean:
	rm -rf $(GLFW_BUILD) obj lib main
