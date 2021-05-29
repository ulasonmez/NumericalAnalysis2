#include <stdio.h>
#include <stdlib.h>
#include <math.h>
double f(double a);
float us(float a,float b);
float hataDegeri(float ustSinir,float altSinir,int adim);
double fturev(double a);
float hataDegeri2(float ust,float alt);
float newVal(float a,float b);
float hata = 0.02;
int main(int argc, char *argv[]) {
	int i,ikiyeBolme=0,newtonThompson=0,dogrusalInterpolasyon=0;
	float altSinir=0,ustSinir=2.0,newtonR=2.0,newtonR1;
	float alt=altSinir,orta,ust=ustSinir;
	if(f(altSinir)!=0 && f(ustSinir)!=0){
		if(f(altSinir)*f(ustSinir)<0){
			printf("IKIYE BOLME METODU\n");
			printf("#           kok            e\n");
			for(i =1;i<=10;i++){
				orta = (alt+ust)/2;

				if(f(orta)==0){
					printf("%d        %f     %f\n",i,orta,hataDegeri(ust,alt,i));
					break;
				}
				else{
					if(i==10){
						printf("%d       %f     %f\n",i,orta,hataDegeri(ust,alt,i));
						break;
					}
					printf("%d        %f     %f\n",i,orta,hataDegeri(ust,alt,i));
					if(hataDegeri(ust,alt,i)<hata && ikiyeBolme==0){
						ikiyeBolme=i;
					}
					if(f(alt)*f(orta)<0){
						ust = orta;
						orta =(alt+ust)/2;
					}
					else if(f(orta)*f(ust)<0){
						alt = orta;
						orta = (alt+ust)/2;
					}

				}
			}
		}
		printf("\n\n");
		printf("NEWTON THOMPSON METODU\n");
		printf("#           kok            e\n");
		for(int j =1;j<=10;j++){
			newtonR1=newtonR -(f(newtonR)/fturev(newtonR));
			if(j==10){
				printf("%d       %f     %f\n",j,newtonR1,hataDegeri2(newtonR1,newtonR));
				break;
			}

			printf("%d        %f     %f\n",j,newtonR1,hataDegeri2(newtonR1,newtonR));
			if(hataDegeri2(newtonR1,newtonR)<hata && newtonThompson==0){
				newtonThompson=j;
			}
			newtonR = newtonR1;

		}
		printf("\n\n");
		printf("DOGRUSAL INTERPOLASYON METODU\n");
		printf("#           kok            e\n");
		alt = altSinir;
		ust=ustSinir;
		orta = newVal(alt,ust);
		for(int j = 1;j<=10;j++){
			if(f(alt)*f(ust)<0){
				if(j==10){
						printf("%d      %f      %f\n",j,orta,hataDegeri2(ust,orta));
						break;
					}
					printf("%d       %f      %f\n",j,orta,hataDegeri2(ust,orta));
					if(hataDegeri2(ust,orta)<0.02 && dogrusalInterpolasyon==0){
						dogrusalInterpolasyon=j;
					}
					if(f(alt)*f(orta)<0){
						ust = orta;
					}
					else if(f(ust)*f(orta)<0){
						alt = orta;
					}
					orta = newVal(alt,ust);
			}
		}
	}
	if(ikiyeBolme!=0){
		printf("Ikiye bolme metodu ile 0.02 den daha kucuk hata degerine %d. adimda ulasilmistir.\n",ikiyeBolme);
	}
	if(newtonThompson!=0){
		printf("Newton Thompson metodu ile 0.02 den daha kucuk hata degerine %d. adimda ulasilmistir.\n",newtonThompson);
	}
	if(dogrusalInterpolasyon!=0){
		printf("Dogrusal Interpolasyon metodu ile 0.02 den daha kucuk hata degerine %d. adimda ulasilmistir.\n",dogrusalInterpolasyon);
	}
	return 0;
}
//fonksiyonun sonucunu dondurur
double f(double a){
	return exp(-0.5*(a))-a-0.2;
}
double fturev(double a){
	return ((-0.5*(a))*exp((-0.5*(a))-1))-1;
}
//us alma fonksiyonu
float us(float a,float b){
	float c = 1;
	b *= -1;
	for(int i =0;i<b;i++){
		c =c*a;
	}
	b *= -1;
	if(b>0){
		return c;
	}
	else if(b<0){
		return 1/c;
	}
	else if(b==0){
		return 1.0;
	}
}
float hataDegeri(float ustSinir,float altSinir,int adim){
	return ((ustSinir-altSinir)/us(2,adim));
}
float hataDegeri2(float ust,float alt){
	if(ust-alt>0){
		return ust-alt;
	}
	else if(ust-alt<0){
		return -1*(ust-alt);
	}
	else return 0;

}
//a = altsinir, b=ustsinir
float newVal(float a,float b){
	return (a*(f(b)) - b*(f(a))) / (f(b) - f(a));
}
