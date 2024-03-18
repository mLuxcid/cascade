# Vulkan Engine
Vulkan engine written in C. Tries to split up things as much as possible to 
improve code readablity.

## building
You'll require a C compiler supporting c11, GNUmake and coreutils. Building is 
as simple as typing `make`.

For debug builds (which are enabled by default right now) you'll also need to 
have address- & undefined behaviour sanitizers. For clang you need `compiler_rt`
 and for GCC `libsanitizer`.
