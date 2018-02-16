#include <stdio.h>
#include <stdlib.h>

#define SENTINEL -100000000

struct dugum {
    int icerik;
    struct dugum *sol;
    struct dugum *sag;
};

struct ikili_arama_agaci{
    struct dugum *kok;
};

void ikili_arama_agaci_olustur(struct ikili_arama_agaci **agac){
    *agac=(struct ikili_arama_agaci*)malloc(sizeof(struct ikili_arama_agaci));
    if(*agac==NULL){
        printf("Heapte gerekli yer ayrilamadi... exit ...\n");
        exit(1);
    }
    (*agac)->kok = NULL;
}

int ikili_agac_bosmu(struct ikili_arama_agaci *agac){
   if(agac->kok==NULL) return 1;
   else return 0;
}

struct dugum* dugum_olustur(int icerik){
    struct dugum *d = (struct dugum*)malloc(sizeof(struct dugum));
    if(d==NULL){
        printf("Heapte gerekli yer ayrilamadi... exit ...\n");
        exit(1);
    }
    d->icerik = icerik; //(*d).icerik=icerik;
    d->sol=d->sag=NULL;
    return d;
}


void ekle(struct ikili_arama_agaci *agac,int icerik){ 
	struct dugum *dugum; 
    struct dugum *d; 
    struct dugum *geri; 
    
    d=agac->kok;
    while(d!=NULL){
        geri=d;
        if(icerik < d->icerik) d=d->sol;
        else if(icerik > d->icerik) d= d->sag;
        else return;
    } 
    dugum=dugum_olustur(icerik); 
    if(agac->kok==NULL){
        agac->kok = dugum;
        return;
    }
    if(icerik < geri->icerik) geri->sol = dugum;
    else geri->sag = dugum;
}

void inorder_yardimci(struct dugum *kok){
    
    if(kok==NULL) return;
    inorder_yardimci(kok->sol);
    printf("%4d ",kok->icerik);
    inorder_yardimci(kok->sag);
    
}

void inorder(struct ikili_arama_agaci *agac){
    if(agac==NULL) return;
    inorder_yardimci(agac->kok);
    printf("\n");
}

void preorder_yardimci(struct dugum *kok){
    
    if(kok==NULL) return;
    printf("%4d ",kok->icerik);
    preorder_yardimci(kok->sol);
    preorder_yardimci(kok->sag);
    
}
void preorder(struct ikili_arama_agaci *agac){
    if(agac==NULL) return;
    preorder_yardimci(agac->kok);
    printf("\n");
}

void postorder_yardimci(struct dugum *kok){
    if(kok==NULL) return;   
    postorder_yardimci(kok->sol);
    postorder_yardimci(kok->sag);
    printf("%4d ",kok->icerik);
    
}

void postorder(struct ikili_arama_agaci *agac){
    if(agac==NULL) return;
    postorder_yardimci(agac->kok);
    printf("\n");
}

int dugum_sayisi(struct dugum *kok){
    if(kok==NULL) return 0;
    return 1+dugum_sayisi(kok->sol)+dugum_sayisi(kok->sag);
}

int yaprak_sayisi(struct dugum *kok){
    if(kok==NULL) return 0;
    if(kok->sol==NULL && kok->sag == NULL) return 1;
    else return yaprak_sayisi(kok->sol)+yaprak_sayisi(kok->sag);
}

