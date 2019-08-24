// #include <time.h>
#include "../lib/util.h"

void do_something(){
	for(int i=0;i<50000;i++){
		int j = i*2;
		j++;
	}
	return;
}
int main(int argc, char **argv) {

	char msg[51];
	unsigned int msg_len = 0;
	clock_t t_send;
	double trans_time;
	double trans_rate;

	// TODO: Establish your cache covert channel
	map_handle_t *handle;     // declaring a handle for file mapping
  	char *map;

  	map = (char *) map_file("/home/vinayakt/test.txt", &handle);

  	if(map==NULL){
  		return -1;
  	}

	printf("Enter message to be send: ");
	fgets (msg, 50, stdin);
	msg_len = strlen(msg);

	t_send = clock();

	// TODO: Transmit message over the cache covert channel

	for(int i=0;i<msg_len;i++){
		if(msg[i]=='A'){
			char x = *(map);
			for(int i=0;i<50000;i++){
				char j = *(map);
				j++;
			}
		}
		else{
			char x = *(map+64);
			for(int i=0;i<50000;i++){
				char j = *(map+64);
				j++;
			}
		}
	}


	t_send = clock() - t_send;
	trans_time = ((double) t_send) / CLOCKS_PER_SEC;
	trans_rate = (double) (msg_len * 8) / trans_time;

	printf("[Sender] Total data Send : %u bytes\n", msg_len);
	printf("[Sender] Time to send data : %lf second\n", trans_time);
	printf("[Sender] Data transmission rate : %lu bps\n", (unsigned long) trans_rate);

	return 0;
}