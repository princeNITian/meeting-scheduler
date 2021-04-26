/*
 * meeting_scheduler.cpp
 *
 *  Created on: 26-Apr-2021
 *      Author: prince
 */

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Meeting;

typedef unordered_map<int, vector<Meeting>> Calender;

class Room {
public:
	Room(string);
	bool book(int,int, int);
	const string& getName() const;

private:
	string name;
	Calender calender;
};

class Meeting {
public:
	Meeting(int, int, Room);
	int getEnd() const;
	int getStart() const;

private:
	int start,end;
	Room room;
};

class Scheduler {
	vector<Room> rooms;
public:
	Scheduler(vector<Room>);
	string book(int,int, int);
};


Room::Room(string name){
	this->name = name;
}

bool Room::book(int day,int start,int end){
	for(Meeting m: calender[day]){
		// to be implemented later
		if(m.getStart() < end && start < m.getEnd())
			return false;
	}
	Meeting meeting(start,end,*this);
	calender[day].push_back(meeting);
	return true;
}

const string& Room::getName() const {
	return name;
}

int Meeting::getEnd() const {
	return end;
}

int Meeting::getStart() const {
	return start;
}

Meeting::Meeting(int start, int end, Room room) : room(room)
{
	this->start = start;
	this->end = end;
}

Scheduler::Scheduler(vector<Room> rooms){
	this->rooms = rooms;
}

string Scheduler::book(int day, int start,int end){
	for(Room &room: rooms){
		bool flag = room.book(day,start,end);
		if(flag==true)
			return room.getName();
	}
	return "No rooms available.";
}


int main() {
	Room room1("Atlas");
	Room room2("Nexus");
	Room room3("Hollycow");

	vector<Room> roomVec;
	roomVec.push_back(room1);
	roomVec.push_back(room2);
	roomVec.push_back(room3);

	Scheduler scheduler(roomVec);

	cout << scheduler.book(15,2,5) <<endl;
	cout << scheduler.book(15,5,8) <<endl;
	cout << scheduler.book(15,4,8) <<endl;
	cout << scheduler.book(15,3,6) <<endl;
	cout << scheduler.book(15,7,8) <<endl;
	cout << scheduler.book(16,6,9) <<endl;
	return 0;
}
