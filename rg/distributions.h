#ifndef DISTRIBUTIONS_H
#define DISTRIBUTIONS_H

extern 
void *Uniform_init(long a,long b);

extern 
long *Uniform_get(void *self);

extern 
void Uniform_dealloc(void *self);


extern 
void *Bernoulli_init();

extern 
long Bernoulli_get(void *self);

extern 
void Bernoulli_dealloc(void *self);

extern 
void *Binomial_init(long n,double p);

extern 
long Binomial_get(void *self);

extern 
void Binomial_dealloc(void *self);


extern
void *NegativeBinomial_init(long k,double p);

extern
long NegativeBinomial_get(void *self);

extern
void NegativeBinomial_dealloc(void *self);


extern
void *Geometric_init(double p);

extern
long Geometric_get(void *self);

extern
void Geometric_dealloc(void *self);


extern
void *Poisson_init(double mean);

extern
long Poisson_get(void *self);

extern
void Poisson_dealloc(void *self);

#endif
