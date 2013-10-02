#include <Python.h>
#include <libxl.h>

#include "sheet.h"

static int
init(XLPySheet *self)
{
    return 0;
}

static void
dealloc(XLPySheet *self)
{
	self->ob_type->tp_free((PyObject*)self);
}

static PyObject *
write_str(XLPySheet *self, PyObject *args)
{
	int row, col;
	const char *val;
	if(!PyArg_ParseTuple(args, "iis", &row, &col, &val)) {
		return NULL;
	}

	if (!xlSheetWriteStr(self->handler, row, col, val, 0)) {
		Py_RETURN_FALSE;
	}
	Py_RETURN_TRUE;
}

static PyObject *
set_merge(XLPySheet *self, PyObject *args)
{
	int rowFirst, rowLast, colFirst, colLast;
	if(!PyArg_ParseTuple(args, "iiii", &rowFirst, &rowLast, &colFirst, &colLast)) {
		return NULL;
	}

	if(xlSheetSetMerge(self->handler, rowFirst, rowLast, colFirst, colLast)) {
		Py_RETURN_TRUE;
	}
	Py_RETURN_FALSE;
}

static PyObject *
set_name(XLPySheet *self, PyObject *args)
{
    const char *name;
    if(!PyArg_ParseTuple(args, "s", &name)) {
        return NULL;
    }

    xlSheetSetName(self->handler, name);
    Py_RETURN_NONE;
}

static PyMethodDef methods[] = {
	{"writeStr", (PyCFunction) write_str, METH_VARARGS,
		"Writes a string into cell with specified format (if present). Returns False if error occurs."},
	{"setMerge", (PyCFunction) set_merge, METH_VARARGS,
		"Sets merged cells for range: rowFirst - rowLast, colFirst - colLast. "
		"Returns False if error occurs."},
    {"setName", (PyCFunction) set_name, METH_VARARGS,
        "Sets the name of the sheet."},
	{NULL}
};

PyTypeObject XLPySheetType = {
   PyObject_HEAD_INIT(NULL)
   0,                         /* ob_size */
   "XLPySheet",               /* tp_name */
   sizeof(XLPySheet),         /* tp_basicsize */
   0,                         /* tp_itemsize */
   (destructor)dealloc,/* tp_dealloc */
   0,                         /* tp_print */
   0,                         /* tp_getattr */
   0,                         /* tp_setattr */
   0,                         /* tp_compare */
   0,                         /* tp_repr */
   0,                         /* tp_as_number */
   0,                         /* tp_as_sequence */
   0,                         /* tp_as_mapping */
   0,                         /* tp_hash */
   0,                         /* tp_call */
   0,                         /* tp_str */
   0,                         /* tp_getattro */
   0,                         /* tp_setattro */
   0,                         /* tp_as_buffer */
   Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /* tp_flags*/
   "XLPy Sheet",                 /* tp_doc */
   0,                         /* tp_traverse */
   0,                         /* tp_clear */
   0,                         /* tp_richcompare */
   0,                         /* tp_weaklistoffset */
   0,                         /* tp_iter */
   0,                         /* tp_iternext */
   methods,            /* tp_methods */
   0,                         /* tp_members */
   0,                         /* tp_getset */
   0,                         /* tp_base */
   0,                         /* tp_dict */
   0,                         /* tp_descr_get */
   0,                         /* tp_descr_set */
   0,                         /* tp_dictoffset */
   (initproc)init,     /* tp_init */
   0,                         /* tp_alloc */
   0,                         /* tp_new */
};