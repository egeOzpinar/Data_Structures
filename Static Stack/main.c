#include <stdio.h>
#include <stdlib.h>

#define SENTINEL -10000000

struct yigin{
    int *dizi;
    int ust;
    int kapasite;
};

struct yigin *kapasiteyi_artir(struct yigin **, int);

struct yigin* yigin_olustur(int kapasite){
    if(kapasite<=0) {
        printf("Kapasite pozitif bir tam sayi olmali... ");
        exit(1);
    } 
    struct yigin *ptr=(struct yigin*)malloc(sizeof(struct yigin));
    ptr->dizi=(int *)malloc(kapasite*sizeof(int));
    ptr->ust=-1;
    ptr->kapasite = kapasite;
    return ptr;
}

void yigin_olustur_parametre_ile(int kapasite, struct yigin **y){
    if(kapasite<=0) {
        printf("Kapasite pozitif bir tam sayi olmali... ");
        exit(1);
    }
    *y=(struct yigin*)malloc(sizeof(struct yigin));
    (*y)->dizi=(int *)malloc(kapasite*sizeof(int));
    (*y)->ust=-1;
    (*y)->kapasite=kapasite;
}

int yigin_bosmu(struct yigin *y){
    if(y->ust==-1) return 1;
    else return 0;
}
int yigin_dolumu(struct yigin *y){
    if(y->ust==y->kapasite-1) return 1;
    else return 0;
}

void yigina_ekle(int eleman, struct yigin **y){
    if(yigin_dolumu(*y)) {
       // printf("Yigin dolu, ekleme yapilamiyor...");
       // return;
        *y=kapasiteyi_artir(y,2);
    }
    
    (*y)->dizi[++(*y)->ust]=eleman;
    
}    

void yigin_yaz(struct yigin *y){
    int i;
    if(y==NULL) {
        printf("Yigin icin yer ayrilmamis. Cikiyorum...\n");
        return;
    }
    printf("Yigin Kapasitesi       :%4d\n",y->kapasite);
    printf("Yigindaki Eleman Sayisi:%4d\n",y->ust+1);
    for(i=y->ust; i>=0; i--){
        printf("%4d ",y->dizi[i]);
    }
    printf("\n");
}

int yigin_eleman_sil(struct yigin *y){
    if(yigin_bosmu(y))return SENTINEL;
    return y->dizi[y->ust--];
        
    
}

void yigin_yok_et(struct yigin **y){
    free((*y)->dizi);
    free(*y);
    *y=NULL;
}

struct yigin *kapasiteyi_artir(struct yigin **ptr, int kackat){
    struct yigin *yeni;
    int i;
    yeni=yigin_olustur(kackat*((*ptr)->kapasite));
    
    for(i=0; i<=(*ptr)->ust; i++)
		yeni->dizi[i]=(*ptr)->dizi[i];
		
    yeni->ust=(*ptr)->ust;
    yigin_yok_et(&(*ptr)); // yigin_yok_et(ptr);
    return yeni;
}

void kapasiteyi_artir_yeni(struct yigin **ptr, int kackat){
    struct yigin *yeni;
    int i;
    yeni=yigin_olustur(kackat*((*ptr)->kapasite));
    for(i=0; i<=(*ptr)->ust; i++)
		yeni->dizi[i]=(*ptr)->dizi[i];
    yeni->ust=(*ptr)->ust;
    yigin_yok_et(&(*ptr)); // yigin_yok_et(ptr);
    *ptr=yeni;
}


int main(int argc, char** argv) {
    struct yigin *A=NULL;
    int x;
    yigin_olustur_parametre_ile(1,&A);
    yigina_ekle(0,&A);
    yigina_ekle(40,&A);
    yigina_ekle(5,&A);
    yigina_ekle(10,&A);

    A=kapasiteyi_artir(&A,5);

	yigina_ekle(-10,&A);
    yigin_yaz(A);
    
    yigina_ekle(-40,&A);
    yigina_ekle(25,&A);
    yigina_ekle(125,&A);
    yigina_ekle(900,&A);
    
	yigin_yaz(A);
      
    printf("Silinen Eleman: %4d\n",yigin_eleman_sil(A));
    printf("Silinen Eleman: %4d\n",yigin_eleman_sil(A));
    printf("Silinen Eleman: %4d\n",yigin_eleman_sil(A));
    yigin_yaz(A);
    yigina_ekle(88,&A); 
    yigin_yaz(A);
      
   return (EXIT_SUCCESS);
}

