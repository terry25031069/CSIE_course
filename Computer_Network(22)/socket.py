import socket, sys
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print ('Socket Created!')
host = '120.126.151.101'
s.connect((host, 8080))

try:
    data = {"StuId": "410785008 BlueWhite"}
    request1 = b"GET /get HTTP/1.1\n\n"
    request2 = b'POST /post HTTP/1.1\nBody:{"StuId":"410785008 BlueWhite"}\n\n'
    s.sendall(request2)
    resp = s.recv(1024)
    http_resp = repr(resp)
    print(http_resp)
except socket.error:
    print ('Send failed')
    sys.exit()
print('Message send successfully')
