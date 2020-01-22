#include "tlvParser.h"

tlvParser::tlvParser()
{
}

tlvParser::tlvParser(std::vector<std::string> inputCodes)
{

	for (auto&& entry : inputCodes)
	{
		hexCodes.push_back(std::stoul(entry, nullptr, 16));
	}

}

tlvParser::tlvParser(std::vector<int> inputCodes)
{
	hexCodes = inputCodes;
}

void tlvParser::setTagLength(int lengthInBytes)
{
	tagLength = lengthInBytes;
}

void tlvParser::parseTLV()
{
	int tlvCase = 0;
	int lengthCounter;
	int maskBit = 0x80;
	std::vector<int> tempVector;

	for (auto&& hex : hexCodes) // do this with iterator
	{

		switch (tlvCase)
		{
		case 0: // tag

			tagVector.push_back(hex);

			tlvCase = 1;
			break;
		case 1: // Length - need to account for 2 byte value

			// insert MSB check -> two byte width is indicated by 1 in MSB of first byte

			if ((hex & maskBit) == 0)
			{
				lengthVector.push_back(hex);
				tlvCase = 3;
				lengthCounter = 0;
			}
			else
			{
				tlvCase = 2;
				int leastSigBits = ~maskBit & hex;
				lengthVector.push_back(maskBit << leastSigBits);

			}

			break;
		case 2: // Length 2 Bytes
		{

			lengthVector.back() += hex;
			tlvCase = 3;
			lengthCounter = 0;

			break;
		}

		case 3: // Values

			tempVector.push_back(hex);
			lengthCounter++;
			if (lengthCounter == lengthVector.back())
			{
				tlvCase = 0;
				valueVector.push_back(tempVector);
				tempVector.clear();
			}

			break;
		default:
			break;

		}

	}
}

std::vector<int> tlvParser::returnTagVector()
{
	return tagVector;
}

std::vector<int> tlvParser::returnLengthVector()
{
	return lengthVector;
}

std::vector<std::vector<int>> tlvParser::returnValueVector()
{
	return valueVector;
}
