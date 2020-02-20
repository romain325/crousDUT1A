/***********************crous.c*****************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "crous.h"

void global(void)
{
	/************INITIALISATION**************/
	int nbLog,nbEtu,nbDem,retour;
	char rep; 
	LISTE tLog;
	LISTE logDisp;
	ETUDIANT** tEtu;
	DEMANDE** tDem;
	tLog = fLireTabLogement(&nbLog);
	tEtu = fLireTabEtudiant(&nbEtu);
	tDem = fLireTabDemande(&nbDem);
	retour = affichLancement();

	/***************GESTION DES CHOIX********************/
	while(retour <= 10)
	{
		switch(retour)
		{
			case 1:		//affichage logements dispo triés par cité
				logDisp = logDispo(tLog,nbLog);
				afficherListeChainee(logDisp);
				printf("\n\n");
				break;
			case 2:		//liste log occupés + identité occupant
				logOccup(tLog,nbLog,tEtu,nbEtu);
				printf("\n\n");
				break;
			case 3:		//liste demande en attentes
				for (int i = 0; i < nbDem; ++i){fEcrireDemande(tDem[i]);}
				printf("\n\n");
				break;
			case 4:		//attribution des logements aux demandeurs
				attributionLogements(tDem,&nbDem,tEtu,nbEtu,tLog,nbLog);
				break;
			case 5:		//saisie d'une nouvelle demande + création etu
				printf("Etes vous déjà enregistré en tant qu'étudiant?? [o/n]\n");
				scanf("%*c%c%*c",&rep);
				if (rep=='o' || rep=='O')
				{
					tDem = nvlDemande(tEtu,&nbEtu,tDem,&nbDem);
				}
				else if (rep=='n' || rep=='N')
				{
					printf("Nous allons donc vous créer un compte étudiant afin de pouvoir procéder à la demande\n");
					tEtu = creatEtu(tEtu,&nbEtu);
					triFusionAttribEtu(tEtu,nbEtu);
				}
				else{
					printf("La réponse indiqué n'est pas reconnu // Retour au menu principal\n");
				}
				break;
			case 6:
				for (int i = 0; i < nbEtu; ++i)
				{
					fEcrireEtudiant(tEtu[i]);
				}
				break;
			case 7:
				nbDem = annulDem(tDem,nbDem);
				break;
			case 8:
				libLogement(tLog);
				attributionLogements(tDem,&nbDem,tEtu,nbEtu,tLog,nbLog);
				break;
			case 9:		//enregistrement des fichiers
				fEnregistrLogement(tLog);
				fEnregistrEtudiant(tEtu,nbEtu);
				fEnregistrDemande(tDem,nbDem);
				printf("Tout les enregistrement de données ont bien été effectué // Retour Menu\n");
				break;
		}
		retour = choix();
	}
	printf("\033[1;37mNous vous remercions d'avoir utiliser notre application\nAurevoir\033[0m\n");
	return;
}

/**********FONCTIONS D'AFFICHAGE DES DIFFERENTES OPTIONS*************/
int choix(void)
{
	int choix;
	printf("\033[1;32m**********************************Veuillez indiquer votre choix parmis ces actions********************************\033[0m\n");
	printf("\t\033[1;32m/1\\\033[0m Affichage des logement disponibles\n");
	printf("\t\033[1;32m/2\\\033[0m Affichage des logement occupés + occupant\n");
	printf("\t\033[1;32m/3\\\033[0m Affichage des demandes en attentes\n");
	printf("\t\033[1;32m/4\\\033[0m Attribution des demandes selon critères et disponibilités\n");
	printf("\t\033[1;32m/5\\\033[0m Création d'une demande de logement\n");
	printf("\t\033[1;32m/6\\\033[0m Affichage de la liste d'étudiants\n");
	printf("\t\033[1;32m/7\\\033[0m Suppression d'une demande\n");
	printf("\t\033[1;32m/8\\\033[0m Liberation d'un logement\n");
	printf("\t\033[1;32m/9\\\033[0m Sauvegarde des informations\n");
	printf("\t\033[1;32m/AUTRE\\\033[0m Sortie du programme\n");
	printf("\033[1;32mVotre choix:\033[0m");
	scanf("%d",&choix);
	printf("\n\033[1;32m******************************************************************************************************************\033[0m\n\n\n");
	return choix;
}

