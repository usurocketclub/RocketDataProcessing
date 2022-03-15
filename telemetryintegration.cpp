#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

int main(){
	string arduinomilli, year, month, day, hour, minute, second, millisecond, xa, ya, za, xg, yg, zg, xang, yang, zang, xm, ym, zm, filewritemillis;
	vector<float> arduinomillis;
	vector<float> minutes;
	vector<float> seconds;
	vector<float> milliseconds;
	vector<float> xAcc;
	vector<float> yAcc;
	vector<float> zAcc;
	vector<float> xGyro;
	vector<float> yGyro;
	vector<float> zGyro;
	vector<float> xAngle;
	vector<float> yAngle;
	vector<float> zAngle;

	const float pi = 3.14159; // Used to convert angles to radians as needed 

	string fileName;
	cout << "Enter file name: ";
	cin >> fileName;

	int i = 0;
	int k = 0;
	float min = 0;

	ifstream data(fileName);
	if (data.is_open()) {
		string line;
	
		getline(data, line);
	

		while(!data.eof()) {
			getline(data,arduinomilli, ',');
			float arduinomillif = stof(arduinomilli);
			getline(data,year, ',');
			getline(data,month, ',');
			getline(data,day, ',');
			getline(data,hour, ',');
			getline(data,minute, ',');
			float minutef = stof(minute);
			if ((minutef == min) || (minutef == min+1)){
				arduinomillis.push_back(arduinomillif);
				minutes.push_back(minutef);
				getline(data,second, ',');
				float secondf = stof(second);
				seconds.push_back(secondf);
				getline(data,millisecond, ',');
				float millisecondf = stof(millisecond);
				milliseconds.push_back(millisecondf);
				getline(data,xa, ',');
				float xaf = stof(xa); 
				xAcc.push_back(xaf);
				getline(data,ya, ',');
				float yaf = stof(ya); 
				yAcc.push_back(yaf);
				getline(data,za, ',');
				float zaf = stof(za);
				zAcc.push_back(zaf);
				getline(data,xg, ',');
				float xgf = stof(xg);
				xGyro.push_back(xgf);
				getline(data,yg, ',');
				float ygf = stof(yg);
				yGyro.push_back(ygf);
				getline(data,zg, ',');
				float zgf = stof(zg);
				zGyro.push_back(zgf);
				getline(data,xang, ',');
				float xangf = stof(xang); 
				xAngle.push_back(xangf);
				getline(data,yang, ',');
				float yangf = stof(yang);
				yAngle.push_back(yangf);
				getline(data,zang, ',');
				float zangf = stof(zang);
				zAngle.push_back(zangf);
				getline(data,xm, ',');
				getline(data,ym, ',');
				getline(data,zm, ',');
				getline(data,filewritemillis, '\n');
				min = minutef;
			}
			else{
				getline(data,second, ',');
				getline(data,millisecond, ',');
				getline(data,xa, ',');
				getline(data,ya, ',');
				getline(data,za, ',');
				getline(data,xg, ',');
				getline(data,yg, ',');
				getline(data,zg, ',');
				getline(data,xang, ',');
				getline(data,yang, ',');
				getline(data,zang, ',');
				getline(data,xm, ',');
				getline(data,ym, ',');
				getline(data,zm, ',');
				getline(data,filewritemillis, '\n');
				k += 1;
			}
			i += 1;	
		}

		data.close();
		cout << "Number of entries: " << i - 1 << endl;
	}
	else{
		cout << "Unable to open the file.";
	}
	
	cout << "Number of truncations: " << k;
	for (int a = 0; a < i-1; a++){
		xAcc[a] = xAcc[a]*16*9.8/32768;
		yAcc[a] = yAcc[a]*16*9.8/32768;
		zAcc[a] = zAcc[a]*16*9.8/32768;
		xGyro[a] = xGyro[a]*2000/32768;
		yGyro[a] = yGyro[a]*2000/32768;
		zGyro[a] = zGyro[a]*2000/32768;
	}

	ofstream outputFile;
  	outputFile.open ("rocketdatafiltered.txt");
 	if(outputFile.is_open()){
 		outputFile << "Arduinomillis" << "," << "Minutes" << "," << "Seconds" << "," << "Milliseconds" << "," << "xAcc" << "," << "yAcc" << "," << "zAcc" << "," << "xGyro" << "," << "yGyro" << "," << "zGyro" << endl;
		for(int b = 0; b < i-1; b++){
			outputFile << arduinomillis[b] << minutes[b] << "," << seconds[b] << "," << milliseconds[b] << "," << xAcc[b] << "," << yAcc[b] << "," << zAcc[b] << "," << xGyro[b] << "," << yGyro[b] << "," << zGyro[b] << endl;
		}
	}
  	outputFile.close();

	return 0;
}

