int CountNumberOfSetBitsLoop(int number)
{
	int j = 0; 
	int bit_counter = 0;

	for(j = 0 ; j < 32 ; j++)
	{

		if ((number & 1) == 1)
		{
			bit_counter++;
		}
		number = number >> 1 ;			
	}

	return bit_counter;
}



int CountNumberOfSetBitsBitWise(int number)
{

	number = number - ((number >> 1) & 1431655765);
	number = (number & 858993459) + ((number >> 2) & 858993459);
	number = (number + (number >> 4)) & 252645135;
	number = number + (number >> 8);
	number = number + (number >> 16);
	number = number & 63;
	return number;
}



void PrintFloatToBinary(float number)
{
	int j = 0; 
	union FloatUnion print_bits = {0};
	int binaryRepresentation = 0;
	print_bits.f = number; 
	binaryRepresentation = print_bits.i;
	
	for(j = 0 ; j < 32 ; j++) 
	{
  		printf("%d", (binaryRepresentation >> j) & 1);
	}
		
}

		
