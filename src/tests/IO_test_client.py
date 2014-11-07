import socket

sock = socket.socket()
sock.connect(('localhost', 7777))

sock.send(b'\xF0')
print(sock.recv(1))

while True:
	str = input().encode('utf-8')

	if(str == b'exit'): break

	str_len = len(str)
	# str_len = 512

	sock.send(b'\x03')
	sock.send(chr(int(str_len % 256)).encode('utf-8'))
	sock.send(chr(int(str_len / 256)).encode('utf-8'))
	sock.send(str)

	print("New message:")

	print("\tType: " + sock.recv(1).decode('utf-8'))

	size = sock.recv(2)
	size = bytearray(size)
	size = size[0] + size[1] * 256
	print("\tSize: " + repr(size))

	print("\tData: " + sock.recv(size).decode('utf-8'))

sock.close()