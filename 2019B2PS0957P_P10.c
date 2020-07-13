#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<time.h>


#define SIZE 50

//linked list to store the books.
struct book{
		int id;
		int dd;
		int mm;
		int yyyy;
		int quantity;
		char title[SIZE];
		char author[SIZE];
		char genre[SIZE];
		struct book* next;
};
typedef struct book book_t;

//structure to store the user details.
struct User{
		char name[SIZE];
		char email[SIZE];
		char uname[SIZE];
		char pwd[SIZE];
		char phno[SIZE];
};

//structure variable that stores details of currently loggedin user.
struct User cur;

//function prototypes.
void main_page();
int input();
void user_login();
void user_page();
void staff_login();
void staff_page();
void user_mgmt();


//fucntion that creates a new node in the book linked list given the appropriate parameters.
book_t* create_new_node(int d, int m , int y, int i, int q, char* a, char* g, char* t){
		book_t* result = malloc(sizeof(book_t));
		if(result == NULL)
				printf("Overflow Error!\n");
		result->id = i;
		result->dd = d;
		result->mm = m;
		result->yyyy = y;
		result->quantity = q;
		strcpy(result->title, t);
		strcpy(result->author, a);
		strcpy(result->genre, g);
		result->next = NULL;
		return result;
}

//fucntion that inserts a node at the head of the linkedlist.
book_t* insert_at_head(book_t** head, book_t* book_to_insert){
		book_to_insert->next = *head;
		*head = book_to_insert;
		return book_to_insert;
}
						
//function that prints the linked list given the pointer to its head.
void printlist(book_t* head){
		book_t* tmp = head;
		while(tmp != NULL){
				printf("*****************************\n");
				printf("Book id: %d\n", tmp->id);
				printf("Title : %s", tmp->title);// \n is not needed as it wasnt trimmed while getting input.
				printf("Author : %s\n", tmp->author);
				printf("Genre : %s\n", tmp->genre);
				printf("Date added to library : %d-%d-%d\n", tmp->dd, tmp->mm, tmp->yyyy);
				printf("No.of books in library : %d\n", tmp->quantity);
				printf("*****************************\n");
				tmp = tmp->next;
		}
		printf("\n");
}

//fucntion to see new arrivals in the library(same month).
void seenew(book_t* head) {
		book_t* tmp = head;
		time_t now;
		time(&now);
		struct tm* local = localtime(&now);
		while(tmp != NULL) {
				if(tmp->mm == (local->tm_mon + 1)&&(tmp->yyyy == (local->tm_year + 1900))) {
				printf("*****************************\n");
				printf("Book id: %d\n", tmp->id);
				printf("Title : %s", tmp->title);
				printf("Author : %s\n", tmp->author);
				printf("Genre : %s\n", tmp->genre);
				printf("Date added to library : %d-%d-%d\n", tmp->dd, tmp->mm, tmp->yyyy);
				printf("No.of books in library : %d\n", tmp->quantity);
				printf("*****************************\n");
				}
				tmp = tmp->next;
		}
}


//function used to destroy the linked list and free all the mallocd nodes.
void destroy(book_t* head){
		if(head == NULL)
				return;
		destroy(head->next);
		free(head);		
}

//function used to append a node to the linkedlist.
void insert_at_tail(book_t** head, book_t* book_to_insert){
		book_t* tail = *head;
		if(*head == NULL){
				*head = book_to_insert;
				return;
		}
		while(tail->next != NULL)
				tail = tail->next;
		tail->next = book_to_insert;
		return;
}

//function used to return the book details of all nodes having same author.
void findnode_a(book_t* head, char* author){
		book_t* tmp = head;
		int count = 0;
		while(tmp != NULL){
				if(strcmp(tmp->author, author) == 0){
						count++;						
						printf("**********************************\n");
						printf("Book id: %d\n", tmp->id);
						printf("Title : %s", tmp->title);
						printf("Genre : %s\n", tmp->genre);
						printf("No.of books in library : %d\n", tmp->quantity);
				
				}					
				tmp = tmp->next;
		}
		if(count == 0){
				printf("No books written by this author are there in the library\n");
				return;
		}

		
}


//function used to return the book details of all nodes having same genre.
void findnode_g(book_t* head, char* genre){
		book_t* tmp = head;
		int count = 0;
		while(tmp != NULL){
				if(strcmp(tmp->genre, genre) == 0){
						count++;
						printf("Book id: %d\n", tmp->id);
						printf("Title : %s", tmp->title);
						printf("Author : %s\n", tmp->author);
						printf("No.of books in library : %d\n", tmp->quantity);
						printf("**********************************\n");
				}
				tmp = tmp->next;
		}
		if(count == 0){
				printf("No books of this genre are there in the library\n");
				return;
		}
}


