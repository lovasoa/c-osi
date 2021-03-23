# Osi-c

A C interface for the [Open Solver Interface](https://github.com/coin-or/Osi#osi).

This project builds a well-defined C API ([`osi.h`](./osi.h)) that you can build against
without having to link your program with any particular solver.

This has two main advantages:
 - You can build a solver-independent executable,
   then switch solvers at runtime by switching the dynamic library (`.so` or `.dll`) you use.
   For instance, you can build your program without access to a proprietary solver, and then
   let people use it with proprietary solvers if they have access to one.
 - This makes it easy to interact with Osi solvers from languages other than C++.
   Osi is defined as a C++ abstract class,
   and this makes it hard to interact with it from languages other than C++.
   Having a single dynamic library with a plain C interface makes it possible to use 
   the solvers from any language that has a
   [C Foreign Function Interface](https://en.wikipedia.org/wiki/Foreign_function_interface),
   such as Java, Go, Python, Rust, and many others.
   
## Downloads

You can download pre-compiled dynamic solver libraries for linux
from the 
[release page](https://github.com/lovasoa/c-osi/releases).