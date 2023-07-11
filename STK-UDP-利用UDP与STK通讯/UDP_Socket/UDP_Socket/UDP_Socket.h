
CWinThread* thread_server;

WSADATA wsa;
SOCKET serverSocket;
struct sockaddr_in* serverAddr;
int AddrLen;

char* CMD;
int CMDLen;

char* timebuf;
char** processControl;

time_t StartTime_second;
struct tm CurrentTime_calendar;