// UDP_Socket.cpp : �������̨Ӧ�ó������ڵ㡣
//������Ҫ���ws2_32.lib��

#include "stdafx.h"
#include "afxwin.h"
#include "defination.h" //�궨��ͷ�ļ�
#include "UDP_Socket.h" //ȫ�ֱ�������ͷ�ļ�
#pragma comment(lib, "ws2_32.lib")//����socket����lib��

//��ȡ��N֡����ʱ��
void GetTime(char* timebuf, int N){

	time_t CurrentTime_second;
	CurrentTime_second = StartTime_second + N * 5;
	localtime_s(&CurrentTime_calendar, &CurrentTime_second);
	strftime(timebuf, 128, "%d %b %Y %H:%M:%S", &CurrentTime_calendar);

}

//�����ʼ��
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

	//��ʼ��dll�ļ�
	WSAStartup(WINSOCK_VERSION, &wsa);

	//����--��ַ�ṹ�����ݳ���
	AddrLen = sizeof(sockaddr);

	//����SOCKET����Ӧ��ַ�ṹ��

	serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
	serverAddr = (sockaddr_in*)malloc(sizeof(sockaddr_in));

	//��������������͵ĵ�ַ�ṹ��
	memset(serverAddr, 0, sizeof(sockaddr_in));
	serverAddr->sin_family = AF_INET;
	serverAddr->sin_port = htons(13);
	serverAddr->sin_addr.S_un.S_addr = inet_addr("192.168.1.169");
}

//�������
void STKend(){
	free(timebuf);
	free(CMD);
	free(serverAddr);
}

//���岢��ʼ���������
void objectSet(char *objectName,double objectLng, double objectLat, double objectHgt){
	memset(CMD,0,256);
	sprintf_s(CMD, 256,"New / */Missile %s",objectName);
	CMDLen = strlen(CMD);
	sendto(serverSocket, (char*)&CMDLen, sizeof(int), 0, (sockaddr*)serverAddr, AddrLen);
	sendto(serverSocket, CMD, CMDLen, 0, (sockaddr*)serverAddr, AddrLen);
	//�Ƿ���Ҫ����ȴ�
	memset(CMD, 0, 256);
	sprintf_s(CMD, 256, "SetPosition */Missile/%s LLA \" 1 Oct 2000 00:00:00.00 \" %.2lf %.2lf %.2lf", \
		objectName,objectLng,objectLat,objectHgt);
	CMDLen = strlen(CMD);
	sendto(serverSocket, (char*)&CMDLen, sizeof(int), 0, (sockaddr*)serverAddr, AddrLen);
	sendto(serverSocket, CMD, CMDLen, 0, (sockaddr*)serverAddr, AddrLen);
}

//�趨�������ʱ�̾�γ��
void pointSet(char *objectName, double objectLng, double objectLat, double objectHgt,int N){
	GetTime(timebuf, N);
	memset(CMD,0,256);
	sprintf_s(CMD, 256, "SetPosition */Missile/%s LLA \" %s \" %.2lf %.2lf %.2lf", \
		objectName, timebuf, objectLng, objectLat, objectHgt);
	CMDLen = strlen(CMD);
	sendto(serverSocket, (char*)&CMDLen, sizeof(int), 0, (sockaddr*)serverAddr, AddrLen);
	sendto(serverSocket, CMD, CMDLen, 0, (sockaddr*)serverAddr, AddrLen);
}

//��Զ��STK Engine��������
void SendCmd(char* cmd){
	memset(CMD, 0, 256);
	sprintf_s(CMD, 256, cmd);
	CMDLen = strlen(CMD);
	sendto(serverSocket, (char*)&CMDLen, sizeof(int), 0, (sockaddr*)serverAddr, AddrLen);
	sendto(serverSocket, CMD, CMDLen, 0, (sockaddr*)serverAddr, AddrLen);
}

//�Է������ʵʱ���̿���
void STKanimate(int animate_Macro){
	memset(CMD, 0, 256);
	sprintf_s(CMD, 256, *(processControl + animate_Macro));
	CMDLen = strlen(CMD);
	sendto(serverSocket, (char*)&CMDLen, sizeof(int), 0, (sockaddr*)serverAddr, AddrLen);
	sendto(serverSocket, CMD, CMDLen, 0, (sockaddr*)serverAddr, AddrLen);
}

//������
int _tmain(int argc, _TCHAR* argv[])
{
	STKinitiate();

	//��������
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