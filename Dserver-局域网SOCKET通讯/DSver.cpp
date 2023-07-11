#include "DSver.h"

DSver::DSver() {
	port = 0;
	IP = "";
	send_ini_ok = false;
	recv_ini_ok = false;
}
DSver::~DSver() {
	closesocket(sock_tar);
	closesocket(sock_src);
	WSACleanup();
}
DSver::DSver(string IP, int port,int data_length,int send_or_recv) {
	send_ini_ok = false;
	recv_ini_ok = false;
	set_port(port);
	set_IP(IP);
	set_len(data_length);
	if (send_or_recv == SEND_DATA) {
		send_ini();
	}
	if (send_or_recv == RECV_DATA) {
		recv_ini();
	}
}
void DSver::set_len(int length) {
	this->length = length;
}

int DSver::get_len() {
	return length;
}

void DSver::set_IP(string IP) {
	this->IP = IP;
}
void DSver::set_port(int port) {
	this->port = port;
}
string DSver::get_IP() {
	return IP;
}
int DSver::get_port() {
	return port;
}
int DSver::recv_ini() {
	if (send_ini_ok) {
		return -1;
	}
	else {
		recv_ini_ok = true;
	}
	if (port == 0 || IP == "") {
		return -1;
	}
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		return -1;
	}

	sock_src = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_src == SOCKET_ERROR) {
		return -1;
	}

	SOCKADDR_IN addrSrv;
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(port);
	addrSrv.sin_addr.S_un.S_addr = inet_addr(IP.c_str());
	
	if (bind(sock_src, (LPSOCKADDR)&addrSrv, sizeof(SOCKADDR_IN)) == SOCKET_ERROR) {
		return -1;
	}
	if (listen(sock_src, 10) == SOCKET_ERROR) {
		return -1;
	}
	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR);
	sock_tar = accept(sock_src,(SOCKADDR *)&addrClient,&len);
	if (sock_tar == SOCKET_ERROR) {
		return -1;
	}
	return 0;
}
int DSver::send_ini() {
	if (recv_ini_ok) {
		return -1;
	}
	else {
		send_ini_ok = true;
	}
	if (port == 0 || IP == "") {
		return -1;
	}
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		return -1;
	}
	sock_tar = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_tar == SOCKET_ERROR) {
		return -1;
	}

	SOCKADDR_IN addrSrv;
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(port);
	addrSrv.sin_addr.S_un.S_addr = inet_addr(IP.c_str());

	if (connect(sock_tar, (struct sockaddr*)&addrSrv, sizeof(addrSrv)) == INVALID_SOCKET) {
		return -1;
	}
	return 0;
}
int DSver::data_recv(void* p) {
	if (!(recv_ini_ok || send_ini_ok)) {
		return -1;
	}
	if (recv(sock_tar, (char*)p, length, 0) <= 0) {
		return -1;
	}
	return 0;
}
int DSver::data_send(void* p) {
	if (!(recv_ini_ok || send_ini_ok)) {
		return -1;
	}
	if (send(sock_tar, (char*)p, length, 0) <= 0) {
		return -1;
	}
	return 0;
}