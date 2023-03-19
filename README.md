# Multi-Platform-Image-Processing-System
The main focus of this project is the implementation of an image procession application on different target platforms: sequential processor with RTOS, bare-metal sequential processor, and multiprocessor.

## Basic setup
Click in the Clone or download button and then press the Download zip button to acquire the repo mirror in a zipped format. Extract it somewhere you find pertinent and you are ready to go from this mirror. Eventual later changes in the code here will require you to repeat the process and find the right patch places.

## Directory structure
This repository is structured as follows:

* `model` contains the executable specification of the application you need to implement for the project. It is provided as a ForSyDe-Haskell project which implements a network of SDF processes, capturing the functional and extra-functional specifications. You need to install, run and understand this model. Refer to the README file for more information.
* `app` contains the source code for the project. Here you can find the hello world examples and our provided code snippets. Here is also where you shall implement your lab projects. It is advisable to create new folders for each new project, otherwise you will have to manage merge conflicts with each update of the main repository. Also, if you intend to reuse the provided build scripts, you should keep the directory structure suggested by the demo applications.
* `bsp` is where the "board support package" (libraries, device drivers, etc.) will be generated. Unless you have good reasons, you should leave it untouched.
* `hardware` is where the architecture/hardware files reside. You should check it out, but for this lab you are not supposed to modify anything.
* `c-util/ppm-io` contains C functions for reading/writing ppm images to/from C data structure. Note: these functions are only expected to be used for modelling applications in C on a regular PC.