//function used to return the book details of all nodes having same title.
void findnode_t(book_t* head, char* title){
		book_t* tmp = head;
		int count = 0;
		while(tmp != NULL){
				if(strcmp(tmp->title, title) == 0){
						count++;
						printf("Book id: %d\n", tmp->id);
						printf("Author : %s\n", tmp->author);
						printf("Genre : %s\n", tmp->genre);
						printf("No.of books in library : %d\n", tmp->quantity);
						printf("**********************************\n");
				}
				tmp = tmp->next;
		}
		if(count == 0){
				printf("No books having this title are there in the library\n");
				return;
		}
}


//function used to return the book details of a node given the issue/id number.
void findnode_i(book_t* head, int id) {
		book_t* tmp = head;
		int count = 0;
		while(tmp != NULL){
				if(tmp->id == id){
						count++;
						printf("Title : %s", tmp->title);
						printf("Author : %s\n", tmp->author);
						printf("Genre : %s\n", tmp->genre);
						printf("No.of books in library : %d\n", tmp->quantity);
						printf("**********************************\n");
				}
				tmp = tmp->next;
		}
		if(count == 0){
				printf("No book in this library has this id \n");
				return;
		}
}

//function used to convert the books.txt file into a linked list.						
book_t* File_to_ll(book_t* head){
		FILE* fp = fopen("books.txt", "r");
		char* line = NULL;
		size_t len = 0;
		book_t* tmp = NULL;
		char* title = NULL;
		char* author = NULL;
		char* genre = NULL;
		char* qtemp = NULL;
		char* dtemp = NULL;
		char* mtemp = NULL;
		char* ytemp = NULL;
		int dd;
		int mm;
		int yyyy;
		int quantity;
		int count = 0;
		if(fp == NULL){
				printf("Error in opening the file");
				return NULL;
		}
		else{
				while(getline(&line, &len, fp) != -1){ //getline mallocs extra 120 bytes which need to be freed!
						count++;
						char* ltmp = line;             //strsep will change the address, so need to store it in a temp variable so that mallocd line can be freed.
						dtemp = strsep(&ltmp, "|");
						mtemp = strsep(&ltmp, "|");
						ytemp = strsep(&ltmp, "|");
						qtemp = strsep(&ltmp, "|");
						author = strsep(&ltmp, "|");
						genre = strsep(&ltmp, "|");
						title = ltmp;
						sscanf(dtemp, "%d", &dd);
						sscanf(mtemp, "%d", &mm);
						sscanf(ytemp, "%d", &yyyy);
						sscanf(qtemp, "%d", &quantity); 
						tmp = create_new_node(dd, mm, yyyy, count, quantity, author, genre, title);
						insert_at_tail(&head, tmp);
				}

		}
		free(line);// to free the getline's malloc
		fclose(fp);
		return head;
}

//fucntion thats used to return the node as a string variable.
char* node_to_string(book_t* node){
		char* buf = malloc(5 * SIZE * sizeof(char));// have to free this!
		sprintf(buf, "%d|%d|%d|%d|%s|%s|%s", node->dd, node->mm, node->yyyy, node->quantity, node->author, node->genre, node->title);
		return buf;
}

//function that dumps the linked list into the books.txt file with updated information of nodes.
void LL_to_file(book_t* head){
		book_t* tmp = head;
		FILE* fp;
		fp = fopen("books.txt", "w");
		if(fp == NULL){
				printf("Could not dump the LL to the file\n");
				return;
		}
		else{
				while(tmp != NULL){
						char* line = node_to_string(tmp);
						fputs(line, fp);
						tmp = tmp->next;
						free(line);
				}
		}
		fclose(fp);
}
				
//function used to trim user inputs(removes\n) and also append "|" at end to save it in file.
char* input_trimmer(char** input){
		char buf[SIZE];
		strcpy(buf, *input);
		buf[strcspn(buf, "\n")] = 0;
		strcat(buf, "|");
		strcpy(*input, buf);
		return *input;
		
}

//function that trims the \n from the user input.
char* nl_trimmer(char** input){
		char buf[SIZE];
		strcpy(buf, *input);
		buf[strcspn(buf, "\n")] = 0;
		strcpy(*input, buf);
		return *input;
}
char* replace(char str[50]){	//Function to remove '\n' from a string to prevent dangling newline problems
	int len;
	len=strlen(str);
	if( str[len-1] == '\n' )
		str[len-1] = 0;
	return(str);
}

//function that reads the books.txt file and initialises the linkedlist.
void add_new_books(){
		FILE* fp = fopen("books.txt", "a");
		if(fp == NULL){
				printf("Error!");
		}
		else{
				printf("Enter the number of books to be added : \n");
				int n;
				n = input();
						char* name = malloc(SIZE * sizeof(char));
						char* genre = malloc(SIZE * sizeof(char));
						char* title = malloc(SIZE * sizeof(char));
						char* quantity = malloc(SIZE * sizeof(char));

				for(int i =0; i < n; i++){						
						printf("Enter the name\n");
						fgets(name, SIZE, stdin);
						printf("Enter the genre\n");
						fgets(genre, SIZE, stdin);
						printf("Enter the title\n");
						fgets(title, SIZE, stdin);
						printf("Enter the quantity\n");
						fgets(quantity, SIZE, stdin);
						fputs(input_trimmer(&quantity), fp);
						fputs(input_trimmer(&name), fp);
						fputs(input_trimmer(&genre), fp);
						fputs(title, fp);
				}
						free(name);
						free(genre);
						free(title);
						free(quantity);
	
		}
		fclose(fp);
}
						
