#include "prototypes.h"
int defaut = -1;
int old = -1;
int newV = -1;


int selectionCarte(std::vector<Cartes*> & cartesJoueur, int x, int y)
{
    SDL_Rect position;
    int resultat = -1;
    for(size_t i = 0; i < cartesJoueur.size(); i++)
    {
        position = cartesJoueur[i]->getPosition();
        if (( x > position.x) && (x < position.x + 100) && (y >position.y) && ( y < position.y + 177))
        {
            resultat = i;
        }
    }

    return resultat;
}

void placerCarte(std::vector<Cartes*> & cartesJoueur,std::vector<Cartes*> & cartesJoueurTerrain,int carteSelec)
{
    cartesJoueurTerrain.push_back(cartesJoueur[carteSelec]);
    cartesJoueur.erase(cartesJoueur.begin() + carteSelec);
}

void actualiserImage(std::vector<Cartes*> & cartesJoueur,std::vector< std::vector<Cartes*> > & cartesJoueurTerrain,std::vector<SDL_Surface*> & imageCache, SDL_Surface  *windowSurface,SDL_Surface *texte,TTF_Font *police)
{
    SDL_Rect position;
    SDL_Color couleur = {255, 255, 255};
    std::stringstream machaine;

    police = TTF_OpenFont("ARLRDBD.TTF", 30);




    for(size_t i = 0; i< cartesJoueur.size(); i++ )
    {
        position = cartesJoueur[i]->getPosition();
        SDL_BlitSurface(imageCache[cartesJoueur[i]->getImage()], NULL, windowSurface, &position);
        if(cartesJoueur[i]->getType() ==1 )
        {
            machaine << cartesJoueur[i]->getVie();
            texte = TTF_RenderText_Solid(police, machaine.str().c_str(), couleur);
            SDL_BlitSurface(texte, NULL, windowSurface, &position);
            machaine.str(" ");
            SDL_FreeSurface(texte);
        }
    }

    for(size_t i = 0; i< cartesJoueurTerrain[0].size(); i++ )
    {
        position = cartesJoueurTerrain[0][i]->getPosition();

        SDL_BlitSurface(imageCache[cartesJoueurTerrain[0][i]->getImage()], NULL, windowSurface, &position);
        machaine << cartesJoueurTerrain[0][i ]->getVie();
        texte = TTF_RenderText_Solid(police, machaine.str().c_str(), couleur);
        SDL_BlitSurface(texte, NULL, windowSurface, &position);
        machaine.str(" ");
        SDL_FreeSurface(texte);
    }

    for(size_t i = 0; i< cartesJoueurTerrain[1].size(); i++ )
    {
        position = cartesJoueurTerrain[1][i]->getPosition();
        SDL_BlitSurface(imageCache[cartesJoueurTerrain[1][i]->getImage()], NULL, windowSurface, &position);
        machaine << cartesJoueurTerrain[1][i ]->getVie();
        texte = TTF_RenderText_Solid(police, machaine.str().c_str(), couleur);
        SDL_BlitSurface(texte, NULL, windowSurface, &position);
        machaine.str(" ");
        SDL_FreeSurface(texte);
    }

    TTF_CloseFont(police);
}

void actualiserPositionCartes(std::vector< std::vector<Cartes*> > & cartesJoueur)
{
    for(size_t i = 0; i < cartesJoueur[0].size(); i++)
    {
        cartesJoueur[0][i]->setPosition(900 - ((cartesJoueur[0].size()-1)*50) + i*100, 990);

    }
}

void actualiserPositionCartesT(std::vector< std::vector<Cartes*> >  & cartesJoueurTerrain)
{
    for(size_t i = 0; i < cartesJoueurTerrain[0].size(); i++)
    {
        cartesJoueurTerrain[0][i]->setPosition(900 - ((cartesJoueurTerrain[0].size()-1)*70) + i*140, 520);

    }
    for(size_t i = 0; i < cartesJoueurTerrain[1].size(); i++)
    {
        cartesJoueurTerrain[1][i]->setPosition(900 - ((cartesJoueurTerrain[1].size()-1)*70) + i*140, 325);

    }
}


