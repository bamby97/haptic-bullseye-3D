#include "Logger.h"

Logger::Logger()
{
	this->info.throwNumber = 0;
	info.hitTarget = false;
	info.timeRemaining = -1.0;
	info.projectilePosition[0] = -1.0;
	info.projectilePosition[1] = -1.0;
	info.projectilePosition[2] = -1.0;
	info.projectileVelocity[0] = -1.0;
	info.projectileVelocity[1] = -1.0;
	info.projectileVelocity[2] = -1.0;
	info.targetDepth = 100.0;

	info.addedScore = 0;
	info.targetHit = 0;
	totalScore = -1;
	frameCount = 0.0f;

	myfile.open("Logger.txt", ios::out | ios::app);
	myfile << "--------------------------------------------------------------------------------------------------------\n";
	myfile.close();
}

void Logger::pushInfo()
{
	gameData.push_back(info);
	
	// clear logged values to default values
	info.hitTarget = false;
	info.timeRemaining = -1.0;
	info.targetDepth = 100.0;
	info.addedScore = 0;
	info.targetHit = 0;
}

void Logger::printInfo()
{
	myfile.open("Logger.txt", ios::out | ios::app);
	myfile << "Throw Number\t Hit Target\t Time Elapsed\t Target Position\t Added Score\t Target Hit\t Projectile Position\t\t  Projectile Velocity \n";

	for (int i = 0; i < gameData.size(); i++)
	{
		myfile << gameData.at(i).throwNumber << "\t\t "
			   << gameData.at(i).hitTarget << "\t\t "
			   << fixed << setprecision(2) << 60.00f - gameData.at(i).timeRemaining << "\t\t "
			   << gameData.at(i).targetDepth << "\t\t\t "
			   << gameData.at(i).addedScore << "\t\t "
			   << gameData.at(i).targetHit << "\t\t "
			   << setprecision(2) << gameData.at(i).projectilePosition[0] << " " 
			   << setprecision(2) << gameData.at(i).projectilePosition[1] << " " 
			   << setprecision(2) << gameData.at(i).projectilePosition[2] << "\t\t "
			   << setprecision(2) << gameData.at(i).projectileVelocity[0] << " "
			   << setprecision(2) << gameData.at(i).projectileVelocity[1] << " "
			   << setprecision(2) << gameData.at(i).projectileVelocity[2] << "\n";

		myfile.flush();
	}

	myfile << "Total Score\n";
	myfile << totalScore <<"\n";
	myfile << "Average Frames per Second\n";
	myfile << fixed << setprecision(2) << frameCount/60.0f << "\n";
	myfile.close();
}

void Logger::setTotalScore(int score)
{
	totalScore = score;
}

void Logger::setFrameCount(float count)
{
	frameCount = count;
}

