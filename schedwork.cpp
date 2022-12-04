#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
//scheduler: actual scheduleHelper which uses recursive backtracking to find solutions for the schedule.
//requires current row/col of availability matrix, a daily schedule input, an availability matrix, days needed, total number of workers, workers needed, max shifts
bool scheduler(DailySchedule& sched, size_t row, size_t col, int needed, const size_t maxShifts, int totalWorkers, int workersNeeded, const AvailabilityMatrix& avail);

//isValid: requires max shifts, number of days, 'needed' value, worker currently being considered, availability matrix, and schedule which needs validity check.
bool isValid(int needed, const size_t maxShifts, size_t current, int days, const AvailabilityMatrix& available, DailySchedule& sched);

// Add your implementation of schedule() and other helper functions here

bool isValid(int needed, const size_t maxShifts, size_t current, int days, const AvailabilityMatrix& available, DailySchedule& sched) {
	size_t dDays;
	size_t shifts;
	shifts = 0;
	dDays = shifts;
	int currDay = 0;
	int workerCol = 0;
	while (currDay < days) {
		while (workerCol < needed) {
			if (sched[currDay][workerCol] != current) { //if the worker for a day and column is not the worker being checked, do nothing.

			}
			else { //otherwise, if the worker scheduled at sched[currDay][workerCol] IS the worker we're looking for, check if they're available that day. If not, the schedule is not valid.
				if (available[currDay][current] == true) {
					shifts++;
					dDays++;
				}
				else if (available[currDay][current] == false) {
					return false;
				}
			}
			workerCol++;
		}
		if (!(dDays <= 1)) {
			if (dDays > 1) {
				return false;
			}
		}
		currDay++;
	}
	bool check = !(shifts > maxShifts);
	return check;
}

bool scheduler(DailySchedule& sched, size_t row, size_t col, size_t needed, const size_t maxShifts, int totalWorkers, size_t workersNeeded, const AvailabilityMatrix& avail) {
	if (row == needed) { //base case for recursion: current row is the last needed
		return true;
	}
	if (col == workersNeeded) { //base case for recursion: 
		return scheduler(sched, row+1, 0, needed, maxShifts, totalWorkers, workersNeeded, avail);
	}
	int curr = 0;
	
	while (curr < totalWorkers) {
		sched[row][col] = (Worker_T)curr;
		if (isValid(needed, maxShifts, curr, workersNeeded, avail, sched)) {
			if (scheduler(sched, row, col+1, needed, maxShifts, totalWorkers, workersNeeded, avail) == false) { //if the next col over is invalid, move on.
				
			}
			else if (scheduler(sched,row,col+1,needed,maxShifts,totalWorkers,workersNeeded,avail) == true) {
				return true;
			}
		}
		curr++;
	}
	sched[row][col] = INVALID_ID;
	return false;
}

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
		
	size_t availableSize = avail.size();
	unsigned int i = 0;
	unsigned int j = 0;
	while (i < availableSize) {
		vector<Worker_T> currRow;
		while (j < dailyNeed) {
			currRow.push_back((unsigned int)-1);
			j++;
		}
		sched.push_back(currRow);
		i++;
	}
	int totalWorkers = avail[0].size();
	size_t row = 0;
	size_t col = 0;
	return scheduler(sched, row, col, availableSize, maxShifts, totalWorkers, dailyNeed, avail);
}

