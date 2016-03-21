// Simple javscript syntax highlighter

// Syntax for the Mu scripting language
var language = 'mu'
var syntax = [
    ['comment', /#.*$/],

    ['define',  /\b(let|fn|type)\b/               ],
    ['control', /\b(if|else|while|for|and|or)\b/  ],
    ['control', /\b(break|continue|return)\b/     ],
    ['type',    /\b(num|str|tbl|fn_)\b/           ],
    ['literal', /\b(nil|_|inf|e|pi|true|false)\b/ ],

    ['literal', /'(\\'|[^'])*'|"(\\"|[^"])*"/,
        ['special', /\\[\\'"fnrtv0]/     ],
        ['special', /\\b[01]{8}/         ],
        ['special', /\\o[0-7]{3}/        ],
        ['special', /\\d[0-9]{3}/        ],
        ['special', /\\x[0-9a-fA-F]{2}/  ]],

    ['literal', /\b[0-9]+(\.[0-9]+)?([eEpP][+-]?[0-9]+)?\b/                 ],
    ['literal', /\b0[bB][01]+(\.[01]+)?([eEpP][+-]?[0-9]+)?\b/              ],
    ['literal', /\b0[oO][0-7]+(\.[0-7]+)?([eEpP][+-]?[0-9]+)?\b/            ],
    ['literal', /\b0[xX][0-9a-fA-F]+(\.[0-9a-fA-F]+)?([eEpP][+-]?[0-9]+)?\b/],
]

function syntax_precompile(syntax, offset) {
    for (var i = (offset || 0); i < syntax.length; i++) {
        syntax[i][1] = new RegExp(syntax[i][1].source, 'gm')
        syntax_precompile(syntax[i], 2)
    }
}

function syntax_span(code, syntax, soffset) {
    var result = ''
    var offset = 0

    while (offset < code.length) {
        var i = soffset || 0;
        for (; i < syntax.length; i++) {
            syntax[i][1].lastIndex = offset
            var match = syntax[i][1].exec(code)

            if (match && match.index == offset) {
                result += '<span class="code ' + syntax[i][0] + '">'
                if (syntax[i].length > 2) {
                    result += syntax_span(match[0], syntax[i], 2)
                } else {
                    result += match[0]
                }
                result += '</span>'

                offset += match[0].length
                break
            }
        }

        if (i == syntax.length) {
            result += code[offset]
            offset += 1
        }
    }

    return result
}

function syntax_highlight() {
    syntax_precompile(syntax)

    var nodes = document.getElementsByClassName('language-' + language)
    for (var n = 0; n < nodes.length; n++) {
        nodes[n].innerHTML = syntax_span(nodes[n].innerHTML, syntax)
    }
}

(function(hook) {
    var oldhook = window.onload
    if (!oldhook) window.onload = hook
    else          window.onload = function() { oldhook(); hook(); }
})(syntax_highlight)
