#include <iostream>
#include <cassert>
using namespace std;


int countSeats(string, char, int&);	//parsing pollData and calling countSection to count total seats
int countSection(string, char, int&);	//count one section's seats, add it to total seats, and also return one section's seats
bool isValidPollString(string);	//parsing pollData and calling isValidPollSection to determine whether pollData valid
bool isValidPollSection(string);	//determine whether one section of pollData is valid
bool isValidStateCode(string);	//determine whether state code is valid, giving by CS31 website
bool isValidPartyCode(char);	//determine whether party code is valid
int myAtoi(string);	//transform string to integer.

int main()
{
	assert(isValidPollString("CT5D,NY9R16D1I,VT,ne3r00D"));
	assert(!isValidPollString("ZT5D,NY9R16D1I,VT,ne3r00D"));	// invalid string
	assert(isValidPollString(""));	// empty string should return true
	assert(!isValidPollString("GOGOBRUINS!"));	//invalid string
	assert(!isValidPollString("CT5D,,NY9R16D1I,VT,ne3r00"));	//repetitive comma
	assert(!isValidPollString("CT5DCK"));	//lack of numbers before the party code

	string allStates = 
		"AL1K,AK1K,AZ1K,AR1K,CA1K,CO1k,Ct1k,DE1k,FL1k,GA1k,HI1K,iD1K,Il1K,IN01k,IA01K,KS01k,KY1k,"
		"LA11A,ME,MA,MD,MI,MN,ms,mO,mT,NE,NV,NH,NJ,NM,NY,NC,ND,"
		"OH,OK,OR,PA,RI,SC,SD,TN,TX,UT01m,VT10M,VA,WA,WV,WI00M,WY01k";
	assert(isValidPollString(allStates));
	int s = 0 ;
	int& seats = s;
	seats = -999;    // so we can detect whether countSeats sets seats
	assert(countSeats("CT5D,NY9R16D1I,VT,ne3r00D", 'd', seats) == 0 && seats == 21);
	seats = -999;    // so we can detect whether countSeats changes seats
	assert(countSeats("CT5D,NY9R16D1I,VT,ne3r00D", '%', seats) == 2 && seats == -999);


	seats = -999;	// return 0 if the poll string is empty
	assert(countSeats("", 'k', seats) == 0 && seats == 0);
	seats = -999;	// return 2 if party code not exist
	assert(countSeats("", '*', seats) == 0 && seats == 0);
	
	seats = -999;    // returns 1 if the poll string is invalid
	assert(countSeats("CT5D,JNY9R16D1I,VT,ne3r00D", 'd', seats) == 1 && seats == -999);
	seats = -999;    // returns 1 if the poll string is invalid
	assert(countSeats("CT5D,,NY9R16D1I,VT,ne3r00D", 'd', seats) == 1 && seats == -999);
	seats = -999;    // returns 1 if the poll string is invalid
	assert(countSeats("#T5D,NY9R16D1I,VT,ne3r00D", 'd', seats) == 1 && seats == -999);
	seats = -999;    // returns 1 if the parameter party is not a letter
	assert(countSeats("CT5D,NY9R16D1I,VT,ne3r00D", '%', seats) == 2 && seats == -999);
	assert(countSeats("CT5D,NY9R16D1I,VT,ne3r00D", ' ', seats) == 2 && seats == -999);
	assert(countSeats("CT5D,NY9R16D1I,VT,ne3r00D", '!', seats) == 2 && seats == -999);
	seats = -999;    // returns 0 and set seats to 0 if the parameter party is nonexisted in the poll string
	assert(countSeats("CT5D,NY9R16D1I,VT,ne3r00D", 'a', seats) == 0 && seats == 0);

	seats = -999;    // returns 1 if the poll string is invalid
	assert(countSeats("CT5D,No23d", 'a', seats) == 1 && seats == -999);
	seats = -999;    // returns 1 if the poll string is invalid
	assert(countSeats("CS31 is Great", 'a', seats) == 1 && seats == -999);

	seats = -999;    // test upper case party code
	assert(countSeats("CT5A,NY9R16D1I,VT,ne3r00D", 'A', seats) == 0 && seats == 5);
	seats = 999;    // test sum beyound 100
	assert(countSeats("CT5A,NY9R16D1I,VT,ne3r99a", 'A', seats) == 0 && seats == 104);

	seats = -999;    // test different letter cases
	assert(countSeats("Ct99A,NY9R16D1I,VT,ne3r99a", 'A', seats) == 0 && seats == 198);

	seats = -123;	//test all staes
	assert(countSeats(allStates, 'A', seats) == 0 && seats == 11);
	seats = 500;	//test all states with positive start seats
	assert(countSeats(allStates, 'k', seats) == 0 && seats == 18);


	assert(isValidPollString("CT5D,NY9R17D1I,VT,ne3r00D"));
		assert(!isValidPollString(",CT5D,NY9R17D1I,VT,ne3r00D"));
		assert(!isValidPollString("CT5D,NY9R17&1I,VT,ne3r00D"));
		assert(!isValidPollString("CT5D,NY9 R17D1I,VT,ne3r0 0D"));
		assert(!isValidPollString("CT5D,NY9 R17D1I,VT,ne3r00 D"));
		assert(!isValidPollString("    "));
		assert(!isValidPollString("NY9R17D1I, Vt, NJ3d5r4D, KS4R"));
		assert(!isValidPollString("TY9R17D1I,Vt,NJ3d5r4D,KS4R"));
		assert(!isValidPollString("NY922R17D1I,Vt,NJ3d5r4D,KS4R"));
		assert(isValidPollString("NY"));
		assert(!isValidPollString("CA32"));		//wrong
		assert(!isValidPollString("NYd"));
		seats = -999;
		assert(countSeats("CT5d,NY9R17D1I,VT,ne3r00d", 'd', seats) == 0 && seats == 22);
		seats = -999;
		assert(countSeats("CT5D,NY9R17D1I,VT,ne3r00D", '%', seats) == 2 && seats == -999);
		assert(countSeats("CA32", 'D', seats) == 1 && seats == -999);
		assert(countSeats("CA", 'D', seats) == 0 && seats == 0);
		seats = -999;
		assert(countSeats("", 'D', seats) == 0 && seats == 0);
		assert(isValidPollString("MA9D,KS4R") && isValidPollString("KS4R,MA9D"));
		assert(isValidPollString("MA9D,,KS4R") == isValidPollString("KS4R,,MA9D"));
		assert(isValidPollString("CT5D,NY9R17D1I,VT,ne3r00D"));
		assert(!isValidPollString(",CT5D,NY9R17D1I,VT,ne3r00D"));
		assert(!isValidPollString(" CT5D,NY9R17D1I,VT,ne3r00D"));
		assert(!isValidPollString("!CT5D,NY9R17D1I,VT,ne3r00D"));
		assert(!isValidPollString("CT5DNY9R17D1IVTne3r00D"));
		assert(!isValidPollString("CT5D5,NY9R17D1I,VT,ne3r00D"));
		assert(!isValidPollString("CT5D5, NY9R17D1I,VT,ne3r00D"));
		assert(!isValidPollString("CT5D5 ,NY9R17D1I,VT,ne3r00D"));
		assert(!isValidPollString("CT5D5, NY9R17D1I ,VT,ne3r00D"));
		assert(!isValidPollString("KS4R, NV3D1R "));
		assert(!isValidPollString("aaaaaaa"));
		assert(!isValidPollString("a"));
		assert(!isValidPollString("NY, ,"));
		assert(!isValidPollString("KS 4R"));
		assert(isValidPollString("KS4R"));
		assert(isValidPollString("KS4r"));
		assert(!isValidPollString("KS4R,"));
		assert(isValidPollString("KS4R"));
		assert(!isValidPollString("ne3r00"));
		assert(!isValidPollString("ne3r000D"));
		assert(!isValidPollString("3r00D"));
		assert(!isValidPollString("ner000D"));
		assert(!isValidPollString("ne3r 000D"));
		assert(!isValidPollString("ne3rr00D"));
		assert(!isValidPollString("ne3rD"));	//119
		assert(!isValidPollString("ne3r00D3"));
		assert(!isValidPollString("ex3r00D3"));
		assert(!isValidPollString("ne3r00DD"));
		assert(!isValidPollString("ne3"));
		assert(!isValidPollString("ne3r9"));
		assert(isValidPollString(""));
		assert(isValidPollString("NY"));
		assert(!isValidPollString("N7Y"));
		assert(!isValidPollString("NY4"));
		assert(!isValidPollString("NY4 "));
		assert(!isValidPollString(" NY4"));
		assert(!isValidPollString("$$,!!,6I"));
		assert(!isValidPollString("ny,!!,6I"));
		assert(!isValidPollString("ny09I,!!,6I"));
	

		seats = 0;
		countSeats("VA7R,KS4R", 'r', seats);
		assert(seats == 11);
		countSeats("VA7R,KS4R4", 'r', seats);
		assert(seats == 11);
		countSeats("VA71R,KS4R", 'r', seats);
		assert(seats == 75);
		countSeats("NY", 'r', seats);
		assert(seats == 0);
	

		assert(countSeats("NY", '@', seats) == 2);
		assert(seats == 0);
	

		assert(countSeats("NY3", 'r', seats) == 1);
		assert(seats == 0);
		seats = 3;
		assert(countSeats("", 'r', seats) == 0);
		assert(seats == 0);
		assert(countSeats("CA99D", 'D', seats) == 0);
		assert(seats == 99);
	

		assert(countSeats("CAD", 'D', seats) == 1);
		assert(seats == 99);
		assert(countSeats("", 'D', seats) == 0);
		assert(seats == 0);
		assert(countSeats("CA99D", '6', seats) == 2);
		assert(seats == 0);










		assert(isValidPollString("CT5D,NY9R17D1I,VT,ne3r00D"));
		assert(!isValidPollString(",CT5D,NY9R17D1I,VT,ne3r00D"));
		assert(!isValidPollString("CT5D,NY9R17&1I,VT,ne3r00D"));
		assert(!isValidPollString("CT5D,NY9 R17D1I,VT,ne3r0 0D"));
		assert(!isValidPollString("CT5D,NY9 R17D1I,VT,ne3r00 D"));
		assert(!isValidPollString("    "));
		assert(!isValidPollString("NY9R17D1I, Vt, NJ3d5r4D, KS4R"));
		assert(!isValidPollString("TY9R17D1I,Vt,NJ3d5r4D,KS4R"));
		assert(!isValidPollString("NY922R17D1I,Vt,NJ3d5r4D,KS4R"));
		assert(isValidPollString("NY"));
		assert(!isValidPollString("CA32"));
		assert(!isValidPollString("NYd"));
		seats = -999;
		assert(countSeats("CT5d,NY9R17D1I,VT,ne3r00d", 'd', seats) == 0 && seats == 22);
		seats = -999;
		assert(countSeats("CT5D,NY9R17D1I,VT,ne3r00D", '%', seats) == 2 && seats == -999);
		assert(countSeats("CA32", 'D', seats) == 1 && seats == -999);
		assert(countSeats("CA", 'D', seats) == 0 && seats == 0);
		seats = -999;
		assert(countSeats("", 'D', seats) == 0 && seats == 0);
		assert(isValidPollString("MA9D,KS4R") && isValidPollString("KS4R,MA9D"));
		assert(isValidPollString("MA9D,,KS4R") == isValidPollString("KS4R,,MA9D"));
		assert(isValidPollString("CT5D,NY9R17D1I,VT,ne3r00D"));
		assert(!isValidPollString(",CT5D,NY9R17D1I,VT,ne3r00D"));
		assert(!isValidPollString(" CT5D,NY9R17D1I,VT,ne3r00D"));
		assert(!isValidPollString("!CT5D,NY9R17D1I,VT,ne3r00D"));
		assert(!isValidPollString("CT5DNY9R17D1IVTne3r00D"));
		assert(!isValidPollString("CT5D5,NY9R17D1I,VT,ne3r00D"));
		assert(!isValidPollString("CT5D5, NY9R17D1I,VT,ne3r00D"));
		assert(!isValidPollString("CT5D5 ,NY9R17D1I,VT,ne3r00D"));
		assert(!isValidPollString("CT5D5, NY9R17D1I ,VT,ne3r00D"));
		assert(!isValidPollString("KS4R, NV3D1R "));
		assert(!isValidPollString("aaaaaaa"));
		assert(!isValidPollString("a"));
		assert(!isValidPollString("NY, ,"));
		assert(!isValidPollString("KS 4R"));
		assert(isValidPollString("KS4R"));
		assert(isValidPollString("KS4r"));
		assert(!isValidPollString("KS4R,"));
		assert(isValidPollString("KS4R"));
		assert(!isValidPollString("ne3r00"));
		assert(!isValidPollString("ne3r000D"));
		assert(!isValidPollString("3r00D"));
		assert(!isValidPollString("ner000D"));
		assert(!isValidPollString("ne3r 000D"));
		assert(!isValidPollString("ne3rr00D"));
		assert(!isValidPollString("ne3rD"));
		assert(!isValidPollString("ne3r00D3"));
		assert(!isValidPollString("ex3r00D3"));
		assert(!isValidPollString("ne3r00DD"));
		assert(!isValidPollString("ne3"));
		assert(!isValidPollString("ne3r9"));
		assert(isValidPollString(""));
		assert(isValidPollString("NY"));
		assert(!isValidPollString("N7Y"));
		assert(!isValidPollString("NY4"));
		assert(!isValidPollString("NY4 "));
		assert(!isValidPollString(" NY4"));
		assert(!isValidPollString("$$,!!,6I"));
		assert(!isValidPollString("ny,!!,6I"));
		assert(!isValidPollString("ny09I,!!,6I"));


		seats = 0;
		countSeats("VA7R,KS4R", 'r', seats);
		assert(seats == 11);
		countSeats("VA7R,KS4R4", 'r', seats);
		assert(seats == 11);
		countSeats("VA71R,KS4R", 'r', seats);
		assert(seats == 75);
		countSeats("NY", 'r', seats);
		assert(seats == 0);


		assert(countSeats("NY", '@', seats) == 2);
		assert(seats == 0);


		assert(countSeats("NY3", 'r', seats) == 1);
		assert(seats == 0);
		seats = 3;
		assert(countSeats("", 'r', seats) == 0);
		assert(seats == 0);
		assert(countSeats("CA99D", 'D', seats) == 0);
		assert(seats == 99);


		assert(countSeats("CAD", 'D', seats) == 1);
		assert(seats == 99);
		assert(countSeats("", 'D', seats) == 0);
		assert(seats == 0);
		assert(countSeats("CA99D", '6', seats) == 2);
		assert(seats == 0);




	cerr << "All tests succeeded" << endl;
}

