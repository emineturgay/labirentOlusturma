#include <iostream>
#include <allegro.h>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctime>

using namespace std;

const double gamma = 0.8;
int siradaki_durum,yeni_durum;
  int n;
  int e,r;

        int *R;
        float Q[200][200];

int rastgele_yer(int n);
int max_degeri_bul(int durum, int a);
int grafik(int hn,int bn);

int main(){

    FILE *dosya;
    FILE * dosya2;
    FILE * dosya3;
    FILE * dosya4;
    char cumle[200];
    int j=0;
    int hn,bn,iterasyon;
     if ((dosya = fopen("input.txt", "r")) == NULL)
    {
        printf("dosya acilamadi!\n");
        exit(1);
    }

    while(fgets(cumle,200,dosya) != NULL)
    {
        n++;
    }


   cout<<"BASLANGIC NOKTASI GIRINIZ : "<<endl;

			do
			{
				cin>> bn;
				if(bn>n-1)
				{
					cout<<"hatali giris tekrar deneyin : "<<endl;
				}

			}while(bn>n-1);

			cout<<"HEDEF NOKTASI GIRINIZ : "<<endl;
			do
			{
				cin>>hn;
				if(hn>n-1)
				{
					cout<<"hatali giris tekrar deneyin : "<<endl;
				}

			}while(hn>n-1);

			cout<<"Iterasyon sayisi girin: "<<endl;
            cin>>iterasyon;

    R=(int*)malloc(n*n*sizeof(int));
    if (R == NULL)
    {
        printf("HATA: bellek ayrilamadi\n");
        exit(1); // programi sonlandir
    }
    int e,r;
     for(e=0; e<n; e++){
        for(r=0; r<n;r++){
            R[e*n+r]= -1;
        }
     }
     fseek(dosya,0,SEEK_SET);

    int satir_sayisi = 0;
    while ( fgets(cumle, 200, dosya) != NULL ) {  // R matrisi olusuyor

           char *kelime =strtok(cumle,", ");
            while (kelime != NULL) {

                    j=atoi(kelime);
                    kelime = strtok(NULL, ", ");
            if(j==hn){
                R[satir_sayisi*n+j]=100;
                R[hn*n+hn]=100;
            }
            else {
                R[satir_sayisi*n+j]=0;
            }
            }
            satir_sayisi++;
    }

   if ((dosya2 = fopen("outR.txt", "w")) == NULL) {
        printf("dosya acilamadi!\n"); exit(1);
   }

  int i,z;
    for(i=0;i<n;i++){
        for(z=0;z<n;z++){
            fprintf(dosya2,"%-5d ",R[i*n+z]);      // R matrisi yazliyior
        }
        fprintf(dosya2,"%c",'\n');
    }


 for(int i = 0; i <n; i++){
        for(int j = 0; j <n; j++){
            Q[i][j] = 0;
		}
	}

      int baslangic_durumu=bn;

    for(int j = 0; j <= iterasyon ; j++){

           siradaki_durum = baslangic_durumu;

	 for(int i = 0; i < n; i++){
       int sonraki_hareket;

    sonraki_hareket = rastgele_yer(n);

	if(R[siradaki_durum*n+sonraki_hareket] >= 0){
        Q[siradaki_durum][sonraki_hareket] = (R[siradaki_durum*n+sonraki_hareket] + (gamma * max_degeri_bul(sonraki_hareket, 2)));
        siradaki_durum = sonraki_hareket;
	}
	}
	}
	if ((dosya3 = fopen("outQ.txt", "w")) == NULL) {
        printf("dosya acilamadi!\n"); exit(1);
   }

    for(int i = 0; i < n; i++){
        for(int j = 0; j <n; j++){
            fprintf(dosya3,"%.1f  ",Q[i][j]);
			if(j < n){
				fprintf(dosya3,"%c",',');
			}
		}
        fprintf(dosya3,"%c",'\n');
	}
    cout << "\n";

    if ((dosya4 = fopen("outPath.txt", "w")) == NULL) {
        printf("dosya acilamadi!\n"); exit(1);
   }

        siradaki_durum = baslangic_durumu;
        yeni_durum = 0;
        fprintf(dosya4,"%d,",siradaki_durum);

		do {
            yeni_durum = max_degeri_bul(siradaki_durum,1);
            fprintf(dosya4,"%d",yeni_durum);
            fprintf(dosya4,"%c",',');
            siradaki_durum = yeni_durum;
        }while(siradaki_durum != hn);

grafik(hn,bn);

	 free(R);
	 fclose(dosya4);
	 fclose(dosya3);
	 fclose(dosya2);
	 fclose(dosya);

	return 0;
}
END_OF_MAIN();


int rastgele_yer(int n){

	int aksiyon;
   int  deger_sec =0;

   do {

     int bolen= RAND_MAX/1;  // 1-rand_max aralýgýnda
     aksiyon = (n*rand()/bolen);

		if(R[siradaki_durum*n+aksiyon] > -1){
    deger_sec =1;  // aksýyonu dondur
		}
     }while(deger_sec==0);

    return aksiyon;
}

int max_degeri_bul(int durum, int a){

	int kazanan=0,yeni_kazanan;
	do {
        yeni_kazanan = 1;
        for(int i = 0; i < n; i++){
				if(Q[durum][i] >= Q[durum][kazanan]){
                    kazanan = i;
                    yeni_kazanan = 0;
				}
		}
}while(yeni_kazanan==1);

	if(a==1)
		return kazanan;  // yol icin
	else if(a==2)
		return Q[durum][kazanan];  //kazanc hesaplamak icin
}

