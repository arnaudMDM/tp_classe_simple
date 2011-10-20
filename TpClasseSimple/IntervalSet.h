/*************************************************************************
 IntervalSet  -  description
 -------------------
 début                : 7 oct. 2011
 copyright            : (C) 2011 par rgicquel
 *************************************************************************/

//---------- Interface de la classe <IntervalSet> (fichier IntervalSet.h) ------
#if ! defined ( INTERVALSET_H_ )
#define INTERVALSET_H_

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// Rôle de la classe <IntervalSet>
//
//
//------------------------------------------------------------------------ 

class IntervalSet
{
	//----------------------------------------------------------------- PUBLIC

public:
	//----------------------------------------------------- Méthodes publiques
	void Display ( );
	// Mode d'emploi :
	//	Affiche ligne par ligne chaque intervalle contenu dans l'objet sous la
	//forme "[x, y]" si l'ensemble contient au moins un intervalle.
	//Puis on affiche sur une dernière ligne le nombre d'intervalles
	//contenus dans l'ensemble sous la forme "Nombre d'intervalles : u", u étant
	//le nombre d'intervalles.
	//	L'objet appelant n'est pas modifié.
	//
	// Contrat :
	//	aucun

	bool Add ( long lLeft, long lRight );
	// Mode d'emploi :
	//	Le premier paramètre désigne la borne inférieure et le deuxième la borne
	//supérieure. La borne inférieure peut être égal à la borne supérieure.
	//Si l'intervalle saisi ne recoupe aucun des intervalles déjà
	//contenus dans l'objet, il est ajouté à l'objet de façon ordonné. La borne
	//inférieure de l'intervalle du paramètre est  supérieure aux bornes
	//inférieures des autres intervalles placés derrière, et viceversa.
	//Il est à noter qu'une borne d'un intervalle ne peut pas être la borne
	//d'un autre intervalle de l'objet. Renvoie vrai si l'ajout a pu se passer
	//ou faux dans le cas contraire.
	//
	// Contrat :
	//	aucun

	bool Add ( IntervalSet& is );
	// Mode d'emploi :Le paramètre est un autre ensemble d'intervalles.
	//La fonction ajoute tous les intervalles de is à l'ensemble de l'objet qui
	//appelle cette fonction si et seulemnt si tous les éléments peuvent être
	//ajoutés. Elle renvoie aussi vrai comme booléen si on peut tout ajouter.
	//Dans le cas contraire, renvoie faux.
	//
	// Contrat :
	//	aucun

	bool Remove ( long lPos );
	// Mode d'emploi : Efface un intervalle de l'ensemble en fonction du
	//paramètre lPos qui définit la position de l'intervalle par rapport aux
	//autres intervalles et renvoie vrai. Le tri est fait par rapport à la
	//valeur de la borne inférieure ou supérieure. Si la valeur de lPos ne
	//correspond pas à une position de l'intervalle, la fonction renvoie faux
	//et ne supprime rien.
	// Contrat :
	//	aucun

	long Count ( ) const;
	// Mode d'emploi :Renvoie le nombre d'intervalles contenus dans l'ensemble.
	//Renvoie 0 si il n'y en a pas.
	//
	// Contrat :
	//	aucun

	bool GetInterval ( long lPos, long& lLeft, long& lRight ) const;
	// Mode d'emploi :renvoie vrai si lPos correspond à une position d'un
	//intervalle et renvoie également la borne inféieure de cet intervalle dans
	//lLeft et renvoie la borne supérieure dans lRight. Si lPos ne correspond
	// à aucun intervalle, cela renvoie juste faux.
	//
	// Contrat :
	//	aucun

	IntervalSet& Union ( IntervalSet& is );
	// Mode d'emploi :Revoie un ensemble d'intervalle qui est le résultat de
	//l'union de l'ensemble de l'objet appelant cette méthode et de l'ensemble
	//de is. Il s'agit d'une union au sens mathématique.
	//
	// Contrat :
	//	aucun

	IntervalSet& Intersection ( IntervalSet& is );
	// Mode d'emploi :Revoie un ensemble d'intervalle qui est le résultat de
	//l'intersection de l'ensemble de l'objet appelant cette méthode et de
	//l'ensemble de is. Il s'agit d'une union au sens mathématique.
	//
	// Contrat :
	//	aucun

	//------------------------------------------------- Surcharge d'opérateurs

	//-------------------------------------------- Constructeurs - destructeur
	IntervalSet ( const IntervalSet& is );
	// Mode d'emploi (constructeur de copie) :
	//	Crée un objet ayant les mêmes caractéristiques que l'objet passé en
	//paramètre
	// Contrat :
	//	aucun

	IntervalSet ( );
	// Mode d'emploi :
	//	Crée un objet avec des valeurs par défaut, c'est à dire aucun intervalle
	// Contrat :
	//	aucun

	virtual ~IntervalSet ( );
	// Mode d'emploi :
	//	Destructeur classique
	// Contrat :
	//	aucun

	//------------------------------------------------------------------ PRIVE

protected:
	//----------------------------------------------------- Méthodes protégées

	//----------------------------------------------------- Attributs protégés
	long borneInf;
	long borneSup;
	long nbInter;
	IntervalSet *suivant;
};

//--------------------------- Autres définitions dépendantes de <IntervalSet>

#endif // INTERVALSET_H_
