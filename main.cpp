#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <conio.h>
#include <graphics.h>
#define HEIGHT 1000
#define WIDTH 1000



//Fonksiyonlarin tanimi
void FillArea(int x,int y,int oldColor,int newColor);

//Faktoriyel hesabi icin gerekli
int fact(int n)
{
    if(n>1)
        return n*fact(n-1);
    else if(n>=0)
        return 1;
}

void Line(int x1,int y1,int x2,int y2){
	int pixelCount;
	int dx,dy;
	float x,xDiff;
	float y,yDiff;
	dx=x2-x1; 
	dy=y2-y1;
	pixelCount=abs(dx) >abs(dy) ? abs(dx):abs(dy);
	xDiff=(float)dx / (float)pixelCount; 
	yDiff=(float)dy / (float)pixelCount;
	x=(float)x1;
	y=(float)y1;
	while(pixelCount--)
	{
		putpixel((int)(x+0.5f),(int)(y+0.5f),WHITE);
		x+=xDiff;
		y+=yDiff;
    }
}

void DrawPolygon(int *arr,int edges){
	edges = edges*2; // Bir kenari 2 nokta birlestirir
	arr[edges]=arr[0];
	arr[edges+1]=arr[1];
	for(int i=0;i<edges;i+=2)
		Line(arr[i],arr[i+1],arr[i+2],arr[i+3]);
	Line(arr[0],arr[1],arr[edges-2],arr[edges-1]);
}

void DrawBezierCurve(int px[], int py[], int n){
	float u,x,y,b;
    putpixel(px[0],py[0],WHITE);
    int nfact=fact(n-1);
    for(u=0.0001;u<1;u+=0.0001)
    {
        x=0;
        y=0;
        for(int i=0;i<n;i++)
        {
            b=(nfact*pow(1-u,n-1-i)*pow(u,i))/(fact(n-1-i)*fact(i));
            x+=b*px[i];
            y+=b*py[i];
        }
        putpixel(x,y,WHITE);
    }
    putpixel(px[n-1],py[n-1],WHITE);
}

void DrawRing(int xCenter,int yCenter,int Radius){
	int x,y;
     float d,i;
     d=2*M_PI*Radius;
     d=1/d;
     for(i=0;i<=2*M_PI;i+=d)
     {
          x=xCenter+int(Radius*cos(i));
          y=yCenter+int(Radius*sin(i));
          putpixel(int(x),int(y),WHITE);
     }
}

void DrawCircle(int xCenter,int yCenter,int r){
	int x,y;
     for(y= -r;y<=r;y++){
     	for(x=-r;x<=r;x++){
     		if(x*x + y*y < r*r)
     			putpixel(x+xCenter,y+yCenter,WHITE);
		 }
	 }
}

void FillArea(int x,int y,int oldColor,int newColor){
	if(getpixel(x,y)==oldColor){
		putpixel(x,y,newColor);
		FillArea(x+1,y,oldColor,newColor);
		FillArea(x-1,y,oldColor,newColor);
		FillArea(x,y+1,oldColor,newColor);
		FillArea(x,y-1,oldColor,newColor);
	}
}

void DrawArc(int xCenter,int yCenter,int sAngle,int fAngle,int Radius){
	int x,y;
     float d,i;
     d=2*M_PI*Radius;
     d=1/d;
     for(i=(sAngle*M_PI)/180;i<=(fAngle*M_PI)/180;i+=d)
     {
          x=xCenter+int(Radius*cos(i));
          y=yCenter+int(Radius*sin(i));
          putpixel(int(x),int(y),WHITE);
     }
}

void DrawEllipse(int xCenter,int yCenter,int Radius1,int Radius2){
	int x,y;
     float d,i;
     d=2*M_PI*Radius1;
     d=1/d;
     for(i=0;i<=2*M_PI;i+=d)
     {
          x=xCenter+int(Radius1*cos(i));
          y=yCenter+int(Radius2*sin(i));
          putpixel(int(x),int(y),WHITE);
     }
}

void DrawDisk(int xCenter,int yCenter,int inR,int outR){
	int x,y;
     for(y= -outR;y<=outR;y++){
     	for(x=-outR;x<=outR;x++){
     		if(x*x + y*y > inR*inR && x*x+y*y < outR*outR)
     			putpixel(x+xCenter,y+yCenter,WHITE);
		 }
	 }
}

