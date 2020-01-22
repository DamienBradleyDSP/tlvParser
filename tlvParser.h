#pragma once
#include <string>
#include <vector>

class tlvParser
{
public:
	tlvParser();
	tlvParser(std::vector<std::string> inputCodes);
	tlvParser(std::vector<int> inputCodes);

	void parseTLV();

	std::vector<int> returnTagVector();
	std::vector<int> returnLengthVector();
	std::vector<std::vector<int>> returnValueVector();

private:

	std::vector<int> hexCodes;

	std::vector<int> tagVector;
	std::vector<int> lengthVector;
	std::vector<std::vector<int>> valueVector;
};

