/***********************************************************
* Fichier     : ConteneurGenesListe.cpp					   *
* Auteur      : Gergi Younis							   *
* Travail     : TP5										   *
* Description : Impl�mentation de la classe liste de g�nes *
************************************************************/
#include "ConteneurGenesListe.h"

ConteneurGenesListe::ConteneurGenesListe() : ConteneurGenes() {}

ConteneurGenesListe::~ConteneurGenesListe() {
// Appel de la fonction vider() qui d�salloue la zone m�moire du tas
// (afin d'�viter les fuites de m�moires suite aux allocations dynamiques des g�nes)
// et vide ensuite la liste de son contenu (de ses pointeurs) r�duidant ainsi sa taille � 0
	vider();
}

void ConteneurGenesListe::inserer(unsigned int id, const string &nom, const string &desc,
	const string &espece, const string &contenu) {
// Les g�nes sont cr��s dynamiquement
	listeGenes_.push_back(new Gene(id, nom, desc, espece, contenu));
}

Gene* ConteneurGenesListe::trouver(unsigned int id) const {
// Utilisation de l'algorithme find_if et du pr�dicat MemeId pour trouver un g�ne dans la liste
// On utilise le mot-cl� auto � la place de list<Gene*>::const_iterator
	auto it = find_if(listeGenes_.begin(), listeGenes_.end(), MemeId(id));
	if(it != listeGenes_.end()) // Si le g�ne ayant id comme identificateur est trouv�
	return *it; // On y retourne un pointeur
	// Si le g�ne n'est pas trouv�, on retourne un pointeur nul
		cout << "Le g�ne" << id << "n'a pas �t� trouv�" << endl;
		return nullptr; 
}

bool ConteneurGenesListe::retirer(unsigned int id) {
// Utilisation de l'algorithme find_if et du pr�dicat MemeId pour retirer un g�ne de la liste
// On utilise le mot cl� auto � la place de list<Gene*>::iterator
	auto it = find_if(listeGenes_.begin(), listeGenes_.end(), MemeId(id));
// Ensuite on d�truit le g�ne trouv�
	if (it != listeGenes_.end()) {
		delete *it;
		listeGenes_.erase(it);
		cout << "Le g�ne a �t� retir�" << endl;
		return true;
	}
	// Si le g�ne n'est pas dans la liste
	cout << "Le g�ne " << id << " n'a pas �t� trouv�" << endl;
	return false;
}

unsigned int ConteneurGenesListe::retirerEspece(const string &espece) {
// D�termination du nombre de g�nes pr�sents dans la liste avant le retrait de l'esp�ce
	unsigned int i = listeGenes_.size();
// Utilisation de l'algorithme remove_if et du foncteur DetruireEspece pour d�truire les g�nes de l'esp�ce
	listeGenes_.remove_if(DetruireEspece(espece));
// Retourner le nombre de g�nes restants dans la liste
	cout << "Nombre de g�nes retir�s = " << i - listeGenes_.size() << endl;
	return (i - listeGenes_.size());
}

void ConteneurGenesListe::vider() {
// Utilisation de l'algorithme for_each et du foncteur DetruireGenes pour d�truire tous les g�nes de la liste
// (en lib�rant les zones m�moires allou�es dynamiquement)
	for_each(listeGenes_.begin(), listeGenes_.end(), DetruireGenes());
// Ensuite on vide la liste de son contenu (les pointeurs)
	listeGenes_.clear();
}

void ConteneurGenesListe::afficherParLongueur(ostream& out) const {
// Utilisation de l'algorithme sort et du pr�dicat binaire TriParLongueur 
// pour trier les g�nes selon la longueur de leurs contenus
// On cr�e d'abord une liste temporaire pour les besoins d'affichage, dans laquelle on copie le contenu de la liste d'origine 
// � l'aide de l'algorithme copy. Cette liste temporaire est due � la constance de la m�thode qui consid�re l'op�ration
// du tri comme modifiant l'objet (en le d�pla�ant dans la liste)
	list<Gene*> temp(listeGenes_.size());
	copy(listeGenes_.begin(), listeGenes_.end(), temp.begin());
	temp.sort(TriParLongueur());
// Ensuite on affiche les g�nes
	copy(temp.begin(), temp.end(), ostream_iterator<Gene*>(out, "\n\n"));
}

void ConteneurGenesListe::afficherParEspeceEtNom(ostream& out) const {
// Utilisation de l'algorithme sort et du pr�dicat binaire TriParEspeceEtNom 
// pour trier les g�nes par ordre alphab�tique d'esp�ce et pour chaque esp�ce
// par ordre alphab�tique de nom
// On cr�e d'abord une liste temporaire pour les besoins d'affichage, dans laquelle on copie le contenu de la liste d'origine 
// � l'aide de l'algorithme copy. Cette liste temporaire est due � la constance de la m�thode qui consid�re l'op�ration
// du tri comme modifiant l'objet (en le d�pla�ant dans la liste)
	list<Gene*> temp(listeGenes_.size());
	copy(listeGenes_.begin(), listeGenes_.end(), temp.begin());
	temp.sort(TriParEspeceEtNom());
// Ensuite on affiche les g�nes
	copy(temp.begin(), temp.end(), ostream_iterator<Gene*>(out, "\n\n"));
}

void ConteneurGenesListe::afficherEspece(const string &espece, ostream& out) const {
// Utilisation de l'algorithme copy_if et du pr�dicat unaire MemeEspece 
// pour afficher les g�nes d'une esp�ce donn�e
	copy_if(listeGenes_.begin(), listeGenes_.end(), ostream_iterator<Gene*>(out), MemeEspece(espece));
}

unsigned int ConteneurGenesListe::modifierNoms(const string &espece, const map<string, string> &noms) {
// Utilisation de l'algorithme count_if et du pr�dicat unaire ModifierNom cr�� � cet effet
// On effectue les modifications n�cessaires de noms tout en renvoyant le nombre de modifications effectu�es
// Une autre alternative d'impl�mentation qui ne fait pas appel � ce foncteur se trouve ci-dessous
// (laiss�e en commentaire)
	unsigned int nbrNomsModif = count_if(listeGenes_.begin(), listeGenes_.end(), ModifierNom(espece, noms));
	cout << "Modification de " << nbrNomsModif << " nom(s) effectu�e" << endl;
	return nbrNomsModif;

// Impl�mentation ne faisant pas appel au foncteur ModifierNom
	//unsigned int nbrNomsModif = 0; // Pour compter le nombre de modifications
	//auto itNoms = noms.begin();
	//auto itListe = listeGenes_.begin();
	//// On parcourt la map des noms
	//for (itNoms; itNoms != noms.end(); ++itNoms) {

	//	while (itListe != listeGenes_.end() && ((*itListe)->getEspece() != espece || itNoms->first != (*itListe)->getNom()))
	//		++itListe;
	//	// Pour chaque esp�ce concern�e, on proc�de � la modification, en rempla�ant le nom correspondant �
	//	// la cl� de la map par celui correspond � la valeur associ�e � cette cl�
	//	if (itListe != listeGenes_.end()) {
	//		(*itListe)->setNom(itNoms->second);
	//		++nbrNomsModif;
	//	}
	//}
	//cout << "Modification de " << nbrNomsModif << " nom(s) effectu�e" << endl;
	//return nbrNomsModif;
}
