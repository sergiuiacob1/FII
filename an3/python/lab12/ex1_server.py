import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(("127.0.0.1", 1234))
s.listen(1)

(connection, address) = s.accept()
print("Connectd address:", address)
suma = 0
try:
    while True:
        data = connection.recv(10).decode("UTF-8")
        print (f'Received data: {data}')
        numbers = data.split('|')
        if len(numbers) > 0:
            numbers = [int(x) for x in data.split('|') if x is not '.' and len(x) > 0]
        suma += sum(numbers)
        if '.' in data:
            break
finally:
    print(f'The sum is {suma}')
    connection.close()
    print("Server closed")
