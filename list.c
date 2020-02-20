/***********************list.c*****************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crous.h"

/**********************************FICHIER CONSACRE AUX LISTES***************************************************/
LISTE nvListe(void){return NULL;}				//initialise notre nouvelle liste

LISTE insertionEnTete(LISTE l, LOGEMENT x)		//insert la val passé en arg en tête de la liste et retourne la nvl liste
{
	MAILLON *m;
	m = (MAILLON*)malloc(sizeof(MAILLON));
	if (m == NULL)
	{
		printf("Erreur Allocation Espace // Sortie du Programme\nVos données non enregistrés seront perdus\n");
		exit(-2);
	}
	m->log = x;
	m->suiv = l;
	return m;
}

int vide(LISTE l)								//Indique si la liste est vide ou non --> utile pour conditions
{
	if (l == NULL)
		return 1;
	return 0;
}

LOGEMENT tete(LISTE l)							//retourne la val de la tete de liste
{
	if (vide(l))
	{
		printf("Opération Interdite // Objet vide // Toute données non sauvés sera perdus\n");
		exit(-1);
	}
	return l->log;
}

void afficherListeChainee(LISTE l)				//affiche l'entierté de la liste
{
	while(!vide(l))
	{
		fEcrireLogement(l->log);
		l = l->suiv;
	}
}

LISTE suppressionEnTete(LISTE l)				//supprime la valeur en tete de la liste et retourne la nouvelle liste
{
	MAILLON *m;
	if (vide(l))
	{
		printf("Opération Interdite // Objet vide\n");
		return l;
	}
	m = l;
	l = l->suiv;
	free(m);			//Il est tres important d'utiliser le m sinon la valeur de l se retrouverai perdu donc prenant de lespace pr rien
	return l;
}

LISTE insererEnQueue(LISTE l, LOGEMENT log)		//insert une valeur en fin de liste
{
	if(vide(l))
		return insertionEnTete(l,log);
	l->suiv = insererEnQueue(l->suiv,log);
	return l;
}

LISTE suppression(LISTE l,char id[8])			//supprime une valeur de la liste qu'importe sa position
{
	if(vide(l))
		return l;
	if (strcmp(tete(l).idLogement,id) < 0)
		return l;
	if (strcmp(id,tete(l).idLogement)==0)
		return suppressionEnTete(l);
	l->suiv = suppression(l->suiv,id);
	return l;
}

LISTE inserer(LISTE l, LOGEMENT log)			//insere une valeur dans la liste qu'importe sa position trié selon le num
{
	if (vide(l))
		return insertionEnTete(l,log);
	if(strcmp(log.idLogement,l->log.idLogement)<0)
		return insertionEnTete(l,log);
	if (strcmp(log.idLogement,l->log.idLogement)==0)
		return l;
	l->suiv = inserer(l->suiv,log);
	return l;
}

LISTE insererPNom(LISTE l, LOGEMENT log)		//insere une valeur dans la liste qu'importe sa position trié selon le nom
{
	if (vide(l))
		return insertionEnTete(l,log);
	if(strcmp(log.nomCite,l->log.nomCite)<0)
		return insertionEnTete(l,log);
	if (strcmp(log.nomCite,l->log.nomCite)==0)
		return l;
	l->suiv = inserer(l->suiv,log);
	return l;
}

int longueurListe(LISTE l)						//retourne la taille de la liste
{
	int cpt=0;
	while(!vide(l))
	{
		cpt++;
		l = l->suiv;
	}
	return cpt;
}

