#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

////////////////////////////////////////////////////////////////

// Patient Management System

const string USER_FILE = "user.txt";
const string APPOINTMENT_FILE = "appointments.txt";
const string MEDICAL_HISTORY_FILE = "medical_history.txt";
const string REPORTS_FILE = "patient_reports.txt";
const string PATIENT_FILE = "patients.txt";
void viewMedicalHistory();
void addMedicalHistory();
void generateReports();
struct Appointment {
    string patientName;
    string doctorName;
    string date;
    string time;
};

struct Patient {
    string name;
    int age;
    string disease;
    string condition;
};

struct MedicalHistory {
    string patientName;
    string disease;
    string condition;
    string treatment;
};

struct PatientReport {
    string patientName;
    string reportType;
    string reportContent;
};






bool signupUser(const string& username, const string& password) {
    ofstream userFile(USER_FILE, ios::app);
    if (!userFile.is_open()) {
        cout << "Error opening user file for signup.\n";
        return false;
    }

    userFile << username << " " << password << endl;
    cout << "Signup successful\n";

    return true;
}

void registerPatient() {
    system("cls");
    string patientName, patientAge, patientDisease, patientCondition;
    cout << "Enter Patient Name: ";
    cin >> patientName;
    cout << "Enter Patient Age: ";
    cin >> patientAge;
    cout << "Enter Patient Disease: ";
    cin >> patientDisease;
    cout << "Enter Patient Examined Condition: ";
    cin >> patientCondition;

    ofstream patientFile("patients.txt", ios::app);
    if (patientFile.is_open()) {
        patientFile << "Patient Name: " << patientName << endl;
        patientFile << "Patient Age: " << patientAge << endl;
        patientFile << "Patient Disease: " << patientDisease << endl;
        patientFile << "Patient Examined Condition: " << patientCondition << endl << endl;

        cout << "Patient registered successfully\n";
    }
    else {
        cout << "Error opening patient file.\n";
    }
}

void scheduleAppointment() {
    system("cls");
    cout << "---------------- SCHEDULE APPOINTMENT ----------------\n\n";

    Appointment newAppointment;

    cout << "Enter Patient Name: ";
    cin.ignore();
    getline(cin, newAppointment.patientName);

    cout << "Enter Doctor Name: ";
    getline(cin, newAppointment.doctorName);

    cout << "Enter Appointment Date (YYYY-MM-DD): ";
    cin >> newAppointment.date;

    cout << "Enter Appointment Time: ";
    cin >> newAppointment.time;

    // Save the appointment to a file
    ofstream appointmentFile(APPOINTMENT_FILE, ios::app);
    if (!appointmentFile.is_open()) {
        cout << "Error opening appointment file.\n";
        return;
    }

    appointmentFile << newAppointment.patientName << " "
        << newAppointment.doctorName << " "
        << newAppointment.date << " "
        << newAppointment.time << endl;

    appointmentFile.close();

    cout << "\nAppointment scheduled successfully!\n";
}

void viewAppointments() {
    system("cls");
    cout << "---------------- VIEW APPOINTMENTS ----------------\n\n";

    ifstream appointmentFile(APPOINTMENT_FILE);
    if (!appointmentFile.is_open()) {
        cout << "No appointments found.\n";
        return;
    }

    vector<Appointment> appointments;
    Appointment tempAppointment;

    while (appointmentFile >> tempAppointment.patientName
        >> tempAppointment.doctorName
        >> tempAppointment.date
        >> tempAppointment.time) {
        appointments.push_back(tempAppointment);
    }

    appointmentFile.close();

    if (appointments.empty()) {
        cout << "No appointments found.\n";
    }
    else {
        cout << "Patient Name\tDoctor Name\tDate\t\tTime\n";
        for (const auto& appointment : appointments) {
            cout << appointment.patientName << "\t\t"
                << appointment.doctorName << "\t\t"
                << appointment.date << "\t"
                << appointment.time << endl;
        }
    }
}

void viewPatients() {
    system("cls");
    cout << "---------------- VIEW PATIENT INFORMATION ----------------\n\n";

    ifstream patientFile(PATIENT_FILE);
    if (!patientFile.is_open()) {
        cout << "No patient information found.\n";
        return;
    }

    vector<Patient> patients;
    Patient tempPatient;

    while (patientFile >> tempPatient.name >> tempPatient.age
        >> tempPatient.disease >> tempPatient.condition) {
        patients.push_back(tempPatient);
    }

    patientFile.close();

    if (patients.empty()) {
        cout << "No patient information found.\n";
    }
    else {
        cout << "Name\t\tAge\tDisease\t\tCondition\n";
        for (const auto& patient : patients) {
            cout << patient.name << "\t\t" << patient.age << "\t"
                << patient.disease << "\t\t" << patient.condition << endl;
        }
    }
}

