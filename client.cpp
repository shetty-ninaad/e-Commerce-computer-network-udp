#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
#include<string.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<termios.h>
#include<iostream>
#include<fcntl.h>
#include<unistd.h>
#include<netdb.h>
#include<dirent.h>

//#include<process.h>
using namespace std;
#define MAXLINE 1024

//// gotoxy and getch for linux
static struct termios old, NEW;
 
void initTermios(int echo) 
{
  tcgetattr(0, &old); 
  NEW = old; 
  NEW.c_lflag &= ~ICANON;
  NEW.c_lflag &= echo ? ECHO : ~ECHO; 
  tcsetattr(0, TCSANOW, &NEW); 
}

void resetTermios(void) 
{
  tcsetattr(0, TCSANOW, &old);
}

char getch_(int echo) 
{
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}

char getch(void) 
{
  return getch_(0);
}

 
void gotoxy(int x,int y)
 {
 printf("%c[%d;%df",0x1B,y,x);
 }
 
 int menu()
{
 char x;int opt=0;
 system("clear");
 gotoxy(5,10);
 cout<<"SIGN IN <";
 gotoxy(5,11);
 cout<<"SIGN UP";
 do {
 x=getch();
 if (x==66)
 {
  gotoxy(5,10);
  cout<<"SIGN IN  ";
  gotoxy(5,11);
  cout<<"SIGN UP <";
  opt=1;
 }
 else if(x==65)
 {
  gotoxy(5,10);
  cout<<"SIGN IN <";
  gotoxy(5,11);
  cout<<"SIGN UP  ";
  opt=0;
 }
 }while(x!=10);
 gotoxy(5,12);
 //cout<<"OPTION SELECTED : ";if(opt) cout<<"SIGNUP" else cout<<"SIGNIN";
 return opt;
} 

////

char signup(char* str)
{	char bss;
	char bs[5],name[25],addr[50],cc[10],id[10],pass[10];
	cout<<"\n\n\t ** SIGN UP **";
	cout<<"\n\n (B)Buyer or (S)Seller : ";
	scanf("%s",bs);
	bss=bs[0];
	cout<<" Name : ";scanf("%s",name);
	cout<<" Address :";scanf("%s",addr);
	cout<<" Credit Card No. : ";scanf("%s",cc);
	cout<<" USER ID (2 digits):";scanf("%s",id);
	cout<<" Password  :"  ;scanf("%s",pass);

	str[0]='0';
	str[1]='*';
	str[2]='\0';
	strcat(str,bs);
	strcat(str,id);
	strcat(str,"*");
	strcat(str,pass);
	strcat(str,"*");
	strcat(str,name);
	strcat(str,"*");
	strcat(str,addr);
	strcat(str,"*");
	strcat(str,cc);
	strcat(str,"*\0");

	return bss;
}

char signin(char* str)
{
	char bss;
	char bs[5],name[25],id[10],pass[10];
	cout<<"\n\n\t ** SIGN IN **";
	cout<<"\n\n (B)Buyer or (S)Seller : ";
	scanf("%s",bs);
	bss=bs[0];
	cout<<" USER ID (2 digits)(unique):";scanf("%s",id);
	cout<<" Password    : ";scanf("%s",pass);
	str[0]='1';
	str[1]='*';
	str[2]='\0';
	
	strcat(str,bs);
	strcat(str,id);
	strcat(str,"*");
	strcat(str,pass);
	strcat(str,"*\0");

	return  bss;
}


