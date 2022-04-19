/* -------------------------Liste des voitures --------------------------------*/
void ListeVoitures(FILE *file) {
    system("cls");
    voiture voiture;
    fseek(file,0,SEEK_SET);
   while(fread(&voiture,sizeof(voiture),1,file) != 0){
     printf("identificateur du voiture ......: %d \n",voiture.idVoiture);
     printf("     La marque : ...............: %s \n",voiture.marque);
     printf("      nom du voiture : .........: %s \n",voiture.nomVoiture);
     printf("             Couleur : .........: %s \n",voiture.couleur);
     printf("nombre des places : ............: %d \n",voiture.nbplaces);
     printf("           Prix par Jour : .....: %d \n",voiture.prixJour);
     printf("             En Location : .....: %s\n",voiture.EnLocation);
     printf("\n ================================ \n");
   }
    fseek(file, 0, SEEK_SET);
	fclose(file);
    main();

}
/*------------------------ajouter  voiture ---------------------------*/

void Ajouter (FILE *file) {
      voiture voiture;
      printf("id : ");
      scanf("%d",&voiture.idVoiture);
      printf ("marque  : ");
      scanf ("%s", &voiture.marque);
      printf ("nom voiture : ");
      scanf ("%s", &voiture.nomVoiture);
      printf("couleur :");
      scanf("%s",&voiture.couleur);
      printf("nombre des places :");
      scanf("%d",&voiture.nbplaces);
      printf("Prix/Jour :");
      scanf("%d",&voiture.prixJour);
      printf("en location ? ");
      scanf("%s",&voiture.EnLocation);
      fseek(file, 0, SEEK_END);
      fwrite(&voiture, sizeof(voiture),1,file);
      fseek(file, 0, SEEK_SET);
      fclose(file);
      system("cls");
      main();
}
/* -----------------------------------------Modifier Voiture -----------------------------------------*/
void Modifier(FILE *file){

    voiture voiture ;
    int trouve = 0;
    int id;
    char test;
    printf("Donnez le id : ");
    scanf("%d",&id);
    fseek(file, 0, SEEK_SET);
     /* verification de id*/
    while (fread(&voiture, sizeof(voiture), 1, file) != 0 && trouve==0) {
        if (voiture.idVoiture == id) {
            trouve = 1 ;
            break ;
        }
    }

    if(trouve == 0){
          printf("Cette voiture  n'existe pas\n");
    }else{

             fseek(file,-(sizeof(voiture)),SEEK_CUR) ;
             printf("Les entrees anciennes : \n");
             printf("marque du voiture........ ........: %s\n",voiture.marque  );
             printf("nom du voiture .............: %s\n",voiture.nomVoiture  );
             printf("couleur du voiture ................: %s\n",voiture.couleur  );
             printf("nbplaces : .....: %d\n",voiture.nbplaces  );
             printf("prix/jour : .....: %d\n",voiture.prixJour  );
             printf("\n\n qu'est ce que tu veux changer ? \n ============================= \n ");

             voiture.idVoiture = id;
             /* modifier la marque */
             printf("marque ? : (o/n) \t ") ;
             scanf("%s",&test) ;
             if(test == 'o'){
                printf("nouv marque : ");
                scanf("%s",&voiture.marque);
             }else strcpy(voiture.marque , voiture.marque);
             printf("\n");

             /* modifier le nom */
             printf("nom ? : (o/n) \t ") ;
             scanf("%s",&test) ;
             if(test == 'o'){
                printf("nouv nom : ");
                scanf("%s",&voiture.nomVoiture) ;
             }else strcpy(voiture.nomVoiture,voiture.nomVoiture);
             printf("\n");

             /* modifier la couleur */
             printf("couleur ? : (o/n) \t ") ;
             scanf("%s",&test) ;
             if(test == 'o'){
                printf("nouv couleur : ");
                scanf("%s",&voiture.couleur) ;
             }else strcpy(voiture.couleur,voiture.couleur) ;
             printf("\n");

             /* modifier nb places*/
             printf("nb palces ? : (o/n) \t ") ;
             scanf("%s",&test) ;
             if(test == 'o'){
                printf("nombre de places : ");
                scanf("%d",&voiture.nbplaces) ;
             } else voiture.nbplaces = voiture.nbplaces ;
             printf("\n");

             /* modifier prix jour*/
             printf("prix jour ? : (o/n) \t ") ;
              scanf("%s",&test) ;
             if(test == 'o'){
                printf("nouv prix jour : ");
                scanf("%d",&voiture.prixJour);
             }else voiture.prixJour = voiture.prixJour ;
             printf("\n");

             /* sauvegarder les modification*/
             fwrite(&voiture,sizeof(voiture),1,file);
        }

        fseek(file, 0, SEEK_SET);  main();
}

/*---------------------------------------supprimer voiture-------------------------------------*/
void Supprimer(FILE *file,FILE *tempV){
   voiture voiture ;
   int trouve = 0;
   int id;
   
   printf("Donnez le id a supprimer : ");
   scanf("%d",&id);

   fseek(file, 0, SEEK_SET);

   // verification de id
  while (fread(&voiture, sizeof(voiture), 1, file) != 0 && trouve==0) {
    if (voiture.idVoiture == id){
        trouve = 1 ;
        break ;
    }
  }

  if (trouve == 0){
    printf("Cette voiture n'existe pas\n");
    system("pause");
    main();
  }

    fseek(file, 0, SEEK_SET);
    
    /* copier les voitures qui n'est pas supprimer dans le fichier "renommerV" */
    while(!feof(file) && fread(&voiture, sizeof(voiture), 1, file))
	{
		if(voiture.idVoiture==id)
		{
            continue;
		}
		else
		{
			fwrite(&voiture,sizeof(voiture),1,tempV);
		}
	}
	fclose(file);
    remove("Voiture.txt");
    fclose(tempV);
    rename("renommerV.txt","Voiture.txt");
    system("cls");
    main();
}
