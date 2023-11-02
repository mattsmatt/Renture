# include <stdio.h>
# include <string.h>

struct car {
	char carName[200], type[100];
	int seat;
	long int price;
	float rating;
};

struct date {
	int d, m, y;
};

struct carOrder {
	char userName[200], carName[400];
	struct date pickUp;
	struct date dropOff;
};

void border(){
	printf("\n"); 
	for (int i=0; i<120; i++){
		printf("="); 
	}
	printf("\n\n"); 
}

int abs(int n){
	if(n >= 0){
		return n;
	}
	else
		return (0-n);
}

void header(){
	printf("\t\t\t"); 
		for (int i=0; i<65; i++){
			printf("#"); 
		}
	printf("\n"); 
		puts("\t\t\t#                                                               #");		
		puts("\t\t\t# 888~-_                       d8                               #");          
		puts("\t\t\t# 888   \\  e88~~8e  888-~88e _d88__ 888  888 888-~  e88~~8e     #");		
		puts("\t\t\t# 888   | d888  88b 888  888  888   888  888 888   d888  88b    #");		
		puts("\t\t\t# 888   / 8888__888 888  888  888   888  888 888   8888__888    #");		
		puts("\t\t\t# 888_-~  Y888    , 888  888  888   888  888 888   Y888    ,    #");		
		puts("\t\t\t# 888 ~-_  *88___/  888  888  *88_/ *88_-888 888    *88___/     #");		
		puts("\t\t\t#                                        ~ Rental Car Service   #");		
		puts("\t\t\t#                                                               #");
		// ASCII art made with https://manytools.org/hacker-tools/ascii-banner/
	printf("\t\t\t"); 
		for (int i=0; i<65; i++){
			printf("#");
		}
	printf("\n");
	border();
};

void menu(){
	puts("Welcome to the Main Menu!");
	puts("Please type a number to access the program\n");
	puts("1. Display All Selection of Cars");
	puts("2. Search Car");
	puts("3. Your Shopping Cart");
	puts("4. Add to Shopping Cart");
	puts("5. Delete All Items in Cart");
	puts("6. Sort Cars by Name in Descending Order");
	puts("7. Sort Cars by Price");
	puts("8. Display Feedback from Other Customers");
	puts("9. Input Your Feedback");
	puts("0. Exit\n");
}

void display(struct car selection[], int i){
	printf("Car:			%s\n", selection[i].carName);
	printf("Type:			%s\n", selection[i].type);
	printf("Seats:			%d\n", selection[i].seat);
	printf("Daily Price:		%ld\n", selection[i].price);
	printf("Rating:			%.1f / 5.0\n", selection[i].rating);
	printf("\n");
}

void DisplayAll(struct car selection[]){
	border();
	for(int i = 0; i<6; i++){
		display(selection, i);
	}
}

struct car SearchCar(struct car selection[], int l, int r, char x[200]){
	struct car sResult;
	// search result
	while (l <= r){
		int mid = (l + r) / 2;
//		printf("%d %d %d \n", l, mid, r);
		if(strcmp(selection[mid].carName, x) == 0){
			sResult = selection[mid];
			return sResult;
		}
		
		if(strcmp(x, selection[mid].carName) < 0){
			return SearchCar(selection, l, mid-1, x);
		}
			
		if(strcmp(x, selection[mid].carName) > 0){
			return SearchCar(selection, mid+1, r, x);
		}
	}
	return sResult;
}

