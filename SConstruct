############################################################### 
# Ad-hoc Networks GmbH										  #
# Author : Michael Ebert									  #
###############################################################

import os
import sys
import subprocess

print("----------------------------------------------------------------")
print("| Compiling mv-cube-camera-------------------------------------|")
print("----------------------------------------------------------------")

buildDirDebug = '#/build/debug'
buildDirRelease = '#/build/release'
buildDirTest = '#/build/test'
buildDirs = [buildDirDebug, buildDirRelease, buildDirTest] 
buildDir = 'build/'

# object files paths
objs = []
# toolchain

include_dirs = [
     # Third party
    '#Drivers/CMSIS/Include/',
    '#Drivers/CMSIS/Device/ST/STM32L4xx/Include/',
    '#Drivers/STM32L4xx_HAL_Driver/Inc/',
    '#Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/',
     # local
    '#Inc/',
    '#SEGGER/RTT/',
]

src_folders =  [
    'Drivers',
    'Src',
    'SEGGER'
]

bin_utils = {
     'AR'      : 'arm-none-eabi-ar',
     'AS'      : 'arm-none-eabi-as',
     'CC'      : 'arm-none-eabi-gcc',
     'CXX'     : 'arm-none-eabi-g++',
     'LINK'    : 'arm-none-eabi-g++',
     'RANLIB'  : 'arm-none-eabi-ranlib'  ,
     'OBJCOPY' : 'arm-none-eabi-objcopy' ,
     'SIZE'    : 'arm-none-eabi-size'
 }
#CCFLAGS
#General options that are passed to the C and C++ compilers
ccflags = [
    '-mcpu=cortex-m4'          , '-mthumb'          , '-O0'                , '-mno-unaligned-access',
    '-fno-move-loop-invariants', '-fsigned-char'    , '-ffunction-sections', '-fdata-sections'      ,
    '-fmessage-length=0'       , '-mfpu=fpv4-sp-d16', '-mfloat-abi=softfp' , '-w'                   ,
    '-Wextra'                ]

#General options that are passed to the C compiler (C only; not C++).
cflags = [ '-std=gnu11']

# linker flags
linkflags = [
    '-mcpu=cortex-m4'     , '-mthumb'         , '-TSTM32L496ZGTx_FLASH.ld' , '-fsigned-char'        ,
    '-ffunction-sections' , '-fdata-sections' , '-fmessage-length=0'       , '-mfpu=fpv4-sp-d16'    ,
    '-mfloat-abi=softfp'  , '-Xlinker'        , '--gc-sections'            , '--specs=nosys.specs'
    ]

#General options that are passed to the C++ compiler
cxxflags = [
    '-fno-use-cxa-atexit',
	'-fno-rtti',
	'-fno-exceptions',
	'-fno-threadsafe-statics',
    '-std=gnu++11',
    ]
#general mixed c assembler options
asppflags = [ '-mcpu=cortex-m4']
#User-specified C preprocessor options
cppdefines = [ 'USE_HAL_DRIVER', 'STM32L496xx', 'HSE_VALUE=8000000',  'USE_FULL_LL_DRIVER']

############################################################### 
# Setup Build Environment									  #
###############################################################
env = Environment(ENV = os.environ, tools = ['mingw'], exports='env')
env['Environment'] = "productive"
Export('env')

############################################################### 
# Compiler Improvements  									  #
###############################################################
# https://stackoverflow.com/questions/1318863/how-to-optimize-the-startup-time-of-an-scons-script
#env.Decider('MD5-timestamp')
#env.SetOption('implicit_cache', 1)
#env.SetOption('num_jobs', 4)
###############################################################

print ('Info : Python version', sys.version_info)
if 'debug' in ARGUMENTS:
	debugLevel = ARGUMENTS.get('debug', 'g3')
	print ('Info : Building Debug with debug level:', debugLevel)
	env.Append(CCFLAGS = '-'+ debugLevel)
	env.Append(CPPDEFINES = 'DEBUG')
	env.Append(CPPDEFINES = 'OS_USE_TRACE_SEMIHOSTING_DEBUG')
	env.Append(CPPDEFINES = 'TRACE')
	buildDir = buildDirDebug
elif 'release' in ARGUMENTS:
	print ('Info : Building Release')
	env.Append(CPPDEFINES = 'RELEASE')
	buildDir = buildDirRelease
elif 'testScons' in ARGUMENTS:
	print ('Info : Building Test')
	env.Append(CCFLAGS = '-g3')
	env.Append(CPPDEFINES = 'TEST')
	buildDir = buildDirTest	
else:
	print ('Info : Building Release')
	env.Append(CPPDEFINES = 'RELEASE')
	buildDir = buildDirRelease



