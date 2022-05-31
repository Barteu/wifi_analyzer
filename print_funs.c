#include "print_funs.h"

void print_frame_body(const u_char *frame_body, int len){
  printf("Frame body [%dB]\n", len);
  for(int i=0; i<len; i+=16){
    for(int j=0; j<16 ;j++){
      if(j + i < len)
        printf("%02x ", frame_body[i+j]);
      else
        printf("   ");
    }
    printf(" ");
    for(int j=0; j<16 ;j++){
      printf("%c", (isprint(frame_body[i+j]) ? frame_body[i+j] : '.'));
    }     
    printf("\n");
  }
  printf("\n");
}


void print_type(u_int8_t type){

	char* type_name;
	switch(type){
		case 0b00:
			type_name = "Management Frame";	
			break;	
		case 0b01:
			type_name = "Control Frame";
			break;	
		case 0b10:
			type_name = "Data Frame";
			break;
		default:
			type_name = "UNKNOWN";
	}
	printf("[Type = %s]\n", type_name);
}


void print_subtype(u_int8_t type, u_int8_t subtype){
	char* subtype_name;
	if(type==0b00){
	    switch(subtype){
	        case WIFI_STYPE_ASSOC_REQ:
	            subtype_name = "Association Request";
		    break;
	        case WIFI_STYPE_ASSOC_RESP:
	            subtype_name = "Association Response";
		    break;		
	        case WIFI_STYPE_REASSOC_REQ:
	            subtype_name = "Reassociation Request";
		    break;			
	        case WIFI_STYPE_REASSOC_RESP:
	            subtype_name = "Reassociation Response";
		    break;
	        case WIFI_STYPE_PROBE_REQ:
	            subtype_name = "Probe Request";
		    break;
	        case WIFI_STYPE_PROBE_RESP:
	            subtype_name = "Probe Response";
		    break;
	        case WIFI_STYPE_BEACON:
	            subtype_name = "Beacon";
		    break;
	        case WIFI_STYPE_ATIM:
	            subtype_name = "Announcemnt Traffic Indication Map";
		    break;
	        case WIFI_STYPE_DISASSOC:
	            subtype_name = "disassociation";
		    break;
	        case WIFI_STYPE_AUTH:
	            subtype_name = "Authentication";
		    break;
	        case WIFI_STYPE_DEAUTH:
	            subtype_name = "Deauthentication";
		    break;
		default:
		    subtype_name = "UNKNOWN";		    
		}
	}
	else if(type==0b01){
	    switch(subtype){
	        case WIFI_STYPE_PSPOLL:
	            subtype_name = "Power-Save Poll";
		    break;
	        case WIFI_STYPE_RTS:
	            subtype_name = "Request-to-Send";
		    break;		
	        case WIFI_STYPE_CTS:
	            subtype_name = "Clear-to-Send";
		    break;			
	        case WIFI_STYPE_ACK:
	            subtype_name = "Acknowledgment";
		    break;
	        case WIFI_STYPE_CFEND:
	            subtype_name = "CF-End";
		    break;
	        case WIFI_STYPE_CFENDACK:
	            subtype_name = "CF-End + CF-ACK";
		    break;
		default:
		    subtype_name = "UNKNOWN";		    
		}
	}
	else if(type==0b10){
	    switch(subtype){
	        case WIFI_STYPE_DATA:
	            subtype_name = "Data";
		    break;
	        case WIFI_STYPE_DATA_CFACK:
	            subtype_name = "Data + CF-ACK";
		    break;		
	        case WIFI_STYPE_DATA_CFPOLL:
	            subtype_name = "Data + CF-POLL";
		    break;			
	        case WIFI_STYPE_DATA_CFACKPOLL:
	            subtype_name = "Data + CF-ACK + CF-POLL";
		    break;
	        case WIFI_STYPE_NULLFUNC:
	            subtype_name = "NULL";
		    break;
	        case WIFI_STYPE_CFACK:
	            subtype_name = "CF-ACK";
		    break;
	        case WIFI_STYPE_CFPOLL:
	            subtype_name = "CF-POLL";
		    break;
	        case WIFI_STYPE_CFACKPOLL:
	            subtype_name = "CF-ACK + CF-POLL";
		    break;
	        case WIFI_STYPE_QOS_DATA:
	            subtype_name = "QoS Data";
		    break;
	        case WIFI_STYPE_QOS_DATA_CFACK:
	            subtype_name = "QoS Data + CF-ACK";
		    break;
	        case WIFI_STYPE_QOS_DATA_CFPOLL:
	            subtype_name = "QoS Data + CF-POLL";
		    break;
	        case WIFI_STYPE_QOS_DATA_CFACKPOLL:
	            subtype_name = "QoS Data + CF-ACK + CF-POLL";
		    break;
	        case WIFI_STYPE_QOS_NULLFUNC:
	            subtype_name = "QoS NULL";
		    break;		
	        case WIFI_STYPE_QOS_CFPOLL:
	            subtype_name = "QoS CF-POLL";
		    break;			
	        case WIFI_STYPE_QOS_CFACK:
	            subtype_name = "QoS CF-ACK";
		    break;
		default:
		    subtype_name = "UNKNOWN";		    
		}
	}
	else{
		subtype_name = "UNKNOWN";
	}
	printf("[Subtype = %s]\n", subtype_name);

}


