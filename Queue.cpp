#include"Queue.h"
#include"Utility.h"
#include<iostream>
using namespace std;
Queue::Queue() {
	count = 0;
	rear = maxqueue - 1;
	front = 0;
}
bool Queue::empty() const {
	return this->count == 0;
}
Error_code Queue::serve() {
	if (count <= 0) return fail;
	count--;
	front = ((front + 1) == maxqueue) ? 0 : (front + 1);
	return success;
}
Error_code Queue::append(const Queue_entry& item) {
	if (count >= maxqueue) return fail;
	count++;
	rear = ((rear)+1 == maxqueue) ? 0 : (rear + 1);
	entry[rear] = item;
	return success;
}
Error_code Queue::retrieve(Queue_entry& item) const {
	if (count <= 0) return fail;
	item = entry[front];
	return success;
}
bool Extended_queue::full() const {
	return count == maxqueue;
}
int Extended_queue::size() const {
	return this->count;
}
void Extended_queue::clear() {
	this->count = 0;
}
Error_code Extended_queue::serve_and_retrieve(Queue_entry& item) {
	if (count <= 0) return fail;
	this->serve();
	this->retrieve(item);
	return success;
}

int Extended_queue::minIndex() {
	int index = front;
	int min = entry[front].getFuel();
	int k;
	for (int i = 1; i < this->size(); i++) {
		k = front + i >= maxqueue ? front + i - maxqueue : front + i;
		if (entry[k].getFuel() < min) {
			min = entry[k].getFuel();
			index = k;
		}
	}
	return index;
}

int Extended_queue::minFuel() {
	int index = front;
	int min = entry[front].getFuel();
	int k;
	for (int i = 1; i < this->size(); i++) {
		k = front + i >= maxqueue ? front + i - maxqueue : front + i;
		if (entry[k].getFuel() < min) {
			min = entry[k].getFuel();
			index = k;
		}
	}
	return min;
}

void Extended_queue::changeOrder(int k) {
	Plane temp = entry[k];
	if (front > k) {
		for (int i = maxqueue + k; i > front; i--) {
			if (i > maxqueue) {
				entry[i - maxqueue] = entry[i - 1 - maxqueue];
			}
			else if (i == maxqueue) {
				entry[0] = entry[maxqueue - 1];
			}
			else {
				entry[i] = entry[i - 1];
			}
		}
		entry[front] = temp;
	}
	else if (front <= k) {
		for (int i = k; i > front; i--) {
			entry[i] = entry[i - 1];
		}
		entry[front] = temp;
	}
}

int Extended_queue::getDistanceWithFront(int k) {
	if (front >= k) {
		return maxqueue - front + k;
	}
	else return k - front;
}

void Extended_queue::reduceFuel() {
	for (int i = 0; i < this->size(); i++) {
		if (front + i < maxqueue) {
			entry[front + i].reduceFuel();
		}
		else {
			entry[front + i - maxqueue].reduceFuel();
		}

	}
}