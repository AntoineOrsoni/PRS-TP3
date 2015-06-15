all: client serveur

client: client.c fonctions.c
	gcc client.c fonctions.c -o client

serveur: serveur.c fonctions.c
	gcc serveur.c fonctions.c -o serveur

clean: 
	rm -rf *.o client serveur


