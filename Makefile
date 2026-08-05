main: obj/glad.o lib/libglfw3.a obj/main.o 
	gcc -o main obj/main.o obj/glad.o -Llib -l:libglfw3.a -lm

obj/main.o: obj main.c
	gcc -c -o obj/main.o main.c -Ivendor/glad/include -Ivendor/glfw/include 

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
