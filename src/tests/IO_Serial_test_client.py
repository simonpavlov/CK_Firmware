import socket

sock = socket.socket()
sock.connect(('localhost', 7777))

sock.send(b'\xF0')
print(sock.recv(1))

for str in [b'a' * 3, b'b' * 128, b'c' * 255, b'd' * 256, b'e' * 32768]:

	str_len = len(str)
	str_len = bytearray([((1 << 8) - 1) & (str_len >> (8 * i)) for i in range(0, 4)])
	print(str_len)

	sock.send(b'\x03')
	sock.send(str_len)
	sock.send(str)

	print("New message:")

	print("\tType: " + sock.recv(1).decode('utf-8'))

	size = sock.recv(4)
	size = bytearray(size)
	size = size[0] + size[1] * 256
	print("\tSize: " + repr(size))
	print("\tData: " + sock.recv(size).decode('utf-8'))
	print("\tCrc16: " + sock.recv(2).decode('utf-8'))


sock.close()