/************FONCTIONS D'AFFICHAGE AU LANCEMENT*************/
int affichLancement(void)
{
	printf(" \n\n\033[1;3m     ,o888888o.    8 888888888888   d888888o. 8888888 8888888888  8 8888     ,o888888o.     b.             8 \n    8888     `88.  8 8888         .`8888:- `88.     8 8888        8 8888  . 8888     `88.   888o.          8 \n ,8 8888       `8. 8 8888         8.`8888.   Y8     8 8888        8 8888 ,8 8888       `8b  Y88888o.       8 \n 88 8888           8 8888         `8.`8888.         8 8888        8 8888 88 8888        `8b .`Y888888o.    8 \n 88 8888           8 888888888888  `8.`8888.        8 8888        8 8888 88 8888         88 8o. `Y888888o. 8 \n 88 8888           8 8888           `8.`8888.       8 8888        8 8888 88 8888         88 8`Y8o. `Y88888o8 \n 88 8888   8888888 8 8888            `8.`8888.      8 8888        8 8888 88 8888        ,8P 8   `Y8o. `Y8888 \n `8 8888       .8- 8 8888        8b   `8.`8888.     8 8888        8 8888 `8 8888       ,8P  8      `Y8o. `Y8 \n    8888     ,88-  8 8888        `8b.   8.`8888     8 8888        8 8888  ` 8888     ,88-   8         `Y8o.` \n     `8888888P-    8 888888888888 `Y8888P ,88P-     8 8888        8 8888     `8888888P-     8            `Yo \n                                                                                                             \n              ,o888888o.    8 888888888o.      ,o888888o.     8 8888      88    d888888o.                    \n             8888     `88.  8 8888    `88.  . 8888     `88.   8 8888      88  .`8888:- `88.                  \n          ,8 8888       `8. 8 8888     `88 ,8 8888       `8b  8 8888      88  8.`8888.   Y8                  \n          88 8888           8 8888     ,88 88 8888        `8b 8 8888      88  `8.`8888.                      \n          88 8888           8 8888.   ,88- 88 8888         88 8 8888      88   `8.`8888.                     \n          88 8888           8 888888888P-  88 8888         88 8 8888      88    `8.`8888.                    \n          88 8888           8 8888`8b      88 8888        ,8P 8 8888      88     `8.`8888.                   \n          `8 8888       .8- 8 8888 `8b.    `8 8888       ,8P  ` 8888     ,8P 8b   `8.`8888.                  \n             8888     ,88-  8 8888   `8b.   ` 8888     ,88-     8888   ,d8P  `8b.  ;8.`8888                  \n              `8888888P-    8 8888     `88.    `8888888P-        `Y88888P-    `Y8888P ,88P-  				 \033[0m\n\n\n");
	return choix();
}


/*****************************AFFICHAGE LOG DISPO PAR CITE*********************************************/
//on a choisi d'utiliser une liste pour les logements, nous allons alors créer une autre liste contenant 
//tout les logements disponibles, nous utiliserons la fonction de liste "insererParNom" pour l'ordre
LISTE logDispo(LISTE l,int nb)
{
	LISTE logLib;
	logLib = nvListe();
	while(l != NULL)		//Valeur mises dans le nvx tablO
	{
		if(l->log.dispo==TRUE)
		{
			logLib = insererPNom(logLib,l->log);
		}
		l = l->suiv;
	}
	return logLib;
}

/*****************************AFFICHAGE DES LOG OCCUP AVEC ID ETU*********************************************/
//On va donc arpenté le fichier des logements et printf l'id LOG et l'id ETU si celui ci est occupé
//On ira donc recherché(rech dicho car tableau trié selon idEtu) l'id Etu dans la liste des etu pour avoir son nom et prenom
void logOccup(LISTE tLog, int nbL, ETUDIANT* tEtu[],int nbE)
{
	int pos;
	for (int i = 0; i < nbL; i++)									//pr chq valeur à l'intérieur du tab LOgement
	{
		if (tLog->log.dispo == FALSE)								//si le logement occupé alors
		{
			pos = rechDichoEtu(tEtu,nbE,tLog->log.idOccupant);		//on cherche le nom de l'etu dans tEtu à partir de son id
			printf("Le logement n°\033[1;33m %s \033[0m est occupé par %s %s ayant pour Id Etudiant:\033[1;35m %s \033[0m\n",tLog->log.idLogement,tEtu[pos]->nom,tEtu[pos]->prenom,tLog->log.idOccupant);
		}
		tLog = tLog->suiv;
	}	
}


