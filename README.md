*This project has been created as part of the 42 curriculum by aiwane.*

# ft_printf

## Description

`ft_printf` is a 42 curriculum project that reimplements the core behavior of the C standard library function `printf()`.

By building it from scratch, you learn how variadic functions work in C, how a format string is parsed character by character, and how each conversion specifier maps to a type and an output routine. The project produces a static library `libftprintf.a` that exposes a single function:

```c
int  ft_printf(const char *format, ...);
```

The function scans the format string left to right. Ordinary characters are written directly to standard output via `write()`. When a `%` is found, the next character is read as a conversion specifier and the matching argument is fetched from the variadic list and printed. Unlike the original `printf()`, no internal output buffering is implemented.

| Specifier | Output |
|:---:|---|
| `%c` | Single character |
| `%s` | String (`NULL` prints as `(null)`) |
| `%p` | Pointer in hex with `0x` prefix (`NULL` prints as `(nil)`) |
| `%d` / `%i` | Signed decimal integer |
| `%u` | Unsigned decimal integer |
| `%x` / `%X` | Hexadecimal integer, lowercase / uppercase |
| `%%` | Literal `%` character |

## Instructions

```sh
make        # build libftprintf.a
make clean  # remove object files
make fclean # remove object files and libftprintf.a
make re     # fclean then make
```

To use the library in your own project:

```sh
cc your_file.c libftprintf.a
```

A test file `main.c` is included at the root of the repository. Build and run it with:

```sh
cc main.c libftprintf.a && ./a.out
```

Each test prints the output of `ft_printf` and `printf` side by side with their return values. Matching output and equal return values confirm correct behavior.

## Resources

**References**

- `man 3 printf` — Full specification of the printf family
- `man 3 stdarg` — `va_list`, `va_start`, `va_arg`, `va_end`
- [cppreference — Variadic functions](https://en.cppreference.com/w/c/variadic)
- [cppreference — fprintf](https://en.cppreference.com/w/c/io/fprintf)
- [42 Norm](https://github.com/42School/norminette)

**Use of AI**

Claude (Anthropic) was used as a learning aid for the following tasks and parts of the project:

- Clarifying subject requirements and edge case behavior (`INT_MIN`, `NULL` for `%s` and `%p`)
- Reviewing the file structure and separation of responsibilities
- Discussing the `va_list *` design choice and the base conversion algorithm
- Improving README structure and wording

All implementation decisions were made and verified by the author against the C standard, the 42 Norm, and the behavior of the system `printf()`.

## Algorithm and Data Structure

### File structure

```
ft_printf.h    Header — macros and prototypes
ft_printf.c    Entry point — format string scanning loop
ft_convert.c   Dispatcher — routes each specifier to the right handler
ft_number.c    Number formatting — signed, unsigned, hex, pointer
ft_output.c    Low-level output — wrappers around write()
ft_utils.c     Utilities — ft_strlen, ft_putnbr_base
```

Each file owns exactly one concern. `ft_printf.c` only scans and dispatches; it has no knowledge of how any individual conversion works. This makes it easy for a reader to find any piece of logic by filename alone.

### Processing flow

```
ft_printf("Hello %s, score: %d\n", name, score)
         |
         v
  scan left to right (tracked by index)
         |
    .----+------.
    |           |
 ordinary    '%' found
 character       |
    |        read next char -> ft_convert()
 ft_write_char   |
             .---+---.---.---.
            %c  %s  %d  %x  %p  ...
             |   |   |   |   |
          char str int hex 0x+hex
```

The main loop stays small because every conversion difference is pushed into the leaf functions.

### Variadic arguments — why va_list is passed as a pointer

C variadic arguments are managed with four macros from `<stdarg.h>`:

```c
va_list  args;
va_start(args, format);  // position the cursor after format
va_arg(args, int);       // read one int and advance the cursor
va_end(args);            // clean up
```

Every call to `va_arg` advances an internal cursor. If `va_list` were passed by value to a helper function, the cursor would advance inside that function but the caller would not see the change — the next specifier would read the wrong argument.

Passing `va_list *` (a pointer) ensures that every `va_arg` call moves the same shared cursor:

```c
int  ft_convert(char type, va_list *args);
//                                 ^--- pointer: caller sees every advance
```

For `ft_printf("%s %d", "hello", 42)`:

```
ft_convert 's' -> va_arg reads "hello", cursor advances to 42
ft_convert 'd' -> va_arg reads 42  <- correct, because cursor is shared
```

### Base conversion — why recursion works naturally

Dividing an integer by its base yields digits in reverse order, least significant first:

```
1234 / 10 -> remainder 4  (ones)
 123 / 10 -> remainder 3  (tens)
  12 / 10 -> remainder 2  (hundreds)
   1 / 10 -> remainder 1  (thousands)
```

Recursion solves the ordering problem: each call recurses before printing, so the deepest call (most significant digit) prints first and the rest unwind in the correct order.

```
putnbr_base(1234)
  putnbr_base(123)
    putnbr_base(12)
      putnbr_base(1)
        -> write '1'   <- deepest call, prints first
      -> write '2'
    -> write '3'
  -> write '4'
```

`ft_putnbr_base` takes the digit table and base length as parameters, so the same function handles `%u` (base 10), `%x` (base 16 lowercase), `%X` (base 16 uppercase), and the numeric part of `%p`.

### INT_MIN edge case

Negating `INT_MIN` (`-2147483648`) as a plain `int` overflows because the result `2147483648` exceeds `INT_MAX` (`2147483647`) — this is undefined behavior in C:

```c
int n = INT_MIN;
n = -n;           // undefined behavior
```

Widening to `long` before negating is safe on a 64-bit system because `long` is 64 bits:

```c
long number = nbr;
if (number < 0)
{
    ft_write_char('-');
    number = -number;   // 2147483648 fits in long
}
```

### Error propagation

Every output function returns the byte count written, or `-1` on a `write()` failure. Each caller checks the return value and propagates `-1` immediately:

```
ft_write_char()   -> -1
ft_print_signed() -> -1
ft_convert()      -> -1
ft_printf()       -> -1
```

All functions follow the same convention, so error handling requires only a single check at each call site.

### Why no struct in the mandatory part

The mandatory part needs only three variables in `ft_printf`:

| Variable | Purpose |
|---|---|
| `index` | Current position in the format string |
| `count` | Total bytes written so far |
| `result` | Return value of the last output call |

One character after `%` is enough to determine the conversion — there is nothing to accumulate, so a struct adds no value. The bonus part introduces flags (`-`, `0`, `.`, `#`, `+`) and a minimum field width that must all be stored before the conversion character is known. That is the point where a struct becomes necessary.