###### configure bin_utils ######
for key in bin_utils.keys():
    env[key] = bin_utils[key]
###### end configure bin_utils ######

env['PROGSUFFIX'] = '.elf'
env['BUILD_ROOT'] = Dir('.');


###### add include_dirs ######
#for directory in include_dirs:
    #if not os.path.exists(directory):
        #print("file not found: " + directory)
    ##env.Append(CCFLAGS ='-I' + directory)
    #env.Append(CPPPATH= " " + directory + " ")
env.Append(CPPPATH=include_dirs)
###### end add include_dirs ######



############################################################################################# 
# Scons Scripts 											                                #
#############################################################################################
# Information for Sconstript function														#
# variant_dir defines the folder where the build artifacts should be placed					#
# duplicate=0 means that the source files from the source folder should be used to compile. # 
# Normally the files are copied to the variant dir.											#					
#############################################################################################

###### add src folders ######
for folder in list(set(src_folders)): # avoid duplicates
    sconscript_name = folder + '/SConscript'
    if not os.path.exists(folder):
        print("directory not found: " + folder)
    if not os.path.exists(sconscript_name):
        print("file not found: " + sconscript_name)
    else:
        o = SConscript('#/' + sconscript_name, variant_dir=buildDir  + '/' + folder, duplicate = 0)
        objs.append(o)
objs.append(env.Object('startup_stm32l496xx.s'))
###### end add src folders ######


###############################################################
#Settings default values 

############################################################### 
# Generate Include Dirs										  #
###############################################################
#def generate_include_dirs(self):
    #"""docstring for generate_include_dir"""
    #path_config = '#config/'
    #path_user_config = '#config/mv_user_config/'
    #incl_dirs = [ '#'+ x[0] for x in os.walk(os.path.normpath(path_lib))]
    #incl_dirs.append(path_config)
    #incl_dirs.append(path_seq)

    #for indx, s in enumerate(incl_dirs):
       #replacePath = s.replace('\\', '/')
       #incl_dirs[indx] = replacePath
    #env.Append(CPPPATH = incl_dirs)

#To improve performance the static dependencies are added to the CCFLAGS. 
#So that these headers are excluded from the scons cpppath dependecy check

############################################################### 
# Compiler flags											  #
###############################################################
#CCFLAGS General options that are passed to the C and C++ compilers
env.Append(CCFLAGS = ccflags)
#CFLAGS General options that are passed to the C compiler (C only; not C++).
env.Append(CFLAGS = cflags)
#CXXFLAGS General options that are passed to the C++ compiler
env.Append(CXXFLAGS = cxxflags)
# linker flags
env.Append(LINKFLAGS = linkflags)
#CPPFLAGS User-specified C preprocessor options
env.Append(CPPDEFINES = cppdefines)

env.Append(ASPPFLAGS = asppflags)

############################################################### 
# Linking       											  #
###############################################################

# binary file builder
def arm_generator(source, target, env, for_signature):
	return '$OBJCOPY -O binary %s %s'%(source[0], target[0])


env.Append(BUILDERS = {
    'Objcopy': Builder(
        generator=arm_generator,
        suffix='.bin',
        src_suffix='.elf'
    )
})

prg = env.Program(
    target = buildDir +'/target',
    source = objs
)


targetFile = env.Objcopy(prg)

############################################################### 
# Post Actions												  #
###############################################################

env.AddPostAction(prg, 'arm-none-eabi-size --format=SysV '+buildDir[2:]+'/target.elf')

############################################################### 
# Clean														  #
###############################################################
env.Clean(targetFile, buildDirs)


############################################################### 
# Prevent Win32 Linking Problem 							  #
###############################################################
# Command Line too long bug of Win32
# https://github.com/SCons/scons/wiki/LongCmdLinesOnWin32

class ourSpawn:
    def ourspawn(self, sh, escape, cmd, args, env):
        newargs = ' '.join(args[1:])
        cmdline = cmd + " " + newargs
        startupinfo = subprocess.STARTUPINFO()
        #startupinfo.dwFlags |= subprocess.STARTF_USESHOWWINDOW
        proc = subprocess.Popen(cmdline, stdin=subprocess.PIPE, stdout=subprocess.PIPE,
            stderr=subprocess.PIPE, startupinfo=startupinfo, shell = False, env = env)
        data, err = proc.communicate()
        rv = proc.wait()
        if rv:
            print ("=====")
            print (err)
            print ("=====")
        return rv

def SetupSpawn( env ):
    if sys.platform == 'win32':
        buf = ourSpawn()
        buf.ourenv = env
        env['SPAWN'] = buf.ourspawn

SetupSpawn(env)
