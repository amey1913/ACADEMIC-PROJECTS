#include <stdio.h>
#include <stdlib.h>	
#include <string.h>
#include <unistd.h>	
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <time.h>

#define MAX_CHARACTER 10000
#define MAXLINE 4096
#define DEBUG 0
int maxId;

struct Email
{
	int EmailId;
	int EmailAccount;
	char Read[2];
	int SenderId;
	int ReceiverId;
	char Subject[100];
	char Body[200];
	char AttachmentName[20];
	char Attachment[200];
	char DateTimeReceived[50];
};

struct Calendar
{	
    int EventId;
    int SenderId; //SenderId is the person who schedules the event
    int ReceipientId;  //ReceipientId are people who are invited to the event
    char Subject[20];
    char Read[2];
    char EventDesc[80];
    char Location[30];
    char StartDate[20]; //format 02/26/2016
    char StartHour[15];  //format 12:31 -- 1-24
    char EndDate[20];
    char EndHour[15]; 
	char AttachmentName[200];
	char Attachment[20];
};

struct User
{
	int UserID;
	char Active[2];
	char FirstName[20];
	char LastName[20];
	char EmailID[30];
	char Password[30];
	struct Email Emails[10];
	struct Calendar Calendars[10];
};

/* Start of Global Variables */ 

	struct sembuf wait, post;
	int semid_lock, fork_id, shm_id, shm_id1, shm_id2;
	struct User *users;
	
	char *NewEventID;
	char *Shutdown;
/* End of Global Variables */ 


void *calendarServer(char *port);
void trimwhitespace(char *str);

struct Calendar * readCalendars(char *file_name)
{
	FILE *reads;
	int flen, calender_count;
	char *buff;
	char *fname;
	char *token_item;
	struct Calendar calendars[10];
	bzero((char *)&calendars, sizeof(calendars));	
	fname = file_name;
	reads = fopen(fname, "r");
	if(reads == NULL)
	{
		perror("Error");
		return (struct Calendar *) calendars;
	}
	else
    	{
		fseek(reads,0,SEEK_END);
		flen = ftell(reads);
		rewind(reads);
		buff = (char*)malloc(sizeof(char)*flen);
		
		if(buff == NULL)
		{
			perror("Memory Error\n");
			bzero((char *)&calendars, sizeof(calendars));	
			fclose(reads);
			exit(0);
		}
		
		fread(buff,1,flen,reads);
		calender_count = -1;
		token_item = strtok(buff, "^~");

		while(token_item != NULL)
		{
			if (atol(token_item) == 0){
				break;
			}
			calender_count++;
			
			calendars[calender_count].EventId = atol(token_item);

			token_item = strtok(NULL, "^~");
			calendars[calender_count].SenderId = atol(token_item);
			
			token_item = strtok(NULL, "^~");
			calendars[calender_count].ReceipientId = atol(token_item);
			
			token_item = strtok(NULL,"^~");
			strcpy(calendars[calender_count].Subject, token_item);
			
			token_item = strtok(NULL,"^~");
			strcpy(calendars[calender_count].Read, token_item);
			
			token_item = strtok(NULL,"^~");
			strcpy(calendars[calender_count].EventDesc,token_item);
			
			token_item = strtok(NULL,"^~");
			strcpy(calendars[calender_count].Location,token_item);
			
			token_item = strtok(NULL,"^~");
			strcpy(calendars[calender_count].StartDate,token_item);
			
			token_item = strtok(NULL,"^~");
			strcpy(calendars[calender_count].StartHour,token_item);
			
			token_item = strtok(NULL,"^~");
			strcpy(calendars[calender_count].EndDate,token_item);
			
			token_item = strtok(NULL,"^~");
			strcpy(calendars[calender_count].EndHour,token_item);
			
			token_item = strtok(NULL,"^~");
			strcpy(calendars[calender_count].Attachment,token_item);
			
			token_item = strtok(NULL,"^~");
			strcpy(calendars[calender_count].AttachmentName,token_item);
		}
    }
	fclose(reads);
	if (calender_count == -1)
    {
		bzero((char *)&calendars, sizeof(calendars));	
    }
	
	return (struct Email *)calendars;
}

struct Email * readEmails(char *file_name)
{
	FILE *reads;
	int flen, email_count;
	char *buff;
	char *fname;
	char *email_item;
	struct Email emails[10];
	bzero((char *)&emails, sizeof(emails));
	fname = file_name;
	reads = fopen(fname, "r");
	if(reads == NULL)
    {
		perror("Error");
		return (struct Email *) emails;
    }
	else
    {
		fseek(reads,0,SEEK_END);
		flen = ftell(reads);
		rewind(reads);
		buff = (char*)malloc(sizeof(char)*flen);
		if(buff == NULL){
			perror("Memory Error\n");
			bzero((char *)&emails, sizeof(emails));	
			fclose(reads);
			exit(0);
		}
		fread(buff,1,flen,reads);
		  
		email_count = -1;
		email_item = strtok(buff, "^~");

		while(email_item != NULL)
		{
			if (atol(email_item) == 0){
				break;
			}
			email_count++;

			emails[email_count].EmailId = atol(email_item);
			
			email_item = strtok(NULL, "^~");
			emails[email_count].EmailAccount = atol(email_item);

			email_item = strtok(NULL,"^~");
			strcpy(emails[email_count].Read, email_item);

			email_item = strtok(NULL,"^~");
			emails[email_count].SenderId = atol(email_item);

			email_item = strtok(NULL,"^~");
			emails[email_count].ReceiverId = atol(email_item);

			email_item = strtok(NULL,"^~");
			strcpy(emails[email_count].Subject,email_item);

			email_item = strtok(NULL,"^~");
			strcpy(emails[email_count].Body,email_item);

			email_item = strtok(NULL,"^~");
			strcpy(emails[email_count].AttachmentName,email_item);

			email_item = strtok(NULL,"^~");
			strcpy(emails[email_count].Attachment,email_item);

			email_item = strtok(NULL,"^~");
			strcpy(emails[email_count].DateTimeReceived,email_item);
		
			email_item = strtok(NULL, "^~");
		}
	}
	fclose(reads);
	if (email_count == -1)
    {
		bzero((char *)&emails, sizeof(emails));	
    }
	
	return (struct Email *)emails;
}


void fillEmails()
{
	char emailFileName[20];
	int i, j;
	for(j = 0; j < 10 ; j++)
    {
		if((strcmp(users[j].Active, "Y") != 0 && strcmp(users[j].Active, "N") != 0) || users[j].Active == NULL){
			break;
		}  
		sprintf(emailFileName, "%d_email.txt", users[j].UserID);
		if(DEBUG > 0)
		{
			printf("File Name: %s\n", emailFileName);  
			fflush(stdin);			
		}
		
		memcpy(users[j].Emails, readEmails(emailFileName), sizeof(struct Email) * 10);
    }
}

void fillCalenders()
{
	char calenderFileName[20];
	int i, j;
	for(j = 0; j < 10 ; j++)
    {
		if((strcmp(users[j].Active, "Y") != 0 && strcmp(users[j].Active, "N") != 0) || users[j].Active == NULL){
			break;
		}  
		sprintf(calenderFileName, "%d_calendar.txt", users[j].UserID);
		if(DEBUG > 0)
		{
			printf("File Name: %s\n", calenderFileName);  
			fflush(stdin);				
		}
		
		memcpy(users[j].Calendars, readCalendars(calenderFileName), sizeof(struct Calendar) * 10);
    }
}


struct User * readUsers()
{
	FILE *reads_user;
	int flen, user_count;
	char *user_buff;
	char fname[20] = "users.txt";
	char *isUser;
	struct User users[10];

	bzero((char *)&users, sizeof(users));

	reads_user = fopen(fname, "r");
	if(reads_user == NULL){
		perror("Error");
		return (struct User *)users;
	}
	else
	{
		fseek(reads_user,0,SEEK_END);
		flen = ftell(reads_user);
		rewind(reads_user);
		bzero((char *)&user_buff, sizeof(user_buff));
		user_buff = (char*)malloc(sizeof(char)*flen);
    
		if(user_buff == NULL){
			perror("Memory Error\n");
			exit(0);
		}
		fread(user_buff,1,flen,reads_user);
		user_count = -1;
		isUser = strtok(user_buff, "^~");

		while(isUser != NULL)
		{
			user_count++;
	
			if (atol(isUser) == 0){
			  break;
			}
			
			users[user_count].UserID = atol(isUser);
			
			isUser = strtok(NULL, "^~");
			strcpy(users[user_count].Active, isUser);
			
			isUser = strtok(NULL, "^~");
			strcpy(users[user_count].EmailID, isUser);
			
			isUser = strtok(NULL, "^~");
			strcpy(users[user_count].Password, isUser);
			
			isUser = strtok(NULL, "^~");
			strcpy(users[user_count].FirstName, isUser);
			
			isUser = strtok(NULL, "^~");
			strcpy(users[user_count].LastName, isUser);
			
			isUser = strtok(NULL, "^~");
		}
	}
  	
	fclose(reads_user);
	
	return (struct User *)users;
}

void getMaxID()
{
 int i, j;
 for(j = 0; j < 10 ; j++)
    {
		if(strcmp(users[j].Active, "Y") != 0 && strcmp(users[j].Active, "N") != 0 ){
			break;
		}
			
		if(users[j].UserID > maxId){
			maxId = users[j].UserID;
		}
    } 
    if(DEBUG > 0)
	{
    	printf("Max ID : %d\n", maxId);
    }
}

void printUserDetails()
{
	char emailFileName[20];
	int i, j;
	for(j = 0; j < 10 ; j++)
    {
		if(strcmp(users[j].Active, "Y") != 0 && strcmp(users[j].Active, "N") != 0 ){
			break;
		}
		
		printf("\n\nUser Details :%d\n:%s\n:%s\n:%s\n:%s\n:%s\n", users[j].UserID
			 , users[j].Active
			 , users[j].FirstName
			 , users[j].LastName
			 , users[j].EmailID
             , users[j].Password);
		if (strcmp(users[j].Emails[0].Read, "Y") == 0 || strcmp(users[j].Emails[0].Read, "N") == 0){
			printf("\n**** User Emails ****");
		}

		for(i = 0; i < 10; i++)
        {
			if ((strcmp(users[j].Emails[i].Read, "Y") != 0 && strcmp(users[j].Emails[i].Read, "N") != 0) || users[j].Emails[i].Read == NULL) 
			{
				break;
			}
			printf("\nEmail No :%d\n:%d\n:%s\n:%d\n:%d\n:%s\n:%s\n:%s\n:%s\n:%s\n", users[j].Emails[i].EmailId
				 , users[j].Emails[i].EmailAccount
				 , users[j].Emails[i].Read
				 , users[j].Emails[i].SenderId
				 , users[j].Emails[i].ReceiverId
				 , users[j].Emails[i].Subject
				 , users[j].Emails[i].Body
				 , users[j].Emails[i].AttachmentName
				 , users[j].Emails[i].Attachment
				 , users[j].Emails[i].DateTimeReceived);
        }
		
		for(i = 0; i < 10; i++)
        {
			if ((strcmp(users[j].Calendars[i].Read, "Y") != 0 && strcmp(users[j].Calendars[i].Read, "N") != 0) 
				|| users[j].Calendars[i].Read == NULL) 
			{
				break;
			}
			printf("\nCalendar Event No :%d\n:%d\n:%d\n:%s\n:%s\n:%s\n:%s\n:%s\n:%s\n:%s\n:%s\n:%s\n:%s\n", users[j].Calendars[i].EventId
				 , users[j].Calendars[i].SenderId
				 , users[j].Calendars[i].ReceipientId
				 , users[j].Calendars[i].Subject
				 , users[j].Calendars[i].Read
				 , users[j].Calendars[i].EventDesc
				 , users[j].Calendars[i].Location
				 , users[j].Calendars[i].StartDate
				 , users[j].Calendars[i].StartHour
				 , users[j].Calendars[i].EndDate
				 , users[j].Calendars[i].EndHour
				 , users[j].Calendars[i].Attachment
				 , users[j].Calendars[i].AttachmentName);
        }
    }
}

