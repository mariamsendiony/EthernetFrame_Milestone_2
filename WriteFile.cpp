
#include "EthernetFrame.cpp"
#include "string.h"
/*
Rather than using inheritance in the code, I used aggregation as the ethernet frame is composed of an ecpri and the ecpri is
composed of an ORAN packet. The lifetime of each of them is independant, an ethernet frame can exist without ORAN(with ROE).
*/

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " second_milstone.txt output_file.txt\n";
        return 1;
    }
    // second_milstone.txt output_file.txt
    string inputFileName = argv[1];
    string outputFileName = argv[2];

    // Open input and output files
    ifstream inputFile(inputFileName);
    ofstream outputFile(outputFileName);

    if (!inputFile || !outputFile) {
         cerr << "Error opening files.\n";
        return 1;
    }

    Config Configuration;  
    readConfig(argv[1], Configuration);

    IQsamples iqq;
    vector<IQsamples> iqvalues = readiq("iq_file.txt",iqq);

    EthernetFrame* ef;
    vector<unsigned int>out;
    string packet;
    string IFG="07";
    out=ef->GeneratePacket_Parameters();
    int count=0;
    ofstream myfile( argv[2]); // Create and open a text file
    if (myfile.is_open()) {
        myfile << "Writing this to a file.\n"; // Write to the file
        for(unsigned int i=0;i<out[2];i++){
            ef=new EthernetFrame;
            packet=ef->generate_packet(out[0],iqvalues);
            myfile<<packet<<'\n';
            count++;
            myfile << "Writing this to a file the packet number "<<count<<'\n'; 
        }
    //Writing the IFG at the end into the file
    if(out[1]>0)
    {
        for(unsigned int i=0;i<out[2];i++)
        {
            myfile<<ef->repeatString(IFG,out[1])<<'\n';
        }
    }
        // Close the file
        myfile.close();

        cout << "Data written to output file.\n";
        
    } else {
        cout << "Unable to open file";
    }
    

    return 0;

}