#include <linux/types.h>
/* Main types */
#define WIFI_FTYPE_MGMT					0b00	//Type management
#define WIFI_FTYPE_CTL					0b01	//Type control
#define WIFI_FTYPE_DATA					0b10	//Type data

/* Type management subtypes*/
#define WIFI_STYPE_ASSOC_REQ			0b0000	//Association request
#define WIFI_STYPE_ASSOC_RESP 			0b0001	//Association response
#define WIFI_STYPE_REASSOC_REQ			0b0010	//Reassociation request
#define WIFI_STYPE_REASSOC_RESP			0b0011	//Reassociation response
#define WIFI_STYPE_PROBE_REQ			0b0100	//Probe request
#define WIFI_STYPE_PROBE_RESP			0b0101	//Probe response
#define WIFI_STYPE_BEACON				0b1000	//Beacon
#define WIFI_STYPE_ATIM					0b1001	//Announcement traffic indication message
#define WIFI_STYPE_DISASSOC				0b1010	//Disassociation
#define WIFI_STYPE_AUTH					0b1011	//Authentication
#define WIFI_STYPE_DEAUTH				0b1100	//Deauthentication

/* Type control subtypes*/
#define WIFI_STYPE_PSPOLL				0b1010	//Power Save (PS)-Poll
#define WIFI_STYPE_RTS					0b1011	//Request To Send
#define WIFI_STYPE_CTS					0b1100	//Clear To Send
#define WIFI_STYPE_ACK					0b1101	//Acknowledgement
#define WIFI_STYPE_CFEND				0b1110	//Contention-Free-End
#define WIFI_STYPE_CFENDACK				0b1111	//CF-End + CF-Ack

/* Type data subtypes*/
#define WIFI_STYPE_DATA					0b0000	//Data
#define WIFI_STYPE_DATA_CFACK			0b0001	//Data + CF-Ack
#define WIFI_STYPE_DATA_CFPOLL			0b0010	//Data + CF-Poll
#define WIFI_STYPE_DATA_CFACKPOLL		0b0011	//Data + CF-Ack + CF-Poll
#define WIFI_STYPE_NULLFUNC				0b0100	//Null function (no data)
#define WIFI_STYPE_CFACK				0b0101	//CF-Ack (no data)
#define WIFI_STYPE_CFPOLL				0b0110	//CF-Poll (no data)
#define WIFI_STYPE_CFACKPOLL			0b0111	//CF-Ack + CF-Poll (no data)
#define WIFI_STYPE_QOS_DATA				0b1000	//QoS Data
#define WIFI_STYPE_QOS_DATA_CFACK		0b1001	//QoS Data + CF-Ack
#define WIFI_STYPE_QOS_DATA_CFPOLL		0b1010	//QoS Data + CF-Poll
#define WIFI_STYPE_QOS_DATA_CFACKPOLL	0b1011	//QoS Data + CF-Ack + CF-Poll
#define WIFI_STYPE_QOS_NULLFUNC			0b1100	//QoS Null (no data)
#define WIFI_STYPE_QOS_CFPOLL			0b1110	//QoS + CF-Poll (no data)
#define WIFI_STYPE_QOS_CFACK			0b1111	//QoS + CF-Ack (no data)


struct radiotap_hdr {
    u_int8_t        revision;     /* set to 0 */
    u_int8_t        pad;
    u_int16_t       len;         /* entire length */
};

struct frame_control {
	u_int8_t protocolVersion :2; /* 0 for 802.11 */
	u_int8_t type : 2; /* data, management, control */
	u_int8_t subtype : 4;
	u_int8_t toDS : 1; /*indicate that destination frame is for DS */
	u_int8_t fromDS : 1; /*indicate frame coming from DS */
	u_int8_t moreFrag : 1; /* set when frame is followed by other fragment */
	u_int8_t retry : 1; /* set in case of retransmission frame */
	u_int8_t powerManagement : 1; /* set when station go Power Save mode (PS) */
	u_int8_t moreData : 1; /* when set means that AP has more buffered data for a stationin Power Save mode */
	u_int8_t WEP : 1; /* indicates that in the Frame Body is data that needs to be processed by WEP algorithm */
	u_int8_t rsvd : 1; /* when set indicate restrictions for transmission */
};

struct wifi_hdr {
    struct frame_control frame_control;
    u_int16_t duration_id;
    u_int8_t addr1[6];
    u_int8_t addr2[6];
    u_int8_t addr3[6];
    u_int16_t sequence_control;
    u_int8_t addr4[6];
};