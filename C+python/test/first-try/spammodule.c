#include <stdio.h>
// #include <time.h>
#include <unistd.h>

#define PY_SSIZE_T_CLEAN
#include </usr/local/Cellar//python@3.10/3.10.6_2/Frameworks/Python.framework/Versions/3.10/include/python3.10/Python.h>

static PyObject *
spam_system(PyObject *self, PyObject *args)
{
    const char *command;
    int sts;

    if (!PyArg_ParseTuple(args, "s", &command))
        return NULL;
    sts = system(command);
    return PyLong_FromLong(sts);
}

static PyMethodDef SpamMethods[] = {
    // ...
    {"system",  spam_system, METH_VARARGS,
     "Execute a shell command."},
    // ...
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

static struct PyModuleDef spammodule = {
    PyModuleDef_HEAD_INIT,
    "spam",   /* name of module */
    NULL, // spam_doc, /* module documentation, may be NULL */
    -1,       /* size of per-interpreter state of the module,
                 or -1 if the module keeps state in global variables. */
    SpamMethods
};

PyMODINIT_FUNC
PyInit_spam(void)
{
    return PyModule_Create(&spammodule);
}

void test() {
    int sum_odd = 0;
    int sum_even = 0;
    for ( int i = 0; i < 100000000; ++i ) {
        if ( i % 2 == 0 )
            sum_even += i;
        else
            sum_odd += i;
        sum_even -= sum_odd;
        sum_odd -= sum_odd;
    }
    printf( "test res: %d %d\n", sum_even, sum_odd );
    Py_INCREF(Py_None);
    return Py_None;
}

void sleep_time( int n ) {
    sleep( n );
}

int main(int argc, char *argv[])
{
    wchar_t *program = Py_DecodeLocale(argv[0], NULL);
    if (program == NULL) {
        fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
        exit(1);
    }

    /* Add a built-in module, before Py_Initialize */
    if (PyImport_AppendInittab("spam", PyInit_spam) == -1) {
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
    PyObject *pmodule = PyImport_ImportModule("spam");
    if (!pmodule) {
        PyErr_Print();
        fprintf(stderr, "Error: could not import module 'spam'\n");
    }

    // ...

    PyMem_RawFree(program);
    return 0;
}