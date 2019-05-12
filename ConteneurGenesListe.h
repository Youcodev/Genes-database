/*******************************************************
* Fichier     : ConteneurGenesListe.h				   *
* Auteur      : Gergi Younis						   *
* Travail     : TP5									   *
* Description : D�finition de la classe liste de g�nes *
********************************************************/
#ifndef CONTENEURGENESLISTE
#define CONTEURGENESLISTE

#include <list>
#include <algorithm>
#include <iterator>
#include "ConteneurGenes.h"
#include "Foncteur.h"

class ConteneurGenesListe : public ConteneurGenes  {
public:
// Constructeur par d�faut
	ConteneurGenesListe();

// Destructeur
	~ConteneurGenesListe();

/****************************************************************
* Fonction : inserer()											*
* Description : Ajoute un g�ne dans la liste des g�nes			*
* Param�tres : Des caract�ristiques du g�ne :					*
*			   Identifiant, Nom, description, esp�ce et contenu *
* Valeur de retour : Aucune										*
*****************************************************************/
	virtual void inserer(unsigned int id, const string &nom, const string &desc, 
		const string &espece, const string &contenu);

/*******************************************************************************
* Fonction : trouver()														   *
* Description : Recherche un g�ne � partir de son id						   *
* Param�tres : L'id du g�ne recherch� 										   *
* Valeur de retour : Adresse du g�ne recherch�								   *
* Note : Cette fonction retourne un pointeur nul si le g�ne n'a pas �t� trouv� *
********************************************************************************/
	virtual Gene* trouver(unsigned int id) const;

/************************************************************************
* Fonction : retirer()													*
* Description : Retire un g�ne de la liste des g�nes � partir de son id	*
* Param�tres : L'id du g�ne � retirer 									*
* Valeur de retour : True si le g�ne a pu �tre retir�					*
*************************************************************************/
	virtual bool retirer(unsigned int id);

/**********************************************************
* Fonction : retirerEspece()							  *
* Description : Retire tous les g�nes d'une esp�ce donn�e *
* Param�tres : L'esp�ce � retirer 						  *
* Valeur de retour : Nombre de g�nes retir�s			  *
***********************************************************/
	virtual unsigned int retirerEspece(const string &espece);

/************************************************************
* Fonction : vider()										*
* Description : Retire tous les g�nes de la liste des g�nes *
* Param�tres : Aucun 										*
* Valeur de retour : Aucune									*
*************************************************************/
	virtual void vider();

/********************************************************************
* Fonction : afficherParLongueur()									*
* Description : Affiche les g�nes par ordre croissant de longueur   *
* Param�tres : Flux de sortie (stream)								*
* Valeur de retour : Aucune											*
*********************************************************************/
	virtual void afficherParLongueur(ostream& out) const;

/****************************************************************************************
* Fonction : afficherParEspeceEtNom()													*
* Description : Affiche les g�nes par ordre alphab�tique d'esp�ce et pour chaque esp�ce *
*				par ordre alphab�tique de nom											*
* Param�tres : Flux de sortie (stream)													*
* Valeur de retour : Aucune																*
*****************************************************************************************/
	virtual void afficherParEspeceEtNom(ostream& out) const;

/**********************************************************************************
* Fonction : afficherEspece()													  *
* Description : Affiche tous les g�nes d'une esp�ce donn�e						  *
* Param�tres : Flux de sortie (stream) et l'esp�ce dont les g�nes sont � afficher *
* Valeur de retour : Aucune														  *
***********************************************************************************/
	virtual void afficherEspece(const string &espece, ostream& out) const;

/****************************************************************************
* Fonction : modifierNoms()													*
* Description : Modifie le nom de g�nes d'une esp�ce donn�e 				*
* Param�tres : L'esp�ce dont les noms de g�nes sont � modifier				*
*			   et une map dont la cl� repr�sente le nom du g�ne � modifier	*
*			   et dont la valeur associ�e repr�sente le nouveau nom d�sir�	*
* Valeur de retour : Nombre de noms modifi�s								*
*****************************************************************************/
	virtual unsigned int modifierNoms(const string &espece, const map<string, string> &noms);

private:
	list<Gene*> listeGenes_;
};


#endif // !CONTENEURGENESLISTE