int countSeats(string pollData, char party, int& seatCount) {
	if (pollData == "") {	//deal with empty string
		seatCount = 0;
		return 0;
	}
	party = toupper(party);
	//transform party code and pollData to upper letter first!
	for (int i = 0; i < pollData.size(); i++) pollData.at(i) = toupper(pollData.at(i));
	if (!isValidPollString(pollData)) return 1;
	if (!isValidPartyCode(party)) return 2;
	seatCount = 0;

	int tokenIndex = pollData.find(",");
	while (tokenIndex != -1) {	//parsing pollData into sections, and call countSection for each section
		string pollSection = pollData.substr(0, tokenIndex);
		pollData = pollData.substr(tokenIndex + 1, pollData.size() - tokenIndex + 1);
		countSection(pollSection, party, seatCount);
		tokenIndex = pollData.find(",");
	}
	countSection(pollData, party, seatCount);	//never forget the last one :)
	return 0;
}

int countSection(string pollSection, char party, int& seatCount) {
	string data = pollSection.substr(2, pollSection.size() - 2);	//cut off the state code
	int endIndex = data.find(party);	//find party code index
	if (endIndex <= 0) return 0;
	int startIndex = endIndex - 1;

	while (startIndex >= 0 && isdigit(data[startIndex])) startIndex--;	//find previous letter index
	startIndex++; //increase one to back to the real start index
	int seat = myAtoi(data.substr(startIndex, endIndex - startIndex));	//get the seats of party
	seatCount += seat;
	return seat;
}