void editPatient() {
    system("cls");
    cout << "---------------- EDIT PATIENT INFORMATION ----------------\n\n";

    string targetName;
    cout << "Enter the name of the patient to edit: ";
    cin.ignore();
    getline(cin, targetName);

    ifstream patientFile(PATIENT_FILE);
    if (!patientFile.is_open()) {
        cout << "Error opening patient file.\n";
        return;
    }

    vector<Patient> patients;
    Patient tempPatient;

    while (patientFile >> tempPatient.name >> tempPatient.age
        >> tempPatient.disease >> tempPatient.condition) {
        patients.push_back(tempPatient);
    }

    patientFile.close();

    bool found = false;
    for (auto& patient : patients) {
        if (patient.name == targetName) {
            found = true;

            cout << "Enter new age: ";
            cin >> patient.age;

            cout << "Enter new disease: ";
            cin.ignore();
            getline(cin, patient.disease);

            cout << "Enter new condition: ";
            getline(cin, patient.condition);

            break;
        }
    }

    if (!found) {
        cout << "Patient not found.\n";
        return;
    }

    // Update the patient file
    ofstream updatedPatientFile(PATIENT_FILE);
    if (!updatedPatientFile.is_open()) {
        cout << "Error opening patient file for update.\n";
        return;
    }

    for (const auto& patient : patients) {
        updatedPatientFile << patient.name << " "
            << patient.age << " "
            << patient.disease << " "
            << patient.condition << endl;
    }

    updatedPatientFile.close();

    cout << "Patient information updated successfully!\n";
}

void userLoggedInMenu() {
    int choice;
    do {
        // system("cls");
        cout << "---------------- Main Menu ----------------\n";
        cout << "1. Register Patient\n";
        cout << "2. Schedule Appointment\n";
        cout << "3. View Appointments\n";
        cout << "4. View Patient Information\n";
        cout << "5. Edit Patient Information\n";
        cout << "6. View Medical History\n";
        cout << "7. Add Medical History\n";
        cout << "8. Generate Reports\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            registerPatient();
            break;
        case 2:
            scheduleAppointment();
            break;
        case 3:
            viewAppointments();
            break;
        case 4:
            viewPatients();
            break;
        case 5:
            editPatient();
            break;
        case 6:
            viewMedicalHistory();
            break;
        case 7:
            addMedicalHistory();
            break;
        case 8:
            generateReports();
            break;
        case 9:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 9);
}

void viewMedicalHistory() {
    system("cls");
    cout << "--------------- VIEW MEDICAL HISTORY ---------------\n\n";

    ifstream historyFile(MEDICAL_HISTORY_FILE);
    if (!historyFile.is_open()) {
        cout << "No medical history found.\n";
        return;
    }

    vector<MedicalHistory> medicalHistory;
    MedicalHistory tempHistory;

    while (historyFile >> tempHistory.patientName
        >> tempHistory.disease
        >> tempHistory.condition
        >> tempHistory.treatment) {
        medicalHistory.push_back(tempHistory);
    }

    historyFile.close();

    if (medicalHistory.empty()) {
        cout << "No medical history found.\n";
    }
    else {
        cout << "Patient Name\tDisease\t\tCondition\tTreatment\n";
        for (const auto& history : medicalHistory) {
            cout << history.patientName << "\t\t" << history.disease << "\t\t"
                << history.condition << "\t\t" << history.treatment << endl;
        }
    }
}

void addMedicalHistory() {
    system("cls");
    cout << "--------------- ADD MEDICAL HISTORY ---------------\n\n";

    MedicalHistory newHistory;
    cout << "Enter patient name: ";
    cin.ignore();
    getline(cin, newHistory.patientName);

    cout << "Enter disease: ";
    getline(cin, newHistory.disease);

    cout << "Enter condition: ";
    getline(cin, newHistory.condition);

    cout << "Enter treatment: ";
    getline(cin, newHistory.treatment);

    ofstream historyFile(MEDICAL_HISTORY_FILE, ios::app);
    if (!historyFile.is_open()) {
        cout << "Error opening medical history file for update.\n";
        return;
    }

    historyFile << newHistory.patientName << " "
        << newHistory.disease << " "
        << newHistory.condition << " "
        << newHistory.treatment << endl;

    historyFile.close();

    cout << "Medical history added successfully!\n";
}

