#include "pch.h"
#include "localGame.h"
#include <windows.h>

#include "shallow.h"// test objecttttttttttttttttttttttttttttttttttt


LocalGame::LocalGame()
{
	kamera = Camera(sf::Vector2f(1024, 768));

	this->loadMap();

	sf::ConvexShape defaultShape;
	defaultShape.setPointCount(3);
	defaultShape.setPoint(0, sf::Vector2f(15,0));
	defaultShape.setPoint(1, sf::Vector2f(30,30));
	defaultShape.setPoint(2, sf::Vector2f(0,30));

	bulletData.push_back(std::pair<std::string, Bullet>("test", Bullet("test", defaultShape, 10, 10,10)));

	if (!this->loadGameFiles())throw 'E';

	this->window = std::make_shared<sf::RenderWindow>(gameInfo.resolution, "Scharnhorst");
	this->window->setFramerateLimit(65);
	this->player = std::make_shared<Player>(1, playerName, "KMS Scharnhorst");
	
	inSocket.bind(sf::Socket::AnyPort);
	inSocket.setBlocking(false);
}

LocalGame::LocalGame(std::string playerName, std::string shipType) : LocalGame()
{
	this->playerName = playerName;
	this->player->setShip(this->findShip(shipType));
	this->shipType = shipType;
	this->player = std::make_shared<Player>(1, playerName, "KMS Scharnhorst");
}

