#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<netdb.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<dirent.h>
#include<fcntl.h>
#include<iostream>
//#include<process.h>
using namespace std;
int substr(char *str,char *search)
{
    int count1 = 0, count2 = 0, i, j, flag,posn=0;


    while (str[count1] != '\0')
        count1++;
    while (search[count2] != '\0')
        count2++;
    for (i = 0; i <= count1 - count2; i++)
    {
        for (j = i; j < i + count2; j++)
        {
            flag = 1;
            if (str[j] != search[j - i])
            {
                flag = 0;
                break;
            }
        }
        if (flag == 1)
          { posn=i;  break;}
    }
    if (flag == 1)
     return posn;  
    else
      return -1;
}


int main(int argc,char **argv)
{
	int sockfd,k;
	int n,lmao;
	system("clear");
	cout<<" \n WELCOME ADMINISTRATOR !!";
	char bufp[10],newi[10],removed[100],tomodify[1024],search[100];
	char op;
	char strs[1024];
	char strn[1024];
	char pass[10],msx1[1024],msx2[1024];
	socklen_t len;
	char msg[1024],ans[1024];
	struct sockaddr_in servaddr,cliaddr;
	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	cout<<" \n\n SOCKET CREATED SUCCESSFULLY";
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=INADDR_ANY;
	servaddr.sin_port=htons(5035);
	bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	cout<<" \n\n SOCKET BINDED WITH ADDRESS SUCCESSFULLY";
	cout<<" \n\n CONNECTION ESTABLISHED SUCCESSFULLY\n";
	for(;;)
	{
  		len=sizeof(cliaddr);
			  		
		  n=recvfrom(sockfd,msg,1024,0,(struct sockaddr*)&cliaddr,  &len);
  			
		int i,j=0,fd=1; char file_name_i[15],file_name_d[15];
		char name[15],address[15],cardno[15],details[100];
  		puts(msg);
  		printf("\n%c",msg[0]);
  		printf("\n");
		  

	if(msg[0]=='1') // SIGN IN
   {
 			j=0;		
  		for(i=2;msg[i]!='*';i++)
  		{		
  			file_name_i[j]=msg[i];
  			file_name_d[j]=msg[i];
  			
			j++;
		}
		printf("\nSIGN IN REQUEST\n");
		if(file_name_i[strlen(file_name_i)-1]!='t')
			strcat(file_name_i,"_i.txt\0");
		if(file_name_d[strlen(file_name_d)-1]!='t')
			strcat(file_name_d,"_d.txt\0");
		//cout<<file_name<<"\n";
	
  		if( access( file_name_i, F_OK ) != -1 ) {
    			// FILE EXISTS
    			ans[0]='5';
		  		ans[1]='\0';
		  	i++;
		  	j=0;
		  	//printf("%s\n",file_name);
		  	for(;msg[i]!='*';i++,j++) pass[j]=msg[i];
		  	j++; pass[j]='\0';
		  	fd=open(file_name_i,O_RDWR);
		  	read(fd,bufp,strlen(pass));
		  	close(fd);
		  	//puts(bufp);
		  	//puts(pass);
		  	if(!strcmp(pass,bufp)) ans[0]='1';
			
			} else 
			{
    		ans[0]='5';
    		ans[1]='\0';
		  		
			}			  	
       sendto(sockfd,ans,n,0,(struct sockaddr*)&cliaddr,len); 

    }
		if(msg[0]=='0') //SIGNUP
  		{	   
		   j=0;
				for(i=2;msg[i]!='*';i++)
  				{	
  					file_name_i[j]=msg[i];
  					file_name_d[j]=msg[i];
					j++;
				}
				j=0;
				i++;
		  		printf("\nSIGNUP REQUEST");
		  		j=0;
		  		for(i=6;msg[i]!='\0';i++,j++)
				  details[j]=msg[i];
				  j++;
				  details[j]='\0';	  
  				if(file_name_i[strlen(file_name_i)-1]!='t')
					strcat(file_name_i,"_i.txt\0");
				if(file_name_d[strlen(file_name_d)-1]!='t')
					strcat(file_name_d,"_d.txt\0");	
  				//printf("\n\n File Name :%s",file_name);
  				if( access( file_name_i, F_OK ) != -1 ) {
    					// file exists
    					ans[0]='1';
		  				ans[1]='\0';
			
					} 
					else 
					{
    				// FILE DOESN'T EXIST
					creat(file_name_d,S_IRUSR | S_IWUSR | S_IWGRP | S_IRGRP  );
					fd=creat(file_name_i,S_IRUSR | S_IWUSR | S_IWGRP | S_IRGRP  );
					write(fd,details,strlen(details));
					close(fd);
						ans[0]='5';
		  				ans[1]='\0';
					}
  					sendto(sockfd,ans,n,0,(struct sockaddr*)&cliaddr,len);
		}
	// END OF SIGNUP AND SIGN IN with file_name as FILE TO BE OPENED
	int ln;
	char buff[100],msg1[1024],msg2[1024],msg3[1024],bufkr[100],bufdep[100];
	
	while(1)
	{
	
	if(file_name_i[0]=='S') //SELLER
	{	
		
		fd=open(file_name_i,O_RDWR);
		read(fd,buff,sizeof(buff));
		close(fd);
		puts(buff);
		for(i=0;buff[i]!='*';i++);
		i++;
		for(j=0;buff[i]!='*';i++,j++)  name[j]=buff[i];
	
		j++; name[j]='\0';
		cout<<" REQUEST BY : "<<name;
		sendto(sockfd,name,n,0,(struct sockaddr*)&cliaddr,len);//sends back the name of the seller
		
		n=recvfrom(sockfd,msg1,1024,0,(struct sockaddr*)&cliaddr,  &len);
		if(msg1[0]=='1')//manage itenm
		{	char prod[15],price[10];
			char hbuff[1024],depbuff[1024];
			fd=open(file_name_d,O_RDWR);
			read(fd,hbuff,sizeof(hbuff));
			close(fd);
			int z=0;
			puts(hbuff);
			sendto(sockfd,hbuff,n,0,(struct sockaddr*)&cliaddr,len);
			n=recvfrom(sockfd,msx1,1024,0,(struct sockaddr*)&cliaddr,  &len);
			int xy1=999;//$ position
		//	msx1[n]=0;
			for(i=0,j=0;msx1[i]!='\0';i++)
			{
				if(msx1[i]=='#')
				{
				  j=z;
				  z=i;
			}
			
				if(msx1[i]=='$') xy1=i;	
			}
			if(xy1==999)
			{
					
			for(i=z+1,k=0;msx1[i]!='\0';i++,k++)
			newi[k]=msx1[i];
			newi[k]='\0';
			}
			else
			{
			
			for(i=j+1,k=0;msx1[i]!='\0';i++,k++)
			newi[k]=msx1[i];
			newi[k]='\0';
		}
			for(i=0;i<=j;i++)
			msx2[i]=msx1[i];
			msx2[i]='\0';
			cout<<msx2;
			int qr;
			int xy; char depart[20];
			if(xy1!=999)
			{
			
			for(i=xy1+1,qr=0;msx1[i]!='\0';i++)
			{
			if(msx1[i]!='#')
			{
					
			removed[qr]=msx1[i];
			qr++;
			}
			removed[i]='\0';
			}
		}
			xy=atoi(newi);//returns the position of dirty area
			printf("\n%d\n",xy);
			if(xy1==999)
			{
			
			for(i=0,j=xy;msx2[j]!='*';j++,i++)
				depart[i]=msx2[j];
		   
		   	depart[i]='\0';
			}
			else
			{
				for(i=0,qr=0;removed[i]!='*';i++,qr++)
				depart[qr]=removed[i];
				depart[qr]='\0';
			}
			cout<<depart;
		    // open department file and edit. use filename as an index to search & replace
		    if(xy1==999)//if price or quantity modified
		    {
		    	strcat(depart,".txt\0");
		    	fd=open(depart,O_RDWR);
		    	read(fd,tomodify,1024);
		    	close(fd);
		    	cout<<tomodify;
		    	char temp[100];
		    	search[0]='\0';
		    	strcat(search,file_name_d);
		    	strcat(search,"*");
		    	for(i=xy+1;msx1[i]!='*';i++);
		    	i++;
				for(j=0;msx1[i]!='*';i++,j++)
		    	{
		    		temp[j]=msx1[i];
				}
				temp[j]='\0';
				strcat(search,temp);
				cout<<"\n Search String for DEPARTMENT :\n"<<search<<"\n";
		    	int si=substr(tomodify,search);
		    	cout<<" Initial Index of Dirty Area :\n"<<si<<"\n";
		    	for(j=xy+1;msx1[j]!='*';j++);
		    	for(i=si;tomodify[i]!='*';i++);
		    	cout<<"\n End Index of Dirty Area : "<<i<<"\n"<<j;
		    	for(;tomodify[i]!='#';i++,j++)
		    	{
		    		tomodify[i]=msx1[j];
				}
				
					char newfile[20];
				newfile[0]='\0';
				strcat(newfile,"cp /dev/null \0");
				strcat(newfile,depart);
				system(newfile);
				fd=open(depart,O_RDWR);
		    	write(fd,tomodify,strlen(tomodify));
		    	close(fd);
		    	
			}
		    else//if removed
		    {	cout<<"\n $ "<<xy1<<endl;
		    	cout<<msx1<<endl;
				char modus[1024];
		   strcat(depart,".txt\0");
		    	fd=open(depart,O_RDWR);
		    	read(fd,tomodify,1024);
		    	close(fd);
		    	cout<<tomodify;
		    	strcat(tomodify,"\0");
		    	char temp[100];
		    	search[0]='\0';
		    	strcat(search,file_name_d);
		    	strcat(search,"*");
		    	for(i=xy1+2;msx1[i]!='*';i++);
		    	i++;
				for(j=0;msx1[i]!='*';i++,j++)
		    	{
		    		temp[j]=msx1[i];
				}
				temp[j]='\0';
				strcat(search,temp);
				cout<<"\n SEARCH STRING :\n"<<search<<"\n";
		    	int si=substr(tomodify,search);
		    	cout<<"\n Initial Index of Dirty Area : \n"<<si<<"\n";
				int si2;
			    for(si2=si+1;tomodify[si2]!='#';si2++);
			    cout<<endl<<si<<endl<<si2;
		    //	cout<<"\nbodse dk "<<i<<"\n"<<j;
		    	for(i=0,j=0;tomodify[i]!='\0';i++)
		    	{	cout<<i<<endl;	
				if(!(i>=si&&i<=si2))
		    		{
		    			modus[j]=tomodify[i];
		    			j++;
					}
				}
				modus[j]='\0';
				cout<<"\n Modified Array to be written into DEPARTMENT  "<<modus;
				
					char newfile[20];
				newfile[0]='\0';
				strcat(newfile,"cp /dev/null \0");
				strcat(newfile,depart);
				system(newfile);
				
				fd=open(depart,O_RDWR);
		    	write(fd,modus,strlen(modus));
		    	close(fd);
					
			}
			cout<<xy<<endl;
			printf("\nk\n%s",msx2);
			printf("\n%s",file_name_d);
			char newfile[20];
			newfile[0]='\0';
			strcat(newfile,"cp /dev/null \0");
			strcat(newfile,file_name_d);
			system(newfile);
			cout<<"\n Array to be written into User File  "<<msx2;
			fd=open(file_name_d,O_RDWR);
			write(fd,msx2,strlen(msx2));
			close(fd);
			
			
		}
		if(msg1[0]=='2')			//add item to sell

		{
			char prod[15],price[10],quantity[15],depart[15],file[100];
			for(i=0;msg1[i]!='\0';i++)printf("%c",msg1[i]);
			cout<<endl;
			for(i=2,j=0;msg1[i]!='*';i++,j++)
			depart[j]=msg1[i];
			j++; depart[j]='\0'; i++;
			cout<<depart<<strlen(depart)<<endl;
		
			for(j=0;msg1[i]!='*';i++,j++)
			prod[j]=msg1[i];
			j++; prod[j]='\0'; i++;
			cout<<prod;
			strcat(bufdep,file_name_d);
			strcpy(file,file_name_d);
		    strcat(bufdep,"*");
			strcat(bufdep,prod);
			strcat(bufdep,"*");
			puts(prod);
			puts(prod);
			for(j=0;msg1[i]!='*';i++,j++)
			price[j]=msg1[i];
			j++; price[j]='\0'; i++;
			strcat(bufdep,price);
			strcat(bufdep,"*");
			
			
			for(j=0;msg1[i]!='*';i++,j++)
			quantity[j]=msg1[i];
			j++; quantity[j]='\0'; i++;
			cout<<quantity<<strlen(quantity)<<endl;
			strcat(bufdep,quantity);
			strcat(bufdep,"#\0");
				puts(quantity);
				puts(quantity);
			for(i=2,j=0;msg1[i]!='\0';i++,j++) {
			bufkr[j]=msg1[i];
			cout<<msg1[i];
			cout<<bufkr[j];
		}
			strcat(bufkr,"#\0");
			cout<<endl;
			puts(file);
			fd=open(file,O_RDWR|O_APPEND);
			write(fd,bufkr,strlen(bufkr));
			close(fd);
			 cout<<endl<<bufkr<<endl;
			 cout<<endl<<bufdep;
			// printf("\nwhy");
			 
			 //printf()
			
		
			strcat(depart,".txt\0");
			fd=open(depart,O_RDWR|O_APPEND);
			write(fd,bufdep,strlen(bufdep));
			close(fd);
			
			

	
		}
		
	}
	else 
	if(file_name_i[0]=='B') //BUYER
	{
		fd=open(file_name_i,O_RDWR);
		read(fd,buff,sizeof(buff));
		close(fd);
		puts(buff);
		for(i=0;buff[i]!='*';i++);
		i++;
		for(j=0;buff[i]!='*';i++,j++)  name[j]=buff[i];
	
		j++; name[j]='\0';
		puts(name);
		sendto(sockfd,name,n,0,(struct sockaddr*)&cliaddr,len);//sends back the name of the buyer
		
		n=recvfrom(sockfd,msg1,1024,0,(struct sockaddr*)&cliaddr,  &len);
		cout<<endl<<"number of bytes  "<<n<<msg1<<endl;
		if(msg1[0]=='1')//browse items from department
		{	char prod[15],price[10];
			char dept[100];
			char depart[100];
			char hbuff[1024];
			dept[0]='\0';
			printf("\n Options Input Recd : %c\n",msg[1]);
			if(msg1[1]=='1') strcat(dept,"ELECTRONICS.txt\0");
			if(msg1[1]=='2') strcat(dept,"BOOKS.txt\0");
			if(msg1[1]=='3') strcat(dept,"MOVIES.txt\0");
			if(msg1[1]=='4') strcat(dept,"GAMES.txt\0");
			fd=open(dept,O_RDWR);
			read(fd,hbuff,sizeof(hbuff));
			close(fd);
			printf("\n File Closed");
			puts(hbuff);
			sendto(sockfd,hbuff,n,0,(struct sockaddr*)&cliaddr,len);
			n=recvfrom(sockfd,msx1,1024,0,(struct sockaddr*)&cliaddr,  &len);
			int xy1=999;//$ position
		//	msx1[n]=0;
			for(i=0,j=0;msx1[i]!='\0';i++)
			{
				if(msx1[i]=='#')
				j=i;
			}//j  gives the position of the dirty area sent in msx1  data#data#29
			
			for(i=j+1,k=0;msx1[i]!='\0';i++,k++)
			newi[k]=msx1[i];
			newi[k]='\0';
			for(i=0;i<=j;i++)
			msx2[i]=msx1[i];
			msx2[i]='\0';
			cout<<msx2;
			int qr;
			int xy;// char depart[20];
			xy=atoi(newi);//returns the position of dirty area
			printf("\n%d\n",xy);
		
			char sellerfile[100];
			for(i=0,j=xy;msx2[j]!='*';j++,i++)
				sellerfile[i]=msx2[j];
		   		sellerfile[i]='\0';
			cout<<"\n Seller File Name : "<<sellerfile;
		   
		    
		    
		    	fd=open(sellerfile,O_RDWR);
		    	read(fd,tomodify,1024);
		    	close(fd);
		    	cout<<"\n Contents of Seller Module File :  "<<tomodify;
		    	char temp[100];
		    	search[0]='\0';
		    	for(i=0;dept[i]!='.';i++)
				depart[i]=dept[i];
		    	strcat(search,depart);
		    	strcat(search,"*");
		    	for(i=xy+1;msx1[i]!='*';i++);
		    	i++;
				for(j=0;msx1[i]!='*';i++,j++)
		    	{
		    		temp[j]=msx1[i];
				}
				temp[j]='\0';
				strcat(search,temp);
				cout<<"\n String to be searched in Dept : "<<search;
		    	int si=substr(tomodify,search);
		    
		    	for(j=xy+1;msx1[j]!='*';j++);
		    	for(i=si;tomodify[i]!='*';i++);
		    
		    	for(;tomodify[i]!='#';i++,j++)
		    	{
		    		tomodify[i]=msx1[j];
				}
				
					char newkfile[20];
				newkfile[0]='\0';
				strcat(newkfile,"cp /dev/null \0");
				strcat(newkfile,dept);
				system(newkfile);
				fd=open(sellerfile,O_RDWR);
		    	write(fd,tomodify,strlen(tomodify));
		    	close(fd);
		    	
			
		   
			cout<<xy<<endl;
		
			printf("\nWriting into %s",dept);
			char newfile[20];
			newfile[0]='\0';
			strcat(newfile,"cp /dev/null \0");
			strcat(newfile,file_name_d);
			//system(newfile);
			cout<<"\n msx2  "<<msx2;
			cout<<"\n depart "<<dept;
			fd=open(dept,O_RDWR);
			write(fd,msx2,strlen(msx2));
			close(fd);
			
			
		}
		if(msg1[0]=='2')			

		{cout<<"\nEntering the Cart\n";
		 cout<<"\n CART TRANSACTIONS SUCCESSFUL";
		/*
			char prod[15],price[10],quantity[15],depart[15],file[100];
			for(i=0;msg1[i]!='\0';i++)printf("%c",msg1[i]);
			cout<<endl;
			for(i=2,j=0;msg1[i]!='*';i++,j++)
			depart[j]=msg1[i];
			j++; depart[j]='\0'; i++;
			cout<<depart<<strlen(depart)<<endl;
		
			for(j=0;msg1[i]!='*';i++,j++)
			prod[j]=msg1[i];
			j++; prod[j]='\0'; i++;
			cout<<prod;
			strcat(bufdep,file_name_d);
			strcpy(file,file_name_d);
		    strcat(bufdep,"*");
			strcat(bufdep,prod);
			strcat(bufdep,"*");
			puts(prod);
			puts(prod);
			for(j=0;msg1[i]!='*';i++,j++)
			price[j]=msg1[i];
			j++; price[j]='\0'; i++;
			strcat(bufdep,price);
			strcat(bufdep,"*");
			
			
			for(j=0;msg1[i]!='*';i++,j++)
			quantity[j]=msg1[i];
			j++; quantity[j]='\0'; i++;
			cout<<quantity<<strlen(quantity)<<endl;
			strcat(bufdep,quantity);
			strcat(bufdep,"#\0");
				puts(quantity);
				puts(quantity);
			for(i=2,j=0;msg1[i]!='\0';i++,j++) {
			bufkr[j]=msg1[i];
			cout<<msg1[i];
			cout<<bufkr[j];
		}
			strcat(bufkr,"#\0");
			cout<<endl;
			puts(file);
			fd=open(file,O_RDWR|O_APPEND);
			write(fd,bufkr,strlen(bufkr));
			close(fd);
			 cout<<endl<<bufkr<<endl;
			 cout<<endl<<bufdep;
			// printf("\nwhy");
			 
			 //printf()
			
		
			strcat(depart,".txt\0");
			fd=open(depart,O_RDWR|O_APPEND);
			write(fd,bufdep,strlen(bufdep));
			close(fd);
	*/	}
	}
}

}
return 0;
}