void generateReports() {
    system("cls");
    cout << "--------------- GENERATE REPORTS ---------------\n\n";

    PatientReport newReport;
    cout << "Enter patient name: ";
    cin.ignore();
    getline(cin, newReport.patientName);

    cout << "Enter report type: ";
    getline(cin, newReport.reportType);

    cout << "Enter report content: ";
    getline(cin, newReport.reportContent);

    ofstream reportsFile(REPORTS_FILE, ios::app);
    if (!reportsFile.is_open()) {
        cout << "Error opening reports file for update.\n";
        return;
    }

    reportsFile << newReport.patientName << " "
        << newReport.reportType << " "
        << newReport.reportContent << endl;

    reportsFile.close();

    cout << "Report generated successfully!\n";
}

bool loginUser(const string& username, const string& password) {
    ifstream userFile(USER_FILE);
    string storedUsername, storedPassword;

    while (userFile >> storedUsername >> storedPassword) {
        if (storedUsername == username && storedPassword == password) {
            userFile.close();
            return true;
        }
    }

    userFile.close();
    return false;
}

void login() {
    string username, password;
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;

    if (loginUser(username, password)) {
        cout << "Login successful!\n";
        userLoggedInMenu();
    }
    else {
        cout << "Login failed. Invalid credentials.\n";
    }
}
void signup() {
    string username, password;
    cout << "Enter a new username: ";
    cin >> username;

    // You can add password complexity checks here if needed
    cout << "Enter a new password: ";
    cin >> password;

    if (signupUser(username, password)) {
        cout << "Signup successful! You can now login.\n";
    }
    else {
        cout << "Signup failed. Please try again with a different username.\n";
    }
}

int patmain() {
    cout << "**********************************************\n";
    cout << "*   Welcome to the Hospital Management System   *\n";
    cout << "**********************************************\n\n";

    int pick;

    do {
        cout << "Main Menu:\n";
        cout << "1. LogIn\n";
        cout << "2. SignUP\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> pick;

        switch (pick) {
        case 1:
            login();
            break;

        case 2:
            signup();
            break;

        case 3:
            cout << "\nExiting...\n";
            break;

        default:
            cout << "\nInvalid choice. Try again.\n";
        }
    } while (pick != 3);

    return 0;
}
//////////////////////////////////////////////////////////////////////////////////

//Doctor Management System//
 
// Creating Function for Login menu...

bool Login() {
	string usrnme, pswrd, un, pw;
	cout << "Enter Username: ";
	cin >> usrnme;
	cout << "Enter Password: ";
	cin >> pswrd;
	ifstream read(usrnme + ".txt");
	getline(read, un);
	getline(read, pw);
	if (usrnme == un && pswrd == pw)
		return true;
	else return false;
}

// Creating Function for MENU Display...

