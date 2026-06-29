#include <Python.h>
typedef struct TSLanguage TSLanguage;
const TSLanguage *tree_sitter_q(void);
static PyObject* _language(PyObject *self, PyObject *args) {
  return PyCapsule_New((void*)tree_sitter_q(), "tree_sitter.Language", NULL);
}
static PyMethodDef methods[] = {{"language", _language, METH_NOARGS, ""},{NULL,NULL,0,NULL}};
static struct PyModuleDef module = {PyModuleDef_HEAD_INIT,"_binding",NULL,-1,methods};
PyMODINIT_FUNC PyInit__binding(void){ return PyModule_Create(&module); }
