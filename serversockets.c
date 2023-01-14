// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include<arpa/inet.h>

int main(int argc, char *argv[]){ 

int socket_desc, c,read_size;
long unsigned int client_socket ;
struct sockaddr_in server, client;
//char client_message[1000];




// get a socket
socket_desc = socket(AF_INET, SOCK_STREAM,0); 
if (socket_desc==-1){ 
	 printf("Could not create socket.");
}
puts("Socket created");

//fill the fields 
server.sin_addr.s_addr = inet_addr("127.0.0.1");
server.sin_family =AF_INET; 
server.sin_port = htons( 8888 ); 


//bind the socket to the port
if(bind(socket_desc,(struct sockaddr *)&server, sizeof(server))<0){ 
	perror("bind faild. error");
	return 1;
}

//start listening for incoming connections
puts("bind done");
listen(socket_desc,3);

puts("waiting for incomming connections...");
c = sizeof(struct sockaddr_in);
client_socket= accept(socket_desc,(struct sockaddr *)&client, (socklen_t*)&c);

if (client_socket == -1) {
      perror("accept falid");
      return 1;
    }
puts("Connection accepted");





//int bufferlenght=5000; 
char line[5000];// character array to store the lines of the file 



//while(read_size=recv(client_socket, client_message, 2000,0)>0) { 
while(1){
	char client_message[1000]="";
	recv(client_socket, client_message, 2000,0);
	puts(client_message);
	//write(client_socket,client_message, strlen(client_message));
	
	
	//opens the file using pointer that points to the file 
	FILE* inputF=fopen("english3.txt","r");
	
	
	int x=0; //Counter to keep the track of occurances 
	
	int c=0;  // varribale to check if word is found or not in the file
	
	char result[1000]; // a character array to store the result 
	
	
	
	  
	
	
	while (fscanf(inputF,"%s",line) == 1  ){  // while loop to go through or scan each line in the file and and store that line into the varriable "line" and it it retuns 1, if there is string or line in the file and loops break when there is no next line  in the file.
	
	    
	
	  
	           if (strstr(line, client_message)!=0){ // use of strstr function to look for the occurance of the client input/word in the line 
	           
	           
	                      x++; // increments the counter, if the occurance of the word is found in the line 
	             
	             if(strcmp(line,client_message) == 0){ // use strcmp function to compare the line with the  word send by the client and gives 0, if both words are same 
	             
	                                c=1;   // if both words are same then c gets equal to 1, whihc is is used to know if the word is found or no
	                        
	             
	             
	             }
	             
	             
	         }
	     
	
	             
	             
	  
	}  if(c==1){ // to checkif the word is found 
	                          
	             // if the word is found it prints word found and number of occurances 
	                      sprintf(result,"Word was found in the dictionary and number of occurances is:  %d ",x);
	                      
	             
	             }    
	             
	             
	             
	             else {
	             // if the word is not found it prints word not found and number of occurances of the word in the file because there would not be the exact word, but it still occurs in lines 
	             
	                     
	                       sprintf(result,"Word was not found in the dictionary and but number of occurances is: %d ",x);
	                   
	             
	             } 
	
	   
	
	 
	
	     
   write(client_socket,result,strlen(result)); // prints the result to the client 
     
     
     
}	



 
  if(read_size==0){ 
  puts("client disconnected");
  fflush(stdout);
}
else if(read_size==-1){
 perror("recv failed");
}
 

return 0;
}
