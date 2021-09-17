#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
using namespace std;


//Define constants
#define C0_Adult 20.00
#define C0_Children 10.00
#define C0_Student 12.00

#define C1_Adult 16.00
#define C1_Children 6.00
#define C1_Student 8.00

#define C2_Adult 18.00
#define C2_Children 8.00
#define C2_Student 10.00

//Declare functions
void display_logo();
void input_movie(string &movie, string &date, string &mtime);
void display_CounterOpen(int &Class0, int &Class1, int &Class2); //begining
void input_seatclass(int &seatclass);
void input_customer(int &No_of_adults, int &No_of_children, int &No_of_students);
void calculate_bill(int seatclass, int No_of_adults, int No_of_children, int No_of_students, double &adultsum, double &childsum, double &studentsum);
void total_bill(int seatclass, double adultsum, double childsum, double studentsum);
void display_seats(int seats[3][30], int seatclass = -1);
void select_seats(int seats[3][30], int seatclass, int No_of_adults, int No_of_children, int No_of_students, int selected[30]);
void display_tickets(string movie, string date, string mtime, int seatclass, int No_of_adults, int No_of_children, int No_of_students, int selected[30]);
void display_reports(string movie, string date, string mtime, int Class0, int Class1, int Class2, int total_adults, int total_children, int total_students, double total_adult_sales, double total_child_sales, double total_student_sales);


int main()
{
	//Declare variables
	int No_of_adults, No_of_students, No_of_children, seatclass, Class0 = 15, Class1 = 15, Class2 = 30, availabletix, totaltix, total_adults = 0, total_children = 0, total_students = 0;
	int seats[3][30] = { {} };
	int selected[30];
	string date, mtime, movie;
	double adultsum, childsum, studentsum, total_adult_sales = 0.0, total_child_sales = 0.0, total_student_sales = 0.0;
	char Resp;

	display_logo(); //TARCinemax Logo
	input_movie(movie, date, mtime); // prompt user's input on movie name and movie date
	display_CounterOpen(Class0, Class1, Class2); // available seats

	do
	{

		do
		{
			// Input Seat Class
			input_seatclass(seatclass); 

			// Input Number of customers
			input_customer(No_of_adults, No_of_children, No_of_students); 
	
			// Count Total tickets
			totaltix = No_of_adults + No_of_children + No_of_students;

			// Count available tickets
			switch (seatclass)
			{
			case 0:
				availabletix = Class0;
				break;

			case 1:
				availabletix = Class1;
				break;

			case 2:
				availabletix = Class2;

			}
			if (availabletix < totaltix)
			{
				cout << "Not Enough Seats In This Class, Please Select Another Class.";
			}

		} while (availabletix < totaltix);

		// Billing
		calculate_bill(seatclass, No_of_adults, No_of_children, No_of_students, adultsum, childsum, studentsum);
		total_bill(seatclass, adultsum, childsum, studentsum);

		// Increase the total sales
		total_adults += No_of_adults;
		total_children += No_of_children;
		total_students += No_of_students;
		total_adult_sales += adultsum;
		total_child_sales += childsum;
		total_student_sales += studentsum;

		// Seats selection
		select_seats(seats, seatclass, No_of_adults, No_of_children, No_of_students, selected); 
		
		// Deduct the available seats 
		switch (seatclass)
		{
		case 0:
			Class0 -= totaltix;
			break;

		case 1:
			Class1 -= totaltix;
			break;

		case 2:
			Class2 -= totaltix;

		}

		cout << endl;
		cout << setw(25) << setfill(' ') << "HERE ARE YOUR TICKETS, ENJOY YOUR MOVIE!" << endl;

		// Print Tickets
		display_tickets(movie, date, mtime, seatclass, No_of_adults, No_of_children, No_of_students, selected);

		// Continue loop
		cout << "\n\t\t\t NEXT CUSTOMER? (Y/N) : \t\t\t";
		cin >> Resp;
		Resp = toupper(Resp);

	} while (Resp == 'Y' && ((Class0 +Class1 +Class2) > 0)); // Breaks loop when there tickets are sold out

	// Display Sales Report 
	display_reports(movie, date, mtime, Class0, Class1, Class2, total_adults, total_children, total_students, total_adult_sales, total_child_sales, total_student_sales);

	system("pause");
	return 0;
}

