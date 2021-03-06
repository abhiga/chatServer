

//
// Implementation of a HashTable that stores void *
//
#include "HashTableVoid.h"
//#include <stdio.h>

// Obtain the hash code of a key
int HashTableVoid::hash(const char * key)
{
	// Add implementation here
	int h = 0;
	const char *p = key;
	while(*p) {
		h+=*p;
		p++;
	}
	return h%TableSize;
}

// Constructor for hash table. Initializes hash table
HashTableVoid::HashTableVoid()
{
	// Add implementation here
	_buckets = (HashTableVoidEntry**)malloc(TableSize*sizeof(HashTableVoidEntry*));
	for (int i = 0; i< TableSize; i++) {
		_buckets[i] = NULL;
	}
}

// Add a record to the hash table. Returns true if key already exists.
// Substitute content if key already exists.
bool HashTableVoid::insertItem( const char * key, void * data)
{
	// Add implementation here
	int h = hash(key);
	HashTableVoidEntry *e = _buckets[h];
	while(e!=NULL) {
		if(!strcmp(e->_key, key)) {
			e->_data = data;
			return true;
		}
		e = e->_next;
	}
	e = new HashTableVoidEntry;
	e->_key = strdup(key);
	e->_data = data;
	e->_next = _buckets[h];
	_buckets[h] = e;
	return false;
}

// Find a key in the dictionary and place in "data" the corresponding record
// Returns false if key is does not exist
bool HashTableVoid::find( const char * key, void ** data)
{
	// Add implementation here
	int h = hash(key);
	HashTableVoidEntry *e = _buckets[h];
	while(e!=NULL) {
		if(!strcmp(e->_key, key)) {
			*data = e->_data;
			return true;
		}
		e = e->_next;
	}
	return false;
}

// Removes an element in the hash table. Return false if key does not exist.
bool HashTableVoid::removeElement(const char * key)
{
	// Add implementation here
	int h = hash(key);
	HashTableVoidEntry * e = _buckets[h];
	HashTableVoidEntry * prev = NULL;
	while(e!=NULL) {
		if(!strcmp(e->_key,key)) {
			if(prev!=NULL)
				prev->_next = e->_next;

			else {
				_buckets[h] = e->_next;
			}
			//	free(e->_key);
			delete e;
			return true;
		}
		prev = e;
		e = e->_next;
	}
	return false;
}

// Creates an iterator object for this hash table
HashTableVoidIterator::HashTableVoidIterator(HashTableVoid * hashTable)
{
	// Add implementation here
	_hashTable = hashTable;
	_currentBucket = 0;
	_currentEntry = _hashTable -> _buckets[0];
	//for (int i = 0; i < _hashTable -> TableSize; i++){
	//	if(_hashTable->_buckets[i]!=NULL){
	//		_currentBucket += i;
	//		_currentEntry = _hashTable -> _buckets[i];
	//		break;
	//	}
	//}

}

// Returns true if there is a next element. Stores data value in data.
bool HashTableVoidIterator::next(const char * & key, void * & data)
{
	// Add implementation here
	//int count = 0;
	//bool flag = true;
	//if(_currentEntry == NULL){
	//printf("abhigas\n");
	//return false;
	//}
	if(_currentEntry == NULL){
		for(int i = _currentBucket; i< _hashTable -> TableSize; i++) {
			_currentBucket++;
			if(_hashTable -> _buckets[i]!=NULL){
				_currentEntry = _hashTable -> _buckets[i];
				key = _currentEntry -> _key;
				data = _currentEntry -> _data;
				return true;
			}

		}
	}
	else if(_currentEntry -> _next != NULL){
		_currentEntry = _currentEntry -> _next;
		key = _currentEntry -> _key;
		data = _currentEntry -> _data;
		//printf("abhiga\n");
		return true;
	}
	else {
		for(int i = _currentBucket; i< _hashTable -> TableSize; i++) {
			_currentBucket++;
			if(_hashTable -> _buckets[i]!=NULL){
				_currentEntry = _hashTable -> _buckets[i];
				key = _currentEntry -> _key;
				data = _currentEntry -> _data;
				return true;
			}
		}


	}
	return false;
}
