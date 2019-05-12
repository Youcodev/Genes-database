/*******************************************************************
* Fichier     : Foncteur.h										   *
* Auteur      : Gergi Younis									   *
* Travail     : TP5												   *
* Description : D�finition et impl�mentation de tous les foncteurs *
********************************************************************/
#ifndef FONCTEUR_H
#define FONCTEUR_H

#include "Gene.h"

class MemeId {
public:
//Constructeur par param�tres
	MemeId(int id): id_(id) {}

/****************************************************************************************
* Fonction : operator ()																*
* Description : Surcharge de l'op�rateur () pour chercher un g�ne d'un id donn�		    *
* Param�tres : L'adresse du g�ne � comparer 											*
* Valeur de retour : True si l'id du g�ne pass� en argument est celui du g�ne recherch�	*
*****************************************************************************************/
	bool operator () (Gene* gene) const {
		return gene->getId() == id_;
	}
private:
	int id_; //id de r�f�rence auquel sera compar� l'id du g�ne pass� en argument
};

class MemeEspece {
public:
	//Constructeur par param�tres
	MemeEspece(const string& espece) : espece_(espece) {}

/******************************************************************************************************
* Fonction : operator ()																			  *
* Description : Surcharge de l'op�rateur () pour v�rifier s'il s'agit de g�nes de la m�me esp�ce	  *
* Param�tres : L'adresse du g�ne � comparer															  *
* Valeur de retour : True si le g�ne pass� en argument appartient � la m�me esp�ce du g�ne recherch�  *
*******************************************************************************************************/
	bool operator () (Gene* gene) const {
		return gene->getEspece() == espece_;
	}
private:
	string espece_ ; //esp�ce de r�f�rence � laquelle sera compar�e celle du g�ne pass� en argument
};

class MemeNom {
public:
	//Constructeur par param�tres
	MemeNom(const string& nom) : nom_(nom) {}

/**********************************************************************************************
* Fonction : operator ()																	  *
* Description : Surcharge de l'op�rateur () pour chercher un g�ne d'un nom donn�			  *
* Param�tres : L'adresse du g�ne � comparer													  *
* Valeur de retour : True si le g�ne pass�e en argument poss�de le m�me nom du g�ne recherch� *
***********************************************************************************************/
	bool operator () (Gene* gene) const {
		return gene->getNom() == nom_;
	}
private:
	string nom_; //nom de r�f�rence auquel sera compar� le nom du g�ne pass� en argument
};

class TriParLongueur {
/************************************************************************************************
* Fonction : operator ()																		*
* Description : Surcharge de l'op�rateur () pour comparer la longueur de contenu de deux g�nes	*
* Param�tres : Les adresses des g�nes � comparer												*
* Valeur de retour : True si la longueur du contenu du premier g�ne est inf�rieure				*
*					 � celle du second															*
*************************************************************************************************/
public:
	bool operator () (Gene* gene1, Gene* gene2) const {
		return (gene1->getContenu()).length() < (gene2->getContenu()).length();
	}
};

class TriParEspeceEtNom {
/*********************************************************************************
* Fonction : operator ()														 *
* Description : Surcharge de l'op�rateur () pour comparer l'esp�ce et le nom de  *
*				deux g�nes, par ordre alphab�tique								 *
* Param�tres : Les adresses des g�nes � comparer								 *
* Valeur de retour : True si le premier g�ne est alphab�tiquement 				 *
*					 inf�rieure au second, en termes d'esp�ce puis de nom		 *
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
* Description : Surcharge de l'op�rateur () pour d�truire tous les g�nes d'un conteneur	*
* Param�tres : Adresse du g�ne � d�truire 												*
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
* Description : Surcharge de l'op�rateur () pour d�truire tous les g�nes d'une esp�ce donn�e *
* Param�tres : Adresse du g�ne de l'esp�ce � d�truire 										 *
* Valeur de retour : True si le g�ne a �t� d�truit											 *
**********************************************************************************************/
	bool operator () (Gene * gene) const {
		if (gene->getEspece() == espece_) {
			delete gene;
			return true;
		}
		return false;
	}
private:
	string espece_; //esp�ce de r�f�rence � laquelle sera compar�e celle du g�ne pass� en argument
};

class ModifierNom {
public:
	ModifierNom(const string& espece, const map<string, string>& noms) : espece_(espece), noms_(noms) {}
/*****************************************************************************************
* Fonction : operator ()																 *
* Description : Surcharge de l'op�rateur () pour modifier des noms d'une esp�ce donn�e   *
* Param�tres : Adresse du g�ne de l'esp�ce dont des noms sont � modifier et une map dont *
*			   la cl� repr�sente le nom � modifier et dont la valeur associ�e � la cl�   * 
*			   repr�sente le nouveau nom												 *
* Valeur de retour : True si la modofication a r�ussi									 *
* Note : Ce foncteur a �t� ajout� pour proposer une alternative d'impl�mentation un peu  *
*		 plus compacte de la m�thode modifierNoms(). Une solution sans ce foncteur est   *
*		 �galement impl�ment�e
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