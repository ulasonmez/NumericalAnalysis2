#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float fonksiyonSonuc(float a){
	return exp(-0.5*(a))-a-0.2;
}
double ikiyeBolmeHata(double son,double ilk,double iterasyon){
	return ((son-ilk)/pow(2,iterasyon));
}
float newtonThompsonHata(float son,float ilk){
	return fabs(son-ilk);
}
float dogrusalInterpolasyonHata(float son,float ilk){
	return fabs(son-ilk);
}
float dogrusalInterpolasyonKok(float ilk,float son){
	float yeniKok = (ilk*(fonksiyonSonuc(son)) - son*(fonksiyonSonuc(ilk))) / (fonksiyonSonuc(son) - fonksiyonSonuc(ilk));
	return yeniKok;
}
float fonksiyonTurevSonuc(float a){
	return ((-0.5*(a))*exp((-0.5*(a))-1))-1;
}
int main(int argc, char *argv[]) {
	int iterasyon,j,ibKontrol=0,ntKontrol=0,diKontrol=0;
	double iterasyonAdim=iterasyon;
	const float altAralik=0,ustAralik=2.0;
	float newtonThompsonBaslangic=2.0,newtonThompsonYeni;
	float ikiyeBolmeIlk=altAralik,ikiyeBolmeOrta,ikiyeBolmeSon=ustAralik;
	float dogrusalInterIlk=altAralik,dogrusalInterSon=ustAralik,dogrusalInterOrta;
	printf("\t\t\t1. Metot\t\t\t 2. Metot\t\t\t\t3. Metot\n");
	printf("#(iterasyon)\t kok\t\te\t\t\tkok\t     e\t\t\t   kok\t\t   e\n");
	for(iterasyon =1;iterasyon<=10;iterasyon++){
	if(fonksiyonSonuc(altAralik)!=0 && fonksiyonSonuc(ustAralik)!=0){
		if(fonksiyonSonuc(altAralik)*fonksiyonSonuc(ustAralik)<0){
				ikiyeBolmeOrta = (ikiyeBolmeIlk+ikiyeBolmeSon)/2;
				if(fonksiyonSonuc(ikiyeBolmeOrta)==0){
					printf("%d\t\t%f\t\t%f",iterasyon,ikiyeBolmeOrta,ikiyeBolmeHata(ikiyeBolmeSon,ikiyeBolmeIlk,iterasyonAdim));
					break;
				}
				else{
					printf("%d\t\t%f    %f",iterasyon,ikiyeBolmeOrta,ikiyeBolmeHata(ikiyeBolmeSon,ikiyeBolmeIlk,iterasyonAdim));
					if(ikiyeBolmeHata(ikiyeBolmeSon,ikiyeBolmeIlk,iterasyonAdim)<0.02 && ibKontrol==0){
						ibKontrol=iterasyon;
					}
					if(fonksiyonSonuc(ikiyeBolmeIlk)*fonksiyonSonuc(ikiyeBolmeOrta)<0){
						ikiyeBolmeSon = ikiyeBolmeOrta;
						ikiyeBolmeOrta =(ikiyeBolmeIlk+ikiyeBolmeSon)/2;
					}
					else if(fonksiyonSonuc(ikiyeBolmeOrta)*fonksiyonSonuc(ikiyeBolmeSon)<0){
						ikiyeBolmeIlk = ikiyeBolmeOrta;
						ikiyeBolmeOrta = (ikiyeBolmeIlk+ikiyeBolmeSon)/2;
					}
				}
	  		}
			newtonThompsonYeni=newtonThompsonBaslangic -(fonksiyonSonuc(newtonThompsonBaslangic)/fonksiyonTurevSonuc(newtonThompsonBaslangic));
			printf("\t\t    %f\t   %f",newtonThompsonYeni,newtonThompsonHata(newtonThompsonYeni,newtonThompsonBaslangic));
			if(newtonThompsonHata(newtonThompsonYeni,newtonThompsonBaslangic)<0.02 && ntKontrol==0){
				ntKontrol=iterasyon;
			}
			newtonThompsonBaslangic = newtonThompsonYeni;
			dogrusalInterOrta = dogrusalInterpolasyonKok(dogrusalInterIlk,dogrusalInterSon);
			if(fonksiyonSonuc(dogrusalInterIlk)*fonksiyonSonuc(dogrusalInterSon)<0){
					printf("\t\t%f\t%f\n",dogrusalInterOrta,dogrusalInterpolasyonHata(dogrusalInterSon,dogrusalInterOrta));
					if(dogrusalInterpolasyonHata(dogrusalInterSon,dogrusalInterOrta)<0.02 && diKontrol==0){
						diKontrol=iterasyon;
					}
					if(fonksiyonSonuc(dogrusalInterIlk)*fonksiyonSonuc(dogrusalInterOrta)<0){
						dogrusalInterSon = dogrusalInterOrta;
					}
					else if(fonksiyonSonuc(dogrusalInterSon)*fonksiyonSonuc(dogrusalInterOrta)<0){
						dogrusalInterIlk = dogrusalInterOrta;
					}
					dogrusalInterOrta = dogrusalInterpolasyonKok(dogrusalInterIlk,dogrusalInterSon);
			}
		}
	}
		printf("\n\nIkiye bolme metodu ile 0.02 den daha kucuk hata degerine %d. adimda ulasilmistir.\n",ibKontrol);
		printf("Newton Thompson metodu ile 0.02 den daha kucuk hata degerine %d. adimda ulasilmistir.\n",ntKontrol);
		printf("Dogrusal Interpolasyon metodu ile 0.02 den daha kucuk hata degerine %d. adimda ulasilmistir.\n",diKontrol);

	return 0;
}