/*****************************Affichage des demandes en Attente*********************************************/
void fAffichDemande(DEMANDE* tDem[],int nb)
{
	for (int i = 0; i < nb; ++i)
	{
		fEcrireDemande(tDem[i]);
	}
}


/*****************************ATTRIBUTION SELON LES CRITERES(echelon/handicap/etc)*********************************************/
//Les critères auront donc l'ordre de priorités suivants: echelon/souhaitLog/souhaitLieu
//la fonction triFusionAttrib tri de maniere decroissante par rapport à l'échelon
void attributionLogements(DEMANDE* tDem[],int *nbDem,ETUDIANT* tEtu[], int nbEtu,LISTE tLog, int nbLog)
{
	LISTE aux;
	int posEtu, pos;
	if (nbDem==0)
	{
		printf("Il n'y a aucune demande en attente.\n");
		return;
	}
	triFusionAttrib(tDem,*nbDem,1);
	for (int i = 0; i < *nbDem; ++i)
	{
		posEtu = rechDichoEtu(tEtu,nbEtu,tDem[i]->idEtudiant);
		pos = rechLog(*tDem[i],tLog,nbLog,*tEtu[posEtu]);
		if (pos == -1)
		{
			printf("\033[1;31mNous n'avons malheureusement pas pu trouver un logement pour l'étudiant %s selon les critères de la demandes %s\033[0m\n",tEtu[posEtu]->idEtudiant,tDem[i]->idDemande);
			printf("Nous vous conseillons de modifier votre recherche à partir du menu principal et nous traiterons votre nouvelle demande\n\n\n");
		}
		else
		{
			aux = tLog;
			for (int k = 0; k < pos; ++k)
			{
				aux = aux->suiv;
			}
			printf("Pour l'étudiant \033[1;35m %s \033[0m nous avons trouver le logement \033[1;34m %s \033[0m selon les critères de la demande \033[1;33m %s \033[0m\n",tEtu[posEtu]->idEtudiant,aux->log.idLogement,tDem[i]->idDemande);
			attribValid(tEtu[posEtu]->idEtudiant,tLog,pos);
			fEcrireLogement(aux->log);
			printf("\n\n");
			supprDemande(tDem,i,nbDem);
			i--;
		}
	}
	
}

void attribValid(char idEtu[], LISTE tLog, int pos)
{
	for (int i = 0; i < pos; ++i)
	{
		tLog = tLog->suiv;
	}
	strcpy(tLog->log.idOccupant,idEtu);
	tLog->log.dispo = FALSE;
}

void supprDemande(DEMANDE** tDem, int pos,int* n)
{
	if (*n == 1)
	{
		free(tDem[0]);
	}
	else{
		DEMANDE* suppr;
		suppr = tDem[pos];
		for (int i = pos; i < *n ; i++)
		{
			tDem[i]=tDem[i+1];
		}
		*n = *n-1;
		free(suppr);
	}
}


/************CREATION DUNE NOUVELLE DEMANDE ET/OU DUN NOUVELLE ETUDIANT SI INEXISTANT*************/
DEMANDE** nvlDemande(ETUDIANT** tEtu,int* nbEtu,DEMANDE** tDem,int* nbDem)
{
	int posEtu,exist;
	char citeSouhait[27],logSouhait[3],idEtu[9];

	printf("Veuillez s'il vous plait nous indiquer votre numéro d'étudiant: (EX: ETU00000)\n");
	scanf("%s%*c",idEtu);

	posEtu = rechDichoEtu(tEtu,*nbEtu,idEtu);
	if (posEtu == -1)
	{
		printf("Etudiant non existant // Retour au menu principal\n");
		return tDem;
	}

	exist = rechDichoDemEtu(tDem,*nbDem,idEtu);
	if (exist != -1)
	{
		printf("Vous avez déjà formuler une demande pour ce numéro d'étudiant // retour au menu\n");
		return tDem;
	}

	typeLogementLieu();		//affichage des options
	printf("\nVeuillez nous indiquer la cité souhaité:");
	fgets(citeSouhait,27,stdin);
	citeSouhait[strlen(citeSouhait)-1]='\0';

	printf("\nVeuillez nous indiquer le type de logement souhaité:");
	scanf("%s",logSouhait);

	tDem = ajoutDem(tDem,nbDem,idEtu,tEtu[posEtu]->echelon,citeSouhait,logSouhait);
	printf("Ajout du logement bien effectué // Retour au menu\n\n");
	return tDem;
}

