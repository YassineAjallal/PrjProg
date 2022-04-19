/*----------------------- Visualiser Contrat -----------------------------------*/

void visualiserContrat(FILE *file) {
	contrat contrat ;
	int trouve=0;
	float num;
	printf("--Donnez le num du contrat : ");
	scanf("%f",&num);
	fseek(file, 0, SEEK_SET);

	while (fread(&contrat, sizeof(contrat), 1, file) != 0 && trouve==0) {

	    if (contrat.numContrat == num) {
			trouve = 1 ; break ;
		}

	}
	if (trouve == 0){
		 printf(" \n\t--contrat introuvable-- \n\n");
	}

	else {
		 fseek(file,-(sizeof (contrat)),SEEK_CUR) ;
		 printf("Les entrees anciennes : \n");
		 printf("numero du contrat ........ ........: %.2f\n",contrat.numContrat);
		 printf("id voiture .............: %d\n",contrat.idVoiture  );
		 printf("id client ................: %d\n",contrat.idClient  );
		 printf("date debu du contrat : .....: %d %d %d\n",contrat.debut.dd , contrat.debut.mm , contrat.debut.yy  );
		 printf("date fin du contrat : .....: %d %d %d\n",contrat.fin.dd , contrat.fin.mm , contrat.fin.yy  );
		 printf("cout : .....: %d\n",contrat.cout  );
	}

 	fseek(file, 0, SEEK_SET);
 	fclose(file);
	main();
}

/*----------------------- louer une voiture-------------------------*/

void louerVoiture(FILE *Vtr , FILE *Clt , FILE *Cont,FILE *tempL){

	client client ;
	voiture test ;
	voiture voiture ;
	contrat contrat ;
	int trouve = 0;
	int trouve2=0 ;
	int id;

  printf("votre id personnel du programme s'il vous plait  : ");
  scanf("%d",&id);
  fseek(Clt, 0, SEEK_SET);

	while (fread(&client, sizeof(client), 1, Clt) != 0 && trouve==0) {
	    if ( client.idClient == id )
	    {
	    	/* insertion des specifications de la voiture */

	      	printf("Entrez les specifications de la voiture voulu : \n");
	      	printf ("marque  : ");
			scanf ("%s", &test.marque);
			printf ("nom voiture : ");
			scanf ("%s", &test.nomVoiture);
			printf("couleur : ");
			scanf("%s",&test.couleur);
			printf("nombre des places :");
			scanf("%d",&test.nbplaces);

	        while (fread(&voiture, sizeof(voiture), 1, Vtr) != 0 && trouve2==0)
			{
				/* comparaison des specifications inserer avec des voitures disponibles*/
	            if(strcmp(voiture.marque,test.marque)==0  &&  strcmp(voiture.nomVoiture,test.nomVoiture)==0  &&  strcmp(voiture.couleur,test.couleur)==0   &&    voiture.nbplaces==test.nbplaces    )
	            {
								/* changement de la valeur de ---enlocation-- et insersion des info de contrat */
	                              if(strcmp(voiture.EnLocation, "Non") == 0 || strcmp(voiture.EnLocation, "non") == 0 || strcmp(voiture.EnLocation, "NON") == 0){
									strcpy(voiture.EnLocation , "Oui");
	                                printf("-----felicitations tu as de la chance , cette voiture est disponible----- \n");
	                                printf("choisir le numero de votre contrat : ");
	                                scanf("%f",&contrat.numContrat);
	                                contrat.idVoiture = voiture.idVoiture ;
	                                contrat.idClient = id ;
	                                printf("tu vas prendre la voiture quand ? : ");
	                                scanf("%d %d %d" , &contrat.debut.dd,&contrat.debut.mm,&contrat.debut.yy);
	                                printf("jusqu'a : ");
	                                scanf("%d %d %d" , &contrat.fin.dd, &contrat.fin.mm , &contrat.fin.yy);
	                                contrat.cout = ( contrat.fin.dd - contrat.debut.dd ) * voiture.prixJour ;
	                                fseek(Cont, 0, SEEK_END);
	                                fwrite (&contrat, sizeof(contrat), 1, Cont);
	                                trouve2 = 1 ;
	                                system("cls");
	                              }else
								  {
	                              	printf("\n    -----cette voiture est en location! chercher une autre voiture-----\n\n\n");
	                              	trouve2 = 1 ;
								  }
	            }
	            /* sauvegarder les modifications de les voitures dans un fichier temporaire */
	            fwrite(&voiture,sizeof(voiture),1,tempL);
	        }

			if(trouve2==0) {
			printf("\n\t cette voiture n'est pas valable ! \n\n\n");
			main();
			}
	        trouve =1;
		}
	}
	if (trouve == 0) {
	printf("\n   Ce nom n'existe pas! veuillez enregister vos info dans --gestion de clients--\n\n\n");
	}
	fseek(Clt, 0, SEEK_SET);
	fseek(Cont, 0, SEEK_SET);
	fclose(Clt);
	fclose(Cont);
	fclose(Vtr);
    remove("Voiture.txt");
    fclose(tempL);
    rename("renommerL.txt","Voiture.txt");
	//system("cls");
	main();
}

/*----------------------------- supprimer contrat ----------------------------------------------*/

