#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>
#include <thread>
#include <limits>
#include <stdlib.h>
#include <fstream>
#include <sstream>

using namespace std;

#define TotalSymptoms 11

string login();
bool login_check(string IC, string pwd, string name);
void regst();
string full_name();
string getIC();
int getAge(string user_ic);
string getGender(string user_ic);
string state();
string password();
string phone_num();
string email_addr();
bool is_valid_email(string email);
string vaccination_status();
bool is_valid_vs(char answer);
string covid_s(string ic_num);
void symptom(string ic_num);
bool is_valid_cs(char cs);
void display_info(string ic);
void display_symptom(string ic);
void updatecvd_txtfile(string ic);
void updatevcc_txtfile(string ic);
void update_data(string ic);
void dashboard();
void faq();
void display_header();
void refresh_pg();
void printLine(int width, char borderChar, char fillChar);

int main(void)
{
	//when system opening
	int choice;
	display_header();

	//let users choose to login or register the account
	cout << "Press [1] LOGIN or [2] REGISTER: ";
	cin >> choice;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	//to make sure users keyin the correct answer
	do
	{
		if (choice != 1 && choice != 2)
		{
			cout << "Please choose [1] or [2]: ";
			cin >> choice;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

	} while (choice != 1 && choice != 2);

	system("CLS");
	display_header();

	//login
	if (choice == 1)
	{
		string ic = login();
		display_info(ic);
		display_symptom(ic);
		update_data(ic);
		this_thread::sleep_for(chrono::milliseconds(3000));
	}
	//register
	else if (choice == 2)
		regst();

	system("CLS");
	display_header();

	dashboard();
	return 0;
}

struct USER
{
	string ic_name;
	string ic_num;
	int age;
	string user_gender;
	string password;
	string phone;
	string email;
	string state;
	char covid_status;
	string vaccination_status;
};

string login()
{
	//design
	cout << "\t\t        ACCOUNT LOGIN" << endl;
	cout << "==================================================================="  << endl;

	//Users need to keyin their Full Name, IC and password to login
	string ic_name;
	cout << "Enter Your Full Name: ";
	getline(cin, ic_name);

	// Convert the name to uppercase
	for (char& c : ic_name)
		c = toupper(c);

	string ic_num;
	cout << "Enter your IC number without'-': ";
	cin >> ic_num;

	string pw;
	cout << "Enter your password: ";
	cin >> pw;

	//if the information of the user are same in the text file, then LOGIN successful
	if (login_check(ic_num, pw, ic_name))
		cout << "\n\t\tLOGIN SUCCESSFUL!\n" << endl;

	// if the information of the user are not same in the text file, then LOGIN fail and go back to the main function
	else
	{
		cout << "\n\t\tLOGIN FAILED!\n" << endl;
		main();
	}
	return ic_num;
}

//check is the information of the user are same in the text file
bool login_check(string IC, string pwd, string name)
{
	// Open the input file for reading.
	ifstream infile("users.txt");

	// Loop through each line in the file.
	string line;
	while (getline(infile, line))
	{
		// Use a stringstream to split the line into fields.
		stringstream ss(line);
		string field;

		// Extract the IC and password fields from the line.
		getline(ss, field, ',');
		string ic_name = field;

		getline(ss, field, ',');
		string ic = field;

		getline(ss, field, ',');
		string pw = field;


		// Check if the IC and password match the input.
		if (ic_name == name && ic == IC && pw == pwd)
		{
			// If there is a match, close the input file and return true.
			infile.close();
			return true;
		}
	}

	// If no match was found, close the input file and return false.
	infile.close();
	return false;
}

//let user to register a new account
void regst()
{
	cout << "\t\t    ACCOUNT REGISTRATION" << endl;
	cout << "==================================================================="  << endl;

	//to get users' information
	string ic_name;
	ic_name = full_name();
	cout << "\n";

	string ic_num, gender;
	int age;
	ic_num = getIC();
	age = getAge(ic_num);
	gender = getGender(ic_num);
	cout << "\n";

	string pw;
	pw = password();
	refresh_pg();

	cout << "\t\t\tUSER DETAILS " << endl;
	cout << "==================================================================="  << endl;

	string stt;
	stt = state();
	refresh_pg();

	string phone;
	phone = phone_num();
	cout << "\n";

	string email;
	email = email_addr();
	refresh_pg();

	string vac_status;
	vac_status = vaccination_status();
	refresh_pg();

	string covid_status;
	covid_status = covid_s(ic_num);
	refresh_pg();

	// Open the output file for writing.
	ofstream outfile("users.txt", ios::app);

	// Write the user information to the output file.
	outfile << ic_name << ","
		<< ic_num << ","
		<< pw << ","
		<< age << ","
		<< gender << ","
		<< phone << ","
		<< email << ","
		<< stt << ","
		<< vac_status << ","
		<< covid_status << endl;


	// Close the output file.
	outfile.close();
	//display the information of user
	display_info(ic_num);
	this_thread::sleep_for(chrono::milliseconds(5000));

	main();
	return;
}

//full name of user as NRIC
string full_name()
{
	string full_name;
	char confirm;
	char conf;

	do
	{
		cout << "Please Enter Your Full Name(NRIC): ";
		getline(cin, full_name);

		// Convert the name to uppercase
		for (char& c : full_name)
			c = toupper(c);


		cout << "Is \"" << full_name << "\" your name? (Y/N): ";
		cin >> confirm;
		conf = toupper(confirm);

		while (conf != 'Y' && conf != 'N')
		{
			cout << "Please Enter (Y/N): ";
			cin >> confirm;
		}

		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the newline character from the input stream

	} while (conf != 'Y');

	return full_name;
}

//to get IC num of users
string getIC()
{
	string user_ic;
	do
	{
		cout << "Please Enter Your IC Number without '-': ";
		cin >> user_ic;
		//validation
		if (user_ic.length() != 12) {
			cout << "INVALID IC!!!" << endl;
		}
	} while (user_ic.length() != 12);
	return user_ic;
}

//calculate the age of user using first tow digits of IC
int getAge(string user_ic)
{
	int year = stoi(user_ic.substr(0, 2));

	auto now = chrono::system_clock::now();
	auto now_c = chrono::system_clock::to_time_t(now);
	int current_year;
	tm current_time;
	localtime_s(&current_time, &now_c);
	current_year = current_time.tm_year + 1900;
	int user_year = (year < 30) ? year + 2000 : year + 1900;
	int age = current_year - user_year;
	return age;
}

//get to know the gender of user by using the last digit of IC
string getGender(string user_ic)
{
	int gender = stoi(user_ic.substr(11, 1));
	string user_gender = (gender % 2 == 0) ? "Female" : "Male";
	return user_gender;
}

//state that user stay currently
string state()
{
	//to show users all of the states in Malaysia
	int state_code;
	cout << "01 - Johor\n";
	cout << "02 - Kedah\n";
	cout << "03 - Kelantan\n";
	cout << "04 - Melaka\n";
	cout << "05 - Negeri Sembilan\n";
	cout << "06 - Pahang\n";
	cout << "07 - Perak\n";
	cout << "08 - Perlis\n";
	cout << "09 - Pulau Pinang\n";
	cout << "10 - Sabah\n";
	cout << "11 - Sarawak\n";
	cout << "12 - Selangor\n";
	cout << "13 - Terengganu\n";
	cout << "14 - Kuala Lumpur\n";
	cout << "15 - Labuan\n";
	cout << "16 - Putrajaya\n\n";

	//validation when user input the state
	do
	{
		cout << "Which state do you living now? ";
		cin >> state_code;
		if (state_code != 1 && state_code != 2 && state_code != 3 && state_code != 4 && state_code != 5 &&
			state_code != 6 && state_code != 7 && state_code != 8 && state_code != 9 && state_code != 10 &&
			state_code != 11 && state_code != 12 && state_code != 13 && state_code != 14 && state_code != 15 && state_code != 16)
			cout << "Invalid Entry! Please try again." << endl;

	} while (state_code != 1 && state_code != 2 && state_code != 3 && state_code != 4 && state_code != 5 &&
		state_code != 6 && state_code != 7 && state_code != 8 && state_code != 9 && state_code != 10 &&
		state_code != 11 && state_code != 12 && state_code != 13 && state_code != 14 && state_code != 15 && state_code != 16);

	//get the name of the state to record in text file
	string state_name;
	switch (state_code)
	{
	case 1:
		state_name = "Johor";
		break;
	case 2:
		state_name = "Kedah";
		break;
	case 3:
		state_name = "Kelantan";
		break;
	case 4:
		state_name = "Melaka";
		break;
	case 5:
		state_name = "Negeri Sembilan";
		break;
	case 6:
		state_name = "Pahang";
		break;
	case 7:
		state_name = "Perak";
		break;
	case 8:
		state_name = "Perlis";
		break;
	case 9:
		state_name = "Pulau Pinang";
		break;
	case 10:
		state_name = "Sabah";
		break;
	case 11:
		state_name = "Sarawak";
		break;
	case 12:
		state_name = "Selangor";
		break;
	case 13:
		state_name = "Terengganu";
		break;
	case 14:
		state_name = "Kuala Lumpur";
		break;
	case 15:
		state_name = "Labuan";
		break;
	default:
		state_name = "Putrajaya";
		break;
	}

	cout << "You are living in " << state_name << endl;

	return state_name;
}

//password to access users' account
string password()
{
	string user_pwd, confirm_pwd;
	bool confirmed = false;

	do
	{
		cout << "\nPlease Enter Your Password (6-12 characters and digits): ";
		cin >> user_pwd;
		int len = user_pwd.length();

		if (len > 12 || len < 6)
		{
			cout << "Password invalid!!!\n";
			cout << "Reminder: Password must be in 6-12 characters or digits\n\n";
			continue;
		}

		cout << "Please retype your password to confirm: ";
		cin >> confirm_pwd;

		if (confirm_pwd == user_pwd)
		{
			cout << "Password Confirmed" << endl;
			confirmed = true;
			break;
		}

		else if (confirm_pwd != user_pwd)
		{
			cout << "Password Confirmation Failed, Please Re-type Your Password\n\n";
			continue;
		}

	} while (!confirmed);

	return user_pwd;
}

//phone number of user
string phone_num()
{
	string ph_num;
	int num;
	do
	{
		cout << "Please Enter Your Phone Number (without '-'): ";
		cin >> ph_num;
		num = ph_num.length();

		//validation to check the phone number
		if (num < 10 || num > 11)
			cout << "Invalid number!" << endl;

	} while (num < 10 || num > 11);

	return ph_num;
}

//email address of user
string email_addr()
{
	string email;

	do
	{
		cout << "Enter your email address here: ";
		cin >> email;
		if (is_valid_email(email))
			cout << "Invalid email! Please try again." << endl;
	} while (is_valid_email(email));

	return email;
}

//validation to check the email
bool is_valid_email(string email)
{
	bool valid = false;
	int at = -1;
	int dot = -1;
	int num = email.length();

	for (int i = 0;i < num;i++)
	{
		if (email[i] == '@')
			at = i;
		else if (email[i] == '.')
			dot = i;
	}

	if (at == -1 || dot == -1 || at > dot)
		valid = true;

	return valid;
}

//vaccination status
string vaccination_status()
{
	char ans;
	char Ans;
	string v_status;
	cout << "\nVaccination Status" << endl;
	cout << "------------------" << endl;
	cout << "(A) Unvaccinated \n(B) Vaccinated - 1st Dose \n(C) Vaccinated - 2nd Dose \n(D) Booseter Dose" << endl;

	//check the input of user
	do
	{
		cout << "Enter your Vaccination Status (A/B/C/D)";
		cin >> ans;
		Ans = toupper(ans);
		if (is_valid_vs(Ans))
			cout << "Invalid Entry! Please try again.";
	} while (is_valid_vs(Ans));

	//
	switch (Ans)
	{
	case 'A':
		v_status = "Unvaccinated";
		break;
	case 'B':
		v_status = "Partially Vaccinated (1st Dose)";
		break;
	case 'C':
		v_status = "Fully Vaccinated (2 Doses)";
		break;
	default:
		v_status = "Fully Vaccinated (2 Doses + Booster shot)";
		break;
	}

	cout << "Your vaccination status = " << v_status << endl;

	return v_status;
}

//validation of vaccination status
bool is_valid_vs(char ans)
{
	bool valid = true;
	if (ans == 'A' || ans == 'B' || ans == 'C' || ans == 'D')
		valid = false;
	return valid;
}

//update COVID-19 status
string covid_s(string ic_num)
{
	char cs;
	char CS;
	string covid_status;
	cout << "\nCOVID-19 Status" << endl;
	cout << "------------------" << endl;
	cout << "Confrimed Case = A person who has tested positive for COVID-19.\n";
	cout << "Suspected Case = A person at risk of being infected with COVID-19.\n";
	cout << "Close Contact = A person who has been exposed to someone infected with COVID-19.\n";
	cout << "Casual Contact = A person who may have been exposed to someone infected with COVID-19.\n";
	cout << "Low Risk = A person with a low risk of COVID-19 infection.\n";
	cout << "(A) Confrimed Case \n(B) Suspected Case \n(C) Close Contac \n(D) Casual Contact \n(E) Low Risk\n" << endl;


	do
	{
		cout << "Enter your COVID-19 Status (A/B/C/D/E)";
		cin >> cs;
		CS = toupper(cs);
		if (is_valid_cs(CS))
			cout << "Invalid Entry! Please try again.";
	} while (is_valid_cs(CS));

	switch (CS)
	{
	case 'A':
		covid_status = "Confirmed Case";
		break;
	case 'B':
		covid_status = "Suspected Case";
		break;
	case 'C':
		covid_status = "Close Contact";
		break;
	case 'D':
		covid_status = "Casual Contact";
		break;
	default:
		covid_status = "Low Risk";
		break;
	}
	cout << "Your current Covid status is " << covid_status << "\n";

	if (CS == 'A' || CS == 'B')
		symptom(ic_num);

	return covid_status;
}

//validation of COVID-19 status
bool is_valid_cs(char cs)
{
	bool valid = true;
	if (cs == 'A' || cs == 'a' || cs == 'B' || cs == 'b' || cs == 'C' || cs == 'c' || cs == 'D' || cs == 'd' || cs == 'E' || cs == 'e')
		valid = false;
	return valid;
}

//symptoms when the users are "Confirmed Case" or "Suspected Case"
void symptom(string ic_num)
{
	char ans;
	string symptoms[TotalSymptoms];

	//list of symptoms
	symptoms[0] = "Fever or chills";
	symptoms[1] = "Cough";
	symptoms[2] = "Shortness of breath or difficulty breathing";
	symptoms[3] = "Fatigue";
	symptoms[4] = "Muscle or body aches";
	symptoms[5] = "Headache";
	symptoms[6] = "New loss of taste or smell";
	symptoms[7] = "Sore throat";
	symptoms[8] = "Congestion or runny nose";
	symptoms[9] = "Nausea or vomiting";
	symptoms[10] = "Diarrhea";
	cout << "Please enter (Y/y) if u have the symptoms and (N/n) if no" << endl;

	ofstream outfile("output.txt", ios::app); // open file in append mode

	// check if the file was opened successfully
	if (!outfile) {
		cerr << "Error opening file" << endl;
		return;
	}

	// write data to the file
	outfile << ic_num;
	for (int i = 0;i < TotalSymptoms;i++)
	{
		cout << i + 1 << ". " << symptoms[i] << " : ";
		cin >> ans;
		toupper(ans);
		while (ans != 'y' && ans != 'Y' && ans != 'n' && ans != 'N')
		{
			cout << "Please choose y/n: ";
			cin >> ans;
		}

		outfile << "," << ans;
	}
	outfile << endl;
	outfile.close(); // close the file

}

//display all the information about the user
void display_info(string ic)
{
	// Open the input file for reading.
	ifstream infile("users.txt");

	// Loop through each line in the file.
	string line;
	while (getline(infile, line))
	{
		// Use a stringstream to split the line into fields.
		stringstream ss(line);
		string field;

		// Extract the every information fields from the line.
		getline(ss, field, ',');
		string ic_name = field;

		getline(ss, field, ',');
		string ic_num = field;

		getline(ss, field, ',');
		string pw = field;

		getline(ss, field, ',');
		string age = field;

		getline(ss, field, ',');
		string gender = field;

		getline(ss, field, ',');
		string pnum = field;

		getline(ss, field, ',');
		string email = field;

		getline(ss, field, ',');
		string state = field;

		getline(ss, field, ',');
		string vaccine = field;

		getline(ss, field, ',');
		string covid = field;

		// Check if the IC and password match the input.
		if (ic == ic_num)
		{
			cout << "Name           = " << ic_name << endl;
			cout << "IC number      = " << ic_num << endl;
			cout << "Age            = " << age << endl;
			cout << "Gender         = " << gender << endl;
			cout << "Phone Number   = " << pnum << endl;
			cout << "Email          = " << email << endl;
			cout << "State Living   = " << state << endl;
			cout << "Vaccine status = " << vaccine << endl;
			cout << "Covid status   = " << covid << endl;
			cout << endl;
		}

	}

	// If no match was found, close the input file and return false.
	infile.close();

}

//display the symptoms of users
void display_symptom(string ic)
{
	// Open the input file for reading.
	string filename = ic + " symptoms.txt";
	ifstream infile(filename);

	// Loop through each line in the file.
	string line;
	while (getline(infile, line))
	{
		// Use a stringstream to split the line into fields.
		stringstream ss(line);
		string field;

		string symptoms[TotalSymptoms];
		symptoms[0] = "Fever or chills";//15
		symptoms[1] = "Cough";//5
		symptoms[2] = "Shortness of breath or difficulty breathing";//42
		symptoms[3] = "Fatigue";//7
		symptoms[4] = "Muscle or body aches";//21
		symptoms[5] = "Headache";//8
		symptoms[6] = "New loss of taste or smell";//26
		symptoms[7] = "Sore throat";//11
		symptoms[8] = "Congestion or runny nose";//23
		symptoms[9] = "Nausea or vamiting";//18
		symptoms[10] = "Diarrhea";//8

		// Extract the IC and password fields from the line.
		getline(ss, field, ',');
		string ic_num = field;

		getline(ss, field, ',');
		string symp1 = field;

		getline(ss, field, ',');
		string symp2 = field;

		getline(ss, field, ',');
		string symp3 = field;

		getline(ss, field, ',');
		string symp4 = field;

		getline(ss, field, ',');
		string symp5 = field;

		getline(ss, field, ',');
		string symp6 = field;

		getline(ss, field, ',');
		string symp7 = field;

		getline(ss, field, ',');
		string symp8 = field;

		getline(ss, field, ',');
		string symp9 = field;

		getline(ss, field, ',');
		string symp10 = field;

		getline(ss, field, ',');
		string symp11 = field;

		// Check if the IC and password match the input.
		if (ic == ic_num)
		{
			cout << "Symptoms: \n";
			cout << symptoms[0] << setw(31) << " - " << symp1 << endl;
			cout << symptoms[1] << setw(41) << " - " << symp2 << endl;
			cout << symptoms[2] << setw(0) << " - " << symp3 << endl;
			cout << symptoms[3] << setw(39) << " - " << symp4 << endl;
			cout << symptoms[4] << setw(26) << " - " << symp5 << endl;
			cout << symptoms[5] << setw(38) << " - " << symp6 << endl;
			cout << symptoms[6] << setw(20) << " - " << symp7 << endl;
			cout << symptoms[7] << setw(35) << " - " << symp8 << endl;
			cout << symptoms[8] << setw(22) << " - " << symp9 << endl;
			cout << symptoms[9] << setw(28) << " - " << symp10 << endl;
			cout << symptoms[10] << setw(38) << " - " << symp11 << endl;
		}
	}

	// If no match was found, close the input file and return false.
	infile.close();
}

//update users' current covid status
void updatecvd_txtfile(string ic)
{
    //open the file for reading and writing
    fstream file("users.txt", ios::in | ios::out);

    // Loop through each line in the file.
    string line;
    while (getline(file, line))
    {
        // Use a stringstream to split the line into fields.
        stringstream ss(line);
        string field;

        getline(ss, field, ',');
        string ic_name = field;

        getline(ss, field, ',');
        string ic_num = field;

        getline(ss, field, ',');
        string pw = field;

        getline(ss, field, ',');
        string age = field;

        getline(ss, field, ',');
        string gender = field;

        getline(ss, field, ',');
        string pnum = field;

        getline(ss, field, ',');
        string email = field;

        getline(ss, field, ',');
        string state = field;

        getline(ss, field, ',');
        string vcc_stt = field;

        string covid_stt = covid_s(ic_num);
        getline(ss, field, ',');
        covid_stt = field;

        // Move the file pointer to the beginning of the line that needs to be updated
        file.seekp(static_cast<int>(file.tellg()) - static_cast<int>(line.length()) - 1);

        // Write the updated data back to the file
        file << ic_name << ","
            << ic_num << ","
            << pw << ","
            << age << ","
            << gender << ","
            << pnum << ","
            << email << ","
            << state << ","
            << vcc_stt << ","
            << covid_stt << endl;

        cout << "Covid status updated successfully" << endl;
    }

    // Close the file
    file.close();

}


//update users' current vaccine status
void updatevcc_txtfile(string ic)
{
    //open the file for reading and writing
    fstream file("users.txt", ios::in | ios::out);

    // Loop through each line in the file.
    string line;
    while (getline(file, line))
    {
        // Use a stringstream to split the line into fields.
        stringstream ss(line);
        string field;

        getline(ss, field, ',');
        string ic_name = field;

        getline(ss, field, ',');
        string ic_num = field;

        getline(ss, field, ',');
        string pw = field;

        getline(ss, field, ',');
        string age = field;

        getline(ss, field, ',');
        string gender = field;

        getline(ss, field, ',');
        string pnum = field;

        getline(ss, field, ',');
        string email = field;

        getline(ss, field, ',');
        string state = field;

        getline(ss, field, ',');
        string vcc_stt = field;

        getline(ss, field, ',');
        string covid_stt = field;

        // Check if this is the correct user based on their IC number.
        if (ic_num == ic)
        {
            // Update the vaccination status.
            string new_vcc_stt = vaccination_status();
            vcc_stt = new_vcc_stt;

            // Move the file pointer to the beginning of the line that needs to be updated
            file.seekp(static_cast<int>(file.tellg()) - static_cast<int>(line.length()) - 1);

            // Write the updated data back to the file
            file << ic_name << ","
                << ic_num << ","
                << pw << ","
                << age << ","
                << gender << ","
                << pnum << ","
                << email << ","
                << state << ","
                << vcc_stt << ","
                << covid_stt << endl;

            cout << "Vaccination status updated successfully" << endl;
            break;
        }
    }

    // Close the file
    file.close();
}

//combination of both updated current covid and vaccine status
void update_data(string ic)
{
	refresh_pg();

	int step = 1;
	if (step == 1)
	{
		char update_vaccine;
		do
		{
			cout << "Do you want to update your vaccine status? (Y/N): ";
			cin >> update_vaccine;

			if (update_vaccine != 'Y' && update_vaccine != 'y' && update_vaccine != 'N' && update_vaccine != 'n')
				cout << "Please enter (Y/N): ";

		} while (update_vaccine != 'Y' && update_vaccine != 'y' && update_vaccine != 'N' && update_vaccine != 'n');

		if (update_vaccine == 'Y' || update_vaccine == 'y')
		{
			updatevcc_txtfile(ic);
		}
		step += 1;
	}

	refresh_pg();

	if (step == 2)
	{
		char update_covid;
		do
		{
			cout << "Do you want to update your covid status? (Y/N): ";
			cin >> update_covid;
			if (update_covid != 'Y' && update_covid != 'y' && update_covid != 'N' && update_covid != 'n')
				cout << "Please enter (Y/N): ";
		} while (update_covid != 'Y' && update_covid != 'y' && update_covid != 'N' && update_covid != 'n');

		if (update_covid == 'Y' || update_covid == 'y')
		{
			updatecvd_txtfile(ic);
		}
	}

	refresh_pg();
	display_info(ic);
}

void dashboard()
{
	cout << "\t\t\t  DASHBOARD " << endl;
	cout << "===================================================================" << endl;
	cout << "1. Booking for Vaccination" << endl;
	cout << "2. Covid-19 Frequently Asked Questions" << endl;
	int num;
	cout << "What is your next step?" << endl;
	cout << "Please enter the number of your choice:";
	cin >> num;

	refresh_pg();
	switch (num)
	{
		case 1:
			//book appointment
			break;
		case 2:
			faq();
			break;
	}

}

void faq()
{
	int question;
	string answer;

	cout << "\t\tCovid-19 Frequently Asked Questions" << endl;
	cout << "==================================================================="<< endl;


	// Display the list of questions
	printLine(68, '*', ' ');
	cout << endl << "Please select a question to view the answer:" << endl;
	printLine(68, '*', ' ');
	cout << "|    1. What is Covid-19?                                          |" << endl;
	cout << "|    2. What are the symptoms of Covid-19?                         |" << endl;
	cout << "|    3. How is Covid-19 spread?                                    |" << endl;
	cout << "|    4. What can I do to protect myself and others from Covid-19?  |" << endl;
	cout << "|    5. How is Covid-19 treated?                                   |" << endl;
	cout << "|    6. How effective are the Covid-19 vaccines?                   |" << endl;
	cout << "|    7. What are the side effects of the Covid-19 vaccines?        |" << endl;
	cout << "|    8. What should I do if I think I have COVID-19?               |" << endl;
	cout << "|    9. Quit FAQ                                                   |" << endl;
	printLine(68, '*', ' ');

	do
	{
		// Read the user's input
		cout << "Please enter your choice (1-9): ";
		cin >> question;

		// Display the answer based on the user's input
		switch (question) {
		case 1:
			answer = "Covid-19 is a highly contagious respiratory illness caused by the SARS-CoV-2 virus.\nIt was first identified in Wuhan, China in December 2019 and has since spread globally, leading to a pandemic.";
			break;
		case 2:
			answer = "The symptoms of Covid-19 can range from mild to severe and\ninclude fever, cough, fatigue, body aches, loss of taste or smell, sore throat, and shortness of breath.\nSome people may also experience headaches, chills, or gastrointestinal symptoms.";
			break;
		case 3:
			answer = "Covid-19 is primarily spread through respiratory droplets when an infected person talks, coughs, or sneezes.\nIt can also be spread by touching a surface contaminated with the virus and then touching your face, mouth, or nose.";
			break;
		case 4:
			answer = "You can protect yourself and others from Covid-19 by getting vaccinated, wearing a mask,\npracticing physical distancing, washing your hands regularly, and staying home if you feel sick.";
			break;
		case 5:
			answer = "There is currently no specific treatment for Covid-19, but some people may require hospitalization and supportive care.\nAntiviral drugs and other medications may be used to help manage symptoms and complications.";
			break;
		case 6:
			answer = "The Covid-19 vaccines have been shown to be highly effective at preventing severe illness, hospitalization, and death from Covid-19.\nThey also help reduce the spread of the virus in the community.";
			break;
		case 7:
			answer = "The most common side effects of the Covid-19 vaccines include pain and swelling at the injection site, fever, fatigue, headache, and muscle aches.\nThese side effects are usually mild and go away within a few days.";
			break;
		case 8:
			answer = "If you think you have COVID-19, you should stay home and self-isolate, contact your healthcare provider, and get tested for the virus.";
			break;
		case 9:
			printLine(68, '*', ' ');
			cout << "Thank you for using the Covid-19 FAQ system" << endl;
			//back to dashboard
			dashboard();
			break;
		default:
			answer = "Invalid choice. Please try again.";
			break;
		}

		// Display the answer to the selected question
		cout << "|  " << answer;
		for (int i = answer.length(); i < 47; i++)
			cout << " ";
		cout << "|" << endl;
		cout << "\n";
		this_thread::sleep_for(chrono::milliseconds(5000));
	} while (question != 9);

}

//some designs of the system
void display_header()
{
	cout << "===================================================================";
	cout << "\n \t\t\t  CORONA WATCH";
	cout << "\n===================================================================" << endl;
}

void refresh_pg()
{
	cout << endl;
	system("PAUSE");
	system("CLS");
	display_header();
}

void printLine(int width, char borderChar, char fillChar)
{
	cout << borderChar;
	for (int i = 0; i < width - 2; i++) {
		cout << fillChar;
	}
	cout << borderChar << endl;
}
