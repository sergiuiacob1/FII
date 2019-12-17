import os
import hashlib
import time
import threading

def test1():
    print ('started')
    for i in range (0, 10):
        time.sleep(1)
        yield str(i) + '-1'

def test2():
    for i in range (0, 10):
        time.sleep(1)
        yield str(i) + '-2'

t = threading.Thread(target=test1)
t.start()
res = t.join()
print (res)


# def ex10(path):
#     _, _, files =os.listdir(path)

# ex10('.')