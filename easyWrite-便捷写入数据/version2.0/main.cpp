#include "easyWrite.h"

int main()
{
    bool table_header = true; //是否创建数据表头

	easyWrite ew("数据.csv",table_header,50);// 创建一个 easyWrite 对象，指定文件名和是否写入表头，设定记录步长（物理时间，毫秒）
    
    //数据
    int a = 0;
    double b = 0;
    bool c = true;

    if (table_header) {

        //数据表头
		const char* str_a = "年龄";
		const char* str_b = "身高";
		const char* str_c = "是否在校";

		ew << &a << str_a << &b << str_b << &c << str_c; // 将数据地址与对应表头依次存入easyWrite类中，只执行一次即可，方便easyWrite下次访问并存储数据 
    }
    else {
		ew << &a << &b << &c ; // 将数据地址存入easyWrite类中，只执行一次即可，方便easyWrite下次访问并存储数据 
    }

    ew.startWrite(); //开始数据记录
    //进入仿真循环
    for (int i = 0; i < 1000; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        a += 1;
        b += 0.1;
        c = !c;
    }
    ew.stopWrite();//结束数据记录

    return 0;
}
