#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 10
#define MAX2 200
void kullanici_adi_al(int kullanici_sayisi, char kullanici_adi[][MAX]);//kullanýcý adlarini alir
void boyut_al(int*N);//oyun tahtasinin boyutunu alir
void matrisi_sifirla(int N, int matris[][MAX]);//oyun tahtasini sifirlar
void drawBoard(int matris[][MAX], int N);// oyun tahtasini cizer
void readFromFile(int matris[][MAX], char *fileName);//dosyadan matris okur
void koordinat_al(int *x1, int *x2, int *y1, int *y2);//hareket noktasýnýn ve hedef noktasinin koordinatlari alinir
void saga_git(int y1, int y2, int x1, int matris[][MAX], int temp, int N);//hedef noktasi hareket noktasinin saginda kaliyorsa saga gider
void sola_git(int y1, int y2, int x1, int matris[][MAX], int temp, int N);//hedef noktasi hareket noktasinin solunda kaliyorsa sola gider
void asagi_git(int x1, int x2, int y1, int matris[][MAX], int temp, int N);//hedef noktasi hareket noktasinin asagisinda kaliyorsa asagi gider
void yukari_git(int x1, int x2, int y1, int matris[][MAX], int temp, int N);//hedef noktasi hareket noktasinin yukarisinda kaliyorsa yukari gider
void rastgele_matris_olustur(int N, int matris[][MAX]);//rastgele modda rastgele matris olusturur
void matris_tut(int k, int N, int matris[][MAX], int matris_tutan[][MAX][MAX]);//undo için her adýmdaki oyun tahtasini tutar
void geri_al(int k, int N, int matris[][MAX], int matris_tutan[][MAX][MAX]);//undo
int dolu_mu(int N, int matris[][MAX]);//oyun tahtasinin tüm hücreleri dolu mu kontrolü yapýlýr
void koordinat_bul(int matris[][MAX], int N, int nokta[][4]);//oyun baslangicindaki oyun tahtasinda yer alan sayilarin koordinatlari bulunur ve nokta matrisine kaydedilir
void path_guncelle(int path[][MAX][MAX2], int length, int count,int k);//yollari hesaplayan count_paths1 fonksiyonunda degismeyen yol koordinatlarýný da tutar
int count_paths1(int i, int j, int i1, int j1, int n, int matris[][MAX], int path[][MAX][MAX2], int path_length_arr[][MAX2],int path_length,int *count, int k);//her bir sayýnýn olusturabilecegi yollari hesaplar
void kombinasyonHesapla(int ihtimal[][MAX], int count_dizi[], int satir, int carpim, int secilenler[5000][MAX], int secilenSayisi, int N,int *count );//her sayý icin bulunan yollarýn farklý kombinasyonu hesaplanir
void matris_yedekle(int N, int matris[][MAX], int temp_matris[][MAX]);//oluþturulan matris tekrar kullanýlmak istenirse bu fonksiyonla yedeklenir
int main(){
	srand(time(NULL));
	int dd=1, dd2=1, dd3=3, flag=1, secim, sec, N, M, sayac, temp, count, count1, count2,coz, evet,carpim,deger1;
	int i, j, k, l, m, x1, x2, y1, y2;
	int matris[MAX][MAX];
	double scor_matrisi[MAX][MAX];
	int temp_matris[MAX][MAX];
	int matris_tutan[MAX][MAX][MAX];
	int nokta[MAX][4];
	int count_dizi[MAX]={0};
	int path_length[MAX][MAX2];	
	int ihtimal[MAX][MAX];
	char geri;
	char kullanici_adi[MAX][MAX];
	char fileName[20];
	double manuel,otomatik,geri_say,rastgele,dosyadan,boyut_s,sure;
	printf("SAYI ESLESTIRME OYUNUNA HOS GELDINIZ!!\n");
	printf("\nKullanici sayisini giriniz: ");
	scanf(" %d", &M);
	m=0;
	while(flag==1 && m<M){
		manuel=0;
		otomatik=0;
		geri_say=0;
		rastgele=0;
		dosyadan=0;
		boyut_s=0;
		printf("\n");
		kullanici_adi_al(m, kullanici_adi);	
		printf("\n");	
		j=0;
		while(kullanici_adi[m][j]){
			printf("%c",kullanici_adi[m][j]);
			j++;
		}
		printf(" adli kullanici icin oyun baslamistir.\n\n");
		dd=1;
		dd2=1;
		count=0;
		while(dd==1){				
			printf("\nANA MENU\n");
			printf("[1]Rastgele Matris Olustur\n[2]Dosyadan Matris Olustur\n[3]Kullanicilarin Skorlarini Goster\n[4]Diger kullaniciya gec\n[5]cikis\nYapmak istediginiz islemi seciniz: ");
			scanf(" %d",&secim);
			if(secim==1){
				rastgele++;
				dd2=1;
				while(dd2==1){
					printf("\n[1]Manuel modda oyna\n[2]Otomatik Modda Oyna\n[3]Ana Menuye don\nYapmak istediginiz islemi seciniz: ");
					scanf(" %d", &sec);
					if(sec==1){	
						manuel++;
						count++;											
						evet=1;
						while(evet==1){
							boyut_al(&N);
							int path[N][MAX][MAX2];
							boyut_s+=N;
							rastgele_matris_olustur(N, matris);
							time_t start,end;
							time(&start);
							koordinat_bul(matris, N, nokta);
							for(i=0;i<N;i++){//her sayý için oluþturulabilecek yollar hesaplanýr ve dizide yol sayýsý tutulur							
								count1=0;		
								count_paths1(nokta[i][0],nokta[i][1],nokta[i][2],nokta[i][3],N,matris,path,path_length,0,&count1,i);
								matris[nokta[i][0]][nokta[i][1]]=i+1;							
								count_dizi[i]=count1;
							}
							carpim=0;	
							for(i=0;i<N;i++){//carpim yaziyor ama toplama islemi yapýlýyor fazla deðisken tutmamak için
								if(count_dizi[i]==0){
									carpim++;
								}
							}	
							if(carpim>0){//her bir sayý için oluþturulabilecek yol yoksa
								printf("\nmatris cozumsuzdur.\n");
								printf("\nyeniden matris olusturulsun ister misiniz(evet icin 1 giriniz): ");
								scanf(" %d",&evet);
								if(evet!=1){
									time(&end);
									sure=sure+start-end;
									dd2=1;
								}								
							}
							else{//tüm sayýlar için oluþturulabilecek yollar varsa çözülüp çöözülmeyeceði ihtimalini kullanýcýya sordum
								printf("\n\nmatris cozumsuzse 1 girin: ");
								scanf(" %d",&coz);
								if(coz==1){
									printf("\nyeniden matris olusturulsun ister misiniz(evet icin 1 giriniz): ");
									scanf(" %d",&evet);
									if(evet!=1){
										time(&end);
										sure=sure+start-end;
										dd2=1;
									}			
								}
								else{									
									while(dolu_mu(N,matris)<N*N){
								    	koordinat_al(&x1,&x2,&y1,&y2);
									    temp=matris[x1][y1];							
										matris_tut(sayac,N,matris, matris_tutan);
										if(x1<0 || x2<0 || y1<0|| y2<0 || x1>=N || x2>=N || y1>=N|| y2>=N){
											printf("\nbu islem gerceklestirilemez\n");
										}
									    else if(x1==x2){
									    	if(y1<y2){
										    	saga_git(y1,y2,x1,matris,temp,N);
											}
											else{
												sola_git(y1,y2,x1,matris,temp,N);
											}						
										}
										else if(y1==y2){
											if(x1<x2){
												asagi_git(x1,x2,y1,matris,temp,N);
											}
											else{
												yukari_git(x1,x2,y1,matris,temp,N);
											}															
										}
										else{
											printf("\nbu islem gerceklestirilemez\n");
											
										}
										sayac++;
										matris_tut(sayac,N,matris, matris_tutan);
										geri='r';
										while(geri=='r' && sayac>0){
											printf("\ngeri almak istiyorsaniz 'r' giriniz: ");
											scanf(" %c",&geri);
											if(geri=='r'){
												geri_al(sayac-1,N,matris,matris_tutan);
												drawBoard(matris,N);
												sayac--;	
											}
										}														
									} 
									
									matrisi_sifirla(N,matris);
								}	
							}															
						}																							
						dd2=1;
					}
					else if(sec==2){
						otomatik++;
						count++;
						evet=1;
						time_t start,end;
						time(&start);
						while(evet==1){
							boyut_al(&N);
							boyut_s+=N;
							matrisi_sifirla(N,matris);
							rastgele_matris_olustur(N, matris);
							int path[N][MAX][MAX2];
							
							koordinat_bul(matris, N, nokta);
							for(i=0;i<N;i++){//her bir sayý için oluþturulabilecek yol sayýsý bulunur ve diziye kaydedilir							
								count1=0;		
								count_paths1(nokta[i][0],nokta[i][1],nokta[i][2],nokta[i][3],N,matris,path,path_length,0,&count1,i);
								matris[nokta[i][0]][nokta[i][1]]=i+1;							
								count_dizi[i]=count1;
							}
							carpim=0;//deðiþkenin adi çarpim ancak toplama iþlemi yapýlýr fazladan deðiþken üretmemek icin	
							for(i=0;i<N;i++){
								if(count_dizi[i]==0){
									carpim++;
								}
							}	
							if(carpim>0){//herhangi bir sayý icin olusturulabilecek bir yol yoksa matris cozumsuzdur
								printf("\nmatris cozumsuzdur.\n");
								printf("\nyeniden matris olusturulsun ister misiniz(evet icin 1 giriniz): ");
								scanf(" %d",&evet);
								if(evet!=1){
									time(&end);
									sure=sure+start-end;
									printf("\n");
									dd2=1;
								}								
							}
								
							else{
								printf("\n");
								matris_yedekle(N,matris,temp_matris);								
								printf("\n");																											
								for(i=0;i<N;i++){
									for(j=0;j<count_dizi[i];j++){
										ihtimal[i][j]=j;
									}
								}														
								int secilenler[5000][MAX]={0};
								count1=0;
								kombinasyonHesapla(ihtimal, count_dizi, 0, carpim, secilenler, 0,N,&count1);
								dd3=1;
								i=0;
									
								while(i<count1 && dd3==1){//i ihtimal ve dd3 0 olana kadar dönülür			
									for(l=0;l<N;l++){//i ihtimalinde her sayi nin yollarinda 0 ya da o sayi var mý diye kontrol yapýlýr ve 0 veya o sayýysa o sayýya eþitlenir							
										for(k=0;k<path_length[l][secilenler[i][l]];k+=2){
											if(matris[path[l][secilenler[i][l]][k]][path[l][secilenler[i][l]][k+1]]==0 || matris[path[l][secilenler[i][l]][k]][path[l][secilenler[i][l]][k+1]]==l+1){
												matris[path[l][secilenler[i][l]][k]][path[l][secilenler[i][l]][k+1]]=l+1;
											}							
										}					
									}
									count2=0;
									for(l=0;l<N;l++){//yollarýn üstüste gelme ihtimaline karþý kontrol						
										for(k=0;k<path_length[l][secilenler[i][l]];k+=2){
											if(matris[path[l][secilenler[i][l]][k]][path[l][secilenler[i][l]][k+1]]==l+1){
												count2++;
											}							
										}					
									}			
									if(count2==N*N){
										dd3=0;
									}		
									else{
										matris_yedekle(N,temp_matris,matris);												
										i++;
										if(i==count1){
											dd3=0;
										}		
									}										
								}					
								drawBoard(matris,N);
								time(&end);
								sure=start-end;							
								dd2=1;					
							}															
						}								
											
															
						dd2=1;
					}
					else if(sec==3){
						dd2=0;
						dd=1;							
					}
					else{
						printf("Gecerli bir secim yapmadiniz.\n");
						dd2=1;
					}
				}			
			}
			else if(secim==2){
				dosyadan++;	
				dd2=1;
				while(dd2==1){
					printf("\n[1]Manuel modda oyna\n[2]Otomatik Modda Oyna\n[3]Ana Menuye don\nYapmak istediginiz islemi seciniz: ");
					scanf(" %d", &sec);
					if(sec==1){
						manuel++;
						count++;					
						boyut_al(&N);
						matrisi_sifirla(N,matris);
						boyut_s+=N;
						printf("Dosya Adini Giriniz: ");
						scanf(" %s",fileName);										
						readFromFile(matris, fileName);
						printf("\n");
					    drawBoard(matris,N);
					    printf("\n");
					    sayac=0;
					    time_t start, end;
					    time(&start);
					    while(dolu_mu(N,matris)<N*N){					    	
					    	koordinat_al(&x1,&x2,&y1,&y2);			    
						    temp=matris[x1][y1];							
							matris_tut(sayac,N,matris, matris_tutan);
							if(x1<0 || x2<0 || y1<0|| y2<0 || x1>=N || x2>=N || y1>=N|| y2>=N){
								printf("\nbu islem gerceklestirilemez\n");
							}
						    else if(x1==x2){
						    	if(y1<y2){
							    	saga_git(y1,y2,x1,matris,temp,N);
								}
								else{
									sola_git(y1,y2,x1,matris,temp,N);
								}						
							}
							else if(y1==y2){
								if(x1<x2){
									asagi_git(x1,x2,y1,matris,temp,N);
								}
								else{
									yukari_git(x1,x2,y1,matris,temp,N);
								}															
							}
							
							else{
								printf("\nbu islem gerceklestirilemez\n");
								
							}
							sayac++;
							matris_tut(sayac,N,matris, matris_tutan);
							geri='r';
							while(geri=='r' && sayac>0){
								printf("\ngeri almak istiyorsaniz 'r' giriniz: ");
								scanf(" %c",&geri);
								if(geri=='r'){
									geri_al(sayac-1,N,matris,matris_tutan);
									drawBoard(matris,N);
									sayac--;	
								}
							}														
						} 
						time(&end);
						sure=sure+start-end; 
						matrisi_sifirla(N,matris); 			    
						dd2=1;
					}
					else if(sec==2){
						otomatik++;
						count++;			
						boyut_al(&N);
						matrisi_sifirla(N,matris);
						int path[N][MAX][MAX2];
						boyut_s+=N;
						printf("Dosya Adini Giriniz: ");
						scanf(" %s",fileName);										
						readFromFile(matris, fileName);
						drawBoard(matris,N);
						printf("\n");
						time_t start, end;//süre tutar
						time(&start);
						matris_yedekle(N,matris,temp_matris);						
						koordinat_bul(matris, N, nokta);
						printf("\n");					
						for(i=0;i<N;i++){//yol sayýsý hesaplanýr ve her sayýnýn kac tane yol yapabilme ihtimali olduðu dizide tutulur							
							count1=0;		
							count_paths1(nokta[i][0],nokta[i][1],nokta[i][2],nokta[i][3],N,matris,path,path_length,0,&count1,i);
							matris[nokta[i][0]][nokta[i][1]]=i+1;							
							count_dizi[i]=count1;
						}
						for(i=0;i<N;i++){
							for(j=0;j<count_dizi[i];j++){
								ihtimal[i][j]=j;
							}
						}												
						int secilenler[5000][MAX]={0};
						count1=0;
						kombinasyonHesapla(ihtimal, count_dizi, 0, carpim, secilenler, 0,N,&count1);
						dd3=1;
						i=0;						
						while(i<count1 && dd3==1){//hesaplanan ihtimal ve dd3 0olana kadar döner		
							for(l=0;l<N;l++){//i ihtimalinde her sayi nin yollarinda 0 ya da o sayi var mý diye kontrol yapýlýr ve 0 veya o sayýysa o sayýya eþitlenir					
								for(k=0;k<path_length[l][secilenler[i][l]];k+=2){
									if(matris[path[l][secilenler[i][l]][k]][path[l][secilenler[i][l]][k+1]]==0 || matris[path[l][secilenler[i][l]][k]][path[l][secilenler[i][l]][k+1]]==l+1){
										matris[path[l][secilenler[i][l]][k]][path[l][secilenler[i][l]][k+1]]=l+1;
									}							
								}					
							}
							count2=0;
							for(l=0;l<N;l++){//yollarýn üstüste gelme ihimaline karþý kontrol						
								for(k=0;k<path_length[l][secilenler[i][l]];k+=2){
									if(matris[path[l][secilenler[i][l]][k]][path[l][secilenler[i][l]][k+1]]==l+1){
										count2++;
									}							
								}					
							}			
							if(count2==N*N){
								dd3=0;
							}		
							else{
								matris_yedekle(N,temp_matris,matris);										
								i++;		
							}										
						}
						if(i==count1){
							printf("\nmatris cozumsuz\n");
						}
						else{
							drawBoard(matris,N);
						}					
						
						time(&end);
						sure=sure+start-end;						
						dd2=1;
					}
					else if(sec==3){
						dd2=0;
						dd=1;
							
					}
					else{
						printf("Gecerli bir secim yapmadiniz.\n");
						dd2=1;
					}
				}			
			}
			else if(secim==3){//oyuncularýn skorlarý gösterilir
				scor_matrisi[m][0]=count;
				scor_matrisi[m][1]=manuel*10;
				scor_matrisi[m][2]=otomatik*5;
				scor_matrisi[m][3]=geri_say*-1;
				scor_matrisi[m][4]=rastgele*10;
				scor_matrisi[m][5]=dosyadan*5;
				scor_matrisi[m][6]=boyut_s*10;
				scor_matrisi[m][7]=sure;
				scor_matrisi[m][8]=0;
				for(i=0;i<8;i++){
					scor_matrisi[m][8]+=scor_matrisi[m][i];					
				}
				printf("\n");
				for(i=0;i<=m;i++){
					j=0;
					while(kullanici_adi[i][j]){
						printf("%c",kullanici_adi[i][j]);
						j++;
					}
					printf(":\noynadigi oyun sayisi: %d\n", scor_matrisi[i][0]);
					printf("oyun scoru: %lf",scor_matrisi[i][8]);
					printf("\n");
				}
				dd=1;
			}
			else if(secim==4){//oynayan oyuncunun skorlarý kaydedilir ve diðer oyuncuya geçilir
				scor_matrisi[m][0]=count;
				scor_matrisi[m][1]=manuel*10;
				scor_matrisi[m][2]=otomatik*5;
				scor_matrisi[m][3]=geri_say*-1;
				scor_matrisi[m][4]=rastgele*10;
				scor_matrisi[m][5]=dosyadan*5;
				scor_matrisi[m][6]=boyut_s*10;
				scor_matrisi[m][7]=sure;
				scor_matrisi[m][8]=0;
				for(i=0;i<8;i++){
					scor_matrisi[m][8]+=scor_matrisi[m][i];
				}
				m++;
				count=0;
				manuel=0;
				otomatik=0;
				geri_say=0;
				rastgele=0;
				dosyadan=0;
				boyut_s=0;
				sure=0;
				dd=0;
			}
			else if(secim==5){//oyun sonlandýrýlýr
				printf("Oyun sonlandirilmistir.");					
				flag=0;
				dd=0;
			}
			else{//yanlýs giriþ yapýlmýstýr tekrar girdi alýnýr
				printf("Gecerli bir secim yapmadiniz.\n");
				dd=1;
			}
		}			
	}	
	return 0;
}
void kullanici_adi_al(int kullanici_sayisi, char kullanici_adi[][MAX]){//kullanýcý adlarini alir
	int i;
	char isim[MAX];
	printf("kullanici adinizi giriniz: ");
	scanf(" %s",&isim);
	i=0;
	while(isim[i]){
		kullanici_adi[kullanici_sayisi][i]=isim[i];
		i++;
	}
}
void boyut_al(int*N){//oyun tahtasinin boyutunu alir
	printf("\nOyun tahtasinin boyutunu giriniz: ");
	scanf(" %d", N);
}
void matrisi_sifirla(int N, int matris[][MAX]){//oyun tahtasini sifirlar
	int i,j;
	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			matris[i][j]=0;
		}
	}
}
void drawBoard(int matris[][MAX], int N){// oyun tahtasini cizer
    int i,j,k;
    printf("\n     ");
    for (k=0;k<N;k++)
        printf("  %d    ",k);
    for(i=0;i<N;i++){
        printf("\n    ");        
        for (k=0;k<N;k++)
            printf("-------");
        printf("\n");
        if (matris[i][0]!=0)
                printf("%d   |  %d   |",i,matris[i][0]);
            else
                printf("%d   |      |",i,matris[i][0]);   
        for(j=1;j<N;j++)
            if (matris[i][j]!=0)
                printf("  %d   |",matris[i][j]);
            else
                printf("      |",matris[i][j]);           
    }
    printf("\n    ");
 	for (k=0;k<N;k++)
        printf("-------");
}
void readFromFile(int matris[][MAX], char *fileName){//dosyadan matris okur
	int i,j, temp;
	FILE *data = fopen(fileName,"r");
	if(!data){
        printf("Dosya Acilamadi!");
		return;
    }
    while(!feof(data)){
        fscanf(data,"%d %d %d\n",&i,&j,&temp);  
		matris[i][j]=temp; 
    }     
  	fclose(data); 
   // Buraya kadar olan bolumde dosyadan okuma yapiliyor. Kodu degistirmeyiniz.
}
void koordinat_al(int *x1, int *x2, int *y1, int *y2){//hareket noktasýnýn ve hedef noktasinin koordinatlari alinir
	printf("\nhareket noktasi koordinatlarini giriniz.\nx: ");
	scanf(" %d", x1);
	printf("y: ");
	scanf(" %d", y1);
	printf("varmak istediginiz noktanin koordinatlarini giriniz.\nx:");
	scanf(" %d", x2);
	printf("y: ");
	scanf(" %d", y2);
}