//function that takes in a string and converts to int, for ease of processing data
int input(){
		char input[20];
		int ret;
		fgets(input, 20, stdin);
		sscanf(input, "%d", &ret);
		return ret;
}

//interface for the search functions
void book_search(book_t* head){
		system("clear");
		printf("************************************************************\n");
		printf("*                  Search  Page                            *\n");
		printf("*                                                          *\n");
		printf("*                  1) Search by Title                      *\n");
		printf("*                  2) Search by Author                     *\n");
		printf("*                  3) Search by Genre                      *\n");
		printf("*                  4) Search by Issue number               *\n");
		printf("*                  5) Exit to Main page                    *\n");
		printf("*                                                          *\n");
		printf("************************************************************\n");
		int ch;	
		printf("Enter your choice (1/2/3/4/5) : \n");		
		do{
				ch = input();
				if(ch == 1){
						printf("Enter the Title : \n");
						char t[SIZE];
						fgets(t, SIZE, stdin);
						findnode_t(head, t);
				}
				else if(ch == 2){
						printf("Enter the name of the author :\n");
						char* a = malloc(SIZE * sizeof(char));
						fgets(a, SIZE, stdin);
						char* aut = nl_trimmer(&a);
						findnode_a(head, aut);
						free(a);
						
				}
				else if(ch == 3){
						printf("Enter the Genre :\n");
						char* g = malloc(SIZE * sizeof(char));
						fgets(g, SIZE, stdin);
						char* gen = nl_trimmer(&g);
						findnode_g(head, gen);
						free(g);
				}
				else if(ch == 4){
						printf("Enter the book id : \n");
						char i[SIZE];
						fgets(i, SIZE, stdin);
						int id;
						sscanf(i, "%d", &id);
						findnode_i(head, id);
				}
				else if(ch == 5){
						main_page(head);
						return;						
				}
				else{
					printf("Invalid choice\n");
					printf("Please enter a valid choice\n");
					ch=0;
			}
		}		
	while(ch == 0);
		printf("Do you want to search again(1) or exit to main page(2) ? \n");
		int cho;
		do{
				cho = input();
				if(cho == 1){
						book_search(head);
				}
				else if(cho == 2){
						main_page(head);
				}
				else{
						printf("Invalid choice\n");
						printf("Please enter a valid choice\n");
						cho = 0;
				}
		}
		while(cho == 0);

}

//interface for the user login portal with password
void user_login(book_t* head) {
		FILE* f1 = fopen("userdet2.txt", "r");
		if(f1 == NULL) {
				printf("Error in opening the file\n");
		}
		else {
				char* line = NULL;
				size_t len = 0;
				char* n = NULL;
				char* e = NULL;
				char* u = NULL;
				char* p = NULL;
				int choice = 0;
				int flag = 0;
				int cho = 0;
				int flag2 = 0;
				int cho2 = 0;
				do {	
						char* uin = malloc(SIZE * sizeof(char));
						char* pin = malloc(SIZE * sizeof(char));
						printf("Enter the username :\n");
						fgets(uin, SIZE, stdin);
						char* utemp = nl_trimmer(&uin);
						strcpy(cur.uname, utemp);
						while(getline(&line, &len, f1) != -1) {
								char* tmp = line;
								n = strsep(&tmp, "|");
								e = strsep(&tmp, "|");
								u = strsep(&tmp, "|");
								p = strsep(&tmp, "|");
								if(strcmp(cur.uname, u) == 0) {
										do { 	
												flag = 1;
												printf("Enter the password :\n");
												fgets(pin, SIZE, stdin);
												char* ptemp = nl_trimmer(&pin);
												strcpy(cur.pwd, ptemp);
												if(strcmp(cur.pwd, p) == 0) {
														flag2 = 1;
														printf("Login successful!\n");
														user_page(head);
														return;
												}
												printf("Invalid password\n");
												printf("Press 1 to retry any other key to return to the main page\n");
												cho2 = input();
												if(cho2 != 1) {
														main_page(head);
														return;
												}
										}
										while(flag2 != 1);
								}
						}
						free(line);
						if(flag == 0) {
								printf("Wrong user name \n");
								printf("Press 1 to retry or any other key to return to main page\n");
								cho = input();
								if(cho != 1) {
										main_page(head);
										return;
								}
						}
						free(uin);
						free(pin);
						fseek(f1, 0, SEEK_SET); 
				}
				while(flag != 1);				
		}
		fclose(f1);
}

//gets the book id to be used for the borrow function
int bid_getter_b(book_t* head) {
		book_t* tmp = head;
		printf("Enter the book id :\n");
		int bid;
		bid = input();
		while(tmp != NULL) {
				if(tmp->id == bid) {
						tmp->quantity--;
						return bid;
				}
				tmp = tmp->next;
		}	
}

