#include "DSver.h"
#include <windows.h>

//���������߳�
DWORD WINAPI thread_send(LPVOID LpParamter) {
	//��ʼ������IP���˿ڡ�һ���Խ������ݵ��ֽڳ��ȡ��趨Ϊ���ݷ���
	DSver ds("127.0.0.1", 30002, sizeof(double) * 3, SEND_DATA);
	double data_send[3];
	data_send[0] = 1;
	data_send[1] = 2;
	data_send[2] = 3;
	while (true) {
		ds.data_send((void*)data_send);
	}
}

//���������߳�
DWORD WINAPI thread_recv(LPVOID LpParamter) {
	//��ʼ������IP���˿ڡ�һ���Խ������ݵ��ֽڳ��ȡ��趨Ϊ���ݽ���
	DSver ds("127.0.0.1", 30002, sizeof(double) * 3,RECV_DATA);
	double data_recv[3];
	while (true) {
		if(ds.data_recv((void*)data_recv)==0)
			printf("%lf\t%lf\t%lf\n", data_recv[0], data_recv[1], data_recv[2]);
	}
}

int main() {
	CreateThread(NULL, 0, thread_send, NULL, 0, NULL);
	CreateThread(NULL, 0, thread_recv, NULL, 0, NULL);
	while (true);
}