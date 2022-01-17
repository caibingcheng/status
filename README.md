## status

status is a header-only/compiled C++ library. It provides utility methods for status setting and getting.

the library provide 2 default class. `safe_status` is a multi-thread safety class, `fast_status` is a faster but not multi-thread safety class.

find the example [here](./example.cpp), compile & execute:
```Shell
$ g++ example.cpp -o example -lpthread
$ ./example
```