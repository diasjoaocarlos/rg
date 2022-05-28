# rg
Random Distribution Generator (Python C API Extension)


Generates random numbers coming from the distributions:

* Uniform(a,b,N)
* Bernoulli(N)
* Binomial(n,p,N)
* NegativeBinomial(k,p,N)
* Geometric(p,N)
* Poisson(mean,N)

where N is the number of numbers generated.

Usage Example:

```
import rg

for i in rg.Poisson(4.5,N=10000):
  print(i)
```

# MacOS

Compiling and linking:

```
g++ -DDISTRIBUTIONS_COMPAT_C -fpermissive -c distributions.cpp
gcc -DNDEBUG -g -O3 -Wall -fPIC -I/$INCLUDE_DIR -c rgmodule.c
gcc -bundle -undefined dynamic_lookup rgmodule.o distributions.o -lstdc++ -L/LIB_DIR -o rg.so
```

- with $INCLUDE_DIR - directory where are the include files, including Python.h;
- with $LIB_DIR - library directory
- import module in the directory where is rg.so
