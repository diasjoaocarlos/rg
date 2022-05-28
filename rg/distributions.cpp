#include <random>
#include <ctime>

class RandomEngine {
  protected:
  public:
     std::default_random_engine *generator;
     RandomEngine() { generator = new std::default_random_engine(std::time(NULL)); }
     RandomEngine(long val) { generator = new std::default_random_engine(val); }
     ~RandomEngine() { delete generator; }
};


class Uniform : RandomEngine {
  protected:
     long min,max;
     std::uniform_int_distribution<long> *distribution;
  public:
     Uniform(long a,long b) : RandomEngine(),min(a),max(b) { distribution = new std::uniform_int_distribution<long>(a,b); }
     Uniform(long a,long b,long val) : RandomEngine(val),min(a),max(b) { distribution = new std::uniform_int_distribution<long>(a,b); }
     ~Uniform() { delete distribution; }
     long operator ()() { return (*distribution)(*generator); }
};


class Bernoulli : public Uniform {
  public:
    Bernoulli() : Uniform(0,1) { }
    Bernoulli(long val) : Uniform(0,1,val) { }
    ~Bernoulli() { }
};


class Binomial : RandomEngine {
  protected:
     long min,max;
     long n;
     double prob;
     std::binomial_distribution<long> *distribution;
  public:
     Binomial(long n,double p) : RandomEngine(),min(0),max(n),n(n),prob(p) { distribution = new std::binomial_distribution<long>(n,p); }
     Binomial(long n,double p,long val) : RandomEngine(val),min(0),max(n),n(n),prob(p) { distribution = new std::binomial_distribution<long>(n,p); }
     ~Binomial() { delete distribution; }
     long operator ()(void) { return (*distribution)(*generator); }
};


class NegativeBinomial : RandomEngine {
  protected:
     long min,max;
     long k;
     double prob;
     std::negative_binomial_distribution<long> *distribution;
  public:
     NegativeBinomial(long k,double p) : RandomEngine(),min(k),max(-1),k(k),prob(p) { distribution = new std::negative_binomial_distribution<long>(k,p); }
     NegativeBinomial(long k,double p,long val) : RandomEngine(val),min(k),max(-1),k(k),prob(p) { distribution = new std::negative_binomial_distribution<long>(k,p); }
     ~NegativeBinomial() { delete distribution; }
     long operator ()(void) { return (*distribution)(*generator); }
};

class Geometric : public NegativeBinomial {
  public:
    Geometric(double p) : NegativeBinomial(1,p) { }
    Geometric(double p,long val) : NegativeBinomial(1,p,val) { }
    ~Geometric() { }
};

class Poisson : RandomEngine {
  protected:
     long min,max;
     double mean;
     std::poisson_distribution<long> *distribution;
  public:
     Poisson(double mean) : RandomEngine(),min(0),max(-1),mean(mean) { distribution = new std::poisson_distribution<long>(mean); }
     Poisson(double mean,long val) : RandomEngine(val),min(0),max(-1),mean(mean) { distribution = new std::poisson_distribution<long>(mean); }
     ~Poisson() { delete distribution; }
     long operator ()(void) { return (*distribution)(*generator); }
};

#ifdef DISTRIBUTIONS_COMPAT_C
extern "C"
void *Uniform_init(long a,long b) {
  return (void *) new Uniform(a,b);
}

extern "C"
long Uniform_get(void *self) {
  return (*(Uniform *) self)();
}

extern "C"
void Uniform_dealloc(void *self) {
  delete (Uniform *) self;
}

extern "C"
void *Bernoulli_init() {
  return (void *) new Bernoulli();
}

extern "C"
long Bernoulli_get(void *self) {
  return (*(Bernoulli *) self)();
}

extern "C"
void Bernoulli_dealloc(void *self) {
  delete (Bernoulli *) self;
}

extern "C"
void *Binomial_init(long n,double p) {
  return (void *) new Binomial(n,p);
}

extern "C"
long Binomial_get(void *self) {
  return (*(Binomial *) self)();
}

extern "C"
void Binomial_dealloc(void *self) {
  delete (Binomial *) self;
}

extern "C"
void *NegativeBinomial_init(long k,double p) {
  return (void *) new NegativeBinomial(k,p);
}

extern "C"
long NegativeBinomial_get(void *self) {
  return (*(NegativeBinomial *) self)();
}

extern "C"
void NegativeBinomial_dealloc(void *self) {
  delete (NegativeBinomial *) self;
}


extern "C"
void *Geometric_init(double p) {
  return (void *) new Geometric(p);
}

extern "C"
long Geometric_get(void *self) {
  return (*(Geometric *) self)();
}

extern "C"
void Geometric_dealloc(void *self) {
  delete (Geometric *) self;
}

extern "C"
void *Poisson_init(double mean) {
  return (void *) new Poisson(mean);
}

extern "C"
long Poisson_get(void *self) {
  return (*(Poisson *) self)();
}

extern "C"
void Poisson_dealloc(void *self) {
  delete (Poisson *) self;
}
#endif