void afficherDetails(int & condDetail, int & carteDetail,std::vector< std::vector<Cartes*> >  & cartesJoueurTerrain,std::vector< std::vector<Cartes*> >  & cartesJoueur,SDL_Surface  *windowSurface,std::vector<SDL_Surface*> imageCache,SDL_Surface *texte,TTF_Font *police, sf::TcpSocket *client)
{
    sf::Packet paquet;
    SDL_Rect position;
    SDL_Color couleur = {255, 255, 255};
    std::stringstream machaine;

    police = TTF_OpenFont("ARLRDBD.TTF", 60);

    if(condDetail == 1)
    {
        if(carteDetail != -1)
        {
            position = cartesJoueurTerrain[0][carteDetail ]->getPosition();
            position.x -= 42;
            position.y -= 59;
            SDL_BlitSurface(imageCache[cartesJoueurTerrain[0][carteDetail ]->getImage()+18], NULL, windowSurface, &position);
            machaine << cartesJoueurTerrain[0][carteDetail ]->getVie();
            texte = TTF_RenderText_Solid(police, machaine.str().c_str(), couleur);
            SDL_BlitSurface(texte, NULL, windowSurface, &position);
            machaine.str(" ");
            SDL_FreeSurface(texte);
        }
    }
    else if(condDetail == 3)
    {
        if(carteDetail != -1)
        {
            position = cartesJoueurTerrain[1][carteDetail ]->getPosition();
            position.x -= 42;
            position.y -= 59;
            SDL_BlitSurface(imageCache[cartesJoueurTerrain[1][carteDetail ]->getImage()+18], NULL, windowSurface, &position);
            machaine << cartesJoueurTerrain[1][carteDetail ]->getVie();
            texte = TTF_RenderText_Solid(police, machaine.str().c_str(), couleur);
            SDL_BlitSurface(texte, NULL, windowSurface, &position);
            machaine.str(" ");
            SDL_FreeSurface(texte);
        }
    }
    else if(condDetail == 2)
    {
        if(carteDetail != -1)
        {
            position = cartesJoueur[0][carteDetail ]->getPosition();
            position.x -= 100;
            position.y -= 300;
            SDL_BlitSurface(imageCache[cartesJoueur[0][carteDetail ]->getImage()+18], NULL, windowSurface, &position);

            if(cartesJoueur[0][carteDetail ]->getType() ==1 )
            {
                machaine << cartesJoueur[0][carteDetail ]->getVie() ;
                texte = TTF_RenderText_Solid(police, machaine.str().c_str(), couleur);
                SDL_BlitSurface(texte, NULL, windowSurface, &position);
                machaine.str(" ");
                SDL_FreeSurface(texte);
            }
        }
        newV = carteDetail;
        if(old != newV)
        {
            paquet.clear();
            paquet << 4;
            client->send(paquet);
            paquet.clear();
            old = newV;
            paquet << carteDetail;
            client->send(paquet);
            paquet.clear();
        }

    }
    TTF_CloseFont(police);
}


void actualiserEnergies(std::vector<EnergyCards> & energiesJoueur)
{
    int cond = 0;

    for(size_t i =0; i<energiesJoueur.size(); i++)
    {
        if(energiesJoueur[i].getElem() == 1)
        {
            energiesJoueur[i].setPosition(0,900 + cond*25);
            cond ++;
        }


    }
    cond = 0;

    for(size_t i =0; i<energiesJoueur.size(); i++)
    {
        if(energiesJoueur[i].getElem() == 2)
        {
            energiesJoueur[i].setPosition(50,900 + cond*25);
            cond ++;
        }


    }
    cond = 0;

    for(size_t i =0; i<energiesJoueur.size(); i++)
    {
        if(energiesJoueur[i].getElem() == 3)
        {
            energiesJoueur[i].setPosition(100,900 + cond*25);
            cond ++;
        }


    }
    cond = 0;

    for(size_t i =0; i<energiesJoueur.size(); i++)
    {
        if(energiesJoueur[i].getElem() == 4)
        {
            energiesJoueur[i].setPosition(150,900 + cond*25);
            cond ++;
        }

    }



}

void afficherEnergies(std::vector<EnergyCards> & energiesJoueur,std::vector<SDL_Surface*> & imageCache, SDL_Surface  *windowSurface)
{
    SDL_Rect position;

    for(size_t i =0; i<energiesJoueur.size(); i++)
    {
        position = energiesJoueur[i].getPosition();
        SDL_BlitSurface(imageCache[energiesJoueur[i].getElem() - 1], NULL, windowSurface, &position);
    }
}

