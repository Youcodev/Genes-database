/********************************************************************************
* Fichier     : main.cpp														*
* Auteur      : Gergi Younis													*
* Travail     : TP5																*
* Description : Programme principal de la gestion de la base de donnée de gènes *
*********************************************************************************/
#include <iostream>
#include <fstream>
#include <clocale>
#include "conteneurGenesListe.h"
#include "conteneurGenesMap.h"
#include "conteneurGenes.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "");
	char c;
	ConteneurGenes* genes;
	
	// Le conteneur a deux implementations parmi lesquelles on choisit
	cout << "---  Voulez-vous utiliser la version liste (1) ou la version map (2) ? " << endl;
	do {
		cin.get(c);
	} while (c != '1' && c != '2');

	if (c == '1') {
		cout << "Utilisation de la version LISTE" << endl;
		genes = new ConteneurGenesListe(); 
	} else {
		cout << "Utilisation de la version MAP" << endl;
		genes = new ConteneurGenesMap();
	}
	
	//	ouverture du fichier de donnees
	ifstream fichier;
	fichier.open("genes.txt");
	if (fichier.fail()) {
		cout << "Fichier non trouve !\n" << endl;
		return 1;
	}
	// Lecture des entrees de chaque gene
	string nom, description, espece, contenu, id;
	getline(fichier, id);
	while (!fichier.eof()) {
		getline(fichier,nom);
		getline(fichier,description);
		getline(fichier,espece);
		getline(fichier,contenu);
		genes->inserer(atoi(id.c_str()), nom, description, espece, contenu);
		getline(fichier,id);
	}
	fichier.close();

	cout << "----------------------------------------------------------" << endl;
	cout << "AFFICHAGE PAR ESPECE ET NOM\n" << endl;
	// !!!!  A FAIRE: afficher les gènes par espèce et nom dans la sortie standard
	genes->afficherParEspeceEtNom(cout);

	cout << "----------------------------------------------------------" << endl;
	cout << "RECHERCHE DU GENE 25107" << endl;
	// !!!! A FAIRE: rechercher et afficher le gène ayant l'ID 25107
	// Le programme doit afficher "Le gène 25107 n'a pas été trouvé" si le géne n'est pas trouvé
	if (genes->trouver(25107) != nullptr)
		genes->afficherEspece((genes->trouver(25107))->getEspece(), cout);

	cout << "----------------------------------------------------------" << endl;
	cout << "RETRAIT DU GENE 2290" << endl;
	// !!!! A FAIRE: retirer le gène 2290
	// Le programme doit afficher "Le gène a été retiré" si le retrait réussit, 
	// ou bien "Le gène 2290 n'a pas été trouvé" si le retrait échoue
	genes->retirer(2290);
	
	cout << "----------------------------------------------------------" << endl;
	cout << "RETRAIT DE L'ESPECE HOMO SAPIENS" << endl;
	// !!!! A FAIRE: retirer tous les gènes de l'espèce Homo sapiens
	// Le programme doit afficher le nombre de gènes retirés ("Nombre de genes retires = XX")
	genes->retirerEspece("Homo sapiens");

	cout << "----------------------------------------------------------" << endl;
	cout << "RETRAIT DU GENE 552" << endl;
	// !!!! A FAIRE: retirer le gène 552
	// Le programme doit afficher "Le gène a été retiré" si le retrait réussit, 
	// ou bien "Le gène 552 n'a pas été trouvé" si le retrait échoue
	genes->retirer(552);

	cout << "----------------------------------------------------------" << endl;
	cout << "MODIFICATION DU NOM DES GENES DE Mus musculus: Avpr1a-->XXXXX, Fmr1-->YYYYY et UwtA1-->ZZZZZ" << endl;
	// !!!! A FAIRE: modifier le nom des gènes suivants pour l'espèce Mus musculus
	// Gène Avpr1a --> nouveau nom = "XXXXX"
	// Gène Fmr1 --> nouveau nom = "YYYYY"
	// Gène UwtA1 --> nouveau nom = "ZZZZZ"
	// Le programme doit afficher le nombre de gènes modifiés ("Modification de XX nom(s) effectuée")
	map<string, string> m;
	m.insert(make_pair("Avpr1a", "XXXXX"));
	m.insert(make_pair("Fmr1", "YYYYY"));
	m.insert(make_pair("UwtA1", "ZZZZZ"));
	genes->modifierNoms("Mus musculus", m);

	cout << "----------------------------------------------------------" << endl;
	cout << "AFFICHAGE PAR LONGEUR\n" << endl;
	// !!!! A FAIRE: afficher les gènes par longueur
	genes->afficherParLongueur(cout);

	// !!!! A FAIRE: N'OUBLIEZ PAS DE RÉPONDRE AUX QUESTIONS DANS UN FICHIER TEXTE !!!!
	// Il n'y a aucune question dans l'énoncé à laquelle il est demandé de répondre dans un fichier texte !

	delete genes;

	return 0;
}