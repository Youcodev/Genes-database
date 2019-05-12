/*****************************************************************
* Fichier     : ConteneurGenes.h
* Auteur      : 
* Travail     : TP5
* Description : Définition de la classe abstraite ConteneurGenes
******************************************************************/
#ifndef _CONTENEUR_GENES_H_
#define _CONTENEUR_GENES_H_

#include "Gene.h"
#include <iostream>
#include <map>
using namespace std;

class ConteneurGenes
{
public:
	ConteneurGenes() { }
	virtual ~ConteneurGenes() {  }

	virtual void inserer(unsigned int id, const string &nom, const string &desc, const string &espece, const string &contenu) = 0;
	virtual Gene* trouver(unsigned int id) const = 0;

	virtual bool retirer(unsigned int id) = 0;
	virtual unsigned int retirerEspece(const string &espece) = 0;
	virtual void vider() = 0; 

	virtual void afficherParEspeceEtNom(ostream& out) const = 0;
	virtual void afficherParLongueur(ostream& out) const = 0;
	virtual void afficherEspece(const string &espece, ostream& out) const = 0;

	virtual unsigned int modifierNoms(const string &espece, const map<string, string> &noms) = 0;

};

#endif // _CONTENEUR_GENES_H_
