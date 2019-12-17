import socket


d = {
    'a': 1234,
    'b': 'hello how are youuuuuuu'
}

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(("127.0.0.1", 1234))

s.send(str(d).encode("UTF-8"))
s.send(b'b')
s.send(b'{{}}')

res = ''
while True:
    data = s.recv(1).decode("UTF-8")
    if not data:
        break
    res += data

print(res)
