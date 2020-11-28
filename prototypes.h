#ifndef PROTOTYPES_H_INCLUDED
#define PROTOTYPES_H_INCLUDED
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SFML/Network.hpp>
#include <functional>


struct Attaque {
  int degat;
  int ID;
  int prix;
  int typeEnergie;
} ;


class Cartes
{
protected:
    std::string m_name,m_description;
    int m_type;
    int m_value, m_rarity;
    SDL_Rect m_position;
    int m_numImage;

public:
    Cartes(std::string name, int type, int value, int rarity,int numImage,int posX,int posY);
    ~Cartes() {};

    void getName()const;
    int getImage();
    int getType ();
    SDL_Rect getPosition()const;
    void setPosition(int posX, int posY);
    virtual int getElem() const = 0;
    virtual int getVie() const = 0;
    virtual void setVie(int deg)  = 0;
    virtual void definirAttaque(int numAtt, int degat, int ID, int prix, int typeEnergie) = 0;
    virtual Attaque getAttaque(int numAtt) = 0;
    virtual int getTypeT() const = 0;
    virtual int getValeurT() const = 0;

};


class CharacterCards: public Cartes
{
private:
    int m_atk, m_hp, m_critique;
    Attaque m_attaque[2];


public :

    CharacterCards(std::string name, int type, int value, int rarity,int numImage,int posX,int posY,int atk, int hp, int critique);
    ~CharacterCards() {};

    virtual int getTypeT() const{}
    virtual int getValeurT() const{}
    virtual int getVie() const;
    virtual void setVie(int deg);
    virtual void definirAttaque(int numAtt, int degat, int ID, int prix, int typeEnergie);
    virtual Attaque getAttaque(int numAtt) ;

    virtual int getElem() const {}

};


class EnergyCards: public Cartes
{
private:
    int m_elem;

public :
    EnergyCards(std::string name, int type, int value, int rarity,int numImage,int posX,int posY,int elem);
    ~EnergyCards() {};

    virtual int getTypeT() const{}
    virtual int getValeurT() const{}
    virtual int getElem() const;
    virtual int getVie() const {}
    virtual void setVie(int deg){}
    virtual void definirAttaque(int numAtt, int degat, int ID, int prix, int typeEnergie){}
    virtual Attaque getAttaque(int numAtt) {}



};

class TrainerCards: public Cartes
{
private:
    int m_typeT;
    int m_valeurT;

public :
    TrainerCards(std::string name, int type, int value, int rarity,int numImage,int posX,int posY,int typeT, int valeurT);
    ~TrainerCards() {};

    virtual int getTypeT() const;
    virtual int getValeurT() const;
    virtual int getElem() const {}
    virtual int getVie() const {}
    virtual void setVie(int deg){}
    virtual void definirAttaque(int numAtt, int degat, int ID, int prix, int typeEnergie){}
    virtual Attaque getAttaque(int numAtt) {}


};



void actualiserPositionCartes(std::vector< std::vector<Cartes*> >  & cartesJoueur);
void libererMain(std::vector<Cartes*> & cartesJoueur);
int selectionCarte(std::vector<Cartes*> & cartesJoueur, int x, int y);
void actualiserPositionCartesT(std::vector< std::vector<Cartes*> >  & cartesJoueurTerrain);
void placerCarte(std::vector<Cartes*> & cartesJoueur,std::vector<Cartes*> & cartesJoueurTerrain,int carteSelec);
void actualiserImage(std::vector<Cartes*> & cartesJoueur,std::vector< std::vector<Cartes*> > & cartesJoueurTerrain,std::vector<SDL_Surface*> & imageCache, SDL_Surface  *windowSurface,SDL_Surface *texte,TTF_Font *police);
void afficherDetails(int & condDetail, int & carteDetail,std::vector< std::vector<Cartes*> >  & cartesJoueurTerrain,std::vector< std::vector<Cartes*> >  & cartesJoueur,SDL_Surface  *windowSurface,std::vector<SDL_Surface*> imageCache,SDL_Surface *texte,TTF_Font *police, sf::TcpSocket *client);
void lancerAttaque(int numAtt, int numCarte,std::vector< std::vector<Cartes*> >  & cartesJoueur,std::vector< std::vector<Cartes*> >  & cartesJoueurTerrain);

void afficherEnergies(std::vector<EnergyCards> & energiesJoueur,std::vector<SDL_Surface*> & imageCache, SDL_Surface  *windowSurface);
void actualiserEnergies(std::vector<EnergyCards> & energiesJoueur);
int testSiAttaquePossible(Attaque attaqueActive,std::vector<EnergyCards> & energiesJoueur, std::vector< std::vector<Cartes*> >  & cartesJoueurTerrain );
void receiveData(int *activePlayer, sf::TcpSocket *socket, int &numJoueur, int *condition, int *ID1, int *ID2, int *degats, int *nbrCarte, int *selec,int *placeID, std::vector<int> *TID1, std::vector<int> *TID2, std::vector<int> *Tdegats);
void actualiserDegats(int & ID1, int &ID2, int & degats, std::vector< std::vector<Cartes*> >  & cartesJoueurTerrain, int vieJoueur[], std::vector<int> &TID1, std::vector<int> &TID2, std::vector<int> &Tdegats);

void afficherCartesAdverses(std::vector< std::vector<Cartes*> >  & cartesJoueur,int carteAdverse,std::vector<SDL_Surface*> & imageCache, SDL_Surface  *windowSurface);
void jeu(int port, std::string nomJoueur, std::vector<int> mainJoueurINT);
void get_text_and_rect(SDL_Renderer *renderer, int x, int y, char *text, TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect,SDL_Color textColor = {255, 255, 255, 0});

void testSiCarteMorte(std::vector< std::vector<Cartes*> >  & cartesJoueurTerrain,std::vector< std::vector<Cartes*> > & cimetiere );
void afficherCimetiere(std::vector< std::vector<Cartes*> > & cimetiere,std::vector<SDL_Surface*> & imageCache, SDL_Surface  *windowSurface);

void actionTrainer(int selec,std::vector< std::vector<Cartes*> >  & cartesJoueurTerrain,std::vector< std::vector<Cartes*> >  & cartesJoueur,std::vector<EnergyCards> & energiesJoueur,int vieJoueur[2], sf::TcpSocket *socket);
void afficherPV(std::string *nomsJoueur,int vieJoueur[2],SDL_Surface *texte,TTF_Font *police,SDL_Surface  *windowSurface);
void lierCarteEtId(int imageID,  std::vector<Cartes*> & carteJoueur );
void lierEnergiesEtID(int imageID,std::vector<EnergyCards> & energiesJoueur);

void actualiserImageDeck(std::vector<Cartes*> & cartesJoueur,std::vector<SDL_Surface*> & imageCache, SDL_Surface  *windowSurface,std::vector<int> selected);
void actualiserCarteDeck(std::vector<Cartes*>  &cartesPioche);
void initDeckCartes(std::vector<SDL_Surface*> &imageCache);

void afficherTour(int & affTour, SDL_Surface* tour,SDL_Surface  *windowSurface);

#endif // PROTOTYPES_H_INCLUDED