int validateUser(char validate[100])
{  
	if(DEBUG > 0){
		printf("Validate : %s\n",validate);
	}
  
	int i;
	char UserId[100],Password[100];
	char *ch;
	ch = strtok(validate, "~");

	strcpy(UserId,ch);
  
	if(DEBUG > 0){
		printf("Input User ID: %s\n", UserId);
	}
  
	ch = strtok(NULL, "~");
  
	strcpy(Password,ch);
  
	if(DEBUG > 0){
		printf("Password: %s\n", Password);
	}
  
	for(i =0 ;i < 10 ;i++)
    {
		if(strcmp(users[i].Active, "Y") != 0 && strcmp(users[i].Active, "N") != 0 ){
			break;
		}
		if(DEBUG > 0){
			printf("Name : %s Password: %s \n",users[i].EmailID,users[i].Password);
		}
		if (strcmp(users[i].EmailID, UserId) == 0 && strcmp(users[i].Password, Password) == 0 ){
			return users[i].UserID;
		}
    } 
	return -1;
}

void getUserEmailID(int id, char *email)
{
	int i,j,k;
	
	printf("userId: %d\n", id);
					
	for(j =0 ;j < 10 ;j++)
	{
		if(strcmp(users[j].Active, "Y") != 0 && strcmp(users[j].Active, "N") != 0 ){
			break;
		}
		if(users[j].UserID == id) 
		{
			strcpy(email, users[j].EmailID);		
			printf("email: %s\n", email);
			return ;
		}
	}

	strcpy(email, " ");		
	return; 		
}


int registration(char data[200])
{   
	char buff2[1000],buff3[1000],emailFileName[200],calendarFileName[200];
	int userId,newId, i;
	char *ch;

	getMaxID(); 

	if(DEBUG > 0){
		if(users[9].UserID != 0){
			printf("Maximum Users Limit Reached, cannot create new User!\n");
			return -1;
		}
	}

	strcpy (buff3, data);
	userId = validateUser(data);

	if(DEBUG > 0){
		printf("User: %d\n",userId);
	}

	if (userId > 0){
		if(DEBUG > 0){
			printf("User %d already exist\n",userId);
		}
		return -1;
	}else{
  
		newId = maxId+1;
		if(DEBUG > 0){
			printf("New user created is %d\n",newId);
		}
		sprintf(buff2, "\n%d%s%s",newId,"~Y~", buff3);
  
		if(DEBUG > 0){
			printf("String used to create user: %s\n", buff2);
		}
		for(i =0 ;i < 10 ;i++)
		{
			if(strcmp(users[i].Active, "Y") != 0 && strcmp(users[i].Active, "N") != 0 ){
				break;
			}
		}

		ch = strtok(buff2, "~");
		users[i].UserID = atol(ch);	
	
		ch = strtok(NULL, "~");
		strcpy(users[i].Active, ch); 
   
		ch = strtok(NULL, "~");
		strcpy(users[i].EmailID, ch);
    	
		ch = strtok(NULL, "~");
		strcpy(users[i].Password, ch);
			
		ch = strtok(NULL, "~");
		strcpy(users[i].FirstName, ch);
    	
		ch = strtok(NULL, "~");
		strcpy(users[i].LastName, ch);	
    
		sprintf(emailFileName, "%d_email.txt", newId );
		FILE *userEmail = fopen(emailFileName, "w+");
		fclose(userEmail);

		sprintf(calendarFileName, "%d_calendar.txt", newId );
		FILE *userCalender = fopen(calendarFileName, "w+");
		fclose(userEmail);
	
		return newId; 
	}
	return -1;
}

int checkTimeClash(char StartDate[11], char StartHour[6], char EndHour[6], int j)
{
	struct tm  p_SDate, p_STime, p_EDate, p_ETime;
	struct tm  c_SDate, c_STime, c_EDate, c_ETime;
	int k;
	//format 02/26/2016
	//format 12:31 -- 1-24

	if (strptime(StartDate, "%m/%d/%Y",&p_SDate) == NULL || strptime(StartHour, "%H:%M",&p_STime) == NULL || strptime(EndHour, "%H:%M",&p_ETime) == NULL)
	{
		perror("\nproposed Strptime failed\n");
		return -1;
	}
	
	for(k = 0; k < 10; k++)
	{
		if ((strcmp(users[j].Calendars[k].Read, "Y") != 0 && strcmp(users[j].Calendars[k].Read, "N") != 0) 
			|| users[j].Calendars[k].Read == NULL) 
		{
			break;
		}

		if (strptime(users[j].Calendars[k].StartDate, "%m/%d/%Y",&c_SDate) == NULL || strptime(users[j].Calendars[k].StartHour, "%H:%M",&c_STime) == NULL ||
		strptime(users[j].Calendars[k].EndDate, "%m/%d/%Y",&c_EDate) == NULL || strptime(users[j].Calendars[k].EndHour, "%H:%M",&c_ETime) == NULL)
		{
			perror("\nproposed Strptime failed\n");
			return -1;
		}

		if (p_SDate.tm_year == c_EDate.tm_year &&  p_SDate.tm_mon == c_SDate.tm_mon &&  p_SDate.tm_mday == c_SDate.tm_mday)
		{
			
			if(((p_STime.tm_hour >= c_STime.tm_hour && p_STime.tm_min >= c_STime.tm_min)
			&& (p_STime.tm_hour <= c_ETime.tm_hour && p_STime.tm_min <= c_ETime.tm_min))
			||
			((p_ETime.tm_hour >= c_STime.tm_hour && p_ETime.tm_min >= c_STime.tm_min)
			&& (p_ETime.tm_hour <= c_ETime.tm_hour && p_ETime.tm_min <= c_ETime.tm_min)))
			{
				return -1;
			}
			
		}

	}
	
	return 0;
}
		
int getNewEventID()
{
	int temp = 0;
	bzero((char *)&NewEventID, sizeof(NewEventID));

	NewEventID = (struct User*) shmat(shm_id1, NULL, 0);
	temp = atol(NewEventID);
	
	temp = temp + 1;
	sprintf(NewEventID, "%d", temp);
	
	shmdt((void *) NewEventID);
	
	return temp;
}				

int writeCalendarEvent(char data[200],char *message) 
{	
	int i,j,k;
	char *ch, *recpt;
	char input_data[200], recList[100];
	
	int  locl_EventId;
	int  locl_SenderId; //SenderId is the person who schedules the event
	int  locl_ReceipientId;  //ReceipientId are people who are invited to the event
	char locl_Subject[20];
	char locl_Read[2];
	char locl_EventDesc[80];
	char locl_Location[30];
	char locl_StartDate[11]; //format 02/26/2016
	char locl_StartHour[06];  //format 12:31 -- 1-24
	char locl_EndDate[11];
	char locl_EndHour[06]; 
	char locl_Attachment[20]; 
	char locl_AttachmentName[200]; 
	
	strcpy(input_data, data);
	ch = strtok(input_data, "~");
	strcpy(recList, ch);
	
	locl_EventId = getNewEventID();					
	
	ch = strtok(NULL, "~");   
	locl_SenderId = atol(ch);
	
	ch = strtok(NULL, "~"); 	
	strcpy(locl_Subject,ch);

	ch = strtok(NULL, "~");
	strcpy(locl_EventDesc,ch);

	ch = strtok(NULL, "~");
	strcpy(locl_Location,ch);

	ch = strtok(NULL, "~");
	strcpy(locl_StartDate,ch);
	
	ch = strtok(NULL, "~");
	strcpy(locl_StartHour,ch);

	ch = strtok(NULL, "~");
	strcpy(locl_EndDate,ch);
	
	ch = strtok(NULL, "~");
	strcpy(locl_EndHour,ch);
	
	ch = strtok(NULL, "~");
	strcpy(locl_Attachment,ch);
	
	ch = strtok(NULL, "~");
	strcpy(locl_AttachmentName,ch);
	
	recpt = strtok(recList, ";");
	printf("Usre : %s\n", recpt);
	
	while(recpt != NULL)
	{
		for(j =0 ;j < 10 ;j++)
		{
			if(strcmp(users[j].Active, "Y") != 0 && strcmp(users[j].Active, "N") != 0 ){
				break;
			}

			if(strcmp(users[j].EmailID, recpt) == 0) 	
			{
				for(i = 0; i < 10; i++)
				{
					if ((strcmp(users[j].Calendars[i].Read, "Y") != 0 && strcmp(users[j].Calendars[i].Read, "N") != 0) 
						|| users[j].Calendars[i].Read == NULL) 
					{
						
						locl_ReceipientId = users[j].UserID;

						strcpy( locl_Read, "N");

						if (checkTimeClash(locl_StartDate, locl_StartHour, locl_EndHour, j) == -1)
						{
							sprintf(message,"Error: Proposed time of Calender Event Clashes with the recipient %s.", users[j].EmailID);
							return -1;
						}
						
						users[j].Calendars[i].EventId = locl_EventId;
						
						users[j].Calendars[i].ReceipientId = locl_ReceipientId;
				
						strcpy(users[j].Calendars[i].Read, "N");
				
						users[j].Calendars[i].SenderId = locl_SenderId;
							
						strcpy(users[j].Calendars[i].Subject, locl_Subject);
		
						strcpy(users[j].Calendars[i].EventDesc, locl_EventDesc);
		
						strcpy(users[j].Calendars[i].Location, locl_Location);
						
						strcpy(users[j].Calendars[i].StartDate, locl_StartDate);
						
						strcpy(users[j].Calendars[i].StartHour, locl_StartHour);
						
						strcpy(users[j].Calendars[i].EndDate, locl_EndDate);
						
						strcpy(users[j].Calendars[i].EndHour, locl_EndHour);
						
						strcpy(users[j].Calendars[i].Attachment, locl_Attachment);
						
						strcpy(users[j].Calendars[i].AttachmentName, locl_AttachmentName);

						sprintf(message,"%s","Calender Event successfully Added");
						break;
					}
				}	
			}
		}
	
		recpt = strtok(NULL, ";");
	}
	//Adding Calendar event to the event creater array
	for(j =0 ;j < 10 ;j++)
	{
		if(strcmp(users[j].Active, "Y") != 0 && strcmp(users[j].Active, "N") != 0 ){
			break;
		}

		if(users[j].UserID == locl_SenderId) 
		{
			for(i = 0; i < 10; i++)
			{
				if ((strcmp(users[j].Calendars[i].Read, "Y") != 0 && strcmp(users[j].Calendars[i].Read, "N") != 0) 
					|| users[j].Calendars[i].Read == NULL) 
				{					
					if (checkTimeClash(locl_StartDate, locl_StartHour, locl_EndHour, j) == -1)
					{
						sprintf(message,"Error: Proposed time of Calender Event Clashes with the recipient %s.", users[j].EmailID);
						return -1;
					}
					
					users[j].Calendars[i].EventId = locl_EventId;
					
					users[j].Calendars[i].ReceipientId = locl_SenderId;
			
					strcpy(users[j].Calendars[i].Read, "N");
			
					users[j].Calendars[i].SenderId = locl_SenderId;
					 	
					strcpy(users[j].Calendars[i].Subject, locl_Subject);
	
					strcpy(users[j].Calendars[i].EventDesc, locl_EventDesc);
	
					strcpy(users[j].Calendars[i].Location, locl_Location);
					
					strcpy(users[j].Calendars[i].StartDate, locl_StartDate);
					
					strcpy(users[j].Calendars[i].StartHour, locl_StartHour);
					
					strcpy(users[j].Calendars[i].EndDate, locl_EndDate);
					
					strcpy(users[j].Calendars[i].EndHour, locl_EndHour);

					strcpy(users[j].Calendars[i].Attachment, locl_Attachment);
					
					strcpy(users[j].Calendars[i].AttachmentName, locl_AttachmentName);

					sprintf(message,"%s","Calender Event successfully Added");
					return 1;
				}
			}	
		}
	}
	
	sprintf(message,"%s","Error in adding Calender Event!");
	
	return -1;
} 

