#include "Licorice.h"	

Licorice::~Licorice(){}	//nothing to delete 


Licorice::Licorice()	//default case 
{
	shatterScore = 0;
	weapon = 0;
	name = "";
}

Licorice::Licorice(string n, int shatter, int w)	//constructor with parameters
{
	name = n;
	shatterScore = shatter;
	weapon = w;
}

int Licorice::fire()
{
	int random = 0+ rand() % (weapon); //generate a random number between 0 and p-1 
	return random; 
}
		
//access functions
int Licorice::getShatterScore()	//not sure this is necessary?
{
	return shatterScore;
}

//comparison functions 
//we had to overload a bunch of operators so we could insert a baby into the tree
//all of these comparisons are done with shatterScore being the means for comparison 

// == operator 
bool operator == (const Licorice & b1, const Licorice & b2)
{
	if(b1.shatterScore == b2.shatterScore)
	{
		return true; 
	}
	else 
	{
		return false; 
	}
}

// <= operator 
bool operator <= (const Licorice & b1, const Licorice & b2)
{
	if(b1.shatterScore <= b2.shatterScore)
	{
		return true; 
	}
	else 
	{
		return false; 
	}
}

// >= operator 
bool operator >= (const Licorice & b1, const Licorice & b2)
{
	if(b1.shatterScore >= b2.shatterScore)
	{
		return true; 
	}
	else 
	{
		return false; 
	}
}

// < operator 
bool operator < (const Licorice & b1, const Licorice & b2)
{
	if(b1.shatterScore < b2.shatterScore)
	{
		return true; 
	}
	else 
	{
		return false; 
	}
}

// > operator 
bool operator > (const Licorice & b1,const Licorice & b2)
{
	if(b1.shatterScore > b2.shatterScore)
	{
		return true; 
	}
	else 
	{
		return false; 
	}
}

// operator overload of << so we can print in the traversals 
ostream & operator << (ostream & out, const Licorice & b)
{
	out << "Baby: " << b.name << " Shatter Score: " << b.shatterScore << " Weapon: " << b.weapon << " "; 
	return out; 
}
	
//our print function mainly for testing 
void Licorice::printBabies()
{
	cout << name << " " << shatterScore << " " << weapon << endl; 
}