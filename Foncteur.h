/*******************************************************************
* Fichier     : Foncteur.h										   *
* Auteur      : Gergi Younis									   *
* Travail     : TP5												   *
* Description : Définition et implémentation de tous les foncteurs *
********************************************************************/
#ifndef FONCTEUR_H
#define FONCTEUR_H

#include "Gene.h"

class MemeId {
public:
//Constructeur par paramètres
	MemeId(int id): id_(id) {}

/****************************************************************************************
* Fonction : operator ()																*
* Description : Surcharge de l'opérateur () pour chercher un gène d'un id donné		    *
* Paramètres : L'adresse du gène à comparer 											*
* Valeur de retour : True si l'id du gène passé en argument est celui du gène recherché	*
*****************************************************************************************/
	bool operator () (Gene* gene) const {
		return gene->getId() == id_;
	}
private:
	int id_; //id de référence auquel sera comparé l'id du gène passé en argument
};

class MemeEspece {
public:
	//Constructeur par paramètres
	MemeEspece(const string& espece) : espece_(espece) {}

/******************************************************************************************************
* Fonction : operator ()																			  *
* Description : Surcharge de l'opérateur () pour vérifier s'il s'agit de gènes de la même espèce	  *
* Paramètres : L'adresse du gène à comparer															  *
* Valeur de retour : True si le gène passé en argument appartient à la même espèce du gène recherché  *
*******************************************************************************************************/
	bool operator () (Gene* gene) const {
		return gene->getEspece() == espece_;
	}
private:
	string espece_ ; //espèce de référence à laquelle sera comparée celle du gène passé en argument
};

class MemeNom {
public:
	//Constructeur par paramètres
	MemeNom(const string& nom) : nom_(nom) {}

/**********************************************************************************************
* Fonction : operator ()																	  *
* Description : Surcharge de l'opérateur () pour chercher un gène d'un nom donné			  *
* Paramètres : L'adresse du gène à comparer													  *
* Valeur de retour : True si le gène passée en argument possède le même nom du gène recherché *
***********************************************************************************************/
	bool operator () (Gene* gene) const {
		return gene->getNom() == nom_;
	}
private:
	string nom_; //nom de référence auquel sera comparé le nom du gène passé en argument
};

class TriParLongueur {
/************************************************************************************************
* Fonction : operator ()																		*
* Description : Surcharge de l'opérateur () pour comparer la longueur de contenu de deux gènes	*
* Paramètres : Les adresses des gènes à comparer												*
* Valeur de retour : True si la longueur du contenu du premier gène est inférieure				*
*					 à celle du second															*
*************************************************************************************************/
public:
	bool operator () (Gene* gene1, Gene* gene2) const {
		return (gene1->getContenu()).length() < (gene2->getContenu()).length();
	}
};

class TriParEspeceEtNom {
/*********************************************************************************
* Fonction : operator ()														 *
* Description : Surcharge de l'opérateur () pour comparer l'espèce et le nom de  *
*				deux gènes, par ordre alphabétique								 *
* Paramètres : Les adresses des gènes à comparer								 *
* Valeur de retour : True si le premier gène est alphabétiquement 				 *
*					 inférieure au second, en termes d'espèce puis de nom		 *
**********************************************************************************/
public:
	bool operator () (Gene* gene1, Gene* gene2) const {
		return (gene1->getEspece() < gene2->getEspece() || 
			(gene1->getEspece() == gene2->getEspece() && gene1->getNom() < gene2->getNom()));
	}
};

class DetruireGenes {
/****************************************************************************************
* Fonction : operator ()																*
* Description : Surcharge de l'opérateur () pour détruire tous les gènes d'un conteneur	*
* Paramètres : Adresse du gène à détruire 												*
* Valeur de retour : Aucune																*
*****************************************************************************************/
public:
	void operator () (Gene* gene) const {
		delete gene;
		gene = nullptr;
	}
};

class DetruireEspece {
public:
	DetruireEspece(const string& espece): espece_(espece) {}
/*********************************************************************************************
* Fonction : operator ()																	 *
* Description : Surcharge de l'opérateur () pour détruire tous les gènes d'une espèce donnée *
* Paramètres : Adresse du gène de l'espèce à détruire 										 *
* Valeur de retour : True si le gène a été détruit											 *
**********************************************************************************************/
	bool operator () (Gene * gene) const {
		if (gene->getEspece() == espece_) {
			delete gene;
			return true;
		}
		return false;
	}
private:
	string espece_; //espèce de référence à laquelle sera comparée celle du gène passé en argument
};

class ModifierNom {
public:
	ModifierNom(const string& espece, const map<string, string>& noms) : espece_(espece), noms_(noms) {}
/*****************************************************************************************
* Fonction : operator ()																 *
* Description : Surcharge de l'opérateur () pour modifier des noms d'une espèce donnée   *
* Paramètres : Adresse du gène de l'espèce dont des noms sont à modifier et une map dont *
*			   la clé représente le nom à modifier et dont la valeur associée à la clé   * 
*			   représente le nouveau nom												 *
* Valeur de retour : True si la modofication a réussi									 *
* Note : Ce foncteur a été ajouté pour proposer une alternative d'implémentation un peu  *
*		 plus compacte de la méthode modifierNoms(). Une solution sans ce foncteur est   *
*		 également implémentée
******************************************************************************************/
	bool operator () (Gene* gene) {
		if (gene->getEspece() == espece_) {
			auto it = noms_.find(gene->getNom());
			if (it != noms_.end()) {
				gene->setNom(it->second);
				return true;
			}
		}
		return false;
	}
private:
	string espece_;
	map<string, string> noms_;
};

#endif // !FONCTEUR_H