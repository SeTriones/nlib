#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include "ngx_queue.h"

typedef struct {
	ngx_queue_t qe;
	int num;
} testNode;

void traverseQueue(ngx_queue_t* qh) {
	ngx_queue_t* q;
	for (q = ngx_queue_head(qh); q != ngx_queue_sentinel(qh); q = ngx_queue_next(q)) {
		testNode* tn = ngx_queue_data(q, testNode, qe);
		printf("%d ", tn->num);
	}
	printf("\n");
}

intptr_t compareTestNode(const ngx_queue_t* a, const ngx_queue_t* b) {
	testNode* na = ngx_queue_data(a, testNode, qe);
	testNode* nb = ngx_queue_data(b, testNode, qe);
	return na->num > nb->num;
}

int main(int argc, char* argv[]) {
	testNode lst[5];
	for (int i = 0; i < 5; i++) {
		lst[i].num = i;
	}
	ngx_queue_t qh;
	ngx_queue_init(&qh);
	ngx_queue_insert_tail(&qh, &lst[0].qe);
	ngx_queue_insert_tail(&qh, &lst[2].qe);
	ngx_queue_insert_tail(&qh, &lst[4].qe);
	ngx_queue_insert_head(&qh, &lst[1].qe);
	ngx_queue_insert_head(&qh, &lst[3].qe);

	traverseQueue(&qh);
	ngx_queue_sort(&qh, compareTestNode);
	traverseQueue(&qh);
}
