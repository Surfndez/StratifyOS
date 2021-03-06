/* Copyright 2011-2018 Tyler Gilbert; 
 * This file is part of Stratify OS.
 *
 * Stratify OS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Stratify OS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Stratify OS.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * 
 */

/*! \addtogroup pthread
 * @{
 *
 */

/*! \file */

#include "config.h"

#include <pthread.h>
#include <errno.h>

#include "cortexm/task.h"
#include "../scheduler/scheduler_flags.h"

typedef struct {
	int tid;
	int cancel;
	int enable;
	int asynchronous;
	int old_state;
	int old_type;
} svcall_cancel_update_t;

void svcall_cancel_update(void * args){
	CORTEXM_SVCALL_ENTER();
	svcall_cancel_update_t * p = args;
	int tid = p->tid;

	if( scheduler_cancel_asynchronous_asserted(tid) ){
		p->old_type = PTHREAD_CANCEL_ASYNCHRONOUS;
	} else {
		p->old_type = PTHREAD_CANCEL_DEFERRED;
	}

	if( scheduler_cancel_enable_asserted(tid) ){
		p->old_state = PTHREAD_CANCEL_ENABLE;
	} else {
		p->old_state = PTHREAD_CANCEL_DISABLE;
	}

	if( p->cancel > 0 ){
		scheduler_root_assert_cancel(tid);
	} else if( p->cancel < 0 ){
		scheduler_root_deassert_cancel(tid);
	}

	if( p->enable > 0 ){
		scheduler_root_assert_cancel_enable(tid);
	} else if( p->enable < 0 ){
		scheduler_root_deassert_cancel_enable(tid);
	}

	if( p->asynchronous > 0 ){
		scheduler_root_assert_cancel_asynchronous(tid);
	} else if( p->asynchronous < 0 ){
		scheduler_root_deassert_cancel_asynchronous(tid);
	}
}


/*! \details This function is not supported.
 * \return -1 with errno equal to ENOTSUP
 */
int pthread_cancel(pthread_t thread){
	int pid = task_get_pid( task_get_current() );
	int thread_pid = task_get_pid( thread );

	if( ((u8)thread >= task_get_total()) ||
		 (pid != thread_pid) ||
			thread == task_get_thread_zero( pid ) ||
			(task_enabled(thread) == 0)
			){
		errno = ESRCH;
		return -1;
	}

	svcall_cancel_update_t update = {0};
	update.tid = thread;

	return -1;
}

/*! \details This function is not supported.
 * \return -1 with errno equal to ENOTSUP
 */
int pthread_setcancelstate(int state, int *oldstate){
	//PTHREAD_CANCEL_ENABLE or PTHREAD_CANCEL_DISABLE
	svcall_cancel_update_t update = {0};
	update.tid = task_get_current();
	if( state == PTHREAD_CANCEL_ENABLE ){
		update.cancel = 1;
	} else if( state == PTHREAD_CANCEL_DISABLE ){
		update.cancel = -1;
	} else {
		errno = EINVAL;
		return -1;
	}
	cortexm_svcall(svcall_cancel_update, &update);

	if( oldstate != 0 ){
		*oldstate = update.old_state;
	}
	return 0;
}

/*! \details This function is not supported.
 * \return -1 with errno equal to ENOTSUP
 */
int pthread_setcanceltype(int type, int *oldtype){
	//PTHREAD_CANCEL_DEFERRED or PTHREAD_CANCEL_ASYNCHRONOUS
	svcall_cancel_update_t update = {0};
	update.tid = task_get_current();
	if( type == PTHREAD_CANCEL_ASYNCHRONOUS ){
		update.asynchronous = 1;
	} else if( type == PTHREAD_CANCEL_DEFERRED ){
		update.asynchronous = -1;
	} else {
		errno = EINVAL;
		return -1;
	}

	cortexm_svcall(svcall_cancel_update, &update);
	if( oldtype != 0 ){
		*oldtype = update.old_type;
	}

	return 0;
}

void pthread_testcancel(){
	if( scheduler_cancel_enable_asserted(task_get_current()) &&
		 scheduler_cancel_asserted(task_get_current()) ){

		//cleanup the thread

	}
}

/*! @} */