int giveRandNum(void)		//donne un nombre de manière aléatoire
{
	int a;
	a=rand()%10;
	return a;
}


ETUDIANT** creatEtu(ETUDIANT** tEtu, int* nbEtu)
{
	ETUDIANT** aux;
	int retour,bours,echelon,handicap;
	char idEtu[9],nom[18],prenom[14],sexe,boursier,handi,b[2];
	*nbEtu = *nbEtu+1; 
	srand(time(NULL));			//generation d'un seed pour l'aléatoire utilisé par la suite

	do
	{
		strcpy(idEtu,"ETU");
		for (int i = 0; i < 5; ++i)
		{
			sprintf(b,"%d",giveRandNum());
 			strcat(idEtu,b);
		}
		printf("%s\n",idEtu );
		retour = rechDichoEtu(tEtu,*nbEtu-2,idEtu);
	}while(retour != -1);
	
	printf("Votre idEtudiant est \033[1;32m %s \033[0m\nPensez à le noter pour le garder!\n\n",idEtu );

	printf("Veuillez indiquer votre nom: ");
	fgets(nom,18,stdin);
	nom[strlen(nom)-1]='\0';
	for (int i = 0; i < strlen(nom); ++i)
	{
		if (nom[i]>='a' && nom[i]<='z')
		{
			nom[i] = nom[i]-32;						//on a appris en systeme que dans l'encodage courant, l'écart entre
		}											//les valeurs minuscules et majuscules est de 32
		
	}

	printf("Veuillez indiquer votre prenom: ");
	fgets(prenom,14,stdin);
	prenom[strlen(prenom)-1]='\0';
	if (prenom[0]>='a' && prenom[0]<='z')
	{
		prenom[0] = prenom[0]-32;	
	}

	do
	{
		printf("Veuillez indiquer votre sexe [H/F]: ");
		scanf("%c%*c",&sexe);
	}while(sexe !='h' && sexe != 'f' && sexe != 'H' && sexe!='F');
	if (sexe == 'h'){sexe = 'H';}
	if (sexe == 'f'){sexe = 'F';}

	do
	{
		printf("Etes vous boursier? [o/n]: ");
		scanf("%c",&boursier);
		if (boursier=='o' || boursier=='O')
		{
			bours=1;
			printf("Veuillez indiquer votre echelon: ");
			scanf("%d",&echelon);
		}
		else if (boursier=='n' || boursier=='N')
		{
			bours=0;
			echelon=-1;
		}
	}
	while(boursier !='o' && boursier!='O' && boursier!='n' && boursier!='N' && echelon >= -1 && echelon <= 7);

	do{
		printf("Avez vous un handicap / Necessitez-vous des accès spéciaux? [o/n]: ");
		scanf("%*c%c",&handi);
	}while(handi !='o' && handi != 'O' && handi != 'n' && handi!='N');
	if (handi == 'o' || handi == 'O')
		handicap = 1;
	else
		handicap = 0;

	aux = (ETUDIANT**)realloc(tEtu,*nbEtu*sizeof(ETUDIANT*));
	if (aux == NULL)
	{
		printf("\033[1;31mERREUR ALLOCATION ESPACE // retour au menu principal, nous vous prions de bien vouloir réessayer\033[0m\n");
		return tEtu;
	}
	tEtu = aux;

	ETUDIANT* nvEtu;
	nvEtu = (ETUDIANT*) malloc(sizeof(ETUDIANT));
	strcpy(nvEtu->idEtudiant,idEtu);
	strcpy(nvEtu->nom,nom);
	strcpy(nvEtu->prenom,prenom);
	nvEtu->sexe = sexe;
	nvEtu->boursier = bours;
	nvEtu->echelon = echelon;
	nvEtu->handicap = handicap;
	tEtu[*nbEtu-1] = nvEtu;
	printf("Voici le résumé de vos informations:\n");
	fEcrireEtudiant(tEtu[*nbEtu-1]);
	printf("\033[1;32mVotre profil étudiant a été créé avec succès, nous vous redirigeons maintenant au menu afin de pouvoir faire votre demande de logement\033[0m\n");
	return tEtu;
}

