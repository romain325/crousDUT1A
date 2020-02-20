/***********************lectOuv.c*****************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crous.h"

/******************************OUVERTURE ET MISE EN MEMOIRE LOGEMENT*********************************************/
//ON UTILISE UNE LISTE CHAINÉE DE STRUCTURES LOGEMENT ET D'UN POINTEUR "SUIV"
LOGEMENT fLireLogement(FILE* flot)
{
	LOGEMENT log;
	fscanf(flot,"%s%*c %s%*c %s %d %d%*c",log.idLogement,log.typeLogement,log.idOccupant,&log.dispo,&log.adaptHandicap);
	fgets(log.nomCite,23,flot);
	log.nomCite[strlen(log.nomCite)-1]='\0';
	return log;
}

void fEcrireLogement(LOGEMENT log)
{
	printf("\033[1;34m %s \033[0m\n\t%s\n\t%s\n\t%s\n\t%d\n\t%d\n\n",log.idLogement,log.nomCite,log.typeLogement,log.idOccupant,log.dispo,log.adaptHandicap);
}

LISTE fLireTabLogement(int* nb)		//On passe en arg un pointeur avec le nb d'elements de la liste
{
	LISTE tLog;
	LOGEMENT aux;
	FILE* flot;
	flot = fopen("data/logements.don","r");
	if (flot == NULL)
	{
		printf("Erreur ouverture fichier // Sortie du Programme\nVos données non enregistrés seront perdus\n");
		exit(-1);
	}
	tLog = nvListe();
	aux = fLireLogement(flot);
	tLog = insertionEnTete(tLog,aux);
	while(!feof(flot))
	{
		aux = fLireLogement(flot);
		tLog = insererEnQueue(tLog,aux);
	}
	*nb = longueurListe(tLog);
	fclose(flot);
	return tLog;
}

void fEnregistrLogement(LISTE tLog)
{
	FILE* flot;
	flot = fopen("data/logements.don","w");
	if (flot == NULL)
	{
		printf("ERREUR lors de l'enregistrement des données // annulation // retour au menu\n");
		return;
	}
	while(tLog != NULL)
	{
		fprintf(flot, "%s\n%s\n%s\n%d\n%d\n%s\n\n", tLog->log.idLogement,tLog->log.typeLogement,tLog->log.idOccupant,tLog->log.dispo,tLog->log.adaptHandicap, tLog->log.nomCite);
		tLog = tLog->suiv;
	}
	fclose(flot);
}


/*****************************OUVERTURE ET MISE EN MEMOIRE ETUDIANT*********************************************/
//ON UTILISE UN TABLEAU DE POINTEURS SUR LA STRUCTURE ETUDIANT
ETUDIANT* fLireEtudiant(FILE* flot)
{
	ETUDIANT* etu;
	etu = (ETUDIANT*)malloc(sizeof(ETUDIANT));
	fscanf(flot,"%s %d %d%*c %c %d %s%*c",etu->idEtudiant,&etu->boursier,&etu->echelon,&etu->sexe, &etu->handicap,etu->prenom);
	fgets(etu->nom,15,flot);
	etu->nom[strlen(etu->nom)-1]='\0';
	return etu;
}

void fEcrireEtudiant(ETUDIANT* etu)
{
	printf("\033[1;35m %s \033[0m\n\t%c\n\t%s\n\t%s\n\t%d\n\t%d\n\t%d\n\n",etu->idEtudiant,etu->sexe,etu->nom,etu->prenom,etu->boursier,etu->echelon,etu->handicap);
}

