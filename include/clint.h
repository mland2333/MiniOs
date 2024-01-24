#define CLINT 0x2000000L

//寄存器，上电时恢复为0,全局为1,且为64bit
#define CLINT_MTIME (CLINT + 0xbff8)

//定时器比较值，自己设初值,mtime>=mtimecmp时，产生中断
#define CLINT_MTIMECMP(hartid) (CLINT + 0x4000 +(hartid)*8)

#define TIME_INTERVAL 10000000
