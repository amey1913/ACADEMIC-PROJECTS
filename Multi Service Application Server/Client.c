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
#define TWO 2
#define MAX_CHARATER 10000

#define REGISTER 10
#define LOGIN 20
#define MENU 30
#define CHECKNEWEMAIL 40
#define WRITEEMAIL 50
#define CHECKALLEMAIL 60
#define LOGOFF 70 //Amey
#define DELETEEMAIL 80
#define FORWARDEMAIL 90 
#define OPENEMAIL 120 

#define DELETECALENDAR 260 //DEL
#define READALLCALENDAR 100 
#define WRITECALENDAR 110 

#define FILTEREMAIL 230 //Fil 
#define DOWNLOADATT 240 //ATT 
#define LISTUSERS 250 //LIST
#define REPLYEMAIL 130 
#define MODIFIEDCALENDAR 140 

int DEBUG = 0;
int LOGOFF_USER = 1;
int MODIFY =0;
void *checkEmailCalendar(void *);
void *sendEmailCalendar(void *);
void trimwhitespace(char *str);
void strCatMessage(char *buffer, char *message);
void registerNewUser(char *buffer, char *message);

void listUsers(char *buffer); //LIST
void login(char *buffer, char *message);
void logoff(char *buffer);
void handleShutdown(char *buffer); //Amey

void readNewEmail(char *buffer);
void checkNewEmail(char *buffer);
void checkAllEmail(char *buffer);
void writeNewEmail(char *buffer, char *message);
void replyEmail(char *buffer, char *message);
void deleteEmail(char *buffer);
void deleteCalendar(char *buffer); //DEL
void forwardEmail(char *buffer);
void readAllCalendar(char *buffer);
void writeCalendar(char *buffer);
void modifiedCalendar(char *buffer);
void Calendar(char *buffer);
void openEmail(char *buffer);
void filterEmail(char *buffer, char *message); //Fil
void downloadAttachment(char *buffer, char *message); //ATT

void handlereadNewEmail(char *buffer,int printEmail);
void handleCheckNewEmail(char *buffer);
void handleCheckAllEmail(char *buffer);
void handleCheckAllCalendar(char *buffer);
void handleLogoff(char *buffer);
void handleListUsers(char *buffer);
void handleRegisterUser(char *buffer , char *USER_ID);
void handleLoginUser(char *buffer , char *USER_ID);
void handleWriteEmail(char *buffer);
void handleDeleteEmail(char *buffer);
void handleDeleteCalendar(char *buffer);//DEL
void handleForwardEmail(char *buffer);
void handleFilterEmail(char *buffer);//Fil
void handleDownloadAttachment(char *buffer);//ATT
void handleReturnedMessage(char *buffer , char * USER_ID ,  int command_code);
void handleOpenEmail(char *buffer , char * USER_ID );
void printMessage(char *buffer);

void error(char *msg)
{
	perror(msg);
	exit(0);
}

/*GLOBAL VARIABLES BEGIN*/

/*Register command*/
char CMD_REGISTER[] = "CMD_REGISTER";

/*Login command*/
char CMD_LOGIN[] = "CMD_LOGIN";
char CMD_LOGOFF[] = "CMD_LOGOFF";
/*Login command*/

char CMD_READNEWEMAIL[] = "CMD_READNEWEMAIL";

char CMD_READALLEMAIL[] = "CMD_READALLEMAIL";

char CMD_WRITEEMAIL[] = "CMD_WRITEEMAIL";

char CMD_OPENEMAIL[] = "CMD_OPENEMAIL";

char CMD_DELETEEMAIL[] = "CMD_DELETEEMAIL";
char CMD_DELETECALENDAR[] = "CMD_DELETECALENDAR";

char CMD_REPLYEMAIL[] = "CMD_REPLYEMAIL";
char CMD_FORWARDEMAIL[] = "CMD_FORWARDEMAIL";

char CMD_FILTEREMAIL[] = "CMD_FILTEREMAIL";  //Fil
char CMD_DOWNLOADATT[] = "CMD_DOWNLOADATT";  //ATT
char CMD_LISTUSERS[] = "CMD_LISTUSERS"; //LIST

char CMD_CHECKNEWEMAIL[] = "CMD_CHECKNEWEMAIL";
char CMD_READALLCALENDAR[] = "CMD_READALLCALENDAR";
char CMD_WRITECALENDAR[] = "CMD_WRITECALENDAR";

/*Display menu command*/
char CMD_MENU[] = "CMD_MENU";

char USER_ID[3] = "000";
char CURRENT_EMAIL_ID[3] = "000";

char temp[MAX_CHARATER] ; //hold temporary string

char const DELIMITER[1] = "`";

int sockfd, portno, n, client_mode;
struct sockaddr_in serv_addr;
struct hostent *server;
int checkEmailCalendar_t_ID = 0;
int sendEmailCalendar_t_ID = 0;
int user_id, send_flag, command_code;

int e_no = 0;
int c_no = 0;

const char delimiter[2] = "~";
char *token;
char message[MAX_CHARATER];

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

	pthread_create(&checkEmailCalendar_t, NULL, checkEmailCalendar, NULL);
	checkEmailCalendar_t_ID = checkEmailCalendar_t;

	pthread_create(&sendEmailCalendar_t, NULL, sendEmailCalendar, NULL);
	sendEmailCalendar_t_ID = sendEmailCalendar_t;

	pthread_join(checkEmailCalendar_t_ID, NULL);
	pthread_join(sendEmailCalendar_t_ID, NULL);

	if (DEBUG > 0)
	{
		printf("After Main thread.\n");
		printf("Port number : %u", 1);
		printf("Socketfd :  %u", 1);
	}

	return 0;
}