ETUDIANT** fLireTabEtudiant(int* nb)		//On passe en arg un pointeur avec le nb d'elements du tab
{
	ETUDIANT** tEtu;
	FILE* flot;
	flot = fopen("data/etudiants.don","r");
	if (flot == NULL)
	{
		printf("Erreur ouverture fichier // Sortie du Programme\nVos données non enregistrés seront perdus");
		exit(-1);
	}
	fscanf(flot,"%d",nb);
	tEtu = (ETUDIANT**) malloc(*nb*sizeof(ETUDIANT*));
	if (tEtu == NULL)
	{
		printf("Erreur Allocation Espace // Sortie du Programme\nVos données non enregistrés seront perdus");
		exit(-2);
	}
	for (int i = 0; i < *nb; i++)
	{
		tEtu[i] = fLireEtudiant(flot);
	}
	fclose(flot);
	return tEtu;
}

void fEnregistrEtudiant(ETUDIANT** tEtu, int nbEtu)
{
	FILE* flot;
	flot = fopen("data/etudiants.don","w");
	if (flot == NULL)
	{
		printf("ERREUR lors de l'enregistrement des données // annulation // retour au menu\n");
		return;
	}
	fprintf(flot, "%d\n\n",nbEtu );
	for (int i = 0; i < nbEtu; ++i)
	{
		fprintf(flot, "%s\n%d\n%d\n%c\n%d\n%s\n%s\n\n", tEtu[i]->idEtudiant,tEtu[i]->boursier,tEtu[i]->echelon,tEtu[i]->sexe,tEtu[i]->handicap,tEtu[i]->prenom,tEtu[i]->nom);
	}
	fclose(flot);
}

/*****************************OUVERTURE ET MISE EN MEMOIRE DEMANDE*********************************************/
//ON UTILISE UN TABLEAU DE POINTEUR DE LA STRUCTURE DEMANDE
DEMANDE* fLireDemande(FILE* flot)
{
	DEMANDE* dem;
	dem = (DEMANDE*)malloc(sizeof(DEMANDE));
	fscanf(flot,"%s %s %d%*c %s%*c",dem->idDemande,dem->idEtudiant,&dem->echelon,dem->typeLogementSouhait);
	fgets(dem->citeSouhait,23,flot);
	dem->citeSouhait[strlen(dem->citeSouhait)-1]='\0';
	return dem;
}

void fEcrireDemande(DEMANDE* dem)
{
	printf("\033[1;33m %s \033[0m\n\t%s\n\t%d\n\t%s\n\t%s\n\n",dem->idDemande,dem->idEtudiant,dem->echelon,dem->citeSouhait,dem->typeLogementSouhait);
}

DEMANDE** fLireTabDemande(int* nb)		//On passe en arg un pointeur avec le nb d'elements du tab
{
	DEMANDE** tDem;
	FILE* flot;
	flot = fopen("data/demandeEnAttente.don","r");
	if (flot == NULL)
	{
		printf("Erreur ouverture fichier // Sortie du Programme\nVos données non enregistrés seront perdus");
		exit(-1);
	}
	fscanf(flot,"%d",nb);
	tDem = (DEMANDE**) malloc(*nb*sizeof(DEMANDE*));
	if (tDem == NULL)
	{
		printf("Erreur Allocation Espace // Sortie du Programme\nVos données non enregistrés seront perdus");
		exit(-2);
	}
	for (int i = 0; i < *nb; i++)
	{
		tDem[i] = fLireDemande(flot);
	}
	fclose(flot);
	return tDem;
}

void fEnregistrDemande(DEMANDE** tDem, int nbDem)
{
	FILE* flot;
	flot = fopen("data/demandeEnAttente.don","w");
	if (flot == NULL)
	{
		printf("ERREUR lors de l'enregistrement des données // annulation // retour au menu\n");
		return;
	}
	fprintf(flot, "%d\n\n",nbDem );
	for (int i = 0; i < nbDem; ++i)
	{
		fprintf(flot,"%s\n%s\n%d\n%s\n%s\n\n",tDem[i]->idDemande,tDem[i]->idEtudiant,tDem[i]->echelon,tDem[i]->typeLogementSouhait,tDem[i]->citeSouhait);
	}
	fclose(flot);
}


