//
//  serveur.c
//  TP3 - Mécanismes TCP
//
//  Created by Orsoni Antoine on 05/06/2015.
//  Copyright (c) 2015 Antoine ORSONI. All rights reserved.
//

#include "serveur.h"
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include "fonctions.h"

int main(int argc, char**argv)
{
    int socketServeurCrtl, socketServeurData;
    long ouvertureCom;
    struct sockaddr_in adServeurCrtl,adServeurData,adClient;
    socklen_t taille = sizeof(adClient);
    char phraseRecue[1000];
    char phraseCombinee[11];
    
    // On vide le contenue de phraseRecue
    bzero(&phraseRecue, sizeof(phraseRecue));
    
    socketServeurCrtl = socket(AF_INET,SOCK_DGRAM,0);
    socketServeurData = socket(AF_INET,SOCK_DGRAM,0);
    
    
    // Socket CONTROLE
    adServeurCrtl.sin_family = AF_INET;
    adServeurCrtl.sin_addr.s_addr = htonl(INADDR_ANY);
    adServeurCrtl.sin_port = htons(5400);
    

    if(bind(socketServeurCrtl,(struct sockaddr *)&adServeurCrtl,sizeof(adServeurCrtl)) == -1) {
        printf("Erreur dans le bind socketServeurCrtl \n");
    }
    
    printf("--------------------------------------------------\n");
    printf("Socket: %d, Adresse: %d, Port: %d\n", socketServeurCrtl, adServeurCrtl.sin_addr.s_addr, adServeurCrtl.sin_port);
    printf("--------------------------------------------------\n");
    
    // Socket DATA
    adServeurData.sin_family = AF_INET;
    adServeurData.sin_addr.s_addr = htonl(INADDR_ANY);
    adServeurData.sin_port = htons(1301);
    
    if(bind(socketServeurData,(struct sockaddr *)&adServeurData,sizeof(adServeurData)) == -1) {
        printf("Erreur dans le bind socketServeurData \n");
    }
    
    
    
    // -------- Création du SYNACK Combiné -----
    sprintf(phraseCombinee, "%s%d", "SYNACK", adServeurData.sin_port);
    
    
    // -------- Réception du SYN --------
    ouvertureCom = recvfrom(socketServeurCrtl, phraseRecue, sizeof(phraseRecue), 0, (struct sockaddr *)&adClient, &taille);
    sendto(socketServeurCrtl, phraseCombinee, sizeof(phraseCombinee), 0, (struct sockaddr *)&adClient, sizeof(adClient));
    phraseRecue[ouvertureCom] = 0;
    
    if(strcmp(phraseRecue, "SYN\n") == 0) {
        printf("SYN du client recu !\n");
    }
    else {
        printf("SYN du client non recu !\n");
        printf("phraseRecue = %s\n", phraseRecue);
    }
    // -------- Fin réception du SYN -------
    
    
    
    // -------- Réception du SYN_ACK --------
    connectTCP_SYNACK(socketServeurCrtl, &adClient, taille);
    // ---------- Fin du SYN_ACK ----------
    
    

    // ------- Réception du ACK -------
    ouvertureCom = recvfrom(socketServeurCrtl, phraseRecue, 1000, 0, (struct sockaddr *)&adClient, &taille);
    phraseRecue[ouvertureCom] = 0;
    
    if(strcmp(phraseRecue, "ACK\n") == 0) {
        printf("ACK du client recu !\n");
    }
    else {
        printf("ACK du client non recu !\n");
        printf("phraseRecue = %s\n", phraseRecue);
    }
    // ------- Fin du ACK -------
    
    
    
    strcpy(phraseRecue, "");
    
    for (;;)
    {
        taille = sizeof(adClient);
        //ouvertureCom = recvfrom(socketServeurData, phraseRecue, 1000, 0, (struct sockaddr *)&adClient, &taille);
        
        // Servira pour l'ACK ensuite
        //sendto(socketServeurData, phraseRecue, ouvertureCom, 0, (struct sockaddr *)&adClient, sizeof(adClient));
        
        
            
        ouvertureCom = recvfrom(socketServeurData, phraseRecue, 1000, 0, (struct sockaddr *)&adClient, &taille);
        printf("-------------------------------------------------------\n");
        phraseRecue[ouvertureCom] = 0;
        printf("Phrase reçue : \n");
        printf("%s", phraseRecue);
        printf("-------------------------------------------------------\n");
    
        
            
        
        
        
        
        
        
        /*
        
        printf("-------------------------------------------------------\n");
        phraseRecue[ouvertureCom] = 0;
        printf("Phrase reçue : \n");
        printf("%s", phraseRecue);
        printf("-------------------------------------------------------\n");
        */
        
        
        
    }
    
}

