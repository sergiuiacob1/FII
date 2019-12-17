import socket
import time

lista = [1, 2, 3, 4, 5, 6]

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(("127.0.0.1", 1234))

for x in lista:
    s.send(str(x).encode("UTF-8"))
    s.send(b'|')
s.send(b'.')

s.close()
