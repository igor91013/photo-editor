#include "UserInteraction.h"

void UserInteraction::start() {
	if (argc == 3) {
		automaticMode();
	}
	else {
		normalMode();
	}

}

void UserInteraction::normalMode() {   
	Image* image = Image::getImage();
	std::string opt;
	while (1) {   
		try {
			std::cout << "\n"
				<< "1. Open...\n"    
				<< "2. Tools\n"              
				<< "3. Export photo\n"      
				<< "4. Save project\n"      
				<< "5. Exit\n"
				<< "Choose an option:\n";
			std::cin >> opt;
			if (opt == "1") {
				openI(*image);                   
			}
			else if (opt == "2") {
				toolsI(*image);                 
			}
			else if (opt == "3") {
				exportI(*image);                
			}
			else if (opt == "4") {         
				saveI(*image);
			}
			else if (opt == "5") {
				exitI(*image);                  
				return;
			}
			else {
				std::cout << "Wrong option chosen, select one of these below:\n";
			}
		}
		catch (Exceptions e) { std::cout<<e.print(); }
		catch (std::exception ex) { std::cout << ex.what(); }
	}
}
/*
void UserInteraction::automaticMode() {
	Image* image = Image::getImage();
	std::string fpath=argv[1], cpath=argv[2], substr;
	
		try {
			
			//fpath = "..\\AutoRegime\\" + fpath;
			substr = fpath.substr(fpath.size() - 3);
			
			//cpath = "..\\Files\\" +cpath;
			Formatter* formatter = nullptr;
			std::cout << fpath << std::endl << cpath << std::endl;
			if (substr == "bmp") {
				formatter = new BmpFormatter();
				image->addLayer(fpath.c_str(), formatter);
			}
			else if (substr == "pam") {
				formatter = new PamFormatter();
				image->addLayer(fpath.c_str(), formatter);
			}
			else if (substr == "myf") {
				formatter = new MyFormatter();
				image->addLayer(new Layer(formatter->read(fpath.c_str())));
			}
			else
				throw std::exception("*** invalid file format");
			//CompositeOperation* cp = CompositeOperation().read(cpath.c_str());
			std::ifstream in(cpath.c_str());
			image->load(in);
			in.close();
			image->applyOperation(image->getOperation());
			Picture pict = image->createPicture();
			
			fpath = fpath.substr(0, fpath.size() - 4) + "(1)." + substr;
			formatter->write(fpath.c_str(), pict);
			return;
			
		}
		catch (Exceptions e) { std::cout << e.print() << '\n'; }
		catch (std::exception ex) { std::cout << ex.what() << '\n'; } 
	
}*/

void UserInteraction::automaticMode() {
	Image* image = Image::getImage();
	std::string fpath = argv[1], cpath = argv[2], substr;

	try {

		substr = fpath.substr(fpath.size() - 3);

		std::cout << fpath << std::endl << cpath << std::endl;
		std::ifstream in(cpath.c_str());
		std::string dummy;
		in >> dummy;
		image->load(in);
		in.close();
		//Picture pict = image->createPicture();
		if (image->getOperation()!=nullptr)
			image->applyOperation(image->getOperation());
		Picture pict = image->createPicture();

		fpath = fpath.substr(0, fpath.size() - 4) + "(1)." + substr;
		BmpFormatter* formatter = new BmpFormatter(true);
		formatter->write(fpath.c_str(), pict);
		delete formatter;
		delete image;
		return;

	}
	catch (Exceptions e) { std::cout << e.print() << '\n'; }
	catch (std::exception ex) { std::cout << ex.what() << '\n'; }

}

