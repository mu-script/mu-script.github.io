---
layout: page
---

Mu script
---------
Hi! Welcome to the home of the Mu scripting language. Currently
the site still needs some work, so sorry if there isn't much here
at the moment.

In the meantime, feel free to look into the current
[development of Mu]({{site.github}}/mu).

Example
-------
In the meantime, here's some quick examples of what Mu should look like:

~~~ mu
# Yes yes, a hello world program
print('Hello World!')
~~~

~~~ mu
# Naive factorial function
fn fac(n) -> if (n == 0) 1 else n*fac(n-1)

# results in +inf
# not really sure what I was expecting
print(fac(100))
~~~

~~~ mu
# Simple quicksort implementation
fn qsort(data)
    let x, data = data[0], sub(data, 1, inf)
    let smaller = qsort(tbl(filter(fn(y) -> x >= y, data)))
    let bigger  = qsort(tbl(filter(fn(y) -> x < y, data)))
    return chain(smaller, [x], bigger)

# Of course we could just use sort
data = [1,5,2,8,6,4,4,5,2,9]
print('[', join(map(repr, qsort(data)), ', '), ']')
print('[', join(map(repr, sort(data)),  ', '), ']')
~~~

~~~ mu
# Solution to Project Euler problem #4
# Simply brute forces the answer

fn ispalin(n)
    let r = repr(n)
    return r == str(reverse(r))

let palins = []

for (x = range(999, 0, -1))
    for (y = range(999, 0, -1))
        if (ispalin(x * y))
            palins[x*y] = [x,y]

    print(x)

for (p, [x, y] = sort(pairs(palins)))
    print(pad(repr(x), 8), '*',
          pad(repr(y), 8), ' = ',
          pad(repr(p), 8))
~~~

~~~ mu
# Simple vector implementation
type vec()
    fn create(self, x, y)
        self[0], self[1] = x, y

    fn `+`([ax,ay],[bx,by]) -> vec(ax+bx, ay+by)
    fn `-`([ax,ay],[bx,by]) -> vec(ax-bx, ay-by)

    fn len(self) -> self->lensq()
    fn lensq([x,y]) -> (x^2 + y^2)^0.5

let a = vec(1, 0)
let b = vec(0, 1)
print('dist: ', (b-a)->len())
~~~
