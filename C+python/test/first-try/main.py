from ctypes import *
from threading import Thread

lib = cdll.LoadLibrary( "./libtest.so" )

t = Thread( target = lib.test )
t.start()

# while True:
    # lib.sleep_time( 1 )