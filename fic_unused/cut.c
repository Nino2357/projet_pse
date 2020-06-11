
void cut(deck* d, int i){
    printf("test2\n");
    deck *temp;
    printf("test3\n");
    int j=i;
    printf("j:%d/n",j);
    for(j=i; j<d->size; j++){
        printf("j:%d/n",j);
        //temp->tab[j-i] = d->tab[j];
        temp->size ++;
        }
    d->size=i;
    concat_deck(temp, d);
    d = temp;
}

void concat_deck(deck* d1, deck* d2){
    for(int i=0;i<d2->size;i++){
        d1->tab[d1->size]=d2->tab[i];
        d1->size ++;
    }
}
