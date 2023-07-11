#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<winsock2.h>
#include<Ws2tcpip.h>

#define SEND_DATA 1
#define RECV_DATA 0

#pragma comment(lib,"ws2_32.lib")

using namespace std;

class DSver {
public:
	DSver(string IP,int port,int data_length,int send_or_recv);
	DSver();
	~DSver();
	int recv_ini();
	int send_ini();
	int data_recv(void* p);
	int data_send(void* p);
	void set_port(int port);
	int get_port();
	void set_IP(string IP);
	string get_IP();
	void set_len(int length);
	int get_len();
private:
	int port;
	string IP;
	WSADATA wsaData;
	int length;
	SOCKET sock_tar;
	SOCKET sock_src;
	bool send_ini_ok,recv_ini_ok;
};