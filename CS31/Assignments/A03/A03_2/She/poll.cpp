
#include <iostream>
#include <cassert>
using namespace std;


bool isValidforcast(string forcast); //tests whether the input string is a valid forcast
bool isValidPollString(string pollData); //tests whether the input string is a valid poll string
int countSeats(string pollData, char party, int& seatCount); //counts the seats for a chosen party

int main()
{
    // to detect whether isValidPollString recognize a valid poll string
    assert(isValidPollString("CT5D,NY9R16D1I,VT,ne3r00D"));
    // to detect whether isValidPollString recognize a valid poll string if there is only one forecast
    assert(isValidPollString("KS4R"));
    // to detect whether isValidPollString recognize a valid poll string if it only has state number
    assert(isValidPollString("NY"));
    // to detect whether isValidPollString recognize a valid poll string when the input is empty
    assert(isValidPollString(""));
    // to detect whether isValidPollString recognize an invalid poll string when there is a comma precedes the first state forecast
    assert(!isValidPollString(",ZT5D,NY9R16D1I,VT,ne3r00D"));
    // to detect whether isValidPollString recognize an invalid poll string when there is a comma follows the last state forecast
    assert(!isValidPollString("ZT5D,NY9R16D1I,VT,ne3r00D,"));
    // to detect whether isValidPollString recognize an invalid poll string when there are two consecutive commas
    assert(!isValidPollString("ZT5D,,NY9R16D1I,VT,ne3r00D"));
    // to detect whether isValidPollString recognize an invalid poll string when the statecode is nonexisted
    assert(!isValidPollString("ZT5D,NY9R16D1I,VT,ne3r00D"));
    // to detect whether isValidPollString recognize an invalid poll string when there is a blank space
    assert(!isValidPollString("ZT5D, NY9R16D1I,VT,ne3r00D"));
    // to detect whether isValidPollString recognize an invalid poll string when there is a special character
    assert(!isValidPollString("ZT5D,@NY9R16D1I,VT,ne3r00D"));
    // to detect whether isValidPollString recognize an invalid poll string when there is more than two digits in the party results
    assert(!isValidPollString("ZT5D,NY9R160D1I,VT,ne3r00D"));
    // to detect whether isValidPollString recognize an invalid poll string when the digit is missing in the party results
    assert(!isValidPollString("ZT5D,NY9R16D1I,VT,ner00D"));
    // to detect whether isValidPollString recognize an invalid poll string when the letter is missing in the party results
    assert(!isValidPollString("ZT5D,NY9R16D1,VT,ne3r00D"));
    // to detect whether isValidPollString recognize an invalid poll string when two letter comes together in the party results
    assert(!isValidPollString("ZT5rD,NY9R16D1,VT,ne3r00D"));
    
    int seats;
    seats = -999;    // so we can detect whether countSeats sets seats and returns the correct value even the party name is in uppercase in the first parameter and in lowercase in the second parameter
    assert(countSeats("CT5D,NY9R16D1I,VT,ne3r00D", 'd', seats) == 0  &&  seats == 21);
    seats = -999;    // so we can detect whether countSeats changes seats and returns 2 if the parameter party is not a letter
    assert(countSeats("CT5D,NY9R16D1I,VT,ne3r00D", '%', seats) == 2  &&  seats == -999);
    seats = -999;    // so we can detect whether the function returns 1 if the poll string is invalid
    assert(countSeats("CT5D, NY9R16D1I,VT,ne3r00D", 'd', seats) == 1  &&  seats == -999);
    seats = -999;    // so we can detect whether the function returns 1 if the parameter party is not a letter and the poll string is invalid
    assert(countSeats("CT5D, NY9R16D1I,VT,ne3r00D", '%', seats) == 1  &&  seats == -999);
    seats = -999;    // so we can detect whether the function returns 0 and set seats to 0 if the parameter party is nonexisted in the poll string
    assert(countSeats("CT5D,NY9R16D1I,VT,ne3r00D", 'a', seats) == 0  &&  seats == 0);



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


bool isValidforcast(string forcast){
    //test whether forcast at least contains state code
    if (forcast.size() < 2)
    {
        return false;
    }
    
    bool isStateCode = false;
    //test whether the first two characters make a state code
    string statecode = "AL AK AZ AR CA CO CT DE FL GA HI ID IL IN IA KS KY LA ME MA MD MI MN MS MO MT NE NV NH NJ NM NY NC ND OH OK OR PA RI SC SD TN TX UT VT VA WA WV WI WY";
    for (int i = 0; i < statecode.size() - 1; i++)
    {
        if (statecode.at(i) == toupper(forcast.at(0)) && statecode.at(i+1) == toupper(forcast.at(1)))
        {
            isStateCode = true;
        }
    }
    
    //test whether the later characters (if any) are party results
    if (forcast.size() > 2)
    {
        //digit comes first, ends with party code
        if (!isdigit(forcast.at(2)) || !isalpha(forcast.at(forcast.size() - 1)))
        {
            return false;
        }
        else {
            for (int i = 2; i < forcast.size() - 1; i++){
                //all characters have to be either number or letter
                if (!isdigit(forcast.at(i)) && !isalpha(forcast.at(i)))
                {
                    return false;
                }
                //no more than two numbers
                if (isdigit(forcast.at(i)) && isdigit(forcast.at(i+1)) && isdigit(forcast.at(i+2)))
                {
                    return false;
                }
                //at least one number (no letters come together)
                if (isalpha(forcast.at(i)) && isalpha(forcast.at(i+1)))
                {
                    return false;
                }
            }
        }
    }
    
    if (isStateCode == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isValidPollString(string pollData){
    // An empty poll data string is acceptable
    if (pollData.size() == 0)
    {
        return true;
    }
    else
    {
        int CountForcast = -1;
        int ValidForcast = 0;
        string initialPollData = pollData;
        pollData = "," + pollData + ","; // this makes it easier to extract state forcast
        for (int i = 0; i < pollData.size(); i++)
        {
            // A poll data string only have letters, digits, and ","
            if (!isdigit(pollData.at(i)) && !isalpha(pollData.at(i)) && pollData.at(i) != ',')
            {
                return false;
            }
            // if there is more than one forcast, test whether codes between ',' are valid forcasts
            if (pollData.at(i) == ',')
            {
                CountForcast += 1;
                string singleforcast;
                //extract string between ',' and test if it is a valid forcast
                for (int j = i+1; j < pollData.size(); j++)
                {
                    if (pollData.at(j) != ',')
                    {
                        singleforcast += pollData.at(j);
                    }
                    else
                    {
                        break;
                    }
                }
                if (isValidforcast(singleforcast))
                {
                    ValidForcast += 1;
                }
            }
        }
        // if there is only one forcast, test if it is valid
        if (CountForcast == 1) {
            if (isValidforcast(initialPollData))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        // if there is more than one forcast, test whether all of them are valid
        if (CountForcast == ValidForcast)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}


int countSeats(string pollData, char party, int& seatCount){
    //If the parameter pollData is not a poll data string, this function returns 1
    if (!isValidPollString(pollData))
    {
        return 1;
    }
    
    //If the parameter party is not a letter, this function returns 2.
    if (!isalpha(party))
    {
        return 2;
    }
    
    //build a new string with only the party results
    string PartyResults;
    for (int i = 2; i < pollData.size(); i++)
    {
        //state code are the first two characters at the beginning and after the ','
        if (i > 1 && pollData.at(i) != ',' && pollData.at(i-1) != ',' && pollData.at(i-2) != ',')
        {
            PartyResults += pollData.at(i);
        }
    }
    //find total number of the party that we are interested in
    seatCount = 0;
    for (int i = 0; i < PartyResults.size(); i++)
    {
        if (toupper(PartyResults.at(i)) == toupper(party))
        {
            //if there is only one digit, add it to total count
            if (i < 2 || !isdigit(PartyResults.at(i-2)))
            {
                seatCount += int(PartyResults.at(i-1) - '0');
            }
            //if there are two digits, do the multiplication
            else
            {
                seatCount = seatCount + int(PartyResults.at(i-2) - '0') * 10 + int(PartyResults.at(i-1) - '0');
            }
        }
    }
    return 0;
}


