/*
 * Compilation:  gcc -Wall ./analyzer.c -o ./analyzer -lpcap
 * Usage:        ./analyzer ? ?
 * NOTES:        libpcap-dev library is needed.
 *               This program requires root privileges.
 */

#include <pcap.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char** argv) {
    printf("hello\n");
}