int testSiAttaquePossible(Attaque attaqueActive,std::vector<EnergyCards> & energiesJoueur, std::vector< std::vector<Cartes*> >  & cartesJoueurTerrain )
{
    // Attaque attaqueActive

    int resultat = 0;
    int numCond = 0 ;
    int eraseCond = 0;

    for(size_t i = 0; i<energiesJoueur.size(); i++)
    {
        if(energiesJoueur[i].getElem() == attaqueActive.typeEnergie)
        {
            numCond++;
        }
    }



    if(numCond >= attaqueActive.prix)
    {
        resultat=1;

        /*for (auto it = energiesJoueur.begin(); it != energiesJoueur.end(); )
        {
            if(it->getElem() == attaqueActive.typeEnergie && eraseCond < attaqueActive.prix)
            {
                it = energiesJoueur.erase(it);
                eraseCond ++;
            }

            it++;
        }*/

        if(energiesJoueur.empty() == false)
        {
            for(int i = energiesJoueur.size() - 1; i >= 0; i--)
            {
                if(energiesJoueur.at(i).getElem() == attaqueActive.typeEnergie && eraseCond < attaqueActive.prix)

                {
                    energiesJoueur.erase( energiesJoueur.begin() + i );
                    eraseCond++;
                }
            }
        }

    }
    else
    {
        resultat = 0;
    }

    return resultat;




}

void actualiserDegats(int & ID1, int &ID2, int & degats, std::vector< std::vector<Cartes*> >  & cartesJoueurTerrain, int vieJoueur[], std::vector<int> &TID1, std::vector<int> &TID2, std::vector<int> &Tdegats)
{
    int temp;
    if(ID2 != -1)
    {
        if( ID1 == 2)
        {
            cartesJoueurTerrain[0][ID2]->setVie(degats);
            ID2 = -1;
            ID1 = -1;
        }
        else if( ID1 == 1)
        {
            cartesJoueurTerrain[1][ID2]->setVie(degats);
            ID2 = -1;
            ID1 = -1;
        }
        else if(ID1 >= 20 && ID1 != 40 && ID1 != 41)
        {
            cartesJoueurTerrain[0][ID1 - 20]->setVie(degats);
            cartesJoueurTerrain[0][ID2]->setVie(degats);
            ID1 = -1;
            ID2 = -1;
        }
    }
    if(ID1 == 40)
    {
        vieJoueur[1]+=degats;
        ID1 = -1;
    }
    else if(ID1 == 41)
    {
        vieJoueur[0]+=degats;
        ID1 = -1;
    }
    temp = TID1.size();
    for(int i =0 ; i < temp; i++)
    {
        if(TID1[i] == 1)
        {
            cartesJoueurTerrain[1][TID2[i]]->setVie(Tdegats[i]);
        }
        else if(TID1[i] == 2)
        {
            cartesJoueurTerrain[0][TID2[i]]->setVie(Tdegats[i]);
        }
    }
    for(int i = 0; i < temp; i++)
    {
        TID1.erase(TID1.begin());
        TID2.erase(TID2.begin());
        Tdegats.erase(Tdegats.begin());
    }
}

void afficherCartesAdverses(std::vector< std::vector<Cartes*> >  & cartesJoueur,int carteAdverse,std::vector<SDL_Surface*> & imageCache, SDL_Surface  *windowSurface)
{

    SDL_Rect position;

    for(size_t i = 0; i < cartesJoueur[1].size(); i++)
    {
        if((int)i == carteAdverse)
        {
            cartesJoueur[1][i]->setPosition(900 - ((cartesJoueur[1].size()-1)*50) + i*100, 0);
        }
        else
        {
            cartesJoueur[1][i]->setPosition(900 - ((cartesJoueur[1].size()-1)*50) + i*100, -50);
        }

        position = cartesJoueur[1][i]->getPosition();
        SDL_BlitSurface(imageCache[36], NULL, windowSurface, &position);

    }
}