void display_logo()
{
	cout << setw(50) << setfill(' ') << "______________________________" << endl;
	cout << setw(50) << setfill(' ') << "|                            |" << endl;
	cout << setw(50) << setfill('-') << "|TAR Cinemax Ticketing System|" << "------------------------" << endl;
	cout << setw(50) << setfill(' ') << "|____________________________|" << endl;
}

void input_movie(string &movie, string &date, string &mtime)
{
	cout << "Movie Name: ";
	getline(cin, movie);

	cout << "Date (Day DD-MM-YYYY): ";
	getline(cin, date);

	cout << "Time (24hours): ";
	getline(cin, mtime);

	cout << endl;
}

void display_CounterOpen(int &Class0, int &Class1, int &Class2)
{
	cout << "Counter is Open for Selling of Tickets" << endl;
	cout << endl;
	cout << "Seats Available: " << endl;
	cout << "-----------------" << endl;
	cout << endl;
	cout << setw(25) << setfill(' ') << "Class 0 (VIP) - " << Class0;
	cout << setw(25) << setfill(' ') << "Class 1 (FRONT) - " << Class1;
	cout << setw(25) << setfill(' ') << "Class 2 (BACK) - " << Class2;
	cout << endl;
}

void input_seatclass(int &seatclass)
{
	do
	{
		cout << endl;
		cout << "Seating Class (0,1,2): ";
		cin >> seatclass;
		cout << endl;

		if (seatclass <= 2 && seatclass >= 0)
			break;
		else
			cout << "Invalid Class! Please Enter Again." << endl;

	} while (seatclass > 2);
}

void input_customer(int &No_of_adults, int &No_of_children, int &No_of_students)
{
	cout << "Number of Adults \t\t\t : ";
	cin >> No_of_adults;

	cout << "Number of Children (BELOW 12 YEARS OLD)\t : ";
	cin >> No_of_children;

	cout << "Number of Students (PRESENT STUDENT CARD): ";
	cin >> No_of_students;
}

void calculate_bill(int seatclass, int No_of_adults, int No_of_children, int No_of_students, double &adultsum, double &childsum, double &studentsum)
{
	switch (seatclass)
	{
	case 0:

		cout << fixed << setprecision(2);
		adultsum = No_of_adults * C0_Adult;
		cout << endl;
		cout << "Number of Adults : \t" << No_of_adults << " @ RM" << C0_Adult << "\t = \t RM " << adultsum;
		cout << endl;

		childsum = No_of_children * C0_Children;
		cout << "Number of Children : \t" << No_of_children << " @ RM" << C0_Children << "\t = \t RM " << childsum;
		cout << endl;

		studentsum = No_of_students * C0_Student;
		cout << "Number of Students : \t" << No_of_students << " @ RM" << C0_Student << "\t = \t RM " << studentsum;
		cout << endl;
		break;

	case 1:

		cout << fixed << setprecision(2);
		adultsum = No_of_adults * C1_Adult;
		cout << endl;
		cout << "Number of Adults : \t" << No_of_adults << " @ RM" << C1_Adult << "\t = \t RM " << adultsum;
		cout << endl;

		childsum = No_of_children * C1_Children;
		cout << "Number of Children : \t" << No_of_children << " @ RM" << C1_Children << "\t = \t RM " << childsum;
		cout << endl;

		studentsum = No_of_students * C1_Student;
		cout << "Number of Students : \t" << No_of_students << " @ RM" << C1_Student << "\t = \t RM " << studentsum;
		cout << endl;
		break;

	case 2:

		cout << fixed << setprecision(2);
		adultsum = No_of_adults * C2_Adult;
		cout << endl;
		cout << "Number of Adults : \t" << No_of_adults << " @ RM" << C2_Adult << "\t = \t RM " << adultsum;
		cout << endl;

		childsum = No_of_children * C2_Children;
		cout << "Number of Children : \t" << No_of_children << " @ RM" << C2_Children << "\t = \t RM " << childsum;
		cout << endl;

		studentsum = No_of_students * C2_Student;
		cout << "Number of Students : \t" << No_of_students << " @ RM" << C2_Student << "\t = \t RM " << studentsum;
		cout << endl;
	}

}