void * checkEmailCalendar(void *vptr)
{
	if (DEBUG > 0)
	{
		printf("checkEmailCalendar thread ID: ");
		printf("%u\n", pthread_self());
	}
	char buffer[MAX_CHARATER];
	char message[MAX_CHARATER];
	int sockfd, option;
	char buff2[200], *tok; //shut
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		error("ERROR opening socket");
	if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
		error("ERROR connecting");
	
	/*Keep connection with server, and sending message*/

	while (1)
	{
		if(LOGOFF_USER == 0)
		{
			close(sockfd);
			pthread_exit(NULL);
		}
		/*Clear buffer before each message sent*/
	
		memset(&buffer[0], 0, sizeof(buffer));
		memset(&message[0], 0, sizeof(message));
		
		
		checkNewEmail(buffer);
		
		/*Sending message to server	*/
		n = send(sockfd, buffer, strlen(buffer), 0);

		if (n < 0)
			error("ERROR writing to socket");

		if (DEBUG > 1)
		{
			printf("This message was sent.\n");
			printf("%s\n", buffer);
		}

		/*Message receive from server	*/
		memset(&buffer[0], 0, sizeof(buffer));

		recv(sockfd, buffer, MAX_CHARATER, 0);

		if (n < 0)
			error("ERROR reading from socket");

		if (DEBUG > 0)
		{
			printf("This message was received.\n");
			printf("%s\n", buffer);
		}	

		strcpy(buff2, buffer);
		tok = strtok(buff2,"~");
		
		if (atol(tok) == 999)
		{
			handleShutdown(buffer);
			return;
			command_code = -1;
		}

		handleCheckNewEmail(buffer);
		sleep(2);
	}

	if (DEBUG > 0)
	{
		printf("outside while loop.\n");
	}
	pthread_exit(NULL);
}

void * sendEmailCalendar(void *vptr)
{
	if (DEBUG > 0)
	{
		printf("sendEmailCalendar: ");
		printf("%u\n", pthread_self());
	}
	char buffer[MAX_CHARATER];
	char buff2[MAX_CHARATER], *tok; //shut
	
	int printEmail = 1;
	int sockfd, option;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		error("ERROR opening socket");
	if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
		error("ERROR connecting");
	/*Keep connection with server, and sending message*/
	
	while (1)
	{
		if(LOGOFF_USER == 0)
		{
			close(sockfd);
			pthread_exit(NULL);
		}

		/*Clear buffer before each message sent*/
		memset(&buffer[0], 0, sizeof(buffer));
		memset(&message[0], 0, sizeof(message));

		printf("Please enter a command: ");
		fgets(buffer, MAX_CHARATER, stdin);

		command_code = VerifyCommand(buffer);
		/*If command is invalid asks user again*/

		if (command_code == -1)
			continue;

		if (command_code == REGISTER)
		{
			registerNewUser(buffer, message);

		}

		if (command_code == LOGIN)
		{
			login(buffer, message);
		}

		if(command_code == LISTUSERS)
		{
			listUsers(buffer);
		}

		if (command_code == LOGOFF)
		{
			logoff(buffer);
		}

		if (command_code == MENU)
		{
 			MODIFY = 0;
			printf("Please select one of the following options.\n");
			
			printf("Enter 1 to Check new emails. (New: %u)\n", e_no);
			printf("Enter 2 to Check all email.\n");
			printf("Enter 3 to Send email.\n");
			printf("Enter 4 to Open email.\n");
			printf("Enter 5 to Filter emails.\n"); 
			
			printf("Enter 6 to Read calendar. (New: %u)\n", c_no);
			printf("Enter 7 to Write calendar.\n");	
			printf("Enter 8 to Delete calendar.\n");
			printf("Enter 9 to Modify Calendar.\n"); 
			
			printf("Enter 10 to Download Attachment.\n"); 
			fgets(buffer, MAX_CHARATER, stdin);
			
			option = atoi(buffer);
				switch (option)
				{
					case 1 :
						command_code= readNewEmail ;
						readNewEmail(buffer);
						break;
					case 2 :
						command_code= CHECKALLEMAIL ;
						checkAllEmail(buffer);
						break;	
					case 3 :
						command_code= WRITEEMAIL ;
						writeNewEmail(buffer,message);
						break;
					case 4 :
						command_code= OPENEMAIL ;
						openEmail(buffer);
						break;	
					case 5 :
						command_code= FILTEREMAIL ;
						filterEmail(buffer, message);
						break;	
					case 6 :
						command_code= READALLCALENDAR ;
						readAllCalendar(buffer);
						break;	
					case 7 :
						command_code= WRITECALENDAR ;
						writeCalendar(buffer);
						break;	
					case 8 :
						command_code= DELETECALENDAR ;
						deleteCalendar(buffer);
						break;
					case 9 :  //Modify Calendar
							command_code= DELETECALENDAR ;
							MODIFY = 1;							
							deleteCalendar(buffer);
							
							//command_code= WRITEEMAIL ;
							//writeNewEmail(buffer,message);
						break;	
					case 10 :
						command_code= DOWNLOADATT ;
						downloadAttachment(buffer, message);
						break;
				}
			
		}
		

		SEND_MESSAGE_TO_SERVER:
		/* 				*/
		/*Sending message to server	*/
		/* 				*/
		n = send(sockfd, buffer, strlen(buffer), 0);

		if (n < 0)
			error("ERROR writing to socket");

		if (DEBUG > 0)
		{
			printf("This message was sent.\n");
			printf("%s\n", buffer);
			printf("Command code after sending message to the server : ");
			printf("%u\n",command_code);
		}

		/* 				*/
		/*Message receive from server	*/
		/* 				*/

		memset(&buffer[0], 0, sizeof(buffer));
		recv(sockfd, buffer, MAXLINE, 0);
		
		if (n < 0)
			error("ERROR reading from socket");
		
		if (DEBUG > 0)
		{
			printf("This message was received.\n");
			printf("%s\n", buffer);
			printf("Current command code :  ");
			printf("%u\n", command_code);
		}

		strcpy(buff2, buffer);
		tok = strtok(buff2,"~");
		
		if (atol(tok) == 999)
		{
			handleShutdown(buffer);
			return;
			command_code = -1;
		}

		/* 				*/
		/*Handle message from server	*/
		/* 				*/

		if (command_code == REGISTER)
		{
			handleRegisterUser(buffer , USER_ID);

		}
		else if (command_code == LOGIN)
		{
			handleLoginUser(buffer, USER_ID);
		}
		else if (command_code == LOGOFF )
		{
			handleLogoff(buffer);
		}
		else if (command_code == readNewEmail )
		{
			handlereadNewEmail(buffer,printEmail);
		}
		else if (command_code == CHECKALLEMAIL )
		{
			handleCheckAllEmail(buffer);
		}
		else if (command_code == WRITEEMAIL )
		{
			handleWriteEmail(buffer);
		}
		else if (command_code == DELETEEMAIL )
		{
			handleDeleteEmail(buffer);
		}
		else if (command_code == FILTEREMAIL )
		{
			handleFilterEmail(buffer);
		}
		else if (command_code == DOWNLOADATT )
		{
			handleDownloadAttachment(buffer);
		}
		else if (command_code == DELETECALENDAR )
		{
			handleDeleteCalendar(buffer);
			if (MODIFY ==1)
			{
 				command_code= WRITECALENDAR ;
				writeCalendar(buffer);
				goto SEND_MESSAGE_TO_SERVER;
			}
			
		}
		else if (command_code == READALLCALENDAR )
		{
			handleCheckAllCalendar(buffer);
		}
		else if (command_code == LISTUSERS)
		{
			handleListUsers(buffer);
		}
		else if (command_code == OPENEMAIL )
		{
			handleOpenEmail(buffer , USER_ID );
			
			/*If the buffer is not empty, that means users want to reply/forward/delete the email message*/
			if (send_flag ==1)
			{
				goto SEND_MESSAGE_TO_SERVER;
			}
			
		}
		else
		{
			handleReturnedMessage(buffer , USER_ID , command_code);
		}	
	}
	pthread_exit(NULL);
}

