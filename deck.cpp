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
            SDL_BlitSurface(imageCache[cartesJoueur[i]->getImage()+12], NULL, windowSurface, &position);
        }
        else if(selected[i]==2)
        {
            position = cartesJoueur[i]->getPosition();
            position.x -= 42;
            position.y -= 59;
            position2 = position;
            position.x += 20;
            position.y +=27;
            SDL_BlitSurface(imageCache[cartesJoueur[i]->getImage()+12], NULL, windowSurface, &position);
            SDL_BlitSurface(imageCache[cartesJoueur[i]->getImage()+12], NULL, windowSurface, &position2);
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
            SDL_BlitSurface(imageCache[cartesJoueur[i]->getImage()+12], NULL, windowSurface, &position);
            SDL_BlitSurface(imageCache[cartesJoueur[i]->getImage()+12], NULL, windowSurface, &position2);
            SDL_BlitSurface(imageCache[cartesJoueur[i]->getImage()+12], NULL, windowSurface, &position3);
        }

    }
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