void total_bill(int seatclass, double adultsum, double childsum, double studentsum)
{
	double total, cash, changedue;

	cout << endl;
	cout << setw(25) << setfill(' ') << "TOTAL BILL - CLASS " << seatclass << endl;
	cout << setw(25) << setfill(' ') << "--------------------";
	cout << endl;

	// Total, cash payment and change due
	cout << endl;
	cout << fixed << setprecision(2);
	total = adultsum + childsum + studentsum;
	cout << "Total = \t\t\t " << right << "RM " << total << endl;

	cout << "Cash Payment = \t\t\t " << right << "RM ";
	cin >> cash;
	cout << right;

	cout << "\t\t\t\t ========" << right;
	cout << endl;


	if (cash == total)
		cout << setw(25) << setfill(' ') << "\n\n------Thank You, Please Come again------\n\n";

	else
	{
		changedue = cash - total;
		cout << "Change Due = \t\t\t " << right << "RM " << changedue << endl;

		cout << "\t\t\t\t ========" << right;
		cout << endl;
	}

}

void display_seats(int seats[3][30], int seatclass)
{
	// Display all seat classes
	if (seatclass == -1) 
	{
		for (int i = 0; i < 3; i++) // i = seatclass 
		{
			cout << "\nClass " << i << "\n";
			cout << "---------\n";

			for (int j = 1; j <= 30; j++) // j = seatnumber
			{
				//  Only class 2 has 30 seats
				if (i != 2 && j > 15) 
				{
					break;
				}

				// Seat Taken
				if (seats[i][j - 1] > 0)
				{
					cout << "x\t\t";
				}
				else 
				{
					if (j < 10) 
						cout << i << "0" << j << "\t\t";
					else 
						cout << i << j << "\t\t";
				}

				if (j % 5 == 0) {
					cout << "\n";
				}
			}
			cout << "\n";
		}
	}
	else
	{
		cout << "Class " << seatclass << "\n";
		for (int j = 1; j <= 30; j++) 
		{
			// This is because only class 2 has 30 seats
			if (seatclass != 2 && j > 15) 
			{
				break;
			}

			if (seats[seatclass][j-1] > 0) 
			{
				cout << "x\t\t";
			}
			else 
			{
				if (j < 10) 
					cout << seatclass << "0" << j << "\t\t";
				else 
					cout << seatclass << j << "\t\t";
			}

			if (j % 5 == 0) 
			{
				cout << "\n";
			}
		}
		cout << "\n";

	}
}

void select_seats(int seats[3][30], int seatclass, int No_of_adults, int No_of_children, int No_of_students, int selected[30])
{
	int seatnumber, actualSeatNumber, total = 0;
	int remainingtix = No_of_adults + No_of_children + No_of_students;

	do {
		display_seats(seats, seatclass);
		cout << "Please select your seats (Enter the seat number): ";
		cin >> seatnumber;
		cout << "\n";
		if (seatnumber / 100 != seatclass) {
			cout << "This seat does not belong to your seat class!\n";
		}
		else {
			actualSeatNumber = (seatnumber % 100) - 1;
			if (seats[seatclass][actualSeatNumber] > 0) 
			{
				cout << "That seat is not available!\n";
			}
			else
			{
				seats[seatclass][actualSeatNumber] = 1;

				selected[total++] = seatnumber;
				remainingtix -= 1;
			}
		}
	} while (remainingtix > 0);
}

