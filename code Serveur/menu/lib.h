#ifndef LIB_H
#define LIB_H

#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
#include <queue>
#include <ctime>
#include <functional>
#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <algorithm>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include <random>
#include "encrypt.h"

//password encryption https://github.com/philipperemy/easy-encryption
struct Users
{
	std::string username;
	sf::TcpSocket* client;
	int ID;
};


void launch_server(int number, std::string &nomJ1, std::string &nomJ2);
int accept_friend(std::string user, std::string friendName, int accept);
int ajouterAmi(std::string user, std::string friendName);
int retirerAmi(std::string user, std::string friendName);
void affichageAmi(std::string user, sf::TcpSocket* client);
void interaction_thread(int *size, int *queue,int *continuer, int *limit, int *energie);

int nbServ = 0;
#endif // LIB_H_INCLUDED