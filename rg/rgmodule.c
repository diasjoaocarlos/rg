#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "structmember.h"
#include "distributions.h"
#include "macroexpand.h"

#define DISTRIBUTION_NAME Uniform
#define RG_D_STRUCT_PARMS \
     long a; \
     long b;
#define RG_NEW_BLOCK self->a = 0;self->b = 0;
#define RG_PARMS_STRING "a", "b",
#define RG_PARMS_MASK "ii"
#define RG_PYARG_PARMS &self->a,&self->b,
#define RG_D_INIT_PARMS self->a,self->b
#define RG_MEMBERS_PARMS \
    {"a", T_INT, offsetof(OBJECT, a), 0, \
     "Distribution parameter."}, \
    {"b", T_INT, offsetof(OBJECT, b), 0, \
     "Distribution parameter."},
#include "_rg_part_.c"

#define DISTRIBUTION_NAME Bernoulli
#define RG_D_STRUCT_PARMS
#define RG_NEW_BLOCK
#define RG_PARMS_STRING
#define RG_PARMS_MASK
#define RG_D_INIT_PARMS
#define RG_PYARG_PARMS
#define RG_MEMBERS_PARMS
#include "_rg_part_.c"

#define DISTRIBUTION_NAME Binomial
#define RG_D_STRUCT_PARMS \
     long n; \
     double p;
#define RG_NEW_BLOCK self->n = 0;self->p = 0.0;
#define RG_PARMS_STRING "n", "p",
#define RG_PARMS_MASK "id"
#define RG_PYARG_PARMS &self->n,&self->p,
#define RG_D_INIT_PARMS self->n,self->p
#define RG_MEMBERS_PARMS \
    {"n", T_INT, offsetof(OBJECT, n), 0, \
     "Distribution parameter."}, \
    {"p", T_DOUBLE, offsetof(OBJECT, p), 0, \
     "Distribution parameter."},
#include "_rg_part_.c"

#define DISTRIBUTION_NAME NegativeBinomial
#define RG_D_STRUCT_PARMS \
     long k; \
     double p;
#define RG_NEW_BLOCK self->k = 0;self->p = 0.0;
#define RG_PARMS_STRING "k", "p",
#define RG_PARMS_MASK "id"
#define RG_PYARG_PARMS &self->k,&self->p,
#define RG_D_INIT_PARMS self->k,self->p
#define RG_MEMBERS_PARMS \
    {"k", T_INT, offsetof(OBJECT, k), 0, \
     "Distribution parameter."}, \
    {"p", T_DOUBLE, offsetof(OBJECT, p), 0, \
     "Distribution parameter."},
#include "_rg_part_.c"


#define DISTRIBUTION_NAME Geometric
#define RG_D_STRUCT_PARMS \
     double p;
#define RG_NEW_BLOCK self->p = 0.0;
#define RG_PARMS_STRING "p",
#define RG_PARMS_MASK "d"
#define RG_PYARG_PARMS &self->p,
#define RG_D_INIT_PARMS self->p
#define RG_MEMBERS_PARMS \
    {"p", T_DOUBLE, offsetof(OBJECT, p), 0, \
     "Distribution parameter."},
#include "_rg_part_.c"


#define DISTRIBUTION_NAME Poisson
#define RG_D_STRUCT_PARMS \
     double mean;
#define RG_NEW_BLOCK self->mean = 0.0;
#define RG_PARMS_STRING "mean",
#define RG_PARMS_MASK "d"
#define RG_PYARG_PARMS &self->mean,
#define RG_D_INIT_PARMS self->mean
#define RG_MEMBERS_PARMS \
    {"mean", T_DOUBLE, offsetof(OBJECT, mean), 0, \
     "Distribution parameter."},
#include "_rg_part_.c"



static PyModuleDef rgmodule = {
    PyModuleDef_HEAD_INIT,
    .m_name = "rg",
    .m_doc = "Random Discrete Distributions.",
    .m_size = -1,
};

PyObject *
PyInit_rg(void)
{
    PyObject *m;
    if (PyType_Ready(&UniformType) < 0)
        return NULL;

    if (PyType_Ready(&BernoulliType) < 0)
        return NULL;

    if (PyType_Ready(&BinomialType) < 0)
        return NULL;

    if (PyType_Ready(&NegativeBinomialType) < 0)
        return NULL;

    if (PyType_Ready(&GeometricType) < 0)
        return NULL;

    if (PyType_Ready(&PoissonType) < 0)
        return NULL;

    m = PyModule_Create(&rgmodule);
    if (m == NULL)
        return NULL;

    Py_INCREF(&UniformType);
    if (PyModule_AddObject(m, "Uniform", (PyObject *) &UniformType) < 0) {
        Py_DECREF(&UniformType);
        Py_DECREF(m);
        return NULL;
    }

    Py_INCREF(&BernoulliType);
    if (PyModule_AddObject(m, "Bernoulli", (PyObject *) &BernoulliType) < 0 ) {
        Py_DECREF(&BernoulliType);
        Py_DECREF(m);
        return NULL;
    }

    Py_INCREF(&BinomialType);
    if (PyModule_AddObject(m, "Binomial", (PyObject *) &BinomialType) < 0) {
        Py_DECREF(&BinomialType);
        Py_DECREF(m);
        return NULL;
    }

    Py_INCREF(&NegativeBinomialType);
    if (PyModule_AddObject(m, "NegativeBinomial", (PyObject *) &NegativeBinomialType) < 0) {
        Py_DECREF(&NegativeBinomialType);
        Py_DECREF(m);
        return NULL;
    }

    Py_INCREF(&GeometricType);
    if (PyModule_AddObject(m, "Geometric", (PyObject *) &GeometricType) < 0) {
        Py_DECREF(&GeometricType);
        Py_DECREF(m);
        return NULL;
    }

    Py_INCREF(&PoissonType);
    if (PyModule_AddObject(m, "Poisson", (PyObject *) &PoissonType) < 0) {
        Py_DECREF(&PoissonType);
        Py_DECREF(m);
        return NULL;
    }

    return m;
}


#include <stdio.h>

int
main(int argc, char *argv[])
{
    wchar_t *program = Py_DecodeLocale(argv[0], NULL);
    if (program == NULL) {
        fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
        exit(1);
    }

    /* Add a built-in module, before Py_Initialize */
    if (PyImport_AppendInittab("rg", PyInit_rg) == -1) {
        fprintf(stderr, "Error: could not extend in-built modules table\n");
        exit(1);
    }

    /* Pass argv[0] to the Python interpreter */
    Py_SetProgramName(program);

    /* Initialize the Python interpreter.  Required.
       If this step fails, it will be a fatal error. */
    Py_Initialize();

    /* Optionally import the module; alternatively,
       import can be deferred until the embedded script
       imports it. */
    PyObject *pmodule = PyImport_ImportModule("rg");
    if (!pmodule) {
        PyErr_Print();
        fprintf(stderr, "Error: could not import module 'rg'\n");
    }

    PyMem_RawFree(program);
    return 0;
}

