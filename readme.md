# dtoa Benchmark

Copyright(c) 2014 Milo Yip (miloyip@gmail.com)

## Introduction

This benchmark evaluates the performance of conversion from double precision IEEE-754 floating point (`double`) to ASCII string. The function prototype is:

~~~~~~~~cpp
void dtoa(double value, char* buffer);
~~~~~~~~

The character string result **must** be convertible to the original value **exactly** via some correct implementation of `strtod()`, i.e. roundtrip convertible.

Note that `dtoa()` is *not* a standard function in C and C++.

## Procedure

Firstly the program verifies the correctness of implementations.

Then, one case for benchmark is carried out:

1. **RandomDigit**: Generates 1000 random `double` values, filtered out `+/-inf` and `nan`. Then convert them to limited precision (1 to 17 decimal digits in significand). Finally convert these numbers into ASCII.

Each digit group is run for 100 times. The minimum time duration is measured for 10 trials.

## Build and Run

1. Configure: `cmake .`
2. Build: `make`
3. Run benchmark: `./dtoa-benchmark`
4. On success, run the `dtoa` executable is generated at `dtoa-benchmark/`
5. The results in CSV format will be written to `dtoa-benchmark/result`.
6. Run GNU `make` in `dtoa-benchmark/result` to generate results in HTML.

## Results

The following are `sequential` results measured on a MacBook Pro (3.5 GHz Intel Core i7), where `u32toa()` is compiled by clang 10.0.1 (clang-1001.0.46.4) and run on macOS. The speedup is based on `sprintf()`.

Function      | Time (ns)  | Speedup 
--------------|-----------:|-------:
ostringstream | 1,353.400  | 0.74x
ostrstream    | 1,223.353  | 0.82x
sprintf       | 999.271    | 1.00x
doubleconv    | 101.112    | 9.88x
grisu2        | 76.788     | 13.01x
milo          | 75.600     | 13.22x
fpconv        | 73.388     | 13.62x
null          | 1.418      | 704.88x

![corei7920@2.67_win64_vc2013_randomdigit_time](result/corei7920@2.67_win64_vc2013_randomdigit_time.png)

![corei7920@2.67_win64_vc2013_randomdigit_timedigit](result/corei7920@2.67_win64_vc2013_randomdigit_timedigit.png)

Note that the `null` implementation does nothing. It measures the overheads of looping and function call.

Some results of various configurations are located at `dtoa-benchmark/result`. They can be accessed online, with interactivity provided by [Google Charts](https://developers.google.com/chart/):

* [corei7920@2.67_win32_vc2013](http://rawgit.com/miloyip/dtoa-benchmark/master/result/corei7920@2.67_win32_vc2013.html)
* [corei7920@2.67_win64_vc2013](http://rawgit.com/miloyip/dtoa-benchmark/master/result/corei7920@2.67_win64_vc2013.html)
* [corei7920@2.67_cygwin32_gcc4.8](http://rawgit.com/miloyip/dtoa-benchmark/master/result/corei7920@2.67_cygwin32_gcc4.8.html)
* [corei7920@2.67_cygwin64_gcc4.8](http://rawgit.com/miloyip/dtoa-benchmark/master/result/corei7920@2.67_cygwin64_gcc4.8.html)

## Implementations

Function      | Description
--------------|-----------
ostringstream | `std::ostringstream` in C++ standard library with `setprecision(17)`.
ostrstream    | `std::ostrstream` in C++ standard library with `setprecision(17)`.
sprintf       | `sprintf()` in C standard library with `"%.17g"` format.
[gay](http://www.netlib.org/fp/) | David M. Gay's `dtoa()` C implementation.
[grisu2](http://florian.loitsch.com/publications/bench.tar.gz?attredirects=0)        | Florian Loitsch's Grisu2 C implementation [1].
[doubleconv](https://code.google.com/p/double-conversion/)    |  C++ implementation extracted from Google's V8 JavaScript Engine with `EcmaScriptConverter().ToShortest()` (based on Grisu3, fall back to slower bignum algorithm when Grisu3 failed to produce shortest implementation).
[fpconv](https://github.com/night-shift/fpconv)        | [night-shift](https://github.com/night-shift)'s  Grisu2 C implementation.
milo          | [miloyip](https://github.com/miloyip)'s Grisu2 C++ header-only implementation.
null          | Do nothing.

Notes:

1. `tostring()` is not tested as it does not fulfill the roundtrip requirement.

2. Grisu2 is chosen because it can generate better human-readable number and >99.9% of results are in shortest. Grisu3 needs another `dtoa()` implementation for not meeting the shortest requirement.

## FAQ

1. How to add an implementation?
   
   You may clone an existing implementation file. And then modify it and add to the CMake config. Note that it will automatically register to the benchmark by macro `REGISTER_TEST(name)`.

   Making pull request of new implementations is welcome.

2. Why not converting `double` to `std::string`?

   It may introduce heap allocation, which is a big overhead. User can easily wrap these low-level functions to return `std::string`, if needed.

3. Why fast `dtoa()` functions is needed?

   They are a very common operations in writing data in text format. The standard way of `sprintf()`, `std::stringstream`, often provides poor performance. The author of this benchmark would optimize the `sprintf` implementation in [RapidJSON](https://github.com/miloyip/rapidjson/), thus he creates this project.

## References

[1] Loitsch, Florian. ["Printing floating-point numbers quickly and accurately with integers."](http://florian.loitsch.com/publications/dtoa-pldi2010.pdf) ACM Sigplan Notices 45.6 (2010): 233-243.

## Related Benchmarks and Discussions

* [Printing Floating-Point Numbers](http://www.ryanjuckett.com/programming/printing-floating-point-numbers/)
