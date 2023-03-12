# icuformat

Note: instructions expect that you are in linux and installed icu.

## How to build
```
g++ icuformat.cpp -o icuformat `pkg-config --libs --cflags icu-uc icu-i18n icu-io`
genrb -d locales ./locales/*.txt
```
## How to use
follow build instructions then run by executing:

```
./icuformat key args
```

you can also use `test.sh`
