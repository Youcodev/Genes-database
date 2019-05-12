/***********************************************************
* Fichier     : ConteneurGenesListe.cpp					   *
* Auteur      : Gergi Younis							   *
* Travail     : TP5										   *
* Description : Implémentation de la classe liste de gènes *
************************************************************/
#include "ConteneurGenesListe.h"

ConteneurGenesListe::ConteneurGenesListe() : ConteneurGenes() {}

ConteneurGenesListe::~ConteneurGenesListe() {
// Appel de la fonction vider() qui désalloue la zone mémoire du tas
// (afin d'éviter les fuites de mémoires suite aux allocations dynamiques des gènes)
// et vide ensuite la liste de son contenu (de ses pointeurs) réduidant ainsi sa taille à 0
	vider();
}

void ConteneurGenesListe::inserer(unsigned int id, const string &nom, const string &desc,
	const string &espece, const string &contenu) {
// Les gènes sont créés dynamiquement
	listeGenes_.push_back(new Gene(id, nom, desc, espece, contenu));
}

Gene* ConteneurGenesListe::trouver(unsigned int id) const {
// Utilisation de l'algorithme find_if et du prédicat MemeId pour trouver un gène dans la liste
// On utilise le mot-clé auto à la place de list<Gene*>::const_iterator
	auto it = find_if(listeGenes_.begin(), listeGenes_.end(), MemeId(id));
	if(it != listeGenes_.end()) // Si le gène ayant id comme identificateur est trouvé
	return *it; // On y retourne un pointeur
	// Si le gène n'est pas trouvé, on retourne un pointeur nul
		cout << "Le gène" << id << "n'a pas été trouvé" << endl;
		return nullptr; 
}

bool ConteneurGenesListe::retirer(unsigned int id) {
// Utilisation de l'algorithme find_if et du prédicat MemeId pour retirer un gène de la liste
// On utilise le mot clé auto à la place de list<Gene*>::iterator
	auto it = find_if(listeGenes_.begin(), listeGenes_.end(), MemeId(id));
// Ensuite on détruit le gène trouvé
	if (it != listeGenes_.end()) {
		delete *it;
		listeGenes_.erase(it);
		cout << "Le gène a été retiré" << endl;
		return true;
	}
	// Si le gène n'est pas dans la liste
	cout << "Le gène " << id << " n'a pas été trouvé" << endl;
	return false;
}

unsigned int ConteneurGenesListe::retirerEspece(const string &espece) {
// Détermination du nombre de gènes présents dans la liste avant le retrait de l'espèce
	unsigned int i = listeGenes_.size();
// Utilisation de l'algorithme remove_if et du foncteur DetruireEspece pour détruire les gènes de l'espèce
	listeGenes_.remove_if(DetruireEspece(espece));
// Retourner le nombre de gènes restants dans la liste
	cout << "Nombre de gènes retirés = " << i - listeGenes_.size() << endl;
	return (i - listeGenes_.size());
}

void ConteneurGenesListe::vider() {
// Utilisation de l'algorithme for_each et du foncteur DetruireGenes pour détruire tous les gènes de la liste
// (en libérant les zones mémoires allouées dynamiquement)
	for_each(listeGenes_.begin(), listeGenes_.end(), DetruireGenes());
// Ensuite on vide la liste de son contenu (les pointeurs)
	listeGenes_.clear();
}

void ConteneurGenesListe::afficherParLongueur(ostream& out) const {
// Utilisation de l'algorithme sort et du prédicat binaire TriParLongueur 
// pour trier les gènes selon la longueur de leurs contenus
// On crée d'abord une liste temporaire pour les besoins d'affichage, dans laquelle on copie le contenu de la liste d'origine 
// à l'aide de l'algorithme copy. Cette liste temporaire est due à la constance de la méthode qui considère l'opération
// du tri comme modifiant l'objet (en le déplaçant dans la liste)
	list<Gene*> temp(listeGenes_.size());
	copy(listeGenes_.begin(), listeGenes_.end(), temp.begin());
	temp.sort(TriParLongueur());
// Ensuite on affiche les gènes
	copy(temp.begin(), temp.end(), ostream_iterator<Gene*>(out, "\n\n"));
}

void ConteneurGenesListe::afficherParEspeceEtNom(ostream& out) const {
// Utilisation de l'algorithme sort et du prédicat binaire TriParEspeceEtNom 
// pour trier les gènes par ordre alphabétique d'espèce et pour chaque espèce
// par ordre alphabétique de nom
// On crée d'abord une liste temporaire pour les besoins d'affichage, dans laquelle on copie le contenu de la liste d'origine 
// à l'aide de l'algorithme copy. Cette liste temporaire est due à la constance de la méthode qui considère l'opération
// du tri comme modifiant l'objet (en le déplaçant dans la liste)
	list<Gene*> temp(listeGenes_.size());
	copy(listeGenes_.begin(), listeGenes_.end(), temp.begin());
	temp.sort(TriParEspeceEtNom());
// Ensuite on affiche les gènes
	copy(temp.begin(), temp.end(), ostream_iterator<Gene*>(out, "\n\n"));
}

void ConteneurGenesListe::afficherEspece(const string &espece, ostream& out) const {
// Utilisation de l'algorithme copy_if et du prédicat unaire MemeEspece 
// pour afficher les gènes d'une espèce donnée
	copy_if(listeGenes_.begin(), listeGenes_.end(), ostream_iterator<Gene*>(out), MemeEspece(espece));
}

unsigned int ConteneurGenesListe::modifierNoms(const string &espece, const map<string, string> &noms) {
// Utilisation de l'algorithme count_if et du prédicat unaire ModifierNom créé à cet effet
// On effectue les modifications nécessaires de noms tout en renvoyant le nombre de modifications effectuées
// Une autre alternative d'implémentation qui ne fait pas appel à ce foncteur se trouve ci-dessous
// (laissée en commentaire)
	unsigned int nbrNomsModif = count_if(listeGenes_.begin(), listeGenes_.end(), ModifierNom(espece, noms));
	cout << "Modification de " << nbrNomsModif << " nom(s) effectuée" << endl;
	return nbrNomsModif;

// Implémentation ne faisant pas appel au foncteur ModifierNom
	//unsigned int nbrNomsModif = 0; // Pour compter le nombre de modifications
	//auto itNoms = noms.begin();
	//auto itListe = listeGenes_.begin();
	//// On parcourt la map des noms
	//for (itNoms; itNoms != noms.end(); ++itNoms) {

	//	while (itListe != listeGenes_.end() && ((*itListe)->getEspece() != espece || itNoms->first != (*itListe)->getNom()))
	//		++itListe;
	//	// Pour chaque espèce concernée, on procède à la modification, en remplaçant le nom correspondant à
	//	// la clé de la map par celui correspond à la valeur associée à cette clé
	//	if (itListe != listeGenes_.end()) {
	//		(*itListe)->setNom(itNoms->second);
	//		++nbrNomsModif;
	//	}
	//}
	//cout << "Modification de " << nbrNomsModif << " nom(s) effectuée" << endl;
	//return nbrNomsModif;
}
