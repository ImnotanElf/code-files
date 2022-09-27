#! /usr/bin/python
from ctypes import *
from threading import Thread 
import time

def main():
    libhello = cdll.LoadLibrary( './compile-dylib/build/lib/libhello.dylib' )
    libgdal = cdll.LoadLibrary( '/Users/xsl/Desktop/code-files/CMake/test/gdal-test/build/libgdal-test.dylib' )
    print( type( libhello ) )
    thread_array = {} 
    start_time = time.time() 
    for tid in range( 2 ): 
        t = Thread( target = libgdal.print_line ) 
        t.start() 
        t.join() 
    end_time = time.time() 
    print( "Total time: {}".format( end_time - start_time ) ) 

if __name__ == '__main__': 
    main()