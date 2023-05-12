# icuformat

Note: instructions expect that you are in linux and installed icu.

## How to build
```
autoreconf --install
./configure --prefix path_of_installation
make
make install
```
## How to use
follow build instructions then run by executing:

```
./path_of_install/bin/icuformat key
```
or use for test
```
./path_of_install/bin/test
```