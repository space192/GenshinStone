#include "prototypes.h"


void jeu(int port, std::string nomJoueur)
{
    int numJoueur, actuJoueur;
    sf::TcpSocket socket;
    sf::Socket::Status status = socket.connect("fournierfamily.ovh", 53000 + port);
    if(status != sf::Socket::Done)
    {
        std::cout << "erreur lors de la connexion" << std::endl;
        exit(1);
    }
    else
    {
        std::string name1;
        std::string name2;
        std::string oponnent;
        std::string nomsJoueur[2] = {nomJoueur,oponnent};
        sf::Packet paquet;
        socket.receive(paquet);
        paquet >> numJoueur;
        paquet.clear();
        socket.receive(paquet);
        paquet >> actuJoueur >> name1 >> name2;
        paquet.clear();
        if(nomJoueur == name1)
        {
            oponnent = name2;
        }
        else if(nomJoueur == name2)
        {
            oponnent = name1;
        }
        std::cout << oponnent << std::endl;
        TTF_Font *police = NULL;
        /* Création de la fenêtre */
        SDL_Window* pWindow = NULL;
        SDL_Event event;
        int condition = 1;
        int conditionSouris = 0;
        int conditionRect = 0;
        int carteSelec = -1;
        int condDetail = 0;
        int carteDetail;
        int carteAttaque = 0;
        int affTour;
        int changeTour= 1;
        Attaque attaqueActive;
        pWindow = SDL_CreateWindow("Mon application SDL2",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,1920,1080,SDL_WINDOW_SHOWN);
        SDL_Surface *windowSurface = NULL;
        windowSurface = SDL_GetWindowSurface( pWindow );
        SDL_Surface *fond = IMG_Load("Fond.png");
        SDL_Surface *texte = NULL;
        SDL_Surface *selec = IMG_Load("selec.png");

        SDL_Surface* tour = IMG_Load("your turn.png");


        int vieJoueur[2] = {150,150};

        //varianles pour réceptions
        int ID1 = -1;
        int ID2= -1;
        int degats= -1;
        int nbrCarte= -1;
        int selecC= -1;
        int placeID= -1;
        std::vector<int> TID1;
        std::vector<int> TID2;
        std::vector<int> Tdegats;

        std::vector<SDL_Surface*> imageCache;


        imageCache.push_back(IMG_Load("Cartes/VentiP.png"));
        imageCache.push_back(IMG_Load("Cartes/TartagliaP.png"));
        imageCache.push_back(IMG_Load("Cartes/NingguangP.png"));
        imageCache.push_back(IMG_Load("Cartes/KleeP.png"));
        imageCache.push_back(IMG_Load("Cartes/BennetP.png"));
        imageCache.push_back(IMG_Load("Cartes/Klee2P.png"));
        imageCache.push_back(IMG_Load("Cartes/MonaP.png"));
        imageCache.push_back(IMG_Load("Cartes/JeanP.png"));
        imageCache.push_back(IMG_Load("Cartes/NoelleP.png"));
        imageCache.push_back(IMG_Load("Cartes/ZhongliP.png"));
        imageCache.push_back(IMG_Load("Cartes/SucroseP.png"));
        imageCache.push_back(IMG_Load("Cartes/BarbaraP.png"));

        imageCache.push_back(IMG_Load("Cartes/abondanceP.png"));
        imageCache.push_back(IMG_Load("Cartes/benedictionP.png"));
        imageCache.push_back(IMG_Load("Cartes/flechesP.png"));
        imageCache.push_back(IMG_Load("Cartes/maledictionP.png"));
        imageCache.push_back(IMG_Load("Cartes/poisonP.png"));
        imageCache.push_back(IMG_Load("Cartes/potionP.png"));















        imageCache.push_back(IMG_Load("Cartes/VentiG.png"));
        imageCache.push_back(IMG_Load("Cartes/TartagliaG.png"));
        imageCache.push_back(IMG_Load("Cartes/NingguangG.png"));
        imageCache.push_back(IMG_Load("Cartes/KleeG.png"));
        imageCache.push_back(IMG_Load("Cartes/BennetG.png"));
        imageCache.push_back(IMG_Load("Cartes/Klee2G.png"));
        imageCache.push_back(IMG_Load("Cartes/MonaG.png"));
        imageCache.push_back(IMG_Load("Cartes/JeanG.png"));
        imageCache.push_back(IMG_Load("Cartes/NoelleG.png"));
        imageCache.push_back(IMG_Load("Cartes/ZhongliG.png"));
        imageCache.push_back(IMG_Load("Cartes/SucroseG.png"));
        imageCache.push_back(IMG_Load("Cartes/BarbaraG.png"));

        imageCache.push_back(IMG_Load("Cartes/abondanceG.png"));
        imageCache.push_back(IMG_Load("Cartes/benedictionG.png"));
        imageCache.push_back(IMG_Load("Cartes/flechesG.png"));
        imageCache.push_back(IMG_Load("Cartes/maledictionG.png"));
        imageCache.push_back(IMG_Load("Cartes/poisonG.png"));
        imageCache.push_back(IMG_Load("Cartes/potionG.png"));




        imageCache.push_back(IMG_Load("back card small.png"));
        imageCache.push_back(IMG_Load("back card big.png"));






        std::vector<SDL_Surface*> imageCacheE;
        imageCacheE.push_back(IMG_Load("eauP.png"));
        imageCacheE.push_back(IMG_Load("terreP.png"));
        imageCacheE.push_back(IMG_Load("airP.png"));
        imageCacheE.push_back(IMG_Load("feuP.png"));

        imageCacheE.push_back(IMG_Load("eauG.png"));
        imageCacheE.push_back(IMG_Load("terreG.png"));
        imageCacheE.push_back(IMG_Load("airG.png"));
        imageCacheE.push_back(IMG_Load("feuG.png"));




        std::vector< std::vector<Cartes*> > cartesJoueur;
        std::vector<Cartes*> TEMP;
        std::vector<Cartes*> TEMP4;


        for(int i = 8; i<18 ; i++)
        {
            lierCarteEtId(i,i,TEMP);
        }

        for(int i = 8; i<18 ; i++)
        {
            lierCarteEtId(i,i,TEMP4);
        }


        if(numJoueur == 1)
        {

            cartesJoueur.push_back(TEMP4);
            cartesJoueur.push_back(TEMP);
        }
        else
        {

            cartesJoueur.push_back(TEMP);
            cartesJoueur.push_back(TEMP4);
        }



        std::vector< std::vector<Cartes*> > cartesJoueurTerrain;
        std::vector<Cartes*> TEMP2;
        std::vector<Cartes*> TEMP3;
        /*TEMP2.push_back( new CharacterCards("Carte1","feu",10,1,1,797,0,10,30,2));
        TEMP2.push_back( new CharacterCards("Carte2","feu",10,1,1,897,0,10,30,2));
        TEMP2.push_back( new CharacterCards("Carte2","feu",10,1,1,897,0,10,30,2));
        TEMP2.push_back( new CharacterCards("Carte2","feu",10,1,1,897,0,10,30,2));
        TEMP2.push_back( new CharacterCards("Carte2","feu",10,1,1,897,0,10,30,2));
        TEMP2.push_back( new CharacterCards("Carte2","feu",10,1,1,897,0,10,30,2));

        TEMP3.push_back( new CharacterCards("Carte1","feu",10,1,1,797,0,10,30,2));
        TEMP3.push_back( new CharacterCards("Carte2","feu",10,1,1,897,0,10,30,2));
        TEMP3.push_back( new CharacterCards("Carte2","feu",10,1,1,897,0,10,30,2));
        TEMP3.push_back( new CharacterCards("Carte2","feu",10,1,1,897,0,10,30,2));
        TEMP3.push_back( new CharacterCards("Carte2","feu",10,1,1,897,0,10,30,2));
        TEMP3.push_back( new CharacterCards("Carte2","feu",10,1,1,897,0,10,30,2));*/


        std::vector<EnergyCards> energiesJoueur;
        energiesJoueur.push_back( EnergyCards("Carte1",3,10,1,1,797,0,1));
        energiesJoueur.push_back( EnergyCards("Carte1",3,10,1,1,797,0,1));
        energiesJoueur.push_back( EnergyCards("Carte1",3,10,1,1,797,0,1));
        energiesJoueur.push_back( EnergyCards("Carte1",3,10,1,1,797,0,2));
        energiesJoueur.push_back( EnergyCards("Carte1",3,10,1,1,797,0,3));
        energiesJoueur.push_back( EnergyCards("Carte1",3,10,1,1,797,0,4));

        std::vector< std::vector<Cartes*> > cimetiere;
        std::vector<Cartes*> TEMP5;
        std::vector<Cartes*> TEMP6;

        cimetiere.push_back(TEMP5);
        cimetiere.push_back(TEMP6);




        SDL_Rect position;

        if(numJoueur == 1)
        {
            cartesJoueurTerrain.push_back(TEMP2);
            cartesJoueurTerrain.push_back(TEMP3);
        }
        else if(numJoueur == 2)
        {
            cartesJoueurTerrain.push_back(TEMP3);
            cartesJoueurTerrain.push_back(TEMP2);

        }



        actualiserPositionCartesT(cartesJoueurTerrain);
        actualiserPositionCartes(cartesJoueur);
        actualiserEnergies(energiesJoueur);



        /*paquet << 3;
        socket.send(paquet);
        paquet.clear();
        paquet << cartesJoueur[0].size();
        socket.send(paquet);
        paquet.clear();*/

        //launching thread
        //void receiveData(int *activePlayer, sf::TcpSocket *socket, int &numJoueur, int *condition, int *ID1, int *ID2, int *degats, int *nbCarte, int *selec,int *placeID)
        sf::Thread thread(std::bind(&receiveData, &actuJoueur,&socket, numJoueur, &condition, &ID1,&ID2,&degats, &nbrCarte, &selecC, &placeID, &TID1, &TID2, &Tdegats));
        thread.launch();
        if( pWindow )
        {

            while(condition == 1)
            {
                if(numJoueur == actuJoueur && changeTour == 1)
                {
                    affTour = 1;
                    changeTour = 0;
                }
                SDL_BlitSurface(fond, NULL, windowSurface, NULL);
                actualiserImage(cartesJoueur[0],cartesJoueurTerrain,imageCache,windowSurface,texte,police);
                afficherEnergies(energiesJoueur,imageCacheE,windowSurface);
                if(numJoueur == actuJoueur)
                {
                    if(SDL_PollEvent( &event ))
                    {


                        switch(event.type)
                        {
                        case SDL_KEYDOWN:
                            switch(event.key.keysym.sym)
                            {
                            case SDLK_ESCAPE:
                                condition = 0;
                                paquet.clear();
                                paquet << 9;
                                socket.send(paquet);
                                thread.terminate();
                                paquet.clear();
                                break;
                            }
                            break;
                        case SDL_MOUSEBUTTONDOWN:

                            //std::cout << "Coordonnes x :" << event.button.x << std::endl;
                           // std::cout << "Coordonnes y :" << event.button.y << std::endl;

                            if((event.button.x > 360 && event.button.x < 1549 && event.button.y > 990 && event.button.y < 1080))
                            {
                                conditionSouris = 1;
                                condDetail = 0;
                                carteSelec = selectionCarte(cartesJoueur[0],event.button.x,event.button.y); //clique sur une carte dans ta main
                            }
                            else if(event.button.x > 322 && event.button.x < 1549 && event.button.y > 500 && event.button.y < 679)
                            {
                                conditionSouris = 3;
                                carteSelec = selectionCarte(cartesJoueurTerrain[0],event.button.x,event.button.y);
                                condDetail=1;
                                carteDetail = carteSelec; //clique sur une carte sur le terrain
                            }
                            else
                            {
                                conditionSouris = 0;
                            }

                            if(event.button.x >1568 && event.button.x < 1773 && event.button.y > 445 && event.button.y < 526)
                            {
                                paquet.clear();
                                paquet << 7; //envoie nombre de carte
                                socket.send(paquet);
                                paquet.clear();
                                if(actuJoueur == 1)
                                {
                                    paquet << 2;
                                }
                                else if(actuJoueur == 2)
                                {
                                    paquet << 1;
                                }
                                socket.send(paquet);
                                paquet.clear();
                                changeTour = 1;
                            }

                            break;
                        case SDL_MOUSEMOTION:

                            if(conditionSouris == 1)
                            {
                                cartesJoueur[0][carteSelec]->setPosition(event.motion.x,event.motion.y);
                            }
                            else if(conditionSouris == 3)
                            {
                                cartesJoueurTerrain[0][carteSelec]->setPosition(event.motion.x,event.motion.y);
                            }
                            else if(conditionSouris == 0)
                            {
                                if(event.button.x > 322 && event.button.x < 1549 && event.button.y > 500 && event.button.y < 679)
                                {
                                    carteSelec = selectionCarte(cartesJoueurTerrain[0],event.button.x,event.button.y);
                                    condDetail=1;
                                    carteDetail = carteSelec;

                                }
                                else if(event.button.x > 360 && event.button.x < 1450 && event.button.y > 350 && event.button.y < 500)
                                {
                                    carteSelec = selectionCarte(cartesJoueurTerrain[1],event.button.x,event.button.y);
                                    condDetail=3;
                                    carteDetail = carteSelec;

                                }
                                else if(event.button.x > 360 && event.button.x < 1450 && event.button.y > 990 && event.button.y < 1080)
                                {
                                    carteSelec = selectionCarte(cartesJoueur[0],event.button.x,event.button.y);
                                    condDetail=2;
                                    carteDetail = carteSelec;

                                }
                                else
                                {
                                    condDetail = 0;
                                }
                            }

                            break;
                        case SDL_MOUSEBUTTONUP:

                            if((event.button.x > 360 && event.button.x < 1450 && event.button.y > 500 && event.button.y < 680 )&&(conditionSouris == 1)&&(cartesJoueur[0][carteSelec]->getType()==1))
                            {
                                placerCarte(cartesJoueur[0], cartesJoueurTerrain[0],carteSelec);
                                actualiserPositionCartes(cartesJoueur);
                                actualiserPositionCartesT(cartesJoueurTerrain);//poser une carte sur le terrain //ENVOIE SERVEUR
                                paquet.clear();
                                paquet << 3; //envoie nombre de carte
                                socket.send(paquet);
                                paquet.clear();
                                paquet << cartesJoueur[0].size();
                                socket.send(paquet);
                                paquet.clear();
                                paquet << 5; //envoie carte place
                                socket.send(paquet);
                                paquet.clear();
                                paquet << carteSelec;
                                socket.send(paquet);
                                paquet.clear();
                            }
                            else if((event.button.x > 360 && event.button.x < 1450 && event.button.y > 500 && event.button.y < 680 )&&(conditionSouris == 1)&&(cartesJoueur[0][carteSelec]->getType()==2))
                            {
                                actionTrainer(carteSelec,cartesJoueurTerrain,cartesJoueur,energiesJoueur,vieJoueur, &socket);
                                cartesJoueur[0].erase(cartesJoueur[0].begin() + carteSelec);
                                actualiserPositionCartes(cartesJoueur);
                                paquet.clear();
                                paquet << 3; //envoie nombre de carte
                                socket.send(paquet);
                                paquet.clear();
                                paquet << cartesJoueur[0].size();
                                socket.send(paquet);
                                paquet.clear();
                                paquet << 5; //envoie carte place
                                socket.send(paquet);
                                paquet.clear();
                                paquet << carteSelec;
                                socket.send(paquet);
                                paquet.clear();
                            }
                            else if(((event.button.x > 360 && event.button.x < 1450 && event.button.y > 350 && event.button.y < 500)&&(conditionSouris == 3)))
                            {


                                carteAttaque = -1;
                                carteAttaque =selectionCarte(cartesJoueurTerrain[1],event.button.x,event.button.y ); //numero de la carte qui va se faire attaquer

                                if(carteAttaque != -1)
                                {
                                    if((event.button.button == SDL_BUTTON_LEFT))
                                    {
                                        attaqueActive = cartesJoueurTerrain[0][carteDetail]->getAttaque(0); //TOUT CA C'EST ATTAQUE
                                    }                                         //ID Attaquant
                                    else
                                    {
                                        attaqueActive = cartesJoueurTerrain[0][carteDetail]->getAttaque(1); //TYPE d'attaque en fonction du bouton
                                    }

                                    if(testSiAttaquePossible(attaqueActive,energiesJoueur,cartesJoueurTerrain) == 1) //gerer les energies
                                    {
                                        cartesJoueurTerrain[1][carteAttaque]->setVie(attaqueActive.degat); //recevoir les degats sur la carte adverse
                                        paquet.clear();
                                        paquet << 2;
                                        socket.send(paquet);
                                        paquet.clear();
                                        paquet << 2 << carteAttaque << attaqueActive.degat;
                                        socket.send(paquet);
                                        paquet.clear();
                                    }//            attaqué                          attaque de l'attaquant


                                }
                                /*else if(cartesJoueurTerrain[1].size() == 0)
                                {


                                    if((event.button.button == SDL_BUTTON_LEFT))
                                    {
                                        attaqueActive = cartesJoueurTerrain[0][carteDetail]->getAttaque(0);
                                    }
                                    else
                                    {
                                        attaqueActive = cartesJoueurTerrain[0][carteDetail]->getAttaque(1);
                                    }

                                    if(testSiAttaquePossible(attaqueActive,energiesJoueur,cartesJoueurTerrain) == 1)
                                    {
                                        vieJoueur[1] -= attaqueActive.degat;
                                        paquet.clear();
                                        paquet << 10;
                                        socket.send(paquet);
                                        paquet.clear();
                                        paquet << 41 << attaqueActive.degat;
                                        socket.send(paquet);
                                        paquet.clear();

                                    }

                                }*/

                                actualiserPositionCartesT(cartesJoueurTerrain);
                            }
                            else if(((event.button.x > 873 && event.button.x < 1060 && event.button.y > 132 && event.button.y < 282)&&(conditionSouris == 3)))
                            {
                                 if((event.button.button == SDL_BUTTON_LEFT))
                                    {
                                        attaqueActive = cartesJoueurTerrain[0][carteDetail]->getAttaque(0);
                                    }
                                    else
                                    {
                                        attaqueActive = cartesJoueurTerrain[0][carteDetail]->getAttaque(1);
                                    }

                                    if(testSiAttaquePossible(attaqueActive,energiesJoueur,cartesJoueurTerrain) == 1)
                                    {
                                        vieJoueur[1] -= attaqueActive.degat;
                                        paquet.clear();
                                        paquet << 10;
                                        socket.send(paquet);
                                        paquet.clear();
                                        paquet << 41 << -attaqueActive.degat;
                                        socket.send(paquet);
                                        paquet.clear();

                                    }
                                    actualiserPositionCartesT(cartesJoueurTerrain);
                            }
                            else if(conditionSouris == 1)
                            {
                                actualiserPositionCartes(cartesJoueur);
                            }


                            conditionSouris = 0;


                            carteSelec = -1;
                            break;
                        }
                    }

                    afficherTour(affTour,tour,windowSurface);

                }
                else
                {

                    actualiserDegats(ID1,ID2,degats,cartesJoueurTerrain,vieJoueur, TID1, TID2, Tdegats);
                    if(placeID != -1)
                    {
                        if(cartesJoueur[1][placeID]->getType()==1)
                        {
                            placerCarte(cartesJoueur[1], cartesJoueurTerrain[1],placeID);
                            actualiserPositionCartesT(cartesJoueurTerrain);
                        }
                        else if(cartesJoueur[1][placeID]->getType()==2)
                        {
                            cartesJoueur[1].erase(cartesJoueur[1].begin() + placeID);
                        }

                        placeID = -1;
                    }




                    if(SDL_PollEvent(&event))
                    {
                        if(event.type == SDL_KEYDOWN)
                        {
                            if(event.key.keysym.sym == SDLK_ESCAPE)
                            {
                                condition = 0;
                                paquet.clear();
                                paquet << 9;
                                socket.send(paquet);
                                thread.terminate();
                                paquet.clear();
                            }
                        }
                    }
                }
                if(actuJoueur == 9)
                {
                    condition = 0;
                }
                afficherDetails(condDetail,carteDetail,cartesJoueurTerrain,cartesJoueur,windowSurface,imageCache,texte,police, &socket);
                afficherCartesAdverses(cartesJoueur,selecC,imageCache,windowSurface);
                afficherPV(nomsJoueur,vieJoueur,texte,police,windowSurface);
                testSiCarteMorte(cartesJoueurTerrain,cimetiere);
                afficherCimetiere(cimetiere,imageCache,windowSurface);
                if(conditionRect == 1)
                {
                    SDL_BlitSurface(selec,NULL,windowSurface,&position);
                }
                SDL_UpdateWindowSurface(pWindow);
            }
        }
        else
        {
            fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
        }


        for(size_t i = 0; i<imageCache.size(); i++)
        {
            SDL_FreeSurface(imageCache[i]);
        }

        SDL_FreeSurface(fond);
        SDL_FreeSurface(texte);
        SDL_FreeSurface(selec);

        SDL_DestroyWindow(pWindow);
        std::cout << "HELLO" << std::endl;
    }
}