void DrawStar(int xm,int ym,int r1,int r2,int color)
{
     float d,d1;
     int arr1[10],arr2[10],j;
     d=0;
     d1=(M_PI)/5;
     for(j=0 ; j<10 ; j+=2)
     {
         arr1[j]=xm+int(r1*cos(d));
         arr1[j+1]=ym+int(r1*sin(d));

         arr2[j]=xm+int(r2*cos(d1));
         arr2[j+1]=ym+int(r2*sin(d1));

         putpixel(arr1[j],arr1[j+1],WHITE);
         putpixel(arr2[j],arr2[j+1],WHITE);

         d+=(2*M_PI)/5;
         d1+=(2*M_PI)/5;
         
         
     }

     for(j=0;j<10;j+=2)// noktalari birlestirme
     {
          Line(arr1[j],arr1[j+1],arr2[j],arr2[j+1]);
          if(j!=0)
          {
        	   Line(arr1[j],arr1[j+1],arr2[j-2],arr2[j-1]);
        	   Line(arr1[j],arr1[j+1],arr2[j-2],arr2[j-1]);
          }
     }
     Line(arr1[0],arr1[1],arr2[0],arr2[1]);
     Line(arr1[0],arr1[1],arr2[8],arr2[9]);
     Line(arr1[2],arr1[3],arr2[0],arr2[1]);
     Line(arr1[2],arr1[3],arr2[2],arr2[3]);
     Line(arr1[4],arr1[5],arr2[2],arr2[3]);
     Line(arr1[4],arr1[5],arr2[4],arr2[5]);
     Line(arr1[6],arr1[7],arr2[4],arr2[5]);
     Line(arr1[6],arr1[7],arr2[6],arr2[7]);
     Line(arr1[8],arr1[9],arr2[6],arr2[7]);
     Line(arr1[8],arr1[9],arr2[8],arr2[9]);
}

//Sekillere gore islemler
void PolygonTranslation(int x,int y,int *s,int n){
	
	for(int i=0;i<n*2;i+=2){
		s[i]=s[i]+x;
		s[i+1]=s[i+1]+y;
	}
	DrawPolygon(s,n);
}

void PolygonRotate(int *s,int angle,int n){
	
	float a = (angle*M_PI)/180;
	int pivotx=s[0],pivoty=s[1];
	int x_shifted,y_shifted;
	for(int i=0;i<n*2;i+=2){
		x_shifted = s[i] - pivotx;
		y_shifted = s[i+1] - pivoty;
		s[i]=pivotx + x_shifted*cos(a) - y_shifted*sin(a);
		s[i+1]=pivoty + x_shifted*sin(a) + y_shifted*cos(a);
	}
	DrawPolygon(s,n);
}

void PolygonScale(int *s,float sx,float sy,int n){
	
	for(int i=0;i<n*2;i+=2){
		s[i]=(int)(s[i]*sx)%HEIGHT;
		s[i+1]=(int)(s[i+1]*sy)%WIDTH;
	}
	DrawPolygon(s,n);
}

void PolygonReflection(int *s,int n,int settings){
	
		if(settings == 1){
			//x eksenine gore
			PolygonTranslation(0,s[1]*2,s,n);	
		}
		else if(settings == 2){
			//y eksenine gore
			PolygonTranslation(s[0]*2,0,s,n);	
		}		

	DrawPolygon(s,n);
}

void PolygonShearing(int *s,float shx,float shy,int n){
	for(int i=0;i<n*2;i+=2){
		s[i]=(int)s[i]+(int)s[i+1]*shx;
		s[i+1]=(int)s[i+1]+(int)s[i]*shy;
		//printf("x=%d y=%d\n",s[i],s[i+1]); Test
	}
	DrawPolygon(s,n);
}

//void OvalRotate(int *s,int angle,int SelectedOval){
//	
//	float a = (angle*M_PI)/180;
//	int pivotx=s[0],pivoty=s[1];
//	int x_shifted,y_shifted;
//	for(int i=0;i<2;i++){
//		x_shifted = s[i] - pivotx;
//		y_shifted = s[i+1] - pivoty;
//		s[i]=pivotx + x_shifted*cos(a) - y_shifted*sin(a);
//		s[i+1]=pivoty + x_shifted*sin(a) + y_shifted*cos(a);
//	}
//	if(SelectedOval==1) DrawRing(s[0],s[1],s[2]);// Cember
//			else if(SelectedOval==2) DrawCircle(s[0],s[1],s[2]); // Daire
//			else if(SelectedOval==3) DrawEllipse(s[0],s[1],s[2],s[3]); // Elips
//			else if(SelectedOval==4) DrawDisk(s[0],s[1],s[2],s[3]); //Disk
//}

