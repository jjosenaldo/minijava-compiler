for filename in ./code-examples/*; do
	echo -e "------ TEST --------------------------\nFile: $filename\n";
	./bin/main.out < "$filename";
	echo -e "--------------------------------------\n\n";
done
