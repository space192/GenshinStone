#include "lib.h"

void serveurInvitAndChat(int *continuer, int *limits);

int main()
{
	srand(time(0));
    sf::TcpListener listener;
    if(listener.listen(53000) != sf::Socket::Done) //ouverture du port d'écoute pour le serveur
	{
		exit(1);
	}
    sf::SocketSelector selector;
    selector.add(listener);
    std::vector<Users> clients;
	std::vector<Users> attente;
	std::vector<sf::Thread*> thread;
	std::map<std::string, int> onlinePlayer;
	std::map<std::string, int>::iterator finder;
	std::vector<int> deck;
	sf::TcpSocket testclient;
	int tempDeck;
	int tempPort;
	std::string recepCommand;
	std::string standardError;
    int suppr = 0, temp, indSuppr;
    std::string identifiant, mdp = "";
    int jour, mois, annee, success = 0, taille;
    std::string loginpsswd, foldername = "users/", folderSave = "users/", tempCMD, friends;
    FILE *account;
    FILE *cAccount;
	FILE *number;
    sf::Packet message;
    int LOGIN;
	int inQueue = 0;
	int menuAmi, nbFriend;
	char tempFriends[100];
	int accept;
	struct stat info;
	int search = 0;
	int tempoSize;
	int limit = 10;
	int continuer = 1;
	int nbEnergie = 10;
	int identificateurDeck = 0, IDdeck, boucleDeck;
    std::string key = "CECI EST UN TEST";
	sf::Thread saisie(std::bind(&interaction_thread , &tempoSize,&inQueue, &continuer, &limit, &nbEnergie));
	saisie.launch();
	sf::Thread alternative(std::bind(&serveurInvitAndChat, &continuer, &limit));
	alternative.launch();
    while(continuer == 1)
    {
		tempoSize = clients.size();
        if(selector.wait() && continuer == 1) //detection d'un evenemment sur le reseau
        {
            if(selector.isReady(listener)) //cas ou un nouveau client se connecte au serveur
            {
                sf::TcpSocket* client = new sf::TcpSocket;
                if(listener.accept(*client) == sf::Socket::Done)
                {
                    clients.push_back(Users());
					clients.back().client = client;
                    selector.add(*client);
                }
                else
                {
                    delete client;
                }
            }
            else
            {
                for(int i =0 ; i < clients.size(); i++) //parcours des joueurs
                {
                    sf::TcpSocket& client = *clients[i].client;
                    if(selector.isReady(client) && continuer == 1) //verification qu'un client est pret
                    {
                        sf::Packet paquet;
                        sf::Socket::Status state = client.receive(paquet);
                        if(state == sf::Socket::Done) //verifie que l'identificateur de données est bien arrivé
                        {
                            paquet >> temp >> LOGIN;
                            if(LOGIN == 0) //verification que le joueur est LOGIN ou pas
                            {
                                sf::Packet RealOne;
                                client.receive(RealOne); //attend la reception des informations reel pour le jeu
                                switch(temp)
                                {
                                case 1: //connexion a un compte deja existant
                                {
									foldername = "users/";
                                    RealOne >> identifiant >> mdp;
									loginpsswd = foldername;
                                    loginpsswd += identifiant;
									loginpsswd += "/";
									loginpsswd += identifiant;
                                    loginpsswd += ".sav";
                                    account = fopen(loginpsswd.c_str(), "rb");
                                    if(account)
                                    {
                                        fread((void *)&taille, 1, sizeof(int), account);
                                        char testmdp[taille];
                                        fread((void *)&testmdp, 1, taille, account);
                                        if(testmdp == encrypt(mdp, key))
                                        {
                                            success = 1;
											clients[i].username = identifiant;
											onlinePlayer.insert(std::pair<std::string, int>(identifiant, i));
                                        }
                                        else
                                        {
                                            success = 2;
                                        }
                                        fclose(account);
                                    }
                                    else
                                    {
                                        success = 4;
                                    }
                                    break;
                                }
                                case 2: // creation d'un nouveau compte sur le serveur
                                {
									foldername = "users/";
                                    RealOne >> identifiant >> mdp >> jour >> mois >> annee;
                                    loginpsswd.clear();
									foldername += identifiant;
									tempCMD = "mkdir ";
									tempCMD += foldername;
									if(system(tempCMD.c_str()) == -1) //creation du dossier pour le joueur
									{
									}
									folderSave = foldername;
									folderSave += "/";
									folderSave += identifiant;                       //folderSave est le string qui contient la sauvegarde principale
                                    folderSave += ".sav";							//foldername est gardé intact pour creer la liste d'amis et le deck
                                    account  = fopen(folderSave.c_str(),"r");  //ouverture du fichier pour le créer puis fermeture instantanée
                                    if(account) 
                                    {
                                        fclose(account);
                                        //le compte existe deja :/
                                        success = 3;
                                    }
                                    else
                                    {
                                        cAccount = fopen(folderSave.c_str(), "awb"); //creation du compte en enregistrant les différentes informations
                                        if(cAccount)
                                        {
                                            mdp = encrypt(mdp, key);
                                            int taille2 = sizeof(mdp)+1;
                                            fwrite((const void *)&taille2,1, sizeof(int), cAccount);
                                            fwrite((const void *)mdp.c_str(),1, sizeof(mdp)+1, cAccount);
                                            fwrite((const void *)&jour,1, sizeof(int), cAccount);
                                            fwrite((const void *)&mois,1, sizeof(int), cAccount);
                                            fwrite((const void *)&annee,1, sizeof(int), cAccount);
                                            fclose(cAccount);
                                            success = 6;
                                        }
                                        else
                                        {
                                            success = 5;
                                        }
										folderSave = "";
										folderSave = foldername;
										folderSave += "/";
										folderSave += "friend_list.sav";
										cAccount = fopen(folderSave.c_str(), "awb");
										if(cAccount)
										{
											fclose(cAccount);
										}
										folderSave = "";
										folderSave = foldername;
										folderSave += "/friend_request.sav";
										cAccount = fopen(folderSave.c_str(), "awb");
										if(cAccount)
										{
											fclose(cAccount);
										}
										folderSave = "";
										folderSave = foldername;
										folderSave += "/nbFriend_request.sav";
										cAccount = fopen(folderSave.c_str(), "w");
										if(cAccount)
										{
											fprintf(cAccount, "0");
											fclose(cAccount);
										}
										folderSave = "";
										folderSave = foldername;
										folderSave += "/nbFriend.sav";
										cAccount = fopen(folderSave.c_str(), "w");
										if(cAccount)
										{
											fprintf(cAccount, "0");
											fclose(cAccount);
										}
                                    }
                                    break;
                                }
                                }
                                message << success;
                                client.send(message);
                                message.clear();
                            }
                            else if(LOGIN == 1) //cas ou le joueur est bien connecté
                            {
                                switch(temp)
                                {
                                case 1: //rejoindre une partie
                                    {
										sf::Packet RealOne;
										client.receive(RealOne);
										inQueue++;
										attente.push_back(Users());
										attente.back().client = clients[i].client;
										attente.back().username = clients[i].username; //ajoute le joueur a la queue pour pouvoir acceder a une game
										RealOne >> attente.back().ID;
										if(inQueue >= 2 && nbServ < limit) //si il y'a plus de deux joueur dans la queue on permet au joueur de rejoindre une partie
										{
											nbServ++;
											tempPort = nbServ;
											sf::Packet tempnbServ;
											for(int i = 0 ; i < 2; i++)
											{
												foldername = "users/";
												foldername += attente[i].username;
												foldername += "/";
												foldername += std::to_string(attente[i].ID);
												foldername += ".sav";
												account = fopen(foldername.c_str(), "rb");
												if(account)
												{
													for(int i = 0 ; i < 25 ; i++)
													{
														fread((void*)&tempDeck, 1, sizeof(int), account); //met les cartes du deck du joueur dans un vecteur de deck
														deck.push_back(tempDeck);
													}
													for(int i = 0 ; i < nbEnergie ;i++)
													{
														deck.push_back(18);
														deck.push_back(19);
														deck.push_back(20); //rajoute les cartes énergies par rapport a la configuration actuel du serveur
														deck.push_back(21);
													}
													std::random_shuffle(std::begin(deck), std::end(deck)); //melange le deck
													tempnbServ << tempPort << (int) deck.size(); //previent le client du nombre de carte qui va arriver
													for(int i = 0 ; i < deck.size(); i++) //met les cartes dans le paquet
													{
														tempnbServ << deck[i];
													}
													attente[i].client->send(tempnbServ); //envoie le tout au client
													tempnbServ.clear();
													fclose(account);
													deck.clear();
												}
											}
											inQueue-=2; //on enleve ces deux joueurs de la queue
											tempnbServ.clear();
											if(attente[0].username != attente[1].username)//on verifie qu'il ne s'agit pas d'un bug coté client
											{
												thread.push_back(new sf::Thread(std::bind(&launch_server, tempPort, attente[0].username, attente[1].username))); //on creer le lobby de la partie
												thread.back()->launch(); //on lance le serveur dédié pour la partie
											}
											attente.erase(attente.begin());
											attente.erase(attente.begin());
											for(int i = 0 ; i < thread.size(); i++)
											{
												if(thread[i] == nullptr)
												{
													thread.erase(thread.begin() +i--); //on vérifie si une partie est terminé et si c'est le cas on supprime la partie en cours
												}
											}
										}
                                        break;
                                    }
                                case 2: //acceder au deck
                                    {
										sf::Packet numDeck;
										client.receive(numDeck);
										numDeck >> IDdeck;
										switch(IDdeck)
										{
											case 1: //creer un deck 
											{
												numDeck.clear();
												client.receive(numDeck);
												numDeck >> identificateurDeck;
												foldername = "users/";
												foldername += clients[i].username;
												foldername += "/";
												foldername += std::to_string(identificateurDeck);
												foldername += ".sav";
												numDeck.clear();
												client.receive(paquet);
												account  = fopen(foldername.c_str(),"wb+");
												if(account)
												{
													paquet >> boucleDeck;
													for(int i = 0 ; i < boucleDeck ; i++)
													{
														paquet >> identificateurDeck;
														fwrite((const void*)&identificateurDeck, 1, sizeof(int), account);
													}
													fclose(account);
												}
												break;
											}
											case 2: //envoyer le deck
											{
												numDeck.clear();
												foldername = "users/";
												foldername += clients[i].username;
												foldername += "/";
												folderSave = foldername;
												for(int i = 0 ; i < 4 ; i++)
												{
													foldername = folderSave;
													foldername += std::to_string(i);
													foldername += ".sav";
													account = fopen(foldername.c_str(), "rb");
													if(account)
													{
														numDeck << 1;
														fclose(account);
													}
													else
													{
														numDeck << 0;
													}
												}
												client.send(numDeck);
												break;
											}
										}
                                        break;
                                    }
								case 3: //gestion des amis
									{
										sf::Packet tempMenuAmi;
										client.receive(tempMenuAmi);
										tempMenuAmi >> menuAmi;
										foldername = "Users/";
										foldername += clients[i].username;
										foldername += "/";
										foldername += "friend_list.sav";
										switch(menuAmi)
										{
											case 1: //afficher la liste des amis
											{
												affichageAmi(clients[i].username, clients[i].client);
												break;
											}
											case 2: //ajouter un amis
											{
												sf::Packet FriendName;
												client.receive(FriendName);
												FriendName >> friends;
												FriendName.clear();
												if(ajouterAmi(clients[i].username, friends) == 1)
												{
													FriendName << 1;
												}
												else
												{
													FriendName << 0;
												}
												client.send(FriendName);
												break;
											}
											case 3: //afficher les requetes d'amis
											{
												sf::Packet request;
												folderSave = "users/";
												folderSave += clients[i].username;
												folderSave += "/friend_request.sav";
												cAccount  = fopen(folderSave.c_str(), "rb");
												if(cAccount)
												{
													folderSave = "users/";
													folderSave += clients[i].username;
													folderSave += "/nbFriend_request.sav";
													number = fopen(folderSave.c_str(), "r+");
													if(number)
													{
														fscanf(number, "%d", &nbFriend);
														request << nbFriend;
														client.send(request);
														request.clear();
														for(int i = 0 ; i < nbFriend ; i++)
														{
															taille = 0;
															fread((void *)&taille, 1, sizeof(int), cAccount);
															fread((void *)&tempFriends, 1, taille, cAccount);
															request << tempFriends;
															client.send(request);
															request.clear();
														}
														fclose(number);
													}
													fclose(cAccount);
												}
												break;
											}
											case 4: //accepter les requetes
											{
												sf::Packet FriendName;
												client.receive(FriendName);
												FriendName >> friends >> accept;
												folderSave = "users/";
												folderSave += friends;
												FriendName.clear();
												if(stat(folderSave.c_str(), &info) == 0)
												{
													FriendName << accept_friend(clients[i].username, friends, accept);
													client.send(FriendName);
													FriendName.clear();
												}
												break;
											}
											case 5: //supprimer un amis
											{
												sf::Packet reussi;
												sf::Packet FriendName;
												client.receive(FriendName);
												FriendName >> friends;
												folderSave = "users/";
												folderSave += friends;
												if(stat(folderSave.c_str(), &info) == 0)
												{
													if(retirerAmi(clients[i].username, friends))
													{
														if(retirerAmi(friends, clients[i].username))
														{
															reussi << 1;
														}
													}
													else
													{
														reussi << 0;
													}
												}
												else
												{
													reussi << 0;
												}
												client.send(reussi);
												break;
											}
											case 6: //proposer de jouer
											{
												sf::Packet FriendName;
												std::string searchName;
												client.receive(FriendName);
												FriendName >> searchName;
												finder = onlinePlayer.find(searchName);
												if(finder != onlinePlayer.end())
												{
													sf::Packet identificateur;
													identificateur << 7;
													clients[i].client->send(identificateur);
													identificateur.clear();
												}
												break;
											}
											case 7:
											{
												sf::Packet FriendName;
												std::string searchName;
												client.receive(FriendName);
												FriendName >> searchName;
												FriendName.clear();
												finder = onlinePlayer.find(searchName);
												if(finder != onlinePlayer.end())
												{
													FriendName << 1;
												}
												else
												{
													FriendName << 0;
												}
												clients[i].client->send(FriendName);
												break;
											}
										}
									}
								case 4://Quitter la queue
									{
										search = -1;
										for(int i = 0 ; i < attente.size();i++)
										{
											if(clients[i].client == attente[i].client)
											{
												search = i;
												i = attente.size();
											}
										}
										if(search != -1)
										{
											attente.erase(attente.begin()+search);
											inQueue--;
											//std::cout << "COUCOU " << inQueue << std::endl;
										}
										break;
									}
                                }
                            }
                        }
                        else if(state == sf::Socket::Disconnected)
                        {
                            //std::cout << "deconnexion d'un client" << std::endl;
                            indSuppr = i;
                            suppr = 1;
                        }
                    }
                }
                if(suppr == 1)
                {
                    selector.remove(*clients[indSuppr].client); //dans le cas de la deconnexion d'un client on le supprime de la liste a surveillé
					clients[indSuppr].client->disconnect();
					onlinePlayer.erase(clients[indSuppr].username);
                    delete clients[indSuppr].client;
                    clients.erase(clients.begin()+indSuppr);
                    suppr = 0;
                }
            }
        }
    }
	for(int i = 0 ; i < clients.size();i++) //suppression de tous les clients a la fin de la partie
	{
		selector.remove(*clients[i].client);
		clients[i].client->disconnect();
	}
	listener.close();
	saisie.terminate();
	alternative.terminate();
}

