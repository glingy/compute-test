Import("env")

#
# Dump build environment (for debug)
# print(env.Dump())
#



#if env.GetBuildType() != "debug":
#  env.Append(
#    LINKFLAGS=[
#      "-flto",
#      "-flto-report",
#      "-fuse-linker-plugin",
#      "-nostartfiles",
#    ]
#  )

#import os
#Import("env")

# Build the test project
#env.Execute("pio run -d test")