//borrow boooks function.Updates the Linked list and the userdet2.txt file
void borrow(book_t* head, int bid) {
		char* n = NULL;
		char* e = NULL;
		char* u = NULL;
		char* pw = NULL;
		char* ph = NULL;
		char* bo = NULL;
		char* utemp = malloc(SIZE * sizeof(char));
		char* botmp = malloc(3 * SIZE * sizeof(char));
		char* s1 = malloc(SIZE* sizeof(char));
		char* newl = malloc(8 * SIZE * sizeof(char));
		int tem;
		int dd, mm , yyyy;
		time_t now;
		time(&now);
		struct tm* local = localtime(&now);
		dd = local->tm_mday;
		mm = local->tm_mon + 1;
		yyyy = local->tm_year + 1900;
		FILE* fr, *fw;
		fr = fopen("userdet2.txt", "r");
		fw = fopen("tempuser.txt", "w");
		if(fr == NULL || fw == NULL) {
				printf("Error in opening the file\n");
		}
		else {
				char* line = NULL;
				size_t len = 0;
				while(getline(&line, &len, fr) != -1) {
						char* tmp = line;
						n = strsep(&tmp, "|");
						e = strsep(&tmp, "|");
						u = strsep(&tmp, "|");
						pw = strsep(&tmp, "|");
						ph = strsep(&tmp, "|");
						bo = strsep(&tmp, "\n");
						strcpy(utemp, u);
						strcpy(botmp, bo);
						if(strcmp(utemp, cur.uname) == 0) {
								sprintf(s1, "%d.%d/%d/%d,", bid, dd, mm, yyyy);
								strcat(botmp, s1);
								sprintf(newl, "%s|%s|%s|%s|%s|%s\n", n, e, utemp, pw, ph, botmp);
								fprintf(fw, "%s", newl);
								printf("Book was borrowed successfuly!\n");
								printf("Enter any key to return to the userpage\n");
								tem = input();
						}
						else {
								sprintf(newl, "%s|%s|%s|%s|%s|%s\n", n, e, utemp, pw, ph, bo);
								fprintf(fw, "%s", newl);
						}
				}
				free(line);
		}
		free(s1);
		free(utemp);
		free(newl);
		free(botmp);
		fclose(fr);
		fclose(fw);
		remove("userdet2.txt");
		rename("tempuser.txt", "userdet2.txt");
		LL_to_file(head);
		user_page(head);
}

//function that deletes the given book id from the userdet2.txt file and updates the LL.
void return_books(book_t* head) {
		FILE* fa = fopen("userdet2.txt", "r");
		FILE* fb = fopen("tmp.txt", "w");
		if(fa == NULL||fb == NULL) {
				printf("Error in opening the file\n");
		}
		else {	
				char* line = NULL;
				char* n = NULL;
				char* e = NULL;
				char* u = NULL;
				char* pw = NULL;
				char* ph = NULL;
				char* bo = NULL;
				char* botmp = NULL;
				char s1[2*SIZE];
				size_t len = 0;
				int flag = 0;
				int cho = 0;
				int res;
				do{
						printf("Enter the bookid to be returned :\n");
						int id;
						id = input();
						char si[SIZE];
						sprintf(si, "%d", id); 
						while(getline(&line, &len, fa) != -1) {
								char* tmp = line;
								n = strsep(&tmp, "|");
								e = strsep(&tmp, "|");
								u = strsep(&tmp, "|");
								pw = strsep(&tmp, "|");
								ph = strsep(&tmp, "|");
								bo = strsep(&tmp, "\n");
								if(strcmp(u, cur.uname) == 0) {
										int i;
										botmp = bo;
										for(i = 0; botmp[i]; botmp[i] == '.' ? i++ : *botmp++);//credit stackoverflow answer for the oneliner
										char s2[i*2*SIZE];
										strcpy(s2,"");
										char* bid[i];
										char* bdate[i];
										for(int j = 0; j < i; ++j) {
												bid[j] = strsep(&bo, ".");
												bdate[j] = strsep(&bo, ",");

												if(strcmp(si, bid[j]) != 0) {
														sprintf(s1, "%s.%s,", bid[j], bdate[j]);
														strcat(s2,s1);
												}
												else {
														if(flag != 1) {
																flag = 1;
																book_t* tmp = head;
																while(tmp != NULL) {
																		if(tmp->id == id) {
																				cho = 0;
																				tmp->quantity++;
																				printf("Book Returned successfuly\n");
																		}
																		tmp = tmp->next;
																}
														}
						
												}
										}
										fprintf(fb, "%s|%s|%s|%s|%s|%s\n", n,e,u,pw,ph,s2);
								}
								else {
										fprintf(fb, "%s|%s|%s|%s|%s|%s\n", n, e, u, pw, ph, bo);
								}
						}
						fseek(fa, 0 , SEEK_SET);
						free(line);
						if( flag != 1) {
								printf("This book id was not borrowed\n");
								printf("Press 1 to retry, any other key to return to the user page\n");
								cho = input();
						}
				}
				while(cho == 1);
				fclose(fa);
				fclose(fb);
				remove("userdet2.txt");
				rename("tmp.txt", "userdet2.txt");
				LL_to_file(head);
				user_page(head);
		}
}

