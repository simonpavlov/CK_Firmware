import socket

sock = socket.socket()
sock.connect(('localhost', 7777))
sock.send('\x03\x0E\x00\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D')

# print sock.recv(1)

sock.close()