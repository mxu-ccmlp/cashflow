from setuptools import setup, Extension,SetuptoolsDeprecationWarning
import warnings
warnings.filterwarnings("ignore", category=SetuptoolsDeprecationWarning) 
import numpy,os,sys,shutil,glob
def get_version():
    #look through all version.c files in the subdirectories and adding the version number digit by digit
    ver = ""
    with open("cffuncs\\cpp\\version.h", 'r') as version_file:
        line = version_file.read().strip().split('\n')[0]
        ver = line.split(' ')[-1].strip("\"")
    return ver
if '--force' in sys.argv:
    print("cleaning build folder.")
    builddir = 'build'
    if os.path.exists(builddir):
        shutil.rmtree(builddir)
    os.makedirs(builddir)
#check operating system
if '--debug' in sys.argv:
    print("++++++++++++++++Debug Mode++++++++++++++++")
    extraargs = {}
else:
    if os.name == 'nt':
        #extra_compile_args = ['/O2', '/arch:AVX2', '/fp:fast']
        print("++++++++++++++++Optimize for Windows++++++++++++++++")
        #extra_compile_args=['/O2', "/Oi", '/GL', '/Ot', '/arch:AVX2', '/fp:fast']
        extra_compile_args=['/FC', '/EHsc','/Zc:forScope','/Gd','/Zi','/Gm-','/sdl','/Zc:inline', '/WX-','/GS','/W3','/Gy','/Zc:wchar_t','/permissive-','/GL','/Oi','/O2','/fp:precise']#   
        extra_link_args=['/LTCG','/NXCOMPAT','/MACHINE:X64','/OPT:REF','/INCREMENTAL:NO','/OPT:ICF']
        extraargs = {"extra_compile_args":extra_compile_args,"extra_link_args":extra_link_args}
    elif os.name == 'posix':
        print("-----------------------Optimize for Linux-----------------------")
        extraargs = {}
extension_module = Extension(
    "cffuncs",  # Name of the compiled extension module
    sources=["cffuncs/cpp/model.cpp"],#, "ccmcalc/ccmcalc.h"
    include_dirs=[numpy.get_include()],  # Include directory
    depends=["cffuncs/cpp/impls.hpp","cffuncs/cpp/version.h","cffuncs/cpp/funcs.hpp"
             ], #,"nonqm/carvana_sp_model.h","nonqm/carvana_sp_data.h"
    **extraargs
)
versionstr = get_version()

setup(
    name="cffuncs",
    packages=["cffuncs"],
    setup_requires=["numpy"],
    ext_modules=[extension_module],
    version=versionstr,
)