void case3Menu(int *c2){
	border();
	puts("Please type a number to access the program");
	puts("1. Update Date");
	puts("2. Display Shopping Cart");
	puts("0. Return to Menu");
	printf("\n");
	scanf("%d", c2);
	getchar();
}

	void updateOrder(){
		border();
		char x[200];
		printf("Search username: ");
		scanf("%[^\n]", x);
		getchar();
		FILE *fp = fopen ("./isiorderan.txt", "r");
		FILE *fp2 = fopen ("./tampungansementara.txt", "w");
		struct carOrder car;
		while (fscanf(fp, "%[^#]#%[^#]#%d-%d-%d#%d-%d-%d\n",car.userName, car.carName, &car.pickUp.d, &car.pickUp.m, &car.pickUp.y, &car.dropOff.d, &car.dropOff.m, &car.dropOff.y ) != EOF){
			if (strcmp(x, car.userName) == 0){
				printf("Enter new pickup date: ");
				scanf("%d-%d-%d", &car.pickUp.d, &car.pickUp.m, &car.pickUp.y);
				printf("Enter new dropoff date: ");
				scanf("%d-%d-%d", &car.dropOff.d, &car.dropOff.m, &car.dropOff.y);
			}
			fprintf(fp2, "%s#%s#%d-%d-%d#%d-%d-%d\n", car.userName, car.carName, car.pickUp.d, car.pickUp.m, car.pickUp.y, car.dropOff.d, car.dropOff.m, car.dropOff.y);
		}
		fclose(fp);
		fclose(fp2);
	 
	 
		fp = fopen ("./isiorderan.txt", "w");
		fp2 = fopen ("./tampungansementara.txt", "r");
		
		while (fscanf(fp2, "%[^#]#%[^#]#%d-%d-%d#%d-%d-%d\n",car.userName, car.carName, &car.pickUp.d, &car.pickUp.m, &car.pickUp.y, &car.dropOff.d, &car.dropOff.m, &car.dropOff.y ) != EOF){
			fprintf(fp, "%s#%s#%d-%d-%d#%d-%d-%d\n", car.userName, car.carName, car.pickUp.d, car.pickUp.m, car.pickUp.y, car.dropOff.d, car.dropOff.m, car.dropOff.y);
		}
		fclose(fp);
		fclose(fp2);
	}
	
	void DisplayOrder(struct car selection[]){
		border();
		long int price;
		bool leap;
		int days;
		struct carOrder order;
		FILE *fptr = fopen(".\\isiorderan.txt","r");	
		while(fscanf(fptr,"%[^#]#%[^#]#%d-%d-%d#%d-%d-%d\n", order.userName, order.carName,\
		&order.pickUp.d, &order.pickUp.m, &order.pickUp.y, &order.dropOff.d, &order.dropOff.m,\
		&order.dropOff.y) != EOF){
			for(int i=0; i<6; i++){
				leap = false;
				if(strcmp(selection[i].carName, order.carName) == 0){
					price = selection[i].price;
					if (order.pickUp.y % 4 == 0){
						leap = true;
					}
					if (order.pickUp.m == 2 && order.dropOff.m % 2 != 0 && leap){
						days = (29 % order.pickUp.d + order.dropOff.d + 1);
					}
					else if (order.pickUp.m == order.dropOff.m){
						days = (order.dropOff.d - order.pickUp.d + 1);
					}
					else{
						if (1 <= order.pickUp.m && order.pickUp.m <= 7){
							if(order.pickUp.m % 2 == 0 && order.dropOff.m % 2 != 0){
								days = (30 % order.pickUp.d + order.dropOff.d + 1);
							}
							else if (order.pickUp.m % 2 != 0 && order.dropOff.m % 2 == 0){
								days = (31 % order.pickUp.d + order.dropOff.d + 1);
							}
						}
						else
							if(order.pickUp.m % 2 == 0 && order.dropOff.m % 2 != 0){
								days = (31 % order.pickUp.d + order.dropOff.d + 1);
							}
							else if (order.pickUp.m % 2 != 0 && order.dropOff.m % 2 == 0){
								days = (30 % order.pickUp.d + order.dropOff.d + 1);
							}
					}
					
					(1 <= days && days <= 7)? price *= days: price = 0;
					((abs(order.pickUp.m-order.dropOff.m) > 1 || order.pickUp.y != order.dropOff.y) && order.pickUp.m != 12)? price = 0: printf("");
					if(order.pickUp.m == 12){
						if(order.dropOff.m != 12 and order.dropOff.m != 1){
							price = 0;
						}
					}
					(price < 0)? price = 0: printf("");
					(order.pickUp.d > 28 && order.pickUp.m == 2 && !leap)? price = 0: printf("");
					(order.dropOff.d > 28 && order.dropOff.m == 2 && !leap)? price = 0: printf("");
				}
			}
			printf("Name:		%s\n", order.userName);
			printf("Car:		%s\n", order.carName);
			printf("Pickup date:	%d-%d-%d\n", order.pickUp.d, order.pickUp.m, order.pickUp.y);
			printf("Dropoff date:	%d-%d-%d\n", order.dropOff.d, order.dropOff.m, order.dropOff.y);
			(price == 0)? printf("Pickup & Dropoff date not valid\n"): printf("Total price:	%ld\n", price);
			printf("\n");
		}
	}

