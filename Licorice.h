#ifndef LICORICE_H
#define LICORICE_H
#include <iostream>
#include <string>
using namespace std;

class Licorice 
{
	private: 
		int shatterScore;
		int weapon; 
		string name;
	
	protected:
	
	public:
		Licorice();
		Licorice(string, int, int);
		~Licorice();
		int fire();
		
		//access functions
		int getShatterScore();
		
		void printBabies();
		
		//operator overloads for comparison so we can insert babies into tree
		friend bool operator == (const Licorice &, const Licorice &); 
		friend bool operator <= (const Licorice &, const Licorice &); 
		friend bool operator >= (const Licorice &, const Licorice &); 
		friend bool operator < (const Licorice &, const Licorice &); 
		friend bool operator > (const Licorice &, const Licorice &); 
		
		//operator overload so we can print in traversals 
		friend ostream & operator << (ostream & , const Licorice &); 


};
#endif