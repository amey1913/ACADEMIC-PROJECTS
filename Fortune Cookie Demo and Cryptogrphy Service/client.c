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

void request_fortune_cookies(char *ar);
void request_encryption_decryption_service(char *ar);

int main(int argc, char *argv[])
{
	int opt;
	// Check if client is passing the connect to server IP Address in Command Line argument. 	
	if(argc != 2)
	{
		perror("Server IP adress is not found! Cannot Continue.\n");
		exit(-1);
	}

	printf("\n\n \t\t...... Welcome......\n\n");
	while(1)
	{
		//Asks User for various options to choose
		printf("\nChoose 1. Fortune Cookies\t2. Encryption/Decryption Service.\t3. Exit\t:"); 
		scanf("%d", &opt);
		switch(opt)
		{
			// Fortune Cookie Service
			case 1: 
				request_fortune_cookies(argv[1]);
				break;
			// Encrypton Decryption Service
			case 2: 
				request_encryption_decryption_service(argv[1]);
				break;
			// Exit
			case 3:
				printf("\nIt was a pleasure working with you! Have a Greate Day!\n\n"); 
				return(0);
			default:
				printf("Incorrect Choice!\n");
				break;
		}
	}
	return(0);
}

void request_fortune_cookies(char *ar)
{
	/* This function will request the server to generate the fortune cookies for the user.
	   And prints the output to the User. */ 

	int 	ser_sock, cli_sock, ser_len, dumm_ret,num_cookies, ret;
	struct 	sockaddr_in ser_addr;
	char 	opt[2], message[2048];

	//Creates the Fortune cookies Server Socket
	ser_sock = socket(AF_INET, SOCK_STREAM, 0); 

	if(ser_sock < 0)
	{
		perror("Unable to create server socket.\n");
		exit(0);
	}

	bzero((char *) &ser_addr, sizeof(ser_addr));
	bzero((char *) &message, sizeof(message));

	ser_addr.sin_family = AF_INET;

	if(inet_aton(ar, &ser_addr.sin_addr.s_addr) <= 0)
	{
		perror("Unable to Convert Server Address.\n");
		exit(0);	
	}   
	ser_addr.sin_port = htons(5005);

	ser_len = sizeof(ser_addr);

	//Connects the Fortune cookies Server
	dumm_ret = connect(ser_sock,(struct sockaddr *) &ser_addr, ser_len); 
	
	if(dumm_ret < 0) 
	{ 
		perror("Unable to Connect to server socket.\n");
		exit(0);
	}  

	printf("Enter number of fortune cookies would you like to have.\n(Maximum Limit is 5 cookies!)\n");
	scanf("%d", &num_cookies);
	if((num_cookies > 0) && (num_cookies < 6))
	{ 
		sprintf(opt, "%d", num_cookies); 

		if((ret = write(ser_sock, opt, 1)) < 0)
		{
			perror("Unable to Write to server socket.\n");
			close(ser_sock);	
			exit(0);
		}

		if((ret = read(ser_sock, message, sizeof(message))) < 0)
		{
			perror("Unable to Write to server socket.\n");
			close(ser_sock);	
			exit(0);
		}

		printf("Here are your Fortune Cookies:\n\n%s", message);
	}
	else
	{	
		printf("Unable to process requested number of fortune cookies!\n"); 
	}
	close(ser_sock);
}

void request_encryption_decryption_service(char *ar)
{
	/* This function will request the server to either encrypt or decrypt 
	   the message based on option selected by a user */

	int 	ser_sock, cli_sock, ser_len, dumm_ret, option, n, ret, i;
	struct 	sockaddr_in ser_addr;
	char 	message[2048], opt[2];

	// Creates the Encryption/Decryption Server socket
	ser_sock = socket(AF_INET, SOCK_STREAM, 0);

	if(ser_sock < 0)
	{
		perror("Unable to create server socket.\n");
		exit(0);
	}

	bzero((char *) &ser_addr, sizeof(ser_addr));
	bzero((char *) &message, sizeof(message));

	ser_addr.sin_family = AF_INET;
	if(inet_aton(ar, &ser_addr.sin_addr.s_addr) <= 0)
	{
		perror("Unable to Convert Server Address.\n");
		exit(0);	
	}
	ser_addr.sin_port = htons(5010);

	ser_len = sizeof(ser_addr);

	// Connects to the Encryption/Decryption Server 
	dumm_ret = connect(ser_sock,(struct sockaddr *) &ser_addr, ser_len);
	if(dumm_ret < 0) 
	{ 
		perror("Unable to Connect to server socket.\n");
		exit(0);
	}  
	while(1)
	{
		bzero((char *) &opt, sizeof(opt));

		printf("\nChoose 1. Encryption\t2. Decryption\t3. Exit:");
		scanf("%d", &option);
		sprintf(opt, "%d", option); 
		write(ser_sock, opt, 1);
		switch(option)
		{
			// Encryption Mode
			case 1:
				bzero((char *) &message, sizeof(message));
				printf("Enter the Text you want to Encrypt:\n");	
				fgetc(stdin);  
				fgets(message, sizeof(message), stdin);  

				write(ser_sock, message, sizeof(message));

				bzero((char *) &message, sizeof(message));

				ret = read(ser_sock, message, sizeof(message));

				printf("Encrypted String: %s\n",message);
				break;
			//Decryption Mode
			case 2:
				bzero((char *) &message, sizeof(message));
				printf("Enter the Text you want to Decrypt:\n");
				fgetc(stdin);  
				fgets(message, sizeof(message), stdin);	  
				
				write(ser_sock, message, sizeof(message));

				bzero((char *) &message, sizeof(message));

				ret = read(ser_sock, message, sizeof(message));
				 
				printf("Decrypted String: %s\n",message);
				break;
			//stop
			case 3:
				close(ser_sock);
				return;
			default:
				printf("Incorrect Choice!\n");
				break;
		}
	}
}