void FillOval(int *s){
	//floodfill(s[0],s[1],WHITE);
	FillArea(s[0],s[1],0,10);
}


void PolygonTransformations(int *s,int n){
	int Selected;
	while(!kbhit()){
		printf("1-) Oteleme\n2-) Dondurme\n3-) Olceklendirme\n4-) Yansima\n5-) Meyillendirme\n6-) Doldur\n7-) Cikis\n\n\t Secim Yapiniz : ");
		scanf("%d", &Selected);
		if(Selected == 1){
			//Oteleme
			int x,y;
			printf("Yatayda oteleme="); scanf("%d",&x);
			printf("Dikeyde oteleme="); scanf("%d",&y);
			PolygonTranslation(x,y,s,n);
		}
		else if(Selected == 2){
			//Dondurme
			int Angle;
			printf("Dondurme Acisi="); scanf("%d",&Angle);
			PolygonRotate(s,Angle,n);
		}
		else if(Selected == 3){
			//Olceklendirme
			float x,y;
			printf("X olcekleme faktoru (float)="); scanf("%f",&x);
			printf("Y olcekleme faktoru (float)="); scanf("%f",&y);
			PolygonScale(s,x,y,n);
		}
		else if(Selected == 4){
			//Yansima
			int settings;
			printf("1-) X eksenine gore\n2-) Y eksenine gore\nSeciminiz:"); scanf("%d",&settings);
			PolygonReflection(s,n,settings);
		}
		else if(Selected == 5){
			//Meyillendirme
			float x,y;
			printf("x ekseninde meyillendirme="); scanf("%f",&x);
			printf("y ekseninde meyillendirme="); scanf("%f",&y);
			PolygonShearing(s,x,y,n);
		}
		else if(Selected == 6){
			FillArea(s[2]+2,s[3]+2,0,10);
		}
		else{
			break;
		}
	}
}



void OvalTransformations(int *s,int SelectedOval){
	int Selected;
	while(!kbhit()){
		printf("1-) Oteleme\n2-) Olceklendirme\n3-) Yansima\n4-) Doldur\n5-) Cikis\n\n\t Secim Yapiniz : ");
		scanf("%d", &Selected);
		if(Selected == 1){
			//Oteleme
			int x,y;
			printf("Yatayda oteleme="); scanf("%d",&x);
			printf("Dikeyde oteleme="); scanf("%d",&y);
			if(SelectedOval==1) DrawRing(s[0]=s[0]+x,s[1]=s[1]+y,s[2]);// Cember
			else if(SelectedOval==2) DrawCircle(s[0]=s[0]+x,s[1]=s[1]+y,s[2]); // Daire
			else if(SelectedOval==3) DrawEllipse(s[0]=s[0]+x,s[1]=s[1]+y,s[2],s[3]); // Elips
			else if(SelectedOval==4) DrawDisk(s[0]=s[0]+x,s[1]=s[1]+y,s[2],s[3]); //Disk
		}
		else if(Selected == 2){
			//Olceklendirme
			float r;
			printf("Yaricap olcekleme faktoru (float)="); scanf("%f",&r);
			if(SelectedOval==1) DrawRing(s[0],s[1],s[2]=(int)s[2]*r);// Cember
			else if(SelectedOval==2) DrawCircle(s[0],s[1],s[2]=(int)s[2]*r); // Daire
			else if(SelectedOval==3) DrawEllipse(s[0],s[1],s[2]=(int)s[2]*r,s[3]=(int)s[3]*r); // Elips
			else if(SelectedOval==4) DrawDisk(s[0],s[1],s[2]=(int)s[2]*r,s[3]=(int)s[3]*r); //Disk
			
		}
		else if(Selected == 3){
			//Yansima
			int settings;
			printf("1-) X eksenine gore\n2-) Y eksenine gore\nSeciminiz:"); scanf("%d",&settings);
			if(SelectedOval==1) if(settings == 1) DrawRing(s[0]=s[0]*2,s[1],s[2]); else DrawRing(s[0],s[1]=s[1]*2,s[2]);// Cember
			else if(SelectedOval==2) if(settings == 1) DrawCircle(s[0]=s[0]*2,s[1],s[2]); else DrawCircle(s[0],s[1]=s[1]*2,s[2]); // Daire
			else if(SelectedOval==3) if(settings == 1) DrawEllipse(s[0]=s[0]*2,s[1],s[2],s[3]); else DrawEllipse(s[0],s[1]=s[1]*2,s[2],s[3]);// Elips
			else if(SelectedOval==4) if(settings == 1) DrawDisk(s[0]=s[0]*2,s[1],s[2],s[3]); else DrawDisk(s[0],s[1]=s[1]*2,s[2],s[3]);//Disk
		}
		else if(Selected == 4){
			FillOval(s);
		}
		else{
			break;
		}
	}
}

