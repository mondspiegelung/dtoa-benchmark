cmake_minimum_required(VERSION 3.1.0)

# Joins arguments and places the results in ${result_var}.
function(join result_var)
  set(result )
  foreach (arg ${ARGN})
    set(result "${result}${arg}")
  endforeach ()
  set(${result_var} "${result}" PARENT_SCOPE)
endfunction()

if (NOT CMAKE_BUILD_TYPE)
  join(doc "Choose the type of build, options are: None(CMAKE_CXX_FLAGS or "
           "CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel.")
  set(CMAKE_BUILD_TYPE Release CACHE STRING ${doc})
endif ()

project(DTOA_BENCHMARK CXX)

add_executable(
  dtoa-benchmark
  src/main.cpp
  # Tests:
  src/doubleconvtest.cpp
  src/milotest.cpp
  src/null.cpp
  src/ostringstream.cpp
  src/sprintf.cpp
  # double-conversion:
  src/double-conversion/bignum-dtoa.cc
  src/double-conversion/bignum.cc
  src/double-conversion/cached-powers.cc
  src/double-conversion/diy-fp.cc
  src/double-conversion/double-conversion.cc
  src/double-conversion/fast-dtoa.cc
  src/double-conversion/fixed-dtoa.cc
  src/double-conversion/strtod.cc)
