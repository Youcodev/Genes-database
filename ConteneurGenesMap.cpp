/**************************************************************
* Fichier     : ConteneurGenesMap.cpp						  *
* Auteur      : Gergi Younis								  *
* Travail     : TP5										      *
* Description : Implémentation de la classe multimap de gènes *
***************************************************************/
#include <vector>
#include "ConteneurGenesMap.h"

ConteneurGenesMap::ConteneurGenesMap() : ConteneurGenes() {}

ConteneurGenesMap::~ConteneurGenesMap() {
// Appel de la fonction vider() qui désalloue la zone mémoire du tas
// (afin d'éviter les fuites de mémoires suite aux allocations dynamiques des gènes)
// et vide ensuite la map de son contenu (de ses pointeurs) réduidant ainsi sa taille à 0
	vider();
}

void ConteneurGenesMap::inserer(unsigned int id, const string &nom, const string &desc,
	const string &espece, const string &contenu) {
// Les gènes sont créés dynamiquement
	mapGenes_.insert(make_pair(espece, new Gene(id, nom, desc, espece, contenu)));
}

Gene* ConteneurGenesMap::trouver(unsigned int id) const {
// On utilise le mot-clé auto à la place de multimap<string, Gene*>::const_iterator
	for (auto it = mapGenes_.begin(); it != mapGenes_.end(); ++it)
		if ((it->second)->getId() == id) // Si le gène ayant id comme identificateur est trouvé
		return it->second; // On y retourne un pointeur
	// Si le gène n'est pas trouvé, on retourne un pointeur nul
			cout << "Le gène" << id << "n'a pas été trouvé" << endl;
			return nullptr; 
}

bool ConteneurGenesMap::retirer(unsigned int id) {
// On utilise le mot clé auto à la place de multimap<int, Gene*>::iterator
	for (auto it = mapGenes_.begin(); it != mapGenes_.end(); ++it)
		if ((it->second)->getId() == id) { // Si le gène est trouvé, on le détruit
		delete it->second;
		mapGenes_.erase(it);
		cout << "Le gène a été retiré" << endl;
		return true;
	}
	// Si le gène n'est pas dans la map
	cout << "Le gène " << id << " n'a pas été trouvé" << endl;
	return false;
}

unsigned int ConteneurGenesMap::retirerEspece(const string &espece) {
// Détermination du nombre de gènes présents dans la map avant le retrait de l'espèce
	unsigned int i = mapGenes_.size();
// Retrait de tous les gènes de l'espèce
	auto it = mapGenes_.begin();
	while (it != mapGenes_.end()) {
		if (it->first == espece) {
			delete it->second;
			mapGenes_.erase(it++);
		}
		else
			++it;
	}
// Retourner le nombre de gènes restants dans la map
	cout << "Nombre de genes retires = " << i - mapGenes_.size() << endl;
	return (i - mapGenes_.size());
}

void ConteneurGenesMap::vider() {
// On détruit d'abord les gènes en libérant les zones mémoires allouées dynamiquement
	for (auto it = mapGenes_.begin(); it != mapGenes_.end(); ++it)
		delete it->second;
// Ensuite on vide la map de son contenu (les pointeurs)
	mapGenes_.erase(mapGenes_.begin(), mapGenes_.end());
}

void ConteneurGenesMap::afficherParLongueur(ostream& out) const {
// Utilisation du prédicat binaire TriParLongueur comme critère de comparaison
// pour trier les gènes selon la longueur de leurs contenus
// Création d'abord d'une multimap temporaire sur laquelle il est possible d'appliquer le prédicat
	multimap<Gene*, Gene*, TriParLongueur> temp;
	for (auto it = mapGenes_.begin(); it != mapGenes_.end(); ++it)
		temp.insert(make_pair(it->second, it->second));
	for (auto it = temp.begin(); it != temp.end(); ++it)
		out << it->second << endl;
}

void ConteneurGenesMap::afficherParEspeceEtNom(ostream& out) const {
// Utilisation du prédicat binaire TriParEspeceEtNom comme critère de comparaison
// pour trier les gènes par ordre alphabétique d'espèce et pour chaque espèce
// par ordre alphabétique de nom
// Création d'abord d'une multimap temporaire sur laquelle il est possible d'appliquer le prédicat
	multimap<Gene*, Gene*, TriParEspeceEtNom> temp;
	for (auto it = mapGenes_.begin(); it != mapGenes_.end(); ++it)
		temp.insert(make_pair(it->second, it->second));
	for (auto it = temp.begin(); it != temp.end(); ++it)
		out << it->second << endl;
}

void ConteneurGenesMap::afficherEspece(const string &espece, ostream& out) const {
	for (auto it = mapGenes_.begin(); it != mapGenes_.end(); ++it) {
		if (it->first == espece) // L'espèce étant la clé de la multimap
		out << it->second; // On y affiche le gène correspondant
		}
}

unsigned int ConteneurGenesMap::modifierNoms(const string &espece, const map<string, string> &noms) {
	unsigned int nbrNomsModif = 0; // Pour compter le nombre de modifications
	auto itNoms = noms.begin();
	auto itMap = mapGenes_.begin();
	// On parcourt la map des noms
	for (itNoms; itNoms != noms.end(); ++itNoms) {
		// Tant qu'on a pas atteint la fin de la map et tant que l'espèce et le nom concernés n'ont pas été trouvés
		while (itMap != mapGenes_.end() && (itMap->first != espece || itNoms->first != itMap->second->getNom()))
			++itMap;
		// Pour chaque espèce concernée, on procède à la modification, en remplaçant le nom correspondant à
		// la clé de la map des noms par celui correspond à la valeur associée à cette clé
		if(itMap != mapGenes_.end()) {
			(itMap->second)->setNom(itNoms->second);
			// Après chaque opération, on incrémente le nombre de modifications
			++nbrNomsModif;
		}
	}
	cout << "Modification de " << nbrNomsModif << " nom(s) effectuée" << endl;
	return nbrNomsModif;
}