*********************************************************************************************************************************************************************************************
ReadMe for assignment submitted by 2019ABPS0976P
Practical section number: P10
Asignment question attempted: 2
*********************************************************************************************************************************************************************************************
Team:
1. 2019B2PS0957P   M.Ashwin
2. 2019ABPS0976P   Harihareshwar.R
*********************************************************************************************************************************************************************************************2
Description of how to run the code and observe the output:
1. The exe is called 2019ABPS0976P_P10.exe. It is a menu-driven application. 

2.The input files are "books.txt", "staffdet.txt", "userdet2.txt" and "venddet.txt".
	2.a.The "books.txt" holds information of all the books present in the library in the format dd|mm|yyyy|Quantity|Author|Genre|Title where '|' is a delimiter.
	2.b.The "staffdet.txt" holds information of the staffs' usernames and their passwords which is used for logging into the staff page.
	2.c.The "userdet2.txt" contains information of the users and the ID of the books they borrowed along with the borrow date. 
	    The format is Name|E-Mail ID|Username|Password|Ph. No.|Book ID.dd/mm/yyyy, where '|', '.' and ',' are delimiters.
	2.d.The "venddet.txt" contains information of the vendors details and their respective books with IDs.

3. On executing the exe, the menu presents four choices to the user namely, Searching for Books, Viewing New Arrivals, accessing User Page and Staff Page.

4. In Choice 1 "Search for Books", the User can Search for Books based on their Title, Author, Genre and Issue No.(ID).

5. Choice 2 "New Arrivals" displays newly added books to the Library which the user could borrow if their interested from thier User Page.

6. Choice 3 "User Login" requires the user to enter their corresponding username and password to access their User Page.
	6.a. On accessing the User Page, the user is prompted to Borrow New books or Return their Previous books.
	6.b. The User can view the "Notification Centre" option to see for due books and if a book they ordered for borrowing is now available.
	6.c. Use any of the credentials from "userdet.txt" to access the User Page.
		Eg: rakesh111 -> Username
		    t!redrg0  -> Password
		*** Please note that these are case sensitive ***

7. Choice 4 "Staff Login" requires user to enter their respective credentials in order to access the Staff Page.
	7.a. In Staff Page, the staff can Add new users, Modify existing users or Delete Users via the "User Management" Page.
	7.b. The staff can view stock of all their books in "Inventory".
	7.c. Finally, the Staff can place order for new books from a list of vendors by entering their respective name and the ID of the book they would like to order from that list.
	7.d. Use any of the credentials from "staffdet.txt" to access the Staff Page.
		Eg: John    -> Username
		    point@9 -> Password
		*** Please note that these are case sensitive ***

8. Ensure before program compilation that all the text files(5 in total excluding ReadMe.txt) are present in the same folder.

9. Note that before borrowing a book, the user has to search for it to know it's ID.
		Eg: For User Rakesh, try entering Book ID 1.

10. strsep and strcspn were used a lot in this program, strsep is used to separate a string at a delimiter, strcspn scans the string for the delimter
*********************************************************************************************************************************************************************************************
Known limitations of the code:
1. We did not check for borrowing of same book twice(or multiple times) by the same user.
2. Giving Enter Key ('\n') as an input might lead to wrong results in some functions.
3. No check for negative/zero in quantity of books while ordering.
4. No check for users having same username.
5. Some issues with time.h functions which has problems near month end, have to be fixed by accounting for this edge case.(becuause of this due date might be wrong/-ve).
6. There are some problems when reordering at the same time when prompted, instead have to return to main and then order the next book.
7. order gets updated  only after closing and reopening the program(becuase it takes time for the books to get delivered!, its a feature not a bug! :P).
8.Sometimes there are problems with return when the user enters a bookid that wasnt borrowed.
9.could not implement the queues for book reservation.
*********************************************************************************************************************************************************************************************
Contributions of the team members:
1.Ashwin did the first two choices namely "Search for Books" and "New arrivals" along with "User Page" and "Inventory".
2.Hari did "User Login", "Staff Login", "User Management" and "Order Books".
We also helped out and did each other's code.
We also took help from internet for help with some functions and also used the linux man pages extensively!
links to some articles form which we got ideas :
1) http://sekrit.de/webdocs/c/beginners-guide-away-from-scanf.html
2) https://stackoverflow.com/questions/11280523/c-reading-from-file-into-structure
3) https://stackoverflow.com/questions/8257714/how-to-convert-an-int-to-string-in-c
*********************************************************************************************************************************************************************************************
