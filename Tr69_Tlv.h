#ifndef _TR69TLV_H_
#define _TR69TLV_H_

typedef struct _Tr69TlvData{
    char URL[256];
    char Username[50];
    char Password[128];
    int EnableCWMP;
    int Tr69Enable;
    int URLchanged;
    int FreshBootUp;
    char ConnectionRequestUsername[50];
    char ConnectionRequestPassword[128];
    int AcsOverRide;
	
}Tr69TlvData;

#endif
