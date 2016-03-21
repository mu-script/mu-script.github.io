---
layout: page
---

Builtins
--------

| Consts            | Types         | Logic         | Arith             | Bit/Set     | String                | Data            | Iterator              | Function        | IO                  |
| ----------------- | ------------- | ------------- | ----------------- | ----------- | --------------------- | --------------- | --------------------- | --------------- | ------------------- |
| [`nil`](#nil)     | [`num`](#num) | [`and`](#and) | [`+`](#+)         | [`~`](#~)   | [`parse`](#parse)     | [`len`](#len)   | [`iter`](#iter)       | [`bind`](#bind) | [`print`](#print)   |
| [`_`](#_)         | [`str`](#str) | [`or`](#or)   | [`-`](#-)         | [`|`](#\|)  | [`repr`](#repr)       | [`tail`](#tail) | [`pairs`](#pairs)     | [`comp`](#comp) | [`error`](#error)   |
| [`true`](#true)   | [`tbl`](#tbl) | [`!`](#!)     | [`*`](#*)         | [`&`](#&)   | [`bin`](#bin)         | [`push`](#push) | [`range`](#range)     |                 | [`import`](#import) |
| [`false`](#false) | [`fn_`](#fn_) | [`==`](#==)   | [`/`](#/)         | [`&~`](#&~) | [`oct`](#oct)         | [`pop`](#pop)   | [`repeat`](#repeat)   |                 |                     |
| [`inf`](#inf)     |               | [`!=`](#!=)   | [`//`](#//)       | [`<<`](#<<) | [`hex`](#hex)         | [`++`](#++)     | [`seed`](#seed)       |                 |                     |
| [`inf`](#inf)     |               | [`is`](#is)   | [`%`](#%)         | [`>>`](#>>) | [`find`](#find)       | [`sub`](#sub)   | [`map`](#map)         |                 |                     |
| [`e`](#e)         |               | [`<`](#<)     | [`^`](#^)         |             | [`replace`](#replace) |                 | [`filter`](#filter)   |                 |                     |
| [`pi`](#pi)       |               | [`>`](#>)     | [`log`](#log)     |             | [`split`](#split)     |                 | [`reduce`](#reduce)   |                 |                     |
| [`id`](#id)       |               | [`<=`](#<=)   | [`abs`](#abs)     |             | [`join`](#join)       |                 | [`any`](#any)         |                 |                     |
|                   |               | [`>=`](#>=)   | [`floor`](#floor) |             | [`pad`](#pad)         |                 | [`all`](#all)         |                 |                     |
|                   |               |               | [`ceil`](#ceil)   |             | [`strip`](#strip)     |                 | [`zip`](#zip)         |                 |                     |
|                   |               |               | [`cos`](#cos)     |             |                       |                 | [`chain`](#chain)     |                 |                     |
|                   |               |               | [`acos`](#acos)   |             |                       |                 | [`take`](#take)       |                 |                     |
|                   |               |               | [`sin`](#sin)     |             |                       |                 | [`drop`](#drop)       |                 |                     |
|                   |               |               | [`asin`](#asin)   |             |                       |                 | [`min`](#min)         |                 |                     |
|                   |               |               | [`tan`](#tan)     |             |                       |                 | [`max`](#max)         |                 |                     |
|                   |               |               | [`atan`](#atan)   |             |                       |                 | [`sort`](#sort)       |                 |                     |
|                   |               |               |                   |             |                       |                 | [`reverse`](#reverse) |                 |                     |


Constants
---------
<dl>
<div id="nil"><div id="_"><div id="false">
<dt markdown="span">[nil](#nil), [_](#nil), [false](#false)</dt>
</div></div></div>
<dd markdown="block">
Representation of nil, the absence of a value.
</dd>

<dt id="true" markdown="span">[true](#true)</dt>
<dd markdown="block">
Arbitrarily 1.

Comparison functions return this value on success, however any non-nil value is considered true.
</dd>

<dt id="inf" markdown="span">[inf](#inf)</dt>
<dd markdown="block">
Numeric representation of infinity.
</dd>

<dt id="e" markdown="span">[e](#e)</dt>
<dd markdown="block">
The constant e = 2.718281..
</dd>

<dt id="pi" markdown="span">[pi](#pi)</dt>
<dd markdown="block">
The constant pi = 3.141592..
</dd>

<dt id="id" markdown="span">[id](#id)</dt>
<dd markdown="block">
The identity function, returns any arguments without modification.
</dd>
</dl>

Type Casts
----------
<dl>
<dt id="num" markdown="span">[num](#num)(x) -> num</dt>
<dd markdown="block">
Converts x to a number.

By default returns `0`.  
If x is a number, x is returned unmodified.  
If x is a single character string, returns the ascii value of x.

To parse a string representation, [parse](#parse) can be used.
</dd>

<dt id="str" markdown="span">[str](#str)(x) -> str</dt>
<dd markdown="block">
Converts x to a string.

By default returns `""`.  
If x is a number, converts x to an ascii character.  
If x is a string, x is returned unmodified.  
If x is iterable, the strings in x are joined together.

To get a string representation, [repr](#repr) can be used.
</dd>

<dt id="tbl" markdown="span">[tbl](#tbl)(x[, tail]) -> tbl</dt>
<dd markdown="block">
Converts x to a table.

By default returns `[]`.  
If x is a number, the table will be preallocated for x pairs.  
If x is a table, a shallow copy of x is returned.  
If x is iterabe, x is exhausted and stored in the resulting table as either key/value pairs or at increasing indices.

If a tail is provided, the new table inherits the tail's elements.
</dd>

<dt id="fn_" markdown="span">[fn\_](#fn_)(x) -> fn</dt>
<dd markdown="block">
Converts x to a function.

By default id is returned.  
If x is a function, x is returned unmodified.

Note: the the name `fn_` is used to avoid conflict with function declarations.
</dd>
</dl>

Logic Operations
----------------
<dl>
<dt id="and" markdown="span">x [and](#and) y -> bool</dt>
<dd markdown="block">
Lazily evaluates the logical and of x and y.
</dd>

<dt id="or" markdown="span">y [or](#or) y -> bool</dt>
<dd markdown="block">
Lazily evaluates the logical or of x and y.
</dd>

<dt id="!" markdown="span">[!](#!)x -> bool</dt>
<dd markdown="block">
Evaluates the logical inverse of x.
</dd>

<div id="=="><div id="!=">
<dt markdown="span">
x [==](#==) y -> bool  
x [!=](#!=) y -> bool  
</dt>
</div></div>
<dd markdown="block">
Tests x and y for equality.

If x/y are nil, result is always true.  
If x/y are numbers or strings, result is true if x and y are the same value.  
If x/y are tables or functions, result is true if x and y reference the same value.
</dd>

<dt id="is" markdown="span">[is](#is)(x, t) -> bool</dt>
<dd markdown="block">
Returns true if x is of type t.
</dd>

<div id="<"><div id=">"><div id="<="><div id=">=">
<dt markdown="span">
x [<](#<) y -> bool  
x [>](#>) y -> bool  
x [<=](#<=) y -> bool  
x [>=](#>=) y -> bool
</dt>
</div></div></div></div>
<dd markdown="block">
Compares x and y.

Numbers are ordered numerically.
Strings are ordered lexicographically.
</dd>
</dl>

Arithmetic Operations
---------------------
<dl>
<dt id="+" markdown="span">
[+](#+)x -> num  
x [+](#+) y -> num
</dt>
<dd markdown="block">
Returns x unmodified or the sum of x and y.
</dd>

<dt id="-" markdown="span">
[-](#-)x -> num
x [-](#-) y -> num
</dt>
<dd markdown="block">
Returns the negation of x or the difference of x and y.
</dd>

<dt id="*" markdown="span">x [\*](#*) y -> num</dt>
<dd markdown="block">
Returns the product of x and y.
</dd>

<dt id="/" markdown="span">x [/](#/) y -> num</dt>
<dd markdown="block">
Returns the quotient of x and y.
</dd>

<dt id="//" markdown="span">x [//](#//) y -> num</dt>
<dd markdown="block">
Returns the floored quotient of x and y.
</dd>

<dt id="%" markdown="span">x [%](#%) y -> num</dt>
<dd markdown="block">
Returns the modulo of x and y.
</dd>

<dt id="^" markdown="span">x [&#94;](#^) y -> num</dt>
<dd markdown="block">
Returns x raised to the power of y.
</dd>

<dt id="log" markdown="span">[log](#log)(x[, base]) -> num</dt>
<dd markdown="block">
Returns the logarithm of x.

By default the base is e.
</dd>

<dt id="abs" markdown="span">[abs](#abs)(x) -> num</dt>
<dd markdown="block">
Returns the absolute value of x.
</dd>

<dt id="floor" markdown="span">[floor](#floor)(x) -> num</dt>
<dd markdown="block">
Returns the largest integer value <= x.
</dd>

<dt id="ceil" markdown="span">[ceil](#ceil)(x) -> num</dt>
<dd markdown="block">
Returns the smallest integer value >= x.
</dd>

<div id="cos"><div id="acos">
<dt markdown="span">
[cos](#cos)(x) -> num  
[acos](#acos)(x) -> num
</dt>
</div></div>
<dd markdown="block">
Returns the cosine and arc-cosine in radians.
</dd>

<div id="sin"><div id="asin">
<dt markdown="span">
[sin](#sin)(x) -> num  
[asin](#asin)(x) -> num
</dt>
</div></div>
<dd markdown="block">
Returns the sine and arc-sine in radians.
</dd>

<div id="tan"><div id="atan">
<dt markdown="span">
[tan](#tan)(x) -> num  
[atan](#atan)(y[, x]) -> num
</dt>
</div></div>
<dd markdown="block">
Returns the tangent and arc-tangent in radians.

Optionally, atan can take two values. This is equivalent to `atan(y/x)` but in the correct quadrant.
</dd>
</dl>

Bitwise/Set Operations
------------------
<dl>
<dt id="~" markdown="span">
[~](#~)x -> v  
x [~](#~) y -> v
</dt>
<dd markdown="block">
Returns the bitwise not of x or the exclusive-or of x and y.

If x and y are tables, `~` performs the symmetric-difference of their keys.
</dd>

<dt id="|" markdown="span">x [|](#|) y -> v</dt>
<dd markdown="block">
Returns the bitwise-or of x and y.

If x and y are tables, `|` performs the union of their keys.
</dd>

<dt id="&" markdown="span">x [&](#&) y -> num</dt>
<dd markdown="block">
Returns the bitwise-and of x and y.

If x and y are tables, `&` performs the intersection of their keys.
</dd>

<dt id="&~" markdown="span">x [&~](#&~) y -> num</dt>
<dd markdown="block">
Returns the bitwise and of x and ~y.

If x and y are tables, `&~` performs the set-difference of their keys.
</dd>

<dt id="<<" markdown="span">x [\<\<](#<<) y -> num</dt>
<dd markdown="block">
Returns x bit shifted left arithmetically by y digits.
</dd>

<dt id=">>" markdown="span">x [\>\>](#>>) y -> num</dt>
<dd markdown="block">
Returns x bit shifted right arithmetically by y digits.
</dd>
</dl>

String Operations
-----------------
<dl>
<dt id="parse" markdown="span">[parse](#parse)(x) -> v</dt>
<dd markdown="block">
Returns the string x parsed as a Mu literal.

If x could not be parsed, an error is raised.
</dd>

<dt id="repr" markdown="span">[repr](#repr)(x[, depth]) -> str</dt>
<dd markdown="block">
Returns a string representation of x.

Depth indicates how many nested tables to represent, by default depth is `1`.
</dd>

<div id="bin"><div id="oct"><div id="hex">
<dt markdown="span">
[bin](#bin)(x) -> str  
[oct](#oct)(x) -> str  
[hex](#hex)(x) -> str
</dt>
</div></div></div>
<dd markdown="block">
Returns the string representation of x in the specific base.
</dd>

<dt id="find" markdown="span">[find](#find)(x, str) -> lower, upper</dt>
<dd markdown="block">
Finds the first occurance of x.

If x is not found, nil is returned.  
Otherwise, the lower and upper bounds of x are returned.
</dd>

<dt id="replace" markdown="span">[replace](#replace)(x, y, str) -> str</dt>
<dd markdown="block">
Replaces each occurance of x with y.
</dd>

<dt id="split" markdown="span">[split](#split)(x[, delim]) -> iter</dt>
<dd markdown="block">
Returns an iterator of the substrings separated by the delimiter.

By default the delimiter is `' '`.
</dd>

<dt id="join" markdown="span">[join](#join)(x[, delim]) -> str</dt>
<dd markdown="block">
Joins each element of x into a string separated by the delimiter.

By default the delimiter is `' '`.
</dd>

<dt id="pad" markdown="span">[pad](#pad)(x, len[, padding]) -> str</dt>
<dd markdown="block">
Pads x with padding until x has a length of at least len.

If len is negative, padding is added to the beginning of the string.  
By default the padding is `' '`.
</dd>

<dt id="strip" markdown="span">[strip](#strip)(x[, dir][, padding]) -> str</dt>
<dd markdown="block">
Strips padding from x.

Padding is stripped from both sides of x when dir is nil, the beginning when dir is negative, and the end when dir is positive.  
By default the padding is `' '`.
</dd>
</dl>

Data Structure Operations
-------------------------
<dl>
<dt id="len" markdown="span">[len](#len)(x) -> num</dt>
<dd markdown="block">
Returns the number of elements in x.
</dd>

<dt id="tail" markdown="span">[tail](#tail)(x) -> tbl</dt>
<dd markdown="block">
Returns the tail chain of x.
</dd>

<dt id="push" markdown="span">[push](#push)(x, v[, index])</dt>
<dd markdown="block">
Pushes v onto table x before the index.

By default, v is push onto the end of the table.
</dd>

<dt id="pop" markdown="span">[pop](#pop)(x[, index]) -> v</dt>
<dd markdown="block">
Pops v off the table x from the index

By default, v is popped off the end of the table.
</dd>

<dt id="++" markdown="span">x [++](#++) y -> v</dt>
<dd markdown="block">
Returns the concatenation of x and y.

When x/y are tables, a third argument can be provided to specify the offset for y.
</dd>

<dt id="sub" markdown="span">[sub](#sub)(x, lower[, upper]) -> v</dt>
<dd markdown="block">
Returns a subset of x specified by the range \[lower, upper).

Negative bounds indicate offsets from the right, and infinity indicates an unlimited boundary.  
The default upper bound is lower+1.
</dd>
</dl>

Iterator Operations
-------------------
<dl>
<dt id="iter" markdown="span">[iter](#iter)(x) -> iter</dt>
<dd markdown="block">
Returns an iterator that iterates over the elements of x.
</dd>

<dt id="pairs" markdown="span">[pairs](#pairs)(x) -> iter</dt>
<dd markdown="block">
Returns an iterator that iterates over the key/value pairs of x.

If x is not a table, increasing indices are used.
</dd>

<dt id="range" markdown="span">[range](#range)([start][, stop][, step]) -> iter</dt>
<dd markdown="block">
Returns an iterator through the range between start and stop incrementing by step.

By default start is `0`, stop is `inf`, and step is `1`.
</dd>

<dt id="repeat" markdown="span">[repeat](#repeat)(x[, n]) -> iter</dt>
<dd markdown="block">
Returns an iterator that repeats x, n times.

By default n is `inf`.
</dd>

<dt id="seed" markdown="span">[seed](#seed)([n]) -> iter</dt>
<dd markdown="block">
Returns a pseudo-random number generator seeded by n.

By default an arbitrary seed is used.  
If the same n is passed into seed, the same random sequence will be generated.
</dd>

<dt id="map" markdown="span">[map](#map)(x, iter) -> iter</dt>
<dd markdown="block">
Lazily applies the x to each element in the iterator.

If x returns nil, the element is filtered out.
</dd>

<dt id="filter" markdown="span">[filter](#filter)(x, iter) -> iter</dt>
<dd markdown="block">
Lazily filters out elements in the iterator when x returns false.
</dd>

<dt id="reduce" markdown="span">[reduce](#reduce)(x, iter[, ..init]) -> iter</dt>
<dd markdown="block">
Reduces the iterator to a single value by repeatedly applying x to an accumulator and element.

The inits are used to start the accumulator.  
If the inits are nil, the first element of iter is used.
</dd>

<dt id="any" markdown="span">[any](#any)(x, iter) -> bool</dt>
<dd markdown="block">
Returns true if x returns true for any element in the iterator.
</dd>

<dt id="all" markdown="span">[all](#all)(x, iter) -> bool</dt>
<dd markdown="block">
Returns true if x returns true for each element in the iterator.
</dd>

<dt id="zip" markdown="span">[zip](#zip)(..iters) -> iter</dt>
<dd markdown="block">
Iterates over the arguments in parallel, returning the aggregated elements.

If there is only a single iterator, it is treated as an iterator of iterators.
</dd>

<dt id="chain" markdown="span">[chain](#chain)(..iters) -> iter</dt>
<dd markdown="block">
Iterates over the arguments in series.

If there is only a single iterator, it is treated as an iterator of iterators.
</dd>

<dt id="take" markdown="span">[take](#take)(n, iter) -> iter</dt>
<dd markdown="block">
Consumes elements from the iterator and iterates over the consumed elements.

If n is a number, n elements are consumed.
If n is a function, elements are consumed until n returns true.
</dd>

<dt id="drop" markdown="span">[drop](#drop)(n, iter) -> iter</dt>
<dd markdown="block">
Consumes elements from the iterator and iterates over the remaining elements.

If n is a number, n elements are consumed.
If n is a function, elements are consumed until n returns true.
</dd>

<dt id="min" markdown="span">[min](#min)(..args) -> min</dt>
<dd markdown="block">
Returns the minimum value based on the [comparison operators](#<).

If only one argument is provided, it is iterated over to find the minimum.  
The result is ordered by only the first value.
</dd>

<dt id="max" markdown="span">[max](#max)(..args) -> max</dt>
<dd markdown="block">
Returns the maximum value based on the [comparison operators](#<).

If only one argument is provided, it is iterated over to find the maximum.  
The result is ordered by only the first value.
</dd>

<dt id="sort" markdown="span">[sort](#sort)(x) -> iter</dt>
<dd markdown="block">
Returns an iterator that iterates over the elements of x in sorted order.

The result is ordered by only the first value.
</dd>

<dt id="reverse" markdown="span">[reverse](#reverse)(x) -> iter</dt>
<dd markdown="block">
Iterates over the elements of x in reversed order.
</dd>
</dl>

Function Operations
-------------------
<dl>
<dt id="bind" markdown="span">[bind](#bind)(x, ..args) -> fn</dt>
<dd markdown="block">
Returns a function that will call x with args prepended to arguments.
</dd>

<dt id="comp" markdown="span">[comp](#comp)(..fns) -> fn</dt>
<dd markdown="block">
Returns a function that calls each function composed from right to left.
</dd>
</dl>

IO Operations
-------------
<dl>
<dt id="print" markdown="span">[print](#print)(..xs)</dt>
<dd markdown="block">
Prints each of the arguments and appends a newline.

repr is called on any argument that is not a string.
</dd>

<dt id="error" markdown="span">[error](#error)(..xs)</dt>
<dd markdown="block">
Errors with a message composed in the same was as [print](#print).
</dd>

<dt id="import" markdown="span">[import](#import)(name) -> module</dt>
<dd markdown="block">
Imports a module.

Available modules are implementation dependent.  
If the module is not found, nil is returned.  
Otherwise, a table is returned containing the module's functions and variables.
</dd>
</dl>
