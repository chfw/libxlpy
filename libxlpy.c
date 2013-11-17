#include <Python.h>
#include <libxl.h>

extern PyTypeObject XLPyBookType;
extern PyTypeObject XLPySheetType;
extern PyTypeObject XLPyFormatType;
extern PyTypeObject XLPyFontType;

#define INIT_TYPE(Type) \
	Type.tp_new = PyType_GenericNew; \
	if (PyType_Ready(&Type) < 0) return; \
	Py_INCREF(&Type)

#define ADD_INT_CONSTANT(v) PyModule_AddIntConstant(mod, #v, v)
void initlibxlpy(void)
{
    PyObject* mod;
    mod = Py_InitModule3("libxlpy", NULL, "A libxl python wrapper");
    if (mod == NULL) return;
     
    // Init Classes
	INIT_TYPE(XLPyBookType);
    INIT_TYPE(XLPySheetType);
	INIT_TYPE(XLPyFormatType);
	INIT_TYPE(XLPyFontType);

    // Module's Public API
    PyModule_AddObject(mod, "Book", (PyObject* )&XLPyBookType);

	ADD_INT_CONSTANT(SHEETTYPE_SHEET);
	ADD_INT_CONSTANT(SHEETTYPE_CHART);
	ADD_INT_CONSTANT(SHEETTYPE_UNKNOWN);

	ADD_INT_CONSTANT(CELLTYPE_NUMBER);
	ADD_INT_CONSTANT(CELLTYPE_STRING);
	ADD_INT_CONSTANT(CELLTYPE_BOOLEAN);
	ADD_INT_CONSTANT(CELLTYPE_BLANK);
	ADD_INT_CONSTANT(CELLTYPE_ERROR);

	ADD_INT_CONSTANT(NUMFORMAT_GENERAL);
	ADD_INT_CONSTANT(NUMFORMAT_NUMBER);
	ADD_INT_CONSTANT(NUMFORMAT_NUMBER_D2);
	ADD_INT_CONSTANT(NUMFORMAT_NUMBER_SEP);
	ADD_INT_CONSTANT(NUMFORMAT_NUMBER_SEP_D2);
	ADD_INT_CONSTANT(NUMFORMAT_CURRENCY_NEGBRA);
	ADD_INT_CONSTANT(NUMFORMAT_CURRENCY_NEGBRARED);
	ADD_INT_CONSTANT(NUMFORMAT_CURRENCY_D2_NEGBRA);
	ADD_INT_CONSTANT(NUMFORMAT_CURRENCY_D2_NEGBRARED);
	ADD_INT_CONSTANT(NUMFORMAT_PERCENT);
	ADD_INT_CONSTANT(NUMFORMAT_PERCENT_D2);
	ADD_INT_CONSTANT(NUMFORMAT_SCIENTIFIC_D2);
	ADD_INT_CONSTANT(NUMFORMAT_FRACTION_ONEDIG);
	ADD_INT_CONSTANT(NUMFORMAT_FRACTION_TWODIG);
	ADD_INT_CONSTANT(NUMFORMAT_DATE);
	ADD_INT_CONSTANT(NUMFORMAT_CUSTOM_D_MON_YY);
	ADD_INT_CONSTANT(NUMFORMAT_CUSTOM_D_MON);
	ADD_INT_CONSTANT(NUMFORMAT_CUSTOM_MON_YY);
	ADD_INT_CONSTANT(NUMFORMAT_CUSTOM_HMM_AM);
	ADD_INT_CONSTANT(NUMFORMAT_CUSTOM_HMMSS_AM);
	ADD_INT_CONSTANT(NUMFORMAT_CUSTOM_HMM);
	ADD_INT_CONSTANT(NUMFORMAT_CUSTOM_HMMSS);
	ADD_INT_CONSTANT(NUMFORMAT_CUSTOM_MDYYYY_HMM);
	ADD_INT_CONSTANT(NUMFORMAT_NUMBER_SEP_NEGBRA);
	ADD_INT_CONSTANT(NUMFORMAT_NUMBER_SEP_NEGBRARED);
	ADD_INT_CONSTANT(NUMFORMAT_NUMBER_D2_SEP_NEGBRA);
	ADD_INT_CONSTANT(NUMFORMAT_NUMBER_D2_SEP_NEGBRARED);
	ADD_INT_CONSTANT(NUMFORMAT_ACCOUNT);
	ADD_INT_CONSTANT(NUMFORMAT_ACCOUNTCUR);
	ADD_INT_CONSTANT(NUMFORMAT_ACCOUNT_D2);
	ADD_INT_CONSTANT(NUMFORMAT_ACCOUNT_D2_CUR);
	ADD_INT_CONSTANT(NUMFORMAT_CUSTOM_MMSS);
	ADD_INT_CONSTANT(NUMFORMAT_CUSTOM_H0MMSS);
	ADD_INT_CONSTANT(NUMFORMAT_CUSTOM_MMSS0);
	ADD_INT_CONSTANT(NUMFORMAT_CUSTOM_000P0E_PLUS0);
	ADD_INT_CONSTANT(NUMFORMAT_TEXT);

    ADD_INT_CONSTANT(ERRORTYPE_NULL);
    ADD_INT_CONSTANT(ERRORTYPE_DIV_0);
    ADD_INT_CONSTANT(ERRORTYPE_VALUE);
    ADD_INT_CONSTANT(ERRORTYPE_REF);
    ADD_INT_CONSTANT(ERRORTYPE_NAME);
    ADD_INT_CONSTANT(ERRORTYPE_NUM);
    ADD_INT_CONSTANT(ERRORTYPE_NA);
    // Available on doc but not on libxl.h
    PyModule_AddIntConstant(mod, "ERRORTYPE_NOERROR", 0xff); 

    ADD_INT_CONSTANT(SHEETSTATE_VISIBLE);
    ADD_INT_CONSTANT(SHEETSTATE_HIDDEN);
    ADD_INT_CONSTANT(SHEETSTATE_VERYHIDDEN);
}
