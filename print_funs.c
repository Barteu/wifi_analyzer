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