#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <chrono>
using namespace std;
using namespace std::chrono;

#define OUTPUT_MODE 0700

int main(int argc, char** argv)
{
	/* Make sure the command line is correct */
	if(argc < 2)
	{
		cout<<"FILE NAME missing\n";

		exit(1);
	}
  auto start = high_resolution_clock::now();
	/* Open the specified file */
	int fd = open(argv[1], O_RDWR);


	if(fd < 0)
	{
		cout<<"\n"<<"input file cannot be opened"<<"\n";
		exit(1);
	}
	

	// stats.st_size is a variable containing the size of inFile.txt
	struct stat instats;
	if (stat(argv[1], &instats)==0)
      		cout<<endl<<"inFile size "<<instats.st_size;
  	else
	       cout<<"Unable to get file properties.\n";
	       
	       
	/* Get the page size  */
	int pagesize = getpagesize();
	cout<<endl<<"page size is " <<pagesize<<"\n";


	/******************Creation of outFile.txt******************/
	int out_fd = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, OUTPUT_MODE);


	if (out_fd < 0) {
		cout << "\n" << "output file cannot be created" << "\n";
		exit(1);        // if it cannot be created, exit
	}
	
	/* map the file into memory */
	char* in_data = (char*)mmap(NULL, instats.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	// Checks if mapping succeeded 
	if(!in_data)
	{
		cout<<"\n"<<"mapping did not succeed"<<"\n";
		exit(1);
	}
	
	/* file must be same size so memory can be allocated */
	ftruncate(out_fd, instats.st_size);
	/* map the file into memory */
	char* out_data = (char*)mmap(NULL, instats.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, out_fd, 0);
	if(!out_data)
	{
		cout<<"\n"<<"mapping did not succeed"<<"\n";
		exit(1);
	}
	memcpy(out_data, in_data, instats.st_size);


	/*//Print the whole file character-by-character 
	for(int fIndex = 0; fIndex < pagesize; ++fIndex)
	{

		cout<<in_data[fIndex];
		if((fIndex%1000)==1)
		    cout<<endl;
	}
  	cout<<endl;
  	*/
  	
	/* Unmap the shared memory region */
	munmap(in_data, instats.st_size);
	munmap(out_data, instats.st_size);

	/* Close the file */
	close(fd);
	close(out_fd);
	
  	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);

    	cout << "Time taken by function: " << duration.count() << " microseconds" << endl;
	return 0;
}
