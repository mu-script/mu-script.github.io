function repl() {
    $('#repl').terminal(function(command) {
        if (command !== '') {
            var result = window.eval(command);
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
}

(function(hook) {
    var oldhook = window.onload
    if (!oldhook) window.onload = hook
    else          window.onload = function() { oldhook(); hook(); }
})(repl)