void sil(struct ikili_arama_agaci *agac, int silinen){
    
    struct dugum *d=agac->kok;
    struct dugum *parent=NULL;
    struct dugum *d1,*d2;
    int sol;
    while(d!=NULL){
        if(silinen < d->icerik){  
            parent=d; d=d->sol; sol=1;
        }
        else if(silinen > d->icerik){
            parent=d; d=d->sag; sol = 0;
        }
        else break;
    }
    if(d==NULL) return;
    if(d->sol==NULL){
        if(parent==NULL) agac->kok=d->sag;
        else{
            if(sol==1) parent->sol=d->sag;
            else parent->sag=d->sag;
        }
    }
    else if(d->sag==NULL){
        if(parent==NULL) agac->kok=d->sol;
        else {
            if(sol==1) parent->sol=d->sol;
            else parent->sag = d->sol;
        }
    }
    else { 
        d1=d->sol;
        d2=NULL;
        while(d1->sag!=NULL){
            d2=d1;
            d1=d1->sag;
        }
        if(d2!=NULL){
            d2->sag= d1->sol;
            d1->sol=d->sol;
        }
        d1->sag = d->sag;
        if(parent==NULL) agac->kok=d1;
        else {
            if(sol==1) parent->sol=d1;
            else parent->sag=d1;
        }
    } 
    
  /*  else {
        d1=d->sag;
        d2=NULL;
        while(d1->sol!=NULL){
            d2=d1;
            d1=d1->sol;
        }
        if(d2!=NULL){
            d2->sol= d1->sag;
            d1->sag=d->sag;
        }
        d1->sol = d->sol;
        if(parent==NULL) agac->kok=d1; 
        else {
            if(sol==1) parent->sol=d1;
            else parent->sag=d1;
        }
    } */
    free(d); 
}

void yoket(struct dugum **kok){
    if(*kok!=NULL){
        yoket(&(*kok)->sol);
        yoket(&(*kok)->sag);
        free(*kok);
        *kok=NULL;
    }
}

int foo(struct dugum *kok){ // ic dugum sayisi
    if(kok==NULL) return 0;
    else if(kok->sol!=NULL || kok->sag!=NULL) 
        return 1+foo(kok->sol) + foo(kok->sag);
    else return 0;
}

struct dugum *kardes_bul(struct dugum *kok,struct dugum *a){
	struct dugum *once, *ileri = kok;
	
	if(kok == NULL) return;
	while(ileri!=NULL){
		once = ileri;
		if(ileri->icerik < a->icerik)	ileri = ileri->sag;
		else	ileri = ileri->sol;
		
		if(ileri == a && ileri->icerik > once->icerik)
			return once->sag;
		else if(ileri==a && ileri->icerik > once->icerik)
			return once->sol;
	}
}

struct ikili_arama_agaci* en_buyuk_bul(struct dugum* kok){
	if(kok==NULL) return;
	
	while(kok->sag!=NULL){
		kok = kok->sag;
	}
	return kok;
}

struct ikili_arama_agaci *en_kucuk_bul(struct dugum* kok){
	if(kok==NULL) return;
	while(kok->sol!=NULL){
		kok = kok->sol;
	}
	return kok;
}

int main(int argc, char** argv) {
    struct ikili_arama_agaci *agac=NULL;
    ikili_arama_agaci_olustur(&agac);
    
    ekle(agac,100);
    ekle(agac,50);
    ekle(agac,200);
    ekle(agac,25);
    ekle(agac,75);
    ekle(agac,20);
    ekle(agac,35);
    ekle(agac,98);
//    ekle(agac,-200);
    ekle(agac,99);
    ekle(agac,500);
    ekle(agac,400);
    ekle(agac,300);
    inorder(agac);
    //preorder(agac);
   // sil(agac,100);
    postorder(agac);
    printf("Dugum Sayisi : %d\n",dugum_sayisi(agac->kok));
    printf("Yaprak sayisi: %d\n",yaprak_sayisi(agac->kok));
   // preorder(agac);
  //  postorder(agac);
    printf("Ic dugum sayisi: %4d\n",foo(agac->kok));
  	struct ikili_arama_agaci *eb = en_buyuk_bul(agac->kok);
    printf("En buyuk eleman : %d\n",*eb);
    struct ikili_arama_agaci *ek = en_kucuk_bul(agac->kok);
    printf("En kucuk eleman : %d\n",*ek);
    int kb = kardes_bul(agac->kok, en_buyuk_bul(agac->kok))->icerik;
    printf("Kardes bul : %d\n",kb);
   	yoket(&(agac->kok));
    
    return (EXIT_SUCCESS);
}
