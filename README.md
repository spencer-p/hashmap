# Hashmap

This is a reference implementation of a hashmap or dictionary in C. It maps
strings to arbitrary `void *` pointers. I wrote it largely for educational
purposes.

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

## Caveats

This implementation does not account for freeing deleted data. In cases where a
single item is removed, the orphan value is returned for the user to free
themselves. When the entire data structure is freed, there is potential for
memory loss. The unit tests use string literals as values and do not worry about
managing the value memory, only the actual hashmap memory. In the future it
would be trivial to add a function pointer to the constructor for freeing
values.

## License

This project is licensed under the WTFPL.