void* sellsomething(char *buffer)
{

//char *buffer=(char *)malloc(sizeof(char)*100);
int ch;int i;
char prod[100];
char quantity[100];
char price[100];
{
printf("\n PLEASE SELECT THE CATOGERY -> ");
printf("\n1. ELECTRONICS\n2. BOOKS\n3. MOVIES\n4. VIDEO GAMES :");
scanf("%d",&ch);
printf("\n ENTER THE PRODUCT NAME :");
scanf("%s",prod);
printf("\n ENTER THE PRICE :");
scanf("%s",price);
printf("\n ENTER THE QUANTITY :");
scanf("%s",quantity);
if(ch==1) strcat(buffer,"ELECTRONICS\0");
if(ch==2) strcat(buffer,"BOOKS\0");
if(ch==3) strcat(buffer,"MOVIES\0");
if(ch==4) strcat(buffer,"GAMES\0");
strcat(buffer,"*");
strcat(buffer,prod);
strcat(buffer,"*");
strcat(buffer,price);
strcat(buffer,"*\0");
strcat(buffer,quantity);
cout<<endl<<prod;
return buffer;
}
}

int main(int argc,char* argv[])
	{
	int sockfd, n,cnts,nom,i,chx,chy,j,k,l,newi,lmao=1;
	char price[100],quantity[100],removed[100];
	socklen_t len;
	char recvline[1024],recvline1[1024],recvline2[1024],recvline3[1024];
	struct sockaddr_in servaddr;
	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	servaddr.sin_port=htons(5035);
	connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));

	int opt,cc,flag,xx,chs;
	char name[10],address[20],bs,sellsome[100],newbuf[1024],newerbuf[1024];
