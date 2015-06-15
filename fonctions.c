//
//  fonctions.c
//  TP3 - Mécanismes TCP
//
//  Created by Orsoni Antoine on 05/06/2015.
//  Copyright (c) 2015 Antoine ORSONI. All rights reserved.
//

#include "fonctions.h"
#include "client.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/time.h>

int connectTCP_SYN(int socketClient) {
    
    struct sockaddr_in adServeur;
    adServeur.sin_family = AF_INET;
    adServeur.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    adServeur.sin_port = htons(1300);
    
    char charSyn[] = "SYN\n";
    
    sendto(socketClient, charSyn, sizeof(charSyn), 0, (struct sockaddr *)&adServeur, sizeof(adServeur));
    
    return 0;
}

int connectTCP_SYNACK(int socketServeur, struct sockaddr_in *adClient, int taille) {
    char charSynAck[] = "SYNACK\n";
    
    sendto(socketServeur, charSynAck, strlen(charSynAck), 0, (struct sockaddr *)&adClient, sizeof(adClient));
    
    return 0;
}

// Découper une phrase selon un déliminteur


