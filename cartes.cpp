#include "prototypes.h"

Cartes::Cartes(std::string name, int type, int value, int rarity,int numImage,int posX,int posY)
{
    m_name=name;
    m_type=type;
    m_value=value;
    m_rarity=rarity;
    m_numImage = numImage;
    m_position.x = posX;
    m_position.y = posY;
}

CharacterCards::CharacterCards(std::string name, int type, int value, int rarity,int numImage,int posX,int posY,int atk, int hp, int critique):Cartes(name,type,value,rarity,numImage,posX,posY),m_atk(atk),m_hp(hp),m_critique(critique)
{

}

EnergyCards::EnergyCards(std::string name, int type, int value, int rarity,int numImage,int posX,int posY,int elem):Cartes(name,type,value,rarity,numImage,posX,posY),m_elem(elem)
{

}

TrainerCards::TrainerCards(std::string name, int type, int value, int rarity,int numImage,int posX,int posY,int typeT,int valeurT):Cartes(name,type,value,rarity,numImage,posX,posY),m_typeT(typeT),m_valeurT(valeurT)
{

}

int Cartes::getImage()
{
    return m_numImage;
}

int Cartes::getType()
{
    return m_type;
}


SDL_Rect Cartes::getPosition() const
{

    return m_position;
}

void Cartes::setPosition(int posX, int posY)
{

    m_position.x = posX;
    m_position.y = posY;

}

int CharacterCards::getVie() const
{
    return m_hp;
}

void Cartes::getName() const
{
    std::cout<<m_name<<std::endl;
}

void CharacterCards::definirAttaque(int numAtt, int degat, int ID, int prix, int typeEnergie)
{
    m_attaque[numAtt].degat = degat;
    m_attaque[numAtt].ID = ID;
    m_attaque[numAtt].prix = prix;
    m_attaque[numAtt].typeEnergie = typeEnergie;
}

Attaque CharacterCards::getAttaque(int numAtt)
{
    return m_attaque[numAtt];
}

void CharacterCards::setVie(int deg)
{
    m_hp -= deg;
}

int EnergyCards::getElem() const
{
    return m_elem;
}


int TrainerCards::getTypeT() const
{
    return m_typeT;
}

int TrainerCards::getValeurT() const
{
    return m_valeurT;
}
