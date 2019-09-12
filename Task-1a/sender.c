// #include <time.h>
#include "../lib/util.h"

static inline void do_something(int loop_param) {
    for(int i=0;i<loop_param;i++) {
        volatile int j = i*2;
        j++;
    }
    return;
}

int main(int argc, char **argv) {

    char msg[BYTES_SENT];
    unsigned int msg_len = 0;
    clock_t t_send;
    double trans_time;
    double trans_rate;

    // TODO: Establish your cache covert channel
    map_handle_t *handle;     // declaring a handle for file mapping
    char *map;

    map = (char *) map_file("../share_mem.txt", &handle);
    if(map == NULL){
        return -1;
    }

    //printf("Enter message to be send: ");
    /* fgets (msg, 50, stdin); */
    for (int i = 0; i < (int) sizeof (msg); i++)
    {
        msg[i] = '0' + (i % NUM_CHARS);
    }

    t_send = clock();

    // TODO: Transmit message over the cache covert channel

    for(int i=0;i < BYTES_SENT;i++) {
        volatile char x = *(map + (msg[i] - '0')*4096);
        do_something (30000);
        x += 2;
        msg_len++;
    }

    t_send = clock() - t_send;
    trans_time = ((double) t_send) / CLOCKS_PER_SEC;
    trans_rate = (double) (msg_len * 8) / trans_time;

    printf("[Sender] Total data Send : %u bytes\n", msg_len);
    printf("[Sender] Time to send data : %lf second\n", trans_time);
    printf("[Sender] Data transmission rate : %lu bps\n", (unsigned long) trans_rate);

    return 0;
}