void LocalGame::gameLoop()
{

	std::shared_ptr <std::vector<std::shared_ptr<sf::Vector2f>>> tpoints = std::make_shared<std::vector<std::shared_ptr<sf::Vector2f>>>();

	tpoints->push_back(std::make_shared<sf::Vector2f>(sf::Vector2f(-300, -300)));
	tpoints->push_back(std::make_shared<sf::Vector2f>(sf::Vector2f(300, -300)));
	tpoints->push_back(std::make_shared<sf::Vector2f>(sf::Vector2f(300, 300)));
	tpoints->push_back(std::make_shared<sf::Vector2f>(sf::Vector2f(-300, 300)));
	this->maps.push_back(std::make_shared<map>());
	this->actualMap = maps[0];
	this->actualMap->addIsland(std::make_shared<shallow> (tpoints, 0, &textures));
	//this->actualMap->islands[0]->setFillColor(sf::Color(200, 0, 200));
	this->actualMap->islands[0]->setPosition(sf::Vector2f(1000, 1000));
	
	

	this->player->setShip(this->findShip(this->shipType));

	sf::Music backgroundMusic;
	backgroundMusic.openFromFile("gamedata/music/background1.flac");
	backgroundMusic.setLoop(true);
	backgroundMusic.setVolume(50);
	backgroundMusic.play();

	sf::Clock time;
	time.restart();

	this->connectionClock.restart();
	double deltaTime;

	//GUI
	sf::Font guiFont;
	guiFont.loadFromFile("gamedata/fonts/PressStart2P.ttf");
	sf::View guiView = window->getView();
	sf::RenderTexture guiTexture;
	guiTexture.create(unsigned int(this->window->getSize().x), unsigned int(this->window->getSize().y));

	std::vector<sf::Text> guiContent;

	sf::Text messageText;
	messageText.setFont(guiFont);
	messageText.setFillColor(sf::Color::Green);
	messageText.setPosition(sf::Vector2f(0,700));
	messageText.setCharacterSize(20);

	guiContent.resize(25);
	guiContent[0]=sf::Text("HP",guiFont);
	guiContent[1]=sf::Text("SPEED",guiFont);
	guiContent[1].setPosition(sf::Vector2f(0,30));
	guiContent[2]=sf::Text("GEAR", guiFont);
	guiContent[2].setPosition(sf::Vector2f(0, 60));

	for (unsigned int i = 3; i < 25; i++)
	{
		guiContent[i].setFont(guiFont);
		guiContent[i].setCharacterSize(15);
		guiContent[i].setPosition(sf::Vector2f((i-3)*100,guiView.getSize().y - 40));
	}
	for (auto & player : otherPlayers)
	{
		player->calculateHPindicator();
	}


	while (window->isOpen() && !endFlag)
	{
		/*if ((this->actualMap->islands[0]->touch(&(this->player->getShip()->hitbox[0]))) || (this->actualMap->islands[0]->touch(&(this->player->getShip()->hitbox[1]))))
		{
			std::cout << "xd" << std::endl;
		}*/
		
		

		if (connectionClock.getElapsedTime().asSeconds() > 100)
		{
			std::cout << "lost connection to server" << std::endl;
			return;
		}
		deltaTime = time.restart().asSeconds()*stalaCzasowa;
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::MouseWheelScrolled)
			{
				kamera.addZoom(event.mouseWheelScroll.delta / 10);
			}
			if (event.type == sf::Event::Resized)
			{
				kamera.view.setSize(sf::Vector2f(this->window->getSize().x, this->window->getSize().y));
				kamera.setDimensions(sf::Vector2f(this->window->getSize()));
			}
			if (event.type == sf::Event::Closed)window->close();
		}

		if(window->hasFocus())this->playerEvent(deltaTime);
		this->sendPlayerPosition(); //wysy�a pozycje i dane gracza
		this->receiveTCP();//odbiera rozkazy TCP
		this->recieveUDP(); //odbiera wiadomo�ci TCP
		this->player->sendBullets(this->TCPsocket);//wysyła dane o bulletach które stworzył gracz

		player->setAngleOfView(kamera.angle);
		this->player->mainPlayerDoStuff(deltaTime, this->actualMap);

		for (auto & player : otherPlayers)
		{
			player->doStuff(deltaTime);
		}
		for (auto & bullet : bullets)
		{
			bullet.fly(deltaTime);
		}



		kamera.setCenter(player->getShip()->getPosition());
		kamera.calculateView(*window, 8);
		kamera.setView(*window);

		window->clear();
		//DRAWING

		auto view = kamera.getViewBounds();
		for (const auto & vector : backgroundMap)
		{
			for (const auto & shape : vector)
			{
				auto object = shape.getGlobalBounds();
				if (object.intersects(view))
				{
					window->draw(shape);
				}
			}
		}

		


		for (auto & wreckage : wreckages)
		{
			wreckage->draw(*window);
		}

		player->draw(*window);
		for (const auto & player : otherPlayers)
		{
			player->draw(*window);
		}

		auto cameraView = kamera.getViewBounds();
		for (auto & bullet : bullets)
		{
			if(cameraView.contains(bullet.getPosition()))bullet.draw(*this->window);
		}
		//GUI

		guiTexture.clear(sf::Color::Transparent);
		this->player->updateGui(guiContent, guiView);
		this->calculatePlayerList(guiContent);
		for (auto & content : guiContent)
		{
			guiTexture.draw(content);
		}
		guiTexture.draw(messageText);


		
		//test.draw(*window);
		this->actualMap->draw(*window);
	
		//wyspa
		//this->actualMap->islands[0]->drawHitbox(*window);
		


		guiTexture.display();
		sf::Sprite gui(guiTexture.getTexture());

		window->setView(guiView);
		window->draw(gui);
		

		window->display();
	}  
}

void LocalGame::playerEvent(const double &deltaTime)
{
	if (player == nullptr)return;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		if (this->isWClicked == 0)
		{
			player->getShip()->changeGear(1);
			this->isWClicked = 1;
		}
	}
	else
	{
		this->isWClicked = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		if (this->isSClicked == 0)
		{
			player->getShip()->changeGear(0);
			isSClicked = 1;
		}
	}
	else
	{
		isSClicked = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		player->getShip()->spin(0, deltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		player->getShip()->spin(1, deltaTime);
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		player->shoot();
	}

}

std::shared_ptr<Player> LocalGame::getPlayerById(unsigned int searchedId)
{
	auto x =std::find_if(otherPlayers.begin(), otherPlayers.end(), [&searchedId](std::shared_ptr<Player> &player) {return player->getPlayerId() == searchedId; });
	if (x != otherPlayers.end())
	{
		return *x;
	}
	else if (this->player->getPlayerId() == searchedId)return this->player;
	else return nullptr;
}