void rentinput(struct car selection[]){
	bool inArray = false;
	struct carOrder rent;
	FILE *fp = fopen("./isiorderan.txt", "a");
	printf("Name: ");
	scanf("%[^\n]", rent.userName);
	getchar();
	printf("Car: ");
	scanf("%[^\n]", rent.carName);
	getchar();
	for (int i=0; i<6; i++){
		if(strcmp(selection[i].carName, rent.carName) == 0){
			inArray = true;
		}	
	}
	if(inArray != true){
		puts("Car not available");
		fclose(fp);
		return;
	}
	printf("Pickup date (DD-MM-YYYY): ");
	scanf("%d-%d-%d", &rent.pickUp.d, &rent.pickUp.m, &rent.pickUp.y);
	printf("Dropoff date (DD-MM-YYYY) (Max. 7 days after pickup): ");
	scanf("%d-%d-%d", &rent.dropOff.d, &rent.dropOff.m, &rent.dropOff.y);
	printf("\n");
	fprintf(fp, "%s#%s#%d-%d-%d#%d-%d-%d\n", rent.userName, rent.carName,\
	rent.pickUp.d, rent.pickUp.m, rent.pickUp.y, rent.dropOff.d, rent.dropOff.m,\
	rent.dropOff.y);
	fclose(fp);
}

void dlete (){
	FILE *fp = fopen ("./isiorderan.txt", "w");
	fclose(fp);
}

void mergeName(struct car selection[], int l, int mid, int r){
	int Lsize = mid - l + 1;
	int Rsize = r - mid;
	
	struct car Larray [Lsize];
	struct car Rarray [Rsize];
	
	for (int i=0; i<Lsize; i++){
		Larray[i] = selection[i + l];
		// the array index must be added by l \
		to adapt to new inputs from the recursion
	}
	
	for (int i=0; i<Rsize; i++){
		Rarray[i] = selection[i + mid + 1];
	}
	
	int idx = l;
	// to not change the original position of said element
	int idxL = 0, idxR = 0;
	// to track the length of left and right arrays
	while (idxL < Lsize && idxR < Rsize){
	// to ensure that the left and right arrays don't experience overflow
		if (strcmp(Larray[idxL].carName, Rarray[idxR].carName) >= 0){
			// compare between minimum values of both arrays
			selection[idx] = Larray[idxL];
			idxL++;
			// increment to move on to the next element of the left array \
			that might be the next element on the destined array
		}
		else{
			selection[idx] = Rarray[idxR];
			idxR++;
			// increment to move on to the next element of the right array \
			that might be the next element on the destined array
		}
		idx++;
	}
	
	while(idxL < Lsize){
		selection[idx] = Larray[idxL];
		idxL++;
		idx++;
	}
	
	while(idxR < Rsize){
		selection[idx] = Rarray[idxR];
		idxR++;
		idx++;
	}
	
	return;
}

void splitName(struct car selection[], int l, int r){
	if (l >= r){
		return;
	}
	// when the low limit exceeds or is equal to the high limit, \
	the function will return the accumulated results
	int mid = (l + r) / 2;
	// divide and conquer
	splitName(selection, l, mid);
	splitName(selection, mid+1, r);
	// recursions used to repeatedly divide the array, \
	then returning the elements of the given array in batches
	mergeName(selection, l, mid, r);
	// the function will run with the final values of l, mid, r \
	before the if condition is fulfilled (0 0 1) or (6 6 7)
}

void mergePrice(struct car selection[], int l, int mid, int r){
	int Lsize = mid - l + 1;
	int Rsize = r - mid;
	
	struct car Larray [Lsize];
	struct car Rarray [Rsize];
	
	for (int i=0; i<Lsize; i++){
		Larray[i] = selection[i + l];
		// the array index must be added by l \
		to adapt to new inputs from the recursion
	}
	
	for (int i=0; i<Rsize; i++){
		Rarray[i] = selection[i + mid + 1];
	}
	
	int idx = l;
	// to not change the original position of said element
	int idxL = 0, idxR = 0;
	// to track the length of left and right arrays
	while (idxL < Lsize && idxR < Rsize){
	// to ensure that the left and right arrays don't experience overflow
		if (Larray[idxL].price < Rarray[idxR].price){
			// compare between minimum values of both arrays
			selection[idx] = Larray[idxL];
			idxL++;
			// increment to move on to the next element of the left array \
			that might be the next element on the destined array
		}
		else{
			selection[idx] = Rarray[idxR];
			idxR++;
			// increment to move on to the next element of the right array \
			that might be the next element on the destined array
		}
		idx++;
	}
	
	while(idxL < Lsize){
		selection[idx] = Larray[idxL];
		idxL++;
		idx++;
	}
	
	while(idxR < Rsize){
		selection[idx] = Rarray[idxR];
		idxR++;
		idx++;
	}
	

	return;
}

void splitPrice(struct car selection[], int l, int r){
	if (l >= r){
		return;
	}
	// when the low limit exceeds or is equal to the high limit, \
	the function will return the accumulated results
	int mid = (l + r) / 2;
	// divide and conquer
	splitPrice(selection, l, mid);
	splitPrice(selection, mid+1, r);
	// recursions used to repeatedly divide the array, \
	then returning the elements of the given array in batches
	mergePrice(selection, l, mid, r);
	// the function will run with the final values of l, mid, r \
	before the if condition is fulfilled (0 0 1) or (6 6 7)
}

