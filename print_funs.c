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
	        case WIFI_STYPE_ASSOC_REQ:
	            subtype_name = "WIFI_STYPE_ASSOC_REQ";
		    break;
	        case WIFI_STYPE_ASSOC_RESP:
	            subtype_name = "WIFI_STYPE_ASSOC_RESP";
		    break;		
	        case WIFI_STYPE_REASSOC_REQ:
	            subtype_name = "WIFI_STYPE_REASSOC_REQ";
		    break;			
	        case WIFI_STYPE_REASSOC_RESP:
	            subtype_name = "WIFI_STYPE_REASSOC_RESP";
		    break;
	        case WIFI_STYPE_PROBE_REQ:
	            subtype_name = "WIFI_STYPE_PROBE_REQ";
		    break;
	        case WIFI_STYPE_PROBE_RESP:
	            subtype_name = "WIFI_STYPE_PROBE_RESP";
		    break;
	        case WIFI_STYPE_BEACON:
	            subtype_name = "WIFI_STYPE_BEACON";
		    break;
	        case WIFI_STYPE_ATIM:
	            subtype_name = "WIFI_STYPE_ATIM";
		    break;
	        case WIFI_STYPE_DISASSOC:
	            subtype_name = "WIFI_STYPE_DISASSOC";
		    break;
	        case WIFI_STYPE_AUTH:
	            subtype_name = "WIFI_STYPE_AUTH";
		    break;
	        case WIFI_STYPE_DEAUTH:
	            subtype_name = "WIFI_STYPE_DEAUTH";
		    break;
		default:
		    subtype_name = "UNKNOWN";		    
		}
	}
	else if(type==0b01){
	    switch(subtype){
	        case WIFI_STYPE_PSPOLL:
	            subtype_name = "WIFI_STYPE_PSPOLL";
		    break;
	        case WIFI_STYPE_RTS:
	            subtype_name = "WIFI_STYPE_RTS";
		    break;		
	        case WIFI_STYPE_CTS:
	            subtype_name = "WIFI_STYPE_CTS";
		    break;			
	        case WIFI_STYPE_ACK:
	            subtype_name = "WIFI_STYPE_ACK";
		    break;
	        case WIFI_STYPE_CFEND:
	            subtype_name = "WIFI_STYPE_CFEND";
		    break;
	        case WIFI_STYPE_CFENDACK:
	            subtype_name = "WIFI_STYPE_CFENDACK";
		    break;
		default:
		    subtype_name = "UNKNOWN";		    
		}
	}
	else if(type==0b10){
	    switch(subtype){
	        case WIFI_STYPE_DATA:
	            subtype_name = "WIFI_STYPE_DATA";
		    break;
	        case WIFI_STYPE_DATA_CFACK:
	            subtype_name = "WIFI_STYPE_DATA_CFACK";
		    break;		
	        case WIFI_STYPE_DATA_CFPOLL:
	            subtype_name = "WIFI_STYPE_DATA_CFPOLL";
		    break;			
	        case WIFI_STYPE_DATA_CFACKPOLL:
	            subtype_name = "WIFI_STYPE_DATA_CFACKPOLL";
		    break;
	        case WIFI_STYPE_NULLFUNC:
	            subtype_name = "WIFI_STYPE_NULLFUNC";
		    break;
	        case WIFI_STYPE_CFACK:
	            subtype_name = "WIFI_STYPE_CFACK";
		    break;
	        case WIFI_STYPE_CFPOLL:
	            subtype_name = "WIFI_STYPE_CFPOLL";
		    break;
	        case WIFI_STYPE_CFACKPOLL:
	            subtype_name = "WIFI_STYPE_CFACKPOLL";
		    break;
	        case WIFI_STYPE_QOS_DATA:
	            subtype_name = "WIFI_STYPE_QOS_DATA";
		    break;
	        case WIFI_STYPE_QOS_DATA_CFACK:
	            subtype_name = "WIFI_STYPE_QOS_DATA_CFACK";
		    break;
	        case WIFI_STYPE_QOS_DATA_CFPOLL:
	            subtype_name = "WIFI_STYPE_QOS_DATA_CFPOLL";
		    break;
	        case WIFI_STYPE_QOS_DATA_CFACKPOLL:
	            subtype_name = "WIFI_STYPE_QOS_DATA_CFACKPOLL";
		    break;
	        case WIFI_STYPE_QOS_NULLFUNC:
	            subtype_name = "WIFI_STYPE_QOS_NULLFUNC";
		    break;		
	        case WIFI_STYPE_QOS_CFPOLL:
	            subtype_name = "WIFI_STYPE_QOS_CFPOLL";
		    break;			
	        case WIFI_STYPE_QOS_CFACK:
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

	bin(frame.protocolVersion);
	printf("\n");
	print_type(frame.type);
	print_subtype(frame.type, frame.subtype);
	printf("\n [toDS = ");
	bin(frame.toDS);
	printf(" ][fromDS = ");
	bin(frame.fromDS);
	printf(" ][moreFrag = ");
	bin(frame.moreFrag);
	printf(" ][retry = ");
	bin(frame.retry);
	printf(" ]\n[powerManagement = ");
	bin(frame.powerManagement);
	printf(" ][moreData = ");
	bin(frame.moreData);
	printf(" ][WEP = ");
	bin(frame.WEP);
	printf(" ][rsvd = ");
	bin(frame.rsvd);
	printf(" ]\n");
}


void print_wifi_hdr(struct wifi_hdr wifihdr){
	printf("[] frame control:");
	print_frame_control(wifihdr.frame_control);
	printf("[] Duration id: %d\n", wifihdr.duration_id);
	switch (wifihdr.frame_control.type)
	{
		case WIFI_FTYPE_DATA:
			printf("[] Addr 1: ");
			print_mac_addr(wifihdr.addr1);
			printf("[] Addr 2: ");
			print_mac_addr(wifihdr.addr2);
			printf("[] Addr 3: ");
			print_mac_addr(wifihdr.addr3);
			printf("[] Addr 4: ");
			print_mac_addr(wifihdr.addr4);
			printf("\n");
			break;
		case WIFI_FTYPE_CTL:
			switch (wifihdr.frame_control.subtype)
			{
				case WIFI_STYPE_PSPOLL:
					printf("[] Addr TA: ");
					print_mac_addr(wifihdr.addr2);
					break;
				case WIFI_STYPE_RTS:
					printf("[] Addr RA: ");
					print_mac_addr(wifihdr.addr1);
					printf("[] Addr TA: ");
					print_mac_addr(wifihdr.addr2);
					break;
				default:
					printf("[] Addr TA: ");
					print_mac_addr(wifihdr.addr1);
					break;
			}
			printf("\n");
			break;
		default:
			printf("[] DA: ");
			print_mac_addr(wifihdr.addr1);
			printf("[] SA: ");
			print_mac_addr(wifihdr.addr2);
			printf("\n");
			break;
	}
	
}