int grafik(int hn,int bn)
{

allegro_init();
install_keyboard();
set_color_depth(32);
set_gfx_mode( GFX_AUTODETECT_WINDOWED, 800, 700, 0, 0);

acquire_screen();
clear_to_color(screen,makecol( 255,255,255));

if(n==4){
 int x=100;
   int y=100;

   while(x<=500){
  rect(screen,x,500,500,100,makecol(255,64,64));

  x+=200;
   }
  while(y<=500){
  rect(screen,100,y,500,100,makecol(255,64,64));
  y+=200;
   }

     for(e=0; e<n; e++){
        for(r=0; r<n;r++){

                if(R[e*n+r]==0){
                 if((e==1 || e==0 ) && (r==0 || r==1 )){ line(screen,300,100,300,300,makecol(255,255,255)); }
                 else if((e==0 || e==2 ) && (r==0 || r==2 )){ line(screen,100,300,300,300,makecol(255,255,255)); }
                 else if ((e==2 || e==3 ) && (r==2 || r==3 )) { line(screen,300,300,300,500,makecol(255,255,255));}
                 else if ((e==1 || e==3 ) && (r==1 || r==3 )){ line(screen,300,300,500,300,makecol(255,255,255));}
           }}}

 int bb,hh;
        bb=bn;
        hh=hn;

             for(int i=0; i<2;i++){
           if(bb==0 ) { line(screen,100,100,300,100,makecol(255,255,255)); line(screen,200,100,200,200,makecol(0,0,0));}
           else if(bb==1) { line(screen,300,100,500,100,makecol(255,255,255)); line(screen,400,100,400,200,makecol(0,0,0));}
           else if(bb==2) { line(screen,100,500,300,500,makecol(255,255,255)); line(screen,200,200,200,500,makecol(0,0,0));}
          else if(bb==3) { line(screen,300,500,500,500,makecol(255,255,255)); line(screen,400,400,400,500,makecol(0,0,0)); }
               bb=hh;
             }

        siradaki_durum = bn;
        yeni_durum = 0;

		do {
            yeni_durum = max_degeri_bul(siradaki_durum,1);
             if((siradaki_durum==1 || siradaki_durum==0 ) && (yeni_durum==0 ||yeni_durum==1 )){ line(screen,200,200,400,200,makecol(0,0,0)); }
                 else if((siradaki_durum==0 || siradaki_durum==2 ) && (yeni_durum==0 || yeni_durum==2 )){ line(screen,200,200,200,400,makecol(0,0,0)); }
                 else if ((siradaki_durum==2 || siradaki_durum==3 ) && (yeni_durum==2 || yeni_durum==3 )) { line(screen,200,400,400,400,makecol(0,0,0));}
                 else if ((siradaki_durum==1 || siradaki_durum==3 ) && (yeni_durum==1 || yeni_durum==3 )){ line(screen,400,200,400,400,makecol(0,0,0));}



            siradaki_durum = yeni_durum;
        } while(siradaki_durum != hn);


             }

    else if(n==9){
   int x=100;
   int y=100;

   while(x<=550){
 rect(screen,x,550,550,100,makecol(255,64,64));   //n=9 ise  450 mesafe
  x+=150;
   }
  while(y<=550){
    rect(screen,100,y,550,100,makecol(255,64,64));
  y+=150;
  }

    for(e=0; e<n; e++){
        for(r=0; r<n; r++){

    if(R[e*n+r]==0){

    if((e==1 || e==0 ) && (r==0 || r==1 )){ line(screen,250,100,250,250,makecol(255,255,255));}
    else if((e==1 || e==2 ) && (r==1 || r==2 )){ line(screen,400,100,400,250,makecol(255,255,255));}
    else if ((e==0 || e==3 ) && (r==0 || r==3 )){ line(screen,100,250,250,250,makecol(255,255,255));}
    else if ((e==1 || e==4 ) && (r==1 || r==4 )){ line(screen,250,250,400,250,makecol(255,255,255));}
    else if ((e==2 || e==5 ) && (r==2 || r==5 )){ line(screen,400,250,550,250,makecol(255,255,255));}
    else if ((e==3 || e==4 ) && (r==3 || r==4 )){ line(screen,250,250,250,400,makecol(255,255,255));}
    else if ((e==5 || e==4 ) && (r==5 || r==4 )){ line(screen,400,250,400,400,makecol(255,255,255));}
    else if ((e==3 || e==6 ) && (r==3 || r==6 )){ line(screen,100,400,250,400,makecol(255,255,255));}
    else if ((e==7 || e==6 ) && (r==7 || r==6 )){ line(screen,250,400,250,550,makecol(255,255,255));}
    else if ((e==7 || e==4 ) && (r==7 || r==4 )){ line(screen,250,400,400,400,makecol(255,255,255));}
    else if ((e==5 || e==8 ) && (r==5 || r==8 )){ line(screen,400,400,550,400,makecol(255,255,255));}
   else if ((e==7 || e==8 ) && (r==7 || r==8 )){ line(screen,400,400,400,550,makecol(255,255,255));}
    }}}

      int bb,hh;
        bb=bn;
        hh=hn;

    for(int i=0; i<2;i++){

    if(bb==0){ line(screen,100,100,250,100,makecol(255,255,255)); line(screen,175,100,175,325,makecol(0,0,0));}
    else if(bb==1) { line(screen,250,100,400,100,makecol(255,255,255));  line(screen,325,100,325,175,makecol(0,0,0));  }
    else if(bb==2) { line(screen,400,100,550,100,makecol(255,255,255)); line(screen,475,100,475,175,makecol(0,0,0)); }
    else if(bb==3) { line(screen,100,250,100,400,makecol(255,255,255)); line(screen,100,325,175,325,makecol(0,0,0));  }
    else if(bb==5) { line(screen,550,250,550,400,makecol(255,255,255)); line(screen,550,325,475,325,makecol(0,0,0));  }
    else if(bb==6) { line(screen,100,550,250,550,makecol(255,255,255)); line(screen,175,550,175,475,makecol(0,0,0));  }
    else if(bb==7) { line(screen,250,550,400,550,makecol(255,255,255)); line(screen,325,550,325,475,makecol(0,0,0));  line(screen,175,475,325,475,makecol(0,0,0));  }
    else if(bb==8) { line(screen,400,550,550,550,makecol(255,255,255)); line(screen,475,175,475,550,makecol(0,0,0)); }
              bb=hh;
          }

          siradaki_durum = bn;
        yeni_durum = 0;

		do {
            yeni_durum = max_degeri_bul(siradaki_durum,1);
               if((siradaki_durum==1 || siradaki_durum==0 ) && (yeni_durum==0 || yeni_durum==1 )){  line(screen,175,175,325,175,makecol(0,0,0));}
    else if((siradaki_durum==1 || siradaki_durum==2 ) && (yeni_durum==1 || yeni_durum==2 )){ line(screen,325,175,475,175,makecol(0,0,0));}
    else if ((siradaki_durum==0 || siradaki_durum==3 ) && (yeni_durum==0 || yeni_durum==3 )){ line(screen,175,175,175,325,makecol(0,0,0));}
    else if ((siradaki_durum==1 || siradaki_durum==4 ) && (yeni_durum==1 || yeni_durum==4 )){ line(screen,325,175,325,325,makecol(0,0,0));}
    else if ((siradaki_durum==2 || siradaki_durum==5 ) && (yeni_durum==2 || yeni_durum==5 )){ line(screen,475,175,475,325,makecol(0,0,0));}
    else if ((siradaki_durum==3 || siradaki_durum==4 ) && (yeni_durum==3 || yeni_durum==4 )){ line(screen,175,325,325,325,makecol(0,0,0));}
    else if ((siradaki_durum==5 || siradaki_durum==4 ) && (yeni_durum==5 || yeni_durum==4 )){ line(screen,325,325,475,325,makecol(0,0,0));}
    else if ((siradaki_durum==3 || siradaki_durum==6 ) && (yeni_durum==3 || yeni_durum==6 )){ line(screen,175,325,175,475,makecol(0,0,0));}
    else if ((siradaki_durum==7 || siradaki_durum==6 ) && (yeni_durum==7 || yeni_durum==6 )){ line(screen,175,475,325,475,makecol(0,0,0));}
    else if ((siradaki_durum==7 || siradaki_durum==4 ) && (yeni_durum==7 || yeni_durum==4 )){ line(screen,325,325,325,475,makecol(0,0,0));}
    else if ((siradaki_durum==5 || siradaki_durum==8 ) && (yeni_durum==5 || yeni_durum==8 )){ line(screen,475,325,475,475,makecol(0,0,0));}
   else if ((siradaki_durum==7 || siradaki_durum==8 ) && (yeni_durum==7 || yeni_durum==8 )){ line(screen,325,475,475,475,makecol(0,0,0));}
            siradaki_durum = yeni_durum;
        } while(siradaki_durum != hn);


          }
    else if(n==16) {

    int x=100;
    int y=100;
    while(x<=580){
   rect(screen,x,580,580,100,makecol(255,64,64));   //n=16 ise  480 mesafe
   x+=120;
    }
    while(y<=580){
          rect(screen,100,y,580,100,makecol(255,64,64));
          y+=120;
    }

    for(e=0; e<n; e++){
        for(r=0; r<n; r++){

                if(R[e*n+r]==0){

                 if((e==1 || e==0 ) && (r==0 || r==1 )){  line(screen,220,100,220,220,makecol(255,255,255));}
                 else if((e==1 || e==2 ) && (r==1 || r==2 )){  line(screen,340,100,340,220,makecol(255,255,255));}
                else if ((e==2 || e==3 ) && (r==2 || r==3 )){  line(screen,460,100,460,220,makecol(255,255,255));}
                else if ((e==0 || e==4 ) && (r==0 || r==4 )){  line(screen,100,220,220,220,makecol(255,255,255));}
                 else if ((e==1 || e==5 ) && (r==1 || r==5 )){  line(screen,220,220,340,220,makecol(255,255,255));}
                else if ((e==2 || e==6 ) && (r==2 || r==6 )){  line(screen,340,220,460,220,makecol(255,255,255));}
                 else if ((e==3 || e==7 ) && (r==3 || r==7 )){  line(screen,460,220,580,220,makecol(255,255,255));}
                 else if ((e==4 || e==5 ) && (r==4 || r==5 )){  line(screen,220,220,220,340,makecol(255,255,255));}
                else if ((e==5 || e==6 ) && (r==5 || r==6 )){  line(screen,340,220,340,340,makecol(255,255,255));}
                 else if ((e==7 || e==6 ) && (r==7 || r==6 )){ line(screen,460,220,460,340,makecol(255,255,255));}
                 else if ((e==4 || e==8 ) && (r==4 || r==8 )){  line(screen,100,340,220,340,makecol(255,255,255));}
                else if ((e==5 || e==9 ) && (r==5 || r==9 )){  line(screen,220,340,340,340,makecol(255,255,255));}
                 else if ((e==6 || e==10 ) && (r==6 || r==10 )){  line(screen,340,340,460,340,makecol(255,255,255));}
                else if ((e==7 || e==11 ) && (r==7 || r==11 )){ line(screen,460,340,580,340,makecol(255,255,255));}
                else if ((e==8 || e==9 ) && (r==8 || r==9 )){ line(screen,220,340,220,460,makecol(255,255,255));}
                else if ((e==10 || e==9 ) && (r==10 || r==9 )){ line(screen,340,340,340,460,makecol(255,255,255));}
                else if ((e==10 || e==11 ) && (r==10 || r==11 )){  line(screen,460,340,460,460,makecol(255,255,255));}
                else if ((e==8 || e==12 ) && (r==8 || r==12 )){ line(screen,100,460,220,460,makecol(255,255,255));}
                else if ((e==13 || e==9 ) && (r==13 || r==9 )){ line(screen,220,460,340,460,makecol(255,255,255));}
                else if ((e==14 || e==10 ) && (r==14 || r==10 )){ line(screen,340,460,460,460,makecol(255,255,255));}
                else if ((e==11 || e==15 ) && (r==11 || r==15 )){ line(screen,460,460,580,460,makecol(255,255,255));}
                else if ((e==13 || e==12 ) && (r==12 || r==13 )){ line(screen,220,460,220,580,makecol(255,255,255));}
                else if ((e==13 || e==14 ) && (r==13 || r==14 )){ line(screen,340,460,340,580,makecol(255,255,255));}
                 else if ((e==14 || e==15 ) && (r==14 || r==15 )){ line(screen,460,460,460,580,makecol(255,255,255));}
           }}}
        int bb,hh;
        bb=bn;
        hh=hn;

          for(int i=0; i<2;i++){

            if(bb==0)  line(screen,100,100,220,100,makecol(255,255,255));
           else if(bb==1) line(screen,220,100,340,100,makecol(255,255,255));
           else if(bb==2) line(screen,340,100,460,100,makecol(255,255,255));
          else if(bb==3) line(screen,460,100,580,100,makecol(255,255,255));
          else if(bb==4) line(screen,100,220,100,340,makecol(255,255,255));
          else if(bb==8) line(screen,100,340,100,460,makecol(255,255,255));
          else if(bb==12) line(screen,100,580,220,580,makecol(255,255,255));
          else if(bb==13) line(screen,220,580,340,580,makecol(255,255,255));
          else if(bb==14) line(screen,340,580,460,580,makecol(255,255,255));
          else if(bb==15) line(screen,460,580,580,580,makecol(255,255,255));
          else if(bb==7) line(screen,580,220,580,340,makecol(255,255,255));
          else if(bb==11) line(screen,580,340,580,460,makecol(255,255,255));
               bb=hh;
          }
           siradaki_durum = bn;
        yeni_durum = 0;

		do {
            yeni_durum = max_degeri_bul(siradaki_durum,1);
                               if((siradaki_durum==1 || siradaki_durum==0 ) && (yeni_durum==0 || yeni_durum==1 )){  line(screen,160,160,280,160,makecol(0,0,0));}
                 else if((siradaki_durum==1 || siradaki_durum==2 ) && (yeni_durum==1 || yeni_durum==2 )){  line(screen,280,160,400,160,makecol(0,0,0));}
                else if ((siradaki_durum==2 || siradaki_durum==3 ) && (yeni_durum==2 || yeni_durum==3 )){  line(screen,400,160,520,160,makecol(0,0,0));}
                else if ((siradaki_durum==0 || siradaki_durum==4 ) && (yeni_durum==0 || yeni_durum==4 )){  line(screen,160,160,160,280,makecol(0,0,0));}
                 else if ((siradaki_durum==1 || siradaki_durum==5 ) && (yeni_durum==1 || yeni_durum==5 )){  line(screen,280,160,280,280,makecol(0,0,0));}
                else if ((siradaki_durum==2 || siradaki_durum==6 ) && (yeni_durum==2 || yeni_durum==6 )){  line(screen,400,160,400,280,makecol(0,0,0));}
                 else if ((siradaki_durum==3 || siradaki_durum==7 ) && (yeni_durum==3 || yeni_durum==7 )){  line(screen,520,160,520,280,makecol(0,0,0));}
                 else if ((siradaki_durum==4 || siradaki_durum==5 ) && (yeni_durum==4 || yeni_durum==5 )){  line(screen,160,280,280,280,makecol(0,0,0));}
                else if ((siradaki_durum==5 || siradaki_durum==6 ) && (yeni_durum==5 || yeni_durum==6 )){  line(screen,280,280,400,280,makecol(0,0,0));}
                 else if ((siradaki_durum==7 || siradaki_durum==6 ) && (yeni_durum==7 || yeni_durum==6 )){ line(screen,400,280,520,280,makecol(0,0,0));}
                 else if ((siradaki_durum==4 || siradaki_durum==8 ) && (yeni_durum==4 || yeni_durum==8 )){  line(screen,160,280,160,400,makecol(0,0,0));}
                else if ((siradaki_durum==5 || siradaki_durum==9 ) && (yeni_durum==5 || yeni_durum==9 )){  line(screen,280,280,280,520,makecol(0,0,0));}
                 else if ((siradaki_durum==6 || siradaki_durum==10 ) && (yeni_durum==6 || yeni_durum==10 )){  line(screen,400,280,400,400,makecol(0,0,0));}
                else if ((siradaki_durum==7 || siradaki_durum==11 ) && (yeni_durum==7 || yeni_durum==11 )){ line(screen,520,280,520,400,makecol(0,0,0));}
                else if ((siradaki_durum==8 || siradaki_durum==9 ) && (yeni_durum==8 || yeni_durum==9 )){ line(screen,160,400,280,400,makecol(0,0,0));}
                else if ((siradaki_durum==10 || siradaki_durum==9 ) && (yeni_durum==10 || yeni_durum==9 )){ line(screen,280,400,400,400,makecol(0,0,0));}
                else if ((siradaki_durum==10 || siradaki_durum==11 ) && (yeni_durum==10 || yeni_durum==11 )){  line(screen,400,400,520,400,makecol(0,0,0));}
                else if ((siradaki_durum==8 || siradaki_durum==12 ) && (yeni_durum==8 || yeni_durum==12 )){ line(screen,160,400,160,520,makecol(0,0,0));}
                else if ((siradaki_durum==13 || siradaki_durum==9 ) && (yeni_durum==13 || yeni_durum==9 )){ line(screen,280,400,280,520,makecol(0,0,0));}
                else if ((siradaki_durum==14 || siradaki_durum==10 ) && (yeni_durum==14 || yeni_durum==10 )){ line(screen,400,400,400,520,makecol(0,0,0));}
                else if ((siradaki_durum==11 || siradaki_durum==15 ) && (yeni_durum==11 || yeni_durum==15 )){ line(screen,520,400,520,520,makecol(0,0,0));}
                else if ((siradaki_durum==13 || siradaki_durum==12 ) && (yeni_durum==12 || yeni_durum==13 )){ line(screen,160,520,280,520,makecol(0,0,0));}
                else if ((siradaki_durum==13 || siradaki_durum==14 ) && (yeni_durum==13 || yeni_durum==14 )){ line(screen,280,520,400,520,makecol(0,0,0));}
                 else if ((siradaki_durum==14 || siradaki_durum==15 ) && (yeni_durum==14 || yeni_durum==15 )){ line(screen,400,520,520,520,makecol(0,0,0));}
            siradaki_durum = yeni_durum;
        } while(siradaki_durum != hn);
            }

    else if (n==25){

     int x=70;
     int y=70;
     while(x<=570){
    rect(screen,x,570,570,70,makecol(255,64,64));   //n=25 ise  500 mesafe
      x+=100;
     }
     while(y<=570){
           rect(screen,70,y,570,70,makecol(255,64,64));
           y+=100;
     }

    for(e=0; e<n; e++){
        for(r=0; r<n; r++){

                if(R[e*n+r]==0){

                 if((e==1 || e==0 ) && (r==0 || r==1 )){  line(screen,170,70,170,170,makecol(255,255,255));}
                 else if((e==1 || e==2 ) && (r==1 || r==2 )){  line(screen,270,70,270,170,makecol(255,255,255));}
                else if ((e==2 || e==3 ) && (r==2 || r==3 )){  line(screen,370,70,370,170,makecol(255,255,255));}
                else if ((e==3 || e==4 ) && (r==3 || r==4 )){  line(screen,470,70,470,170,makecol(255,255,255));}
                 else if ((e==0 || e==5 ) && (r==0 || r==5 )){  line(screen,70,170,170,170,makecol(255,255,255));}
                else if ((e==1 || e==6 ) && (r==1 || r==6 )){  line(screen,170,170,270,170,makecol(255,255,255));}
                 else if ((e==2 || e==7 ) && (r==2 || r==7 )){  line(screen,270,170,370,170,makecol(255,255,255));}
                 else if ((e==3 || e==8 ) && (r==3 || r==8 )){  line(screen,370,170,470,170,makecol(255,255,255));}
                  else if ((e==4 || e==9 ) && (r==4 || r==9 )){ line(screen,470,170,570,170,makecol(255,255,255));}
                else if ((e==5 || e==6 ) && (r==5 || r==6 )){  line(screen,170,170,170,270,makecol(255,255,255));}
                 else if ((e==7 || e==6 ) && (r==7 || r==6 )){ line(screen,270,170,270,270,makecol(255,255,255));}
                 else if ((e==7 || e==8 ) && (r==7 || r==8 )){  line(screen,370,170,370,270,makecol(255,255,255));}
                else if ((e==8 || e==9 ) && (r==8 || r==9 )){  line(screen,470,170,470,270,makecol(255,255,255));}
                 else if ((e==5 || e==10 ) && (r==5 || r==10 )){  line(screen,70,270,170,270,makecol(255,255,255));}
                else if ((e==6 || e==11 ) && (r==6 || r==11 )){ line(screen,170,370,270,270,makecol(255,255,255));}
                else if ((e==7 || e==12 ) && (r==7 || r==12 )){ line(screen,270,270,370,270,makecol(255,255,255));}
                else if ((e==8 || e==13 ) && (r==8 || r==13 )){ line(screen,370,270,470,270,makecol(255,255,255));}
                else if ((e==9 || e==14 ) && (r==9 || r==14 )){  line(screen,470,270,570,270,makecol(255,255,255));}
                else if ((e==10 || e==11 ) && (r==10 || r==11 )){ line(screen,170,270,170,370,makecol(255,255,255));}
                else if ((e==11 || e==12 ) && (r==11 || r==12)){ line(screen,270,270,270,370,makecol(255,255,255));}
                else if ((e==12 || e==13 ) && (r==12 || r==13 )){ line(screen,370,270,370,370,makecol(255,255,255));}
                else if ((e==13 || e==14 ) && (r==13 || r==14 )){ line(screen,470,270,470,370,makecol(255,255,255));}
                else if ((e==10 || e==15 ) && (r==10 || r==15 )){ line(screen,70,370,170,370,makecol(255,255,255));}
                else if ((e==11 || e==16 ) && (r==11|| r==16 )){ line(screen,170,370,270,370,makecol(255,255,255));}
                 else if ((e==12 || e==17 ) && (r==12 || r==17 )){ line(screen,270,370,370,370,makecol(255,255,255));}
                else if ((e==13 || e==18 ) && (r==13 || r==18 )){ line(screen,370,370,470,370,makecol(255,255,255));}
               else if ((e==14 || e==19 ) && (r==14 || r==19 )){ line(screen,470,370,570,370,makecol(255,255,255));}
                else if ((e==15 || e==16 ) && (r==15 || r==16 )){ line(screen,170,370,170,470,makecol(255,255,255));}
                else if ((e==16 || e==17 ) && (r==16 || r==17 )){ line(screen,270,370,270,470,makecol(255,255,255));}
             else if ((e==17 || e==18 ) && (r==17 || r==18 )){ line(screen,370,370,370,470,makecol(255,255,255));}
             else if ((e==18 || e==19 ) && (r==18 || r==19 )){ line(screen,470,370,470,470,makecol(255,255,255));}
             else if ((e==15 || e==20 ) && (r==15 || r==20 )){ line(screen,70,470,170,470,makecol(255,255,255));}
             else if ((e==16 || e==21 ) && (r==16 || r==21 )){ line(screen,170,470,270,470,makecol(255,255,255));}
             else if ((e==17 || e==22 ) && (r==17 || r==22 )){ line(screen,270,470,370,470,makecol(255,255,255));}
             else if ((e==18 || e==23 ) && (r==18 || r==23 )){ line(screen,370,470,470,470,makecol(255,255,255));}
             else if ((e==19 || e==24 ) && (r==19 || r==24 )){ line(screen,470,470,570,470,makecol(255,255,255));}
              else if ((e==20 || e==21 ) && (r==20 || r==21 )){ line(screen,170,470,170,570,makecol(255,255,255));}
            else if ((e==21 || e==22 ) && (r==21 || r==22 )){ line(screen,270,470,270,570,makecol(255,255,255));}
            else if ((e==22 || e==23 ) && (r==22 || r==23 )){ line(screen,370,470,370,570,makecol(255,255,255));}
            else if ((e==23 || e==24 ) && (r==23 || r==24 )){ line(screen,470,470,470,570,makecol(255,255,255));}

           }}}

          int bb,hh;
        bb=bn;
        hh=hn;
          for(int i=0; i<2;i++){

             if(bb==0) { line(screen,70,70,170,70,makecol(255,255,255));}
           else if(bb==1){ line(screen,170,70,270,70,makecol(255,255,255));}
           else if(bb==2){ line(screen,270,70,370,70,makecol(255,255,255));}
          else if(bb==3){ line(screen,370,70,470,70,makecol(255,255,255));}
          else if(bb==4) {line(screen,470,70,570,70,makecol(255,255,255));}
          else if(bb==9) {line(screen,570,170,570,270,makecol(255,255,255));}
          else if(bb==14) {line(screen,570,270,570,370,makecol(255,255,255));}
          else if(bb==19) {line(screen,570,370,570,470,makecol(255,255,255));}
          else if(bb==24) {line(screen,470,570,570,570,makecol(255,255,255));}
          else if(bb==23) {line(screen,370,570,470,570,makecol(255,255,255));}
          else if(bb==22) {line(screen,270,570,370,570,makecol(255,255,255));}
          else if(bb==21) {line(screen,170,570,270,570,makecol(255,255,255));}
          else if(bb==20) {line(screen,70,570,170,570,makecol(255,255,255));}
          else if(bb==15) {line(screen,70,370,70,470,makecol(255,255,255));}
          else if(bb==10) {line(screen,70,270,70,370,makecol(255,255,255));}
          else if(bb==5) {line(screen,70,170,70,270,makecol(255,255,255));}

               bb=hh;
          }


           siradaki_durum = bn;
        yeni_durum = 0;

		do {
            yeni_durum = max_degeri_bul(siradaki_durum,1);
    if((siradaki_durum==1 || siradaki_durum==0 ) && (yeni_durum==0 || yeni_durum==1 )){  line(screen,120,120,220,120,makecol(0,0,0));}
    else if((siradaki_durum==1 || siradaki_durum==2 ) && (yeni_durum==1 || yeni_durum==2 )){  line(screen,220,120,320,120,makecol(0,0,0));}
    else if ((siradaki_durum==2 || siradaki_durum==3 ) && (yeni_durum==2 || yeni_durum==3 )){  line(screen,320,120,420,120,makecol(0,0,0));}
    else if ((siradaki_durum==3 || siradaki_durum==4 ) && (yeni_durum==3 || yeni_durum==4 )){  line(screen,420,120,520,120,makecol(0,0,0));}
    else if ((siradaki_durum==0 || siradaki_durum==5 ) && (yeni_durum==0 || yeni_durum==5 )){  line(screen,120,120,120,220,makecol(0,0,0));}
    else if ((siradaki_durum==1 || siradaki_durum==6 ) && (yeni_durum==1 || yeni_durum==6 )){  line(screen,220,120,220,220,makecol(0,0,0));}
    else if ((siradaki_durum==2 || siradaki_durum==7 ) && (yeni_durum==2 || yeni_durum==7 )){  line(screen,320,120,320,220,makecol(0,0,0));}
    else if ((siradaki_durum==3 || siradaki_durum==8 ) && (yeni_durum==3 || yeni_durum==8 )){  line(screen,420,120,420,220,makecol(0,0,0));}
    else if ((siradaki_durum==4 || siradaki_durum==9 ) && (yeni_durum==4 || yeni_durum==9 )){ line(screen,520,120,520,220,makecol(0,0,0));}
    else if ((siradaki_durum==5 || siradaki_durum==6 ) && (yeni_durum==5 || yeni_durum==6 )){  line(screen,120,220,220,220,makecol(0,0,0));}
    else if ((siradaki_durum==7 || siradaki_durum==6 ) && (yeni_durum==7 || yeni_durum==6 )){ line(screen,220,220,320,220,makecol(0,0,0));}
    else if ((siradaki_durum==7 || siradaki_durum==8 ) && (yeni_durum==7 || yeni_durum==8 )){  line(screen,320,220,420,220,makecol(0,0,0));}
    else if ((siradaki_durum==8 || siradaki_durum==9 ) && (yeni_durum==8 || yeni_durum==9 )){  line(screen,420,220,520,220,makecol(0,0,0));}
    else if ((siradaki_durum==5 || siradaki_durum==10 ) && (yeni_durum==5 || yeni_durum==10 )){  line(screen,120,220,120,320,makecol(0,0,0));}
    else if ((siradaki_durum==6 || siradaki_durum==11 ) && (yeni_durum==6 || yeni_durum==11 )){ line(screen,220,220,220,320,makecol(0,0,0));}
    else if ((siradaki_durum==7 || siradaki_durum==12 ) && (yeni_durum==7 || yeni_durum==12 )){ line(screen,320,220,320,320,makecol(0,0,0));}
    else if ((siradaki_durum==8 || siradaki_durum==13 ) && (yeni_durum==8 || yeni_durum==13 )){ line(screen,420,220,420,320,makecol(0,0,0));}
    else if ((siradaki_durum==9 || siradaki_durum==14 ) && (yeni_durum==9 || yeni_durum==14 )){  line(screen,520,220,520,320,makecol(0,0,0));}
    else if ((siradaki_durum==10 || siradaki_durum==11 ) && (yeni_durum==10 || yeni_durum==11 )){ line(screen,120,320,220,320,makecol(0,0,0));}
    else if ((siradaki_durum==11 || siradaki_durum==12 ) && (yeni_durum==11 || yeni_durum==12)){ line(screen,220,320,320,320,makecol(0,0,0));}
    else if ((siradaki_durum==12 || siradaki_durum==13 ) && (yeni_durum==12 || yeni_durum==13 )){ line(screen,320,320,420,320,makecol(0,0,0));}
    else if ((siradaki_durum==13 || siradaki_durum==14 ) && (yeni_durum==13 || yeni_durum==14 )){ line(screen,420,320,520,320,makecol(0,0,0));}
    else if ((siradaki_durum==10 || siradaki_durum==15 ) && (yeni_durum==10 || yeni_durum==15 )){ line(screen,120,320,120,420,makecol(0,0,0));}
    else if ((siradaki_durum==11 || siradaki_durum==16 ) && (yeni_durum==11|| yeni_durum==16 )){ line(screen,220,320,220,420,makecol(0,0,0));}
    else if ((siradaki_durum==12 || siradaki_durum==17 ) && (yeni_durum==12 || yeni_durum==17 )){ line(screen,320,320,320,420,makecol(0,0,0));}
    else if ((siradaki_durum==13 || siradaki_durum==18 ) && (yeni_durum==13 || yeni_durum==18 )){ line(screen,420,320,420,420,makecol(0,0,0));}
    else if ((siradaki_durum==14 || siradaki_durum==19 ) && (yeni_durum==14 || yeni_durum==19 )){ line(screen,520,320,520,420,makecol(0,0,0));}
    else if ((siradaki_durum==15 || siradaki_durum==16 ) && (yeni_durum==15 || yeni_durum==16 )){ line(screen,120,420,220,420,makecol(0,0,0));}
    else if ((siradaki_durum==16 || siradaki_durum==17 ) && (yeni_durum==16 || yeni_durum==17 )){ line(screen,220,420,320,420,makecol(0,0,0));}
    else if ((siradaki_durum==17 || siradaki_durum==18 ) && (yeni_durum==17 || yeni_durum==18 )){ line(screen,320,420,420,420,makecol(0,0,0));}
    else if ((siradaki_durum==18 || siradaki_durum==19 ) && (yeni_durum==18 || yeni_durum==19 )){ line(screen,420,420,520,420,makecol(0,0,0));}
    else if ((siradaki_durum==15 || siradaki_durum==20 ) && (yeni_durum==15 || yeni_durum==20 )){ line(screen,120,420,120,520,makecol(0,0,0));}
    else if ((siradaki_durum==16 || siradaki_durum==21 ) && (yeni_durum==16 || yeni_durum==21 )){ line(screen,220,420,220,520,makecol(0,0,0));}
    else if ((siradaki_durum==17 || siradaki_durum==22 ) && (yeni_durum==17 || yeni_durum==22 )){ line(screen,320,420,320,520,makecol(0,0,0));}
    else if ((siradaki_durum==18 || siradaki_durum==23 ) && (yeni_durum==18 || yeni_durum==23 )){ line(screen,420,420,420,520,makecol(0,0,0));}
    else if ((siradaki_durum==19 || siradaki_durum==24 ) && (yeni_durum==19 || yeni_durum==24 )){ line(screen,520,420,520,520,makecol(0,0,0));}
    else if ((siradaki_durum==20 || siradaki_durum==21 ) && (yeni_durum==20 || yeni_durum==21 )){ line(screen,120,520,220,520,makecol(0,0,0));}
    else if ((siradaki_durum==21 || siradaki_durum==22 ) && (yeni_durum==21 || yeni_durum==22 )){ line(screen,220,520,320,520,makecol(0,0,0));}
    else if ((siradaki_durum==22 || siradaki_durum==23 ) && (yeni_durum==22 || yeni_durum==23 )){ line(screen,320,520,420,520,makecol(0,0,0));}
    else if ((siradaki_durum==23 || siradaki_durum==24 ) && (yeni_durum==23 || yeni_durum==24 )){ line(screen,420,520,520,520,makecol(0,0,0));}

            siradaki_durum = yeni_durum;
        } while(siradaki_durum != hn);
    }


    else if (n==36){

     int x=70;
     int y=70;
     while(x<=670){
    rect(screen,x,670,670,70,makecol(255,64,64));
      x+=100;
     }
     while(y<=670){
           rect(screen,70,y,670,70,makecol(255,64,64));
           y+=100;
     }

    for(e=0; e<n; e++){
        for(r=0; r<n; r++){

                if(R[e*n+r]==0){

                 if((e==1 || e==0 ) && (r==0 || r==1 )){  line(screen,170,70,170,170,makecol(255,255,255));}
                 else if((e==1 || e==2 ) && (r==1 || r==2 )){  line(screen,270,70,270,170,makecol(255,255,255));}
                else if ((e==2 || e==3 ) && (r==2 || r==3 )){  line(screen,370,70,370,170,makecol(255,255,255));}
                else if ((e==3 || e==4 ) && (r==3 || r==4 )){  line(screen,470,70,470,170,makecol(255,255,255));}
                 else if ((e==4 || e==5 ) && (r==4 || r==5 )){  line(screen,570,70,570,170,makecol(255,255,255));}
                else if ((e==0 || e==6 ) && (r==0 || r==6 )){  line(screen,70,170,170,170,makecol(255,255,255));}
                 else if ((e==1 || e==7 ) && (r==1 || r==7 )){  line(screen,170,170,270,170,makecol(255,255,255));}
                 else if ((e==2 || e==8 ) && (r==2 || r==8 )){  line(screen,270,170,370,170,makecol(255,255,255));}
                  else if ((e==3 || e==9 ) && (r==3 || r==9 )){ line(screen,370,170,470,170,makecol(255,255,255));}
                else if ((e==4 || e==10 ) && (r==4 || r==10 )){  line(screen,470,170,570,170,makecol(255,255,255));}
                 else if ((e==5 || e==11 ) && (r==5 || r==11 )){ line(screen,570,170,670,170,makecol(255,255,255));}
                 else if ((e==6 || e==7 ) && (r==6 || r==7 )){  line(screen,170,170,170,270,makecol(255,255,255));}
                else if ((e==7 || e==8 ) && (r==7 || r==8 )){  line(screen,270,170,270,270,makecol(255,255,255));}
                 else if ((e==8 || e==9 ) && (r==8 || r==9 )){  line(screen,370,170,370,270,makecol(255,255,255));}
                else if ((e==9 || e==10 ) && (r==9 || r==10 )){ line(screen,470,170,470,270,makecol(255,255,255));}
                else if ((e==10 || e==11 ) && (r==10 || r==11 )){ line(screen,570,170,570,270,makecol(255,255,255));}
                else if ((e==6 || e==12 ) && (r==6 || r==12 )){ line(screen,70,270,170,270,makecol(255,255,255));}
                else if ((e==7 || e==13 ) && (r==7 || r==13 )){  line(screen,170,270,270,270,makecol(255,255,255));}
                else if ((e==8 || e==14 ) && (r==8 || r==14 )){ line(screen,270,270,370,270,makecol(255,255,255));}
                else if ((e==9 || e==15 ) && (r==9 || r==15)){ line(screen,370,270,470,270,makecol(255,255,255));}
                else if ((e==10 || e==16 ) && (r==10 || r==16 )){ line(screen,470,270,570,270,makecol(255,255,255));}
                else if ((e==11 || e==17 ) && (r==11 || r==17 )){ line(screen,570,270,670,270,makecol(255,255,255));}
                else if ((e==12 || e==13 ) && (r==12 || r==13 )){ line(screen,170,270,170,370,makecol(255,255,255));}
                else if ((e==13 || e==14 ) && (r==13|| r==14 )){ line(screen,270,270,270,370,makecol(255,255,255));}
                 else if ((e==14 || e==15 ) && (r==14 || r==15 )){ line(screen,370,270,370,370,makecol(255,255,255));}
                else if ((e==15 || e==16 ) && (r==15 || r==16 )){ line(screen,470,270,470,370,makecol(255,255,255));}
               else if ((e==16 || e==17 ) && (r==16 || r==17 )){ line(screen,570,270,570,370,makecol(255,255,255));}
                else if ((e==12 || e==18 ) && (r==12 || r==18 )){ line(screen,70,370,170,370,makecol(255,255,255));}
                else if ((e==13 || e==19 ) && (r==13 || r==19 )){ line(screen,170,370,270,370,makecol(255,255,255));}
             else if ((e==14 || e==20 ) && (r==14 || r==20 )){ line(screen,270,370,370,370,makecol(255,255,255));}
             else if ((e==15 || e==21 ) && (r==15 || r==21 )){ line(screen,370,370,470,370,makecol(255,255,255));}
             else if ((e==16 || e==22 ) && (r==16 || r==22 )){ line(screen,470,370,570,370,makecol(255,255,255));}
             else if ((e==17 || e==23 ) && (r==17 || r==23 )){ line(screen,570,370,670,370,makecol(255,255,255));}
             else if ((e==18 || e==19 ) && (r==18 || r==19 )){ line(screen,170,370,170,470,makecol(255,255,255));}
             else if ((e==19 || e==20 ) && (r==19 || r==20 )){ line(screen,270,370,270,470,makecol(255,255,255));}
             else if ((e==20 || e==21 ) && (r==20 || r==21 )){ line(screen,370,370,370,470,makecol(255,255,255));}
              else if ((e==21 || e==22 ) && (r==21 || r==22 )){ line(screen,470,370,470,470,makecol(255,255,255));}
            else if ((e==22 || e==23 ) && (r==22 || r==23 )){ line(screen,570,370,570,470,makecol(255,255,255));}
            else if ((e==18 || e==24 ) && (r==18 || r==24 )){ line(screen,70,470,170,470,makecol(255,255,255));}
            else if ((e==19 || e==25 ) && (r==19 || r==25 )){ line(screen,170,470,270,470,makecol(255,255,255));}
            else if ((e==20 || e==26 ) && (r==20 || r==26 )){ line(screen,270,470,370,470,makecol(255,255,255));}
            else if ((e==21 || e==27 ) && (r==21 || r==27 )){ line(screen,370,470,470,470,makecol(255,255,255));}
            else if ((e==22 || e==28 ) && (r==22 || r==28 )){ line(screen,470,470,570,470,makecol(255,255,255));}
            else if ((e==23 || e==29 ) && (r==23 || r==29 )){ line(screen,570,470,670,470,makecol(255,255,255));}
            else if ((e==24 || e==25 ) && (r==24 || r==25 )){ line(screen,170,470,170,570,makecol(255,255,255));}
            else if ((e==25 || e==26 ) && (r==25 || r==26 )){ line(screen,270,470,270,570,makecol(255,255,255));}
            else if ((e==26 || e==27 ) && (r==26 || r==27 )){ line(screen,370,470,370,570,makecol(255,255,255));}
            else if ((e==27 || e==28 ) && (r==27 || r==28 )){ line(screen,470,470,470,570,makecol(255,255,255));}
            else if ((e==28 || e==29 ) && (r==28 || r==29 )){ line(screen,570,470,570,570,makecol(255,255,255));}
            else if ((e==24 || e==30 ) && (r==24 || r==30 )){ line(screen,70,570,170,570,makecol(255,255,255));}
            else if ((e==25 || e==31 ) && (r==25 || r==31 )){ line(screen,170,570,270,570,makecol(255,255,255));}
            else if ((e==26 || e==32 ) && (r==26 || r==32 )){ line(screen,270,570,370,570,makecol(255,255,255));}
            else if ((e==27 || e==33 ) && (r==27 || r==33 )){ line(screen,370,570,470,570,makecol(255,255,255));}
            else if ((e==28 || e==34 ) && (r==28 || r==34 )){ line(screen,470,570,570,570,makecol(255,255,255));}
            else if ((e==29 || e==35 ) && (r==29 || r==35 )){ line(screen,570,570,670,570,makecol(255,255,255));}
            else if ((e==30 || e==31 ) && (r==30 || r==31 )){ line(screen,170,570,170,670,makecol(255,255,255));}
            else if ((e==31 || e==32 ) && (r==31 || r==32 )){ line(screen,270,570,270,670,makecol(255,255,255));}
            else if ((e==32 || e==33 ) && (r==32 || r==33 )){ line(screen,370,570,370,670,makecol(255,255,255));}
            else if ((e==33 || e==34 ) && (r==33 || r==34 )){ line(screen,470,570,470,670,makecol(255,255,255));}
            else if ((e==34 || e==35 ) && (r==34 || r==35 )){ line(screen,570,570,570,670,makecol(255,255,255));}


           }}}
           int bb,hh;
        bb=bn;
        hh=hn;
          for(int i=0; i<2;i++){

             if(bb==0)  line(screen,70,70,170,70,makecol(255,255,255));
           else if(bb==1) line(screen,170,70,270,70,makecol(255,255,255));
           else if(bb==2) line(screen,270,70,370,70,makecol(255,255,255));
          else if(bb==3) line(screen,370,70,470,70,makecol(255,255,255));
          else if(bb==4) line(screen,470,70,570,70,makecol(255,255,255));
          else if(bb==5) line(screen,570,170,670,70,makecol(255,255,255));
          else if(bb==6) line(screen,70,170,70,270,makecol(255,255,255));
          else if(bb==12) line(screen,70,270,70,370,makecol(255,255,255));
          else if(bb==18) line(screen,70,370,70,470,makecol(255,255,255));
          else if(bb==24) line(screen,70,470,70,570,makecol(255,255,255));
          else if(bb==30) line(screen,70,670,170,670,makecol(255,255,255));
          else if(bb==31) line(screen,170,670,270,670,makecol(255,255,255));
          else if(bb==32) line(screen,270,670,370,670,makecol(255,255,255));
          else if(bb==33) line(screen,370,670,470,670,makecol(255,255,255));
          else if(bb==34) line(screen,470,670,570,670,makecol(255,255,255));
          else if(bb==35) line(screen,570,670,670,670,makecol(255,255,255));
          else if(bb==29) line(screen,670,470,670,570,makecol(255,255,255));
          else if(bb==23) line(screen,670,370,670,470,makecol(255,255,255));
          else if(bb==17) line(screen,670,270,670,370,makecol(255,255,255));
          else if(bb==11) line(screen,670,170,670,270,makecol(255,255,255));



               bb=hh;
          }

           siradaki_durum = bn;
        yeni_durum = 0;

		do {
            yeni_durum = max_degeri_bul(siradaki_durum,1);
                if((siradaki_durum==1 || siradaki_durum==0 ) && (yeni_durum==0 || yeni_durum==1 )){  line(screen,120,120,220,120,makecol(0,0,0));}
                 else if((siradaki_durum==1 || siradaki_durum==2 ) && (yeni_durum==1 || yeni_durum==2 )){  line(screen,220,120,320,120,makecol(0,0,0));}
                else if ((siradaki_durum==2 || siradaki_durum==3 ) && (yeni_durum==2 || yeni_durum==3 )){  line(screen,320,120,420,120,makecol(0,0,0));}
                else if ((siradaki_durum==3 || siradaki_durum==4 ) && (yeni_durum==3 || yeni_durum==4 )){  line(screen,420,120,520,120,makecol(0,0,0));}
                 else if ((siradaki_durum==4 || siradaki_durum==5 ) && (yeni_durum==4 || yeni_durum==5 )){  line(screen,520,120,620,120,makecol(0,0,0));}
                else if ((siradaki_durum==0 || siradaki_durum==6 ) && (yeni_durum==0 || yeni_durum==6 )){  line(screen,120,120,120,220,makecol(0,0,0));}
                 else if ((siradaki_durum==1 || siradaki_durum==7 ) && (yeni_durum==1 || yeni_durum==7 )){  line(screen,220,120,220,220,makecol(0,0,0));}
                 else if ((siradaki_durum==2 || siradaki_durum==8 ) && (yeni_durum==2 || yeni_durum==8 )){  line(screen,320,120,320,220,makecol(0,0,0));}
                  else if ((siradaki_durum==3 || siradaki_durum==9 ) && (yeni_durum==3 || yeni_durum==9 )){ line(screen,420,120,420,220,makecol(0,0,0));}
                else if ((siradaki_durum==4 || siradaki_durum==10 ) && (yeni_durum==4 || yeni_durum==10 )){  line(screen,520,120,520,220,makecol(0,0,0));}
                 else if ((siradaki_durum==5 || siradaki_durum==11 ) && (yeni_durum==5 || yeni_durum==11 )){ line(screen,620,120,620,220,makecol(0,0,0));}
                 else if ((siradaki_durum==6 || siradaki_durum==7 ) && (yeni_durum==6 || yeni_durum==7 )){  line(screen,120,220,220,220,makecol(0,0,0));}
                else if ((siradaki_durum==7 || siradaki_durum==8 ) && (yeni_durum==7 || yeni_durum==8 )){  line(screen,220,220,320,220,makecol(0,0,0));}
                 else if ((siradaki_durum==8 || siradaki_durum==9 ) && (yeni_durum==8 || yeni_durum==9 )){  line(screen,320,220,420,220,makecol(0,0,0));}
                else if ((siradaki_durum==9 || siradaki_durum==10 ) && (yeni_durum==9 || yeni_durum==10 )){ line(screen,420,220,520,220,makecol(0,0,0));}
                else if ((siradaki_durum==10 || siradaki_durum==11 ) && (yeni_durum==10 || yeni_durum==11 )){ line(screen,520,220,620,220,makecol(0,0,0));}
                else if ((siradaki_durum==6 || siradaki_durum==12 ) && (yeni_durum==6 || yeni_durum==12 )){ line(screen,120,220,120,320,makecol(0,0,0));}
                else if ((siradaki_durum==7 || siradaki_durum==13 ) && (yeni_durum==7 || yeni_durum==13 )){  line(screen,220,220,220,320,makecol(0,0,0));}
                else if ((siradaki_durum==8 || siradaki_durum==14 ) && (yeni_durum==8 || yeni_durum==14 )){ line(screen,320,220,320,320,makecol(0,0,0));}
                else if ((siradaki_durum==9 || siradaki_durum==15 ) && (yeni_durum==9 || yeni_durum==15)){ line(screen,420,220,420,320,makecol(0,0,0));}
                else if ((siradaki_durum==10 || siradaki_durum==16 ) && (yeni_durum==10 || yeni_durum==16 )){ line(screen,520,220,520,320,makecol(0,0,0));}
                else if ((siradaki_durum==11 || siradaki_durum==17 ) && (yeni_durum==11 || yeni_durum==17 )){ line(screen,620,220,620,320,makecol(0,0,0));}
                else if ((siradaki_durum==12 || siradaki_durum==13 ) && (yeni_durum==12 || yeni_durum==13 )){ line(screen,120,320,220,320,makecol(0,0,0));}
                else if ((siradaki_durum==13 || siradaki_durum==14 ) && (yeni_durum==13|| yeni_durum==14 )){ line(screen,220,320,320,320,makecol(0,0,0));}
                 else if ((siradaki_durum==14 || siradaki_durum==15 ) && (yeni_durum==14 || yeni_durum==15 )){ line(screen,320,320,420,320,makecol(0,0,0));}
                else if ((siradaki_durum==15 || siradaki_durum==16 ) && (yeni_durum==15 || yeni_durum==16 )){ line(screen,420,320,520,320,makecol(0,0,0));}
               else if ((siradaki_durum==16 || siradaki_durum==17 ) && (yeni_durum==16 || yeni_durum==17 )){ line(screen,520,320,620,320,makecol(0,0,0));}
                else if ((siradaki_durum==12 || siradaki_durum==18 ) && (yeni_durum==12 || yeni_durum==18 )){ line(screen,120,320,120,420,makecol(0,0,0));}
                else if ((siradaki_durum==13 || siradaki_durum==19 ) && (yeni_durum==13 || yeni_durum==19 )){ line(screen,220,320,220,420,makecol(0,0,0));}
             else if ((siradaki_durum==14 || siradaki_durum==20 ) && (yeni_durum==14 || yeni_durum==20 )){ line(screen,320,320,320,420,makecol(0,0,0));}
             else if ((siradaki_durum==15 || siradaki_durum==21 ) && (yeni_durum==15 || yeni_durum==21 )){ line(screen,420,320,420,420,makecol(0,0,0));}
             else if ((siradaki_durum==16 || siradaki_durum==22 ) && (yeni_durum==16 || yeni_durum==22 )){ line(screen,520,320,520,420,makecol(0,0,0));}
             else if ((siradaki_durum==17 || siradaki_durum==23 ) && (yeni_durum==17 || yeni_durum==23 )){ line(screen,620,320,620,420,makecol(0,0,0));}
             else if ((siradaki_durum==18 || siradaki_durum==19 ) && (yeni_durum==18 || yeni_durum==19 )){ line(screen,120,420,220,420,makecol(0,0,0));}
             else if ((siradaki_durum==19 || siradaki_durum==20 ) && (yeni_durum==19 || yeni_durum==20 )){ line(screen,220,420,320,420,makecol(0,0,0));}
             else if ((siradaki_durum==20 || siradaki_durum==21 ) && (yeni_durum==20 || yeni_durum==21 )){ line(screen,320,420,420,420,makecol(0,0,0));}
              else if ((siradaki_durum==21 || siradaki_durum==22 ) && (yeni_durum==21 || yeni_durum==22 )){ line(screen,420,420,520,420,makecol(0,0,0));}
            else if ((siradaki_durum==22 || siradaki_durum==23 ) && (yeni_durum==22 || yeni_durum==23 )){ line(screen,520,420,620,420,makecol(0,0,0));}
            else if ((siradaki_durum==18 || siradaki_durum==24 ) && (yeni_durum==18 || yeni_durum==24 )){ line(screen,120,420,120,520,makecol(0,0,0));}
            else if ((siradaki_durum==19 || siradaki_durum==25 ) && (yeni_durum==19 || yeni_durum==25 )){ line(screen,220,420,220,520,makecol(0,0,0));}
            else if ((siradaki_durum==20 || siradaki_durum==26 ) && (yeni_durum==20 || yeni_durum==26 )){ line(screen,320,420,320,520,makecol(0,0,0));}
            else if ((siradaki_durum==21 || siradaki_durum==27 ) && (yeni_durum==21 || yeni_durum==27 )){ line(screen,420,420,420,520,makecol(0,0,0));}
            else if ((siradaki_durum==22 || siradaki_durum==28 ) && (yeni_durum==22 || yeni_durum==28 )){ line(screen,520,420,520,520,makecol(0,0,0));}
            else if ((siradaki_durum==23 || siradaki_durum==29 ) && (yeni_durum==23 || yeni_durum==29 )){ line(screen,620,420,620,520,makecol(0,0,0));}
            else if ((siradaki_durum==24 || siradaki_durum==25 ) && (yeni_durum==24 || yeni_durum==25 )){ line(screen,120,520,220,520,makecol(0,0,0));}
            else if ((siradaki_durum==25 || siradaki_durum==26 ) && (yeni_durum==25 || yeni_durum==26 )){ line(screen,220,520,320,520,makecol(0,0,0));}
            else if ((siradaki_durum==26 || siradaki_durum==27 ) && (yeni_durum==26 || yeni_durum==27 )){ line(screen,320,520,420,520,makecol(0,0,0));}
            else if ((siradaki_durum==27 || siradaki_durum==28 ) && (yeni_durum==27 || yeni_durum==28 )){ line(screen,420,520,520,520,makecol(0,0,0));}
            else if ((siradaki_durum==28 || siradaki_durum==29 ) && (yeni_durum==28 || yeni_durum==29 )){ line(screen,520,520,620,520,makecol(0,0,0));}
            else if ((siradaki_durum==24 || siradaki_durum==30 ) && (yeni_durum==24 || yeni_durum==30 )){ line(screen,120,520,120,620,makecol(0,0,0));}
            else if ((siradaki_durum==25 || siradaki_durum==31 ) && (yeni_durum==25 || yeni_durum==31 )){ line(screen,220,520,220,620,makecol(0,0,0));}
            else if ((siradaki_durum==26 || siradaki_durum==32 ) && (yeni_durum==26 || yeni_durum==32 )){ line(screen,320,520,320,620,makecol(0,0,0));}
            else if ((siradaki_durum==27 || siradaki_durum==33 ) && (yeni_durum==27 || yeni_durum==33 )){ line(screen,420,520,420,620,makecol(0,0,0));}
            else if ((siradaki_durum==28 || siradaki_durum==34 ) && (yeni_durum==28 || yeni_durum==34 )){ line(screen,520,520,520,620,makecol(0,0,0));}
            else if ((siradaki_durum==29 || siradaki_durum==35 ) && (yeni_durum==29 || yeni_durum==35 )){ line(screen,620,520,620,620,makecol(0,0,0));}
            else if ((siradaki_durum==30 || siradaki_durum==31 ) && (yeni_durum==30 || yeni_durum==31 )){ line(screen,120,620,220,620,makecol(0,0,0));}
            else if ((siradaki_durum==31 || siradaki_durum==32 ) && (yeni_durum==31 || yeni_durum==32 )){ line(screen,220,620,320,620,makecol(0,0,0));}
            else if ((siradaki_durum==32 || siradaki_durum==33 ) && (yeni_durum==32 || yeni_durum==33 )){ line(screen,320,620,420,620,makecol(0,0,0));}
            else if ((siradaki_durum==33 || siradaki_durum==34 ) && (yeni_durum==33 || yeni_durum==34 )){ line(screen,420,620,520,620,makecol(0,0,0));}
            else if ((siradaki_durum==34 || siradaki_durum==35 ) && (yeni_durum==34 || yeni_durum==35 )){ line(screen,520,620,620,620,makecol(0,0,0));}
            siradaki_durum = yeni_durum;
        } while(siradaki_durum != hn);
    }

else
    exit(1);

release_screen();

while(!key[KEY_ESC]){}

return 0;
}
