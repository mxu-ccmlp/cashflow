#include <Python.h>
#include <stdio.h>
#include <numpy/arrayobject.h>
#include <future>
#include <sstream>
#include <cstring>
#include "impls.hpp"
#include <chrono>
#include <ctime>
#include "version.h"

static PyMethodDef cffuncsModelMethods[] = {
    {"calc_default", cf_funcs::method_calc_default, METH_VARARGS, "calc default."},
    {"calc_dq", cf_funcs::method_calc_dq, METH_VARARGS, "calc dq."},
    {"calc_prepayment", cf_funcs::method_calc_prepayment, METH_VARARGS, "calc prepayment."},
    {NULL, NULL, 0, NULL}
};

////////////////////##################the following lines never change.###########################
static struct PyModuleDef cffuncsmodule = {
    PyModuleDef_HEAD_INIT,
    "cffuncs",
    "Python interface for the cashflow C library function",
    -1,
    cffuncsModelMethods
};

PyMODINIT_FUNC PyInit_cffuncs(void) {
    import_array();
    PyObject *m = NULL;
    m = PyModule_Create(&cffuncsmodule);
    char *versions = new char[strlen(CFFUNCS_VERSION)+strlen(CFFUNCS_VERSION_COMMITHASH)+2];
    strcpy(versions,CFFUNCS_VERSION);
    strcat(versions,"+");
    strcat(versions,CFFUNCS_VERSION_COMMITHASH);
    PyModule_AddStringConstant(m, "__version__", versions);
    return m;
}
