/**************************************************************
* Fichier     : ConteneurGenesMap.cpp						  *
* Auteur      : Gergi Younis								  *
* Travail     : TP5										      *
* Description : Impl�mentation de la classe multimap de g�nes *
***************************************************************/
#include <vector>
#include "ConteneurGenesMap.h"

ConteneurGenesMap::ConteneurGenesMap() : ConteneurGenes() {}

ConteneurGenesMap::~ConteneurGenesMap() {
// Appel de la fonction vider() qui d�salloue la zone m�moire du tas
// (afin d'�viter les fuites de m�moires suite aux allocations dynamiques des g�nes)
// et vide ensuite la map de son contenu (de ses pointeurs) r�duidant ainsi sa taille � 0
	vider();
}

void ConteneurGenesMap::inserer(unsigned int id, const string &nom, const string &desc,
	const string &espece, const string &contenu) {
// Les g�nes sont cr��s dynamiquement
	mapGenes_.insert(make_pair(espece, new Gene(id, nom, desc, espece, contenu)));
}

Gene* ConteneurGenesMap::trouver(unsigned int id) const {
// On utilise le mot-cl� auto � la place de multimap<string, Gene*>::const_iterator
	for (auto it = mapGenes_.begin(); it != mapGenes_.end(); ++it)
		if ((it->second)->getId() == id) // Si le g�ne ayant id comme identificateur est trouv�
		return it->second; // On y retourne un pointeur
	// Si le g�ne n'est pas trouv�, on retourne un pointeur nul
			cout << "Le g�ne" << id << "n'a pas �t� trouv�" << endl;
			return nullptr; 
}

bool ConteneurGenesMap::retirer(unsigned int id) {
// On utilise le mot cl� auto � la place de multimap<int, Gene*>::iterator
	for (auto it = mapGenes_.begin(); it != mapGenes_.end(); ++it)
		if ((it->second)->getId() == id) { // Si le g�ne est trouv�, on le d�truit
		delete it->second;
		mapGenes_.erase(it);
		cout << "Le g�ne a �t� retir�" << endl;
		return true;
	}
	// Si le g�ne n'est pas dans la map
	cout << "Le g�ne " << id << " n'a pas �t� trouv�" << endl;
	return false;
}

unsigned int ConteneurGenesMap::retirerEspece(const string &espece) {
// D�termination du nombre de g�nes pr�sents dans la map avant le retrait de l'esp�ce
	unsigned int i = mapGenes_.size();
// Retrait de tous les g�nes de l'esp�ce
	auto it = mapGenes_.begin();
	while (it != mapGenes_.end()) {
		if (it->first == espece) {
			delete it->second;
			mapGenes_.erase(it++);
		}
		else
			++it;
	}
// Retourner le nombre de g�nes restants dans la map
	cout << "Nombre de genes retires = " << i - mapGenes_.size() << endl;
	return (i - mapGenes_.size());
}

void ConteneurGenesMap::vider() {
// On d�truit d'abord les g�nes en lib�rant les zones m�moires allou�es dynamiquement
	for (auto it = mapGenes_.begin(); it != mapGenes_.end(); ++it)
		delete it->second;
// Ensuite on vide la map de son contenu (les pointeurs)
	mapGenes_.erase(mapGenes_.begin(), mapGenes_.end());
}

void ConteneurGenesMap::afficherParLongueur(ostream& out) const {
// Utilisation du pr�dicat binaire TriParLongueur comme crit�re de comparaison
// pour trier les g�nes selon la longueur de leurs contenus
// Cr�ation d'abord d'une multimap temporaire sur laquelle il est possible d'appliquer le pr�dicat
	multimap<Gene*, Gene*, TriParLongueur> temp;
	for (auto it = mapGenes_.begin(); it != mapGenes_.end(); ++it)
		temp.insert(make_pair(it->second, it->second));
	for (auto it = temp.begin(); it != temp.end(); ++it)
		out << it->second << endl;
}

void ConteneurGenesMap::afficherParEspeceEtNom(ostream& out) const {
// Utilisation du pr�dicat binaire TriParEspeceEtNom comme crit�re de comparaison
// pour trier les g�nes par ordre alphab�tique d'esp�ce et pour chaque esp�ce
// par ordre alphab�tique de nom
// Cr�ation d'abord d'une multimap temporaire sur laquelle il est possible d'appliquer le pr�dicat
	multimap<Gene*, Gene*, TriParEspeceEtNom> temp;
	for (auto it = mapGenes_.begin(); it != mapGenes_.end(); ++it)
		temp.insert(make_pair(it->second, it->second));
	for (auto it = temp.begin(); it != temp.end(); ++it)
		out << it->second << endl;
}

void ConteneurGenesMap::afficherEspece(const string &espece, ostream& out) const {
	for (auto it = mapGenes_.begin(); it != mapGenes_.end(); ++it) {
		if (it->first == espece) // L'esp�ce �tant la cl� de la multimap
		out << it->second; // On y affiche le g�ne correspondant
		}
}

unsigned int ConteneurGenesMap::modifierNoms(const string &espece, const map<string, string> &noms) {
	unsigned int nbrNomsModif = 0; // Pour compter le nombre de modifications
	auto itNoms = noms.begin();
	auto itMap = mapGenes_.begin();
	// On parcourt la map des noms
	for (itNoms; itNoms != noms.end(); ++itNoms) {
		// Tant qu'on a pas atteint la fin de la map et tant que l'esp�ce et le nom concern�s n'ont pas �t� trouv�s
		while (itMap != mapGenes_.end() && (itMap->first != espece || itNoms->first != itMap->second->getNom()))
			++itMap;
		// Pour chaque esp�ce concern�e, on proc�de � la modification, en rempla�ant le nom correspondant �
		// la cl� de la map des noms par celui correspond � la valeur associ�e � cette cl�
		if(itMap != mapGenes_.end()) {
			(itMap->second)->setNom(itNoms->second);
			// Apr�s chaque op�ration, on incr�mente le nombre de modifications
			++nbrNomsModif;
		}
	}
	cout << "Modification de " << nbrNomsModif << " nom(s) effectu�e" << endl;
	return nbrNomsModif;
}