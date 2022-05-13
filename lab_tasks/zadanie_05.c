/*
 * Compilation:  gcc -Wall ./zadanie_05.c -o ./zadanie_05 -lpcap
 * Usage:        ./zadanie_05 INTERFACE
 * NOTE:         This program requires root privileges.
 *
 */

#include <pcap.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <linux/ip.h>
#include <linux/if_arp.h>
#include <linux/if_ether.h>
#include <linux/if_packet.h>

char* errbuf;
pcap_t* handle;

void cleanup() {
  pcap_close(handle);
  free(errbuf);
}

struct results {
    int arp;
    int ip;
    int udp;
    int tcp;
    int other;
} res;

void stop(int signo) {
  printf("\nARP: %d", res.arp);
  printf("\nIP: %d", res.ip);
  printf("\n-UDP: %d", res.udp);
  printf("\n-TCP: %d", res.tcp);
  printf("\nOther: %d\n", res.other);
  exit(EXIT_SUCCESS);
}


void trap(u_char *user, const struct pcap_pkthdr *h, const u_char *bytes) {
  printf("[%dB of %dB]\n", h->caplen, h->len);

  struct ethhdr *hdr = (struct ethhdr*) bytes;

  if (hdr->h_proto == htons(ETH_P_IP) ){
      res.ip +=1;
      struct iphdr *iph = (struct iphdr*)( bytes + ETH_HLEN);

      if(iph->protocol == (char)17){
        res.udp +=1;
      }
      else if(iph->protocol == (char)6){
        res.tcp +=1;
      }
  }
  else if (hdr->h_proto == htons(ETH_P_ARP) ) {
      res.arp +=1;
  }
  else {
    res.other +=1;
  }
}


int main(int argc, char** argv) {

  atexit(cleanup);
  signal(SIGINT, stop);
  errbuf = malloc(PCAP_ERRBUF_SIZE);
  handle = pcap_create(argv[1], errbuf);
  pcap_set_promisc(handle, 1);
  pcap_set_snaplen(handle, 65535);
  pcap_set_timeout(handle, 1000);
  pcap_activate(handle);
  pcap_loop(handle, -1, trap, NULL);
}
