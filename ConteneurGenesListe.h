/*******************************************************
* Fichier     : ConteneurGenesListe.h				   *
* Auteur      : Gergi Younis						   *
* Travail     : TP5									   *
* Description : Définition de la classe liste de gènes *
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
// Constructeur par défaut
	ConteneurGenesListe();

// Destructeur
	~ConteneurGenesListe();

/****************************************************************
* Fonction : inserer()											*
* Description : Ajoute un gène dans la liste des gènes			*
* Paramètres : Des caractéristiques du gène :					*
*			   Identifiant, Nom, description, espèce et contenu *
* Valeur de retour : Aucune										*
*****************************************************************/
	virtual void inserer(unsigned int id, const string &nom, const string &desc, 
		const string &espece, const string &contenu);

/*******************************************************************************
* Fonction : trouver()														   *
* Description : Recherche un gène à partir de son id						   *
* Paramètres : L'id du gène recherché 										   *
* Valeur de retour : Adresse du gène recherché								   *
* Note : Cette fonction retourne un pointeur nul si le gène n'a pas été trouvé *
********************************************************************************/
	virtual Gene* trouver(unsigned int id) const;

/************************************************************************
* Fonction : retirer()													*
* Description : Retire un gène de la liste des génes à partir de son id	*
* Paramètres : L'id du gène à retirer 									*
* Valeur de retour : True si le gène a pu être retiré					*
*************************************************************************/
	virtual bool retirer(unsigned int id);

/**********************************************************
* Fonction : retirerEspece()							  *
* Description : Retire tous les gènes d'une espèce donnée *
* Paramètres : L'espèce à retirer 						  *
* Valeur de retour : Nombre de gènes retirés			  *
***********************************************************/
	virtual unsigned int retirerEspece(const string &espece);

/************************************************************
* Fonction : vider()										*
* Description : Retire tous les gènes de la liste des gènes *
* Paramètres : Aucun 										*
* Valeur de retour : Aucune									*
*************************************************************/
	virtual void vider();

/********************************************************************
* Fonction : afficherParLongueur()									*
* Description : Affiche les gènes par ordre croissant de longueur   *
* Paramètres : Flux de sortie (stream)								*
* Valeur de retour : Aucune											*
*********************************************************************/
	virtual void afficherParLongueur(ostream& out) const;

/****************************************************************************************
* Fonction : afficherParEspeceEtNom()													*
* Description : Affiche les gènes par ordre alphabétique d'espèce et pour chaque espèce *
*				par ordre alphabétique de nom											*
* Paramètres : Flux de sortie (stream)													*
* Valeur de retour : Aucune																*
*****************************************************************************************/
	virtual void afficherParEspeceEtNom(ostream& out) const;

/**********************************************************************************
* Fonction : afficherEspece()													  *
* Description : Affiche tous les gènes d'une espèce donnée						  *
* Paramètres : Flux de sortie (stream) et l'espèce dont les gènes sont à afficher *
* Valeur de retour : Aucune														  *
***********************************************************************************/
	virtual void afficherEspece(const string &espece, ostream& out) const;

/****************************************************************************
* Fonction : modifierNoms()													*
* Description : Modifie le nom de gènes d'une espèce donnée 				*
* Paramètres : L'espèce dont les noms de gènes sont à modifier				*
*			   et une map dont la clé représente le nom du gène à modifier	*
*			   et dont la valeur associée représente le nouveau nom désiré	*
* Valeur de retour : Nombre de noms modifiés								*
*****************************************************************************/
	virtual unsigned int modifierNoms(const string &espece, const map<string, string> &noms);

private:
	list<Gene*> listeGenes_;
};


#endif // !CONTENEURGENESLISTE