//notifies the user if books are due and also says how much time left before return.
void notify_due() { 
		FILE* f1 = fopen("userdet2.txt","r");
		if(f1 == NULL) {
				printf("Error in opening the file\n");
		}
		else {	
				char* n = NULL;
				char* e = NULL;
				char* u = NULL;
				char* pw = NULL;
				char* ph = NULL;
				char* bo = NULL;
				char* botmp = NULL;
				char* utemp = malloc(SIZE * sizeof(char));
				int dd, mm, yyyy;
				int day, month, year;
				time_t now;
				struct tm* local = localtime(&now);
				day = local->tm_mday;
				month = local->tm_mon + 1;
				year = local->tm_year + 1900;
				char* line = NULL;
				size_t len = 0;
				while(getline(&line,&len,f1) != -1) {
						char* tmp = line;
						n = strsep(&tmp, "|");
						e = strsep(&tmp, "|");
						u = strsep(&tmp, "|");
						pw = strsep(&tmp, "|");
						ph = strsep(&tmp, "|");
						bo = strsep(&tmp, "\n");
						strcpy(utemp,u);
						if(strcmp(utemp, cur.uname) == 0) {
										int i;
										botmp = bo;
										for(i = 0; botmp[i]; botmp[i] == '.' ? i++ : *botmp++);//credit stackoverflow answer for the oneliner
										char* bid[i];
										char* bdate[i];
										for(int j = 0; j < i; ++j) {
												bid[j] = strsep(&bo, ".");
												bdate[j] = strsep(&bo, ",");
												sscanf(bdate[j], "%d/%d/%d", &dd, &mm, &yyyy);
												printf("%s.%d/%d/%d",bid[j], dd, mm, yyyy);
												if(mm == month && (day >= dd + 15)) {
														printf("book %s is due!\n", bid[j]);
												}
												else {
														printf("book %s is due in %d days\n", bid[j],(15 - (day - dd)));
												}
										}
						}
				}
				free(line);
				free(utemp);
		}
		fclose(f1);
}

//the interface for the userpage, options to borrow, return etc are present here.
void user_page(book_t* head){
		system("clear");
		printf("************************************************************\n");
		printf("*                         Welcome!                         *\n");
		printf("*                                                          *\n");
		printf("*                  1) Borrow New Books                     *\n");
		printf("*                  2) Return Pending Books                 *\n");
		printf("*                  3) Notifications centre                 *\n");
		printf("*                  4) Return To Main Page                  *\n");
		printf("*                                                          *\n");
		printf("************************************************************\n");
		int ch;
		printf("Enter your choice (1/2/3/4) : \n");
		do{
			ch = input();
			if(ch == 1){
				int bid = bid_getter_b(head);
				borrow(head,bid);
			}
			else if(ch == 2){
				return_books(head);
			}
			else if(ch == 3) {
				    printf("************************************************************\n");
					printf("*                  Notificiations page                     *\n");
					notify_due();
					int temp;
					printf("Press any key to return to user page\n");
					temp = input();
					user_page(head);
			}
			else if(ch == 4){
				main_page(head);
			}
			else{
				printf("Invalid Choice!\n");
				printf("Please enter a Valid Choice!\n");
				ch=0;
			}
		}
		while (ch == 0);
}

//interface for staff login with staff id and password.
void staff_login(book_t* head){
		char ch;
		do{
			system("clear");
			char un[50], pd[50], read[50];
			FILE *fp;
			fp=fopen("staffdet.txt","r");
			if(fp != NULL){
				printf("************************************************************\n");
				printf("*                        Staff Login                       *\n");
				printf("-->Enter Username: ");
				fgets(un,sizeof(un),stdin);
				if(strcmp(un,"\n")==0){
					ch=1;
					continue;
				}
				
				while(fgets(read,sizeof(read),fp)){
					if(strcmp(read,un)==0){
						fgets(read,sizeof(read),fp);
						printf("-->Enter Password: ");
						fgets(pd, sizeof(pd), stdin);
						if(strcmp(read,pd)==0){
							printf("Login Successfull!\n");
							staff_page(head);
						}
					}
				}
			}
			else{
				printf("Fatal Error!\n");
			}
			fclose(fp);
		
			printf("Retry?\nEnter 1 else any other character to return to Main Page: ");
			ch = input();
		}
		while(ch == 1);
		main_page(head);
}


