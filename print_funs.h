#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "wifi_types.h" 

void print_frame_body(const u_char *frame_body, int len);
void print_type(u_int8_t type);
void print_subtype(u_int8_t type, u_int8_t subtype);
void print_mac_addr(u_int8_t addr[]);
void bin(unsigned n);
void print_frame_control(struct frame_control frame);
void print_wifi_hdr(struct wifi_hdr wifihdr );
