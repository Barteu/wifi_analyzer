/*
 * Compilation:  gcc -Wall analyzer.c print_funs.c -o analyzer -lpcap
 * Usage:        ./analyzer INTERFACE
 * NOTES:        libpcap-dev library is needed.
 *               This program requires root privileges.
 */

#include <pcap.h>
#include <signal.h>
#include "print_funs.h"

char* errbuf;
pcap_t* handle;

void cleanup() {
  pcap_close(handle);
  free(errbuf);
}

void stop(int signo) {
  exit(EXIT_SUCCESS);
}


void trap(u_char *user, const struct pcap_pkthdr *h, const u_char *bytes) {
  struct radiotap_hdr *rthdr = (struct radiotap_hdr *) bytes;
  struct wifi_hdr *wifihdr = (struct wifi_hdr *) (bytes + rthdr->len);
  printf("[%dB of %dB]\n", h->caplen, h->len);
  print_wifi_hdr(*wifihdr);

  const u_char *frame_body;
  int frame_len;
  if(wifihdr->frame_control.type == WIFI_FTYPE_MGMT){
    frame_body = bytes + rthdr->len + sizeof(struct wifi_hdr) - 6;
    frame_len = h->len - rthdr->len - sizeof(struct wifi_hdr) + 2;
    print_frame_body(frame_body, frame_len);
  }else if(wifihdr->frame_control.type == WIFI_FTYPE_DATA){
    switch (wifihdr->frame_control.subtype)
    {
      case WIFI_STYPE_QOS_DATA:	
      case WIFI_STYPE_QOS_DATA_CFACK:
      case WIFI_STYPE_QOS_DATA_CFPOLL:
      case WIFI_STYPE_QOS_DATA_CFACKPOLL:
      case WIFI_STYPE_QOS_NULLFUNC:
      case WIFI_STYPE_QOS_CFPOLL:
      case WIFI_STYPE_QOS_CFACK:
        frame_body = bytes + rthdr->len + sizeof(struct wifi_hdr) + 2;
        frame_len = h->len - rthdr->len - sizeof(struct wifi_hdr) - 6;
        break;
      default:
        frame_body = bytes + rthdr->len + sizeof(struct wifi_hdr);
        frame_len = h->len - rthdr->len - sizeof(struct wifi_hdr) - 4;
        break;
    }
    print_frame_body(frame_body, frame_len);
  }
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


    atexit(cleanup);
    signal(SIGINT, stop);
    errbuf = malloc(PCAP_ERRBUF_SIZE);
    handle = pcap_create(dev, errbuf);
    pcap_set_promisc(handle, 1);
    pcap_set_snaplen(handle, 65535);
    pcap_set_timeout(handle, 1000);
    if(pcap_activate(handle)!=0)
    {
      exit(EXIT_FAILURE);
    }


  /* check if IEEE802.11 device is used*/
  if (pcap_datalink(handle) != DLT_IEEE802_11_RADIO) {
      fprintf(stderr, "Interface %s is not an IEEE802.11\n", dev);
      exit(EXIT_FAILURE);
  }
  
  printf("analyzer is running...\n");
  pcap_loop(handle, -1, trap, NULL);

}