void receiveData(int *activePlayer, sf::TcpSocket *socket, int &numJoueur, int *condition, int *ID1, int *ID2, int *degats, int *nbrCarte, int *selec,int *placeID, std::vector<int> *TID1, std::vector<int> *TID2, std::vector<int> *Tdegats, std::string sent, std::string *chaine, bool *notification, int pioche[])
{
    sf::Packet tempReceive;
    int receive = 0;
    int old, news, compteur, compteur2, compteur3, old2, news2;
    sf::Packet paquet;
    sf::Packet realOne;
    int boucle;
    int temp, temp2, temp3;
    std::string tempChaine;
    int continuer = 1;
    while(continuer != 9)
    {
        socket->receive(tempReceive);
        tempReceive >> receive;
        if(receive != 9 && receive != 15)
        {
            socket->receive(realOne);
        }
        if(receive != 4)
        {
            old = news;
            news = receive;
        }
        switch(receive)
        {
        case 1:
        {
            realOne >> tempChaine; //recevoir un texte
            if(tempChaine != sent)
            {
                *chaine = tempChaine;
                *notification = true;
            }
            else
            {
                *notification = false;
            }
            break;
        }
        case 2:
        {
            realOne >> *ID1 >> *ID2 >> *degats; //recevoir une attaque
            break;
        }
        case 3:
        {
            realOne >> *nbrCarte;//nombre carte adversaire
            break;
        }
        case 4:
        {
            old2 = news2;
            realOne >> *selec;//carte selectionnee
            news2 = *selec;
            break;
        }
        case 5: //placer une carte
        {
            realOne >> *placeID;
            break;
        }
        case 6:
        {
            //décés d'une carte
            break;
        }
        case 7:
        {
            realOne >> *activePlayer;
            break;
        }
        case 9:
        {
            continuer = 9;
            *condition = 0;
            break;
        }
        case 10:
        {
            realOne >> *ID1 >> *degats;
            break;
        }
        case 11:
        {
            realOne >> boucle;
            for(int i = 0 ; i < boucle ; i++)
            {
                realOne >> temp >> temp2 >> temp3;
                TID1->push_back(temp);
                TID2->push_back(temp2);
                Tdegats->push_back(temp3);
            }
            break;
        }
        case 12:
        {
            realOne >> pioche[0] >> pioche[1] >> pioche[2];
            break;
        }
        case 15:
        {
            break;
        }
        default:
        {
            std::cout << "erreur lors du choix de la reception" << std::endl;
            compteur2++;
            break;
        }
        }
        if(old == news)
        {
            compteur ++;
        }
        else
        {
            compteur = 0;
        }
        if(old2 == news2)
        {
            compteur3++;
        }
        else
        {
            compteur3 = 0;
        }
        if(compteur == 40 || compteur2 == 40 || compteur3 == 40)
        {
            continuer = 9;
            *condition = 0;
        }
        tempReceive.clear();
        paquet.clear();
        realOne.clear();
    }
}

void get_text_and_rect(SDL_Renderer *renderer, int x, int y, char *text, TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect,SDL_Color textColor)
{
    int text_width;
    int text_height;
    SDL_Surface *surface;
    //SDL_Color textColor = {255, 255, 255, 0};

    surface = TTF_RenderText_Solid(font, text, textColor);
    *texture = SDL_CreateTextureFromSurface(renderer, surface);
    text_width = surface->w;
    text_height = surface->h;
    SDL_FreeSurface(surface);
    rect->x = x;
    rect->y = y;
    rect->w = text_width;
    rect->h = text_height;
}


void testSiCarteMorte(std::vector< std::vector<Cartes*> >  & cartesJoueurTerrain,std::vector< std::vector<Cartes*> > & cimetiere )
{
    for(size_t i = 0; i<cartesJoueurTerrain[0].size(); i++)
    {
        if(cartesJoueurTerrain[0][i]->getVie() <=0 )
        {
            cimetiere[0].push_back(cartesJoueurTerrain[0][i]);
            cartesJoueurTerrain[0].erase(cartesJoueurTerrain[0].begin() + i);


            actualiserPositionCartesT(cartesJoueurTerrain);
        }
    }

    for(size_t i = 0; i<cartesJoueurTerrain[1].size(); i++)
    {
        if(cartesJoueurTerrain[1][i]->getVie() <=0 )
        {
            cimetiere[1].push_back(cartesJoueurTerrain[1][i]);
            cartesJoueurTerrain[1].erase(cartesJoueurTerrain[1].begin() + i);


            actualiserPositionCartesT(cartesJoueurTerrain);
        }
    }
}

