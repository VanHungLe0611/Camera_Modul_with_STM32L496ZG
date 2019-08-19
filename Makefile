.PHONY: all clean install debugBuild releaseBuild
default:all
all:
debug_build:
		scons -j4 debug=g3
release_build:
		scons -j4 release=1
clean:
		scons -c
rtags:
		scons -j4 debug=g3 nocomstrings=0
install:		
		scons install
