#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <time.h>
#include <string.h>
#include <netdb.h>

struct cookies
{
  	int 	flg;
 	char 	data[200];
}; 

struct cookies clist[50];	//Created structure to hold 50 Fortune cookies data and the usage flag.   

void *server_for_fortune_cookie_service();
void *server_for_encription_decription_service();

int main(int agrc, char *argv[])
{
  	pthread_t 	ser1, ser2;
  	char 		buf[200];
  	FILE 		*f;
  	int 		i;

  	f = fopen("50FortuneCookies.txt", "r");		
  	if(f)
    	{
      		i = 0;
		//Read Fortune cookie file and save in structure.
      		while(fgets(buf,200, f) != NULL)	
			{
	  		strcpy(clist[i].data,buf);
	  		clist[i].flg = 0;
	  		i++;
			}
    	}
  	else
    	{
      		perror("Unable to Open Fortune Cookie File.\n"); 
	      	fclose(f);
      		exit(-1);
    	}

  	fclose(f);
	

	// Started two thread to keep both server working parallay.
  	pthread_create(&ser1, NULL, server_for_fortune_cookie_service, NULL);	
  	pthread_create(&ser2, NULL, server_for_encription_decription_service, NULL);

  	pthread_join(ser1, NULL);
  	pthread_join(ser2, NULL);
  
	return(0);
} 

void *server_for_fortune_cookie_service()
{
	/** 	This function creates and listen on Fortune cookie server socket and runs in Itterative mode.
		It will read the number of cookies that client as requested and returns that number of random cookies.**/

  	int 	ser_sock, cli_sock, sock_len, dumm_ret, fid, i, r_pos, read_flag, rem_c;
  	struct sockaddr_in 	ser_addr, cli_addr;
  	char 	num_c[2], ind[3], message[2048];
	
	// Creating socket for Fortune cookie Server.
  	ser_sock = socket(AF_INET, SOCK_STREAM, 0);
  	if(ser_sock < 0)
    	{
      		perror("Unable to create Fortune Cookie server socket.\n");
      		exit(0);
    	}
  	bzero((char *) &ser_addr, sizeof(ser_addr)); 
   
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	// Port 5005 is reseverd for Fortune Cookie server.
	ser_addr.sin_port = htons(5005);

	sock_len = sizeof(ser_addr);
	dumm_ret = bind(ser_sock, (struct sockaddr *) &ser_addr, sock_len);
	if(dumm_ret < 0)
    	{
		perror("Unable to Bind to Fortune Cookie Server socket.\n");
		close(ser_sock);
		exit(0);
    	}

  	dumm_ret = listen(ser_sock, 5);
  	if(dumm_ret < 0)
    	{
	      perror("Unable to Listen on Fortune Cookie server socket.\n");
	      close(ser_sock);
	      exit(0);
    	}
	printf("\nFortune Cookie Server is running!!!\n");

	for(;;)
    	{
		sock_len = sizeof(cli_addr);
		cli_sock = accept(ser_sock,(struct sockaddr *) &cli_addr, &sock_len);
		if(cli_sock < 0)
		{
			perror("Unable to accept on Fortune Cookie server socket.\n");
			close(ser_sock);
			exit(0);
		}
		rem_c = 0;

		bzero((char *) &message, sizeof(message)); 	  
		read(cli_sock, num_c, 1);	//Accept Number of cookies.
		srand(time(NULL));
		// Check for cookies availability.
		for(i = 0; i<50; i++)
		{
			if(clist[i].flg == 0)
			{ 
				rem_c++;
			}
		}
		
		if(rem_c < atol(num_c))
		{
			strcat(message, "Insufficient Cookies to process request! Available Cookies : ");
			sprintf(ind, "%d.\n", rem_c);
			strcat(message, ind);
			write(cli_sock, message, sizeof(message));
			close(cli_sock);
    		}  	
		else
		{
			//Generate Random number of cookies.				
			for(i = 1; i <= atol(num_c); i++)
			{
				read_flag = 0;
				while(read_flag == 0)
				{
					r_pos = rand() % 50;
					if(clist[r_pos].flg == 0)
					{
						sprintf(ind, "%d. ", i);
						strcat(message, ind);
						strcat(message, clist[r_pos].data);
						clist[r_pos].flg = 1;
						read_flag = 1;
					}	
		    		}
			}
			//Send Cookies to Client.
			write(cli_sock, message, sizeof(message));
			close(cli_sock);
		}
    	}  
}

void *server_for_encription_decription_service()
{
	/** 	This function creates and listen on Encription Decription Server socket and runs in Concurrent mode.
		It will thru loop read and write operations till client notifies to close.
	 	It encypts and decryts the message send by client usnig shift by 4 ASSCI logic.**/


	int ser_sock, cli_sock, sock_len, dumm_ret, fid, i, n;
	struct sockaddr_in ser_addr, cli_addr;
	char opt[2];
	char temp;	

	char message[2048];
	// Creating socket for Encription Decription Server.
	ser_sock = socket(AF_INET, SOCK_STREAM, 0);
	if(ser_sock < 0)
	{
		perror("Unable to create E/D server socket.\n");
		exit(0);
	}
	bzero((char *) &ser_addr, sizeof(ser_addr)); 

	ser_addr.sin_family = AF_INET;
	ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	// Port 5010 is reseverd for Encription Decription server.
	ser_addr.sin_port = htons(5010);

	sock_len = sizeof(ser_addr);
	dumm_ret = bind(ser_sock, (struct sockaddr *) &ser_addr, sock_len);
	if(dumm_ret < 0)
	{
		perror("Unable to Bind to E/D Server socket.\n");
		close(ser_sock);
		exit(0);
	}

	dumm_ret = listen(ser_sock, 5);
	if(dumm_ret < 0)
	{
		perror("Unable to Listen on E/D server socket.\n");
		close(ser_sock);
		exit(0);
	}
	printf("\nEncription Decription Server is running!!!\n");

	for(;;)
	{
		sock_len = sizeof(cli_addr);
		// Accepting connections..
		cli_sock = accept(ser_sock,(struct sockaddr *) &cli_addr, &sock_len);
		if(cli_sock < 0)
		{
			perror("Unable to Connect to E/D server socket.\n");
			close(ser_sock);
			exit(0);
		}
		//Every Accepted Connection for ED server is forked into seprate process.
		fid = fork();
		if(fid == 0)
		{
			close(ser_sock);	//Close Old Socket in Child Process.
			for(;;)
			{
				bzero((char *) &opt, sizeof(opt));
				// Accept mode request from client to switch between Encryption and Decryption mode. 	  
				read(cli_sock, opt, 1);

				switch(atol(opt))
				{
					case 1:
						bzero((char *) &message, sizeof(message)); 
						//Accept message to be Encrypt..	  
						read(cli_sock, message, sizeof(message));
						n = strlen(message);
						for(i = 0; i< n; i++)
						  message[i] += 4;
						message[n] = '\0';
						//Return Encrypted message..	  
						write(cli_sock, message, sizeof(message));
						break;
					case 2:
						bzero((char *) &message, sizeof(message)); 	  
						//Accept message to be Decrypt..		
						read(cli_sock, message, sizeof(message));
						n = strlen(message);
						for(i = 0; i< n; i++)
						  message[i] -= 4;
						message[strlen(message)] = '\0';
						//Return Decrypted message..
						write(cli_sock, message, sizeof(message));
						break;
					case 3:
						close(cli_sock);
						exit(0);
					deafult :
						break;
				}
			}
		}
		else
		{
			//Close accepted socket from parent process so that it can accept next connect request.
			close(cli_sock);
		}  
	}  
}