void afficherCimetiere(std::vector< std::vector<Cartes*> > & cimetiere,std::vector<SDL_Surface*> & imageCache, SDL_Surface  *windowSurface)
{
    SDL_Rect position;






    if(cimetiere[0].size() != 0)
    {
        position.x = 0;
        position.y = 0;
        SDL_BlitSurface(imageCache[cimetiere[0][0]->getImage()], NULL, windowSurface, &position);
    }

    if(cimetiere[1].size() != 0)
    {

        position.x = 0;
        position.y = 100;
        SDL_BlitSurface(imageCache[cimetiere[1][0]->getImage()], NULL, windowSurface, &position);
    }



}

void actionTrainer(int selec,std::vector< std::vector<Cartes*> >  & cartesJoueurTerrain,std::vector< std::vector<Cartes*> >  & cartesJoueur,std::vector<EnergyCards> & energiesJoueur,int vieJoueur[2], sf::TcpSocket *socket)
{


    int valeur = cartesJoueur[0][selec]->getValeurT();
    int type = cartesJoueur[0][selec]->getTypeT();
    int carteAlea;
    int temp;
    sf::Packet paquet;




    if( type == 1)
    {
        paquet << 11;
        socket->send(paquet);
        paquet.clear();
        paquet << cartesJoueurTerrain[0].size();
        for(size_t i = 0; i < cartesJoueurTerrain[0].size(); i++)
        {
            cartesJoueurTerrain[0][i]->setVie(valeur); // envoie de ID ET DEGATS HEAL
            paquet << 1 << i << valeur; //indique que a la reception on doit changer la valeur de l'ennemie du point de vue du joueur qui receptionne
        }
        socket->send(paquet);
        paquet.clear();
    }
    else if( type == 2)
    {
        paquet << 11;
        socket->send(paquet);
        paquet.clear();
        paquet << cartesJoueurTerrain[1].size();
        for(size_t i = 0; i < cartesJoueurTerrain[1].size() ; i++)
        {
            cartesJoueurTerrain[1][i]->setVie(valeur); // envoie de ID et DEGATS
            paquet << 2 << i << valeur; //nous inflige des dégats a nos cartes en reception
        }
        socket->send(paquet);
        paquet.clear();
    }
    else if (type == 3)
    {
        if(cartesJoueurTerrain[1].size() != 0)
        {
            carteAlea =rand()%(cartesJoueurTerrain[1].size() ) + 0; // envoie de ID et DEGATS
            cartesJoueurTerrain[1][carteAlea]->setVie(valeur);
            temp = carteAlea;
        }

        if(cartesJoueurTerrain[1].size() != 0)
        {
            carteAlea =rand()%(cartesJoueurTerrain[1].size() )  + 0; // envoie de ID et DEGATS
            cartesJoueurTerrain[1][carteAlea]->setVie(valeur);
        }
        paquet.clear();
        paquet << 2;
        socket->send(paquet);
        paquet.clear();
        paquet << temp+20 << carteAlea << valeur;
        socket->send(paquet);
        paquet.clear();

    }
    else if(type ==4)
    {
        energiesJoueur.push_back( EnergyCards("Carte1",2,10,1,1,797,0,1));
        energiesJoueur.push_back( EnergyCards("Carte1",2,10,1,1,797,0,1));
        energiesJoueur.push_back( EnergyCards("Carte1",2,10,1,1,797,0,2));
        energiesJoueur.push_back( EnergyCards("Carte1",2,10,1,1,797,0,2));
        energiesJoueur.push_back( EnergyCards("Carte1",2,10,1,1,797,0,3));
        energiesJoueur.push_back( EnergyCards("Carte1",2,10,1,1,797,0,3));
        energiesJoueur.push_back( EnergyCards("Carte1",2,10,1,1,797,0,4));
        energiesJoueur.push_back( EnergyCards("Carte1",2,10,1,1,797,0,4));

        actualiserEnergies(energiesJoueur);
    }
    else if(type ==5)
    {
        vieJoueur[0]+= valeur; // ENVOIE DE DEGATS
        paquet.clear();
        paquet << 10;
        socket->send(paquet);
        paquet.clear();
        paquet << 40 << valeur;
        socket->send(paquet);
        paquet.clear();
    }
    else if(type ==6)
    {
        vieJoueur[1]+= valeur;
        paquet.clear();
        paquet << 10;
        socket->send(paquet);
        paquet.clear();
        paquet << 41 << valeur;
        socket->send(paquet);
        paquet.clear();
    }
}