void DisplayFeedback(){
	border();
	float rating;
	char comment[151];
	FILE *fptr = fopen(".\\feedback.txt","r");
	float sum = 0;
	int count = 0;
	while(fscanf(fptr, "%f#%[^\n]\n", &rating, comment) != EOF){
		count++;
		sum += rating;
		printf("Rating: %.1f\n", rating);
		printf("Comment: %s\n\n", comment);
	}
	printf("The average rating: %.1f / 5.0\n", sum/count);
	fclose(fptr);
}

void AddFeedback(){
	border();
	float rating;
	char comment[151], x[151];
	FILE *fptr = fopen(".\\feedback.txt","a");	
	printf("Rating ( / 5.0 ): ");
	scanf("%f", &rating);
	getchar();
	printf("Comment (max. 150 char): ");
	scanf("%[^\n]", x);
	getchar();
	strcpy(comment, x);
	if(strlen(comment) > 100){
		puts("Don't get too carried away there, buddy");
	}
	fprintf(fptr, "%.1f#%s\n", rating, comment);
	fclose(fptr);
}

void footer(){
	char ch = '-';
	while(ch != '\n'){
		static int i = 0;
		if(i == 32){
			ch = '\n';
			printf("%c", ch);
			i++;
		}
		else{
			printf("%c", ch);
			i++;
		}
	}
	
	puts("You may now leave the program");
	printf("\n");
	puts("\tBBBB   YY  YY EEEEEE  !!!  ");
	puts("\tBB  BB  YYYY  EE      !!!  ");
	puts("\tBBBB     YY   EEEEEE  !!!  ");
	puts("\tBB  BB   YY   EE           ");
	puts("\tBBBB     YY   EEEEEE  !!! ");
	// created manually
}

int main(){
	short unsigned int choice;
	struct car selection [6];
	FILE *fp = fopen("./carSelectionData.txt","r");
	for(int i = 0; i<6; i++){
		fscanf(fp, "%[^#]#%[^#]#%d#%ld#%f\n", selection[i].carName, selection[i].type, &selection[i].seat, &selection[i].price, &selection[i].rating);
	}
	fclose(fp);
	header();
	do{
		menu();
		bool found = false;
		scanf("%d", &choice);
		getchar();
		(0 <= choice && choice <= 9)? printf(""): puts("The number can only be in the range of 0 to 9");
		
		switch(choice){
			case 1:{
				DisplayAll(selection);
				break;
			}
			case 2:{
				char x [200];
				struct car sResult;
				printf("Search Car: ");
				scanf("%[^\n]", x);
				sResult = SearchCar(selection, 0, 5, x);
				for(int i = 0; i<6; i++){
					if(strcmp(selection[i].carName, sResult.carName) == 0){
						found = true;
					}
				}
				if (found == true){
					puts("Found");
					printf("Car:			%s\n", sResult.carName);
					printf("Type:			%s\n", sResult.type);
					printf("Seats:			%d\n", sResult.seat);
					printf("Daily Price:		%ld\n", sResult.price);
					printf("Rating:			%.1f / 5.0\n", sResult.rating);
					printf("\n");
				}
				else
					puts("Not found");
				break;
			}
			case 3:{
				int choice2;
				int *c2;
				c2 = &choice2;
				do{
					case3Menu(c2);
					switch(choice2){
						case 1:{
							updateOrder();
							break;
						}
						case 2:{
							DisplayOrder(selection);
							break;
						}
					}
				}while(choice2 != 0);
				break;
			}
			case 4:{
				rentinput(selection);
				break;
			}
			case 5:{
				char c = 'O';
				while(c != 'Y' and c != 'N'){
					puts("Are you sure? (Y / N)");
					scanf("%c", &c);
					getchar();
				}
				if(c == 'Y'){
					dlete();
				}
				else if(c == 'N'){
					printf("");
				}
				break;
			}
			case 6:{
				splitName(selection, 0, 6-1);
				puts("Sorting successful!\nDisplay all selection to see results.");
				break;
			}
			case 7:{
				splitPrice(selection, 0, 6-1);
				puts("Sorting successful!\nDisplay all selection to see results.");
				break;
			}
			case 8:{
				DisplayFeedback();
				break;
			}
			case 9:{
				AddFeedback();
				break;
			}
		}
		border();
	}while(choice != 0);
	
	footer();
	return 0;
}
