#include<stdio.h>
#include<stdlib.h>
#include<zmq.h>
#include<unistd.h>
#include<string.h>
#include <sys/time.h>
#include <malloc.h>
#include <string.h>


enum outformat {
	BAYER, FRGB, FRNUM,
};

#pragma pack(2)
struct framsg {
	unsigned int fid;     //4
	enum outformat ofmt;  //4
	struct timeval tmstp; //16
	unsigned int w;       //4
	unsigned int h;       //4
	unsigned int depth;   //4
	unsigned int type;    //4
	unsigned int size;    //4
	void *addr;           //8
};
#pragma pack()

struct framsg *getframe(int fid, int w, int h, int d, int t)
{
	int i = 0;
	unsigned short int *addr = NULL;
	unsigned short int val = 0;
	struct framsg *frame = (struct framsg *)malloc(sizeof(struct framsg) + w * h * t / 8);
	memset(frame, 0, sizeof(struct framsg) + w * h * t / 8);
	//
	gettimeofday(&frame->tmstp, NULL);
	frame->fid = fid;
	frame->ofmt = BAYER;
	frame->w = w;
	frame->h = h;
	frame->depth = d;
	frame->type = t;
	frame->size = w * h * t / 8;
	frame->addr = (void *)frame + sizeof(struct framsg);
	/** printf("frame %p addr %p *addr 0x%lx\n", frame, frame->addr, *((unsigned long int *)frame->addr)); */
	for (i = 0; i < frame->size; i++) {
		*((unsigned short int *)frame->addr + i) = rand() % (1 << d);
		/** printf("frame %p addr %p *addr 0x%04x\n", frame,  */
		/**         (unsigned short int *)frame->addr + i, */
		/**         *((unsigned short int *)frame->addr + i)); */
	}
	//
	return frame;
}

int main(void)
{
        void *ctx,*sock;
        int ret = 0;
        char data[1024];
        int idx = 0;
		size_t len = 0;
        ctx = zmq_ctx_new();
        sock = zmq_socket(ctx,ZMQ_PUB);
        ret = zmq_bind(sock,"tcp://127.0.0.1:5555");
        while(1) {
			struct framsg *frame = getframe(idx, 4, 3, 12, 16);
			/** struct framsg *frame = getframe(idx, 640, 480, 12, 16); */
			/** ret = zmq_send(sock, (void *)frame, sizeof(struct framsg), 0); */
			len = sizeof(struct framsg);
			ret = zmq_send(sock, (void *)frame, len, 0);
			free(frame);
			idx++;
			sleep(1);
			/** break; */
        }
        zmq_close(sock);
        zmq_ctx_destroy(ctx);
        return 0;
}
