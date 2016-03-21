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
Mu is designed to be as simple to understand as possible. To achieve this,
Mu is built around a small set of simple concepts that are composable in
powerful ways.

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

TODO
----
