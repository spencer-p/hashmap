# Hashmap

This is a reference implementation of a hashmap or dictionary in C. I wrote it
largely for educational purposes.

It uses a fairly simple linked list chaining solution to manage collisions.

## Building

Make sure you have a working C compiler and GNU make.

```sh
make all
```

This will produce `hashmap.o` and `linkedlist.o` in the `src/` directory (in
addition to the unit tests in `tests/`).

## Testing

The tests require [libcheck](https://libcheck.github.io/check/), so make sure
you've got that installed.

```sh
make tests
```

This should automatically run the tests.

## License

This project is licensed under the WTFPL.