int VerifyCommand(char *cmd)
{

	/*Convert arr to string to use with strcmp() */
	char strcmd[MAX_CHARATER];
	char CMD[MAX_CHARATER];
	strcpy(strcmd, cmd); /*Remove end of line character*/
	int i;
	int count = 0;
	if (DEBUG > 0)
	{
		printf("Command is : ");
		printf("%s\n", CMD);
		printf("%u", strlen(cmd));
	}
	strcpy(CMD, CMD_REGISTER);
	for (i = 0; i < strlen(CMD); i++)
	{
		if (strlen(strcmd) != strlen(CMD) + 1) //+ 1 to account for end of line charater
			break;
		if (strcmd[i] != CMD[i])
			break;
	}
	count = strlen(CMD);
	if (count == i)
	{
		if (DEBUG > 2)
		{
			printf("The command found : ");
			printf("%s\n", CMD);
		}

		return 10;
	}



	strcpy(CMD, CMD_LOGIN);
	for (i = 0; i < strlen(CMD); i++)
	{
		if (strlen(strcmd) != strlen(CMD) + 1) //+ 1 to account for end of line charater
			break;
		if (strcmd[i] != CMD[i])
			break;
	}
	count = strlen(CMD);
	if (count == i)
	{
		if (DEBUG > 1)
		{
			printf("The command found : ");
			printf("%s\n", CMD);
		}

		return 20;
	}

	strcpy(CMD, CMD_MENU);
	for (i = 0; i < strlen(CMD); i++)
	{
		if (strlen(strcmd) != strlen(CMD) + 1) //+ 1 to account for end of line charater
			break;
		if (strcmd[i] != CMD[i])
			break;
	}
	count = strlen(CMD);
	if (count == i)
	{
		if (DEBUG > 1)
		{
			printf("The command found : ");
			printf("%s\n", CMD);
		}
		return 30;
	}

	strcpy(CMD, CMD_LOGOFF);
	for (i = 0; i < strlen(CMD); i++)
	{
		if (strlen(strcmd) != strlen(CMD) + 1) //+ 1 to account for end of line charater
			break;
		if (strcmd[i] != CMD[i])
			break;
	}
	count = strlen(CMD);
	if (count == i)
	{
		if (DEBUG > 1)
		{
			printf("The command found : ");
			printf("%s\n", CMD);
		}
		return 70;
	}
        strcpy(CMD, CMD_LISTUSERS);
	for (i = 0; i < strlen(CMD); i++)
	{
		if (strlen(strcmd) != strlen(CMD) + 1) //+ 1 to account for end of line charater
			break;
		if (strcmd[i] != CMD[i])
			break;
	}
	count = strlen(CMD);
	if (count == i)
	{
		if (DEBUG > 1)
		{
			printf("The command found : ");
			printf("%s\n", CMD);
		}
		return 250;
	}

	if (DEBUG > 0)
	{
		printf("The command NOT found : ");
		printf("%s\n", cmd);
	}

	return -1;
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

void printMessage(char *buffer)
{
	if (DEBUG > 0)
	{
		printf("printMessage.\n");
		printf("%s\n",buffer);
	}

	int return_code;
  	char *token;
	token = strtok(buffer, delimiter);
	return_code = atoi(token);

	if (return_code < 1)
	{
		token = strtok(NULL, delimiter);
		if (token != NULL)
		{
			printf("%s\n",token);
		}
		else
		{
			printf("We could not complete you request. Please contact admin for assitance.\n");
		}		
	}
	else
	{
		while( token != NULL ) 
		{
			printf("%s\n" , token);
	      		token = strtok(NULL, delimiter);
		}	
	}
}

void registerNewUser(char *buffer, char *message)
{
	/*remove newline charater*/
	buffer[strcspn(buffer, "\n")] = 0;

	if (DEBUG > 0)
	{
		printf("Registering user .\n");
	}

	printf("Please enter UserName: ");
	fgets(message, MAX_CHARATER, stdin);
	strCatMessage(buffer, message);


	printf("Please enter Password: ");
	fgets(message, MAX_CHARATER, stdin);
	strCatMessage(buffer, message);


	printf("Please enter Last Name: ");
	fgets(message, MAX_CHARATER, stdin);
	strCatMessage(buffer, message);


	printf("Please enter First Name: ");
	fgets(message, MAX_CHARATER, stdin);
	strCatMessage(buffer, message);

	if (DEBUG > 0)
	{
		printf("Message is : ");
		printf("%s\n", buffer);
	}
}

void login(char *buffer, char *message)
{
	/*remove newline charater*/
	buffer[strcspn(buffer, "\n")] = 0;

	if (DEBUG > 0)
	{
		printf("Login user .\n");
	}

	printf("Please enter UserName: ");
	fgets(message, MAX_CHARATER, stdin);
	strCatMessage(buffer, message);


	printf("Please enter Password: ");
	fgets(message, MAX_CHARATER, stdin);
	strCatMessage(buffer, message);
}

void logoff(char *buffer)
{
	memset(&buffer[0], 0, sizeof(buffer));
	trimwhitespace(USER_ID);
	strcat(buffer, CMD_LOGOFF);
	strcat(buffer,"~");
	strcat(buffer,USER_ID);
	trimwhitespace(buffer);
	if (DEBUG > 0)
	{
		printf("Log Off User .\n");
		printf("%s\n",USER_ID);
		printf("%s\n",CMD_LOGOFF);
		printf("%s\n",buffer);
	}		
}

void handleLogoff(char *buffer)
{
	if (DEBUG > 0)
	{
		printf("lOG oFF BUFFER : %s\n" , buffer);
	}
	
	char *token;
	token = strtok(buffer, delimiter);

	if (atol(token) == 1)
	{
		printf("\n.. Closing Client !\n");
		LOGOFF_USER = 0;
	}else{
		printf("Unable to close Client !\n");
		LOGOFF_USER = 1;
	}

}

void readNewEmail(char *buffer)
{
	memset(&buffer[0], 0, sizeof(buffer));
	memset(&temp[0], 0, sizeof(temp));
	trimwhitespace(USER_ID);
	strcpy(buffer,  CMD_READNEWEMAIL);
	strcat(buffer,"~");
	strcat(buffer,USER_ID);
	trimwhitespace(buffer);
	if (DEBUG > 1)
	{
		printf("Check new Emails .\n");
		printf("%s\n",USER_ID);
		printf("%s\n",CMD_READNEWEMAIL);
		printf("%s\n",buffer);
	}			
}

void checkNewEmail(char *buffer)
{
	memset(&buffer[0], 0, sizeof(buffer));
	memset(&temp[0], 0, sizeof(temp));
	trimwhitespace(USER_ID);
	strcpy(buffer,  CMD_CHECKNEWEMAIL);
	strcat(buffer,"~");
	strcat(buffer,USER_ID);
	trimwhitespace(buffer);
	if (DEBUG > 1)
	{
		printf("Check new Emails .\n");
		printf("%s\n",USER_ID);
		printf("%s\n",CMD_CHECKNEWEMAIL);
		printf("%s\n",buffer);
	}			
}

void openEmail(char *buffer)
{
	char message[MAX_CHARATER];	
	memset(&buffer[0], 0, sizeof(buffer));
	memset(&CURRENT_EMAIL_ID[0], 0, sizeof(CURRENT_EMAIL_ID));
	memset(&temp[0], 0, sizeof(temp));
	trimwhitespace(USER_ID);
	strcpy(buffer,  CMD_OPENEMAIL);
	strcat(buffer,"~");
	strcat(buffer,USER_ID);
	printf("Please enter Email ID: ");
	fgets(message, MAX_CHARATER, stdin);
	strcpy(CURRENT_EMAIL_ID , message);
	trimwhitespace(CURRENT_EMAIL_ID);
	strCatMessage(buffer, message);
	trimwhitespace(buffer);
	if (DEBUG > 1)
	{
		printf("open email .\n");
		printf("%s\n",USER_ID);
		printf("%s\n",CMD_OPENEMAIL);
		printf("%s\n",buffer);
	}			
}

void deleteEmail(char *buffer)
{
	char message[MAX_CHARATER];	
	memset(&buffer[0], 0, sizeof(buffer));
	memset(&temp[0], 0, sizeof(temp));
	trimwhitespace(USER_ID);
	strcpy(buffer,  CMD_DELETEEMAIL);
	strcat(buffer,"~");
	strcat(buffer,USER_ID);

	fgets(message, MAX_CHARATER, stdin);
	strcat(buffer,"~");
	strcat(buffer , CURRENT_EMAIL_ID);

	trimwhitespace(buffer);
	if (DEBUG >0 )
	{
		printf("delete email .\n");
		printf("%s\n",USER_ID);
		printf("%s\n",CMD_DELETEEMAIL);
		printf("%s\n",buffer);
		printf("Command code after delete email .\n");
		printf("%u\n",command_code);
	}			
}

void forwardEmail(char *buffer)
{
	char message[MAX_CHARATER];	
	int recieverEmailID;
	memset(&buffer[0], 0, sizeof(buffer));
	memset(&temp[0], 0, sizeof(temp));
	trimwhitespace(USER_ID);
	strcpy(buffer,  CMD_FORWARDEMAIL);
	strcat(buffer,"~");
	strcat(buffer,USER_ID);
	strcat(buffer,"~");
	strcat(buffer , CURRENT_EMAIL_ID);
	fgets(message, MAX_CHARATER, stdin);
	
	printf("Please enter receiver Emails (Seprated By ;): ");
	fgets(message, MAX_CHARATER, stdin);
	recieverEmailID = atoi(message);
	strCatMessage(buffer, message);		
	
	trimwhitespace(buffer);
	if (DEBUG > 0)
	{
		printf("FORWARD email .\n");
		printf("%s\n",USER_ID);
		printf("%s\n",CMD_FORWARDEMAIL);
		printf("%s\n",buffer);
	}			
}

void checkAllEmail(char *buffer)
{
	memset(&buffer[0], 0, sizeof(buffer));
	memset(&temp[0], 0, sizeof(temp));
	printf("USER_ID: %s\n",USER_ID);
	trimwhitespace(USER_ID);
	printf("USER_ID: %s\n",USER_ID);
	strcpy(buffer,  CMD_READALLEMAIL);
	strcat(buffer,"~");
	strcat(buffer,USER_ID);
	trimwhitespace(buffer);
	if (DEBUG > 1)
	{
		printf("Check new Emails .\n");
		printf("%s\n",USER_ID);
		printf("%s\n",CMD_READALLEMAIL);
		printf("%s\n",buffer);
	}			
}

void readAllCalendar(char *buffer)
{
	memset(&buffer[0], 0, sizeof(buffer));
	memset(&temp[0], 0, sizeof(temp));
	printf("USER_ID: %s\n",USER_ID);
	trimwhitespace(USER_ID);
	printf("USER_ID: %s\n",USER_ID);
	strcpy(buffer,  CMD_READALLCALENDAR);
	strcat(buffer,"~");
	strcat(buffer,USER_ID);
	trimwhitespace(buffer);
	if (DEBUG == 0)
	{
		printf("Read all calendar .\n");
		printf("%s\n",USER_ID);
		printf("%s\n",CMD_READALLCALENDAR);
		printf("%s\n",buffer);
	}			
}

void writeCalendar(char *buffer)
{
	char message[MAX_CHARATER], eventDate[30];
	time_t current_time;
	char* c_time_string, USER_ID_LOCAL[3];

	strcpy(buffer,CMD_WRITECALENDAR);
	strcpy(USER_ID_LOCAL, USER_ID);
		
	trimwhitespace(USER_ID);	
	printf("Please enter receiver Emails (Seprated By ;): ");
	fgets(message, MAX_CHARATER, stdin);
	strCatMessage(buffer, message);

	strCatMessage(buffer, USER_ID_LOCAL);
	
	printf("Please enter subject: ");
	fgets(message, MAX_CHARATER, stdin);
	strCatMessage(buffer, message);

	printf("Please enter event description: ");
	fgets(message, MAX_CHARATER, stdin);
	strCatMessage(buffer, message);

	printf("Please enter location: ");
	fgets(message, MAX_CHARATER, stdin);
	strCatMessage(buffer, message);

	printf("Please enter date (Format :02/26/2016): ");
	fgets(message, MAX_CHARATER, stdin);
	strcpy(eventDate, message);
	strCatMessage(buffer, message);

	printf("Please enter start hour (Format :12:31): ");
	fgets(message, MAX_CHARATER, stdin);
	strCatMessage(buffer, message);

	/*
	printf("Please enter end date: ");
	fgets(message, MAX_CHARATER, stdin);
	strCatMessage(buffer, message);
	*/
	strCatMessage(buffer, eventDate);

	printf("Please enter end hour (Format :12:31): ");
	fgets(message, MAX_CHARATER, stdin);
	strCatMessage(buffer, message);
	
	printf("Please enter attachement name: ");
	fgets(message, MAX_CHARATER, stdin);
	strCatMessage(buffer, message);

	printf("Please enter attachement: ");
	fgets(message, MAX_CHARATER, stdin);
	strCatMessage(buffer, message);
}

void writeNewEmail(char *buffer, char *message)
{
	time_t current_time;
	char* c_time_string, USER_ID_LOCAL[3];

	strcpy(buffer,CMD_WRITEEMAIL);
	strcpy(USER_ID_LOCAL, USER_ID);
		
	trimwhitespace(USER_ID);	
	printf("Please enter receiver Email: ");
	fgets(message, MAX_CHARATER, stdin);
	strCatMessage(buffer, message);

	strCatMessage(buffer, USER_ID_LOCAL);
	
	printf("Please enter subject: ");
	fgets(message, MAX_CHARATER, stdin);
	strCatMessage(buffer, message);

	printf("Please enter body: ");
	fgets(message, MAX_CHARATER, stdin);
	strCatMessage(buffer, message);

	printf("Please enter attachement name: ");
	fgets(message, MAX_CHARATER, stdin);
	strCatMessage(buffer, message);

	printf("Please enter attachement: ");
	fgets(message, MAX_CHARATER, stdin);
	strCatMessage(buffer, message);

	/* Obtain current time. */
	current_time = time(NULL);

	if (current_time == ((time_t)-1))
	{
		(void) fprintf(stderr, "Failure to obtain the current time.\n");
	}

	/* Convert to local time format. */
	c_time_string = ctime(&current_time);

	if (c_time_string == NULL)
	{
		(void) fprintf(stderr, "Failure to convert the current time.\n");
	}

	strCatMessage(buffer, c_time_string );	
	printf("USER_ID: %s\n",USER_ID);
}

void replyEmail(char *buffer, char *message)
{
	time_t current_time;
	char* c_time_string, USER_ID_LOCAL[3];

	strcpy(buffer,CMD_REPLYEMAIL);
	strcpy(USER_ID_LOCAL, USER_ID);
		
	trimwhitespace(USER_ID);	

	memset(&message[0], 0, sizeof(message));
	strcpy(message , CURRENT_EMAIL_ID);	
	strCatMessage(buffer, message);

	strCatMessage(buffer, USER_ID_LOCAL);

	fgets(message, MAX_CHARATER, stdin);

	fflush(stdin);

	printf("Please enter body: ");
	fgets(message, MAX_CHARATER, stdin);
	strCatMessage(buffer, message);

	/* Obtain current time. */
	current_time = time(NULL);

	if (current_time == ((time_t)-1))
	{
		(void) fprintf(stderr, "Failure to obtain the current time.\n");
	}

	/* Convert to local time format. */
	c_time_string = ctime(&current_time);

	if (c_time_string == NULL)
	{
		(void) fprintf(stderr, "Failure to convert the current time.\n");
	}

	strCatMessage(buffer, c_time_string );	
	printf("USER_ID: %s\n",USER_ID);
}

void  handleRegisterUser(char *buffer , char *USER_ID)
{
	int user_id;
	memset(&USER_ID[0], 0, sizeof(USER_ID));
	user_id = atoi(buffer);
	trimwhitespace(buffer);
	if (user_id > 0)
	{
		printf("Congratulation your user ID is : %u\n" , user_id);
		strcpy(USER_ID , buffer);
	}
	else
	{
		printf("We cannot register new user at this time. Please contact Admin.\n");

	}
}

void  handleLoginUser(char *buffer, char *USER_ID)
{
	int user_id;
	memset(&USER_ID[0], 0, sizeof(USER_ID));
	user_id = atoi(buffer);
	trimwhitespace(buffer);
	if (user_id > 0)
	{
		printf("Congratulation!! you have sucessfully logged in : %u\n" , user_id);
		strcpy(USER_ID , buffer);
	}
	else
	{
		printf("We cannot login at this time. Please contact Admin.\n");
	}
}

void handlereadNewEmail(char *buffer, int printEmail)
{
	
	if (DEBUG > 0)
	{
		printf("handlereadNewEmail .\n");
		printf("%s\n",buffer);
	}

  	char *token;
	int numberOfNewEmails;
	int counter = 0;
	token = strtok(buffer, delimiter);

	while( token != NULL ) 
	{
		printf("%s\n" , token);
		token = strtok(NULL, delimiter);
	}


}
void handleCheckNewEmail(char *buffer)
{
	
	if (DEBUG > 1)
	{
		printf("handleCheckNewEmail .\n");
		printf("%s\n",buffer);
	}

  	char *token;
	int numberOfNewEmails,numberOfNewCalendars;
	int counter = 0;
	token = strtok(buffer, delimiter);
    
	numberOfNewEmails = atoi(token);
	if (numberOfNewEmails > 0)
	{
		e_no = numberOfNewEmails;
	}
	else
	{
		e_no = 0;
	}
	
	token = strtok(NULL, delimiter);
    
	numberOfNewCalendars = atoi(token);
	if (numberOfNewCalendars > 0)
	{
		c_no = numberOfNewCalendars;
	}else{
		c_no = 0;
	}
	
	if ((e_no < numberOfNewEmails) || (c_no < numberOfNewCalendars))
	{
		printf("\nYou have %u unread email(s) and %u unread calendar(s).\n", numberOfNewEmails, numberOfNewCalendars);
	}
}

void handleCheckAllEmail(char *buffer)
{
	if (DEBUG > 0)
	{
		printf("handleCheckAllEmail .\n");
		printf("%s\n",buffer);
	}

  	char *token;
	int numberOfNewEmails;
	int counter = 0;

	token = strtok(buffer, delimiter);

	while( token != NULL ) 
	{
		printf("%s\n" , token);
	      	token = strtok(NULL, delimiter);
	}
}

void handleCheckAllCalendar(char *buffer)
{
	if (DEBUG > 0)
	{
		printf("handleCheckAllCalendar .\n");
		printf("%s\n",buffer);
	}

  	char *token;
	int numberOfNewEmails;
	int counter = 0;

	token = strtok(buffer, delimiter);
	if (atol(token) > 0)
	{
		while( token != NULL ) 
		{
			printf("%s\n" , token);
			token = strtok(NULL, delimiter);
		}
	}
	else
	{
		printf("We could not read calendars at this time. Please contact Admin\n");

	}
	
}

void  handleWriteEmail(char *buffer)
{
	int return_cd;
	return_cd = atoi(buffer);
	if (return_cd > 0)
	{
		printf("Congratulation!! you have sucessfully sent email.\n");
		printf("USER_ID: %s\n",USER_ID);
	}
	else
	{
		printf("We could not send email at this time. Please contact Admin\n");

	}
}

void  handleDeleteEmail(char *buffer)
{
	int return_cd;
	return_cd = atoi(buffer);
	if (return_cd > 0)
	{
		printf("Congratulation!! you have sucessfully deleted an email.\n");
	}
	else
	{
		printf("We could not delete your requested email at this time. Please contact Admin\n");
	}
}

void  handleForwardEmail(char *buffer)
{
	int return_cd;
	return_cd = atoi(buffer);
	if (return_cd > 0)
	{
		printf("Congratulation!! you have sucessfully forwarded an email.\n");
	}
	else
	{
		printf("We could not commplete your request at this time. Please contact Admin\n");
	}
}

void  handleOpenEmail(char *buffer ,char * USER_ID )
{
	char select[TWO];
	int option;
	send_flag= 1;
	trimwhitespace(buffer);
	printMessage(buffer);
	fflush(stdin);
	printf("Press [1 to reply] [2 to foward] [3 to delete] [0 to exit] : ");
	fgets(select, TWO , stdin);
       option = atoi(select);
		switch (option)
		{
                        printf("option ius %d",option);
			case 1 :
				command_code= REPLYEMAIL ;
				replyEmail(buffer , message);
				break;	
			case 2 :
				command_code= FORWARDEMAIL ;
				forwardEmail(buffer);
				break;	
			case 3 :
				command_code= DELETEEMAIL ;
				deleteEmail(buffer);
				break;		
			case 0 :
				memset(&buffer[0], 0, sizeof(buffer));
				send_flag= 0;
				break;
		}
	
}

void  handleReturnedMessage(char *buffer ,char * USER_ID , int command_code)
{
	int return_cd;
	return_cd = atoi(buffer);
	if (return_cd > 0)
	{
		printf("Congratulation!! you have sucessfully forwarded an email.\n");
	}
	else
	{
		printf("We could not commplete your request at this time. Please contact Admin\n");
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
		printf("\n.. Server Replied: %s\n", token);
		
		printf("\n.. Closing Client !\n");
		LOGOFF_USER = 0;
	}else{
		printf("\n.. Unable to Shutdown Server!\n");
		LOGOFF_USER = 1;
	}
	exit(0);
}

void handleFilterEmail(char *buffer)
{	
	if (DEBUG > 0)
	{
		printf("handleFilterEmail .\n");
		printf("%s\n",buffer);
	}

  	char *token;
	int numberOfNewEmails;
	int counter = 0;
	token = strtok(buffer, delimiter);

	while( token != NULL ) 
	{
		printf("%s\n" , token);
		token = strtok(NULL, delimiter);
	}
}

void filterEmail(char *buffer, char *message)
{
	char opti[2];	
	int recieverEmailID, option;
	
	memset(&buffer[0], 0, sizeof(buffer));
	memset(&temp[0], 0, sizeof(temp));

	bzero((char *)&opti, sizeof(opti));	
	
	trimwhitespace(USER_ID);
	
	strcpy(buffer,  CMD_FILTEREMAIL);
	strcat(buffer,"~");
	strcat(buffer,USER_ID);
	strcat(buffer,"~");
	
	//Your option
	printf("Enter 1 to filter by sender email id.\n");
	printf("Enter 2 to filter by subjec.\n");
	printf("Enter 3 to filter by recived date.\n");
	fflush(stdin);
	fgets(opti, 2, stdin);
	//fgets(opti, 2, stdin);
	option = atoi(opti);
	switch ( option )
	{
		case 1 :
			strcat(buffer,  "S");
			fflush(stdin);
			fgets(message, MAX_CHARATER, stdin);
			printf("Please enter Reciever Email ID: ");
			fgets(message, MAX_CHARATER, stdin);
                       // fgets(message, MAX_CHARATER, stdin);
			strCatMessage(buffer, message);
			break;

		case 2 :
			strcat(buffer,  "M");
			fflush(stdin);
			fgets(message, MAX_CHARATER, stdin);
			printf("Please enter Subject data: ");
			fgets(message, MAX_CHARATER, stdin);
			strCatMessage(buffer, message);
			
			break;
		case 3 :
			
			strcat(buffer,  "D");
			fflush(stdin);
			fgets(message, MAX_CHARATER, stdin);
			printf("Please enter date in (mmm/dd/yyyy) format (eg. mar/03/2016): ");
			fgets(message, MAX_CHARATER, stdin);
			strCatMessage(buffer, message);
			
			break;
	}
	strcat(buffer,  "^");
			
	trimwhitespace(buffer);
	if (DEBUG > 0)
	{
		printf("Filter email .\n");
		printf("%s\n",USER_ID);
		printf("%s\n",CMD_FILTEREMAIL);
		printf("%s\n",buffer);
	}			
}

void handleDownloadAttachment(char *buffer)
{
	int ret = 0;
	char newFileName[100], newFileData[MAX_CHARATER];
	
	if (DEBUG > 0)
	{
		printf("handleDownloadAttachment .\n");
		printf("%s\n",buffer);
	}

  	char *token;
	int numberOfNewEmails;
	int counter = 0;
	token = strtok(buffer, delimiter);

	ret = atoi(token);
	if (ret == 0)
	{
		printf("Unable to Download Attachment!\n" , token); 
	}
	else
	{
		token = strtok(NULL, delimiter);	

		strcpy(newFileName, token);
	    strcat(newFileName, ".txt");
		token = strtok(NULL, delimiter);	

		strcpy(newFileData, token);
		
		FILE *userAttachment = fopen(newFileName, "w+");
		fprintf(userAttachment,"%s", newFileData);
		
		fclose(userAttachment);		
		printf("Attachment Downloaded!\n" , token); 
	
	}

}

void downloadAttachment(char *buffer, char *message)
{
	char opti[2];	
	int recieverEmailID, option;
	
	memset(&buffer[0], 0, sizeof(buffer));
	memset(&temp[0], 0, sizeof(temp));

	bzero((char *)&opti, sizeof(opti));	
	
	trimwhitespace(USER_ID);
	
	strcpy(buffer,  CMD_DOWNLOADATT);
	strcat(buffer,"~");
	strcat(buffer,USER_ID);
	strcat(buffer,"~");
	
	//Your option
	printf("Enter 1 to Download Email Attachment.\n");
	printf("Enter 2 to Download Calendar Event Attachment.\n");
	
	fgets(opti, 2, stdin);
	//fgets(opti, 2, stdin);
	option = atoi(opti);
	switch ( option )
	{
		case 1 :
			strcat(buffer,  "E");
			fflush(stdin);
			fgets(message, MAX_CHARATER, stdin);
			printf("Enter Email ID: ");
			fgets(message, MAX_CHARATER, stdin);
			strCatMessage(buffer, message);
			break;

		case 2 :
			strcat(buffer,  "C");
			fflush(stdin);
			fgets(message, MAX_CHARATER, stdin);
			printf("Enter Calendar Event ID: ");
			fgets(message, MAX_CHARATER, stdin);
			strCatMessage(buffer, message);			
			break;
	}
	strcat(buffer,  "^");
			
	trimwhitespace(buffer);
	if (DEBUG > 0)
	{
		printf("Download Attachment.\n");
		printf("%s\n",USER_ID);
		printf("%s\n",CMD_DOWNLOADATT);
		printf("%s\n",buffer);
	}		

}

void  handleDeleteCalendar(char *buffer)
{
	int return_cd;
	token = strtok(buffer, delimiter);
        
	return_cd = atoi(token);
	if (return_cd > 0)
	{
		printf("Congratulation!! you have sucessfully deleted calendar event.\n");
                if(MODIFY == 1) {
			
	       }
	}
	else
	{
		printf("We could not delete your requested calendar event at this time. Please contact Admin\n");

	}
}

void deleteCalendar(char *buffer)
{
	char message[MAX_CHARATER];	
	memset(&buffer[0], 0, sizeof(buffer));
	memset(&temp[0], 0, sizeof(temp));
	
	trimwhitespace(USER_ID);
	
	strcpy(buffer,  CMD_DELETECALENDAR);
	strcat(buffer,"~");
	strcat(buffer,USER_ID);
	fflush(stdin);

	printf("Please enter calendar event ID to delete: ");
	fgets(message, MAX_CHARATER, stdin);
	
	strCatMessage(buffer, message);
	trimwhitespace(buffer);
	if (DEBUG > 1)
	{
		printf("delete calendar .\n");
		printf("%s\n",USER_ID);
		printf("%s\n",CMD_DELETECALENDAR);
		printf("%s\n",buffer);
	}			
}

void  handleListUsers(char *buffer)
{
	if (DEBUG > 0)
	{
		printf("handleListUsers .\n");
		printf("%s\n",buffer);
	}

  	char *token;
	int numberOfNewEmails;
	int counter = 0;
    	token = strtok(buffer, delimiter);

	while( token != NULL ) 
	{
		printf("%s\n" , token);
	      	token = strtok(NULL, delimiter);
	}
}

void listUsers(char *buffer)
{
	char message[MAX_CHARATER];	
	memset(&buffer[0], 0, sizeof(buffer));
	memset(&temp[0], 0, sizeof(temp));
	
	trimwhitespace(USER_ID);
	
	strcpy(buffer,  CMD_LISTUSERS);
	strcat(buffer,"~");
	strcat(buffer,USER_ID);
	
	trimwhitespace(buffer);
	if (DEBUG > 1)
	{
		printf("List Users .\n");
		printf("%s\n",USER_ID);
		printf("%s\n",CMD_LISTUSERS);
		printf("%s\n",buffer);
	}			
}
