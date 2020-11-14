vec3 vecFill(double x, double y, double z)	//returns a vec3 object with all the data filled
{
	vec3 obj;
	obj.x = x;
	obj.y = y;
	obj.z = z;
	return obj;
}

float DistBetw(float x0, float y0, float x1, float y1)
{
	return sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0));
}


void loadObjModel(const char *filename)
{
	std::ifstream file(filename, std::ios::in);	//making an input stream object
	if (!file)
	{
		std::cerr << "Could not find or open " << filename << std::endl;
		exit(1);	//Exits if the file failed to open
	}
	else
	{
		std::cout << "File: " << filename << " found and opened sucessfully." << std::endl;
	}
	
	/*
	1.Getting each line of the file
	2.Checking for the prefix v->vert f->faces
	3.Pushing the data to the respective vector
	*/
	std::string line;
	while (std::getline(file, line))
	{
		if (line.substr(0, 2) == "v ")
		{
			std::istringstream var(line.substr(2));
			float x, y, z;
			var >> x; var >> y; var >> z;
			vertData.push_back(vecFill(x,y,z));
		}
		if (line.substr(0, 2) == "f ")
		{
			int v1, v2, v3;
			int vt1, vt2, vt3;
			int vn1, vn2, vn3;
			//Here vt and vn are not in use as of now but are parsed for future use
			const char* chh = line.c_str();
			sscanf_s(chh, "f %i/%i/%i %i/%i/%i %i/%i/%i", &v1, &vt1, &vn1, &v2, &vt2, &vn2, &v3, &vt3, &vn3);
			fVertData.push_back(vecFill(v1, v2, v3));
		}
	}
	file.close();
}
