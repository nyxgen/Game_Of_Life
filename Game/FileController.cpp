#include "FileController.h"

void FileController::loadStructure(const string& filePath, const shared_ptr<Settings>& settings, const shared_ptr<Board>& board)
{
	boost::filesystem::path p{ filePath };
	boost::filesystem::ifstream ifs{ p };
	unsigned int x = 0, y = 0;
	unsigned int currentPositionX = 0;
	unsigned int currentPositionY = 0;
	char data;
	unsigned int number = 0;

	while (!ifs.eof() && ifs.is_open())
	{
		ifs >> data;
		if (data >= 48 && data <= 57)
		{
			number *= 10;
			number += static_cast<unsigned int>(data) - 48;
		}
		else if (data == 'x')
		{
			ifs >> data;
			if (data == '=')
			{
				ifs >> data;
				while (data != ',')
				{

					x *= 10;
					x += static_cast<unsigned int>(data) - 48;
					ifs >> data;
				}
				if (x > settings->size().x)
					return;

			}

		}
		else if (data == 'y')
		{
			ifs >> data;
			if (data == '=')
			{
				ifs >> data;
				while (data != ',')
				{

					y *= 10;
					y += static_cast<unsigned>(data) - 48;
					ifs >> data;
				}
				if (y > settings->size().y)
					return;
			}
		}
		else if (data == 'b')
		{
			if (number == 0)
				number = 1;
			for (unsigned int i = 0; i < number; ++i)
			{
				if (currentPositionX >= x)
				{
					currentPositionX = 0;
					++currentPositionY;
					if (currentPositionY >= y)
						return;
				}
				try {
					board->alive(currentPositionX, currentPositionY, false);
				}
				catch (exception e) {}
				++currentPositionX;
			}
			number = 0;

		}
		else if (data == 'o')
		{
			if (number == 0)
				number = 1;
			for (unsigned int i = 0; i < number; ++i)
			{
				if (currentPositionX >= x)
				{
					currentPositionX = 0;
					++currentPositionY;
					if (currentPositionY >= y)
						return;
				}
				try {
					board->alive(currentPositionX, currentPositionY, true);
				}
				catch (exception e) {}
				++currentPositionX;

			}
			number = 0;
		}
		else if (data == '$')
		{
			currentPositionX = 0;
			++currentPositionY;
		}
		else if (data == '!')
		{
		}
	}
	settings->loadedStructure(filePath);
}

void FileController::saveStructure(const string& filePath, const bool& overwrite, const bool& readyToLoad, const shared_ptr<Settings>& settings, const shared_ptr<Board>& board)
{
	string filePathCopy = filePath;
	int fileNumber = 0;
	if (!overwrite)
	{
		while (boost::filesystem::exists(filePathCopy + ".rle"))
		{
			fileNumber++;
			filePathCopy = filePath + to_string(fileNumber);
		}
	}
	filePathCopy += ".rle";
	boost::filesystem::path p{ filePathCopy };
	boost::filesystem::ofstream ofs{ p };

	sf::Vector2u size = board->tilesCount();
	sf::Vector2u currentPosition = sf::Vector2u(0, 0);
	int number = 0;
	ofs << "x = " << size.x << ", y = " << size.y << "," << endl;
	for (unsigned int i = 0; i < size.x; i++)
	{
		bool written = false;
		bool lastWrittenAlive = false;
		bool currentAlive = board->tile(0, i)->alive();
		for (unsigned int j = 0; j < size.y; j++)
		{
			if (board->tile(j, i)->alive() != currentAlive)
			{
				currentAlive = !currentAlive;
				if (number != 1)
					ofs << number;
				if (currentAlive)
				{
					ofs << "b";
					lastWrittenAlive = false;
				}
				else
				{
					ofs << "o";
					lastWrittenAlive = true;
				}
				number = 0;
				written = true;

			}
			if (j == size.y - 1)
			{
				if (!written && board->tile(j, i)->alive())
				{
					if (number != 1)
						ofs << number;
					ofs << "o";
					written = true;
				}
			}
			number++;
		}
		number = 0;
		if ((i != size.x - 1))
		{
			ofs << "$";
		}
	}
	ofs << "!";
	if (readyToLoad)
		settings->addFile(filePathCopy);
}
