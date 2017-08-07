function repl() {
    var mu_repl = Module.cwrap('mu_repl', 'string', ['string'])

    var term = $('#repl').terminal(function(command) {
        if (command !== '') {
            var result = mu_repl(command);
            if (result != undefined) {
                this.echo(String(result));
            }
        }
    }, {
        greetings: false,
        name: 'repl',
        height: 400,
        prompt: '> ',
    });

    Module.print = term.echo
    Module.printErr = term.error
}

(function(hook) {
    var oldhook = window.onload
    if (!oldhook) window.onload = hook
    else          window.onload = function() { oldhook(); hook(); }
})(repl)