void affichageAmi(std::string user, sf::TcpSocket* client)
{
	//permet d'envoyer au client la liste d'amis sur le jeu
	//on ouvre le fichier du joueur et on recupere tous les noms des amis
	//on recupere aussi le nombre d'amis dans un autre fichier
	FILE* fp;
	std::string temp;
	int nbFriend;
	sf::Packet amitie;
	char tempString[100];
	int taille;
	std::string userWay = "users/";
	userWay += user;
	userWay += "/nbFriend.sav";
	fp = fopen(userWay.c_str(), "r");
	if(fp)
	{
		fscanf(fp, "%d", &nbFriend);
		fclose(fp);
	}
	amitie << nbFriend;
	client->send(amitie);
	amitie.clear();
	userWay = "users/";
	userWay += user;
	userWay += "/friend_list.sav";
	fp = fopen(userWay.c_str(), "rb");
	if(fp)
	{
		for(int i = 0 ; i < nbFriend ; i++)
		{
			fread((void *) &taille, 1, sizeof(int), fp);
			fread((void *) &tempString, 1, taille, fp);
			amitie << tempString;
			client->send(amitie);	
			amitie.clear();
		}
		fclose(fp);
	}
}

int ajouterAmi(std::string user, std::string friendName)
{
	//on recupere le nom du joueur qui demande l'amis et le nom du joueur qui va recevoir la demande d'amis afin de la stocker dans les fichiers pour que le joueur puisse accepter ou refuser quand il sera connecté
	//on verifie aussi que le joueur en question existe avant de commmencer a faire des modifications
	FILE *cAccount;
	FILE *number;
	int nbFriend, taille, tailleUsername, SPAM = 0;
	struct stat info;
	std::string folderSave = "users/";
	folderSave += friendName;
	char tempFriends[100];
	if(stat(folderSave.c_str(), &info) != 0)
	{
		return 0;
	}
	else
	{
		folderSave += "/friend_request.sav";
		cAccount = fopen(folderSave.c_str(), "rb+");
		if(cAccount)
		{
			folderSave = "users/";
			folderSave += friendName;
			folderSave += "/nbFriend_request.sav";
			number = fopen(folderSave.c_str(), "r+");
			if(number)
			{
				SPAM = 0;
				fscanf(number, "%d", &nbFriend);
				for(int i = 0 ; i < nbFriend ; i++)
				{
					taille = 0;
					fread((void *)&taille, 1, sizeof(int), cAccount);
					fread((void *)&tempFriends, 1, taille, cAccount);
					if(user == tempFriends)
					{
						SPAM = 1;
					}
				}
				if(SPAM == 0)
				{
					tailleUsername = sizeof(user);
					fwrite((const void *)&tailleUsername,1, sizeof(int), cAccount);
					fwrite((const void *)user.c_str(),1, sizeof(user), cAccount);
					nbFriend++;
				}
				fclose(number);
			}
			number = fopen(folderSave.c_str(), "w+");
			if(number)
			{
				fprintf(number, "%d", nbFriend);
				fclose(number);
			}
			fclose(cAccount);
			return 1;
		}
		return 0;
	}
}