bool LocalGame::joinServer()
{
	std::string IP;
	std::cout << "type server IP and port" << std::endl;
	std::cin >> IP;
	if (IP == "single")return 1;
	TCPsocket.setBlocking(true);

	if (connectToServer(IP) == false)return 0;

	sf::Packet newPlayerPacket;
	newPlayerPacket << "PLA" << unsigned int(0) << this->playerName << this->shipType << this->player->getShip()->getName();

	TCPsocket.send(newPlayerPacket);
	newPlayerPacket.clear();

	sf::Clock connectionClock;
	connectionClock.restart();
	std::string receivedMessage;
	while (connectionClock.getElapsedTime().asSeconds() < 10)
	{
		TCPsocket.receive(newPlayerPacket);
		if (newPlayerPacket >> receivedMessage)
		{
			if (receivedMessage == "PLJ")
			{
				std::string newPlayerName = "error";
				unsigned int id = 0;
				float x, y, angle = 0;
				newPlayerPacket >> id;
				newPlayerPacket >> newPlayerName;
				std::cout << "received PLJ : " << id << ' ' << newPlayerName << std::endl;
				player = std::make_shared<Player>(id, newPlayerName);
				newPlayerPacket >> x;
				newPlayerPacket >> y;
				newPlayerPacket >> angle;
				std::cout << "receiving player position : " << x << ' ' << y << std::endl;

				player->getShip()->setPosition(sf::Vector2f(x, y));
				player->getShip()->setRotation(angle);
				std::cout << "joined game succesfully" << std::endl;
				return 1;
			}
			else
			{
				receivedMessage.clear();
			}
		}
	}
	std::cout << "could not create new player on server" << std::endl;
	return 0;
}

void LocalGame::printAdresses()
{
	std::cout << "TCP client working on: " << sf::IpAddress::getLocalAddress() << ':' << TCPsocket.getLocalPort() << std::endl;
	std::cout << "UDP client working on: " << sf::IpAddress::getLocalAddress() << ':' << inSocket.getLocalPort() << std::endl;
	std::cout << "UDP server working on: " << serverInfo.serverAddress << ':' << serverInfo.serverUdpPort << std::endl;
}

bool LocalGame::inView(sf::Vector2f pos)
{
	return false;
}