void saga_git(int y1, int y2, int x1, int matris[][MAX], int temp, int N){//hedef noktasi hareket noktasinin saginda kaliyorsa saga gider
	int i,sayac=0;
	for(i=y1+1; i<y2; i++){
		if(matris[x1][i]!=0){
			sayac++;
		}							
	}		
	if(sayac==0){
		if(matris[x1][y2]==temp || matris[x1][y2]==0){
			for(i=y1+1; i<=y2; i++){
				matris[x1][i]=temp;
			}
			printf("\n");
			drawBoard(matris,N);
			printf("\n");
		}
		else{
			printf("\nBu hamle gerceklestirilemez.\n");
		}
		
	}
	else{
		printf("\nBu hamle gerceklestirilemez.\n");	
	}
}
void sola_git(int y1, int y2, int x1, int matris[][MAX], int temp, int N){//hedef noktasi hareket noktasinin solunda kaliyorsa sola gider
	int i,sayac=0;
	for(i=y1-1; i>y2; i--){
		if(matris[x1][i]!=0){
			sayac++;
		}							
	}		
	if(sayac==0){
		if(matris[x1][y2]==temp || matris[x1][y2]==0){
			for(i=y1-1; i>=y2; i--){
				matris[x1][i]=temp;
			}
			printf("\n");
			drawBoard(matris,N);
			printf("\n");	
		}
		else{
			printf("\nBu hamle gerceklestirilemez.\n");	
		}	
	}
	else{
		printf("\nBu hamle gerceklestirilemez.\n");	
	}
}
void asagi_git(int x1, int x2, int y1, int matris[][MAX], int temp, int N){//hedef noktasi hareket noktasinin asagisinda kaliyorsa asagi gider
	int i,sayac=0;
	for(i=x1+1; i<x2; i++){
		if(matris[i][y1]!=0){
			sayac++;
		}							
	}		
	if(sayac==0){
		if(matris[x2][y1]==temp || matris[x2][y1]==0){
			for(i=x1+1; i<=x2; i++){
				matris[i][y1]=temp;
			}
			printf("\n");
			drawBoard(matris,N);
			printf("\n");	
		}
		else{
			printf("\nBu hamle gerceklestirilemez.\n");	
		}	
	}
	else{
		printf("\nBu hamle gerceklestirilemez.\n");	
	}	
}
void yukari_git(int x1, int x2, int y1, int matris[][MAX], int temp, int N){//hedef noktasi hareket noktasinin yukarisinda kaliyorsa yukari gider
	int i,sayac=0;
	for(i=x1-1; i>x2; i--){
		if(matris[i][y1]!=0){
			sayac++;
		}							
	}		
	if(sayac==0){
		if(matris[x2][y1]==temp || matris[x2][y1]==0){
			for(i=x1-1; i>=x2; i--){
				matris[i][y1]=temp;
			}
			printf("\n");
			drawBoard(matris,N);
			printf("\n");	
		}
		else{
			printf("\nBu hamle gerceklestirilemez.\n");
		}			
	}
	else{
		printf("\nBu hamle gerceklestirilemez.\n");	
	}
}
void rastgele_matris_olustur(int N, int matris[][MAX]){//rastgele modda rastgele matris olusturur
	int i, j, k, l;
	matrisi_sifirla(N,matris);
	for(k=1; k<=N; k++){							
		l=0;
		while(l<2){
			i=rand() % N;
			j=rand() % N;
			if(matris[i][j]==0){
				matris[i][j]=k;
				l++;
			}
		}							
	}
	drawBoard(matris, N);
	printf("\n");	
}
void matris_tut(int k, int N, int matris[][MAX], int matris_tutan[][MAX][MAX]){//undo icin her bir adýmda olusan oyun tahtasini tutar
	int i, j;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			matris_tutan[k][i][j]=matris[i][j];
		}
	}
}
void geri_al(int k, int N, int matris[][MAX], int matris_tutan[][MAX][MAX]){//undo
	int i, j;	
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			matris[i][j]=matris_tutan[k][i][j];
		}
	}
}
int dolu_mu(int N, int matris[][MAX]){//oyun tahtasinin tüm hücreleri dolu mu kontrolü yapýlýr
	int i,j; 
	int dolu=0;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			if(matris[i][j]!=0){
				dolu++;
			}
		}
	}
	return dolu;
}
void koordinat_bul(int matris[][MAX], int N, int nokta[][4]){//oyun baslangicindaki oyun tahtasinda yer alan sayilarin koordinatlari bulunur ve nokta matrisine kaydedilir
	int i,j,k,l;
	for(k=1;k<=N;k++){
		l=0;
		for(i=0;i<N;i++){
			for(j=0;j<N;j++){				
				if(matris[i][j]==k){
					nokta[k-1][l]=i;
					nokta[k-1][l+1]=j;
					l+=2;
				}	
			}	
		}	
	}	
}
void path_guncelle(int path[][MAX][MAX2], int length, int count,int k){//yollari hesaplayan count_paths1 fonksiyonunda degismeyen yol koordinatlarýný da tutar
	int i;
	if(count>0){
		for(i=0; i<length; i+=2){
			if(path[k][count][i]==0 && path[k][count][i+1]==0){
				path[k][count][i]=path[k][count-1][i];
				path[k][count][i+1]=path[k][count-1][i+1];
			}
		}
		printf("\n");			
	}
}
int count_paths1(int i, int j, int i1, int j1, int n, int matris[][MAX], int path[][MAX][MAX2], int path_length_arr[][MAX2],int path_length,int *count, int k){//her bir sayýnýn olusturabilecegi yollari hesaplar
	int deger2;
	if(i==i1 && j==j1){
		path[k][*count][path_length++]=i;
		path[k][*count][path_length++]=j;
		deger2=(*count);
		path_length_arr[k][*count]=path_length;	
		path_guncelle(path, path_length, deger2, k);	
		(*count)++;
		return 1;
	}
	if(i>=n || j>=n){
		return 0;
	}
	if(i<0 || j<0){
		return 0;
	}
	if(matris[i][j]!=0 && matris[i][j]!=matris[i1][j1]){
		return 0;
	}
	if(matris[i][j] == k+1 || matris[i][j] == 0){
		matris[i][j] = k+2;
		path[k][*count][path_length++]=i;
		path[k][*count][path_length++]=j;		
		count_paths1(i,j+1,i1,j1,n,matris,path,path_length_arr,path_length,count,k);
		count_paths1(i+1,j,i1,j1,n,matris,path,path_length_arr,path_length,count,k);
		count_paths1(i,j-1,i1,j1,n,matris,path,path_length_arr,path_length,count,k);
		count_paths1(i-1,j,i1,j1,n,matris,path,path_length_arr,path_length,count,k);
		matris[i][j] = 0;	
	}	
}
void kombinasyonHesapla(int ihtimal[][MAX], int count_dizi[], int satir, int carpim, int secilenler[5000][MAX], int secilenSayisi, int N,int *count ){//her sayý icin bulunan yollarýn farklý kombinasyonu hesaplanir
	int i,j;
    if (satir == N) {    	
        (*count)++;
        printf("\n");
        return;
    }

    for (j = 0; j < count_dizi[satir]; j++) {
        secilenler[*count][secilenSayisi] = ihtimal[satir][j];
        kombinasyonHesapla(ihtimal, count_dizi, satir + 1, carpim, secilenler, secilenSayisi + 1,N,count);
    }
}
void matris_yedekle(int N, int matris[][MAX], int temp_matris[][MAX]){;//oluþturulan matris tekrar kullanýlmak istenirse bu fonksiyonla yedeklenir
	int i,j;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			temp_matris[i][j]=matris[i][j];
		}
	}
}
