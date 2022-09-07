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
    libtest = cdll.LoadLibrary( './libtest.so' )
    libexample = cdll.LoadLibrary( './libexample.so' )
    thread_array = {} 
    start_time = time.time() 
    for tid in range( 2 ): 
        t = Thread( target = libexample.test ) 
        t.start() 
        t.join() 
    end_time = time.time() 
    print( "Total time: {}".format( end_time - start_time ) ) 
    
if __name__ == '__main__': 
    main()