int forwardEmail(char data[200]) 
{
	printf("\nData : %s", data);
	int i,j,userId,emailId,result;
	char *chs;
	result = 0;
	char tempData[200], fwd[200],recEmailID[30], strID[10], strSenderEmail[30];
	strcpy(tempData, data);
	
	printf("\nSlipting Data %s\n", tempData);
	
	chs = strtok(tempData, "~");
	printf("token ID: %s", chs);
	userId = atol(chs);

	
	chs = strtok(NULL, "~");
	printf("token ID: %s", chs);
	emailId = atol(chs);

	
	chs = strtok(NULL, "~");
	printf("token ID: %s", chs);
	strcpy(recEmailID, chs);
	printf("recEmailID ID: %s", recEmailID);
	
	for(j =0 ;j < 10 ;j++)
		{
			if(strcmp(users[j].Active, "Y") != 0 && strcmp(users[j].Active, "N") != 0 ){
				break;
			}
			if(users[j].UserID == userId) {
			for(i = 0; i < 10; i++)
			{
				if(strcmp(users[j].Emails[i].Read, "Y") != 0 && strcmp(users[j].Emails[i].Read, "N") != 0 ){
                           break;
				}
				if (users[j].Emails[i].EmailId == emailId) {
					printf("Email ID: %d", users[j].Emails[i].EmailId);
					
					memset(&fwd[0], 0, sizeof(fwd)); 

					strcpy(fwd, recEmailID);
					printf("fwd ID: %s", fwd);
	
					strcat(fwd, "~");			
					
					printf("fwd ID: %s", fwd);
					
					sprintf(strID, "%d",userId);
					strcat(fwd, strID);
					strcat(fwd, "~"); 
					strcat(fwd, users[j].Emails[i].Subject);
					strcat(fwd, "~");
					strcat(fwd, users[j].Emails[i].Body);
					strcat(fwd, "~");
					strcat(fwd, users[j].Emails[i].AttachmentName);
					strcat(fwd, "~");
					strcat(fwd, users[j].Emails[i].Attachment);
					strcat(fwd, "~");
					strcat(fwd, users[j].Emails[i].DateTimeReceived);
	 
					printf("Forward String: %s", fwd);
					
					result = writeEmail(fwd); 
					
					return result;    
				}
			}
		}
	}
	
	return result;
}

int deleteEmail(int userId, int emailId) 
{
	
	
printf("userId %d and  emailId\n",userId,emailId);

int i,j,k,emailIndex;
int size = 0;
 
  for(j =0 ;j < 10 ;j++)
  {
if(strcmp(users[j].Active, "Y") != 0 && strcmp(users[j].Active, "N") != 0 ){
break;
}
if(users[j].UserID == userId) {
printf("User id matched %d",users[j].UserID);
    emailIndex = -1;
   for(i = 0; i < 10; i++)
{
            if(strcmp(users[j].Emails[i].Read, "Y") != 0 && strcmp(users[j].Emails[i].Read, "N") != 0 ){
                        break;
    }
           if (users[j].Emails[i].EmailId == emailId) {
                 emailIndex = i;
    }
            size++;
       }
     printf("Size is %d and index is %d",size,emailIndex);
     if (emailIndex == -1) {
 return 0;
     }
     else if (size == 1 && emailIndex == 0) {
      // bzero((char *)&users[j].Emails[0], sizeof(struct Email));
memset(&users[j].Emails[0],0,sizeof(users[j].Emails[0]));
        return 1;  
     }
     else {
for(k = emailIndex; k < size-1 ; k++) {
           users[j].Emails[k] = users[j].Emails[k+1];
       }
		//bzero((char *)&users[j].Emails[size-1], sizeof(struct Email));
		memset(&users[j].Emails[size-1],0,sizeof(users[j].Emails[size-1]));
       return 1;
     }
 
}

  }
        return 0;
}

int getMaxEmailId(int userId)
{
 int i,j;
 int maxId = 1;
 for(j = 0; j < 10 ; j++)
   {
if(strcmp(users[j].Active, "Y") != 0 && strcmp(users[j].Active, "N") != 0 ){
break;
}
         if(users[j].UserID == userId) { 
for(i = 0; i < 10; i++)
{
if ((strcmp(users[j].Emails[i].Read, "Y") != 0 && strcmp(users[j].Emails[i].Read, "N") != 0) || users[j].Emails[i].Read == NULL) 
{
          break;
                                }
                                if (users[j].Emails[i].EmailId > maxId) {
                                        maxId = users[j].Emails[i].EmailId;
                                }
                        }
           }
   }
 return maxId;
}

