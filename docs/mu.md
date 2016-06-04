---
layout: page
---

Getting started with Mu
-----------------------
``` mu
# Yes yes, a hello world program
print('Hello World!')
```

This is a (hopefully complete) guide to the [Mu language](http://mu-script.org).
The easiest way to learn Mu is interactively, so I would suggest downloading
the [Mu executable](https://github.com/mu-script/mux) so you can play around
with the examples. Anyways, lets get started!

Types
-----
Mu is designed to be as simple to reason about. To achieve this, Mu is built
around a small set of simple concepts that are composable in powerful ways.

Mu has only five types. Understanding these types and how they complement
each other is the key to understanding Mu.

Nil
---
``` mu
let a = nil
let b = _
```

Nil represents the complete lack of value. Any uninitialized variables
default to the value nil and assigning nil to a variable effectively
deletes it.

Numbers
-------
``` mu
let a = 2
let b = -3.14
let c = 0.3e-22
let d = 0xfc80
let e = 0b1p16
let f = inf
```

The number type represents real numbers. Implemented as floating-point
values, numbers are limited only by the precision of the processor.
The precision is garunteed to span the maximum size of Mu's data structures, 
so I wouldn't worry too much about integer rounding errors.

Infinity is a special value that represents the numeric upper-limit.
Greater than any other number except itself, infinity is useful for
representing unbounded arguments.

Strings
-------
``` mu
let a = 'hi'
let b = "hello"
let c = 'a\nb\nd'
let d = "\0\0\0\0"
let e = '\x68\x69!'
```

The string type represents an immutable array of bytes. The length is
stored with the string allowing any 8bit values. Strings are interned 
to minimize memory consumption and allow constant-time equality tests.

Unlike most interpreted languages, values are _not_ automatically coerced
into strings unless explicitly casted with [repr](/docs/builtins#repr) to
avoid surprising mistakes.

Tables
------
``` mu
let a = ['x': 1, 'y': 2]
let b = [1: 'x', 2: 'y']
let c = [1, 'a', 2, 'b', 3, 'c']
let d = [x: 1, y: 2]

a['x'] # looks up 1
a.y    # looks up 2
a.z    # looks up nil
```

The table type represents an associative array of key/value pairs.
Implemented as a hashtable, tables allow average constant-time lookup 
and assignment. Any Mu type can be used as a key or value, with nil
representing a missing entry. Tables are surprisingly powerful and
can emulate many of the data-structures found in more complex languages.

Functions
---------
``` mu
let a = fn() -> 1
let b = fn(a) -> a
fn c() -> 3

a()  # returns 1
b()  # returns nil
b(2) # returns 2
c()  # returns 3
c(2) # returns 3
```

Functions are first-class values in Mu, which means functions get their
own type like any other value. Functions have lexical scope which
allows them to contain state and support composability. Functions offer
a very flexible representation of computation in Mu.

Don't worry if the function type seems ill-defined right now. As functions
are central to Mu, their syntax and utility will be covered in more detail.

Syntax
------
``` mu
# Find all of the prime factors
fn factor(n)
    for (i = range(2, n-1))
        if (n % i == 0)
            let fs = factor(n/i)
            push(fs, i)
            return fs

    return [n]

print(factor(43*29*7*5*3*3))
```

Mu has familiar syntax for developers coming from C influenced languages,
however reduces syntactic noise by relying on a dynamic type system
and whitespace sensitivity.

Whitespace is entirely optional and may be omitted in favor of explicit syntax.
Statements are delimited by newlines outside of parentheses and by explicit
semicolons. Blocks of statements are grouped by indention, but may be 
explicitely overridden by braces. The syntax of Mu generally does what you
would expect it to, in an effort to avoid programming errors and improve
readability.

Operators
---------
``` mu
# Reverse-Polish calculator
fn calc(program)
    let stack = []
    let ops = ['+': (+), '-': (-), '*': (*), '/': (/)]

    for (c = split(program))
        if (!ops[c])
            push(stack, parse(c))
        else
            let b, a = pop(stack), pop(stack)
            push(stack, ops[c](a, b))

    return pop(stack)

# Prints 7
print(calc('1 2 3 * +'))
print(1 + 2*3)

# Prints 9
print(calc('1 2 + 3 *'))
print(1+2 * 3)
```
Mu is composed of entirely table lookups and function calls. In Mu,
operators are really just syntactic sugar for function calls. Outside
of binary and unary expressions, operators can be treated like any
other identifier.

To simplify the language, operators do not have implicit precedence.
Instead, operator precedence is definied lexically by the amount of
whitespace around operators and their arguments. The result is
expressions that usually do what you would expect. Of course, precedence 
may be explicitely overridden by parentheses.


Assignments
-----------
``` mu
# Returns both a parsed number and the remaining string
fn nparse(s)
    fn isnum(c)
        return c >= '0' and c <= '9'

    let n = str(take(isnum, s))
    return parse(n), sub(s, len(n), inf)

# Formats a string
fn format(f, ..args)
    let buffer = []
    let ops = ['x': hex, 'o': oct, 'b': bin]
    f = tbl(f)

    while (len(f) > 0)
        [c, ..f] = f

        if (c == '%')
            let n, [c, ..f] = nparse(f)
            let [x, ..args] = args
            c = pad((ops[c] or repr)(x), -n)

        push(buffer, c)

    return str(buffer)

# Simple printf
fn printf(f, ..args)
    print(format(f, ..args))

printf("Hi! %6d %6d %6d", 111, 222, 333)
```


assignments unpacking?


Control Flow
------------
control flow functions/returns

``` mu
# BF Interpreter
fn bf(program)
    let tape = []
    let cell = 0
    let pc = 0
    let buffer = []

    # Precalculate all the loop offsets
    let loop = [targets: [], stack: []]

    for (offset, op = pairs(program))
        if (op == '[')
            push(loop.stack, offset)
        else if (op == ']')
            target = pop(loop.stack)
            loop.targets[offset] = target
            loop.targets[target] = offset

    # Opcodes
    let ops = [
        '>': fn() { cell = cell+1 },
        '<': fn() { cell = cell-1 },
        '+': fn() { tape[cell] = (tape[cell] or 0) + 1 },
        '-': fn() { tape[cell] = (tape[cell] or 0) - 1 },
        '.': fn() { push(buffer, str(tape[cell])) },
        '[': fn() { if (tape[cell] == 0) pc = loop.targets[pc] },
        ']': fn() { if (tape[cell] != 0) pc = loop.targets[pc] },
    ]

    # Interpreter loop
    while (pc < len(program))
        let op = ops[sub(program, pc)]
        if (!op)
            pc = pc + 1
            continue

        op()
        pc = pc + 1
        print(tape)

    print(str(buffer))

# Hello World Program
bf('++++++++++[>+++++++>++++++++++>+++>+<<<<-]' ++
   '>++.>+.+++++++..+++.>++.<<+++++++++++++++.' ++
   '>.+++.------.--------.>+.>.')

```

Lexical Scope
-------------
tail recursion?

``` mu
regex example
```

Iterators
---------
``` mu
iteration over rose-tree?
```

Inheritance
-----------
```
vector example
```