void display_tickets(string movie, string date, string mtime, int seatclass, int No_of_adults, int No_of_children, int No_of_students, int selected[])
{
	int i, total = 0, seatnum;
	double adultprice, childprice, studntprice;

	// Declare ticket price for each class
	if (seatclass == 0)
	{
		adultprice = C0_Adult;
		childprice = C0_Children;
		studntprice = C0_Student;

	}
	else if (seatclass == 1)
	{
		adultprice = C1_Adult;
		childprice = C1_Children;
		studntprice = C1_Student;
	}
	else
	{
		adultprice = C2_Adult;
		childprice = C2_Children;
		studntprice = C2_Student;
	}


	// Adult Tickets
	for (i = 1; i <= No_of_adults; i++)
	{
		seatnum = selected[total++];
		cout << endl;
		cout << "|" << setw(96) << setfill('=') << "|" << endl;
		cout << "|" << setw(65) << setfill(' ') << "TAR CINEMAX TICKET \t\t\t\t:  ADULT - CLASS " << seatclass << "\t|" << endl;
		cout << "|" << setw(10) << setfill(' ') << "\t\t Movie Name : \t\t" << movie << right << "\t\t\t: \t" << movie << "\t|" << endl;
		cout << "|" << setw(10) << setfill(' ') << "\t\t Movie Date : \t\t" << date << right << "\t\t\t: \t" << date << "\t|" << endl;
		cout << "|" << setw(10) << setfill(' ') << "\t\t Movie Time : \t\t" << mtime << right << "\t\t\t\t: \t" << mtime << "\t\t|" << endl;
		cout << "|" << setw(10) << setfill(' ') << "\tSeat Number : " << setw(3) << setfill('0') << seatnum << fixed << setprecision(2) << "\t\t\tPrice : RM" << right << adultprice << "\t\t: \t" << setw(3) << setfill('0') << seatnum << "\t\t|" << endl;
		cout << "|" << setw(96) << setfill('=') << "|" << endl;
		cout << endl;

	}

	// Children Tickets
	for (i = 1; i <= No_of_children; i++)
	{
		seatnum = selected[total++];
		cout << endl;
		cout << "|" << setw(96) << setfill('=') << "|" << endl;
		cout << "|" << setw(65) << setfill(' ') << "TAR CINEMAX TICKET \t\t\t\t:  CHILDREN - CLASS " << seatclass << "\t|" << endl;
		cout << "|" << setw(10) << setfill(' ') << "\t\t Movie Name : \t\t" << movie << right << "\t\t\t: \t" << movie << "\t|" << endl;
		cout << "|" << setw(10) << setfill(' ') << "\t\t Movie Date : \t\t" << date << right << "\t\t\t: \t" << date << "\t|" << endl;
		cout << "|" << setw(10) << setfill(' ') << "\t\t Movie Time : \t\t" << mtime << right << "\t\t\t\t: \t" << mtime << "\t\t|" << endl;
		cout << "|" << setw(10) << setfill(' ') << "\tSeat Number : " << setw(3) << setfill('0') << seatnum << fixed << setprecision(2) << "\t\t\tPrice : RM" << right << childprice << "\t\t: \t" << setw(3) << setfill('0') << seatnum << "\t\t|" << endl;
		cout << "|" << setw(96) << setfill('=') << "|" << endl;
		cout << endl;

	}

	// Student Tickets
	for (i = 1; i <= No_of_students; i++)
	{
		seatnum = selected[total++];
		cout << endl;
		cout << "|" << setw(96) << setfill('=') << "|" << endl;
		cout << "|" << setw(65) << setfill(' ') << "TAR CINEMAX TICKET \t\t\t\t:  STUDENT - CLASS " << seatclass << "\t|" << endl;
		cout << "|" << setw(10) << setfill(' ') << "\t\t Movie Name : \t\t" << movie << right << "\t\t\t: \t" << movie << "\t|" << endl;
		cout << "|" << setw(10) << setfill(' ') << "\t\t Movie Date : \t\t" << date << right << "\t\t\t: \t" << date << "\t|" << endl;
		cout << "|" << setw(10) << setfill(' ') << "\t\t Movie Time : \t\t" << mtime << right << "\t\t\t\t: \t" << mtime << "\t\t|" << endl;
		cout << "|" << setw(10) << setfill(' ') << "\tSeat Number : " << setw(3) << setfill('0') << seatnum << fixed << setprecision(2) << "\t\t\tPrice : RM" << right << studntprice << "\t\t: \t" << setw(3) << setfill('0') << seatnum << "\t\t|" << endl;
		cout << "|" << setw(96) << setfill('=') << "|" << endl;
		cout << endl;
	}

}

