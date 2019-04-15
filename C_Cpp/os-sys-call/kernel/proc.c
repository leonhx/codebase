
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                               proc.c
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                                    Forrest Yu, 2005
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "type.h"
#include "const.h"
#include "protect.h"
#include "proto.h"
#include "string.h"
#include "proc.h"
#include "global.h"

/*======================================================================*
                              schedule
 *======================================================================*/
PUBLIC void schedule()
{
	PROCESS* p;

	for (p = proc_table; p < proc_table+NR_TASKS; p++) {
		if (p->blocked_by != NULL) {
			if (p->blocked_by->value > 0) {
				p->blocked_by = NULL;
			}
		}
	}

	int	 greatest_ticks = 0;

	while (!greatest_ticks) {
		for (p = proc_table; p < proc_table+NR_TASKS; p++) {
			if (p->blocked_by == NULL && p->sleep_ticks <= 0 
				&& p->ticks > greatest_ticks) {
				greatest_ticks = p->ticks;
				p_proc_ready = p;
			}
		}

		if (!greatest_ticks) {
			for (p = proc_table; p < proc_table+NR_TASKS; p++) {
				p->ticks = p->priority;
			}
		}
	}
}

/*======================================================================*
                           sys_get_ticks
 *======================================================================*/
PUBLIC int sys_get_ticks()
{
	return ticks;
}

/*======================================================================*
                           sys_disp_str
 *======================================================================*/
PUBLIC void sys_disp_str(char* str)
{
	k_disp_str(str);
}

/*======================================================================*
                           sys_process_sleep
 *======================================================================*/
PUBLIC void sys_process_sleep(int mill_seconds)
{
	p_proc_ready->sleep_ticks = mill_seconds * HZ / 1000;
	schedule();
}

/*======================================================================*
                           sys_sem_p
 *======================================================================*/
PUBLIC void sys_sem_p(sem_t *s) {
	if (s->value <= 0) {
		p_proc_ready->blocked_by = s;
		schedule();
	} else {
		s->value --;
	}
}

/*======================================================================*
                           sys_sem_v
 *======================================================================*/
PUBLIC void sys_sem_v(sem_t *s) {
	s->value ++;
}