void afficherPV(std::string *nomsJoueur,int vieJoueur[2],SDL_Surface *texte,TTF_Font *police,SDL_Surface  *windowSurface)
{
    SDL_Rect position;
    SDL_Color couleur = {255, 255, 255};
    std::stringstream machaine;
    std::stringstream machaine2;


    police = TTF_OpenFont("ARLRDBD.TTF", 30);

    position.x = 880;
    position.y = 850;
    machaine << "PV joueur: " <<vieJoueur[0];
    texte = TTF_RenderText_Solid(police, machaine.str().c_str(), couleur);
    SDL_BlitSurface(texte, NULL, windowSurface, &position);
    SDL_FreeSurface(texte);
    position.x = 880;
    position.y = 820;
    machaine2 << nomsJoueur[0];
    texte = TTF_RenderText_Solid(police, machaine2.str().c_str(), couleur);
    SDL_BlitSurface(texte, NULL, windowSurface, &position);

    machaine.str(" ");
    machaine2.str(" ");
    SDL_FreeSurface(texte);

    position.x = 880;
    position.y = 200;
    machaine << "PV joueur: " <<vieJoueur[1];
    texte = TTF_RenderText_Solid(police, machaine.str().c_str(), couleur);
    SDL_BlitSurface(texte, NULL, windowSurface, &position);
    SDL_FreeSurface(texte);
    position.x = 880;
    position.y = 170;
    machaine2 << nomsJoueur[1];
    texte = TTF_RenderText_Solid(police, machaine2.str().c_str(), couleur);
    SDL_BlitSurface(texte, NULL, windowSurface, &position);
    machaine.str(" ");
    machaine2.str(" ");
    SDL_FreeSurface(texte);


    TTF_CloseFont(police);
}


