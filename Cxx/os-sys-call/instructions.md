1. `include/const.h`中修改`NR_SYS_CALL`的值

2. `include/proto.h`中增加系统调用和对应的处理例程的声明

3. `kernel/global.c`中在系统调用表`sys_call_table`中增加系统调用

4. `kernel/syscall.sam`中增加中断向量、导出符号和处理例程的实现（注意修改`mov eax, _NR_*`）

5. `kernel/proc.c`中增加系统调用的实现