void UserInteraction::openI(Image& image) { 
	std::string opt;
	while (1) {
		std::cout << "\nOpen:\n"
			<< "1. Project file\n"   
			<< "2. Bmp file\n"       
			<< "3. Pam file\n"       
			<< "4. MyFormat file\n"
			<< "0. Back\n"           
			<< "Choose an option:\n";
		std::cin >> opt;
		if (opt == "0")
			return;
		else if (opt == "1") {
			std::string opt, name;
			while (1) {
				std::cout << "\nSave current project?\n"
					<< "1. Yes\n"
					<< "2. No\n";
				std::cin >> opt;
				if (opt == "1") {
					saveI(image);
					loadI(image);
					break;
				}
				else if (opt == "2") {
					loadI(image);
					break;
				}
				else
					std::cout << "Wrong option chosen, select one of these below:\n";
			}

		}
		else if (opt == "2") {
			std::string path;
			bool alpha = false;
			std::cout << "\nEnter the name of the file: ";
			std::cin >> path;
			path = "..\\Files\\" + path + ".bmp";
			image.addLayer(path.c_str(), &BmpFormatter());
		}
		else if (opt == "3") {
			std::string path;
			std::cout << "\nEnter the name of the file: ";
			std::cin >> path;
			path = "..\\Files\\" + path + ".pam";
			image.addLayer(path.c_str(), &PamFormatter());
		}
		else if (opt == "4") {
			std::string path;
			std::cout << "\nEnter the name of the file: ";
			std::cin >> path;
			path = "..\\Files\\" + path + ".myf";
			image.addLayer(new Layer(MyFormatter().read(path.c_str())));
		}
		else {
			std::cout << "Wrong option chosen, select one of these below:\n";
		}
	}
}

void UserInteraction::toolsI(Image& image) {
	while (1) {
		try {
			std::string opt;
			std::cout << "\n"
				<< "1. Layers\n"               
				<< "2. Add selection\n" 
				<< "3. Delete selection\n"
				<< "4. Picture operations\n"     
				<< "0. Back\n"                   
				<< "Choose an option\n";
			std::cin >> opt;
			if (opt == "1") {
				layersI(image);
			}
			else if (opt == "2") {
				selecI(image);
			}
			else if (opt == "3") {
				int i = 0;
				int j = 0;
				for (Selection s : image.getSelections()) {
					//std::cout << "selection " << ++i << ":  name: " <<s.getName() << std::endl;
					std::cout << "selection " << ++i << std::endl;
					for (Rectangle r : s.getRectangles()) {
						std::cout <<++j<< ". Rectangle: Row: "<<r.getRow()<<" Col: " << r.getCol() << " Width: " << r.getWidth()<<" Height: " << r.getHeight()<<std::endl;
					}
					j = 0;
				}
				std::cout << "choose which selection you want to delete"<<std::endl;
				std::cin >> i;
				image.deleteSelection(i);
			}
			else if (opt == "4") {
				opI(image);
			}
			else if (opt == "0")
				return;
			else
				std::cout << "Wrong option chosen, select one of these below:\n";
		}
		catch (std::exception e) { e.what(); }

	}

}

void UserInteraction::exportI(Image& image) {
	std::string opt;
	while (1) {
		std::cout << "\nExport as:\n"
			<< "1. BMP\n"            
			<< "2. PAM\n"           
			<< "3. MyFormat\n" 
			<< "0. Back\n"   
			<< "Choose an option:\n";
		std::cin >> opt;
		if (opt == "1") {
			std::string path;
			bool alpha;
			std::cout << "Please enter filename and then 1/0 for yes/no alpha channel: ";
			std::cin >> path >> alpha;
			path = "..\\Files\\" + path + ".bmp";
			image.createPicture();
			BmpFormatter bp;
			bp.setWithAlpha(alpha);
			bp.write(path.c_str(), image.getPicture());
		}
		else if (opt == "2") {
			std::string path;
			std::cout << "Please enter filename: ";
			std::cin >> path;
			path = "..\\Files\\" + path + ".pam";
			image.createPicture();
			PamFormatter().write(path.c_str(), image.getPicture());
		}
		else if (opt == "3") {
			std::string path;
			std::cout << "Please enter filename: ";
			std::cin >> path;
			path = "..\\Files\\" + path + ".myf";
			image.createPicture();
			MyFormatter().write(path.c_str(), image.getPicture());
		}
		else if (opt == "0")
			return;
		else {
			std::cout << "Wrong option chosen, select one of these below:\n";
		}
	}
}