//add users to the library system
void add_users(book_t* head){
		char ch;
		do{
			system("clear");
			struct User u;
			FILE *fp;
			fp=fopen("userdet2.txt","a");
			
			if(fp != NULL){
			printf("************************************************************\n");
			printf("*                       Add New Users                      *\n");
			printf("-->Enter New User's Details\n");
			printf("-->Enter User's name: ");
			fgets(u.name,sizeof(u.name),stdin);
			printf("-->Enter Email-ID: ");
			fgets(u.email,sizeof(u.email),stdin);
			printf("-->Enter phone number : ");
			fgets(u.phno,sizeof(u.phno),stdin);
			printf("-->Enter Username: ");
			fgets(u.uname,sizeof(u.uname),stdin);
			printf("-->Enter Password: ");
			fgets(u.pwd,sizeof(u.pwd),stdin);
			char* name = u.name;
			char* email = u.email;
			char* phn = u.phno;
			char* uname = u.uname;;
			char* pwd = u.pwd;

			fprintf(fp,"%s|%s|%s|%s|%s|\n",nl_trimmer(&name), nl_trimmer(&email), nl_trimmer(&uname), nl_trimmer(&pwd), nl_trimmer(&phn));
}

			else{
				printf("*** Error in opening the File! ***\n");
			}
			
			fclose(fp);
			printf("-->Record Successfully Added!\n");
			printf("-->Do you want to add more Records?\n");
			printf("-->Enter 1 to add or any other character to return to User Management Screen: ");
			ch = input();
		
		}
		while(ch == 1);
		user_mgmt(head);
}

//modify users that are currently there			
void mod_users(book_t* head){
		char un[SIZE];
		char s1[6*SIZE];
		char* line = NULL;
		char* n = NULL;
		char* e = NULL;
		char* uname = NULL;
		char* pw = NULL;
		char* ph = NULL;
		char* bo = NULL;

		char* nte = NULL;
		char* ete = NULL;
		char* unate = NULL;
		char* pwte = NULL;
		char* phte = NULL;


		struct User new;
		size_t size = 0;
		FILE* fr = fopen("userdet2.txt", "r");
		FILE* fw = fopen("tempusr.txt", "w");
		int flag = 0;
		int cho = 0;
		int temp;
		if(fr == NULL || fw == NULL) {
				printf("Error in opening the file \n");
		}
		else {	
				printf("************************************************************\n");
				printf("*                        Modify User                       *\n");
				do {
						printf("Enter the username of the record to be modified :\n");
						fgets(un, SIZE, stdin);
						char* utemp = un;
						while(getline(&line, &size, fr) != -1) {
								char* tmp = line;
								n = strsep(&tmp, "|");
								e = strsep(&tmp, "|");
								uname = strsep(&tmp, "|");
								pw = strsep(&tmp, "|");
								ph = strsep(&tmp, "|");
								bo = tmp;
								if(strcmp(uname, nl_trimmer(&utemp)) == 0) {
										flag = 1;
										printf("Enter the new name \n");
										fgets(new.name, SIZE, stdin);
										printf("Enter the new email \n");
										fgets(new.email, SIZE, stdin);
										printf("Enter the new phone number\n");
										fgets(new.phno , SIZE, stdin);
										printf("Enter the new username \n");
										fgets(new.uname, SIZE, stdin);
										printf("Enter the new password \n");
										fgets(new.pwd, SIZE, stdin);

										nte = new.name;
										ete = new.email;
										unate = new.uname;
										pwte = new.pwd;
										phte = new.phno;
										sprintf(s1, "%s%s%s%s%s%s", input_trimmer(&nte), input_trimmer(&ete), input_trimmer(&unate), input_trimmer(&pwte), input_trimmer(&phte), bo);
										fprintf(fw, "%s", s1);
										printf("Record successfuly modified!\n");
										printf("Press any key to return to staff page\n");
										temp = input();

								}
							else {
										fprintf(fw, "%s|%s|%s|%s|%s|%s", n, e, uname, pw, ph, bo);
							}
						}
						free(line);
						fseek(fr, 0, SEEK_SET);
						if(flag == 0) {
								printf("Enter a valid username \n");
								printf("Press 1 to retry, any other key to return to staff page \n");
								cho = input();
						}	
				}
				while(cho == 1);
		}
		fclose(fr);
		fclose(fw);
		remove("userdet2.txt");
		rename("tempusr.txt", "userdet2.txt");
		staff_page(head);
}

//delete users from the database 
void del_users(book_t* head){
		char un[SIZE];
		char* line = NULL;
		char* n = NULL;
		char* e = NULL;
		char* uname = NULL;
		char* pw = NULL;
		char* ph = NULL;
		char* bo = NULL;
		size_t size = 0;
		FILE* fr = fopen("userdet2.txt", "r");
		FILE* fw = fopen("tempusr.txt", "w");
		int flag = 0;
		int cho = 0;
		int temp;
		if(fr == NULL || fw == NULL) {
				printf("Error in opening the file \n");
		}
		else {	
				printf("************************************************************\n");
				printf("*                        Delete User                       *\n");
				do {
						printf("Enter the username of the record to be modified :\n");
						fgets(un, SIZE, stdin);
						char* utemp = un;
						while(getline(&line, &size, fr) != -1) {
								char* tmp = line;
								n = strsep(&tmp, "|");
								e = strsep(&tmp, "|");
								uname = strsep(&tmp, "|");
								pw = strsep(&tmp, "|");
								ph = strsep(&tmp, "|");
								bo = tmp;
								if(strcmp(uname, nl_trimmer(&utemp)) == 0) {
										flag = 1;
										printf("Record successfuly Deleted!\n");
										printf("Press any key to return to the staff page\n");
										temp = input();

								}
							else {
										fprintf(fw, "%s|%s|%s|%s|%s|%s", n, e, uname, pw, ph, bo);
							}
						}
						free(line);
						fseek(fr, 0, SEEK_SET);
						if(flag == 0) {
								printf("Enter a valid username \n");
								printf("Press 1 to retry, any other key to return to staff page \n");
								cho = input();
						}	
				}
				while(cho == 1);
		}
		fclose(fr);
		fclose(fw);
		remove("userdet2.txt");
		rename("tempusr.txt", "userdet2.txt");
		staff_page(head);
		
}

