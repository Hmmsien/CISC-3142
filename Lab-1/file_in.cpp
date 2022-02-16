//Huimin Chen
//CISC-3142
//Lab 1

/* Homework Objective: fix this program to match the requirements listed: 
  1. successfully reads all lines of the input file
  2. calculate the average price per brand, average price per category 
  3. writes to an output file
  4. for each unique year, list the count of skus and also print out the skus as a list i.e. 2000 (3): 111, 211, 311 and make a new line per year.
*/

#include <iostream>
#include <iterator>
#include <fstream>
#include <map>
#include <numeric>
#include <sstream>
#include <vector>
using namespace std;

//replace all "," to space
void replace(string&line, char at, char with) {
    for(int i=0; i<line.length(); i++) {
        if(line[i] == at)  
            line[i] = with;
    }
}

//calculate the average price per brand
// This function calculates the average prices per brand
void calculateAveragePerBrand(vector<string> vBrand, vector<float> vPrice, ofstream& out_stream)
{
    // Declaring a map to store the prices band wise
    map<string,vector<float> > brandMap;
    
    // Storing the prices band wise
    for(int i = 0; i < vBrand.size(); i++)
    {
        brandMap[vBrand[i]].push_back(vPrice[i]);
    }

    // Writing the headers to the output file
    out_stream << "\tBrand\tAverage\n";
    
    // Declaring an iterator for map to iterate over the map
    map<string,vector<float> >::iterator it;
    
    // Iterating over the map
    for(it = brandMap.begin(); it != brandMap.end(); ++it)
    {
        // Storing the current brand
        string curBrand = it->first;
        // Storing the prices of current brand
        vector<float> curPrices = it->second;
        // Storing the sum of prices of current brand
        float brandSum = accumulate(curPrices.begin(), curPrices.end(),0.0);
        // Calculating the average of prices of current brand
        float average = brandSum / curPrices.size();
        
        // Writing the brand name and it's average to the output file
        out_stream << "\t" << curBrand << "\t" << average << "\n";
    }
    // Writing a newline to the output file
    out_stream << endl;
}

// This function calculates the average prices per category
void calculateAveragePerCategory(vector<string> vCategory, vector<float> vPrice, ofstream& out_stream)
{
    // Declaring a map to store the prices category wise
    map<string,vector<float> > categoryMap;
    // Storing the prices category wise
    for(int i = 0; i < vCategory.size(); i++)
    {
        categoryMap[vCategory[i]].push_back(vPrice[i]);
    }

    // Writing the headers to the output file
    out_stream << "\tCategory\tAverage\n";
    
    // Declaring an iterator for map to iterate over the map
    map<string,vector<float> >::iterator it;
    
    // Iterating over the map
    for(it = categoryMap.begin(); it != categoryMap.end(); it++)
    {
        // Storing the current category
        string curCategory = it->first;
        // Storing the prices of current category
        vector<float> curPrices = it->second;
        // Storing the sum of prices of current category
        float brandSum = accumulate(curPrices.begin(), curPrices.end(),0.0);
        // Calculating the average of prices of current category
        float average = brandSum / curPrices.size();

        // Writing the category name and it's average to the output file
        out_stream << "\t" << curCategory << "\t" << average << "\n";
    }
    // Writing a newline to the output file
    out_stream << endl;
}

void calculateSKUCount(vector<int> vYear,vector<int> vSKU, ofstream& out_stream)
{
    // Declaring a map to store the sku's year wise
    map<int,vector<int> > yearMap;
    
    // Storing the sku's band wise
    for(int i = 0; i < vYear.size(); i++)
    {
        yearMap[vYear[i]].push_back(vSKU[i]);
    }

    // Writing the headers to the output file
    out_stream << "\tYear\tSKU's\n";
    
    // Declaring an iterator for map to iterate over the map
    map<int,vector<int> >::iterator it;
    
    // Iterating over the map
    for(it = yearMap.begin(); it != yearMap.end(); it++)
    {
        // Writing the year to the output file
        out_stream << it->first << "\t";

        // Declaring an iterator to iterate over the vector for the current year
        vector<int>::iterator sku_it;

        // Iterating over sku's for current year
        for(sku_it = it->second.begin(); sku_it != it->second.end(); sku_it++)
        {
            // Writing the sku to the output file
            out_stream << *sku_it;

            // If this is not the last sku for current year, write a space to the output file
            if(sku_it != it->second.end())
            {
                out_stream << " ";
            }
            // Else, write a tab to the output file
            else
            {
                out_stream << "\t";
            }
        }
        // Writing the number of sku's for current year to the output file
        out_stream << "(Count: " << it->second.size() << ")" << endl;
    }
}

int main() {
     // define variables
    int SKU;
    string brand;
    string category;
    int year;
    float price;
    vector<int> vSKU;
    vector<string> vBrand;
    vector<string> vCategory;
    vector<int> vYear;
    vector<float> vPrice;

    //read data from file
    ifstream in_stream;
    //write data to file
    ofstream out_stream;

    //opening the input and output file
    in_stream.open("data.csv");
    out_stream.open("output.txt");

    //if file open
    if(!in_stream.fail()) {
        //store current line that read from file
        string line;

        // Reading the header line but not using it, because it is not needed
        getline(in_stream,line);

        //read all data from file until end
        while(getline(in_stream,line)) {
            
            // Replacing commas with spaces
            replace(line,',',' ');

            //store line to the ss object
            stringstream ss(line);

            //store values from each column for current row
            ss>>SKU;
            ss>>brand;
            ss>>category;
            ss>>year;
            ss>>price;

            //write value into vector
            vSKU.push_back(SKU);
            vBrand.push_back(brand);
            vCategory.push_back(category);
            vYear.push_back(year);
            vPrice.push_back(price);
        }//close file
        in_stream.close();
    }else
    {
        out_stream<<"Unable to open file";
    }

    //write value to output file 
    out_stream << "SKU" << "\t" << "Brand" << "\t" << "Category"<< "\t" << "Year" << "\t" << "Price" << endl;

    // Writing rows read to the output file
    for (int j = 0; j < vSKU.size(); j++)   {
        out_stream << vSKU[j] << "\t" << vBrand[j] << "\t" << vCategory[j] << "\t" << vYear[j] << "\t" << vPrice[j] << endl;
    }// Writing a newline to the output file
    out_stream << endl;
    
    // Calculating the average price per brand and storing them in the output file
    calculateAveragePerBrand(vBrand,vPrice,out_stream);
    
    // Calculating the average price per category and storing them in the output file
    calculateAveragePerCategory(vCategory,vPrice,out_stream);

    // Calculating the SKU count for each year and storing them in the output file
    calculateSKUCount(vYear,vSKU, out_stream);
    
    // Closing the input and output files
    in_stream.close();
    out_stream.close();
}
