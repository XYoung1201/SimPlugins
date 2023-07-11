// UDP_Socket.cpp : 定义控制台应用程序的入口点。
//连接器要添加ws2_32.lib库

#include "stdafx.h"
#include "afxwin.h"
#include "defination.h" //宏定义头文件
#include "UDP_Socket.h" //全局变量声明头文件
#pragma comment(lib, "ws2_32.lib")//引入socket所需lib库

//获取第N帧仿真时刻
void GetTime(char* timebuf, int N){

	time_t CurrentTime_second;
	CurrentTime_second = StartTime_second + N * 5;
	localtime_s(&CurrentTime_calendar, &CurrentTime_second);
	strftime(timebuf, 128, "%d %b %Y %H:%M:%S", &CurrentTime_calendar);

}

//仿真初始化
void STKinitiate(){

	CMD = (char*)malloc(256);
	timebuf = (char*)malloc(128); 
	processControl = (char**)malloc(6 * sizeof(char*));
	for (int i = 0; i < 6; i++){
		*(processControl + i) = (char*)malloc(sizeof(char)*30);
	}

	strcpy_s(*(processControl + 0), 30, "Animate * Start Forward End");
	strcpy_s(*(processControl + 1), 30, "Animate * Start Reverse End");
	strcpy_s(*(processControl + 2), 30, "Animate * Pause");
	strcpy_s(*(processControl + 3), 30, "Animate * Reset");
	strcpy_s(*(processControl + 4), 30, "Animate * Faster");
	strcpy_s(*(processControl + 5), 30, "Animate * Slower");

	struct tm StartTime_calendar;
	StartTime_calendar.tm_hour = 0;
	StartTime_calendar.tm_min = 0;
	StartTime_calendar.tm_sec = 0;
	StartTime_calendar.tm_mon = 9;
	StartTime_calendar.tm_mday = 1;
	StartTime_calendar.tm_year = 100;
	StartTime_second = mktime(&StartTime_calendar);

	//初始化dll文件
	WSAStartup(WINSOCK_VERSION, &wsa);

	//参数--地址结构体数据长度
	AddrLen = sizeof(sockaddr);

	//创建SOCKET与相应地址结构体

	serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
	serverAddr = (sockaddr_in*)malloc(sizeof(sockaddr_in));

	//设置向服务器发送的地址结构体
	memset(serverAddr, 0, sizeof(sockaddr_in));
	serverAddr->sin_family = AF_INET;
	serverAddr->sin_port = htons(13);
	serverAddr->sin_addr.S_un.S_addr = inet_addr("192.168.1.169");
}

//仿真结束
void STKend(){
	free(timebuf);
	free(CMD);
	free(serverAddr);
}

//定义并初始化仿真对象
void objectSet(char *objectName,double objectLng, double objectLat, double objectHgt){
	memset(CMD,0,256);
	sprintf_s(CMD, 256,"New / */Missile %s",objectName);
	CMDLen = strlen(CMD);
	sendto(serverSocket, (char*)&CMDLen, sizeof(int), 0, (sockaddr*)serverAddr, AddrLen);
	sendto(serverSocket, CMD, CMDLen, 0, (sockaddr*)serverAddr, AddrLen);
	//是否需要加入等待
	memset(CMD, 0, 256);
	sprintf_s(CMD, 256, "SetPosition */Missile/%s LLA \" 1 Oct 2000 00:00:00.00 \" %.2lf %.2lf %.2lf", \
		objectName,objectLng,objectLat,objectHgt);
	CMDLen = strlen(CMD);
	sendto(serverSocket, (char*)&CMDLen, sizeof(int), 0, (sockaddr*)serverAddr, AddrLen);
	sendto(serverSocket, CMD, CMDLen, 0, (sockaddr*)serverAddr, AddrLen);
}

//设定仿真对象时刻经纬高
void pointSet(char *objectName, double objectLng, double objectLat, double objectHgt,int N){
	GetTime(timebuf, N);
	memset(CMD,0,256);
	sprintf_s(CMD, 256, "SetPosition */Missile/%s LLA \" %s \" %.2lf %.2lf %.2lf", \
		objectName, timebuf, objectLng, objectLat, objectHgt);
	CMDLen = strlen(CMD);
	sendto(serverSocket, (char*)&CMDLen, sizeof(int), 0, (sockaddr*)serverAddr, AddrLen);
	sendto(serverSocket, CMD, CMDLen, 0, (sockaddr*)serverAddr, AddrLen);
}

//向远程STK Engine发送命令
void SendCmd(char* cmd){
	memset(CMD, 0, 256);
	sprintf_s(CMD, 256, cmd);
	CMDLen = strlen(CMD);
	sendto(serverSocket, (char*)&CMDLen, sizeof(int), 0, (sockaddr*)serverAddr, AddrLen);
	sendto(serverSocket, CMD, CMDLen, 0, (sockaddr*)serverAddr, AddrLen);
}

//对仿真进行实时流程控制
void STKanimate(int animate_Macro){
	memset(CMD, 0, 256);
	sprintf_s(CMD, 256, *(processControl + animate_Macro));
	CMDLen = strlen(CMD);
	sendto(serverSocket, (char*)&CMDLen, sizeof(int), 0, (sockaddr*)serverAddr, AddrLen);
	sendto(serverSocket, CMD, CMDLen, 0, (sockaddr*)serverAddr, AddrLen);
}

//主程序
int _tmain(int argc, _TCHAR* argv[])
{
	STKinitiate();

	//发送命令
	system("pause");
	STKanimate(ANIMATE_RESET);
	objectSet("missile_1", 15, 15, 0);
	pointSet("missile_1",30,30,5,400);
	pointSet("missile_1",60,60,5,600);
	system("pause");
	while (1){
		STKanimate(ANIMATE_START_FORWARD);
		system("pause");
		STKanimate(ANIMATE_RESET);
	}

	

	STKend();

	return 0;
}