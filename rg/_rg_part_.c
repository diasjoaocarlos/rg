#ifndef DISTRIBUTION_NAME
#error Bad usage of _rg_part_.c (e.g. Uniform)
#endif

#define OBJECT XCONCAT(DISTRIBUTION_NAME,Object)
#define DEALLOC XCONCAT(_,_DEALLOC)
#define _DEALLOC XCONCAT(DISTRIBUTION_NAME,_dealloc)
#define NEW XCONCAT(_,XCONCAT(DISTRIBUTION_NAME,_new))
#define INIT XCONCAT(_,_INIT)
#define _INIT XCONCAT(DISTRIBUTION_NAME,_init)
#define DISTRIBUTION_MEMBERS XCONCAT(DISTRIBUTION_NAME,_members)
#define ITER XCONCAT(_,XCONCAT(DISTRIBUTION_NAME,__iter__))
#define NEXT XCONCAT(_,XCONCAT(DISTRIBUTION_NAME,__next__))
#define _GET XCONCAT(DISTRIBUTION_NAME,_get)
#define DISTRIBUTION_METHODS XCONCAT(DISTRIBUTION_NAME,_methods)
#define DISTRIBUTION_TYPE XCONCAT(DISTRIBUTION_NAME,Type)


typedef struct {
    PyObject_HEAD
    RG_D_STRUCT_PARMS
    long N;
    void *engine;
    long i;
} OBJECT;

static void
DEALLOC(OBJECT *self)
{
    _DEALLOC(self->engine);
    Py_TYPE(self)->tp_free((PyObject *) self);
}

static PyObject *
NEW(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    OBJECT *self;
    self = (OBJECT *) type->tp_alloc(type, 0);
    if (self != NULL) {
        RG_NEW_BLOCK

        self->N = 0;
    }

    return (PyObject *) self;
}

static int
INIT(OBJECT *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = { RG_PARMS_STRING "N", NULL };

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|" RG_PARMS_MASK "i", kwlist,
                                     RG_PYARG_PARMS &self->N))
        return -1;

    self->engine = _INIT(RG_D_INIT_PARMS);

    if (!self->engine)
        return -1;

    return 0;
}

static PyMemberDef DISTRIBUTION_MEMBERS[] = {
    RG_MEMBERS_PARMS
    {"N", T_INT, offsetof(OBJECT, N), 0,
     "Distribution size."},
    {NULL, NULL, NULL, 0, NULL}  /* Sentinel */
};

static PyObject *
ITER(OBJECT *self, PyObject *Py_UNUSED(ignored))
{
    Py_INCREF(self);

    self->i=0;

    return (PyObject *) self;
}

static PyObject *
NEXT(OBJECT *self, PyObject *Py_UNUSED(ignored))
{
    if (self->i>=self->N) {
       PyErr_SetNone(PyExc_StopIteration);
       return NULL;
    }

    long n = _GET(self->engine);

    self->i++;

    return PyLong_FromLong(n);
}

static PyMethodDef DISTRIBUTION_METHODS[] = {
    {"__iter__", (PyCFunction) ITER, METH_NOARGS,
     "Iterator."
    },
    {"__next__", (PyCFunction) NEXT, METH_NOARGS,
     "Next value."
    },
    {NULL}  /* Sentinel */
};

static PyTypeObject DISTRIBUTION_TYPE = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "rg."XSTR(DISTRIBUTION_NAME),
    .tp_doc = PyDoc_STR(XSTR(DISTRIBUTION_NAME)" distribution"),
    .tp_basicsize = sizeof(OBJECT),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_new = NEW,
    .tp_init = (initproc) INIT,
    .tp_dealloc = (destructor) DEALLOC,
    .tp_members = DISTRIBUTION_MEMBERS,
    .tp_methods = DISTRIBUTION_METHODS,
    .tp_iter = ITER,
    .tp_iternext = NEXT,
};