void lierCarteEtId(int imageID,  std::vector<Cartes*> & cartesJoueur )
{

    if(imageID == 0)
    {
        cartesJoueur.push_back( new CharacterCards("Venti",1,10,10,0,797,0,10,7,2));
        cartesJoueur[cartesJoueur.size()-1]->definirAttaque(0,2,1,1,3);
        cartesJoueur[cartesJoueur.size()-1]->definirAttaque(1,8,1,3,3);

    }
    else if(imageID == 1)
    {
        cartesJoueur.push_back( new CharacterCards("Tartaglia",1,10,10,1,797,0,10,7,2));
        cartesJoueur[cartesJoueur.size()-1]->definirAttaque(0,1,1,1,1);
        cartesJoueur[cartesJoueur.size()-1]->definirAttaque(1,5,1,3,1);
    }
    else if(imageID == 2)
    {
        cartesJoueur.push_back( new CharacterCards("Ningguang",1,10,10,2,797,0,10,7,2));
        cartesJoueur[cartesJoueur.size()-1]->definirAttaque(0,1,1,1,2);
        cartesJoueur[cartesJoueur.size()-1]->definirAttaque(1,3,1,2,2);
    }
    else if(imageID == 3)
    {
        cartesJoueur.push_back( new CharacterCards("Klee",1,10,10,3,797,0,10,7,2));
        cartesJoueur[cartesJoueur.size()-1]->definirAttaque(0,1,1,1,4);
        cartesJoueur[cartesJoueur.size()-1]->definirAttaque(1,5,1,3,4);
    }
    else if(imageID == 4)
    {
        cartesJoueur.push_back( new CharacterCards("Bennett",1,10,10,4,797,0,10,7,2));
        cartesJoueur[cartesJoueur.size()-1]->definirAttaque(0,2,1,1,4);
        cartesJoueur[cartesJoueur.size()-1]->definirAttaque(1,5,1,2,4);
    }
    else if(imageID == 5)
    {
        cartesJoueur.push_back( new CharacterCards("Klee",1,10,10,5,797,0,10,7,2));
        cartesJoueur[cartesJoueur.size()-1]->definirAttaque(0,1,1,1,4);
        cartesJoueur[cartesJoueur.size()-1]->definirAttaque(1,8,1,3,4);
    }
    else if(imageID == 6)
    {
        cartesJoueur.push_back( new CharacterCards("Mona",1,10,10,6,797,0,10,7,2));
        cartesJoueur[cartesJoueur.size()-1]->definirAttaque(0,2,1,1,1);
        cartesJoueur[cartesJoueur.size()-1]->definirAttaque(1,10,1,4,1);
    }
    else if(imageID == 7)
    {
        cartesJoueur.push_back( new CharacterCards("Jean",1,10,10,7,797,0,10,7,2));
        cartesJoueur[cartesJoueur.size()-1]->definirAttaque(0,3,1,1,3);
        cartesJoueur[cartesJoueur.size()-1]->definirAttaque(1,10,1,4,3);
    }
    else if(imageID == 8)
    {
        cartesJoueur.push_back( new CharacterCards("Noelle",1,10,10,8,797,0,10,7,2));
        cartesJoueur[cartesJoueur.size()-1]->definirAttaque(0,2,1,1,2);
        cartesJoueur[cartesJoueur.size()-1]->definirAttaque(1,6,1,3,2);
    }
    else if(imageID == 9)
    {
        cartesJoueur.push_back( new CharacterCards("Zhongli",1,10,10,9,797,0,10,7,2));
        cartesJoueur[cartesJoueur.size()-1]->definirAttaque(0,2,1,1,2);
        cartesJoueur[cartesJoueur.size()-1]->definirAttaque(1,10,1,4,2);
    }
    else if(imageID == 10)
    {
        cartesJoueur.push_back( new CharacterCards("Sucrose",1,10,10,10,797,0,10,7,2));
        cartesJoueur[cartesJoueur.size()-1]->definirAttaque(0,1,1,1,3);
        cartesJoueur[cartesJoueur.size()-1]->definirAttaque(1,3,1,2,3);
    }
    else if(imageID == 11)
    {
        cartesJoueur.push_back( new CharacterCards("Barbara",1,10,10,11,797,0,10,7,2));
        cartesJoueur[cartesJoueur.size()-1]->definirAttaque(0,2,1,1,1);
        cartesJoueur[cartesJoueur.size()-1]->definirAttaque(1,4,1,2,1);
    }
    else if(imageID == 12)
    {
        cartesJoueur.push_back( new TrainerCards("abondance",2,10,10,12,0,0,4,1));
    }
    else if(imageID == 13)
    {
        cartesJoueur.push_back( new TrainerCards("benediction",2,10,10,13,0,0,1,-4));
    }
    else if(imageID == 14)
    {
        cartesJoueur.push_back( new TrainerCards("fleches",2,10,10,14,0,0,3,8));
    }
    else if(imageID == 15)
    {
        cartesJoueur.push_back( new TrainerCards("malediction",2,10,10,15,0,0,2,4));
    }
    else if(imageID == 16)
    {
        cartesJoueur.push_back( new TrainerCards("poison",2,10,10,16,0,0,6,-8));
    }
    else if(imageID == 17)
    {
        cartesJoueur.push_back( new TrainerCards("potion",2,10,10,17,0,0,5,6));
    }

    /*for(size_t i = 0; i < cartesJoueur.size(); i ++)
    {
        temp = cartesJoueur[i]->getImage();
        if(temp== 0)
        {

            cartesJoueur[i]->definirAttaque(0,2,1,1,3);
            cartesJoueur[i]->definirAttaque(1,8,1,3,3);

        }
        else if(temp == 1)
        {

            cartesJoueur[i]->definirAttaque(0,1,1,1,1);
            cartesJoueur[i]->definirAttaque(1,5,1,3,1);
        }
        else if(temp == 2)
        {

            cartesJoueur[i]->definirAttaque(0,1,1,1,2);
            cartesJoueur[i]->definirAttaque(1,3,1,2,2);
        }
        else if(temp == 3)
        {

            cartesJoueur[i]->definirAttaque(0,1,1,1,4);
            cartesJoueur[i]->definirAttaque(1,5,1,3,4);
        }
        else if(temp == 4)
        {

            cartesJoueur[i]->definirAttaque(0,2,1,1,4);
            cartesJoueur[i]->definirAttaque(1,5,1,2,4);
        }
        else if(temp == 5)
        {

            cartesJoueur[i]->definirAttaque(0,1,1,1,4);
            cartesJoueur[i]->definirAttaque(1,8,1,3,4);
        }
        else if(temp == 6)
        {

           cartesJoueur[i]->definirAttaque(0,2,1,1,1);
            cartesJoueur[i]->definirAttaque(1,10,1,4,1);
        }
        else if(temp == 7)
        {

            cartesJoueur[i]->definirAttaque(0,3,1,1,3);
            cartesJoueur[i]->definirAttaque(1,10,1,4,3);
        }
        else if(temp == 8)
        {

            cartesJoueur[i]->definirAttaque(0,2,1,1,2);
            cartesJoueur[i]->definirAttaque(1,6,1,3,2);
        }
        else if(temp == 9)
        {

            cartesJoueur[i]->definirAttaque(0,2,1,1,2);
            cartesJoueur[i]->definirAttaque(1,10,1,4,2);
        }
        else if(temp== 10)
        {

            cartesJoueur[i]->definirAttaque(0,1,1,1,3);
            cartesJoueur[i]->definirAttaque(1,3,1,2,3);
        }
        else if(temp == 11)
        {

            cartesJoueur[i]->definirAttaque(0,2,1,1,1);
            cartesJoueur[i]->definirAttaque(1,4,1,2,1);
        }

    }*/
}


