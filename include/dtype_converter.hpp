#ifndef DTYPE_CONVERTER_H
#define DTYPE_CONVERTER_H
#include <stdexcept>
#include "object.hpp"

#if PY_MAJOR_VERSION >= 3
#define IS_PY3
#endif

namespace pyextend
{
  template<class T>
  class List;

  template<class T>
  class DataTypeConverter
  {
  public:
    DataTypeConverter(){};


    /** Converts a data type to python */
    PyObject* c2py( const T& value )
    {
      throw std::invalid_argument("Cannot convert arbitrary types to Python objects!");
    };

    /** Convert python object to C++ type */
    Object py2c( PyObject* pyobj )
    {
      return Object(pyobj);
    };
  };



  /** PyObject to double */
  template <>
  class DataTypeConverter<double>
  {
  public:
    DataTypeConverter(){};

    /** Conert C-type to python */
    PyObject* c2py( double value )
    {
      return PyFloat_FromDouble(value);
    };

    double py2c( PyObject* pyobj )
    {
      return PyFloat_AsDouble(pyobj);
    };
  };



  /** Int object */
  template<>
  class DataTypeConverter<int>
  {
  public:
    DataTypeConverter(){};

    /** Convert C-type to python */
    PyObject* c2py( int value )
    {
      #ifdef IS_PY3
        return PyLong_FromLong(value);
      #else
        return PyInt_FromLong(value);
      #endif
    };

    int py2c( PyObject *pyobj )
    {
      #ifdef IS_PY3
        return PyLong_AsLong(pyobj);
      #else
        return PyInt_AsLong(pyobj);
      #endif
    };
  };


  /** Convert to nested list */
  template<class T>
  class DataTypeConverter< pyextend::List<T> >
  {
  public:
    DataTypeConverter(){};


    /** Convert to C-type */
    PyObject* c2py( pyextend::List<T> &list )
    {
      return list.raw_ptr();
    };


    /** Convert Python to C */
    List<T> py2c( PyObject* pylist, bool own )
    {
      return List<T>(pylist, own);
    };


    /** Default implementation, wrapper does not own the underlying pointer */
    List<T> py2c( PyObject *pylist )
    {
      return py2c( pylist, false );
    }
  };
};
#endif
