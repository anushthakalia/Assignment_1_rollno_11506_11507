#include<iostream>
#include<fstream>
#include<string.h>
#include <cstring>

using namespace std;
// the function pattern(pat,f) will give the array of the pattern has to be searched for
int *pattern(string pat,int f[]) {
	//length of pattern
	int len=pat.length();
	f[0]=0;//initialising first element of the array to 0
	int i=0;// i,j are counters of the pattern 
	for (int j=1;j<len;j++) {
		//if char at i and j are equal
		if (pat[i]==pat[j]) {

			f[j]=i+1;
			i++;

		}	else {
		//if char at i and j are not equal
		//if i is not at 0
			while (i>0) {
				i=f[i-1];
				if (pat[i]==pat[j]) {

         			f[j]=i+1;
          			i++;
          			break;
        		}


			}// if i is at 0
			if (i==0) {
        		f[j]=i;
        	}


		}    
    }// f is the array of pattern
    return f;
}
// This function returns 1 if pattern is found in the text otherwise , it returns 0
int substring_find (string text,string pat,int f[]){

	int k=text.length();
	int m=pat.length();
	int i=0;// i is the counter for pattern
	int j=0;// j is the counter for text
	int flag=0;// flag is set to 1 if pattern is found in text, otherwise it is 0

	while (j<k){
		//if characters of pattern and text match,then both i and j are incremented
		if (pat[i]==text[j]){
			i++;
			j++;
			if(i==m){
				flag=1;
				break;
			}

		
		} else if (pat[i]!=text[j] && i==0) {
			//if characters don't match and counter of pattern is 0, j is incremented

			j++;
			if (j==k) flag=0;

		} else if (pat[i]!=text[j]) {
			//if characters don't match,then i is set to the value of ith element in pattern array
			i=f[i-1];

		}
                  
    }
    return flag;
}
//This is the function which calls pattern and substring_find function
char KMP(string text,string pat){
	char a='a';// if pattern is found in text, b is assigned as a otherwise value of a is unchanged
	int f[pat.length()];
	int *final;
	//calling the pattern function, which return pointer to the array of pattern
	final=pattern(pat,f);
	//it tells whether pat has been found in text or not
	int s=substring_find(text,pat,final);
	// if flag is 1, pat has been found in text and value of a is now b.
	if (s==1) a='b';
	return a;
}

// function for finding a particular text in a file
void DictionarySearch(string filename,string pattern, char option){
	ifstream object1;              //declaring an object for reading the text file

	object1.open(filename.c_str());//opening the txt file
    if (!object1.is_open()){
		cout<<"error";
    }
	char letter;// the charcter which will loop through all characters of the file.

	int i=0;// counter of word

	int char_count=0;// counts number of characters in txt file

	float word_match_count=0;//initialising the variable for number of words in which the pattern has been found

	float word_count=0;//initialising the variable for number of words in text file

	char word[20];// array in which the text is stored

	int char_position=0;// position of the text
	while (object1.get(letter)) {
		char_count++;
		if (letter==' '|| letter=='\n'|| letter=='.'|| letter==','|| letter=='"') {//a blank space or \n signify end of a word
			word_count++;

			string word1=string(word);
			char a=KMP(word1,pattern);// running KMP on the word1(the text) and pattern
      
      		if (a=='b') {//if pattern is found in word1, then a will be b, and that text will be outputted
      	  	
           		word_match_count++;
           		cout<<pattern +" found in "+string (word)+" at position ";
           		cout<<char_position<<endl;
      	  	}
 
      		i=0;// setting counter of word again to 0
     
      		for (int j=0;j<20;j++) {
        
      			word[j]='\0';// setting each element in word to  null
      		}

       
		} else {
    		if (i==0) {
        		char_position=char_count; 
    		}
    		word[i]=letter;//storing characters in word array
			i++;
    	}	       
	}
	// probabilty of findig the pattern in the text file is given by matched words/total words
	if (option=='y') {
	cout<<endl;
	cout<<"The probability of finding "<< pattern<<" is "<< word_match_count/word_count<<endl;
	cout<<endl;
	}
          
}

void para_count(string filename){
	ifstream myfile;// reading the file
	int count=1;
	myfile.open(filename.c_str());//opening the file
    if (!myfile.is_open()) { 
		cout<<"error";
    }
	char word;

	while (myfile.get(word)) {//for each character till end of file
		if (word=='\n') {
			count++;//  if \n is encountered(signifying a new paragraph) count is incremented
		}
		
	}
	cout<<"The number of paragraphs in the text are: "<<count<<endl;
	cout<<endl;
    myfile.close();// closing the file
}

 

int main() {
	int choice;
	char n='\0';
	string filename;
	while (n!='n') {
		    

		cout<<"                   Menu                       "<<endl;
		cout<<"********************************************"<<endl;
		
		cout<<"1. To find number of paragraphs in the text"<<endl;
		cout<<"2. To find a particular string in the text "<<endl;
		cout<<"********************************************"<<endl;
		cout<<endl;
		cout<<"Enter the filename along with its extension: ";
		cin>>filename;//input for filename
	    cout<<endl;
		cout<<"Enter your choice--> ";
	    cin>>choice;
		switch (choice) {
			case 1:
			{
			 	para_count(filename);//function for finding number of paragraphs
				break;
			}
			case 2:
			{
			  	string pattern;
		        char option='\0';
		        cout<<endl;
		        cout<<"Enter the pattern you want to search for: ";
		        cin>>pattern;
		        cout<<endl;
		        cout<<"Do you want to find the probabilty of finding the pattern in the text file? y or n ? -> ";
		        cin>>option;
		        cout<<endl;
                DictionarySearch(filename,pattern,option);//function for finding a pattern in the text file
        		break;
        	}
        	default:
        		cout<<"Enter a valid choice!"<<endl;
       

		}
		cout<<"Do you want to continue? y or n -> ";
		cin>>n;
	}



}