void print_mac_addr(u_int8_t addr[]){
printf("%02x:%02x:%02x:%02x:%02x:%02x\n",
           addr[0], addr[1], addr[2],
           addr[3], addr[4], addr[5]);

} 


void bin(unsigned n)
{
    if (n > 1)
        bin(n / 2);
    printf("%d", n % 2);
}


void print_frame_control(struct frame_control frame){

	printf("[protocolVersion = ");
	bin(frame.protocolVersion);
	printf("]\n");
	print_type(frame.type);
	print_subtype(frame.type, frame.subtype);
	printf("[toDS = ");
	bin(frame.toDS);
	printf("][fromDS = ");
	bin(frame.fromDS);
	printf("][moreFrag = ");
	bin(frame.moreFrag);
	printf("][retry = ");
	bin(frame.retry);
	printf("]\n[powerManagement = ");
	bin(frame.powerManagement);
	printf("][moreData = ");
	bin(frame.moreData);
	printf("][WEP = ");
	bin(frame.WEP);
	printf("][rsvd = ");
	bin(frame.rsvd);
	printf("]\n\n");
}


void print_wifi_hdr(struct wifi_hdr wifihdr){
	printf("Frame control:\n");
	print_frame_control(wifihdr.frame_control);
	printf("Duration/id: %d\n", wifihdr.duration_id);
	switch (wifihdr.frame_control.type)
	{
		case WIFI_FTYPE_DATA:
			printf("Receiver address: ");
			print_mac_addr(wifihdr.addr1);
			printf("Transmitter address: ");
			print_mac_addr(wifihdr.addr2);
			printf("Destination (deafult gateway)/filtering: ");
			print_mac_addr(wifihdr.addr3);
			printf("Addr used in ad hoc: ");
			print_mac_addr(wifihdr.addr4);
			printf("\n");
			break;
		case WIFI_FTYPE_CTL:
			switch (wifihdr.frame_control.subtype)
			{
				case WIFI_STYPE_PSPOLL:
					printf("BSSID: ");
					print_mac_addr(wifihdr.addr1);
					printf("Transmitter address: ");
					print_mac_addr(wifihdr.addr2);
					break;
				case WIFI_STYPE_RTS:
					printf("Receiver address: ");
					print_mac_addr(wifihdr.addr1);
					printf("Transmitter address: ");
					print_mac_addr(wifihdr.addr2);
					break;
				case WIFI_STYPE_ACK:
				case WIFI_STYPE_CTS:
					printf("Receiver address: ");
					print_mac_addr(wifihdr.addr1);
					break;
				default:
					printf("Receiver address: ");
					print_mac_addr(wifihdr.addr1);
					printf("BSSID: ");
					print_mac_addr(wifihdr.addr2);
					break;
			}
			printf("\n");
			break;
		case WIFI_FTYPE_MGMT:
			printf("Destination addresses: ");
			print_mac_addr(wifihdr.addr1);
			printf("Source addresses: ");
			print_mac_addr(wifihdr.addr2);
			printf("BSSID: ");
			print_mac_addr(wifihdr.addr3);
			printf("\n");
			break;
		default:
			printf("Something went wrong\n");
			break;
	}
	printf("\n");
}
