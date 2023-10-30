
all: server client
	@echo "[+] Build Complete"

server: server.cpp  socket.cpp
	@g++ server.cpp -o server

client: client.cpp socket.cpp
	@g++ client.cpp -o client

clean:
	@rm -rf server client
	@echo "Done!"


