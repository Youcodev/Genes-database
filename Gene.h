/************************************************
 * Fichier     : gene.h
 * Auteur      : 
 * Travail     : TP5
 * Description : Définition de la classe Gene
 ***********************************************/

#ifndef _GENE_H_
#define _GENE_H_

#include <iostream>
#include <string>

using namespace std;

class Gene
	{
	public:
		Gene(unsigned int id, string nom, string desc, string espece, string contenu);

		unsigned int getId() const;
		string getNom() const;
		string getEspece() const;
		string getDesc() const;
		string getContenu() const;

		void setNom(string nom);

		void afficher(ostream& out) const;


	private:
		int id_;			// identificateur du gène
		string nom_;		// nom d'usager du gène
		string espece_;		// nom de l'espèce
		string desc_;		// description du gène
		string contenu_;	// contenu en nucléotides
};

ostream& operator << (ostream& out, const Gene& gene);
ostream& operator << (ostream& out, Gene* gene);

#endif 
