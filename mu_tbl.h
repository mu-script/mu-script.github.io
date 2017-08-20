/*
 * Mu tbls, key-value lookup tables
 *
 * Copyright (c) 2016 Christopher Haster
 * Distributed under the MIT license in mu.h
 */
#ifndef MU_TBL_H
#define MU_TBL_H
#include "mu_config.h"
#include "mu_types.h"


// Definition of Mu's table type
//
// Each table is composed of an array of values
// with a stride for keys/values. If keys/values
// is not stored in the array it is implicitely
// stored as a range/offset based on the specified
// offset and length.
struct mtbl {
    mref_t ref;
    mlen_t len;
    mlen_t nils;
    muintq_t npw2;
    muintq_t isize;

    mu_t tail;
    mu_t *array;
};


// Table creation functions
mu_t mu_tbl_create(muint_t size);
mu_t mu_tbl_createtail(muint_t size, mu_t tail);

// Conversion operations
mu_t mu_tbl_fromlist(mu_t *list, muint_t n);
mu_t mu_tbl_frompairs(mu_t (*pairs)[2], muint_t n);
mu_t mu_tbl_frommu(mu_t m);

// Table access functions
mu_inline mlen_t mu_tbl_getlen(mu_t m);
mu_inline mu_t mu_tbl_gettail(mu_t m);

// Changing the tail of the table
void mu_tbl_settail(mu_t t, mu_t tail);

// Create constant reference to table
mu_inline mu_t mu_tbl_const(mu_t t);

// Recursively looks up a key in the table
// returns either that value or nil
mu_t mu_tbl_lookup(mu_t t, mu_t k);

// Inserts a value in the table with the given key
// without decending down the tail chain
void mu_tbl_insert(mu_t t, mu_t k, mu_t v);

// Recursively assigns a value in the table with the given key
// decends down the tail chain until its found
void mu_tbl_assign(mu_t t, mu_t k, mu_t v);

// Performs iteration on a table
bool mu_tbl_next(mu_t t, muint_t *i, mu_t *k, mu_t *v);
mu_t mu_tbl_iter(mu_t t);
mu_t mu_tbl_pairs(mu_t t);

// Table representation
mu_t mu_tbl_parsen(const mbyte_t **pos, const mbyte_t *end);
mu_t mu_tbl_parse(const char *s, muint_t n);
mu_t mu_tbl_repr(mu_t t, mu_t depth);

// Array-like manipulation
void mu_tbl_push(mu_t t, mu_t v, mint_t i);
mu_t mu_tbl_pop(mu_t t, mint_t i);

mu_t mu_tbl_concat(mu_t a, mu_t b, mu_t offset);
mu_t mu_tbl_subset(mu_t t, mint_t lower, mint_t upper);

// Set operations
mu_t mu_tbl_and(mu_t a, mu_t b);
mu_t mu_tbl_or(mu_t a, mu_t b);
mu_t mu_tbl_xor(mu_t a, mu_t b);
mu_t mu_tbl_diff(mu_t a, mu_t b);


// Table access functions
mu_inline mlen_t mu_tbl_getlen(mu_t m) {
    return ((struct mtbl *)((muint_t)m & ~7))->len;
}

mu_inline mu_t mu_tbl_gettail(mu_t m) {
    return mu_inc(((struct mtbl *)((muint_t)m & ~7))->tail);
}

mu_inline mu_t mu_tbl_const(mu_t t) {
    return mu_inc((mu_t)((MTTBL ^ MTRTBL) | (muint_t)t));
}


// Table constant macros
#define MU_DEF_LIST(name, ...)                                              \
mu_pure mu_t name(void) {                                                   \
    static mu_t ref = 0;                                                    \
    static mu_t (*const def[])(void) = __VA_ARGS__;                         \
    static struct mtbl inst = {0};                                          \
                                                                            \
    extern mu_t mu_tbl_initlist(struct mtbl *,                              \
            mu_t (*const *)(void), muint_t);                                \
    if (!ref) {                                                             \
        ref = mu_tbl_initlist(&inst, def, sizeof def / sizeof(def[0]));     \
    }                                                                       \
                                                                            \
    return ref;                                                             \
}

#define MU_DEF_TBL(name, ...)                                               \
mu_pure mu_t name(void) {                                                   \
    static mu_t ref = 0;                                                    \
    static mu_t (*const def[][2])(void) = __VA_ARGS__;                      \
    static struct mtbl inst = {0};                                          \
                                                                            \
    extern mu_t mu_tbl_initpairs(struct mtbl *, mu_t (*)(void),             \
            mu_t (*const (*)[2])(void), muint_t);                           \
    if (!ref) {                                                             \
        ref = mu_tbl_initpairs(&inst, 0,                                    \
                def, sizeof def / sizeof(def[0]));                          \
    }                                                                       \
                                                                            \
    return ref;                                                             \
}

#define MU_DEF_TBLTAIL(name, tail, ...)                                     \
mu_pure mu_t name(void) {                                                   \
    static mu_t ref = 0;                                                    \
    static mu_t (*const def[][2])(void) = __VA_ARGS__;                      \
    static struct mtbl inst = {0};                                          \
                                                                            \
    extern mu_t mu_tbl_initpairs(struct mtbl *, mu_t (*)(void),             \
            mu_t (*const (*)[2])(void), muint_t);                           \
    if (!ref) {                                                             \
        ref = mu_tbl_initpairs(&inst, tail,                                 \
                def, sizeof def / sizeof(def[0]));                          \
    }                                                                       \
                                                                            \
    return ref;                                                             \
}


#endif