///////////////
	while(1)
	{

		char sign_up[1024],sign_in[1024];
		int s;
		s=menu(); // MENU FOR SIGNUP or SIGNIN
		if(s==1)
		{	xx=0;
			do
			{
			
			bs=signup(sign_up);
			len=sizeof(servaddr);
			sendto(sockfd,sign_up,1024,0,(struct sockaddr*)&servaddr,len);
			n=recvfrom(sockfd,recvline,1024,0,NULL,NULL);
			recvline[n]=0;
			if(recvline[0]=='1')
					{
						xx=1;
						cout<<" USER ID ALREADY EXISTS. PLZ ENTER DIFFERENT USER ID";
					}
			if(recvline[0]=='5')
					{
					xx=0;
					cout<<"\n SIGNED UP SUCCESFULLY\n Automatically SIGNING IN \n";
					goto here;
					}
		}while(xx==1);
		}
		if(s==0)
		{		xx=0;
				do
				{
				bs=signin(sign_in);
				len=sizeof(servaddr);
				sendto(sockfd,sign_in,1024,0,(struct sockaddr*)&servaddr,len);
				n=recvfrom(sockfd,recvline,1024,0,NULL,NULL);
				recvline[n]=0;
				if(recvline[0]=='5')
					{
						xx=1;
						cout<<" USER DOESN'T EXIST OR INCORRECT PASSWORD\n";	
					}
				
					if(recvline[0]=='1')
						xx=0;
				
				}while(xx==1);
				cout<<"\n SUCCESSFULLY SIGNED IN\n";
				
				here:
				
				if(bs=='B')
				{
				while(1)
					{
						system("clear");
						n=recvfrom(sockfd,recvline1,1024,0,NULL,NULL);
					recvline1[n];
					printf("\n HEY THERE,  %s ! ",recvline1);
			 	
					printf("\n 1. BROWSE ITEMS \n 2. VIEW CART\n 3. LOG OUT -> ");
					cin>>chs;
					if(chs==1)//BROWSE ITEMS
					{		//int choice;	
							char at[3];
							printf("\n Please choose Department ->\n");
							printf("\n 1. ELECTRONICS\n 2. BOOKS\n 3. MOVIES\n. 4. VIDEO GAMES -> ");
							cin>>at[1];
							
							at[0]='1';
							at[2]='\0';
							sendto(sockfd,at,1024,0,(struct sockaddr*)&servaddr,len);
							n=recvfrom(sockfd,newbuf,1024,0,NULL,NULL);
							//newbuf[n]=0;
							cout<<"\n Products of the selected Department : \n";
							for(i=0;newbuf[i]!='*';i++);
							i++;
							cout<<"\n 1)"	;
							nom=2;
							
							for(;newbuf[i]!='*';i++)
							{
								cout<<newbuf[i];
							}
							cnts=0;
							for(;newbuf[i]!='\0';i++)
							{
								if(newbuf[i]=='*')
								{
									cnts++;
									if(cnts%3==0)
									{
									
									cout<<"\n "<<nom<<")";
									nom++;
									}
								}
									if(cnts%3==0&&newbuf[i]!='*')
									{
									cout<<newbuf[i];	
									}
							}
							cout<<"\n\n | Select the product | Enter Product No -> \n";
							scanf("%d",&chx);
							printf("\n 1. BUY NOW\n 2. ADD TO CART\n");
							scanf("%d",&chy);
						
						
							for(i=0,j=0;j<chx-1;i++)
							{
								if(newbuf[i]=='#') j++;
							}
							cnts=0;
							newi=i;
							int lx;
							int qnty;
							
							cnts=0;
							if(chy==2)//ADD TO CART
							{
							int m,n=0;
							char buf[100],data[100];
							for(m=2;sign_in[m]!='*';m++)
							{
							buf[n]=sign_in[m];
							n++;
							}
							buf[n]='\0';
							strcat(buf,"_d.txt");
							
							m=0; 
							for(n=newi;newbuf[n]!='#';n++)
							{
								data[m]=newbuf[n];
								m++;
							}
							data[m]='#';
							data[m+1]='\0';
																																									
						int f_d=open(buf,O_RDWR |O_APPEND);
		                  	write(f_d,data,strlen(data));
							close(f_d);
							printf("\n\n   Product has been added to your cart succesfully !! \n");
							}
							if(chy==1) //BUY THE PRODUCT
							{	char qu[10];
								for(;;i++)
								{
									if(newbuf[i]=='*')cnts++;
									if (cnts==3) break;
								}
								i++;
								j=i;
								l=0;
								for(;newbuf[i]!='#';i++)
								{
									qu[l]=newbuf[i];
									l++;
								}
								qnty=atoi(qu);
								qnty--;
								sprintf(quantity,"%d",qnty);	
								l=0;
								for(;newbuf[j]!='#';j++)
								{
									newbuf[j]=quantity[l];
									l++;
								}
							}
							char axy[10]; 
							sprintf(axy,"%d",newi);
							strcat(newbuf,axy);
							strcat(newbuf,"\0");
							sendto(sockfd,newbuf,1024,0,(struct sockaddr*)&servaddr,len);
						
						
						}
							
							
							
					
					if(chs==2) //VIEW CART
					{	char	atx[2];
							atx[0]='2';
							atx[1]='\0';
							sendto(sockfd,atx,1024,0,(struct sockaddr*)&servaddr,len);
						int m,n=0;
							char buf[100],data[100];
							for(m=2;sign_in[m]!='*';m++)
							{
							buf[n]=sign_in[m];
							n++;
							}
							buf[n]='\0';
							cout<<"\n CART of USER "<<buf<<endl;
							strcat(buf,"_d.txt");
						
							int f_d=open(buf,O_RDWR,O_APPEND);
							
		                  	read(f_d,data,1024);
							close(f_d);
							int cnt=3;
						
							cout<<"\n PRODUCT NAME   PRICE\n ";
					    		
							for(i=0;data[i]!='*';i++);
							i++;
							cout<<"\n 1)"	;
							nom=2;
							int prce=1,space=1;
							for(;data[i]!='*';i++)
							{
								cout<<data[i];
								if(prce==1&&data[i+1]=='*')
								{	if(space==1)
									{
										cout<<"     ";
										space=0;
									}
									for(j=i+2;data[j]!='*';j++)
									cout<<data[j];
									prce=0;
								}
							}
							prce=1;
							space=0;
							cnts=0;
							for(;data[i]!='\0';i++)
							{
								if(data[i]=='*')
								{
									cnts++;
									if(cnts%3==0)
									{
									prce=1;
									cout<<"\n\n "<<nom<<")";
									nom++;
									}
								}
									if(cnts%3==0&&data[i]!='*')
									{
									cout<<data[i];	
										if(prce==1&& data[i+1]=='*')
								{	if(space=1)
									{
										cout<<"     ";
										space=0;
									}
									for(j=i+2;data[j]!='*';j++)
									cout<<data[j];
									prce=0;
								}
									}
							}
							char cho;
							int chu;
						 	printf("\n\nEnter PRODUCT NO in the CART to Manage     OR \n (y) Buy All the ITEMS IN CART \n (n) Remove All the ITEMS IN CART   ->  ");
						 	cin>>cho;
							if(cho=='y') 
							{
							printf("\n\n All the items in the CART Purchased Succesfully ! Thank You !");
						char newkfile[20];
						newkfile[0]='\0';
						strcat(newkfile,"cp /dev/null \0");
						strcat(newkfile,buf);
						system(newkfile);
							}
							if(cho=='n') 
							{
							printf("\n\n All the items in the CART Removed Succesfully ! Thank You !");
								char newkfile[20];
								newkfile[0]='\0';
								strcat(newkfile,"cp /dev/null \0");
								strcat(newkfile,buf);
								system(newkfile);
							}
							if(cho!='y'&&cho!='n')
							{
								printf("\n\n 1.BUY Item\n 2.REMOVE Item  -> ");
								cin>>chu;
								
								printf("\n OKAY  %d",chu);
								if(chu==1)
								{	chx=cho-'0';
									printf("\n TRANSACTION SUCCESFUL ! ");
									printf("\n Item Purchased Succesfully !");
									for(i=0,j=0;j<chx-1;i++)
									{	
									if(data[i]=='#') j++;
									}
									for(k=i;data[k]!='#';k++);
									char newdata[1024];
									int lk;
									for(j=0,lk=0;data[j]!='\0';j++)
									{
										if(!(j>=i&&j<=k))
										{
											newdata[lk]=data[j];
											lk++;
										}
									}
									char newkfile[20];
								newkfile[0]='\0';
								strcat(newkfile,"cp /dev/null \0");
								strcat(newkfile,buf);
								system(newkfile);
								int fd=open(buf,O_RDWR);
								write(fd,newdata,strlen(newdata));
								close(fd);
									
								}
								else
								{
									printf("\n\n Item Removed from CART Succesfully ! ");
									chx=cho-'0';
									
									for(i=0,j=0;j<chx-1;i++)
									{	
									if(data[i]=='#') j++;
									}
									for(k=i;data[k]!='#';k++);
									char newdata[1024];
									int lk;
									for(j=0,lk=0;data[j]!='\0';j++)
									{
										if(!(j>=i&&j<=k))
										{
											newdata[lk]=data[j];
											lk++;
										}
									}
									char newkfile[20];
								newkfile[0]='\0';
								strcat(newkfile,"cp /dev/null \0");
								strcat(newkfile,buf);
								system(newkfile);
								int fd=open(buf,O_RDWR);
								write(fd,newdata,strlen(newdata));
								close(fd);
								}
								
							}
							    
					
					}
					if(chs==3) //lOG OUT
					{		
						cout<<"LOGGED OUT SUCCESFULLY\nHAVE A GREAT DAY!!!\nGOOD BYE";
						exit(0);
					}
				}
				}
				if(bs=='S')
				{	
					
					while(1)
					{
						system("clear");
						n=recvfrom(sockfd,recvline1,1024,0,NULL,NULL);
					recvline1[n];
					printf("\nHEY THERE, %s !",recvline1);
			 	
					printf("\n 1. MANAGE INVENTORY \n 2. ADD ITEMS\n 3. LOG OUT  -> ");
					cin>>chs;
					if(chs==1)//MANAGE ITEMS
					{		char at[2];
							at[0]='1';
							at[1]='\0';
							sendto(sockfd,at,1024,0,(struct sockaddr*)&servaddr,len);
							n=recvfrom(sockfd,newbuf,1024,0,NULL,NULL);
							newbuf[n]=0;
							cout<<"\nYour Products ->\n";
							for(i=0;newbuf[i]!='*';i++);
							i++;
							cout<<"\n 1)"	;
							nom=2;
							
							for(;newbuf[i]!='*';i++)
							{
								cout<<newbuf[i];
							}
							cnts=0;
							for(;newbuf[i]!='\0';i++)
							{
								if(newbuf[i]=='*')
								{
									cnts++;
									if(cnts%3==0)
									{
									
									cout<<"\n "<<nom<<")";
									nom++;
									}
								}
									if(cnts%3==0&&newbuf[i]!='*')
									{
									 cout<<newbuf[i];	
									}
							}
							cout<<"\n\n | MANAGE ITEMS | Enter Product No -> ";
							scanf("%d",&chx);
							printf("\n\n 1. Remove Item\n 2. Change Price \n 3. Change Quantity -> ");
							scanf("%d",&chy);
							if(chy==1) printf("\nItem Removed SUCCESSFULLY");
							if(chy==2)
							{
								printf("\n Enter the NEW Price : ");
								scanf("%s",price);
								printf("\n Price changed SUCCESFULLY");
							}
							if(chy==3)
							{
								printf("\n Enter the NEW Quantity : ");
								scanf("%s",quantity);
								printf("\n Quantity Changed SUCCESFULLY");
							}
							for(i=0,j=0;j<chx-1;i++)
							{
								if(newbuf[i]=='#') j++;
							}
							cnts=0;
							newi=i;
							int lx;
							if(chy==1)
						
							{	removed[0]='$';
							for(k=0,l=0,lx=1;newbuf[k]!='\0';k++)
							{
								if(newbuf[k]=='#') cnts++;
								if(cnts!=chx-1)
								{
									newerbuf[l]=newbuf[k];
									l++;
								}
								else
								{
									removed[lx]=newbuf[k];
									lx++;
								}
							}
							newerbuf[l]='\0';
							removed[lx]='\0';
							if(newerbuf[0]=='#')
							{
								for(l=0;newerbuf[l+1]!='\0';l++)
								{
									newerbuf[l]=newerbuf[l+1];
								}
								newerbuf[l]='\0';
							}
							}
							
							cnts=0;
							if(chy==2)
							{
								for(;;i++)
								{
									if(newbuf[i]=='*')cnts++;
									if (cnts==2) break;
								}
								i++;
								l=0;
								for(;newbuf[i]!='*';i++)
								{
									newbuf[i]=price[l];
									l++;
								}
							
							}
							if(chy==3)
							{
								for(;;i++)
								{
									if(newbuf[i]=='*')cnts++;
									if (cnts==3) break;
								}
								i++;
								l=0;
								for(;newbuf[i]!='#';i++)
								{
									newbuf[i]=quantity[l];
									l++;
								}
									
							}
							char axy[10]; 
							sprintf(axy,"%d",newi);
							
							if(chy==1) 
							{
							strcat(newerbuf,axy);
							strcat(newerbuf,"\0");
							strcat(newerbuf,removed);
						//	printf("\n%s",newerbuf);
							sendto(sockfd,newerbuf,strlen(newerbuf),0,(struct sockaddr*)&servaddr,len);		
							}
							else
							{		
							strcat(newbuf,axy);
							strcat(newbuf,"\0");
						//	printf("\n%s",newbuf);
						    sendto(sockfd,newbuf,1024,0,(struct sockaddr*)&servaddr,len);
						
						}				
					}
					if(chs==2)
					{
					sellsome[0]='2';
					strcat(sellsome,"*\0");	
					sellsomething(sellsome);
					len=sizeof(servaddr);
					sendto(sockfd,sellsome,1024,0,(struct sockaddr*)&servaddr,len);
					cout<<"\n Succefully Added ";
					
					}
					if(chs==3)
					{	
						cout<<"\n\n LOGGED OUT SUCCESFULLY\n HAVE A GREAT DAY!!!\nGOOD BYE";
						exit(0);
					}
				}
				}						
		}
		
///////////////

	}	
return 0;
}