void display_reports(string movie, string date, string mtime, int Class0, int Class1, int Class2, int total_adults, int total_children, int total_students, double total_adult_sales, double total_child_sales, double total_student_sales)
{
	int total_sold = 60 - (Class0 + Class1 + Class2);
	double percentage = 0.0;
	double total_sales = total_adult_sales + total_child_sales + total_student_sales;

	cout << endl << endl;
	cout << setw(80) << setfill('=');
	cout << "\n\t\t\t\t" << "TICKET SALES REPORT" << endl << endl;
	cout << "Movie Title: \t\t" << movie << endl;
	cout << "Date / Time: \t\t" << date << "(" << mtime << ")" << endl << endl;

	cout << "SEAT OCCOPANCY FOR EACH CLASS:" << endl << endl;
	cout << "\t\tTotal Seats \t\tQuantity Sold\t\tSold %" << endl;

	cout << "Class 0\t\t" << setw(6) << setfill(' ') << right << "15" << "\t\t\t" << setw(7) << right << (15-Class0) << "\t\t\t ";
	percentage = (15.0 - Class0) / 15.0 * 100.0;
	cout << setw(3) << setfill(' ') << right << setprecision(0) << fixed << percentage << endl;

	cout << "Class 1\t\t" << setw(6) << setfill(' ') << right << "15" << "\t\t\t" << setw(7) << right << (15- Class1) << "\t\t\t ";
	percentage = (15.0 - Class1) / 15.0 * 100.0;
	cout << setw(3) << setfill(' ') << right << setprecision(0) << fixed << percentage << endl;

	cout << "Class 2\t\t" << setw(6) << setfill(' ') << right << "30" << "\t\t\t" << setw(7) << right << (30-Class2) << "\t\t\t ";
	percentage = (30.0 - Class2) / 30.0 * 100.0;
	cout << setw(3) << setfill(' ') << right << setprecision(0) << fixed << percentage << endl;

	cout << "\t\t  ------ \t\t   ------ \t       --------" << endl;
	percentage = (double)total_sold / 60.0 * 100.0;
	cout << "\t\t    60   \t\t     " << setw(2) << right << total_sold << "   \t         ";
	cout << setw(3) << setfill(' ') << right << setprecision(0) << fixed << percentage << endl << endl;

	cout << "SALES FOR EACH CATEGORY TYPE\n\n";
	cout << "\t\tCategory \t\t    Seats\t\tSales (RM)" << endl;

	cout << "\t\t  ADULT \t\t    " << setw(3) << right << total_adults << "\t\t\t ";
	cout << setw(6) << setfill(' ') << setprecision(2) << fixed << total_adult_sales << endl;

	cout << "\t\t  CHILD \t\t    " << setw(3) << right << total_children << "\t\t\t ";
	cout << setw(6) << setfill(' ') << setprecision(2) << fixed << total_child_sales << endl;

	cout << "\t\t  STUDENT\t\t    " << setw(3) << right << total_students << "\t\t\t ";
	cout << setw(6) << setfill(' ') << setprecision(2) << fixed << total_student_sales << endl;

	cout << "\t\t\t\t\t   -------\t\t----------" << endl;
	cout << "\t\t  TOTAL \t\t    " << setw(3) << right << total_sold << "\t\t\t ";
	cout << setw(6) << setfill(' ') << setprecision(2) << fixed << total_sales << endl << endl;
	cout << setw(80) << setfill('=');
}
