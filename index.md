---
layout: page
---

Mu script
---------
Mu is a lightweight scripting language designed to be easily embedded into
existing projects. With simplicity as its core goal, Mu boasts a minimal
language backed by a small but powerful builtin library.

``` mu
# A quicksort implementation
fn qsort(data)
    let [x, ..data] = tbl(data)
    if (len(data) == 0)
        return [x]

    let small = filter(fn(y) -> y <  x, data)
    let large = filter(fn(y) -> y >= x, data)
    return qsort(small) ++ [x] ++ qsort(large)

print(qsort([1,5,2,8,6,4,5,2,9]))
```

Learn more
----------
[Mu language guide](/docs/mu)  
Start here to learn about the language.

[Mu executable](https://github.com/mu-script/mux)   
Setup a local interpreter to quickly jump into Mu.

[Mu source](https://github.com/mu-script/mu)  
Get involved in the open-source project.

[Builtins reference](/docs/builtins)  
Overview of the builtin library.
