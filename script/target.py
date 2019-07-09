"""
####################
# Target types def #
####################

  Florian Dupeyron (floolfy)
  September 2018

"""

import re

class Target:
    def __init__( self, **args ):
        self.name = args.get    ( "name" )
        self.rule = args.get    ( "rule"         )
        self.deps = args.get    ( "deps", dict() )
        self.gen_name = args.get("gen_name", lambda x : x )
        self.gen_rule = args.get("gen_rule", lambda o, name, rule, deps : "build {name} : {rule} {deps}".format(
            name = name,
            rule = rule,
            deps = deps
        ))

        self.vars    = args.get("vars", dict() )
        self.aliases = args.get( "aliases", [] )

    def __str__( self ):
        return self.gen_name( self.name )

def obj( src ):
    """
    Generates obj file from source src
    """
    print( " -- Adding object target for " + str(src) )
    return Target(
        name     = str(src) + ".o",
        rule     = "cc",
        deps     = [ src ],
        gen_name = lambda x : "$dir_obj/" + x,
        vars     = { "cflags" : "$cflags -D__FILENAME__=\\\"{}\\\"".format(str(src)) }
    )

def executable( name, **args ):
    """
    Generates executable file <name> from :
       * srcs : source names (generate objs targets)
       * objs : additional objs
    """
    print( "\nAdding executable " + str(name) )
    objs = []
    for src in args.get("srcs"):
        dd = obj( src )
        for path in args.get( "incdirs", [] ):
            dd.vars[ "cflags" ] += " -I" + path
        objs.append( dd )


    return Target(
        name      = name,
        rule      = "ld",
        deps      = objs + args.get("objs", []),
        gen_name  = lambda x : "$dir_bin/" + x,
        aliases = args.get( "aliases", [] )
    )

def lib( name, **args ):
    """
    Generates static library <name> with :
        * srcs : source file names
        * objs : additional objects
    """
    print( "\nAdding static library " + str(name) )
    objs = []
    for src in args.get("srcs"):
        dd = obj( src )
        for path in args.get( "incdirs", [] ):
            dd.vars[ "cflags" ] += " -I" + path
        objs.append( dd )
    return Target(
        name     = name + ".a",
        rule     = "lib",
        deps     = objs + args.get("objs", []),
        gen_name = lambda x : "$dir_lib/" + x,
        aliases  = args.get("aliases", [])
    )

def re2c( name, **args ):
    print( "\nAdding re2c file " + str(name) )
    mt = re.match( "(.*?).re.c", name )
    if not mt : raise RuntimeError( "Could not match .re.c extension for target name " + repr(name) )
    cname = mt.group(1) + ".c"

    return Target(
        name = cname,
        rule = "re2c",
        deps = [ name ],
        aliases = args.get( "aliases", [] )
    )