void UserInteraction::layersI(Image& image) {  
	while (1) {
		try {
			std::string opt;
			std::cout << "\n1. Add layer\n"
				<< "2. Delete layer\n"
				<< "3. Set layer as active or visible\n"
				<< "0. Back\n";
			std::cin >> opt;
			if (opt == "1") {
				while (1) {
					try {
						std::cout << "\n"
							<< "1. Add file as a layer\n" 
							<< "2. Add a layer with choosen colour\n" 
							<< "0. Back\n"; 
						std::cin >> opt;
						if (opt == "1") {
							while (1) {
								std::string opt;
								std::cout << "\n"
									<< "1. Bmp\n"
									<< "2. Pam\n"
									<< "3. MyFormat\n"
									<< "0. Back\n";
								std::cin >> opt;
								if (opt == "1") {
									std::string path;
									std::cout << "\nEnter the name of the BMP file: ";
									std::cin >> path;
									path = "..\\Files\\" + path + ".bmp";
									image.addLayer(path.c_str(), &BmpFormatter());
								}
								else if (opt == "2") {
									std::string path;
									std::cout << "\nEnter the name of the PAM file: ";
									std::cin >> path;
									path = "..\\Files\\" + path + ".pam";
									image.addLayer(path.c_str(), &PamFormatter());
								}
								else if (opt == "3")
								{
									std::string path;
									std::cout << "\nEnter the name of the file: ";
									std::cin >> path;
									path = "..\\Files\\" + path + ".myf";
									image.addLayer(new Layer(MyFormatter().read(path.c_str())));
								}
								else if (opt == "0")
									break;
								else
									std::cout << "Wrong option chosen, select one of these below:\n";
							}
						}
						else if (opt == "2") {
							int width, height, red, green, blue, alpha;
							std::cout << "\nPlease enter values for width, height, red, green, blue and alpha respectively\n";
							std::cin >> width >> height >> red >> green >> blue >> alpha;
							image.addLayer(new Layer(new Picture(width, height, Pixel(red, green, blue, alpha))));
							//lazy me should check for correct data here
							std::cout << "Layer added successfully\n";
						}

						else if (opt == "0")
							break;
						else
							std::cout << "Wrong option chosen, select one of these below:\n";
					}
					catch (Exceptions e) { std::cout << e.print(); }
					catch (std::exception e) { e.what(); }
				}
			}
			else if (opt == "2") {
				deleteLayerI(image);
			}
			else if (opt == "3") {
				if (image.getLayers().empty())
					std::cout << "There are no layers at the moment\n";
				else {
					int i = 0, n, a, v;
					std::cout << "Statuses of current layers are: " << std::endl;
					for (Layer* r : image.getLayers())
						std::cout << "Layer " << ++i << ":      active:" << r->isActive() << " visible:" << r->isVisible() << std::endl;
					std::cout << "Select layer number and choose new statuses: " << std::endl;
					std::cin >> n >> a >> v;
					image.getLayers()[n - 1]->setActive(a);
					image.getLayers()[n - 1]->setVisible(v);
				}
			}
			else if (opt == "0")
				return;

			else {
				std::cout << "Wrong option chosen, select one of these below:\n";
			}
		}
		catch (IndexingError i) { i.print(); }
		catch (std::exception e) { std::cout<<e.what(); }
	}
}

void UserInteraction::saveI(Image& image) {
	std::string path;
	std::cout << "\nChoose a name for the file: ";
	std::cin >> path;
	std::ofstream out("..\\SavedProjects\\" + path + ".mp");
	if (!out) throw std::exception("*** File open failed!");
	image.setPath("..\\SavedProjects\\" + path + ".bmp");
	image.save(out, 0);
	out.close();
}

void UserInteraction::loadI(Image& image) {
	std::string path;
	std::cout << "Enter the file name: ";
	std::cin >> path;
	std::ifstream in("..\\SavedProjects\\" + path + ".mp");
	if (!in) throw std::exception("*** File not found!");
	std::string dummy; in >> dummy;
	image.setPath("..\\SavedProjects\\" + path + ".bmp");
	image.load(in);
	in.close();
}

void UserInteraction::selecI(Image& image) {
	size_t sur;   
	int row, col, width, height;
	std::vector<Rectangle> rectangles;
	
	std::string name;
	std::cout << "\nChoose a name for selection\n";
	std::cin >> name;
	std::cout << "\n1. Choose how many surfaces you want to select\n";
	std::cin >> sur;
	
	for (size_t i = 0; i < sur; i++) {
		std::cout << "\nEnter row and column of top-left point for " << i + 1 << ". surface\n";
		std::cin >> row >> col;
		std::cout << "\nEnter width and height for " << i + 1 << ". surface\n";
		std::cin >> width >> height;
		
		Rectangle rec(row, col, width, height);
		rectangles.push_back(rec);
	}
	//Selection s(name, rectangles);
	Selection s(rectangles);
	image.addSelection(s);
}

