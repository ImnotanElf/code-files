#! /usr/bin/python
from ctypes import *
from threading import Thread 
import time 
def my_counter(): 
    i = 0 
    for _ in range( 1_0000_0000 ): 
        i = i + 1 
    return True 
def main():
    libhello = cdll.LoadLibrary( './compile-dylib/build/lib/libhello.dylib' )
    thread_array = {} 
    start_time = time.time() 
    for tid in range( 2 ): 
        t = Thread( target = libhello.HelloFunc ) 
        t.start() 
        thread_array[ tid ] = t 
    for i in range( 2 ): 
        thread_array[ i ].join() 
    end_time = time.time() 
    print( "Total time: {}".format( end_time - start_time ) ) 
if __name__ == '__main__': 
    main()