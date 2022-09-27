from ctypes import *
from re import A
import sys

def main():
    libdal_test_path = "/Users/xsl/Desktop/code-files/C+python/test/gdal-test/dylib/build/libgdal-test.dylib"
    libgdal_test = cdll.LoadLibrary( libdal_test_path )
    read_txt = libgdal_test.read_txt
    read_txt.argtypes = ( c_char_p, )
    read_txt.restype  = c_char_p
    file_path = b"/Users/xsl/Desktop/code-files/C+python/test/gdal-test/test.txt"
    fp = c_char_p( file_path )
    res = read_txt( fp )
    print( "res: ", res )

if __name__ == "__main__":
    main()