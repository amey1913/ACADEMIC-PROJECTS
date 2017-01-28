/*Name : Ha Vu
* Date : 03/05/2016
*
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <pthread.h>

#define MAXLINE 4096 /*max text line length*/
#define MAX_CHARATER 10000

#define SHUTDOWN 900 //shut

int DEBUG = 2;

int LOGOFF_USER = 1;

void handleShutdown(char *buffer); //shur

void shutdown_server(char *buffer); //shut

void * sendEmailCalendar(void *vptr);

void error(char *msg)
{
	perror(msg);
	exit(0);
}

/*GLOBAL VARIABLES BEGIN*/

char CMD_SHUTDOWN[] = "CMD_SHUTDOWN"; //shut

char USER_ID[3] = "000";

char temp[MAX_CHARATER] ; //hold temporary string

int sockfd, portno, n, client_mode;
struct sockaddr_in serv_addr;
struct hostent *server;
int checkEmailCalendar_t_ID = 0;
int sendEmailCalendar_t_ID = 0;
int user_id ;
const char delimiter[2] = "~";
char *token;

/*GLOBAL VARIABLES END*/

int main(int argc, char *argv[])
{
	pthread_t checkEmailCalendar_t, sendEmailCalendar_t;
	if (argc < 3) {
		fprintf(stderr, "usage %s hostname port\n", argv[0]);
		exit(0);
	}
	portno = atoi(argv[2]);

	server = gethostbyname(argv[1]);
	if (server == NULL) {
		fprintf(stderr, "ERROR, no such host\n");
		exit(0);
	}
	bzero((char *)&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr,
		(char *)&serv_addr.sin_addr.s_addr,
		server->h_length);
	serv_addr.sin_port = htons(portno);

	if (DEBUG > 1)
	{
		printf("Main thread.\n");
		printf("Port number : %u", 1);
		printf("Socketfd :  %u", 1);
	}

	pthread_create(&sendEmailCalendar_t, NULL, sendEmailCalendar, NULL);
	sendEmailCalendar_t_ID = sendEmailCalendar_t;

	pthread_join(sendEmailCalendar_t_ID, NULL);

	if (DEBUG > 0)
	{
		printf("After Main thread.\n");
		printf("Port number : %u", 1);
		printf("Socketfd :  %u", 1);
	}

	return 0;
}

void * sendEmailCalendar(void *vptr)
{
	if (DEBUG > 0)
	{
		printf("sendEmailCalendar: ");
		printf("%u\n", pthread_self());
	}
	char buffer[MAX_CHARATER];
	char message[MAX_CHARATER];

	int printEmail = 1;
	int sockfd, command_code, option;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		error("ERROR opening socket");
	if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
		error("ERROR connecting");

	/*Clear buffer before each message sent*/
	memset(&buffer[0], 0, sizeof(buffer));
	memset(&message[0], 0, sizeof(message));

	shutdown_server(buffer);
	
	/*Sending message to server	*/
	n = send(sockfd, buffer, strlen(buffer), 0);

	if (n < 0)
		error("ERROR writing to socket");

	if (DEBUG > 0)
	{
		printf("This message was sent.\n");
		printf("%s\n", buffer);
	}

	/*Message receive from server	*/

	memset(&buffer[0], 0, sizeof(buffer));
	recv(sockfd, buffer, MAXLINE, 0);
	
	if (n < 0)
		error("ERROR reading from socket");
	if (DEBUG > 1)
	{
		printf("This message was received.\n");
		printf("%s\n", buffer);
	}
	
	handleShutdown(buffer);

	pthread_exit(NULL);
}


void trimwhitespace(char *str)
{
	char *end;

	// Trim leading space
	while (isspace(*str)) str++;

	if (*str == 0)  // All spaces?
	{
		return;
	}

	// Trim trailing space
	end = str + strlen(str) - 1;
	while (end > str && isspace(*end)) end--;

	// Write new null terminator
	*(end + 1) = 0;


}
void strCatMessage(char *buffer, char *message)
{
	trimwhitespace(message);
	strcat(buffer, "~");
	strcat(buffer, message);
	memset(&message[0], 0, sizeof(message));
}

void shutdown_server(char *buffer)
{
	memset(&buffer[0], 0, sizeof(buffer));
	trimwhitespace(USER_ID);
	strcat(buffer, CMD_SHUTDOWN);
	strcat(buffer,"~");
	strcat(buffer,USER_ID);
	trimwhitespace(buffer);
	if (DEBUG > 0)
	{
		printf("Shut Down Server .\n");
		printf("%s\n",USER_ID);
		printf("%s\n",CMD_SHUTDOWN);
		printf("%s\n",buffer);
	}		

}

void handleShutdown(char *buffer)
{
	if (DEBUG > 0)
		printf("Shutdown BUFFER : %s\n" , buffer);
	
	char *token;
	
	token = strtok(buffer, delimiter);

	if (atol(token) == 999)
	{
		token = strtok(buffer, delimiter);
		printf("\nServer Replied:\n%s\n", token);
		
		printf("\n.. Closing Client ! ..\n");
		
	}else{
		printf("\n.. Unable to Shutdown Server!\n");
		
	}

}