void CutWindow(int x1,int y1,int x2,int y2){
	for(int x=0;x<WIDTH;x++){
		for(int y=0;y<HEIGHT;y++){
			if(x>=x1 && y>=y1 && x<=x2 && y<=y2){
				//secili pixel icinde ise bir sey yapma
			}
			else{
				if(getpixel(x,y)!=0)
				putpixel(x,y,0);
			}
		}
	}
}

int main()
{
	initwindow(HEIGHT,WIDTH,"Grafik Ekrani",0,0);
	int SelectedShape;
	int x1,y1,x2,y2;
	while(!kbhit())
	{
		system("CLS");
		printf("AHMED YILMAZ 171213038\n1-) Cizgi\n2-) Bezier Egrisi\n3-) Ucgen\n4-) Kare\n5-) Dikdortgen\n6-) Cokgen\n7-) Cember\n8-) Daire\n9-) Yay\n10-) Elips\n11-) Disk\n12-) Ekran Kirpma\n13-) Yildiz\n14-) Cikis\n\n\t Secim Yapiniz : ");
		scanf("%d", &SelectedShape);
		if(SelectedShape == 1) {
			printf("Baslangic koordinatlari\n");
			printf("x1="); scanf("%d",&x1);
			printf("y1="); scanf("%d",&y1);
			printf("Bitis koordinatlari\n");
			printf("x2="); scanf("%d",&x2);
			printf("y2="); scanf("%d",&y2);
			Line(x1,y1,x2,y2);
		}
		else if(SelectedShape == 2) {
			//Bezier Egrisi
			int n;
			printf("Kac kontrol noktali bezier egrisi:");
			scanf("%d",&n);
			int px[n],py[n];
    		for(int i=0;i<n;i++){
    			printf("%d. kontrol noktasi koordinatlari\n",i+1);
    			printf("x=");
    			scanf("%d",&px[i]);
    			printf("y=");
    			scanf("%d",&py[i]);
			}
			DrawBezierCurve(px,py,n);
		}
		else if(SelectedShape == 3) {
			int Triangle[6];
			printf("x1="); scanf("%d",&Triangle[0]);
			printf("y1="); scanf("%d",&Triangle[1]);
			printf("x2="); scanf("%d",&Triangle[2]);
			printf("y2="); scanf("%d",&Triangle[3]);
			printf("x3="); scanf("%d",&Triangle[4]);
			printf("y3="); scanf("%d",&Triangle[5]);
			DrawPolygon(Triangle,3);
			PolygonTransformations(Triangle,3);
		}
		else if(SelectedShape == 4) {
			int e,Square[8];
			printf("Sol ust x koordinati="); scanf("%d",&x1);
			printf("Sol ust y koordinati="); scanf("%d",&y1);
			printf("Kenar uzunlugu="); scanf("%d",&e);
			Square[0]=x1;Square[1]=y1;Square[2]=x1+e;Square[3]=y1;Square[4]=x1+e;Square[5]=y1-e;Square[6]=x1;Square[7]=y1-e;
			DrawPolygon(Square,4);
			PolygonTransformations(Square,4);
		}
		else if(SelectedShape == 5) {
			printf("Ust sol kose x koordinati="); scanf("%d",&x1);
			printf("Ust sol kose y koordinati="); scanf("%d",&y1);
			printf("Alt sag kose x koordinati="); scanf("%d",&x2);
			printf("Alt sag kose y koordinati="); scanf("%d",&y2);
			int Rectangle[8];
			Rectangle[0]=x1;Rectangle[1]=y1;Rectangle[2]=x2;Rectangle[3]=y1;Rectangle[4]=x2;Rectangle[5]=y2;Rectangle[6]=x1;Rectangle[7]=y2;
			DrawPolygon(Rectangle,4);
			PolygonTransformations(Rectangle,4);
		}
		else if(SelectedShape == 6) {
			int n,j=1;
			printf("Cokgenin kenar sayisi="); scanf("%d",&n);
			int Polygon[n*2];
			for(int i=0;i<n*2;i+=2){
				printf("%d.Kose icin koordinatlar\n",j);
				printf("x=");
				scanf("%d",&Polygon[i]);
				printf("y=");
				scanf("%d",&Polygon[i+1]);
				j++;
			}
			DrawPolygon(Polygon,n);
			PolygonTransformations(Polygon,n);
		}
		else if(SelectedShape == 7) {
			//Cember
			int Ring[3];
			printf("Cemberin merkez koordinatlari\n");
			printf("x="); scanf("%d",&Ring[0]);
			printf("y="); scanf("%d",&Ring[1]);
			printf("Yaricap="); scanf("%d",&Ring[2]);
			DrawRing(Ring[0],Ring[1],Ring[2]);
			OvalTransformations(Ring,1);
		}
		else if(SelectedShape == 8) {
			//Daire
			int Circle[3];
			printf("Dairenin merkez koordinatlari\n");
			printf("x="); scanf("%d",&Circle[0]);
			printf("y="); scanf("%d",&Circle[1]);
			printf("Yaricap="); scanf("%d",&Circle[2]);
			DrawCircle(Circle[0],Circle[1],Circle[2]);
			OvalTransformations(Circle,2);
		}
		else if(SelectedShape == 9) {
			//Yay
			int Arc[5];
			printf("Yayin merkez koordinatlari\n");
			printf("x="); scanf("%d",&Arc[0]);
			printf("y="); scanf("%d",&Arc[1]);
			printf("Baslangic acisi="); scanf("%d",&Arc[2]);
			printf("Bitis acisi="); scanf("%d",&Arc[3]);
			printf("Yaricap="); scanf("%d",&Arc[4]);
			DrawArc(Arc[0],Arc[1],Arc[2],Arc[3],Arc[4]);
		}
		else if(SelectedShape == 10) {
			//Elips
			int Ellipse[4];
			printf("Elipsin merkez koordinatlari\n");
			printf("x="); scanf("%d",&Ellipse[0]);
			printf("y="); scanf("%d",&Ellipse[1]);
			printf("Yaricap1="); scanf("%d",&Ellipse[2]);
			printf("Yaricap2="); scanf("%d",&Ellipse[3]);
			DrawEllipse(Ellipse[0],Ellipse[1],Ellipse[2],Ellipse[3]);
			OvalTransformations(Ellipse,3);
		}
		else if(SelectedShape == 11) {
			int Disk[4];
			printf("Diskin merkez koordinatlari\n");
			printf("x="); scanf("%d",&Disk[0]);
			printf("y="); scanf("%d",&Disk[1]);
			printf("Ic yaricap="); scanf("%d",&Disk[2]);
			printf("Dis yaricap="); scanf("%d",&Disk[3]);
			DrawDisk(Disk[0],Disk[1],Disk[2],Disk[3]);
			OvalTransformations(Disk,4);
		}
		else if (SelectedShape == 12){
			//Ekrani kirpma
			printf("Kirpilacak ekran koordinatlari\n");
			printf("Ust sol kose x koordinati="); scanf("%d",&x1);
			printf("Ust sol kose y koordinati="); scanf("%d",&y1);
			printf("Alt sag kose x koordinati="); scanf("%d",&x2);
			printf("Alt sag kose y koordinati="); scanf("%d",&y2);
			CutWindow(x1,y1,x2,y2);
		}
		else if(SelectedShape == 13){
			int r1=50,r2=100;
			printf("Yildizin merkez koordinatlari\n");
			printf("x koordinati="); scanf("%d",&x1);
			printf("y koordinati="); scanf("%d",&y1);
			DrawStar(x1,y1,r1,r2,WHITE);
			while(!kbhit() ){
				int starSelect;
				printf("1-) Oteleme\n2-) Olceklendirme\n3-) Doldur\n4-) Cikis\n\n\t Secim Yapiniz : ");
				scanf("%d",&starSelect);
				if(starSelect == 1){
					int x,y;
					printf("Yatayda oteleme="); scanf("%d",&x);
					printf("Dikeyde oteleme="); scanf("%d",&y);
					DrawStar(x1=x1+x,y1=y1+y,r1,r2,WHITE);
				}
				else if(starSelect == 2){
					int x,y;
					printf("x olceklendirme faktoru="); scanf("%d",&x);
					printf("y olceklendirme faktoru="); scanf("%d",&y);
					DrawStar(x1,y1,r1=r1+x,r2=r2+y,WHITE);
				}
				else if(starSelect == 3){
					FillArea(x1,y1,0,15);
				}
				else{
					break;
				}
			}
		}
		else if(SelectedShape == 14){
			return 0;
		}
	}
	while( !kbhit() );
	closegraph( );
	return( 0 );
}