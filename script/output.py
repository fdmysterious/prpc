"""
######################
# Output ninja rules #
######################

  Florian Dupeyron (floolfy)
  September 2018

"""

import script.target as target

def add_deps( ss, dep ):
    """
    Adds dependency rule to dict ss. Value is a tuple containing
    a list of dependency file names, and the proper target rule.
    If dep is a string, no rule is added. is actually a postfix
    tree walk.
    """
    if isinstance( dep, target.Target ):
        if ( dep.name in ss ) and not ( dep is ss[dep.name][0] ):
            print( repr(dep) )
            print( repr(ss[dep.name] ) )
            raise RuntimeError( "Duplicate entry : " + dep.name )

        #########################################
        # TODO # More explicit var names

        depnames = ""
        for ch in dep.deps :
            depnames += str(ch) + " "
            add_deps( ss, ch )

        ss[ dep.name ] = (dep, depnames)

def rules( fhandle, target_list ):
    if not isinstance( target_list, list ):
        raise TypeError("Must be list of targets")

    # Step 1 # Constructing set of targets
    ss = dict()
    for tt in target_list : add_deps( ss, tt )

    # Step 2 # Printing rules
    for rr, dnames in ss.values():
        #print( "build {name} : {rule} {depnames}".format(
        #    name     = str( rr ),
        #    rule     = rr.rule,
        #    depnames = dnames
        #), file=fhandle )
        #print( rr.gen_rule( rr, str(rr), rr.rule, dnames ), file=fhandle )
        print( "build {name} : {rule} {deps}".format( name = str(rr), rule = rr.rule, deps = dnames),file=fhandle)
        for k, v in rr.vars.items():
            print( "    {} = {}".format(k,v), file=fhandle)
        for aa in rr.aliases:
            print( "build {alias} : phony {name}".format( alias =aa, name = str(rr) ), file=fhandle )
        print("",file=fhandle)
