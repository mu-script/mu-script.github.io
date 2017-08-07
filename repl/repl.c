/*
 * simple Mu repl for embedded with emscripten
 */
#include "mu/mu.h"
#include "mu/tbl.h"
#include "mu/fn.h"
#include "mu/vm.h"
#include "mu/str.h"
#include "mu/num.h"
#include <stdio.h>
#include <stdlib.h>
#include <emscripten.h>

// io hooks
void mu_sys_print(const char *message, muint_t len) {
    EM_ASM_({
        Module.print(Pointer_stringify($0, $1));
    }, message, len);
}

void mu_sys_error(const char *message, muint_t len) {
    EM_ASM_({
        throw 'error: ' + Pointer_stringify($0, $1);
    }, message, len);
}

// import hooks
static mcnt_t mu_bfn_dis(mu_t *frame) {
    if (!mu_isfn(frame[0])) {
        mu_errorf("expected mu function");
    }

    mu_t code = mu_fn_getcode(frame[0]);
    if (!code) {
        mu_errorf("expected mu function");
    }

    mu_dis(code);
    mu_dec(code);
    mu_dec(frame[0]);
    return 0;
}

MU_GEN_STR(mu_sys_key_dis, "dis")
MU_GEN_BFN(mu_sys_bfn_dis, 0x1, mu_bfn_dis)
MU_GEN_TBL(mu_sys_tbl_dis, {
    { mu_sys_key_dis, mu_sys_bfn_dis }
})

MU_GEN_TBL(mu_sys_imports, {
    { mu_sys_key_dis, mu_sys_tbl_dis }
})

mu_t mu_sys_import(mu_t name) {
    mu_t module = mu_tbl_lookup(mu_sys_imports(), name);
    return module;
}

// actual entry point
mu_t globals = 0;
char res_buffer[512];

EMSCRIPTEN_KEEPALIVE
char *mu_repl(const char *s) {
    if (!globals) {
        globals = mu_tbl_create(0);
        mu_tbl_settail(globals, MU_BUILTINS);
    }

    mu_t res = mu_eval(s, strlen(s), globals, 0x0f);

    mu_t repr = mu_fn_call(MU_REPR, 0x21, res, mu_num_fromuint(2));
    memcpy(res_buffer, mu_str_getdata(repr)+1, mu_str_getlen(repr)-2);
    res_buffer[mu_str_getlen(repr)-2] = '\0';
    mu_dec(repr);
    return res_buffer;
}
