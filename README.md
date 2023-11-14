Reproduces a potential AMD driver bug.

After compiling (make), the build folder contains an executable (kernel) that will run the shader code with one thread (dispatching one workgroup with a workgroup size of 1). If multiple GPUs are available, one can be chosen with the `-d` flag (e.g. `./kernel -d 1`). `-v` enable validation layers.

The output of the program should be that index 2 of the mem buffer gets the value 2. However, we have seen instances where it is 1.
