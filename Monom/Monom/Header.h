#pragma once
#define VARS_COUNT 3 
class Monom {
	float _coef;
	int _powers[VARS_COUNT];
	size_t _vars_count;
	// имена vars
public:
	Monom(const Monom&);
	Monom(float _coef, int _powers, size_t _vars_count);
	//==
	//+(Monom)
	//*int
	//-(Monom)
	// /Monom
	//*(Monom)
	//!=
	//=
	//+=
	//-=
	//*=(Monom)
	//*=int 
	// /=
	// >Monom
	//<Monom
};

class Polynom {
	static char* var_names[VARS_COUNT];
	TList <Monom>_polynom;
	Polynom();
	Polynom(const Polynom&);
	Polynom(std::string  pol);
	//+Mon,Pol
	//-Mon,Pol
	//*Mon,Pol
	// /Mon,Pol
	

};
//1 вариант :
/*P(x,y,2)
2 вариант :
Pn(x1,..xn)/