int menu() {
	system("cls");
	cout << "=====================================================" << endl;
	cout << "-------------------MAIN MENU-------------------------" << endl;
	cout << "=====================================================" << endl;
	cout << "1.     Press 1 for Patient's Description. " << endl;
	cout << "2.     Press 2 for Online Appointment. " << endl;
	cout << "3.     Press 3 for Checking Scheduled Appointments." << endl;
	cout << "4.     Press 4 for Checking Available doctors." << endl;
	cout << "5.     Press 5 for Editing Doctor Profile. " << endl;
	cout << "6.     Press 6 for Checking Doctor Profile. " << endl;
	cout << "7.     Press 7 to Exit." << endl;
	int k;
	cin >> k;
	return k;
}
int docmain() {
	char a;

	//Using file handling to make some appointment reports...
	ofstream file1;
	file1.open("Patient1.txt");
	file1 << "Patient Name: Ahmad" << endl;
	file1 << "Patient Age: 32" << endl;
	file1 << "Appointment Day: Monday" << endl;
	file1 << "Appointment Time: 06:30pm" << endl;
	file1.close();

	ofstream file2;
	file2.open("Patient2.txt");
	file2 << "Patient Name: Abdullah" << endl;
	file2 << "Patient Age: 23" << endl;
	file2 << "Appointment Day: Wednesday" << endl;
	file2 << "Appointment Time: 07:00pm" << endl;
	file2.close();

	ofstream file3;
	file3.open("Patient3.txt");
	file3 << "Patient Name: Asim" << endl;
	file3 << "Patient Age: 40" << endl;
	file3 << "Appointment Day: Monday" << endl;
	file3 << "Appointment Time: 08:00pm" << endl;
	file3.close();

	ofstream file4;
	file4.open("Patient4.txt");
	file4 << "Patient Name: Muneer" << endl;
	file4 << "Patient Age: 35" << endl;
	file4 << "Appointment Day: Wednesday" << endl;
	file4 << "Appointment Time: 06:00pm" << endl;
	file4.close();

	ofstream file5;
	file5.open("Patient5.txt");
	file5 << "Patient Name: Zohaib" << endl;
	file5 << "Patient Age: 45" << endl;
	file5 << "Appointment Day: Friday" << endl;
	file5 << "Appointment Time: 08:00pm" << endl;
	file5.close();

	// File Handling to save available doctors' information....

	ofstream filedoc;
	filedoc.open("DoctorsAvailable.txt");
	filedoc << "=============================================" << endl;
	filedoc << "        < Three Doctors Available >          " << endl;
	filedoc << "  [Information and Timing are given below:]  " << endl;
	filedoc << "---------------------------------------------" << endl << endl;
	filedoc << "     Dr. Rana (Skin specialist)              " << endl;
	filedoc << "            [Timing]                         " << endl;
	filedoc << "Monday To Friday          09AM to 05PM" << endl;
	filedoc << "Saturday                  09AM to 01PM" << endl;
	filedoc << "Sunday                           OFF" << endl;
	filedoc << "---------------------------------------------" << endl;
	filedoc << "     Dr. Waqas (Child Specialist)            " << endl;
	filedoc << "            [Timing]                         " << endl;
	filedoc << "Monday to Friday          02PM to 10PM" << endl;
	filedoc << "Saturday                  08AM to 01PM" << endl;
	filedoc << "Sunday                    12PM to 09PM" << endl;
	filedoc << "---------------------------------------------" << endl;
	filedoc << "     Dr. Ahmad (General Surgeon)             " << endl;
	filedoc << "Monday to Friday          08PM to 05PM" << endl;
	filedoc << "Saturday                  10AM to 01PM" << endl;
	filedoc << "Sunday                             OFF" << endl;
	filedoc.close();

	int choice=0;
	string usrnme, pswrd;
	cout << "|----------WELCOME TO HOSPITAL MANAGEMENT SYSTEM----------|" << endl;
	cout << "===========================================================" << endl << endl;
	cout << "Doctor's Login Registration: " << endl;
	cout << "Press 1 to SignUp:" << endl << "Press 2 to Login : " << endl << "Press 3 to Exit." << endl;
	while (choice != 3) {
		cin >> choice;

		// SignUp for Doctor...

		if (choice == 1) {
			cout << "Select a username: ";
			cin >> usrnme;
			cout << "Select a password: ";
			cin >> pswrd;
			ofstream file;
			file.open(usrnme + ".txt");
			file << usrnme << endl << pswrd;
			file.close();
			docmain();
		}

		// Login for Doctor...

		else if (choice == 2) {
			bool status = Login();
			if (!status) {
				cout << "INCORRECT LOGIN..." << endl;
				return 0;
			}
			else {
				string usrnme, name, ptname, disease, day, condition;
				int menu_num, number = 0, num, age, ptage, time;
				cout << "Enter Name: " << endl; cin >> usrnme;
				cout << "Login Completed..." << endl;
				cout << "Press any key and then press Enter to Continue..." << endl;
				cin >> a;
				system("cls");
				cout << "Welcome Dr. " << usrnme << endl;
				cout << "Press 1 for Main Menu and 2 to exit." << endl;
				cin >> menu_num;
				if (menu_num == 1) {
					while (number != 7) {
						number = menu();
						// For Writing Patient's Description....

						if (number == 1) {
							system("cls");
							cout << "-----------------PATIENT'S DESCRIPTION MENU--------------" << endl;
							cout << "Press 1 for Ear Treatment." << endl;
							cout << "Press 2 for Nose Treatment. " << endl;
							cout << "Press 3 for Throat Treatment. " << endl;
							cout << "Press 4 for Accident Treatment. " << endl;
							cout << "Press 5 for Eyes Treatment. " << endl;
							cout << "Press 6 for Stomach disorder." << endl;
							cout << "Press 7 for Respiratory Problem. " << endl;
							cin >> num;
							system("cls");
							cout << "----------(Patient description)---------" << endl;
							cout << "Patient name: ";
							cin >> ptname;
							cout << "Patient age: ";
							cin >> ptage;
							cout << "Patient's disease: ";
							cin >> disease;
							cout << "Patient's Examined Condition (According to Doctor): " << endl;
							cin >> condition;
							if (num == 1) {
								cout << "Recommended Medicine: Ibuprofen, Amoxicillin, Augmentin..." << endl;
								cout << "First aid: Cotton, banding gauge, Neosprorin(Ointment)..." << endl << endl;
								cout << "Press any key to move to main menu...";
								cin >> a;
								menu();
							}
							else if (num == 2) {
								cout << "Recommended Medicine: " << endl;
								cout << "For nose bleeding: Afrin or Dristan(Apply on Bleeding spot and pinch for 5-10 minutes)..." << endl;
								cout << "For flue: Coldrex, Panadol..." << endl;
								cout << "Press any key and then Press Enter to move to main menu...";
								cin >> a;
								menu();
							}
							else if (num == 3) {
								cout << "Recommended Medicine: " << "Claritac, Paracetamol, Neo-Antial" << endl;
								cout << "Recommended Injection: Oxidil 500mg" << endl;
								cout << "Press any key and then Press Enter to move to main menu...";
								cin >> a;
								menu();
							}
							else if (num == 4) {
								cout << "Recommended Medicine: Panadol, Aspirin" << endl;
								cout << "Recommended Injection: Tetanus Vaccine" << endl;
								cout << "First aid Ointments: Dettol Antiseptic, Polyfax, Piodin..." << endl;
								cout << "Recommended Test: X-ray..." << endl;
								cout << "Press any key and then Press Enter to move to main menu...";
								cin >> a;
								menu();
							}
							else if (num == 5) {
								cout << "Recommended Eye Ointment: Neosporin or Polyfax" << endl;
								cout << "Press any key and then Press Enter to move to main menu...";
								cin >> a;
								menu();
							}
							else if (num == 6) {
								cout << "Recommended Medicine: Buscopan, Gravinate, Imodium..." << endl;
								cout << "Recommended Drip: Dextrose Solution Drip..." << endl;
								cout << "Press any key and then Press Enter to move to main menu...";
								cin >> a;
								menu();
							}
							else if (num == 7) {
								cout << "Recommended Medicine: Penicillin, Amoxyllin..." << endl;
								cout << "Recommended Injection: Augmentin DS..." << endl;
								cout << "Press any key and then Press Enter to move to main menu...";
								cin >> a;
								menu();
							}
							return 1;
						}
						// Online Appointment...
						else if (number == 2) {
							system("cls");
							cout << "-----------------------ONLINE APPOINTMENT MENU-----------------------" << endl;
							cout << "Appointment Days: Monday, Wednesday, Friday..." << endl << "Appointment Time: 06:00pm to 09:00pm" << endl;;
							cout << "Patient's First Name: " << endl; cin >> name;
							cout << "Patient's age: " << endl; cin >> age;
							cout << "Enter Day of Appointment: " << endl; cin >> day;
							cout << "Enter Appointment Time in pm: (6,7 or 8)" << endl; cin >> time;
							cout << "Dear " << name << ", You can visit hospital on " << day << " at " << time << " pm." << endl;
							cout << "Press any key and then Press Enter to move to main menu...";
							cin >> a;
							menu();
						}

						// Checking Scheduled Appointments...

						else if (number == 3) {
							system("cls");
							cout << "-----------------------APPOINTMENT CHECKING MENU---------------------" << endl;
							int ap_num;
							string str1, str2, str3, str4, str5;
							cout << "Press 1 for checking Appointments scheduled on Monday, 2 for checking Appointments scheduled on Wednesday, 3 for checking Appointments scheduled for Friday, 4 for checking all Scheduled appointments... " << endl;
							cin >> ap_num;
							if (ap_num == 1) {
								cout << "Monday Scheduled Appointment: " << endl << endl;
								cout << "Appointment 1: " << endl;
								ifstream file_1;
								file_1.open("Patient1.txt");
								while (!file_1.eof()) {
									str1 = file_1.get();
									cout << str1;
								}
								cout << endl;
								cout << "Appointment 2: " << endl;
								ifstream file_2;
								file_2.open("Patient3.txt");
								while (!file_2.eof()) {
									str2 = file_2.get();
									cout << str2;
								}
							}
							else if (ap_num == 2) {
								cout << "Wednesday Scheduled Appointments: " << endl << endl;
								cout << "Appointment 1: " << endl;
								ifstream file_3;
								file_3.open("Patient2.txt");
								while (!file_3.eof()) {
									str3 = file_3.get();
									cout << str3;
								}
								cout << endl;
								cout << "Appointment 2: " << endl;
								ifstream file_4;
								file_4.open("Patient4.txt");
								while (!file_4.eof()) {
									str4 = file_4.get();
									cout << str4;
								}
							}
							else if (ap_num == 3) {
								cout << "Friday Scheduled Appointment: " << endl << endl;
								cout << "Appointment 1: " << endl;
								ifstream file_5;
								file_5.open("Patient2.txt");
								while (!file_5.eof()) {
									str5 = file_5.get();
									cout << str5;
								}
							}
							else cout << "Input error: " << endl;
							cout << "Press any key and then Press Enter to move to main menu...";
							cin >> a;
							menu();
						}

						// Checking Available Doctors...

						else if (number == 4) {
							system("cls");
							string str6;
							ifstream filedoc;
							filedoc.open("DoctorsAvailable.txt");
							while (!filedoc.eof()) {
								str6 = filedoc.get();
								cout << str6;
							}
							cout << "Press any key and then Press Enter to move to main menu...";
							cin >> a;
							menu();
						}

						// Editing Doctor Profile...

						else if (number == 5) {
							system("cls");
							int docage, docsalary, day, month, year;
							string docname, docgmail, docexpyears, docprof;
							cout << endl << "Enter Your Name: ";
							cin >> docname;
							cout << endl << "Enter Gmail: ";
							cin >> docgmail;
							cout << endl << "Enter Age: ";
							cin >> docage;
							cout << "Enter Profession: ";
							cin >> docprof;
							cout << endl << "Enter your Profession's Experience (In years): ";
							cin >> docexpyears;
							cout << endl << "Enter Date joined(In format dd mm yyyy): ";
							cin >> day >> month >> year;
							cout << endl << "Enter Salary (In rupees): ";
							cin >> docsalary;
							ofstream profile;
							profile.open("Dr." + docname + ".txt");
							profile << "Doctor name: " << docname << endl;
							profile << "Doctor Gmail:" << docgmail << endl;
							profile << "Doctor Age: " << docage << endl;
							profile << "Doctor Profession: " << docprof;
							profile << "Doctor Experience (In Years): " << docexpyears << endl;
							profile << "Date Joined: " << day << " " << month << " " << year << endl;
							profile << "Doctor Salary: " << docsalary;
							profile.close();
							cout << "Profile Updated..." << endl;
							cout << "Press any key and then Press Enter to move to main menu...";
							cin >> a;
							menu();
						}

						// Checking Doctor Profile...

						else if (number == 6) {
							system("cls");
							cout << "----------------DOCTOR PROFILE-------------------" << endl;
							string st;
							ifstream fil;
							fil.open("Dr.Faizan.txt");
							while (!fil.eof()) {
								st = fil.get();
								cout << st;
							}
							cout << "Press any key and then Press Enter to move to main menu...";
							cin >> a;
							menu();
						}

						// Exiting...

						else if (number == 7) {
							system("cls");
							cout << "Exiting..." << endl;
						}
						else
							cout << "Input Error...." << endl;
					}
				}
				else if (menu_num == 2) {
					cout << "Exiting...." << endl << endl;
				}
				else {
					cout << "Error Occured..." << endl;
					return 0;
				}
			}

		}
		else if (choice == 3) {
			cout << "Exiting..." << endl;
			return 0;
		}
		else {
			cout << "Input Error..." << endl;
		}
	}
	return 0;
}
int main() {
	int z=0;
	cout << "------------WELCOME TO HOSPITAL MANAGEMENT SYSTEM---------------" << endl;
	cout << "Press 1 if you are patient." << endl;
	cout << "Press 2 if you are doctor." << endl;
	cout << "Press 3 to Exit." << endl;
	while (z != 3) {
		cin >> z;

		if (z == 1) {
			patmain();
		}
		else if (z == 2) {
			docmain();
		}
		else if (z == 3) {
			cout << "Exiting..." << endl;
			return 0;
		}
		else {
			cout << "Input Error..." << endl;
		}
	}
	return 0;
}
