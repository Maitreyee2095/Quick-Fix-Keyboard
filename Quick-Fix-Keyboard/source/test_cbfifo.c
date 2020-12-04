/*
 * test_cbfifo.c
 *
 *  Created on: Nov 8, 2020
 *      Author: maitr
 */



#include <stdio.h>
#include <assert.h>
#include <stdint.h>

#include "test_cbfifo.h"
#include "Circular_buffer.h"

#define max(x,y) ((x) > (y) ? (x) : (y))
cb_t kCB_TX_FIFO;
static int g_tests_passed = 0;
static int g_tests_total = 0;
static int g_skip_tests = 0;

#define test_assert(value) {                                            \
		g_tests_total++;                                                      \
		if (!g_skip_tests) {                                                  \
			if (value) {                                                        \
				g_tests_passed++;                                                 \
			} else {                                                            \
				printf("ERROR: test failure at line %d\n", __LINE__);             \
				g_skip_tests = 1;                                                 \
			}                                                                   \
		}                                                                     \
}

#define test_equal(value1, value2) {                                    \
		g_tests_total++;                                                      \
		if (!g_skip_tests) {                                                  \
			long res1 = (long)(value1);                                         \
			long res2 = (long)(value2);                                         \
			if (res1 == res2) {                                                 \
				g_tests_passed++;                                                 \
			} else {                                                            \
				printf("ERROR: test failure at line %d: %ld != %ld\n", __LINE__, res1, res2); \
				g_skip_tests = 1;                                                 \
			}                                                                   \
		}                                                                     \
}

static void test_cbfifo_one_iteration()
{
	char *str ="To be, or not to be: that is the question:\n"
			"Whether 'tis nobler in the mind to suffer\n"
			"The slings and arrows of outrageous fortune,\n"
			"Or to take arms against a sea of troubles,\n"
			"And by opposing end them? To die, to sleep--\n"
			"No more--and by a sleep to say we end\n"
			"The heart-ache and the thousand natural shocks\n"
			"That flesh is heir to, 'tis a consummation\n"
			"Devoutly to be wish'd. To die, to sleep;\n"
			"To sleep: perchance to dream: ay, there's the rub;\n"
			"For in that sleep of death what dreams may come\n"
			"When we have shuffled off this mortal coil,\n"
			"Must give us pause.";
	char buf[512];
	char buf2[512];
	cb_init(&kCB_TX_FIFO);
	const int str_len = sizeof(str) / sizeof(const char *);
	const int cap = cb_Size(&kCB_TX_FIFO);
	test_assert(strlen(str) >= cap*2);
	test_assert(sizeof(buf) > cap);
	test_assert(cap == 256);

	test_equal(cb_Length(&kCB_TX_FIFO), 0);
	test_equal(cb_Dequeue(&kCB_TX_FIFO, buf, cap), 0);
	test_equal(cb_Dequeue(&kCB_TX_FIFO, buf, 1), 0);
	test_assert(!cb_Full(&kCB_TX_FIFO));
	// enqueue 10 bytes, then dequeue same amt
	test_equal(cb_Enqueue(&kCB_TX_FIFO, str, 10), 10);
	test_equal(cb_Dequeue(&kCB_TX_FIFO, buf, 10), 10);

	// enqueue all the elements, then dequeue all
	for (int i=0; i<str_len; i++) {
		test_equal(cb_Enqueue(&kCB_TX_FIFO, str+i,i+1), i+1);
		test_equal(cb_Length(&kCB_TX_FIFO), i+1);
	}
	for (int i=0; i<str_len; i++) {
		test_equal((cb_Dequeue(&kCB_TX_FIFO,buf2,i+1)),i+1);
		test_equal(cb_Length(&kCB_TX_FIFO), str_len - i - 1);
		test_equal(cb_Size(&kCB_TX_FIFO), cap);
	}

	// should be empty now
	test_equal(cb_Length(&kCB_TX_FIFO), 0);
	test_equal(cb_Dequeue(&kCB_TX_FIFO,buf,1), NULL);
	test_equal(cb_Size(&kCB_TX_FIFO), cap);

	// enqueue one, then enqueue one, dequeue one, etc, through the whole list
	test_equal(cb_Enqueue(&kCB_TX_FIFO, str+0,1), 1);
	for (int i=1; i<str_len; i++) {
		test_equal(cb_Enqueue(&kCB_TX_FIFO, str+i,1), 2);
		test_equal(cb_Length(&kCB_TX_FIFO), 2);
		test_equal(cb_Dequeue(&kCB_TX_FIFO,buf,1), 1);
		test_equal(cb_Length(&kCB_TX_FIFO), 1);

	}
	test_equal(cb_Dequeue(&kCB_TX_FIFO,buf,1), 1);

	// should be empty now
	test_equal(cb_Length(&kCB_TX_FIFO), 0);
	test_equal(cb_Dequeue(&kCB_TX_FIFO,buf,1), NULL);
	test_equal(cb_Size(&kCB_TX_FIFO), cap);

	test_equal(cb_Enqueue(&kCB_TX_FIFO, str , 10), 10);
	test_equal(cb_Length(&kCB_TX_FIFO), 10);
	test_equal(cb_Dequeue(&kCB_TX_FIFO, buf , 5), 5);
	test_equal(cb_Length(&kCB_TX_FIFO), 5);
	test_equal(cb_Dequeue(&kCB_TX_FIFO, buf+5 , 5), 5);
	test_equal(cb_Length(&kCB_TX_FIFO), 0);
	test_equal(strncmp(buf, str, 10), 0);
	test_assert(!cb_Full(&kCB_TX_FIFO));

	test_equal(cb_Enqueue(&kCB_TX_FIFO, str , cap), cap);
	test_equal(cb_Length(&kCB_TX_FIFO), cap);
	test_assert(cb_Full(&kCB_TX_FIFO));
	test_equal(cb_Enqueue(&kCB_TX_FIFO, str , 1), 0);
	test_assert(cb_Full(&kCB_TX_FIFO));
	test_equal(cb_Dequeue(&kCB_TX_FIFO, buf , cap), cap);
	test_assert(!cb_Full(&kCB_TX_FIFO));
	test_equal(cb_Length(&kCB_TX_FIFO), 0);
	test_equal(strncmp(buf, str, cap), 0);
	// create a second fifo
	cb_t KCB_RX_FIFO;

	cb_init(&KCB_RX_FIFO);
	//const int capa = cb_Size(&KCB_RX_FIFO);

	test_equal(cb_Length(&KCB_RX_FIFO), 0);
	test_equal(cb_Dequeue(&KCB_RX_FIFO, buf, cap), 0);
	test_equal(cb_Dequeue(&KCB_RX_FIFO, buf, 1), 0);
	test_assert(!cb_Full(&KCB_RX_FIFO));

	test_equal(cb_Enqueue(&KCB_RX_FIFO, str,255), 255);
	test_equal(cb_Dequeue(&KCB_RX_FIFO, buf2,280), 255);
}


void test_cbfifo()
{
	g_tests_passed = 0;
	g_tests_total = 0;
	g_skip_tests = 0;

	test_cbfifo_one_iteration();
	g_skip_tests = 0;


	printf(" %s: passed %d/%d test cases (%2.1f%%)\n", __FUNCTION__,
			g_tests_passed, g_tests_total, 100.0*g_tests_passed/g_tests_total);
}
