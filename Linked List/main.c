#include <stdio.h>
#include <stdlib.h>

typedef struct hucre{
	int icerik;
	struct hucre *sonraki;
}hucre;

hucre *hucre_olustur(int icerik){
	hucre *a;
	a = (hucre*)malloc(sizeof(hucre)); 
	if (a == NULL){
		printf("Heap alanýnda yer ayrýlamadý");
		exit(1);
	}
	a->icerik = icerik;
	a->sonraki = NULL;
	return a;
}

hucre *liste_basina_ekle(int icerik, hucre **liste_basi){
	hucre* a = hucre_olustur(icerik);
	a->sonraki = *liste_basi; 
	*liste_basi = a;
}

hucre **ters(hucre **liste_basi){
	hucre *gecici;
	if(*liste_basi == NULL)
		return liste_basi;
	
	else if((*liste_basi)->sonraki == NULL)
		return &((*liste_basi)->sonraki);
	
	else {
		gecici = *liste_basi;
		*liste_basi = (*liste_basi)->sonraki;
		*ters(liste_basi) = gecici;
		gecici -> sonraki = NULL;
		return &(gecici->sonraki);
	}
}

hucre* liste_sonuna_ekle(int icerik, hucre **liste_basi){
	hucre* a = hucre_olustur(icerik);
	if(*liste_basi == NULL){
		a->sonraki = *liste_basi;
		*liste_basi = a;
	}
	else{
		hucre *x = *liste_basi;
		while (x->sonraki!=NULL){
			x=x->sonraki;
		}
		x->sonraki = a;
	}
}

void liste_sirali_ekle(int icerik, hucre **liste_basi){
	hucre *a,*b, *eklenen;
	b = *liste_basi;
	while(b!=NULL && b->icerik <= icerik){ 
		a=b;
		b = b->sonraki;
	}
	eklenen=hucre_olustur(icerik);
	if(b==*liste_basi){
		eklenen->sonraki = *liste_basi;
		*liste_basi = eklenen;
	}
	else{
		a->sonraki = eklenen;
		eklenen->sonraki = b;
	}
}

hucre* liste_sirala(hucre **liste_basi){
	hucre *a,*b,*c,*d;
	
	if(*liste_basi == NULL || (*liste_basi)->sonraki == NULL){
		return;
	}
	d = (*liste_basi)->sonraki;
	(*liste_basi)->sonraki = NULL;
	
	while(d!=NULL){
		c=d;
		d=d->sonraki;
		b=*liste_basi;
		while(b!=NULL && b->icerik < c->icerik){
			a=b;
			b=b->sonraki;
		}
		if(b==*liste_basi){
			c->sonraki = *liste_basi;
			*liste_basi = c;
		}
		else{
			a->sonraki = c;
			c->sonraki = b;
		}
	}
}

void liste_ters_cevir(hucre **liste_basi){
	hucre *a,*b;
	a = NULL;
	while(*liste_basi!=NULL){
		b = *liste_basi;
		*liste_basi = (*liste_basi)->sonraki;
		b->sonraki = a;
		a = b;
	}
	*liste_basi = a;
}

void liste_ucur(hucre **liste_basi){
	hucre *simdiki;
	while(*liste_basi!=NULL){
		simdiki = *liste_basi;
		*liste_basi = (*liste_basi) -> sonraki;
		free(simdiki);
	}
}


hucre* liste_eleman_sil(int silinen, hucre **liste_basi){
	hucre *temp = *liste_basi;
	hucre *once;  //temp ve bir önceki elemanýný tutmamýz gerekiyor.
	while(temp!=NULL && temp->icerik!=silinen){
		once = temp;
		temp = temp->sonraki;
	}
	
	if(temp==NULL)
		return 0;
	else{
		if(temp==*liste_basi)
			*liste_basi = (*liste_basi)->sonraki;
		else{
			once->sonraki = temp->sonraki;
			free(temp);
		}
	}
}

void liste_yaz(hucre *liste_basi){ 
	while(liste_basi!=NULL){
		printf("%d\t",liste_basi->icerik);
		liste_basi = liste_basi->sonraki;
	}
	printf("\n");
}

void liste_yaz_recursive(hucre *liste_basi){
	if(liste_basi!=NULL){
		printf("%4d ",liste_basi->icerik);
		liste_yaz_recursive(liste_basi->sonraki);
	}
}

void liste_yaz_recursive_tersten(hucre *liste_basi){
	if(liste_basi!=NULL){
		liste_yaz_recursive_tersten(liste_basi->sonraki);
		printf("%4d ",liste_basi->icerik);
	}
}

int main(int argc, char** argv) {
	hucre *liste_basi=NULL;
	liste_basina_ekle(100,&liste_basi);
	liste_basina_ekle(19,&liste_basi);
	liste_basina_ekle(22,&liste_basi);
	
	liste_sonuna_ekle(12,&liste_basi);
	liste_sonuna_ekle(44,&liste_basi);	
	
	liste_eleman_sil(19,&liste_basi);
	liste_yaz(liste_basi);
	liste_ters_cevir(&liste_basi);
	printf("\n");
	liste_yaz(liste_basi);
	ters(&liste_basi);
	
	liste_yaz(liste_basi);
	liste_sirala(&liste_basi);
	liste_yaz(liste_basi);
	liste_sirali_ekle(34,&liste_basi);
	liste_basina_ekle(17,&liste_basi);
	liste_yaz(liste_basi);
	
	return (EXIT_SUCCESS);
}
