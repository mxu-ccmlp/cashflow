#pragma once
#include <Python.h>
#include <stdio.h>
#include <numpy/arrayobject.h>
#include <string>
#include <map>
#include "funcs.hpp"
#define default_cprx 1.0
#define default_cdrx 1.0
#define default_sevx 1.0
#define default_ficoMigration 0
#define default_full_doc_frac 0.1
#define default_prepay_penalty_frac 0.5

#define para_data_structure double****
#define para_type_count 4
#define para_id_count 8
#define aggres_nfield 25
namespace cf_funcs {
    static PyObject* method_calc_prepayment(PyObject *self, PyObject *args){
        int paths, projmos;
        PyObject *loanspyo;
        if(!PyArg_ParseTuple(args, "iiO", &paths, &projmos, &loanspyo)){
            PyErr_SetString(PyExc_ValueError, "iiO not valid.");
            return 0;
        }
        return Py_BuildValue("d", 0.0);
    }
    static PyObject* method_calc_dq(PyObject *self, PyObject *args){
        int paths, projmos;
        PyObject *loanspyo;
        if(!PyArg_ParseTuple(args, "iiO", &paths, &projmos, &loanspyo)){
            PyErr_SetString(PyExc_ValueError, "iiO not valid.");
            return 0;
        }
        return Py_BuildValue("d", 0.0);
    }
    static PyObject* method_calc_default(PyObject *self, PyObject *args){
        int paths, projmos;
        PyObject *loanspyo;
        if(!PyArg_ParseTuple(args, "iiO", &paths, &projmos, &loanspyo)){
            PyErr_SetString(PyExc_ValueError, "iiO not valid.");
            return 0;
        }
        return Py_BuildValue("d", 0.0);
    }
}