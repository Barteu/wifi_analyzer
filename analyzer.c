/*
 * Compilation:  gcc -Wall ./analyzer.c -o ./analyzer -lpcap
 * Usage:        ./analyzer INTERFACE
 * NOTES:        libpcap-dev library is needed.
 *               This program requires root privileges.
 */

#include <pcap.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

// -----------====----------- pcapsniff.c code <start>
char* errbuf;
pcap_t* handle;

void cleanup() {
  pcap_close(handle);
  free(errbuf);
}

void stop(int signo) {
  exit(EXIT_SUCCESS);
}
// =====----------------------==== pcapsniff.c code <end>


void trap(u_char *user, const struct pcap_pkthdr *h, const u_char *bytes) {
  printf("[%dB of %dB]\n", h->caplen, h->len);
}

int main(int argc, char** argv) {

  /* device name */
    char *dev = NULL;    
    if (argc == 2) {
        dev = argv[1];
    } else {
        fprintf(stderr, "Couldn't find given device: %s\n", errbuf);
        exit(EXIT_FAILURE);
    }


// -----------====----------- pcapsniff.c code <start>
    atexit(cleanup);
    signal(SIGINT, stop);
    errbuf = malloc(PCAP_ERRBUF_SIZE);
    handle = pcap_create(dev, errbuf);
    pcap_set_promisc(handle, 1);
    pcap_set_snaplen(handle, 65535);
    pcap_set_timeout(handle, 1000);
    pcap_activate(handle);
// =====----------------------==== pcapsniff.c code <end>


  /* check if IEEE802.11 device is used*/
    if (pcap_datalink(handle) != DLT_IEEE802_11) {
        fprintf(stderr, "Interface %s is not an IEEE802.11\n", dev);
        exit(EXIT_FAILURE);
    }
    printf("analyzer is running...\n");

// -----------====----------- pcapsniff.c code <start>
    pcap_loop(handle, -1, trap, NULL);
// =====----------------------==== pcapsniff.c code <end>
}