//display all the users currently signed in.
void disp_users(book_t* head) {
		FILE* fr = fopen("userdet2.txt", "r");
		if(fr == NULL) {
				printf("Error in opening the file \n");
		}
		else {	char* n = NULL;
				char* e = NULL;
				char* u = NULL;
				char* p = NULL;
				char* ph = NULL;
				char* line = NULL;
				size_t len = 0;
				while(getline(&line, &len, fr) != -1) {
						char* tmp = line;
						n = strsep(&tmp, "|");
						e = strsep(&tmp, "|");
						u = strsep(&tmp, "|");
						p = strsep(&tmp, "|");
						ph = strsep(&tmp, "|");
						printf("***************************************\n");
						printf("*  Name :  %s                         *\n", n);
						printf("*  Email :  %s                        *\n", e);
						printf("*  Phone number :  %s                 *\n", ph);
						printf("*  Username :  %s                     *\n", u);
						printf("*  Password :  %s                     *\n", p);
						printf("***************************************\n");
				}
				free(line);
				fclose(fr);
				printf("Press any key to return to the staff page\n");
				int temp = input();
				staff_page(head);

		}
}

//interface for usermanagement portal
void user_mgmt(book_t* head){
		system("clear");
		printf("************************************************************\n");
		printf("*                         Welcome!                         *\n");
		printf("*                                                          *\n");
		printf("*                  1) Add New Users                        *\n");
		printf("*                  2) Modify Existing Users                *\n");
		printf("*                  3) Delete Existing Users                *\n");
		printf("*                  4) Display all users                    *\n");	
		printf("*                  5) Return to Staff Page                 *\n");
		printf("*                                                          *\n");
		printf("************************************************************\n");
		int ch;
		printf("Enter your choice (1/2/3/4/5) : \n");
		do{
			ch = input();
			if(ch == 1){		
				add_users(head);
			}
			else if(ch == 2){
				mod_users(head);
			}
			else if(ch == 3){
				del_users(head);
			}
			else if(ch == 4) {
					disp_users(head);
			}
			else if(ch == 5){
				staff_page(head);
			}
			else{
				printf("Invalid Choice!\n");
				printf("Please enter a Valid Choice!\n");
				ch=0;
			}
		}
		while (ch == 0);
}



