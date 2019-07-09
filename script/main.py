import target
import output


libmain = target.lib(
    "libmain",
    srcs = [
        "lib.c"
    ]
)

exe = target.executable(
    "app",
    srcs=[
        "main.c"
    ],
    objs = [ libmain ]
)

output.rules( [exe] )
