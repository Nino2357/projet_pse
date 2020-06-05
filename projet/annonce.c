






bet annonce(player ordre[4], team ordre_t[2]){
    bet mise;
    int compt = 0;
    int last_betting;
    bool a_mise = false; //Indique si un joueur à fait une mise (a_misé)
    char* will;
    // premiere mise
    while(a_mise==0){
        printf("Premier joueur, voulez vous miser?  y/n  \n");
        scanf("%c",will);
        if(will!="y"){
            printf("Second joueur, voulez vous miser?  y/n  \n");
            scanf("%c",will);
            if(will!="y"){
                printf("Troisième joueur, voulez vous miser?  y/n  \n");
                scanf("%c",will);
                if(will!="y"){
                    printf("Dernier joueur, voulez vous miser?  y/n  \n");
                    scanf("%c",will);
                    if(will!="y"){
                        mise.goal=0;
                        return mise;
                    }
                    else{
                        printf("Quelle couleur misez vous? (1 = coeur, 2 = carreau, 3 = pique, 4 = trefle)");
                        scanf("%d",&mise.color);
                        printf("Combien misez vous? (Au moins 80, 160 = capot)");
                        scanf("%d",&mise.goal);
                        last_betting=3;
                        a_mise = true;
                    }  
                }
                else{
                        printf("Quelle couleur misez vous? (1 = coeur, 2 = carreau, 3 = pique, 4 = trefle)");
                        scanf("%d",&mise.color);
                        printf("Combien misez vous? (Au moins 80, 160 = capot)");
                        scanf("%d",&mise.goal);
                        last_betting=2;
                        a_mise = true;
                }
            }
            else{
                        printf("Quelle couleur misez vous? (1 = coeur, 2 = carreau, 3 = pique, 4 = trefle)");
                        scanf("%d",&mise.color);
                        printf("Combien misez vous? (Au moins 80, 160 = capot)");
                        scanf("%d",&mise.goal);
                        last_betting=1;
                        a_mise = true;
            }
        }
        else{
                        printf("Quelle couleur misez vous? (1 = coeur, 2 = carreau, 3 = pique, 4 = trefle)");
                        scanf("%d",&mise.color);
                        printf("Combien misez vous? (Au moins 80, 160 = capot)");
                        scanf("%d",&mise.goal);
                        last_betting=0;
                        a_mise = true;
        }
    }
    //surenchere
    while(compt<3){
        printf("Voulez vous surenchérir? y/n");
        scanf("%c",will);
        if(will!="y"){
            printf("Voulez vous surenchérir?  y/n  \n");
            scanf("%s",will);
            if(will!="y"){
                printf("Troisième joueur, voulez vous miser?  y/n  \n");
                scanf("%s",will);
                if(will!="y"){
                    return mise;
                    }
                else{
                        printf("Quelle couleur misez vous? (1 = coeur, 2 = carreau, 3 = pique, 4 = trefle)");
                        scanf("%d",&mise.color);
                        printf("Combien misez vous? (Au moins %d, 160 = capot et 200 = coinche)",mise.goal);
                        scanf("%d",&mise.goal);
                        last_betting=2;
                }
            }
            else{
                        printf("Quelle couleur misez vous? (1 = coeur, 2 = carreau, 3 = pique, 4 = trefle)");
                        scanf("%d",&mise.color);
                        printf("Combien misez vous? (Au moins 80, 160 = capot)");
                        scanf("%d",&mise.goal);
                        last_betting=1;
            }
        }
        else{
                        printf("Quelle couleur misez vous? (1 = coeur, 2 = carreau, 3 = pique, 4 = trefle)");
                        scanf("%d",&mise.color);
                        printf("Combien misez vous? (Au moins 80, 160 = capot)");
                        scanf("%d",&mise.goal);
                        last_betting=0;
        }
    }
    mise.equipe = ordre_t[last_betting];
}