DEMANDE** ajoutDem(DEMANDE** tDem,int* nbDem,char idEtu[],int echelon,char citeSouhait[],char logSouhait[])
{
	int retour;
	char idDem[9],b[2];
	DEMANDE** aux;

	do
	{
		strcpy(idDem,"DEM");
		for (int i = 0; i < 5; ++i)
		{
			sprintf(b,"%d",giveRandNum());
 			strcat(idDem,b);
		}	
		printf("%s\n",idDem );
		retour = rechDichoDem(tDem,*nbDem,idDem);
	}while(retour != -1);

	*nbDem = *nbDem+1;
	aux = (DEMANDE**)realloc(tDem,*nbDem*sizeof(DEMANDE*));
	if (aux == NULL)
	{
		printf("\033[1;31mERREUR ALLOCATION ESPACE // retour au menu principal, nous vous prions de bien vouloir réessayer\033[0m\n");
		return tDem;
	}

	tDem = aux;
	DEMANDE* nvDem;
	nvDem = (DEMANDE*)malloc(sizeof(DEMANDE));
	if (nvDem == NULL)
	{
		printf("\033[1;31mERREUR ALLOCATION ESPACE // retour au menu principal, nous vous prions de bien vouloir réessayer\033[0m\n");
		return tDem;
	}
	nvDem->echelon = echelon;
	strcpy(nvDem->idDemande,idDem);		 
	strcpy(nvDem->idEtudiant,idEtu);
	strcpy(nvDem->citeSouhait,citeSouhait);
	strcpy(nvDem->typeLogementSouhait,logSouhait);
	tDem[*nbDem-1] = nvDem;
	printf("Voici un récapituatif de votre demande:\n");
	fEcrireDemande(tDem[*nbDem-1]);
	return tDem;
}

void typeLogementLieu(void)
{
	printf("VOICI AVANT TOUT LES TYPES DE LOGEMENTS DISPONIBLES SELON LES LIEUX:\n");
	printf("\tDollet:CH,ST,T1\n");
	printf("\tLa Gare:ST\n");
	printf("\tHauts de LaFayette:ST\n");
	printf("\tLes Laureats:ST,T1,T2\n");
	printf("\tAmboise:CH,ST,T1,T2\n");
	printf("\tCite 1:CH\n");
	printf("\tCite 2:CH\n");
	printf("\tPasteur:ST\n");
	printf("\033[1;3m/!\\VOTRE DEMANDE NE SERA PAS TRAITÉ SI VOUS RENSEIGNÉ DES COMBINAISONS INEXISTANTES\033[0m\n");
}


/**********************ANNULATION D'UNE DEMANDE***************************/
int annulDem(DEMANDE ** tDem,int n)
{	char num[9];
	int pos;
 	printf("Quelle demande doit faire l'objet d'une annulation?:  ");
 	scanf("%s", num);
 	pos=rechDichoDem(tDem,n,num);
 	if(pos==-1)
 	{	printf("\033[1;3mDemande non trouvée\033[0m\n");
 		return -1;
    }
   decalerGauche(tDem,n,pos);
   printf("\033[1;3mSuppression de votre demande bien effectué // Retour au menu\033[0m\n\n");
   return n-1;

}

void decalerGauche (DEMANDE **tDem, int n,int pos)
{	int i;
	for (i = pos; i < n; i++)
	{
	   tDem[i]=tDem[i+1];
	}
}

/*********************LIBERATION DU LOGEMENT*************************/
void libLogement(LISTE tLog)
{
	char idEtu[9],replace[2]={'0','\0'};
	printf("Veuillez nous indiquer votre numéro Étudiant: ");
	scanf("%s",idEtu);

	while(tLog != NULL)
	{
		if (strcmp(tLog->log.idOccupant,idEtu)==0)
		{
			tLog->log.dispo = 1;
			strcpy(tLog->log.idOccupant,replace);
			printf("\033[1;32mVotre logement a bien été libéré, nous vous remercions // Lancement attribution \033[0m\n\n");
			return;
		}
		tLog = tLog->suiv;
	}
	printf("\033[1;31mMalheureusement nous n'avons pu trouvé un logement relié à votre numéro d'étudiant // Lancement Attribution\033[0m\n\n");
	return;
}