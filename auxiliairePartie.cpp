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
        machaine << cartesJoueur[i]->getVie();
        texte = TTF_RenderText_Solid(police, machaine.str().c_str(), couleur);
        SDL_BlitSurface(texte, NULL, windowSurface, &position);
        machaine.str(" ");
        SDL_FreeSurface(texte);
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
        cartesJoueurTerrain[0][i]->setPosition(900 - ((cartesJoueurTerrain[0].size()-1)*70) + i*140, 600);

    }
    for(size_t i = 0; i < cartesJoueurTerrain[1].size(); i++)
    {
        cartesJoueurTerrain[1][i]->setPosition(900 - ((cartesJoueurTerrain[1].size()-1)*70) + i*140, 350);

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
                    SDL_BlitSurface(imageCache[cartesJoueurTerrain[0][carteDetail ]->getImage()-1], NULL, windowSurface, &position);
                    machaine << cartesJoueur[0][carteDetail ]->getVie();
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
                    SDL_BlitSurface(imageCache[cartesJoueurTerrain[1][carteDetail ]->getImage()-1], NULL, windowSurface, &position);
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
                    SDL_BlitSurface(imageCache[cartesJoueur[0][carteDetail ]->getImage()-1], NULL, windowSurface, &position);
                    machaine << cartesJoueur[0][carteDetail ]->getVie() ;
                    texte = TTF_RenderText_Solid(police, machaine.str().c_str(), couleur);
                    SDL_BlitSurface(texte, NULL, windowSurface, &position);
                    machaine.str(" ");
                    SDL_FreeSurface(texte);
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

    for(size_t i =0; i<energiesJoueur.size();i++)
    {
        if(energiesJoueur[i].getElem() == 1)
        {
            energiesJoueur[i].setPosition(0,900 + cond*25);
            cond ++;
        }


    }
    cond = 0;

    for(size_t i =0; i<energiesJoueur.size();i++)
    {
        if(energiesJoueur[i].getElem() == 2)
        {
            energiesJoueur[i].setPosition(50,900 + cond*25);
            cond ++;
        }


    }
    cond = 0;

    for(size_t i =0; i<energiesJoueur.size();i++)
    {
        if(energiesJoueur[i].getElem() == 3)
        {
            energiesJoueur[i].setPosition(100,900 + cond*25);
            cond ++;
        }


    }
    cond = 0;

    for(size_t i =0; i<energiesJoueur.size();i++)
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

    for(size_t i =0; i<energiesJoueur.size();i++)
    {
        position = energiesJoueur[i].getPosition();
        SDL_BlitSurface(imageCache[energiesJoueur[i].getImage()], NULL, windowSurface, &position);
    }
}

int testSiAttaquePossible(Attaque attaqueActive,std::vector<EnergyCards> & energiesJoueur, std::vector< std::vector<Cartes*> >  & cartesJoueurTerrain )
{
   // Attaque attaqueActive

    int resultat = 0;
    int typeCond = 0;
    int numCond = 0 ;
    int eraseCond = 0;

    for(size_t i = 0; i<energiesJoueur.size();i++)
    {
        if(energiesJoueur[i].getElem() == attaqueActive.typeEnergie)
        {
            numCond++;
        }
    }



    if(numCond >= attaqueActive.prix)
    {
        resultat=1;

        for (auto it = energiesJoueur.begin(); it != energiesJoueur.end(); )
        {
            if(it->getElem() == attaqueActive.typeEnergie && eraseCond < attaqueActive.prix)
            {
                it = energiesJoueur.erase(it);
                eraseCond ++;
            }

            it++;
        }

    }
    else
    {
        resultat = 0;
    }

    return resultat;




}

void actualiserDegats(int & ID, int & degats, std::vector< std::vector<Cartes*> >  & cartesJoueurTerrain )
{
    cartesJoueurTerrain[0][ID]->setVie(degats);
}

void afficherCartesAdverses(std::vector< std::vector<Cartes*> >  & cartesJoueur,int carteAdverse,std::vector<SDL_Surface*> & imageCache, SDL_Surface  *windowSurface)
{

    SDL_Rect position;

    for(size_t i = 0; i < cartesJoueur[1].size(); i++)
    {
        if(i == carteAdverse)
        {
            cartesJoueur[1][i]->setPosition(900 - ((cartesJoueur[1].size()-1)*50) + i*100, 50);
        }
        else
        {
            cartesJoueur[1][i]->setPosition(900 - ((cartesJoueur[1].size()-1)*50) + i*100, -50);
        }

        position = cartesJoueur[1][i]->getPosition();
        SDL_BlitSurface(imageCache[cartesJoueur[1][i]->getImage()], NULL, windowSurface, &position);

    }
}

void receiveData(int *activePlayer, sf::TcpSocket *socket, int &numJoueur, int *condition, int *ID1, int *ID2, int *degats, int *nbrCarte, int *selec,int *placeID)
{
    sf::Packet tempReceive;
    int receive = 0;
    sf::Packet paquet;
    sf::Packet realOne;
    std::string chaine;
    int continuer = 1;
    while(continuer != 9)
    {
            socket->receive(tempReceive);
            tempReceive >> receive;
            if(receive != 9)
            {
                socket->receive(realOne);
            }
            switch(receive)
            {
            case 1:
            {
                realOne >> chaine; //recevoir un texte
                std::cout << chaine << std::endl;
                break;
            }
            case 2:
            {
                realOne >> *ID1 >> *ID2 >> *degats; //recevoir une attaque
                std::cout << "ID1: " << *ID1 << std::endl << "ID2: " << *ID2 << std::endl << "degats: " << *degats << std::endl;
                break;
            }
            case 3:
            {
                realOne >> *nbrCarte;//nombre carte adversaire
                std::cout << "nbrCarte" << *nbrCarte << std::endl;
                break;
            }
            case 4:
            {
                realOne >> *selec;//carte selectionnee
                std::cout << "carte selec: " << *selec << std::endl;
                break;
            }
            case 5: //placer une carte
            {
                realOne >> *placeID;
                std::cout << "place ID: " << *placeID << std::endl;
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
                std::cout << *activePlayer << std::endl;
                break;
            }
            case 9:
            {
                continuer = 9;
                *condition = 0;
                break;
            }
            default:
            {
                std::cout << "erreur lors du choix de la reception" << std::endl;
                break;
            }
            }
        tempReceive.clear();
        paquet.clear();
        realOne.clear();
    }
}

void get_text_and_rect(SDL_Renderer *renderer, int x, int y, char *text, TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect)
{
    int text_width;
    int text_height;
    SDL_Surface *surface;
    SDL_Color textColor = {255, 255, 255, 0};

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
