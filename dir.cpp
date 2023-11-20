#include<stdio.h>
#include<dos.h>
#include<memory.h>
#include<stdlib.h>
#include<string.h>

struct BOOT{
	char jmp[3];
	char OME[8];
	int bytes_per_sector;
	char sectors_per_cluster;
	int reserved;
	char FAT_cnt;
	int ROOT_size;
	int total_sectors;
	char media;
	int FAT_size;
	int sectors_per_track;
	int head_cnt;
	long hidden_sectors;
	long total_sectors_long;
	char unknown[3];
	long serial;
	char volume[11];
	char FAT_type[8];
	char loader[448];
	char mark[2];
};

struct ROOT{
	char name[8];
	char ext[3];
	char attr;
	char reserved[10];
	char time[2];
	char date[2];
	int first_cluster;
	long size;
};

void getbit(char x, char s[8]){
	for( int i=0;i<8;i++){
		s[i]=(x &(1<<i)) ?1:0;
	}
}
int convert(char *s, int i, int j){
	int sum=0,pow=1;
	for( int k=i;k<=j;k++){
		sum+=pow*s[k];
		pow*=2;
	}
	return sum;
}
void main(){
	#code truoc
	
	for( int i=0;i<10;i++){
		int j=0;
		for( j=0;j<8;j++) printf("%c",root[i].name[j]);printf("\t");
		for( j=0;j<3;j++) printf("%c",root[i].ext[j]);printf("\t");
		char n[20];
		sprintf(n,"%ld",root[i].size);//dua ve dang str
		if( strlen(n) %3==0){
			for( j=0;j<strlen(n);j++){
				if( j!=0 && j!=strlen(n)-1 && j%3==2) printf("%c,",n[j]);
				else printf("%c",n[j]);
			}
		}else if( strlen(n) %3==1){
			for( j=0;j<strlen(n);j++){
				if( j!=strlen(n)-1 && j%3==0) printf("%c,",n[j]);
				else printf("%c",n[j]);
			}
		}else for( j=0;j<strlen(n);j++){
			if( j!=strlen(n) -1&& j%3==1) printf("%c,",n[j]);
			else printf("%c",n[j]);
		}
		printf("\t");
		
		//ngay, thang, nam
		char s[16],s1[8],s2[8];
		getbit(root[i].date[0],s1);//ngay thang
		getbit(root[i].date[1],s2);//nam
		for( j=0;j<8;j++) s[j]=s1[j],s[j+8]=s2[j];
		int ngay=convert(s,0,4);
		int thang=convert(s,5,8);
		int nam=convert(s,9,15);nam+=1980
		if( thang < 10) printf("0%d-",thang);else printf("%d-",thang);
		if( ngay<10) printf("0%d",ngay); else printf("%d",ngay);
		printf("-%d\t",nam%100);
		
		//gio,phut,giay
		getbit(root[i].time[0],s1);
		getbit(root[i].time[1],s2);
		for( j=0;j<8;j++){
			s[j]=s1[j];
			s[j+8]=s2[j];
		}
		int gio=convert(s,11,15);
		int phut=convert(s,5,10);
		if( gio<12) printf("%d:",gio);else printf("%d:",gio-12);
		if( phut <10) printf("0%d",phut);else printf("%d",phut);
		if( gio<12) printf("a");else printf("p");
		printf("\n");
	}
	getchar();
}