void supprimerContrat(FILE *Vtr ,FILE *Cont,FILE *tempCT){
	contrat contrat ;
	voiture voiture ;
	float num;
	int trouve2=0;
	int trouve = 0;
	int CTidV = 0;
	char test;

	printf("donner le num de contrat : ");
	scanf("%f",&num);


	fseek(Cont , 0, SEEK_SET);

	/* verification de num de contrat */
	while (fread(&contrat, sizeof(contrat), 1, Cont) != 0 && trouve==0) {
		if(contrat.numContrat == num )
		{
					trouve = 1;
					CTidV = contrat.idVoiture;
					break;
		}
	}
	if (trouve == 0) {
		system("cls");
		printf("\n\t\t --cette Contrat n'est pas valable--\n\n");
		main();
	}

	else {
		fseek(Vtr, 0, SEEK_SET);
		while (fread(&voiture, sizeof(voiture), 1, Vtr) != 0 && trouve2==0)
			{
				/* verification si la voiture est louee ou non*/
				if(voiture.idVoiture == CTidV && strcmp(voiture.EnLocation, "Non" ) == 0){
						fseek(Cont, 0, SEEK_SET);
						while(fread(&contrat, sizeof(contrat), 1, Cont))
						{
						//	fread(&contrat,sizeof(contrat),1,Cont);
							if(contrat.numContrat==num)
							{
								continue;
							}
							else
							{
							/* sauvegarder les modification dans un fichier temporaire*/
							fwrite(&contrat,sizeof(contrat),1,tempCT);
							}
						}
						trouve2 = 1;
					}else
					{
						printf("\n  --tu ne peut pas supprimer une contrat avant retourner une voiture--\n\n\n");
					}
				}
			}

	if(trouve2 != 0){
		fclose(Cont);
		remove("Contrat.txt");
		fclose(tempCT);
		rename("renommerCT.txt" , "Contrat.txt");
	}

	fclose(Vtr);
	main();

}

/*--------------------------------- Modifier Contrat -------------------------------------------*/
void modifierContrat(FILE *file ){

	contrat contrat ;
	int trouve = 0;
	int num;
	char test;

	printf("Donnez le num : ");
	scanf("%d",&num);

	fseek(file, 0, SEEK_SET);

	/* verification de num de contrat */
	while (fread(&contrat, sizeof(contrat), 1, file) != 0 && trouve==0) {
	if (contrat.numContrat == num) {
		trouve = 1 ;
		break ;
	 }
	}

	if (trouve == 0)  printf("Cette contrat n'existe pas\n");

    else{
	    fseek(file,-(sizeof contrat),SEEK_CUR) ;
		printf("Les entrees anciennes : \n");
	    printf("date debut ........ ........: %d %d %d\n",contrat.debut.dd , contrat.debut.mm , contrat.debut.yy  );
	    printf("date fin .............: %d %d %d\n",contrat.fin.dd , contrat.fin.mm , contrat.fin.yy  );

	    printf("\n\n qu'est ce que tu veux changer ? \n ============================= \n ");

	    contrat.numContrat = num ;

	    /* modifier la date de debut */

	    printf("debut ? : (o/n) \t ") ;
		scanf("%s",&test) ;
		if(test == 'o')
			scanf("%d %d %d",&contrat.debut.dd,&contrat.debut.mm,&contrat.debut.yy) ;
		else
			contrat.debut = contrat.debut  ;
		printf("\n");

		/* modifier la date de fin */

	    printf("fin ? : (o/n) \t ") ;
		scanf("%s",&test) ;
		if(test == 'o')
			scanf("%d %d %d",&contrat.fin.dd,&contrat.fin.mm,&contrat.fin.yy) ;
		else
			contrat.fin = contrat.fin ;
		printf("\n");

		contrat.cout = contrat.cout ;

		contrat.idClient = contrat.idClient ;

		contrat.idVoiture = contrat.idVoiture ;

		/* sauvegarder les modification */
		fwrite(&contrat,sizeof contrat,1,file);
		system("cls");
    }

    fseek(file, 0, SEEK_SET);
    fclose(file);
	main();


}

/*--------------------------------- retourner une voiture ---------------------------------------*/

 void retournerV(FILE *Cont ,FILE *Vtr,FILE *tempR){

	voiture voiture ;
	contrat contrat ;
	int trouve=0;
	float num;

    printf("donner le num de contrat : ");
	scanf("%f",&num);

	fseek(Cont , 0, SEEK_SET);

	/* verification de num de contrat */
	while (fread(&contrat, sizeof(contrat), 1, Cont) != 0 && trouve==0) {
		if(contrat.numContrat == num )
		{
					trouve = 1;
					break;
		}
	}

	if(trouve == 0){
		printf("cette Contrat n'est pas valable\n");
	}
	else{
		fseek(Cont , 0, SEEK_SET);
		while (fread(&contrat, sizeof(contrat), 1, Cont) != 0) {
			if(contrat.numContrat == num ){
					fseek(Vtr , 0, SEEK_SET);
					while (fread(&voiture, sizeof(voiture), 1, Vtr) != 0) {

						/* changement de la valeur de --enlocation-- */
						if(contrat.idVoiture == voiture.idVoiture){
							strcpy(voiture.EnLocation , "Non");
						}
						/* sauvegarde des modifications dans un fichier temporaire */
						fwrite(&voiture,sizeof(voiture),1,tempR);
					}
					fclose(Vtr);
					remove("Voiture.txt");
					fclose(tempR);
					rename("renommerR.txt","Voiture.txt");
					printf("\n \t--veuillez supprimer votre contrat-- \n\n");
				}
			}
		}
	fseek(Cont, 0, SEEK_SET);
	fclose(Cont);
	//system("cls");
	main();
}
