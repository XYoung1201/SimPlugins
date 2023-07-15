#include "easyWrite.h"

int main()
{
    bool table_header = true; //是否创建数据表头

	easyWrite ew("数据.csv",table_header);// 创建一个 easyWrite 对象，指定文件名和是否写入表头
    
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

    //进入仿真循环
    for (int i = 0; i < 1000; i++) {
		ew.write(); // 再次将数据写入文件，无需重新添加数据和数据名称
        a += 1;
        b += 0.1;
        c = !c;
    }

    return 0;
}
