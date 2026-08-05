# OpenGL Playground

Simple playground for OpenGL with all dependencies manually maintained.
Build the main executable with:

```bash
make main
```

## Dependencies

Direct dependencies are located in the `vendor/` directory. A quick overview 
(might be out of sync with the actual dependencies):

* GLFW 3.5.1 (git submodule checked out via the version tag)
* glad 2.0.8 (generated via [the generator](https://gen.glad.sh/)

GLFW itself is built from source via the included CMake script. This contains
additional dependencies which need to be resolved on the first run of make.
Make sure to install the development packages for the listed dependencies.