bool LocalGame::loadBullets()
{
	std::fstream in("gamedata/bullets.dat");
	if (!in.good())	return 0;

	std::string name,endWord;
	unsigned int pointCount;
	float x, y;
	float speed, damage,caliber;

	while (true)
	{
		endWord = "ERR";

		std::getline(in, name);

		in >> pointCount;

		in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		sf::ConvexShape bulletShape;
		bulletShape.setPointCount(pointCount);
		bulletShape.setFillColor(sf::Color::Red);
		
		for (unsigned int i = 0; i < pointCount; i++)
		{
			in >> x;
			in >> y;
			bulletShape.setPoint(i,sf::Vector2f(x,y));
			in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		//Origin
		in >> x;
		in >> y;
		bulletShape.setOrigin(x,y);
		in >> speed;
		in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		in >> damage;
		in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		in >> caliber;
		in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::getline(in, endWord);
		
		if (endWord != "END_BULLET")break;
		bulletData.push_back(std::pair<std::string,Bullet>(name,Bullet(name,bulletShape, speed, damage,caliber)));
	}
	in.close();
	return 1;
}
bool LocalGame::loadBarrels()
{
	std::fstream in("gamedata/barrels.dat");
	if (!in.good())	return 0;

	std::string name, mainBulletType, endWord;
	unsigned int point_count, caliber;
	while (!in.eof())
	{
		std::shared_ptr<Barrel> newBarrel;

		unsigned int pointCount = 0;
		float x, y;
		float reloadTime;
		sf::ConvexShape barrelShape;
		barrelShape.setFillColor(sf::Color::Blue);

		std::getline(in, name);//nazwa
		std::getline(in, mainBulletType);//nazwa pocisku
		in >> caliber;//kaliber
		in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		in >> reloadTime;//kaliber
		in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		in >> pointCount;//ilość punktów
		in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		barrelShape.setPointCount(pointCount);

		float maxx=0, maxy=0;//używane do znalezienia originu

		for (unsigned int i = 0; i < pointCount; i++)//punkty
		{
			in >> x;
			in >> y;

			barrelShape.setPoint(i, sf::Vector2f(x, y));
			in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			if (x > maxx)maxx = x;
			if (y > maxy)maxy = y;
		}
		barrelShape.setOrigin(sf::Vector2f(maxx/2,0));


		std::getline(in, endWord);//2 razy bo musi przeskoczyć do następnej lini
		if (endWord != "END_BARREL")return 0;
		barrelData.push_back(std::pair<std::string,Barrel>(name, Barrel(name, sf::Vector2f(0, 0), barrelShape, findBullet(mainBulletType), caliber,reloadTime)));
		barrelData.back().second.length = maxy;
	}
	in.close();
	return 1;
}
bool LocalGame::loadTurrets()
{
	std::fstream in("gamedata/turrets.dat");
	if (!in.good())return 0;

	std::string name, cannonType, endWord;
	unsigned int point_count;
	while (!in.eof())
	{
		endWord = "ERR";
		std::shared_ptr<Turret> newTurret;

		unsigned int pointCount = 0;
		float x, y;
		sf::ConvexShape turretShape;
		
		turretShape.setFillColor(sf::Color::Red);

		std::getline(in, name);//nazwa

		in >> pointCount;//ilość punktów
		in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		turretShape.setPointCount(pointCount);
		for (unsigned int i = 0; i < pointCount; i++)//punkty
		{
			in >> x;
			in >> y;
			turretShape.setPoint(i, sf::Vector2f(x, y));
			in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		in >> x;
		in >> y;
		turretShape.setOrigin(sf::Vector2f(x,y));//origin

		float parameters[3];
		in >> parameters[0];
		in >> parameters[1];
		in >> parameters[2];

		in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		newTurret = std::make_shared<Turret>(name, name, turretShape, parameters);

		unsigned int cannonCount = 0;
		in >> cannonCount;
		in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		for (unsigned int i = 0; i < cannonCount; i++)//działa
		{
			std::getline(in, cannonType);
			in >> x;
			in >> y;
			newTurret->addBarrel(findBarrel(cannonType),sf::Vector2f(x,y- findBarrel(cannonType).length)+ findBarrel(cannonType).getOrigin());
			in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}		
		std::getline(in, endWord);
		if (endWord != "END_TURRET")break;
		turretData.push_back(std::pair<std::string,Turret>(name,Turret(*newTurret)));
	}
	in.close();
	return 1;
}
bool LocalGame::loadSounds()
{
	std::ifstream in("gamedata/sounds/file_list.txt");
	if (!in.good())return 0;

	std::string filename;
	std::shared_ptr<sf::SoundBuffer> buffer;
	while (!in.eof())
	{
		buffer = std::make_shared<sf::SoundBuffer>();
		in >> filename;
		if (!buffer->loadFromFile("gamedata/sounds/" + filename))
		{
			std::cout << "cannot load gamedata/sounds/" + filename << std::endl;
			continue;
		}
		this->soundBuffers.insert(std::pair<std::string,std::shared_ptr<sf::SoundBuffer>>(filename,buffer));
	}
	return true;
}
bool LocalGame::loadShips()
{
	std::fstream in("gamedata/ships.dat");

	if (!in.good())return 0;

	std::string name, endWord;
	unsigned int point_count;
	while (true)
	{
		endWord = "ERR";
		std::shared_ptr<Ship> newShip;

		unsigned int pointCount = 0;
		float x, y;
		sf::ConvexShape shipShape;

		shipShape.setFillColor(sf::Color::Red);

		std::getline(in, name);//nazwa
		float parameters[6];//parametry
		in >> parameters[0];
		in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		in >> parameters[1];
		in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		in >> parameters[2];
		in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		in >> parameters[3];
		in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		in >> parameters[4];
		in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		in >> parameters[5];
		in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		in >> pointCount;//ilość punktów
		in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		shipShape.setPointCount(pointCount);
		float maxx=0, maxy=0;
		for (unsigned int i = 0; i < pointCount; i++)//punkty
		{
			in >> x;
			in >> y;
			if (x > maxx)maxx = x;
			if (y > maxy)maxy = y;
			shipShape.setPoint(i, sf::Vector2f(x, y));
			in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		shipShape.setOrigin(sf::Vector2f(maxx/2, maxy/2));//origin

		newShip = std::make_shared<Ship>(name, parameters, shipShape);

		unsigned int turretCount = 0;
		in >> turretCount;
		in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		std::string turretName;
		float turretRestrictedArea[2];
		float startingAngle=69;
		
		for (unsigned int i = 0; i < turretCount; i++)//turrety
		{
			std::getline(in,turretName);
			in >> x;
			in >> y;
			in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			in >> turretRestrictedArea[0];
			in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			in >> turretRestrictedArea[1];
			in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			in >> startingAngle;
			in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::shared_ptr<Turret> newTurret = std::make_shared<Turret>(this->findTurret(turretName));
			newTurret->setRestrictedArea(turretRestrictedArea);
			//newTurret->setRotation(startingAngle); // to nie jest potrzebne bo ustawia się automatycznie w setRestrictedArea (bo zrąbałeś kąt początkowy w pliku xd a mój obrut cału czas działał dobrze)
			newShip->addTurret(newTurret,sf::Vector2f(x,y));
		}
		
		std::getline(in, endWord);
		if (endWord != "END_SHIP")break;
		shipData.push_back(std::pair<std::string, Ship>(name, Ship(*newShip)));
	}
	in.close();
	return 1;
}
Bullet LocalGame::findBullet(std::string name)
{
	for (auto &bullet : bulletData)
	{
		if (bullet.first == name)return bullet.second;
	}
	std::cout << "cannot find bullet " << name << std::endl;
	return bulletData.front().second;
}
Barrel LocalGame::findBarrel(std::string name)
{
	for (auto &barrel : barrelData)
	{
		if (barrel.first == name)return barrel.second;
	}
	std::cout << "cannot find barrel " << name << std::endl;
	return barrelData.front().second;
}
Turret LocalGame::findTurret(std::string name)
{
	for (auto &turret : turretData)
	{
		if (turret.first == name)return turret.second;
	}
	std::cout << "cannot find turret " << name << std::endl;
	return turretData.front().second;
}
Ship LocalGame::findShip(std::string name)
{
	for (auto &ship : shipData)
	{
		if (ship.first == name)return ship.second;
	}
	std::cout << "cannot find ship " << name << std::endl;
	return shipData.front().second;
}
std::shared_ptr<sf::SoundBuffer> LocalGame::findSoundBuffer(int caliber)
{
	for (auto & pair : soundBuffers)
	{
		if (pair.first == std::to_string(caliber)+".wav")
		{
			return pair.second;
		}
	}
	std::shared_ptr<sf::SoundBuffer> newSound = std::make_shared<sf::SoundBuffer>();
	return newSound;
}
void LocalGame::eraseBullet(unsigned int id)
{
	for (auto it = bullets.begin(); it != bullets.end(); it++)
	{
		if (it->getId() == id)bullets.erase(it);
	}
}
void LocalGame::calculatePlayerList(std::vector<sf::Text> &guiContent)
{
	unsigned int i = 0;
	for (auto & player : otherPlayers)
	{
		guiContent[i + 12].setString(std::to_string(player->getScore()) + " "+ player->getPlayerName() + " " + std::to_string(int(100*(player->getPlayerHP()/ (player->getMaxPlayerHP())))) + "%");
		guiContent[i + 12].setPosition(sf::Vector2f(10,100+i*30));
		if (player->getPlayerHP() / player->getMaxPlayerHP() < 0.2)
		{
			guiContent[i + 12].setFillColor(sf::Color(255, 0, 0, 180));
		}
		else guiContent[i + 12].setFillColor(sf::Color(255,255,255,127));
		i++;
	}
}
void LocalGame::generateWreckage(std::shared_ptr<Player> player)
{
	wreckages.push_back(std::make_shared<Ship>(*(player->getShip())));
	wreckages.back()->setPosition(player->getShip()->getPosition());
	wreckages.back()->setRotation(player->getShip()->getRotation());
}

bool LocalGame::connectToServer(const std::string &adress)
{
	auto dots = std::count_if(adress.begin(), adress.end(), [](char a) {return a == '.'; });
	if (dots != 3)
	{
		std::cout << "wrong IP format" << std::endl;
		return 0;
	}
	auto pos = adress.find(':');
	if (pos == std::string::npos)
	{
		std::cout << "need port number" << std::endl;
		return 0;
	}


	std::string IP = adress.substr(0, pos);
	std::stringstream port(adress.substr(pos + 1));


	unsigned short portNum;
	port >> portNum;

	std::cout << IP << ' ';
	std::cout << portNum << std::endl;

	if (portNum < 1025 || portNum >65535)
	{
		std::cout << "port number must be between 1024 and 65535" << std::endl;
		return 0;
	}
	TCPsocket.connect(sf::IpAddress(IP), portNum, sf::seconds(3));


	//-----------------------------------------------------------

	sf::Packet helloPacket;
	helloPacket.clear();
	helloPacket << "HI_" << inSocket.getLocalPort();
	std::cout << "sending \"HI\" to server" << std::endl;
	TCPsocket.send(helloPacket);
	helloPacket.clear();


	TCPsocket.receive(helloPacket);
	std::string message;
	helloPacket >> message;
	if (message == "HI_")
	{
		this->serverInfo.serverAddress = TCPsocket.getRemoteAddress();
		helloPacket >> serverInfo.serverUdpPort;
		std::cout << "server responded with \"HI\" and port " << serverInfo.serverUdpPort << std::endl;
		this->serverInfo.serverAddress = IP;
		TCPsocket.setBlocking(false);
		return true;
	}
	TCPsocket.setBlocking(false);
	return false;

}


LocalGame::~LocalGame()
{
}

void LocalGame::sendPlayerPosition()
{
	this->player->sendPlayerPosition(outSocket, this->serverInfo.serverAddress, this->serverInfo.serverUdpPort);
}

bool LocalGame::loadGameFiles()
{
	if (!this->loadBullets())std::cout << "cannot load bullets" << std::endl;
	if (!this->loadBarrels())std::cout << "cannot load barrels" << std::endl;
	if (!this->loadTurrets())std::cout << "cannot load turrets" << std::endl;
	if (!this->loadShips())std::cout << "cannot load ships" << std::endl;
	if (!this->loadSounds())std::cout << "cannot load sounds" << std::endl;
	return true;
}

void LocalGame::loadMap()
{
	sf::Texture waterTexture;
	waterTexture.loadFromFile("gamedata/textures/water.jpg");
	this->textures.insert(std::pair<std::string, sf::Texture>("water1", waterTexture));

	sf::Texture shallowTexture;
	shallowTexture.loadFromFile("gamedata/textures/shallow.png");
	this->textures.insert(std::pair<std::string,sf::Texture>("shallow1", shallowTexture));

	this->backgroundMap.resize(128); 
	for (auto & vector : backgroundMap)
	{
		vector.resize(128);
	}
	//c1 i c2 to liczniki położenia bitmapy
	unsigned int c1 = 0, c2 = 0;
	for (auto & vector : backgroundMap)
	{
		c2 = 0;
		for (auto & shape : vector)
		{
			shape.setSize(sf::Vector2f(360, 360));
			shape.setPosition(c1 * 360, c2 * 360);
			shape.setTexture(&textures["water1"]);
			c2++;
		}
		c1++;
	}
}

void LocalGame::receivePlayersPositions()
{
	sf::Packet receivedPacket;
	receivedPacket.clear();
	sf::IpAddress IP;
	unsigned short port;
	sf::Clock connectionClock;
	connectionClock.restart();

	this->inSocket.receive(receivedPacket, IP, port);
	while (connectionClock.getElapsedTime().asMilliseconds() < 30)
	{
		std::string message = "NULL";
		if (receivedPacket >> message)
		{
			//std::cout << message << std::endl;

			if (message == "PPS")
			{
				//std::cout << "received PPS" << std::endl;
				unsigned int playerId;
				float x, y, shipAngle, cannonAngle;

				unsigned int iterator;
				receivedPacket >> iterator;
				for (unsigned int i = 0; i < iterator; i++)
				{
					receivedPacket >> playerId;
					receivedPacket >> x;
					receivedPacket >> y;
					receivedPacket >> shipAngle;
					receivedPacket >> cannonAngle;

					auto player = this->getPlayerById(playerId);
					if (player == nullptr)
					{
						receivedPacket.clear();
						return;
					}
					else
					{
						player->getShip()->setPosition(sf::Vector2f(x, y));
						player->getShip()->setRotation(shipAngle);
						player->getShip()->setCannonRotation(cannonAngle);
						receivedPacket.clear();
					}
				}
			}
			if (message == "POS")
			{
				unsigned int id;
				sf::Vector2f position;
				float angle;
				float cannonAngle;
				receivedPacket >> id;
				auto player = this->getPlayerById(id);
				if (player == nullptr)return;
				if (player->getPlayerId() == this->player->getPlayerId())return;
				receivedPacket >> position.x;
				receivedPacket >> position.y;
				receivedPacket >> angle;
				receivedPacket >> cannonAngle;

				player->getShip()->setPosition(position);
				player->getShip()->setRotation(angle);
				player->setAngleOfView(cannonAngle);

			}
		}
	}
	inSocket.setBlocking(false);
	return;
		
}

void LocalGame::receiveTCP()
{
	sf::Packet receivedPacket;
	receivedPacket.clear();

	sf::Clock connectionClock;
	connectionClock.restart();
	while (connectionClock.getElapsedTime().asMilliseconds()<30)
	{
		if (TCPsocket.receive(receivedPacket) != sf::Socket::Done)return;
		std::string message;
		if (receivedPacket >> message)
		{
			if (message == "PLA")
			{

				unsigned int playerId = 0;
				std::string playerName, playerShip, playerShipName;

				receivedPacket >> playerId;
				receivedPacket >> playerName;
				receivedPacket >> playerShip;
				receivedPacket >> playerShipName;

				if (playerId == 0)return;
				if (playerId == this->player->getPlayerId())return;
				auto player = getPlayerById(playerId);
				if (player != nullptr)return;

				player = std::make_shared<Player>(playerId, playerName, playerShip);
				player->setShip(this->findShip(playerShip));
				player->getShip()->setPosition(sf::Vector2f(100, 100));
				player->setShipName(playerShipName);
				player->calculateHPindicator();
				std::cout << "received PLA " << playerId <<"/" <<playerName <<"/" <<playerShip <<std::endl;
				otherPlayers.push_back(player);
			}
			else if (message == "BUL")
			{
				jw::bulletInfo receivedData;
				receivedPacket >> receivedData;
				std::shared_ptr<Bullet> newBullet = std::make_shared<Bullet>(this->findBullet(receivedData.name));
				newBullet->setBulletInfo(receivedData);
				this->bullets.push_back(*newBullet);

				while (this->sounds.size() > 200)
				{
					sounds.erase(sounds.begin());
				}

				std::shared_ptr<sf::Sound> newSound = std::make_shared<sf::Sound>();
				newSound->setBuffer(*(this->findSoundBuffer(newBullet->getCaliber())));
				sounds.push_back(newSound);	
				newSound->play();
			}
			else if (message == "HIT")
			{
				unsigned int preyId,bulletId,predatorId;
				float damage;
				double preyHPleft;
				receivedPacket >> preyId >> bulletId >> predatorId >> damage >> preyHPleft;
				auto prey = this->getPlayerById(preyId);
				//prey->subtractHP(damage);
				prey->setHP(preyHPleft);
				prey->calculateHPindicator();
				this->eraseBullet(bulletId);
				std::cout << "received HIT " << preyId << ' ' << damage << std::endl;
			}
			else if (message == "KIL")
			{
				unsigned int preyId, predatorId;
				receivedPacket >> preyId;
				receivedPacket >> predatorId;
				this->generateWreckage(getPlayerById(preyId));
				this->getPlayerById(preyId)->getShip()->setPosition(sf::Vector2f(-32000, -32000));
				this->getPlayerById(predatorId)->increaseScore();
				this->getPlayerById(preyId)->respawn(sf::Vector2f(backgroundMap.size(),backgroundMap[0].size()));
			}
			else if (message == "EXT")
			{
				unsigned int afkPlayerId;

				std::cout << "exit" << std::endl;
				receivedPacket >> afkPlayerId;

				for (auto it = otherPlayers.begin(); it != otherPlayers.end(); it++)
				{
					if ((*it)->getPlayerId() == (*it)->getPlayerId())
					{
						otherPlayers.erase(it);
						break;
					}
				}
			}
			else if (message == "AFK")
			{
				this->connectionClock.restart();
				sf::Packet afkPacket;
				afkPacket << "AFK";
				this->sendTCP(afkPacket);
			}
			receivedPacket.clear();
		}
		else continue;
	}
}

void LocalGame::recieveUDP()
{
	this->receivePlayersPositions();
}

void LocalGame::sendTCP(sf::Packet messagePacket)
{
	this->TCPsocket.send(messagePacket);
}


