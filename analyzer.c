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
#include "wifi_types.h"
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



void print_type(u_int8_t type){

	char* type_name;
	switch(type){
		case 0b00:
			type_name = "WIFI_FTYPE_MGMT";	
			break;	
		case 0b01:
			type_name = "WIFI_FTYPE_CTL";
			break;	
		case 0b10:
			type_name = "WIFI_FTYPE_DATA";
			break;
		default:
			type_name = "UNKNOWN";
	}
	printf("Type = %s\n", type_name);
}


void print_subtype(u_int8_t type, u_int8_t subtype){
	char* subtype_name;
	if(type==0b00){
	    switch(subtype){
	        case 0b0000:
	            subtype_name = "WIFI_STYPE_ASSOC_REQ";
		    break;
	        case 0b0001:
	            subtype_name = "WIFI_STYPE_ASSOC_RESP";
		    break;		
	        case 0b0010:
	            subtype_name = "WIFI_STYPE_REASSOC_REQ";
		    break;			
	        case 0b0011:
	            subtype_name = "WIFI_STYPE_REASSOC_RESP";
		    break;
	        case 0b0100:
	            subtype_name = "WIFI_STYPE_PROBE_REQ";
		    break;
	        case 0b0101:
	            subtype_name = "WIFI_STYPE_PROBE_RESP";
		    break;
	        case 0b1000:
	            subtype_name = "WIFI_STYPE_BEACON";
		    break;
	        case 0b1001:
	            subtype_name = "WIFI_STYPE_ATIM";
		    break;
	        case 0b1010:
	            subtype_name = "WIFI_STYPE_DISASSOC";
		    break;
	        case 0b1011:
	            subtype_name = "WIFI_STYPE_AUTH";
		    break;
	        case 0b1100:
	            subtype_name = "WIFI_STYPE_DEAUTH";
		    break;
		default:
		    subtype_name = "UNKNOWN";		    
		}
	}
	else if(type==0b01){
	    switch(subtype){
	        case 0b1010:
	            subtype_name = "WIFI_STYPE_PSPOLL";
		    break;
	        case 0b1011:
	            subtype_name = "WIFI_STYPE_RTS";
		    break;		
	        case 0b1100:
	            subtype_name = "WIFI_STYPE_CTS";
		    break;			
	        case 0b1101:
	            subtype_name = "WIFI_STYPE_ACK";
		    break;
	        case 0b1110:
	            subtype_name = "WIFI_STYPE_CFEND";
		    break;
	        case 0b1111:
	            subtype_name = "WIFI_STYPE_CFENDACK";
		    break;
		default:
		    subtype_name = "UNKNOWN";		    
		}
	}
	else if(type==0b10){
	    switch(subtype){
	        case 0b0000:
	            subtype_name = "WIFI_STYPE_DATA";
		    break;
	        case 0b0001:
	            subtype_name = "WIFI_STYPE_DATA_CFACK";
		    break;		
	        case 0b0010:
	            subtype_name = "WIFI_STYPE_DATA_CFPOLL";
		    break;			
	        case 0b0011:
	            subtype_name = "WIFI_STYPE_DATA_CFACKPOLL";
		    break;
	        case 0b0100:
	            subtype_name = "WIFI_STYPE_NULLFUNC";
		    break;
	        case 0b0101:
	            subtype_name = "WIFI_STYPE_CFACK";
		    break;
	        case 0b0110:
	            subtype_name = "WIFI_STYPE_CFPOLL";
		    break;
	        case 0b0111:
	            subtype_name = "WIFI_STYPE_CFACKPOLL";
		    break;
	        case 0b1000:
	            subtype_name = "WIFI_STYPE_QOS_DATA";
		    break;
	        case 0b1001:
	            subtype_name = "WIFI_STYPE_QOS_DATA_CFACK";
		    break;
	        case 0b1010:
	            subtype_name = "WIFI_STYPE_QOS_DATA_CFPOLL";
		    break;
	        case 0b1011:
	            subtype_name = "WIFI_STYPE_QOS_DATA_CFACKPOLL";
		    break;
	        case 0b1100:
	            subtype_name = "WIFI_STYPE_QOS_NULLFUNC";
		    break;		
	        case 0b1110:
	            subtype_name = "WIFI_STYPE_QOS_CFPOLL";
		    break;			
	        case 0b1111:
	            subtype_name = "WIFI_STYPE_QOS_CFACK";
		    break;
		default:
		    subtype_name = "UNKNOWN";		    
		}
	}
	else{
		subtype_name = "UNKNOWN";
	}
	printf("Subtype = %s\n", subtype_name);

}



void print_wifi_hdr(struct wifi_hdr wifihdr ){
	print_type(wifihdr.frame_control.type);
	print_subtype(wifihdr.frame_control.type, wifihdr.frame_control.subtype);
	printf("\n");
	
}


void trap(u_char *user, const struct pcap_pkthdr *h, const u_char *bytes) {
  struct radiotap_hdr *rthdr = (struct radiotap_hdr *) bytes;
  struct wifi_hdr *wifihdr = (struct wifi_hdr *) (bytes + rthdr->len);
  print_wifi_hdr(*wifihdr);
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
// =====----------------------==== pcapsniff.c code <end>
    switch(pcap_activate(handle))
    {
      case 0:
        printf("OK\n");
        break;
      default:
        exit(EXIT_FAILURE);

    }


  /* check if IEEE802.11 device is used*/
  printf("%d\n",pcap_datalink(handle));
    if (pcap_datalink(handle) != DLT_IEEE802_11_RADIO) {
        fprintf(stderr, "Interface %s is not an IEEE802.11\n", dev);
        exit(EXIT_FAILURE);
    }
    printf("analyzer is running...\n");

// -----------====----------- pcapsniff.c code <start>
    pcap_loop(handle, -1, trap, NULL);
// =====----------------------==== pcapsniff.c code <end>
}