int writeEmail(char data[1000]) {
	int i,j, ret;
	char *ch, emailList[100], *userEmailToken;

	ret = 0;
	int L_EmailId;
	int L_EmailAccount;
	char L_Read[2];
	int L_SenderId;
	int L_ReceiverId;
	char L_Subject[100];
	char L_Body[200];
	char L_AttachmentName[20];
	char L_Attachment[200];
	char L_DateTimeReceived[50];
	
	ch = strtok(data, "~");
	strcpy(emailList, ch);

	ch = strtok(NULL, "~"); 
	trimwhitespace(ch);	
	L_SenderId = atol(ch);

	ch = strtok(NULL, "~");
	trimwhitespace(ch);
	strcpy(L_Subject,ch);

	ch = strtok(NULL, "~");
	trimwhitespace(ch);
	strcpy(L_Body,ch);

	ch = strtok(NULL, "~");
	trimwhitespace(ch);
	strcpy(L_AttachmentName,ch);

	ch = strtok(NULL, "~");
	trimwhitespace(ch);
	strcpy(L_Attachment,ch);

	ch = strtok(NULL, "~");
	trimwhitespace(ch);
	strcpy(L_DateTimeReceived,ch);
	
	
	userEmailToken = strtok(emailList, ";");
	printf("Usre : %s\n", userEmailToken);
	
	while(userEmailToken != NULL)
	{
		for(j =0 ;j < 10 ;j++)
		{
			if(strcmp(users[j].Active, "Y") != 0 && strcmp(users[j].Active, "N") != 0 ){
				break;
			}

			if(strcmp(users[j].EmailID, userEmailToken) == 0) 
			{ 
				for(i = 0; i < 10; i++)
				{
					if((strcmp(users[j].Emails[i].Read, "Y") != 0 && strcmp(users[j].Emails[i].Read, "N") != 0) || users[j].Emails[i].Read == NULL) 
					{
						printf("Usre : %s\n", userEmailToken);
	
						users[j].Emails[i].EmailId = getMaxEmailId(users[j].UserID)+1;
						users[j].Emails[i].EmailAccount = users[j].UserID;
						users[j].Emails[i].ReceiverId= users[j].UserID;

						strcpy( users[j].Emails[i].Read, "N");

						users[j].Emails[i].SenderId = L_SenderId;
						
						strcpy(users[j].Emails[i].Subject,L_Subject);

						strcpy(users[j].Emails[i].Body,L_Body);

						strcpy(users[j].Emails[i].AttachmentName,L_AttachmentName);

						strcpy(users[j].Emails[i].Attachment,L_Attachment);

						strcpy(users[j].Emails[i].DateTimeReceived,L_DateTimeReceived);

						ret = 1;
						break;
					} 
				}
			}
		}
		userEmailToken = strtok(NULL, ";");
	}
	return ret;
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

int updateUserFile(int userId)
{
	FILE *fp;
	int j;
	if((fp = fopen("users.txt","w")) == NULL)
	{
		perror("Error in opening a file.\n");
		return -1;
	}

	for(j =0 ;j < 10 ;j++)
   	{
		if(strcmp(users[j].Active, "Y") != 0 && strcmp(users[j].Active, "N") != 0 ){
			break;
		}

		fprintf(fp,"%d",users[j].UserID);
		fprintf(fp,"~");
		fprintf(fp,"%s",users[j].Active);
		fprintf(fp,"~");
		fprintf(fp,"%s",users[j].EmailID);
		fprintf(fp,"~");
		fprintf(fp,"%s",users[j].Password);
		fprintf(fp,"~");
		fprintf(fp,"%s",users[j].FirstName);
		fprintf(fp,"~");
		fprintf(fp,"%s",users[j].LastName);	
		fprintf(fp,"^\n ");
	}
	fclose(fp);

	bzero((char *)&NewEventID, sizeof(NewEventID));
	NewEventID = (char *) shmat(shm_id1, NULL, 0);

	FILE *read_eventID;
	read_eventID = fopen("eventID.txt", "w");
	if(read_eventID == NULL)
    	{
		perror("Error");
		return -1;
   	}
	else
    	{
		fprintf(read_eventID,"%s",NewEventID);
	}

	fclose(read_eventID);
	shmdt((void *) NewEventID);

	return 0;
}

int logoffUser(int userId,char *buff) 
{
	FILE *fp1, *fp2;
	char emailFileName[20], calendarFileName[20];

 	int i, j, ret;
	
	ret = updateUserFile(userId);
	
	if(ret == -1 )
	{
		sprintf(buff,"%s","Error in opening a users file.");
		return -1;
	}

	
	for(j =0 ;j < 10 ;j++)
	{
		if(strcmp(users[j].Active, "Y") != 0 && strcmp(users[j].Active, "N") != 0 )
		{
			break;
		}	
		
		
		if(users[j].UserID == userId) 
		{
			
			sprintf(emailFileName, "%d_email.txt", users[j].UserID);
				
			if((fp1 = fopen(emailFileName,"w")) == NULL)
			{
				perror("Error in opening a file.\n");
				sprintf(buff,"%s","Error in opening a email file.\0");
				return -1;
			}
			
			for(i = 0; i < 10; i++)
			{
				if ((strcmp(users[j].Emails[i].Read, "Y") != 0 && strcmp(users[j].Emails[i].Read, "N") != 0) || users[j].Emails[i].Read == NULL) 
				{
					break;
				}
				fprintf(fp1,"%d",users[j].Emails[i].EmailId);
				fprintf(fp1,"~");
				fprintf(fp1,"%d",users[j].Emails[i].EmailAccount);
				fprintf(fp1,"~");
				fprintf(fp1,"%s",users[j].Emails[i].Read);
				fprintf(fp1,"~");
				fprintf(fp1,"%d",users[j].Emails[i].SenderId);
				fprintf(fp1,"~");
				fprintf(fp1,"%d",users[j].Emails[i].ReceiverId);
				fprintf(fp1,"~");
				fprintf(fp1,"%s",users[j].Emails[i].Subject);
				fprintf(fp1,"~");
				fprintf(fp1,"%s",users[j].Emails[i].Body);
				fprintf(fp1,"~");
				fprintf(fp1,"%s",users[j].Emails[i].AttachmentName);
				fprintf(fp1,"~");
				fprintf(fp1,"%s",users[j].Emails[i].Attachment);
				fprintf(fp1,"~");
				fprintf(fp1,"%s",users[j].Emails[i].DateTimeReceived);
				fprintf(fp1,"^\n ");	
			}
			fclose(fp1);
			
			
			sprintf(calendarFileName, "%d_calendar.txt", users[j].UserID);
				
			if((fp2 = fopen(calendarFileName,"w")) == NULL)
			{
				perror("Error in opening a file.\n");
				sprintf(buff,"%s","Error in opening a calendar file.\0");
				return -1;
			}
				
			for(i = 0; i < 10; i++)
			{
				if ((strcmp(users[j].Calendars[i].Read, "Y") != 0 && strcmp(users[j].Calendars[i].Read, "N") != 0) 
					|| users[j].Calendars[i].Read == NULL) 
				{
					break;
				}
				fprintf(fp2,"%d",users[j].Calendars[i].EventId);
				fprintf(fp2,"~");
				fprintf(fp2,"%d",users[j].Calendars[i].SenderId);
				fprintf(fp2,"~");
				fprintf(fp2,"%d",users[j].Calendars[i].ReceipientId);
				fprintf(fp2,"~");
				fprintf(fp2,"%s",users[j].Calendars[i].Subject);
				fprintf(fp2,"~");
				fprintf(fp2,"%s",users[j].Calendars[i].Read);
				fprintf(fp2,"~");
				fprintf(fp2,"%s",users[j].Calendars[i].EventDesc);
				fprintf(fp2,"~");
				fprintf(fp2,"%s",users[j].Calendars[i].Location);
				fprintf(fp2,"~");
				fprintf(fp2,"%s",users[j].Calendars[i].StartDate);
				fprintf(fp2,"~");
				fprintf(fp2,"%s",users[j].Calendars[i].StartHour);
				fprintf(fp2,"~");
				fprintf(fp2,"%s",users[j].Calendars[i].EndDate);
				fprintf(fp2,"~");
				fprintf(fp2,"%s",users[j].Calendars[i].EndHour);
				fprintf(fp2,"~");
				fprintf(fp2,"%s",users[j].Calendars[i].Attachment);
				fprintf(fp2,"~");
				fprintf(fp2,"%s",users[j].Calendars[i].AttachmentName);
				fprintf(fp2,"^\n ");
			}
		    fclose(fp2);
			
		}
	}
	sprintf(buff,"%s","User Successfully Logged Off.\0");
	return 1;
}

int shutdownServer(char *buff) 
{
	int j, ret = 0;
	
	
	for(j =0 ;j < 10 ;j++)
	{
		if(strcmp(users[j].Active, "Y") != 0 && strcmp(users[j].Active, "N") != 0 )
		{
			break;
		}	
		ret = logoffUser(users[j].UserID, buff);
	}
	
	if (ret == 1)
	{
		sprintf(buff,"%s","Successfully Shutdown Server.\n");
		ret = 999;
	}else
	{
		sprintf(buff,"%s","Unable Shutdown Server.\n");
	}
	
	//shmctl(shm_id, IPC_RMID, NULL);	// removing old shared memorry for the same key.
	//shmctl(shm_id1, IPC_RMID, NULL);	// removing old shared memorry for the same key.
	//shmctl(shm_id2, IPC_RMID, NULL);	// removing old shared memorry for the same key.
	
	return ret;
}

int getSenderDetails(int userId, char *senderInfo) {
	int j;
	char field[500];
	for (j=0 ;j < 10 ;j++) 
	{
		if(strcmp(users[j].Active, "Y") != 0 && strcmp(users[j].Active, "N") != 0 ){
			break;
		}
		if(users[j].UserID == userId) {
		        strcat(senderInfo, " Sender Emaild ID :");
		        strcat(senderInfo, users[j].EmailID);
			    strcat(senderInfo, " Sender Full Name :");	
				strcat(senderInfo, users[j].FirstName);
		        strcat(senderInfo, " ");
				strcat(senderInfo, users[j].LastName);
		}
 
	}
}

int readAllEmails(int userId,char *buffer) {
   int i,j,k;
   char field[500],senderInfo[200], emailNO[10];
   memset(&field[0], 0, sizeof(field));
   for(j =0 ;j < 10 ;j++)
   {
		if(strcmp(users[j].Active, "Y") != 0 && strcmp(users[j].Active, "N") != 0 ){
			break;
		}
        if(users[j].UserID == userId) 
		{
			k=0;
			for(i = 0; i < 10; i++)
			{

				if(DEBUG > 0)
				{
					printf("userId: %d\n", users[j].UserID);
					printf("Read: %s\n", users[j].Emails[i].Read);
				}
				if(strcmp(users[j].Emails[i].Read, "Y") != 0 && strcmp(users[j].Emails[i].Read, "N") != 0 ){
					break;
				}
				memset(&senderInfo[0], 0, sizeof(senderInfo));  
									
				sprintf(emailNO, "%d", users[j].Emails[i].EmailId);
				if(i == 0 )
				{
					strcpy(buffer, "\nEmail No: ");
					strcat(buffer, emailNO);
				}else
				{
					strcpy(field, "\nEmail No: ");
					strcat(field, emailNO);
					strcat(buffer, field);
				}
				

				getSenderDetails(users[j].Emails[i].SenderId,senderInfo);		
				strcpy(field,senderInfo);	
				strcat(buffer, field);
		
				
				strcat(buffer, "     Subject :");
				strcpy(field, users[j].Emails[i].Subject);	
				strcat(buffer,field);
			
			
				if(strcmp(users[j].Emails[i].AttachmentName, "") != 0) 
				{
					strcat(buffer, "     Attachment Name :");
					strcpy(field,users[j].Emails[i].AttachmentName);	
					strcat(buffer,field);
				}
				
				strcat(buffer, "     Date :");				
				strcpy(field, users[j].Emails[i].DateTimeReceived);	
				strcat(buffer,field);
				
				strcat(buffer, "~");
			}
			if(DEBUG > 0)
			{
				printf("Emails: %s\n", buffer);
			}
			return k;
		}
    }
	return 0;
}

int filterEmails(int userId, char data[100], char *buffer)
{
	int i,j,k, add_Email;
	char field[500],senderInfo[200], emailNO[10], temp[100], criteria[2], *tok, strData[100], senderID[30];
	memset(&field[0], 0, sizeof(field));
	char year[10], month[10], date[10], *dateTok, dateField[20];
				
   strcpy(temp, data);
   add_Email = 0;
   tok = strtok(temp, "~");
   strcpy(criteria, tok);
   
   tok = strtok(NULL, "~");
   strcpy(strData, tok);
   
   for(j =0 ;j < 10 ;j++)
   {
		if(strcmp(users[j].Active, "Y") != 0 && strcmp(users[j].Active, "N") != 0 ){
			break;
		}
        if(users[j].UserID == userId) 
		{
			k=0;
			for(i = 0; i < 10; i++)
			{

				if(DEBUG > 0)
				{
					printf("userId: %d\n", users[j].UserID);
					printf("Read: %s\n", users[j].Emails[i].Read);
				}
				if(strcmp(users[j].Emails[i].Read, "Y") != 0 && strcmp(users[j].Emails[i].Read, "N") != 0 ){
					break;
				}
				if(strcmp(criteria, "S") == 0)
				{
					memset(&senderID[0], 0, sizeof(senderID));  
					getUserEmailID(users[j].Emails[i].SenderId, senderID);
					
					if(strstr(senderID, strData) != NULL)
					{
						add_Email = 1;
					}else
					{
						add_Email = 0;
					}
					
				}
				
				if(strcmp(criteria, "M") == 0)
				{
					if(strstr(users[j].Emails[i].Subject, strData) != NULL)
					{
						add_Email = 1;
					}else
					{
						add_Email = 0;
					}
					
				}
				
				if(strcmp(criteria, "D") == 0)
				{	
					int day = 0;
					
					strcpy(dateField, strData);
					dateTok = strtok(dateField, "/");
					strcpy(month, dateTok);
					
					dateTok = strtok(NULL, "/");
					strcpy(date, dateTok);
					day = atol(date);
					
					sprintf(date, "%d", day);
					
					dateTok = strtok(NULL, "/");
					strcpy(year, dateTok);
					
					if(	strstr(users[j].Emails[i].DateTimeReceived, year) != NULL &&
						strstr(users[j].Emails[i].DateTimeReceived, month) != NULL &&
						strstr(users[j].Emails[i].DateTimeReceived, date) != NULL )
					{
						add_Email = 1;
					}else
					{
						add_Email = 0;
					}
					
				}
				
				if(add_Email == 1)
				{
					memset(&senderInfo[0], 0, sizeof(senderInfo));  
										
					sprintf(emailNO, "%d", users[j].Emails[i].EmailId);
					if(i == 0 )
					{
						memset(&field[0], 0, sizeof(field));
	   
						strcpy(buffer, "\n\nEmail No: ");
						strcat(buffer, emailNO);
					}else
					{
						strcat(field, "\nEmail No: ");
						strcat(field, emailNO);
						strcat(buffer, field);
					}
					

					getSenderDetails(users[j].Emails[i].SenderId,senderInfo);		
					strcpy(field,senderInfo);	
					strcat(buffer, field);
			
					strcat(buffer, "     Subject :");
					strcpy(field, users[j].Emails[i].Subject);	
					strcat(buffer,field);
				
				
					if(strcmp(users[j].Emails[i].AttachmentName, "") != 0) 
					{
						strcat(buffer, "     Attachment Name :");
						strcpy(field,users[j].Emails[i].AttachmentName);	
						strcat(buffer,field);
					}
					
					strcat(buffer, "     Date :");				
					strcpy(field, users[j].Emails[i].DateTimeReceived);	
					strcat(buffer,field);
					
					strcat(buffer, "~");
				}
			}
			if(DEBUG > 0)
			{	
				printf("Emails: %s\n", buffer);
			}
			
			return k;
		}
    }
	return 0;
}


int openEmail(int userId,int emailId,char *buffer) {

	int i,j,k;
	char field[500],senderInfo[200],strID[10];
	memset(&field[0], 0, sizeof(field));
	for(j =0 ;j < 10 ;j++)
	{
		if(strcmp(users[j].Active, "Y") != 0 && strcmp(users[j].Active, "N") != 0 )
		{
			break;
		}
        
		if(users[j].UserID == userId)
		{
			k=0;
			for(i = 0; i < 10; i++)
			{
				if(users[j].Emails[i].EmailId == emailId) 
				{
					if(DEBUG > 0)
					{
						printf("userId: %d\n", users[j].UserID);
					}
					
					memset(&senderInfo[0], 0, sizeof(senderInfo));
					
					strcpy(users[j].Emails[i].Read, "Y");
								
					if(i == 0 )
					{
						strcpy(buffer, "\nEmail No: ");
						sprintf(strID, "%d",users[j].Emails[i].EmailId);
					    strcat(buffer, strID);
					}else
					{
						strcpy(field, "\nEmail No: ");
						sprintf(strID, "%d",users[j].Emails[i].EmailId);
						strCatMessage(buffer, strID);
					}
					
					getSenderDetails(users[j].Emails[i].SenderId,senderInfo);	
                    strcpy(field,senderInfo);	
					strCatMessage(buffer, field);
		            strcat(buffer, "\nSubject :");
					strcpy(field, users[j].Emails[i].Subject);	
					strCatMessage(buffer,field);
				
					strcat(buffer, "\nMessage body :");
					strcpy(field,users[j].Emails[i].Body);	
					strCatMessage(buffer,field);
				
					strcat(buffer, "\nAttachment Name :");
					strcpy(field,users[j].Emails[i].AttachmentName);	
					strCatMessage(buffer,field);

					strcat(buffer, "\nAttachment :");
					strcpy(field,users[j].Emails[i].Attachment);	
					strCatMessage(buffer,field);

					strcat(buffer, "\nDate :");				
					strcpy(field, users[j].Emails[i].DateTimeReceived);	
					strCatMessage(buffer,field);
					
					return 1;
					
				}
				
			}
	    
		}
	}
	
	if(DEBUG > 0)
		printf("%s\n", buffer);
	return 0;
}


int getEmailID(int userId, int emailId, char *senderInfo) {
	int i,j;
	char field[500];
	for (j=0 ;j < 10 ;j++) 
	{
		if(strcmp(users[j].Active, "Y") != 0 && strcmp(users[j].Active, "N") != 0 ){
			break;
		}
		if(users[j].UserID == userId) {
		
			for(i = 0; i < 10; i++)
			{
				if ((strcmp(users[j].Emails[i].Read, "Y") != 0 && strcmp(users[j].Emails[i].Read, "N") != 0)) 
				{
					break;
				}
				if (users[j].Emails[i].EmailId == emailId) {
					strcat(senderInfo, users[j].EmailID);
			        return 1;
				}
		    
			}
		}
 
	}
	return 0;
}

int replyEmail(char data[1000]) {
	int i,j,emailNo,senderId, senderIndex, emailIndex;
	char senderInfo[200];
	char *ch;
	ch = strtok(data, "~");
	emailNo = atol(ch);
	ch = strtok(NULL , "~");
	senderId = atol(ch);
	memset(&senderInfo[0], 0, sizeof(senderInfo)); 
	getEmailID(senderId,emailNo,senderInfo);
	senderIndex = 0;
	emailIndex = 0;

	for (j=0 ;j < 10 ;j++) 
	{
		if(strcmp(users[j].Active, "Y") != 0 && strcmp(users[j].Active, "N") != 0 ){
			break;
		}

		if(users[j].UserID == senderId) {
		
			for(i = 0; i < 10; i++)
			{
				if ((strcmp(users[j].Emails[i].Read, "Y") != 0 && strcmp(users[j].Emails[i].Read, "N") != 0)) 
				{
					break;
				}

				if (users[j].Emails[i].EmailId == emailNo) {
					senderIndex = j;
					emailIndex = i;
			        	break;
				}
		    
			}
		}
 
	}
	
	for(j =0 ;j < 10 ;j++)
	{
		if(strcmp(users[j].Active, "Y") != 0 && strcmp(users[j].Active, "N") != 0 ){
			break;
		}

      	if(strcmp(users[j].EmailID,senderInfo) == 0) 
		{ 
			for(i = 0; i < 10; i++)
			{
				if ((strcmp(users[j].Emails[i].Read, "Y") != 0 && strcmp(users[j].Emails[i].Read, "N") != 0) || users[j].Emails[i].Read == NULL) 
				{
					users[j].Emails[i].EmailId = getMaxEmailId(users[j].UserID)+1;
					users[j].Emails[i].EmailAccount = users[j].UserID;
					users[j].Emails[i].ReceiverId= users[j].UserID;
				
					strcpy( users[j].Emails[i].Read, "N");
				    	users[j].Emails[i].SenderId = senderId;
		
					strcpy(users[j].Emails[i].Subject,users[senderIndex].Emails[emailIndex].Subject); 
		
					ch = strtok(NULL, "~");
					strcpy(users[j].Emails[i].Body,ch);
		
					strcpy(users[j].Emails[i].AttachmentName, users[senderIndex].Emails[emailIndex].AttachmentName);
					
					strcpy(users[j].Emails[i].Attachment, users[senderIndex].Emails[emailIndex].Attachment);
					
					ch = strtok(NULL, "~");
					strcpy(users[j].Emails[i].DateTimeReceived,ch);
					
					return 1;
				}	
			}
        }
    }
	return 0;
}


int readAllCalendars(int userId,char *buffer) {
	int i,j,k,x,y;
	char field[500],senderInfo[200], eventNo[10];
	memset(&field[0], 0, sizeof(field));
	   
   	for(j =0 ;j < 10 ;j++)
   	{
		if(strcmp(users[j].Active, "Y") != 0 && strcmp(users[j].Active, "N") != 0 ){
			break;
		}
		
		if(users[j].UserID == userId) 
		{
			for(i = 0; i < 10; i++)
			{
				
				if ((strcmp(users[j].Calendars[i].Read, "Y") != 0 && strcmp(users[j].Calendars[i].Read, "N") != 0) 
					|| users[j].Calendars[i].Read == NULL) 
				{
					break;
				}
				
				if(DEBUG > 0)
				{
					printf("userId: %d\n", users[j].UserID);
				}
				
				memset(&senderInfo[0], 0, sizeof(senderInfo));  
				strcpy(users[j].Calendars[i].Read, "Y");
				
				k++;
				
				sprintf(eventNo, "%d", users[j].Calendars[i].EventId);
				
				if(i == 0 )
				{
					strcpy(buffer, "\n\nEvent No: ");
					strcat(buffer, eventNo);
				}else
				{
					strcpy(field, "\n\nEvent No: ");
					strcat(field, eventNo);
					strCatMessage(buffer, field);
				}
			
				getSenderDetails(users[j].Calendars[i].SenderId,senderInfo);		
				strcpy(field,senderInfo);	
				strCatMessage(buffer, field);

				strcat(buffer, "\nSubject : ");
				strcpy(field, users[j].Calendars[i].Subject);	
				strCatMessage(buffer,field);
				
				/*
				strcat(buffer, "\Attendees : ");
				for(x =0 ;x < 10 ;j++)
				{
					if(strcmp(users[x].Active, "Y") != 0 && strcmp(users[x].Active, "N") != 0 ){
						break;
					}
					
					for(y = 0; y < 10; y++)
					{
						
						if ((strcmp(users[x].Calendars[y].Read, "Y") != 0 && strcmp(users[x].Calendars[y].Read, "N") != 0) 
							|| users[x].Calendars[y].Read == NULL) 
						{
							break;
						}
						
						if (atoi(eventNo) == users[x].Calendars[y].EventId)
						{
							strcat(buffer, users[x].FirstName);	
							strcat(buffer, " ");	
							strcat(buffer, users[x].LastName);	
							strcat(buffer, " ; ");	
							break;
						}
					}
				}
				strcat(buffer, "~");
				*/			
				strcat(buffer, "\nEvent Description : ");
				strcpy(field,users[j].Calendars[i].EventDesc);	
				strCatMessage(buffer,field);
				
				strcat(buffer, "\nLocation : ");
				strcpy(field,users[j].Calendars[i].Location);	
				strCatMessage(buffer,field);

				strcat(buffer, "\nStarting : ");
				strcpy(field,users[j].Calendars[i].StartDate);
				strcat(field," ");
				strcat(field,users[j].Calendars[i].StartHour);

				strCatMessage(buffer,field);

				strcat(buffer, "\nEnding : ");				
				strcpy(field,users[j].Calendars[i].EndDate);
				strcat(field," ");
				strcat(field,users[j].Calendars[i].EndHour);
				
				strCatMessage(buffer,field);
				
				strcat(buffer, "\nAttachment : ");				
				strcpy(field,users[j].Calendars[i].Attachment);
				
				strCatMessage(buffer,field);
				
			}
			if(DEBUG > 0)
			{
				printf("Calendar Events: %s\n", buffer);
			}
			return k;
		}
	}
	return 0;
}

int readNewCalendars(int userId,char *buffer) {
   int i,j,k;
   char field[500],senderInfo[200],eventNo[10];
   memset(&field[0], 0, sizeof(field));
   
   for(j =0 ;j < 10 ;j++)
   {
		if(strcmp(users[j].Active, "Y") != 0 && strcmp(users[j].Active, "N") != 0 ){
			break;
		}
        if(users[j].UserID == userId) 
		{
			k=0;
			for(i = 0; i < 10; i++)
			{
				if(DEBUG > 0)
				{
					printf("userId: %d\n", users[j].UserID);
				}
				
				if(strcmp(users[j].Emails[i].Read, "N") == 0) 
				{
					k++;
					memset(&senderInfo[0], 0, sizeof(senderInfo));  
					strcpy(users[j].Calendars[i].Read, "Y");
					
					sprintf(eventNo, "%d", users[j].Calendars[i].EventId);
					if(i == 0 )
					{
						strcat(buffer, "\n\nEvent No: ");
						strcat(buffer, eventNo);
					}else
					{
						strcat(field, "\n\nEvent No: ");
						strcat(field, eventNo);
						strcat(field, eventNo);
						strCatMessage(buffer, field);
					}


					getSenderDetails(users[j].Calendars[i].SenderId,senderInfo);		
					strcpy(field,senderInfo);	
					strCatMessage(buffer, field);
					
					strcat(buffer, "\nSubject :");
					strcpy(field, users[j].Calendars[i].Subject);	
					strCatMessage(buffer,field);
					
					strcat(buffer, "\nEvent Description :");
					strcpy(field,users[j].Calendars[i].EventDesc);	
					strCatMessage(buffer,field);
					
					strcat(buffer, "\Location :");
					strcpy(field,users[j].Calendars[i].Location);	
					strCatMessage(buffer,field);

					strcat(buffer, "\nStarting :");
					strcpy(field,users[j].Calendars[i].StartDate);
					strcpy(field," ");
					strcpy(field,users[j].Calendars[i].StartHour);

					strCatMessage(buffer,field);

					strcat(buffer, "\nEnding :");				
					strcpy(field,users[j].Calendars[i].EndDate);
					strcpy(field," ");
					strcpy(field,users[j].Calendars[i].EndHour);

					strCatMessage(buffer,field);
					
					strcat(buffer, "\Attachment :");				
					strcpy(field,users[j].Calendars[i].Attachment);
				
					strCatMessage(buffer,field);
				}
			}
			if(DEBUG > 0)
			{
				printf("Calendars: %s\n", buffer);
			}
			return k;
		}
    }
	return 0;
}

int readNewEmails(int userId,char *buffer) {
	int i,j,k;
	char field[500],senderInfo[200], emailNO[10];
	memset(&field[0], 0, sizeof(field));
	for(j =0 ;j < 10 ;j++)
	{
		if(strcmp(users[j].Active, "Y") != 0 && strcmp(users[j].Active, "N") != 0 )
		{
			break;
		}
        
		if(users[j].UserID == userId)
		{
			k=0;
			for(i = 0; i < 10; i++)
			{
				if(strcmp(users[j].Emails[i].Read, "N") == 0) 
				{
					if(DEBUG > 0)
					{
						printf("userId: %d\n", users[j].UserID);
					}
					
					k++;
						
					sprintf(emailNO, "%d", users[j].Emails[i].EmailId);
					
					if(i == 0 )
					{
						strcpy(buffer, "\nEmail No: ");
						strcat(buffer, emailNO);
					}else
					{
						strcpy(field, "\nEmail No: ");
						strcat(field, emailNO);
						strcat(buffer, field);
					}
					
					memset(&senderInfo[0], 0, sizeof(senderInfo));  
					
					getSenderDetails(users[j].Emails[i].SenderId, senderInfo);		
					strcpy(field,senderInfo);	
					strcat(buffer, field);
		
					strcat(buffer, " Subject :");
					strcpy(field, users[j].Emails[i].Subject);	
					strcat(buffer,field);
				
					
					if(strcmp(users[j].Emails[i].AttachmentName, "") != 0) 
					{
						strcat(buffer, " Attachment Name :");
						strcpy(field,users[j].Emails[i].AttachmentName);	
						strcat(buffer,field);
					}
					 
					strcat(buffer, " Date :");				
					strcpy(field, users[j].Emails[i].DateTimeReceived);	
					strcat(buffer,field);
					strcat(buffer, "~");
				}
			}
			
			if(DEBUG > 0)
				printf("eMAILS: %s\n", buffer);
			return k;
		}
	}
	if(DEBUG > 0)
		printf("%s\n", buffer);
	return k;
}

int checkNewEmails(int userId,char *buffer) {
   int i,j,k;
   char field[500];
   memset(&field[0], 0, sizeof(field));
   sprintf(buffer,"%s", "Checked New Emails");
   for(j =0 ;j < 10 ;j++)
   {
		if(strcmp(users[j].Active, "Y") != 0 && strcmp(users[j].Active, "N") != 0 ){
			break;
		}
                
		if(users[j].UserID == userId) {
			k=0;
			for(i = 0; i < 10; i++)
			{
				if(strcmp(users[j].Emails[i].Read, "N") == 0) 
				{
					k++;
				}
			}
			return k;
		}
    }
	
	if(DEBUG > 0)
		printf("%s\n", buffer);
	return k;
}

int checkNewCalendars(int userId,char *buffer) {
	int i,j,k;
	char field[500],senderInfo[200];
	memset(&field[0], 0, sizeof(field));
	sprintf(buffer,"%s", "Checked New Calendars");
	for(j =0 ;j < 10 ;j++)
	{
		if(strcmp(users[j].Active, "Y") != 0 && strcmp(users[j].Active, "N") != 0 ){
			break;
		}
        if(users[j].UserID == userId) 
		{
			k=0;
			for(i = 0; i < 10; i++)
			{
				if(DEBUG > 0)
				{
					printf("userId: %d\n", users[j].UserID);
				}
				
				if(strcmp(users[j].Calendars[i].Read, "N") == 0) 
				{
                			k++;
				}
			}
			if(DEBUG > 0)
			{
				printf("Calendars: %s\n", buffer);
			}
			return k;
		}
    }
	return 0;
}

void error(char *msg)
{
	perror(msg);
	exit(1);
}

void setSemaphoreAndSharedMemory()
{
	char *buff;
	struct User TempUsers[10];
	
	wait.sem_num = 0;
	wait.sem_op = -1;
	wait.sem_flg = SEM_UNDO;

	post.sem_num = 0;
	post.sem_op = 1;
	post.sem_flg = SEM_UNDO;

	if((semid_lock = semget(ftok(".", 3),1, IPC_CREAT | 0666))  < 0)
		perror("Error in Crating lock Sem\n\n");

	if((semctl(semid_lock, 0, SETVAL, 1)) < 0)
		perror("Error in init lock Sem\n\n");

	semop(semid_lock, &wait, 1);

	memcpy(TempUsers, readUsers(), sizeof(struct User) * 10);


	shm_id = shmget(ftok(".",4), sizeof(struct User) * 10, IPC_CREAT | 0666);
	shmctl(shm_id, IPC_RMID, NULL);	// removing old shared memorry for the same key.

	shm_id = shmget(ftok(".",4), sizeof(struct User) * 10, IPC_CREAT | 0666);

	shm_id1 = shmget(ftok(".",5), 20, IPC_CREAT | 0666);
	shmctl(shm_id1, IPC_RMID, NULL);	// removing old shared memorry for the same key.

	shm_id1 = shmget(ftok(".",5), 20, IPC_CREAT | 0666);
	
	shm_id2 = shmget(ftok(".",6), 20, IPC_CREAT | 0666);
	shmctl(shm_id2, IPC_RMID, NULL);	// removing old shared memorry for the same key.

	shm_id2 = shmget(ftok(".",6), 20, IPC_CREAT | 0666);

	users = (struct User*) shmat(shm_id, NULL, 0);
	NewEventID = shmat(shm_id1, NULL, 0);
	
	Shutdown = shmat(shm_id2, NULL, 0);
	strcpy(Shutdown, "No");
	
	
	FILE *read_eventID;
	read_eventID = fopen("eventID.txt", "r");
	if(read_eventID == NULL)
    	{
		perror("Error");
   	}
	else
    	{
		buff = (char*)malloc(sizeof(char) * 20);
		
		if(buff == NULL)
		{
			perror("Memory Error: \n");
			fclose(read_eventID);
			exit(0);
		}
		
		fread(buff,1,20,read_eventID);

		memcpy(NewEventID, buff, sizeof(buff));
	}
	fclose(read_eventID);
	
	memcpy(users, TempUsers,  sizeof(TempUsers));
	
	fillEmails();
	
	fillCalenders();
	
	if(DEBUG > 0)
    {
		printUserDetails();
    }       
	
	shmdt((void *) users);
	shmdt((void *) NewEventID);
	shmdt((void *) Shutdown);
  
	semop(semid_lock, &post, 1);
	
}

void getSemaphoreAndSharedMemory()
{
    if((semid_lock = semget(ftok(".", 3),1, 0)) < 0)
	perror("Error in child Crating lock Sem\n\n");

    shm_id = shmget(ftok(".",4), sizeof(struct User) * 10, 0666);
    shm_id1 = shmget(ftok(".",5), 20, 0666);	
    shm_id2 = shmget(ftok(".",6), 20, 0666);	
}

void UserList(char *buffer) {
	int i,j;
	char field[500];
	memset(&field[0], 0, sizeof(field));
	for(j =0 ;j < 10 ;j++)
	{
		if(strcmp(users[j].Active, "Y") != 0 && strcmp(users[j].Active, "N") != 0 ){
			break;
		}
  
		strcpy(field, users[j].EmailID); 
		strcat(field, "\n Clendar Event:\n"); 
		strCatMessage(buffer,field);
		
		for(i = 0; i < 10; i++)
		{
			
			if ((strcmp(users[j].Calendars[i].Read, "Y") != 0 && strcmp(users[j].Calendars[i].Read, "N") != 0) 
				|| users[j].Calendars[i].Read == NULL) 
			{
				break;
			}
			
			if(DEBUG > 0)
			{
				printf("userId: %d\n", users[j].UserID);
			}
			
			strcat(buffer, "\nSubject : ");
			strcpy(field, users[j].Calendars[i].Subject);	
			strCatMessage(buffer,field);
			
			strcat(buffer, "\nStarting : ");
			strcpy(field,users[j].Calendars[i].StartDate);
			strcat(field," ");
			strcat(field,users[j].Calendars[i].StartHour);
			
			strCatMessage(buffer,field);

			strcat(buffer, "\nEnding : ");				
			strcpy(field,users[j].Calendars[i].EndDate);
			strcat(field," ");
			strcat(field,users[j].Calendars[i].EndHour);
			strCatMessage(buffer,field);
		}	
	}
}

int deleteCalender(int uid, int EventId) 
{
	int i,j,k,calIndex, ret = 0;
	int size = 0;
	for(j =0 ;j < 10 ;j++)
    {
		if(strcmp(users[j].Active, "Y") != 0 && strcmp(users[j].Active, "N") != 0 ){
			break;
		}
		calIndex = -1;
		for(i = 0; i < 10; i++)
		{
			if(strcmp(users[j].Calendars[i].Read, "Y") != 0 && strcmp(users[j].Calendars[i].Read, "N") != 0 ){
				break;
			}
			if (users[j].UserID == uid)
			{
				if(users[j].Calendars[i].EventId == EventId) {
					calIndex = i;
				}
			}
			size++;   
		}
		
		if (calIndex == -1) {
			printf("reached first ret\n");
		}
		else if (size == 1 && calIndex == 0) 
		{
			memset(&users[j].Calendars[0],0,sizeof(users[j].Calendars[0]));
			ret = 1;
			printf("reached second ret\n");
        }
        else
		{
			for(k = calIndex; k < size-1 ; k++)
			{
				users[j].Calendars[k] = users[j].Calendars[k+1];
			}
			memset(&users[j].Calendars[size-1],0,sizeof(users[j].Calendars[size-1]));
			ret = 1;
			printf("reached thrid ret\n");
        } 
  
	}
	
	printf(" ret %d\n", ret);
			
	return ret;
}

int downloadAttachment(char data[100],char *buffer) 
{
	int i,j,userId,id;
	char *ch;
	char opt[2];
	ch = strtok(data, "~");
	userId = atol(ch);
        printf("userId %d",userId);
        ch = strtok(NULL , "~");
	strcpy(opt,ch);
        printf("char is %s",opt);
	ch = strtok(NULL , "~");
	id = atol(ch);
        printf("emaildId %d",id);
	
	for(j =0 ;j < 10 ;j++)
	{
		if(strcmp(users[j].Active, "Y") != 0 && strcmp(users[j].Active, "N") != 0 ){
		break;
		}
  
		if (users[j].UserID == userId)
		{
			if(strcmp(opt, "E") == 0 )
			{
				for(i = 0; i < 10; i++)
				{
					if ((strcmp(users[j].Emails[i].Read, "Y") != 0 && strcmp(users[j].Emails[i].Read, "N") != 0) || users[j].Emails[i].Read == NULL) 
					{
						break;
					} 
					
					if (users[j].Emails[i].EmailId == id)
					{
						strcpy(buffer,users[j].Emails[i].AttachmentName);
						strcat(buffer, "~");
						strcat(buffer,users[j].Emails[i].Attachment);
						return 1;
					}
				}
			}
			else if (strcmp(opt, "C") == 0)
			{
				for(i = 0; i < 10; i++)
				{
					if ((strcmp(users[j].Calendars[i].Read, "Y") != 0 && strcmp(users[j].Calendars[i].Read, "N") != 0) || users[j].Calendars[i].Read == NULL) 
					{
						if (users[j].Calendars[i].EventId == id) {
							strcpy(buffer,users[j].Calendars[i].AttachmentName);
							strcat(buffer, "~");
							strcat(buffer,users[j].Calendars[i].Attachment);
							return 1;
						}		
					}
				}
			}
		}
	}
	return 0;
}

int main(int argc, char *argv[])
{
	setSemaphoreAndSharedMemory();
	calendarServer(argv[1]);

	printf("\n***   Email/Calendar Server Has Been Shut-Down!    ****\n");
	return 0;
}

void *calendarServer(char *port)
{
	int sockfd,newsockfd,portno,clilen;
	char buffer[MAX_CHARACTER], reply[MAX_CHARACTER];
	char opt[2],cmd[20],data[1000];
	char *st;
	struct sockaddr_in serv_addr,cli_addr;
	int n,pid,random,counter,mode,childpid,i,x,len,result;

	sockfd = socket(AF_INET,SOCK_STREAM,0);
	portno = atoi(port);
	if(sockfd < 0)
    {
		error("ERROR opening socket");
    }
  
	bzero((char *) &serv_addr,sizeof(serv_addr));
  
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
  
	if(bind(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
    {
		error("ERROR on binding");
    }
	
	listen(sockfd,10);
	printf("\n***   Email/Calendar Server Is Running!    ****\n");	
    
	for(;;)
	{
		clilen = sizeof(cli_addr);
		newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr,&clilen);
		
		if(newsockfd <0)
		{
			error("ERROR on accept");
		}
		if((childpid=fork())==0)
		{
			close(sockfd);
			getSemaphoreAndSharedMemory();

			while(1)
			{
				memset(&buffer[0],0,sizeof(buffer));
				recv(newsockfd,buffer,MAXLINE,0);
						
				
				bzero((char *)&Shutdown, sizeof(Shutdown));

				Shutdown = (char *) shmat(shm_id2, NULL, 0);
					
				if (DEBUG > 0)
					printf("check shutdown in child process %s \n", Shutdown);
			
				if (strcmp(Shutdown,"Yes") == 0) 
				{
					memset(&buffer[0],0,sizeof(buffer));
					
					sprintf(buffer, "%s", "999~\nServer Shutdown.\nUnable To Process Current Request.\nYour Previous Actions Were Successfully Saved.");
					
					send(newsockfd,buffer,strlen(buffer),0);
					close(newsockfd);
					shmdt((void *) Shutdown);
				
					exit(0);
				}
				
				shmdt((void *) Shutdown);
				
				
				if(DEBUG > 0)
				{
					printf("REACHED read Command : %s ", buffer);
				}
				
				st = strtok(buffer, "~");
				strcpy(cmd,st);
				st = strtok(NULL, "|");
				strcpy(data,st);

				if(strcmp(cmd,"CMD_LOGIN") == 0) 
				{	
					memset(&buffer[0],0,sizeof(buffer));

					semop(semid_lock, &wait, 1);
				
					bzero((char *)&users, sizeof(users));
					
					users = (struct User*) shmat(shm_id, NULL, 0);
					
					if(DEBUG == 0)
					{
						printUserDetails();
					}
					
					result= validateUser(data);
					
					shmdt((void *) users);
					semop(semid_lock, &post, 1);

					sprintf(buffer,"%d",result);
					send(newsockfd,buffer,strlen(buffer),0);
				}
				else if( strcmp(cmd,"CMD_REGISTER") == 0)
				{
					memset(&buffer[0],0,sizeof(buffer));

					semop(semid_lock, &wait, 1);
				
					bzero((char *)&users, sizeof(users));
					users = (struct User*) shmat(shm_id, NULL, 0);			
					result = registration(data);
					shmdt((void *) users);
					
					semop(semid_lock, &post, 1);

					sprintf(buffer,"%d",result);
					send(newsockfd,buffer,strlen(buffer),0);
				}  
				else if  (strcmp(cmd,"CMD_WRITEEMAIL") == 0) 
				{
					memset(&buffer[0],0,sizeof(buffer));
					semop(semid_lock, &wait, 1);
					
					bzero((char *)&users, sizeof(users));
					users = (struct User*) shmat(shm_id, NULL, 0);			
					
					result = writeEmail(data);
					if(DEBUG > 0)
					{
						//printUserDetails();
					}
					shmdt((void *) users);
								
					semop(semid_lock, &post, 1);
					sprintf(buffer,"%d",result);
					send(newsockfd,buffer,strlen(buffer),0);
				}
				else if  (strcmp(cmd,"CMD_FORWARDEMAIL") == 0) 
				{
					memset(&buffer[0],0,sizeof(buffer));
					semop(semid_lock, &wait, 1);
					
					bzero((char *)&users, sizeof(users));
					users = (struct User*) shmat(shm_id, NULL, 0);			
					
					result = forwardEmail(data);
					if(DEBUG > 0)
					{
						printUserDetails();
					}
					
					shmdt((void *) users);
								
					semop(semid_lock, &post, 1);
					sprintf(buffer,"%d",result);
					send(newsockfd,buffer,strlen(buffer),0);
				}
				else if  (strcmp(cmd,"CMD_READALLEMAIL") == 0) 
				{
					if(DEBUG > 0)
					{
						printf("REACHED READALLEMAIL\n");
					}
						
					memset(&buffer[0],0,sizeof(buffer));
					memset(&reply[0],0,sizeof(reply));
					semop(semid_lock, &wait, 1);
							
					bzero((char *)&users, sizeof(users));
					users = (struct User*) shmat(shm_id, NULL, 0);			
					if(DEBUG > 0)
					{
						printf("Data %s\n", data);
					}
					result = readAllEmails(atol(data), reply);
					shmdt((void *) users);
								
					semop(semid_lock, &post, 1);
					sprintf(buffer,"%d~%s",result,reply);
					send(newsockfd,buffer,strlen(buffer),0);
				}
				else if  (strcmp(cmd,"CMD_REPLYEMAIL") == 0) 
				{
					if(DEBUG > 0)
					{
						printf("REACHED CMD_REPLYEMAIL\n");
					}
						
					memset(&buffer[0],0,sizeof(buffer));
					memset(&reply[0],0,sizeof(reply));
					semop(semid_lock, &wait, 1);
							
					bzero((char *)&users, sizeof(users));
					users = (struct User*) shmat(shm_id, NULL, 0);			
					if(DEBUG > 0)
					{
						printf("Data %s\n", data);
					}
					result = replyEmail(data);
					shmdt((void *) users);
								
					semop(semid_lock, &post, 1);
					sprintf(buffer,"%d~%s",result,reply);
		
					send(newsockfd,buffer,strlen(buffer),0);
				}
				else if  (strcmp(cmd,"CMD_OPENEMAIL") == 0) 
				{
					if(DEBUG > 0)
					{
						printf("REACHED CMD_OPENEMAIL\n");
					}
						
					memset(&buffer[0],0,sizeof(buffer));
					memset(&reply[0],0,sizeof(reply));
					semop(semid_lock, &wait, 1);
							
					bzero((char *)&users, sizeof(users));
					users = (struct User*) shmat(shm_id, NULL, 0);			
					if(DEBUG > 0)
					{
						printf("Data %s\n", data);
					}
					int uid, emailNo;
					char *dataPart;
					
					dataPart = strtok(data, "~");
					uid = atol(dataPart);
					
					dataPart = strtok(NULL , "~");
					emailNo = atol(dataPart);
					
					result = openEmail(uid,emailNo,reply);
					shmdt((void *) users);
								
					semop(semid_lock, &post, 1);
					sprintf(buffer,"%d~%s",result,reply);
					send(newsockfd,buffer,strlen(buffer),0);
				}
				else if  (strcmp(cmd,"CMD_FILTEREMAIL") == 0) 
				{
					if(DEBUG > 0)
					{
						printf("REACHED CMD_FILTEREMAIL\n");
					}
						
					memset(&buffer[0],0,sizeof(buffer));
					memset(&reply[0],0,sizeof(reply));
					semop(semid_lock, &wait, 1);
							
					bzero((char *)&users, sizeof(users));
					users = (struct User*) shmat(shm_id, NULL, 0);			
					
					int uid1 = -1;
					char *dataPart, filter[100];
						
					if(DEBUG > 0)
					{
						printf("Data %s\n", data);
					
						printf("uid : %d\n", uid1);

						printf("filter criteria : %s\n", filter);	
					}
					
					dataPart = strtok(data, "~");
					uid1 = atol(dataPart);
					
					dataPart = strtok(NULL, "^");
					strcpy(filter, dataPart);
					
					result = filterEmails(uid1, filter, reply);
					
					shmdt((void *) users);			
					semop(semid_lock, &post, 1);
					
					sprintf(buffer,"%d~%s",result,reply);
					send(newsockfd,buffer,strlen(buffer),0);
				}
				else if  (strcmp(cmd,"CMD_READALLCALENDAR") == 0) 
				{
					if(DEBUG > 0)
					{
						printf("REACHED CMD_READALLCALENDAR\n");
					}
						
					memset(&buffer[0],0,sizeof(buffer));
					memset(&reply[0],0,sizeof(reply));
					semop(semid_lock, &wait, 1);
							
					bzero((char *)&users, sizeof(users));
					users = (struct User*) shmat(shm_id, NULL, 0);			
					if(DEBUG > 0)
					{
						printf("Data: %s\n", data);
					}
					result = readAllCalendars(atol(data), reply);
					shmdt((void *) users);
								
					semop(semid_lock, &post, 1);
					sprintf(buffer,"%d~%s",result,reply);
					send(newsockfd,buffer,strlen(buffer),0);
				}
				else if (strcmp(cmd,"CMD_READNEWEMAIL") == 0) 
				{
					if(DEBUG > 0)
					{
						printf("REACHED READNEWEMAIL\n");
					}
					memset(&buffer[0],0,sizeof(buffer));
					memset(&reply[0],0,sizeof(reply));
					semop(semid_lock, &wait, 1);
						
					bzero((char *)&users, sizeof(users));
					users = (struct User*) shmat(shm_id, NULL, 0);			
					if(DEBUG > 0)
					{
						printf("Data %s\n", data);
					}
					result = readNewEmails(atol(data), reply);
					shmdt((void *) users);
							
					semop(semid_lock, &post, 1);
					trimwhitespace(reply);
					sprintf(buffer,"%d~%s",result,reply);
					
					
					send(newsockfd,buffer,strlen(buffer),0);
				}
				else if  (strcmp(cmd,"CMD_READNEWCALENDAR") == 0) 
				{
					if(DEBUG > 0)
					{
						printf("REACHED CMD_READNEWCALENDAR\n");
					}
						
					memset(&buffer[0],0,sizeof(buffer));
					memset(&reply[0],0,sizeof(reply));
					semop(semid_lock, &wait, 1);
							
					bzero((char *)&users, sizeof(users));
					users = (struct User*) shmat(shm_id, NULL, 0);			
					if(DEBUG > 0)
					{
						printf("Data: %s\n", data);
					}
					result = readNewCalendars(atol(data), reply);
					shmdt((void *) users);
								
					semop(semid_lock, &post, 1);
					sprintf(buffer,"%d~%s",result,reply);
					send(newsockfd,buffer,strlen(buffer),0);
				}
				else if (strcmp(cmd,"CMD_CHECKNEWEMAIL") == 0) 
				{
					if(DEBUG > 0)
					{
						printf("REACHED CMD_CHECKNEWEMAIL\n");
					}
					memset(&buffer[0],0,sizeof(buffer));
					memset(&reply[0],0,sizeof(reply));
					semop(semid_lock, &wait, 1);
						
					bzero((char *)&users, sizeof(users));
					users = (struct User*) shmat(shm_id, NULL, 0);			
					if(DEBUG > 0)
					{
						printf("Data %s\n", data);
					}
					int ret1 = 0;
					result = checkNewEmails(atol(data), reply);
					
					ret1 = checkNewCalendars(atol(data), reply);

					shmdt((void *) users);
							
					semop(semid_lock, &post, 1);
					sprintf(buffer,"%d~%d~%s", result, ret1, reply);
					send(newsockfd,buffer,strlen(buffer),0);
				}
				else if (strcmp(cmd,"CMD_DELETEEMAIL") == 0) 
				{
					if(DEBUG > 0)
					{
						printf("REACHED CMD_DELETEEMAIL\n");
					}
					memset(&buffer[0],0,sizeof(buffer));
					memset(&reply[0],0,sizeof(reply));
					semop(semid_lock, &wait, 1);
						
					bzero((char *)&users, sizeof(users));
					users = (struct User*) shmat(shm_id, NULL, 0);			
					if(DEBUG > 0)
					{
						printf("Data %s\n", data);
					}
					int uid, emailNo;
					char *dataPart;
					
					dataPart = strtok(data, "~");
					uid = atol(dataPart);
					dataPart = strtok(NULL , "~");
					emailNo = atol(dataPart);
										
					result = deleteEmail(uid, emailNo);
					shmdt((void *) users);
							
					semop(semid_lock, &post, 1);
					sprintf(buffer,"%d~",result);
					send(newsockfd,buffer,strlen(buffer),0);
				}
				else if (strcmp(cmd,"CMD_CHECKNEWCALENDAR") == 0) 
				{
					if(DEBUG > 0)
					{
						printf("REACHED CMD_CHECKNEWCALENDAR\n");
					}
					memset(&buffer[0],0,sizeof(buffer));
					memset(&reply[0],0,sizeof(reply));
					semop(semid_lock, &wait, 1);
						
					bzero((char *)&users, sizeof(users));
					users = (struct User*) shmat(shm_id, NULL, 0);			
					if(DEBUG > 0)
					{
						printf("Data %s\n", data);
					}
					result = checkNewCalendars(atol(data), reply);
					shmdt((void *) users);
							
					semop(semid_lock, &post, 1);
					sprintf(buffer,"%d~%s",result,reply);
					send(newsockfd,buffer,strlen(buffer),0);
				}
				else if (strcmp(cmd,"CMD_WRITECALENDAR") == 0) 
				{
					if(DEBUG > 0)
					{
						printf("REACHED CMD_WRITECALENDAR\n");
					}
					memset(&buffer[0],0,sizeof(buffer));
					memset(&reply[0],0,sizeof(reply));
					semop(semid_lock, &wait, 1);
						
					bzero((char *)&users, sizeof(users));
					users = (struct User*) shmat(shm_id, NULL, 0);			
					if(DEBUG > 0)
					{
						printf("Data: %s\n", data);
					}
					
					result = writeCalendarEvent(data, reply);
	
					shmdt((void *) users);
							
					semop(semid_lock, &post, 1);
					sprintf(buffer,"%d~%s",result,reply);
					send(newsockfd,buffer,strlen(buffer),0);
				}
				else if (strcmp(cmd,"CMD_LOGOFF") == 0) 
				{
					if(DEBUG > 0)
					{
						printf("REACHED CMD_LOGOFF\n");
					}
					
					memset(&buffer[0],0,sizeof(buffer));
					memset(&reply[0],0,sizeof(reply));

					semop(semid_lock, &wait, 1);
						
					bzero((char *)&users, sizeof(users));
					users = (struct User*) shmat(shm_id, NULL, 0);	
				
					if(DEBUG > 0)
					{
						printf("User: %s\n", data);
					}

					result = logoffUser(atol(data), reply);
					shmdt((void *) users);
							
					semop(semid_lock, &post, 1);
					sprintf(buffer,"%d~%s",result,reply);
					if(DEBUG > 0)
						printf("Reached logoff reply: %s", buffer);
					
					send(newsockfd,buffer,strlen(buffer),0);
					if (result == 1) 
					{
						close(newsockfd);
						exit(0);
					}
				}
				else if (strcmp(cmd,"CMD_SHUTDOWN") == 0) 
				{
					if(DEBUG > 0)
					{
						printf("REACHED CMD_Shutdown\n");
					}
					
					memset(&buffer[0],0,sizeof(buffer));
					memset(&reply[0],0,sizeof(reply));

					semop(semid_lock, &wait, 1);
					
					bzero((char *)&Shutdown, sizeof(Shutdown));

					Shutdown = (char *) shmat(shm_id2, NULL, 0);
					strcpy(Shutdown,"Yes");	
				
					shmdt((void *) Shutdown);
					
					bzero((char *)&users, sizeof(users));
					users = (struct User*) shmat(shm_id, NULL, 0);	
					
					result = shutdownServer(reply);
					
					shmdt((void *) users);							
					semop(semid_lock, &post, 1);
					
					sprintf(buffer,"%d~%s",result,reply);
					
					if(DEBUG > 0)
						printf("Reached Shutdown reply: %s\n", buffer);
					
					send(newsockfd,buffer,strlen(buffer),0);
					
					if (result == 999) 
					{
						close(newsockfd);
						exit(0);
					}
				}
				else if  (strcmp(cmd,"CMD_DOWNLOADATT") == 0) 
				{
					if(DEBUG > 0)
						printf("reached DOWNLOADATT\n");

					memset(&buffer[0],0,sizeof(buffer));
					memset(&reply[0],0,sizeof(reply));
					semop(semid_lock, &wait, 1);

					bzero((char *)&users, sizeof(users));
					users = (struct User*) shmat(shm_id, NULL, 0);   

					result = downloadAttachment(data,reply);
					if(DEBUG > 0)
						printf("reacheds after downloadAttachment\n");
					shmdt((void *) users);

					semop(semid_lock, &post, 1);
					sprintf(buffer,"%d~%s",result,reply);
					send(newsockfd,buffer,strlen(buffer),0);
				}
				else if  (strcmp(cmd,"CMD_LISTUSERS") == 0) 
				{
					if(DEBUG > 0)
						printf("reached CMD_LISTUSERS\n");

					memset(&buffer[0],0,sizeof(buffer));
					memset(&reply[0],0,sizeof(reply));
					semop(semid_lock, &wait, 1);

					bzero((char *)&users, sizeof(users));
					users = (struct User*) shmat(shm_id, NULL, 0);   

					UserList(reply);
					if(DEBUG > 0)
						printf("reacheds after list user\n");
					shmdt((void *) users);

					semop(semid_lock, &post, 1);
					sprintf(buffer,"%d~%s",result,reply);
					send(newsockfd,buffer,strlen(buffer),0);
				}
				else if  (strcmp(cmd,"CMD_DELETECALENDAR") == 0) 
				{
					if(DEBUG > 0)
						printf("reached CMD_DELETECALENDAR\n");

					memset(&buffer[0],0,sizeof(buffer));
					memset(&reply[0],0,sizeof(reply));
					semop(semid_lock, &wait, 1);

					bzero((char *)&users, sizeof(users));
					users = (struct User*) shmat(shm_id, NULL, 0);   
			
					int calNo;
					int uid;
					char *dataPart;
					
					dataPart = strtok(data, "~");
					uid = atol(dataPart);
					
					dataPart = strtok(NULL, "~");
					calNo = atol(dataPart);
					
					printf("uid no : %d\n",uid );
					printf("cal no : %d\n",calNo );
					
					result = deleteCalender(uid, calNo);
					if(DEBUG > 0)
						printf("reacheds after CMD_DELETECALENDAR\n");
					
					shmdt((void *) users);

					semop(semid_lock, &post, 1);
					sprintf(buffer,"%d~",result);
					send(newsockfd,buffer,strlen(buffer),0);
				}			
				else 
				{
					if(DEBUG > 0)
					{
						printf("REACHED Invalid Command\n");
					}

					memset(&buffer[0],0,sizeof(buffer));
					sprintf(buffer,"Invalid Command!");
					send(newsockfd,buffer,strlen(buffer),0);
				}
			}
		}
		else
		{
			
			sleep(1);
			close(newsockfd);
			bzero((char *)&Shutdown, sizeof(Shutdown));

			Shutdown = (char *) shmat(shm_id2, NULL, 0);
			
			if (DEBUG > 0)
				printf("check shutdown in main process %s \n", Shutdown);
			
			if (strcmp(Shutdown,"Yes") == 0) 
				{
					printf("\n*******      Shutting Down Mail/Calendar Server!     ********\n");
					
					exit(0);
				}
			shmdt((void *) Shutdown);
	
		}
	}
}