bool isValidPollString(string pollData) {
	if (pollData == "") return true;
	for (int i = 0; i < pollData.size(); i++) pollData.at(i) = toupper(pollData.at(i));
	//transform pollData to upper letter first!
	int tokenIndex = pollData.find(",");
	while (tokenIndex != -1) {	//parsing pollData to sections, and call isValidPollSection to determine whether each section is valid
		string pollSection = pollData.substr(0, tokenIndex);
		pollData = pollData.substr(tokenIndex + 1, pollData.size() - tokenIndex + 1);
		if (!isValidPollSection(pollSection)) return false;
		tokenIndex = pollData.find(",");
	}
	if (!isValidPollSection(pollData)) return false;		//never forget the last one :)
	return true;
}

bool isValidPollSection(string pollSection) {
	string stateCode = pollSection.substr(0, 2);
	if (!isValidStateCode(stateCode)) return false;	//check whether the first two letters are valid state code

	int digitLen = 0, letterLen = 0;	//record the length of consective digits and letters
	int digitPartCount = 0, letterPartCount = 0;	//tracking the number of digit parts and letter parts

	for (int i = 2; i < pollSection.size(); i++) {
		if (digitLen > 2 || letterLen > 1) return false;
		//digits part length beyound 2 or letter part length beyound 1, then it is not valid
		if (isdigit(pollSection.at(i))) {
			if (digitLen == 0) digitPartCount++;;
			letterLen = 0;	//reset letter length
			digitLen++;
		}
		else if (isalpha(pollSection.at(i))) {
			if (letterLen == 0) letterPartCount++;
			digitLen = 0;	//reset digit length
			letterLen++;
		}
		else return false; ///if current character is not a letter nor a digit, it is invalid
	}
	if (digitLen > 2 || letterLen > 1) return false;	//never forget the last one :)
	if (digitPartCount != letterPartCount) return false;	//if the number digit part and the letter part is not equal, it is invalid
	return true;
}

bool isValidStateCode(string stateCode) {
	const string codes =
		"AL.AK.AZ.AR.CA.CO.CT.DE.FL.GA.HI.ID.IL.IN.IA.KS.KY."
		"LA.ME.MA.MD.MI.MN.MS.MO.MT.NE.NV.NH.NJ.NM.NY.NC.ND."
		"OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
	return (stateCode.size() == 2 &&
		stateCode.find('.') == string::npos &&  // no '.' in stateCode
		codes.find(stateCode) != string::npos);  // match found
}

bool isValidPartyCode(char partyCode) {
	return isalpha(partyCode);
}

int myAtoi(string numString) {
	int res = 0;
	for (int i = 0; i < numString.size(); i++) {
		res *= 10;
		res += numString[i] - '0';
	}
	return res;
}