//
//  fonctions.h
//  TP3 - Mécanismes TCP
//
//  Created by Orsoni Antoine on 05/06/2015.
//  Copyright (c) 2015 Antoine ORSONI. All rights reserved.
//

#ifndef __TP3___Me_canismes_TCP__fonctions__
#define __TP3___Me_canismes_TCP__fonctions__

#include <stdio.h>
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

int connectTCP_SYN(int socketClient);

int connectTCP_SYNACK(int socketServeur, struct sockaddr_in *adClient, int taille);

#endif /* defined(__TP3___Me_canismes_TCP__fonctions__) */

