#include "prototypes.h"
void actualiserImageDeck(std::vector<Cartes*> & cartesJoueur,std::vector<SDL_Surface*> & imageCache, SDL_Surface  *windowSurface,std::vector<int> selected)
{
    SDL_Rect position, position2, position3;
    for(size_t i = 0; i< cartesJoueur.size(); i++ )
    {
        if(selected[i] == 0)
        {
            position = cartesJoueur[i]->getPosition();
            SDL_BlitSurface(imageCache[cartesJoueur[i]->getImage()], NULL, windowSurface, &position);
        }
        else if(selected[i]==1)
        {
            position = cartesJoueur[i]->getPosition();
            position.x -= 42;
            position.y -= 59;
            SDL_BlitSurface(imageCache[cartesJoueur[i]->getImage()+18], NULL, windowSurface, &position);
        }
        else if(selected[i]==2)
        {
            position = cartesJoueur[i]->getPosition();
            position.x -= 42;
            position.y -= 59;
            position2 = position;
            position.x += 20;
            position.y +=27;
            SDL_BlitSurface(imageCache[cartesJoueur[i]->getImage()+18], NULL, windowSurface, &position);
            SDL_BlitSurface(imageCache[cartesJoueur[i]->getImage()+18], NULL, windowSurface, &position2);
        }
        else if(selected[i]==3)
        {
            position = cartesJoueur[i]->getPosition();
            position.x -= 42;
            position.y -= 59;
            position2 = position;
            position.x += 20;
            position.y +=27;
            position3 = position;
            position3.x += 20;
            position3.y += 27;
            SDL_BlitSurface(imageCache[cartesJoueur[i]->getImage()+18], NULL, windowSurface, &position);
            SDL_BlitSurface(imageCache[cartesJoueur[i]->getImage()+18], NULL, windowSurface, &position2);
            SDL_BlitSurface(imageCache[cartesJoueur[i]->getImage()+18], NULL, windowSurface, &position3);
        }

    }
}

void initDeckCartes(std::vector<SDL_Surface*> &imageCache)
{
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
}

void actualiserCarteDeck(std::vector<Cartes*>  &cartesPioche)
{
    int y = 100, x = 0;

    for(size_t i = 0; i < cartesPioche.size(); i++)
    {
        cartesPioche[i]->setPosition(100 + x*200, y);
        if(x==8)
        {
            x = 0;
            y+=250;
        }
        else{x++;}

    }
}