void UserInteraction::opI(Image& image) {
	CompositeOperation* cp = image.getOperation();
	if (cp == nullptr) image.setOperation(cp = new CompositeOperation());

	while (1) {
		std::string opt;
		std::cout 
			<< "\n"
			<< "1. Add operations\n"
			<< "2. Apply operations\n"
			<< "3. Clear operations container\n"
			<< "4. Apply mediana effect\n"
			<< "5. Export composite function\n"
			<< "0. Back\n";
		std::cin >> opt;
		if (opt == "1") {
			while (1) {
				std::string opt;
				std::cout << "Possible operations are: \n"
					<< "1. Black and White\n"
					<< "2. Grayscale\n"
					<< "3. Inversion\n"
					<< "4. Color selections\n"
					<< "5. Transparency\n"
					<< "6. Brightness\n"
					<< "0. Back\n";
				std::cin >> opt;
				if (opt == "1")
					cp->addOperation(new BlackAndWhite());
				else if (opt == "2")
					cp->addOperation(new Grayscale());
				else if (opt == "3")
					cp->addOperation(new Inversion());
				else if (opt == "4") {
					int red, green, blue, alpha;
					std::cout << "Please enter red, green, blue and alpha values\n";
					std::cin >> red >> green >> blue >> alpha;
					cp->addOperation(new SetPixel(Pixel(red, green, blue, alpha)));
				}
				else if (opt == "5") {
					int value;
					std::cout << "Enter transparency level from 0 to 100\n";
					std::cin >> value;
					cp->addOperation(new Transparency(value));
				}
				else if (opt == "6") {
					int value;
					std::cout << "Enter brightness level from -255 to +255\n";
					std::cin >> value;
					cp->addOperation(new Add(value));
				}
				else if (opt == "0")
					break;

				else
					"Wrong option chosen, select one of these below:\n";
			}
		}
		else if (opt == "2") {
			if (cp->getOperations().empty()) {
				std::cout << "*** no operations added\n";
				break;
			}
			image.applyOperation(cp);
			image.createPicture(); ////////
		}
		else if (opt == "3")
			cp->remove();
		else if (opt == "4") {
			int i = 0;  
			std::cout << "Current layers are: " << std::endl;
			for (Layer* r : image.getLayers())
				std::cout << "Layer " << ++i << ":      active:" << r->isActive() << " visible:" << r->isVisible() << std::endl;
			std::cout << "Choose the layer that you want to apply mediana on\n";
			std::cin >> i;
			
			
			Picture& picture = *(image.getLayers()[i - 1]->getPicture());
			std::vector<Pixel>& pixels = *picture.getPixels();
			Mediana m(picture);
			for_each(pixels.begin(), pixels.end(), [&m](Pixel& p) { m(p); });		
		}
		else if (opt == "5") { 
			std::string name;
			std::cout << "Enter the file name: ";
			std::cin>>name;
			std::ofstream out("..\\Files\\"+name+".fun");
			cp->save(out,0);
		}
		else if (opt == "0")
			return;
		else
			std::cout << "Wrong option chosen, select one of these below:\n";
	}
}

void UserInteraction::deleteLayerI(Image& image) {
	if (image.getLayers().empty()) throw std::exception("*** there are no layers at the moment");
	int i = 0;
	std::cout << "Current layers are: " << std::endl;
	for (Layer* r : image.getLayers())
		std::cout << "Layer " << ++i << ":      active:" << r->isActive() << " visible:" << r->isVisible() << std::endl;
	std::cout << "\nChoose sequence number of the layer you want to delete: " << std::endl;
	std::cin >> i;
	if (i<1 || i>image.getLayers().size()) throw IndexingError();
	image.deleteLayer(i - 1);
	std::cout << "Layer deleted sucessfully" << std::endl;
}

void UserInteraction::exitI(Image& image) {
	std::string opt;
	while (1) {
		std::cout << "\nSave before exit ?\n"
			<< "1. Yes\n"
			<< "2. No\n";
		std::cin >> opt;
		if (opt == "1") {
			saveI(image);
			return;
		}
		else if (opt == "2")
			return;
		else
			std::cout << "Wrong option chosen, select one of these below:\n";
	}
}