void book_order(book_t* head){		//This function accesses "venddet.txt" and asks the user to search for Vendors and enter a Book-ID. The details of that book are then stored in "books.txt"
	
		FILE *fp, *add;
		fp=fopen("venddet.txt","r");
		add=fopen("books.txt","a");
		
		if(fp==NULL || add==NULL)
		printf("Error!\n");
		
		else{
			int day, month, year;
		
			time_t now;
			time(&now);
			struct tm *local = localtime(&now);
			day = local->tm_mday;			// get day of month (1 to 31)
			month = local->tm_mon + 1;	   	// get month of year (0 to 11)
			year = local->tm_year + 1900;		// get year since 1900
		
			book_t* book = NULL;
		
			char read[SIZE];
			char inp[SIZE];
			char em[SIZE];
			int ch, hc;
			
			char st[SIZE];
			char sa[SIZE];
			char sg[SIZE];
		
			char* s1 = malloc(SIZE * sizeof(char));
			char* s2 = malloc(SIZE * sizeof(char));
		
			char* dd = malloc(SIZE * sizeof(char));
			char* mm = malloc(SIZE * sizeof(char));
			char* yyyy = malloc(SIZE * sizeof(char));
		
			char tid[SIZE];
			int copies;
			int id;
			int count=0;


				ch = 0;
				system("clear");
				printf("************************************************************\n");
				printf("*                         Welcome!                         *\n");
				printf("*                                                          *\n");
				printf("*                   Displaying Vendor List                 *\n");
				printf("*                                                          *\n");
				fseek(fp, 0, SEEK_SET);
				while(fgets(read,sizeof(read),fp)){
					if(strcmp("Vendor\n",read)==0){
						printf("--> %s",read);
						fgets(read,sizeof(read),fp);
						printf("--> %s\n",read);
					}
				}
			
				do{
			
					fseek(fp,0,SEEK_SET);
					printf("-->Enter Vendor's Name: ");
					fgets(inp,sizeof(inp),stdin);
					if(strcmp(inp,"\n")==0){
						printf("Retry\n");
						ch = 1;
						break;
					}
					else{
						printf("************************************************************");

						while(fgets(read,sizeof(read),fp)){
							if(strcmp(read,inp)==0){
								fgets(read,sizeof(read),fp);
								strcpy(em,read);
								for(int i=1;i<=2;i++){
									fgets(read,sizeof(read),fp);
								}	
							
								while(fgets(read,sizeof(read),fp)){
									if(strcmp("Vendor\n",read)==0){
										printf("************************************************************\n\n");
										break;
									}
									else{
										if(strcmp(read,"\n")==0)
										{
											printf("%s",read);
										}
										else
										{
											printf("--> %s",read);
										}
										
									}
								}
					
								count++;	
							}
						}
					if(count == 0){
						printf("\nEnter the right choice!\n");
					}
					}
				}
				while(count == 0);
		
				count=0;
		
				do{
				
					printf("\n-->Enter the ID of the book you would like to order: ");
					fgets(tid, sizeof(tid), stdin);
					sscanf(tid, "%d", &id);
			
					fseek(fp,0,SEEK_SET);
					while(fgets(read,sizeof(read), fp)){
						if(strcmp(tid, read)==0){
							
							fgets(st, sizeof(st), fp);						   
							fgets(sa, sizeof(sa), fp);
							fgets(sg, sizeof(sg), fp);
	
							++count;
							printf("\n-->Enter the no. of copies you would like to order: ");
							copies = input();
															
							sprintf(dd, "%d|", day);
							sprintf(mm, "%d|", month);
							sprintf(yyyy, "%d|", year);
							sprintf(s2, "%d", copies);
	
							strcat(dd,mm);
							strcat(dd,yyyy);
							strcat(dd,s2);
	
							sprintf(s1,"%s|%s|%s|%s\n",dd,replace(sa),replace(sg),st);
							fprintf(add,"%s",s1);				
							printf("\n-->Would you like to place an order of '%d' copies to Vendor '%s' to their E-Mail ID '%s' ?\n",copies, replace(inp), replace(em));
							printf("-->Enter 1 to place order else any other character to re-order different book from the same vendor: ");
							hc = input();

							
						}
					}	
					if(count == 0){
						printf("Error! No Such ID found! Please try again!\n");
					}	
				}
				while(count == 0 || hc != 1);
							book = create_new_node(day, month, year, id, copies, sa, sg, st);
							insert_at_tail(&head, book);
				
				printf("\n*** Order Successfully Placed! ***\n\n");
	
			free(s1);
			free(s2);

			free(mm);
			free(dd);
			free(yyyy);

			fclose(fp);

			staff_page(head);
		}		
}


//interface for the staff page, allows user management, inventory and order books
void staff_page(book_t* head){
		system("clear");
		printf("************************************************************\n");
		printf("*                         Welcome!                         *\n");
		printf("*                                                          *\n");
		printf("*                  1) User Management                      *\n");
		printf("*                  2) Inventory                            *\n");
		printf("*                  3) Place Book Orders                    *\n");
		printf("*                  4) Return to Main Page                  *\n");
		printf("*                                                          *\n");
		printf("************************************************************\n");
		int ch;
		printf("Enter your choice (1/2/3/4) : \n");
		do{
			ch = input();
			if(ch == 1){
				user_mgmt(head);
			}
			else if(ch == 2){
				printlist(head);
			}
			else if(ch == 3){
				book_order(head);
			}

			else if(ch == 4){
				main_page(head);
			}
			else{
				printf("Invalid Choice!\n");
				printf("Please enter a Valid Choice!\n");
				ch=0;
			}
		}
		while (ch == 0);
}

//main page displayed while entering the program
void main_page(book_t* head){
		system("clear");
		printf("************************************************************\n");
		printf("*                  Welcome to the Library                  *\n");
		printf("*                                                          *\n");
		printf("*                  1) Search for Books                     *\n");
		printf("*                  2) See New Arrivals                     *\n");
		printf("*                  3) User Login                           *\n");
		printf("*                  4) Staff Login                          *\n");
		printf("*                  5) Exit the Program                     *\n");
		printf("*                                                          *\n");
		printf("************************************************************\n");
		int ch;
		printf("Enter your choice (1/2/3/4/5) : \n");
		do{
				ch = input();
				if(ch == 1){
						book_search(head);
				}
				else if(ch == 2){
						seenew(head);
						printf("Press any key to return to the main page \n");
						int ch = input();
						main_page(head);
				}
				else if(ch == 3){
						user_login(head);
				}
				else if(ch == 4){
						staff_login(head);
				}
				else if(ch == 5){
						printf("Have a nice day!\n");
						exit(0);
				}
				else{
					printf("Invalid choice\n");
					printf("Please enter a valid choice\n");
					ch=0;
				}
		}		
	while(ch == 0);		
}


int main(){
		book_t* head = NULL;
		head = File_to_ll(head);
		main_page(head);
		destroy(head);
		return 0;
}

