/*
 * linux/include/asm-i386/timex.h
 *
 * i386 architecture timex specifications
 */
#ifndef _ASMi386_TIMEX_H
#define _ASMi386_TIMEX_H

#include <linux/config.h>
#include <asm/processor.h>

/**
 * 8254芯片的内部振荡频率
 */
#ifdef CONFIG_X86_ELAN
#  define CLOCK_TICK_RATE 1189200 /* AMD Elan has different frequency! */
#else
/**
 * CLOCK_TICK_RATE产生的值为1193182。这是8254芯片的内部振荡频率。
 */
#  define CLOCK_TICK_RATE 1193182 /* Underlying HZ */
#endif


/*
 * Standard way to access the cycle counter on i586+ CPUs.
 * Currently only used on SMP.
 *
 * If you really have a SMP machine with i486 chips or older,
 * compile for that, and this will just always return zero.
 * That's ok, it just means that the nicer scheduling heuristics
 * won't work for you.
 *
 * We only use the low 32 bits, and we'd simply better make sure
 * that we reschedule before that wraps. Scheduling at least every
 * four billion cycles just basically sounds like a good idea,
 * regardless of how fast the machine is. 
 */
typedef unsigned long long cycles_t;

extern cycles_t cacheflush_time;

static inline cycles_t get_cycles (void)
{
	unsigned long long ret=0;

#ifndef CONFIG_X86_TSC
	if (!cpu_has_tsc)
		return 0;
#endif

#if defined(CONFIG_X86_GENERIC) || defined(CONFIG_X86_TSC)
	rdtscll(ret);
#endif
	return ret;
}

extern unsigned long cpu_khz;

#endif
