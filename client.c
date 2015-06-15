//
//  client.c
//  TP3 - Mécanismes TCP
//
//  Created by Orsoni Antoine on 05/06/2015.
//  Copyright (c) 2015 Antoine ORSONI. All rights reserved.
//

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
#include "fonctions.h"

int main(int argc, char**argv)
{
    int socketClientCrtl, socketClientData;
    long ouvertureCom;

    char phraseRecueClient[1000];
    char phraseEnvoyee[1000];
    char portServeurDataString[5];
    int portServeurDataInt;
    char synAck[7];
    socklen_t taille;
    
    // Variables temporaires
    int i, j;
    
    // Vérification du nombre d'arguments
    if (argc != 2)
    {
        printf("usage:  udpcli <IP address>\n");
        exit(1);
    }
    
    // Ouverture de la socket Client
    struct sockaddr_in adServeurCrtl;
    struct sockaddr_in adServeurData;
    
    socketClientCrtl = socket(AF_INET, SOCK_DGRAM, 0);
    socketClientData = socket(AF_INET, SOCK_DGRAM, 0);
    
    // Crtl
    bzero(&adServeurCrtl,sizeof(adServeurCrtl));

    adServeurCrtl.sin_family = AF_INET;
    adServeurCrtl.sin_addr.s_addr = inet_addr(argv[1]);
    adServeurCrtl.sin_port = htons(5400);
    
    
    // Data
    bzero(&adServeurData,sizeof(adServeurData));
    
    adServeurData.sin_family = AF_INET;
    adServeurData.sin_addr.s_addr = inet_addr(argv[1]);
    
    
    
    taille = sizeof(adServeurCrtl);
    
    // ---------   Envoi du SYN au Serveur -------
    printf("--------------------------------------------------\n");
    printf("Socket: %d, Adresse: %d, Port: %d\n", socketClientCrtl, adServeurCrtl.sin_addr.s_addr, adServeurCrtl.sin_port);
    printf("--------------------------------------------------\n");

    char charSyn[] = "SYN\n";
    sendto(socketClientCrtl, charSyn, sizeof(charSyn), 0, (struct sockaddr *)&adServeurCrtl, taille);
        
    
    
    // -------- Réception du SYN ACK--------
    ouvertureCom = recvfrom(socketClientCrtl, phraseRecueClient, 1000, 0, (struct sockaddr *)&adServeurCrtl, &taille);
    
    // J'envoie l'ACK au serveur
    sendto(socketClientCrtl, "ACK\n", ouvertureCom+3, 0, (struct sockaddr *)&adServeurCrtl, sizeof(adServeurCrtl));
    phraseRecueClient[ouvertureCom] = 0;
    
    
    // Récupération du SYNACK
    for(i = 0; i < 6; i++) {
        synAck[i] = phraseRecueClient[i];
    }
    
    
    // Récupération du portServeurData
    i = 0;
    for(j = 6; j < 10; j++) {
        portServeurDataString[i] = phraseRecueClient[j];
        i++;
    }
    
    // Conversion en entier, puis en langage "réseau -> humain"
    portServeurDataInt = atoi(portServeurDataString);
    adServeurData.sin_port = portServeurDataInt;

    
    
    if(strcmp(synAck, "SYNACK") == 0) {
        printf("SYN ACK du serveur recu !\n");
    }
    else {
        printf("SYN ACK du serveur non recu !\n");
        printf("phraseRecue = %s\n", phraseRecueClient);
    }
    // -------- Fin réception du SYN ACK -------
    
    
    
    while (fgets(phraseEnvoyee, 10000, stdin) != NULL)
    {
        sendto(socketClientData, phraseEnvoyee, strlen(phraseEnvoyee), 0, (struct sockaddr *)&adServeurData, sizeof(adServeurData));
        
        //Servira pour l'ACK ensuite
        //ouvertureCom = recvfrom(socketClientData, phraseEnvoyee, 10000, 0, NULL, NULL);
        
        phraseEnvoyee[ouvertureCom] = 0;
        //fputs(phraseEnvoyee,stdout);
    }
}