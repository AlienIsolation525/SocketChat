all:
	g++ Client_lin.plat.h Client_win.plat.h Server_lin.plat.h Server_win.plat.h Source.cpp -o SocketChat