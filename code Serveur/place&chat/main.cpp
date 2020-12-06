#include <SFML/Network.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sys/socket.h>

int main(int argc, char* argv[])
{
	//std::cout << "SERVER ONLINE with port :" << 53000 + atoi(argv[1]) << std::endl;
	srand(time(nullptr));
	sf::TcpListener listener;
	if(listener.listen(53000 + atoi(argv[1]))!= sf::Socket::Done)
	{
		exit(1);
	}
	std::string name1 = argv[2];
	std::string name2 = argv[3];
    std::vector<sf::TcpSocket*> clients;
    sf::SocketSelector selector;
    selector.add(listener);
    int continuer = 1;
    int nbrJoueur = 0;
    int temp;
    std::string chaine;
    int ID1, ID2, degats;
	int placeID;
    int nbrCarte, selec;
	int suppr = 0, indSuppr;
	int GAMEON = 0;
	int activePlayer = (rand()% (2 -1+1))+1;
	int ID;
	int size;
	sf::Packet actu;
    while(continuer == 1)
    {
		//std::cout << clients.size() << std::endl;
        if (selector.wait())
        {
            if (selector.isReady(listener) && nbrJoueur != 2) //permet l'arrivé des joueurs sur le serveur avant de commencer la partie
            {
                sf::TcpSocket* client = new sf::TcpSocket;
                if(listener.accept(*client) == sf::Socket::Done)
                {
                    clients.push_back(client);
                    nbrJoueur++;
                    sf::Packet paquet;
                    paquet << nbrJoueur;
                    selector.add(*client);
                    client->send(paquet);
					paquet.clear();
					paquet << activePlayer << name1 << name2;
					client->send(paquet);
                }
				else
				{
					delete client;
				}
            }
			else if(nbrJoueur == 2) //n'accepte plus de nouveau client et permet au joueur de jouer
            {
				GAMEON = 1;
                for(int i = 0 ; i < clients.size(); i++) //parcours les différents joueurs pour verifier si l'un deux fait quelque chose
                {
					sf::TcpSocket& client = *clients[i];
                    if(selector.isReady(client)) //verifie que le client est pret
                    {
                        sf::Packet paquet;
						sf::Socket::Status state = client.receive(paquet);  //recupere l'identificateur de données
                        if(state == sf::Socket::Done)
                        {
							paquet >> temp;
							sf::Packet realOne;
							client.receive(realOne); //recoie la donnée importante a traité
							if(activePlayer == 1)
							{	
								if(temp == 7)
								{
									clients[0]->send(paquet);
									clients[0]->send(realOne); //different cas ou l'on a bessoin de transferer des informations d'un joueur a un autre
									//ici il s'agit du changement de tour il faut donc prevenir les deux joueurs que c'est maintenant a qq d'autre de jouer
								}
								if(temp != 13)
								{
									clients[1]->send(paquet);
									clients[1]->send(realOne);
								}
							}
							else if(activePlayer == 2)
							{
								if(temp == 7)
								{
									clients[1]->send(paquet);
									clients[1]->send(realOne);
								}
								if(temp != 13)
								{
									clients[0]->send(paquet);
									clients[0]->send(realOne);
								}
							}
							if(temp == 9)
							{
								clients[0]->send(paquet);
								clients[1]->send(paquet);
								//arrete la partie
							}
							if(temp == 1)
							{
								clients[0]->send(paquet);
								clients[0]->send(realOne);
								clients[1]->send(paquet);
								clients[1]->send(realOne);
								//permet d'envoyer des messages sur le chat
							}
							if(temp == 13)
							{
								if(i == 0)
								{
									clients[1]->send(paquet);
									clients[1]->send(realOne);
									//permet d'utiliser la pioche
								}
								else if(i == 1)
								{
									clients[0]->send(paquet);
									clients[0]->send(realOne);
								}
							}
							
							switch(temp)
							{
								case 1:
								{
									realOne >> chaine; //recevoir un texte
									break;
								}
								case 2:
								{	
									realOne >> ID1 >> ID2 >> degats; //recevoir une attaque
									break;
								}
								case 3:
								{
									realOne >> nbrCarte;//nombre carte adversaire
									break;
								}
								case 4:
								{
									realOne >> selec;//carte selectionnee
									break;
								}
								case 5: //placer une carte
								{
									realOne >> placeID;
									break;
								}
								case 6:
								{
									//décés d'une carte
									break;
								}
								case 7:
								{
									realOne >> activePlayer;
									break;
								}
								case 9:
								{
									break;
								}
								case 10: //attaquer le joueur directement
								{
									realOne >> ID >> degats;
									break;
								}
								case 11:
								{
									break;
								}
								case 12:
								{
									break;
								}
								case 13:
								{
									break;
								}
								default:
								{
									std::cout << "erreur lors du choix de la reception" << std::endl;
									break;
								}
							}
						}
						else if(state == sf::Socket::Disconnected)
						{
							//std::cout << "deconnexion d'un client (game)" << std::endl;
							indSuppr = i;
							suppr = 1;
						}
                    }
                }
				if(suppr == 1)
				{
					selector.remove(*clients[indSuppr]); //supprime les clients qui se deconnecte
					clients[indSuppr]->disconnect();	
					delete clients[indSuppr];
					clients.erase(clients.begin()+indSuppr);
					suppr = 0;
					nbrJoueur--;
				}
            }
			if(clients.size()<2 && GAMEON == 1) //arrete la boucle infini
			{
				continuer = 0;
			}
        }
    }
	for(int i = 0 ; i < clients.size();i++) //deconnecte tous les clients
	{
		selector.remove(*clients[i]);
		clients[i]->disconnect();
	}
	listener.close();
	return 0; //retourne 0 si tout c'est bien passé et retourne 1 si quelque chose a planté
}