int retirerAmi(std::string user, std::string friendName)
{
	//permet de supprimer un amis de sa liste d'amis
	FILE *fp;
	FILE *fp_tempo;
	FILE *number;
	int verif = 0;
	int nbFriend=0, taille;
	std::string userWay = "users/";
	std::string friendFileWay;
	userWay += user;
	std::string temp = userWay;
	temp += "/temp.sav";
	userWay += "/friend_list.sav";
	fp = fopen(userWay.c_str(), "rb");
	fp_tempo = fopen(temp.c_str(), "awb");
	userWay = "users/";
	userWay += user;
	userWay +="/nbFriend.sav";
	number = fopen(userWay.c_str(), "r");
	char tempString[100];
	if(number)
	{
		fscanf(number, "%d", &nbFriend);
		fclose(number);
	}
	if(fp)
	{
		if(fp_tempo)
		{
			for(int i = 0 ; i < nbFriend ; i++)
			{
				taille = 0;
				fread((void *)&taille, 1, sizeof(int), fp);
				fread((void *)&tempString, 1, taille, fp);
				if(friendName != tempString)
				{
					fwrite((const void *)&taille,1, sizeof(int), fp_tempo);
					fwrite((const void *)tempString,1, taille, fp_tempo);
				}
				else
				{
					verif = 1;
				}
			}
			fclose(fp);
			fclose(fp_tempo);
			userWay = "users/";
			userWay += user;
			userWay += "/friend_list.sav";
			friendFileWay = userWay;
			remove(userWay.c_str());
			userWay = "users/";
			userWay += user;
			userWay += "/temp.sav";
			rename(userWay.c_str(), friendFileWay.c_str());
			if(verif == 1)
			{
				userWay = "users/";
				userWay += user;
				userWay += "/nbFriend.sav";
				number = fopen(userWay.c_str(), "w+");
				if(number)
				{
					nbFriend--;
					fprintf(number, "%d", nbFriend);
					fclose(number);
				}
			}
		}
	}
	if(verif == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int accept_friend(std::string user, std::string friendName, int accept)
{
	//permet d'accepter ou de refuser une demande d'amis en modifiant le fichier de la personne qui fait la demande ainsi que le fichier de la personne qui recoit la demande d'amis
	//on fait aussi décroitre le nombre de demande d'amis stocker dans un fichier
	//et finalement on fait croitre le nombre d'amis des deux cotés dans le cas ou le joueur accepte la demande d'amis
	std::string userFileWay = "users/";
	userFileWay += user;
	userFileWay += "/friend_list.sav";
	std::string friendFileWay = "users/";
	friendFileWay += friendName;
	friendFileWay += "/friend_list.sav";
	std::string nbFriendF;
	int tailleUsername = 0;
	int nbRequest;
	int taille;
	int nbFriendRequest;
	int nbFriend;
	FILE* fp; 
	FILE* fp_temporaire;
	FILE* number;
	char tempFriends[100];
	if(accept == 1)
	{
		fp = fopen(userFileWay.c_str(), "awb");
		if(fp)
		{
			tailleUsername = sizeof(friendName);
			fwrite((const void *)&tailleUsername,1, sizeof(int), fp);
			fwrite((const void *)friendName.c_str(),1, sizeof(friendName), fp);
			fclose(fp);
		}
		fp = fopen(friendFileWay.c_str(), "awb");
		if(fp)
		{
			tailleUsername = sizeof(user);
			fwrite((const void *)&tailleUsername,1, sizeof(int), fp);
			fwrite((const void *)user.c_str(),1, sizeof(user), fp);
			fclose(fp);
		}
		nbFriendF = "users/";
		nbFriendF += user;
		nbFriendF += "/nbFriend.sav";
		number = fopen(nbFriendF.c_str(), "r");
		if(number)
		{
			fscanf(number, "%d", &nbFriend);
			fclose(number);
		}
		number = fopen(nbFriendF.c_str(), "w+");
		if(number)
		{
			nbFriend++;
			fprintf(number, "%d", nbFriend);
			fclose(number);
		}
		nbFriendF = "users/";
		nbFriendF += friendName;
		nbFriendF += "/nbFriend.sav";
		number = fopen(nbFriendF.c_str(), "r");
		if(number)
		{
			fscanf(number, "%d", &nbFriend);
			fclose(number);
		}
		number = fopen(nbFriendF.c_str(), "w+");
		if(number)
		{
			nbFriend++;
			fprintf(number, "%d", nbFriend);
			fclose(number);
		}
	}
	userFileWay = "users/";
	userFileWay += user;
	userFileWay += "/nbFriend_request.sav";
	fp = fopen(userFileWay.c_str(), "r");
	if(fp)
	{
		fscanf(fp, "%d", &nbFriendRequest);
		fclose(fp);
	}
	userFileWay = "users/";
	userFileWay += user;
	userFileWay += "/friend_request.sav";
	fp = fopen(userFileWay.c_str(), "rb");
	userFileWay = "users/";
	userFileWay += user;
	userFileWay += "/temp.sav";
	fp_temporaire = fopen(userFileWay.c_str(), "wb");
	if(fp)
	{
		if(fp_temporaire)
		{
			taille = 0;
			for(int i = 0 ; i < nbFriendRequest ; i++)
			{
				fread((void *)&taille, 1, sizeof(int), fp);
				fread((void *)&tempFriends, 1, taille, fp);
				if(friendName != tempFriends)
				{
					fwrite((const void *)&taille,1, sizeof(int), fp_temporaire);
					fwrite((const void *)tempFriends,1, taille, fp_temporaire);
				}
			}
			fclose(fp);
			fclose(fp_temporaire);
			userFileWay = "users/";
			userFileWay += user;
			userFileWay += "/friend_request.sav";
			friendFileWay = userFileWay;
			remove(userFileWay.c_str());
			userFileWay = "users/";
			userFileWay += user;
			userFileWay += "/temp.sav";
			rename(userFileWay.c_str(), friendFileWay.c_str());
			userFileWay = "users/";
			userFileWay += user;
			userFileWay +="/nbFriend_request.sav";
			number = fopen(userFileWay.c_str(), "r");
			if(number)
			{
				fscanf(number, "%d", &nbRequest);
				nbRequest--;
				fclose(number);
			}
			number = fopen(userFileWay.c_str(), "w+");
			if(number)
			{
				fprintf(number, "%d", nbRequest);
				fclose(number);
			}
		}
	}
	if(accept == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


void launch_server(int number, std::string &nomJ1, std::string &nomJ2)
{
	int temp;
	std::string chaine = "sudo /home/arthur/code/'place&chat'/./sfml-app "; //permet de lancer une partie
	chaine += std::to_string(number);
	chaine += " ";
	chaine += nomJ1; //on envoie trois parmetres au main de ce lobby, le premier est le port sur lequel le client va devoir se connecter, le deuxieme est le nom du joueur 1 et le 3eme et le nom du joueur 2
	chaine += " ";
	chaine += nomJ2;
	temp = system(chaine.c_str());
	if(temp != 0)
	{
		std::cout << "erreur SERVEUR DE JEU" << std::endl;
	}
	nbServ--;
	//std::cout << nbServ << std::endl;
}


void interaction_thread(int *size,int *queue,int *continuer, int *limit, int *energie)
{
	//permet de changer les parametres des parties sur le serveur en permettant une interaction avec la personne possedant le serveur
	std::string saisie;
	int choix;
	while(1)
	{
		std::cin >> saisie;
		if(saisie == "/help")
		{
			std::cout << "/online pour obtenir le nombre de joueur en ligne" << std::endl;
			std::cout << "/onlineServ pour obtenir le nombre de serveur en ligne" << std::endl;
			std::cout << "/onlineQueue pour obtenir le nombre de serveur en ligne" << std::endl;
			std::cout << "/limit pour modifier le nombre de serveur maximum" << std::endl;
			std::cout << "/energie pour modifier le nombre d'énergie que l'on va placer dans le deck du joueur" << std::endl;
			std::cout << "/stop pour arreter le serveur" << std::endl;
			std::cout << "/about pour obtenir plus d'informations sur le jeu" << std::endl;
		}
		else if(saisie == "/online")
		{
			std::cout << "il y a " << *size << "en ligne actuellement" << std::endl;
		}
		else if(saisie == "/onlineServ")
		{
			std::cout << "il y a " << nbServ << "de partie en cours" << std::endl;
		}
		else if(saisie == "/onlineQueue")
		{
			std::cout << "il y a " << *queue << "de joueur en attente de partie" << std::endl;
		}
		else if(saisie == "/limit")
		{
			std::cout << "la limite actuelle est de " << *limit << "voulez vous la modifier ?" << std::endl << "1.oui" << std::endl << "2.non" << std::endl;
			while(!(std::cin >> choix))
            {
                std::cin.clear();
                std::cin.ignore(INT_MAX, '\n');
            }
			if(choix == 1)
			{
				while(!(std::cin >> choix) && choix < 0)
				{
                std::cin.clear();
                std::cin.ignore(INT_MAX, '\n');
				}
				*limit = choix;
			}
		}
		else if(saisie == "/stop")
		{
			*continuer = 0;
		}
		else if(saisie == "/about")
		{
			std::cout << "Serveur du projet ECEmon ING2 en C++, il s'agit d'un projet étudiant" << std::endl;
			std::cout << "lien du Github : https://github.com/space192/Projet-S1-ING2" << std::endl;
		}
		else if(saisie == "/energie")
		{
			std::cout << "il y a actuellement " << *energie << "dans le deck des joueurs" <<"voulez vous la modifier ?" << std::endl << "1.oui" << std::endl << "2.non" << std::endl;
			while(!(std::cin >> choix))
			{
				std::cin.clear();
				std::cin.ignore(INT_MAX, '\n');
			}
			if(choix == 1)
			{
				while(!(std::cin >> choix) && choix < 0)
				{
					std::cin.clear();
					std::cin.ignore(INT_MAX, '\n');
				}
				*energie = choix;
			}
		}
		else
		{
			std::cout << "entrer /help pour obtenir toute les commandes !" << std::endl;
		}
	}
}

void serveurInvitAndChat(int *continuer, int *limits)
{
	//feature non implementé sur le coté client il permet au client d'envoyer des messages privé a un de ses amis, et de lui proposer de jouer avec lui pour faire des parties privés
	int identificateur;
	sf::TcpListener listener;
	listener.listen(52999);
	sf::SocketSelector selector;
	selector.add(listener);
	std::vector<Users> clients;
	std::vector<sf::Thread*> thread;
	std::map<std::string, sf::TcpSocket*> onlineClients;
	std::map<std::string, sf::TcpSocket*>::iterator finder;
	std::map<std::string, sf::TcpSocket*>::iterator finder2;
	sf::Packet ID, data, tempnbServ;
	std::string foldername;
	int nbrClients = 0;
	int indSuppr, suppr = 0;
	std::string player, message;
	std::string players[2];
	int acceptation;
	while (*continuer == 1)
	{
		if(selector.wait())
		{
			if(selector.isReady(listener))
			{
				sf::TcpSocket* client = new sf::TcpSocket;
                if(listener.accept(*client) == sf::Socket::Done)
                {
					data.clear();
                    clients.push_back(Users());
					clients.back().client = client;
                    selector.add(*client);
					client->receive(data); //recoie le login du joueur
					data >> clients.back().username;
					onlineClients.insert(std::pair<std::string, sf::TcpSocket*>(clients.back().username, clients.back().client));
					nbrClients++;
                }
                else
                {
                    delete client;
                }
			}
			else
			{
				for(int i =0 ; i < clients.size();i++)
				{
					sf::TcpSocket &client = *clients[i].client;
					if(selector.isReady(client))
					{
                        sf::Socket::Status state = client.receive(ID);
                        if(state == sf::Socket::Done)
                        {
							ID >> identificateur;
							client.receive(data);
							switch(identificateur)
							{
								case 1://chat
								{
									data >> player >> message;
									finder = onlineClients.find(player);
									if(finder != onlineClients.end())
									{
										ID.clear();
										data.clear();
										ID << 1;
										data << clients[i].username << message;
										finder->second->send(ID);
										finder->second->send(data);
									}
									break;
								}
								case 2: //envoyer une demande de partie
								{
									ID.clear();
									ID << 2;
									data >> players[0] >> players[1];
									finder = onlineClients.find(players[1]);
									if(finder != onlineClients.end())
									{
										finder->second->send(ID);
										finder->second->send(data);
									}
									break;
								}
								case 3:
								{
									data >> players[0] >> players[1] >> acceptation;
									if(acceptation == 1)
									{
										finder = onlineClients.find(players[0]);
										finder2 = onlineClients.find(players[1]);
										if(finder != onlineClients.end())
										{
											if(finder2 != onlineClients.end())
											{
												if(nbServ < *limits)
												{
													nbServ++;
													sf::Packet tempnbServ;
													for(int i = 0 ; i < 2 ; i++)
													{
														foldername = "users/";
														foldername += players[i];
														foldername += "/";
														foldername += players[i];
														foldername += ".sav";
													}
												}
											}
										}
									}
									break;
								}
							}
						}
						else if(state == sf::Socket::Disconnected)
                        {
                            indSuppr = i;
                            suppr = 1;
                        }
					}
					ID.clear();
					data.clear();
				}
				if(suppr == 1)
                {
                    selector.remove(*clients[indSuppr].client);
					onlineClients.erase(clients[indSuppr].username);
                    delete clients[indSuppr].client;
                    clients.erase(clients.begin()+indSuppr);
                    suppr = 0;
					std::cout << "coucou" << std::endl;
                }
			}
		}
	}
	listener.close();
}