void lierEnergiesEtID(int imageID,std::vector<EnergyCards> & energiesJoueur)
{
    if(imageID -17 == 1)
    {
        energiesJoueur.push_back( EnergyCards("Carte1",3,10,1,1,797,0,1));
    }
    else if(imageID - 17== 2)
    {
        energiesJoueur.push_back( EnergyCards("Carte1",3,10,1,1,797,0,2));
    }
    else if(imageID - 17 == 3)
    {
        energiesJoueur.push_back( EnergyCards("Carte1",3,10,1,1,797,0,2));
    }
    else if(imageID - 17== 4)
    {
        energiesJoueur.push_back( EnergyCards("Carte1",3,10,1,1,797,0,2));
    }
}


void afficherTour(int & affTour, SDL_Surface* tour,SDL_Surface  *windowSurface)
{
    SDL_Rect position;

    position.x = 750;
    position.y = 400;

    if(affTour != 0)
    {
        SDL_BlitSurface(tour, NULL, windowSurface, &position);
        affTour++;
        if(affTour == 45)
        {
            affTour = 0;
        }
    }
}

void afficherChat(std::vector<std::string> & chat,SDL_Surface *texte,SDL_Surface *fondChat,TTF_Font *police,SDL_Surface  *windowSurface,std::stringstream & message)
{
    SDL_Rect position;
    SDL_Color couleur = {255, 255, 255};
    std::stringstream machaine;

    police = TTF_OpenFont("ARLRDBD.TTF", 30);


    position.x = 560;
    position.y = 200;


    SDL_BlitSurface(fondChat, NULL, windowSurface, &position);

    for(int i = 0; i<11; i ++)
    {
        position.x = 600;
        position.y = 220 + i*35;
        machaine <<chat[i];
        texte = TTF_RenderText_Solid(police, machaine.str().c_str(), couleur);
        SDL_BlitSurface(texte, NULL, windowSurface, &position);
        SDL_FreeSurface(texte);
        machaine.str(" ");
    }

    position.x = 600;
    position.y = 220 + 385;

    texte = TTF_RenderText_Solid(police, message.str().c_str(), couleur);
    SDL_BlitSurface(texte, NULL, windowSurface, &position);
    SDL_FreeSurface(texte);

    TTF_CloseFont(police);

}

void ajouterMessage(std::vector<std::string> & chat,std::string tempEnvoie)
{
    chat.erase(chat.begin());
    chat.push_back(tempEnvoie);

}

void initaliserMain(std::vector<int> & mainJoueurINT,std::vector< std::vector<Cartes*> >  & cartesJoueur,std::vector<EnergyCards> & energiesJoueur)
{
    for(int i = 0; i<6; i++)
    {
        if(mainJoueurINT[0] <18)
        {
            lierCarteEtId(mainJoueurINT[0],cartesJoueur[0]);
        }
        else
        {
            lierEnergiesEtID(mainJoueurINT[0],energiesJoueur);

        }

        mainJoueurINT.erase(mainJoueurINT.begin());

    }
    actualiserPositionCartes(cartesJoueur);
    actualiserEnergies(energiesJoueur);
}
