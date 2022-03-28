=================================
PRPC: Petit Remote Procedure Call
=================================

:Authors:  - Florian Dupeyron <florian.dupeyron@mugcat.fr>
:Date:     Around 2018

Petit RPC is an old project that aimed to bring a light-footprint RPC interface,
inspired by JSON-RPC. I found this project in an old backup, so I upload it as a kind
of nostalgic backup, and maybe it can find its uses.

Build dependencies
==================

- `re2c`: to generate the lexer source files.
- `python3`: build scripts.
- `ninja`: build

How to build
============

.. code:: bash

    $ /ext/cmdline  
    > ./gen 

    Adding re2c file src/prpc/prpc/lex.re.c

    Adding static library libprpc
     -- Adding object target for src/prpc/prpc/lex.c
     -- Adding object target for src/prpc/prpc/parse.c
     -- Adding object target for src/prpc/prpc/msg.c
     -- Adding object target for src/prpc/prpc/cmds.c

    Adding static library libmain
     -- Adding object target for src/common/sys/ansiterm.c
     -- Adding object target for src/common/sys/log.c

    Adding re2c file src/example/cmds.re.c

    Adding executable example
     -- Adding object target for src/example/cmds.c
     -- Adding object target for src/example/app.c
     -- Adding object target for src/example/main.c

    Adding static library libtest

    Adding executable tests/parse
     -- Adding object target for tests/parse.c

    Adding executable tests/lex
     -- Adding object target for tests/lex.c

    Adding executable tests/msg
     -- Adding object target for tests/msg.c

    $ /ext/cmdline  
    > ninja
    [14/14] Linking bin/example
