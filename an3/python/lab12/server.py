import socket
import threading
import ast

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(('127.0.0.1', 1234))
s.listen(1)


def handle_client(connection, address):
    print("Connectd address:", address)
    total_data = ''
    while True:
        data = connection.recv(10).decode("UTF-8")
        print(f'Received data: {data}')
        if not data:
            break
        total_data += data
        if data.endswith('{{}}'):
            total_data = total_data[:-4]
            break

    d, cheie = total_data.rsplit('}')
    d += '}'
    d = ast.literal_eval(d)
    print(f'The dictionary is: {d}')
    print(f'The key is: {cheie}')
    if cheie in d:
        connection.send(str(d[cheie]).encode("UTF-8"))
    else:
        connection.send(b'Key not found in dictionary')

    print('Connection done\n')
    connection.close()


while True:
    (connection, address) = s.accept()
    t = threading.Thread(target=handle_client, args=(connection, address))
    t.start()
