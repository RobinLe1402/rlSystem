# rlSystem - OS abstraction
<img src="/res/badges/utf8.svg" title="The code in this repo uses UTF-8 strings" width="50px"/>

This repo contains the static library `rlSystem` which offers OS-dependent functionality:
* File system interaction - change current directory, delete/move files/directories, ...
* App execution - run an app, synchronously or asynchronously
* (Windows only) Conversion between UTF-8 and the operating system's string encoding

## OS Support
While written primarily for Windows 64-bit, the code in this repository is **for the most part**
portable and also contains some Linux-specific code.

However, to compile for a platform other than Windows, you'll have to either remove some functions
or add an implementation for your platform.

> [!NOTE]
> Whenever a function is not implemented for your platform, the following preprocessor directive
> becomes active:
> 
> ```cpp
#error "Not implemented"
```