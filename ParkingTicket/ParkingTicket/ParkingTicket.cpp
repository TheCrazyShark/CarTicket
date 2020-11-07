/*
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Name:			|	Shane Smith
userID:			|	sas1041
Project Name:	|	ParkingTicket
File Name:		|	ParkingTicket.cpp
STATUS:			|	This program does work correctly.
Start Date:		|	10/13/2020
End Date:		|	10/21/2020
Description:	|	This program aims to demonstrate how the Parked Car, ParkingMeter, ParkingTicket, and PoliceOfficer class can collaberate.
				|
				| 	This program was done entirely by me and no part of this program was plagiarized, intentionally or unintentionally, from anybody. I would be held
				| 	accountable and penalized if any part of this program was plagiarized.
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/

#include <iostream>
#include <string>
using namespace std;

class ParkingMeter {
	private:
		int minutesPurchased;
	public:
		void setMinutesPurchased() { // Called by the Car class to set how many minutes have been purchased
			cout << "Please enter how long the meter has been paid for." << endl;
			cin >> minutesPurchased;
		}
		int getMinutesPurchased() {
			return minutesPurchased;
		}
};

class ParkedCar{
	private:
		ParkingMeter carParkingMeter;
		string make;
		string model;
		string color;
		string licenseNumber;
		int numMinutes;
	public:
		ParkedCar() {
			make = "";
			model = "";
			color = "";
			licenseNumber = "";
			numMinutes = 0;
		}
		void setAttributes() { // Sets all of the car's attributes
			cout << "Please enter the parked car's Make, Model, Color, License Plate Number, and the number of minutes the car has been parked seperated by enter." << endl;
			getline(cin, make);
			getline(cin, model);
			getline(cin, color);
			getline(cin, licenseNumber);
			cin >> numMinutes;
			cin.ignore();

			cout << "This car is a " << color << " " << make << " " << model << " with the license number: " << licenseNumber << ". It has been parked for " << numMinutes << " minutes" << endl;
		}
		void setMinutesPurchased() { // Sets the number of minutes purchased by a car
			carParkingMeter.setMinutesPurchased();
		}
		string getMake() {
			return make;
		}
		string getModel() {
			return model;
		}
		string getColor() {
			return color;
		}
		string getLicenseNumber() {
			return licenseNumber;
		}
		int getNumMinutes() {
			return numMinutes;
		}
		int getMinutesPurchased() {
			return carParkingMeter.getMinutesPurchased();
		}
};

class ParkingTicket {
private:
	ParkedCar car;
	int fineAmount;
public:
	ParkingTicket() {
		fineAmount = 0;
	}
	void setCar(ParkedCar pCar) {
		car = pCar;
	}
	void setFineAmount() {
		int minutesOverLimit = car.getNumMinutes() - car.getMinutesPurchased(); // Gets the number of minutes that the car has been parked over the time that has been paid

		if (minutesOverLimit <= 60) { // If the minutesOverLimit is less than or equal to 60 minutes, the fine amount is only $25
			fineAmount = 25;
		}
		else {
			fineAmount += 25;
			minutesOverLimit = minutesOverLimit - 60; // Since the minutesOverLimit is over 60, we can automatically assume the "first hour" ticket and remove 60 minutes

			while (minutesOverLimit > 0) { // While the minutesOverLlimit is greater than 0, we can add 10 for each hour or part of an hour
				fineAmount += 10;
				minutesOverLimit -= 60;			}
		}
	}
	int getFineAmount() {
		return fineAmount;
	}
};


class PoliceOfficer {
private:
	ParkingTicket ticket; // Makes an instance of ticket
	ParkedCar car; // Makes an instance of car
	string officerName;
	string badgeNum;
public:
	PoliceOfficer() {
		officerName = "";
		badgeNum = "";
	}
	void setTicket(ParkedCar pCar) { // Sets the ticket for a car
		car = pCar;
		ticket.setCar(car);
		ticket.setFineAmount();
	}
	void setOfficer(string pOfficerName, string pBadgeNum) { // Sets the attributes for the officer
		officerName = pOfficerName;
		badgeNum = pBadgeNum;
	}
	string getOfficerName() {
		return officerName;
	}
	string getBadgeNum() {
		return badgeNum;
	}
	int getTicket() {
		return ticket.getFineAmount();
	}
};

int main() {
	ParkedCar car1;
	PoliceOfficer officer;

	car1.setAttributes(); // Sets the car's attributes
	car1.setMinutesPurchased(); // Sets the minutes purchased by a car
	if (car1.getNumMinutes() > car1.getMinutesPurchased()) { // Only calls the officer methods if they are needed. I.e. if the number of minutes a car has been parked exceeds the number of minutes purchased
		officer.setOfficer("Shane Smith", "POL123"); // Sets the officer's name and badge number
		officer.setTicket(car1); // Sets the ticket from an officer for a specified car
		cout << "The fine for this car is: $" << officer.getTicket() << " and it was given by officer " << officer.getOfficerName() << ", Badge #:" << officer.getBadgeNum() << "." << endl;
	}

	return 0;
}
