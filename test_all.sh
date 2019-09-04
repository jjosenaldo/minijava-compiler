#!/bin/bash

for filename in ./code-examples/*;
do
	echo -e "------ TEST --------------------------\nFile: $filename\n";
	./main.out < "$filename";
	echo -e "--------------------------------------\n\n";
done
