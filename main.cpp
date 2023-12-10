#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <string>

using namespace std;

void read_data_for_high_score(string high_score_combined[10]) {
	ifstream read_high_score;
	read_high_score.open("txt_files/record.txt");
		for (int i = 0; i < 10; i++) {
			getline(read_high_score, high_score_combined[i]);
		}
	read_high_score.close();
}

void write_data_for_high_score(string high_score_combined[10], string high_score_player_names[10], int high_score_arr[10]) {
	ofstream write_high_score;
	write_high_score.open("txt_files/record.txt");
		for (int i = 0; i < 10; i++) {
			high_score_combined[i] = high_score_player_names[i] + to_string(high_score_arr[i]);
			write_high_score << high_score_combined[i] << endl;
		}
	write_high_score.close();
}

int counting_for_separate_string(string name) {
	int i = 0;
	int count = 0;
	while (name[i] != '\0') {
		if (name[i] >= 'A' && name[i] <= 'Z' || name[i] >= 'a' && name[i] <= 'z')
			count++;
		i++;
	}
	return count;
}

void separating_strings(int high_score_arr[10], string high_score_player_names[10], string high_score_combined[10]) {
	for (int i = 0; i < 10; i++) {
		int length = high_score_combined[i].length();
		string temp;
		int count = counting_for_separate_string(high_score_combined[i]);
		high_score_arr[i] = stoi(high_score_combined[i].substr(count, length - count));
		high_score_player_names[i] = high_score_combined[i].substr(0, count);
		//cout << high_score_player_names[i] << " " << high_score_arr[i]<<endl;
	}
}

void sorting(int high_score_arr[10], string high_score_player_names[10], string high_score_combined[10]) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10 - i; j++) {
			if (high_score_arr[j] < high_score_arr[j + 1]) {
				swap(high_score_arr[j], high_score_arr[j + 1]);
				swap(high_score_player_names[j], high_score_player_names[j]);
				swap(high_score_combined[j], high_score_combined[j + 1]);
			}
		}
	}
}

void read_data_for_settings(float & laser_speed,float &jet_speed, int & lives, int & str_laser_color_index) {

	ifstream read_settings;
	read_settings.open("txt_files/settings.txt");
	read_settings >> laser_speed;
	read_settings >> jet_speed;
	read_settings >> lives;
	read_settings >> str_laser_color_index;
	read_settings.close();

}

void write_data_for_settings(float laser_speed,float jet_speed,int lives,int str_laser_color_index) {
	ofstream write_settings;
	write_settings.open("txt_files/settings.txt");
	write_settings << laser_speed << std::endl;
	write_settings << jet_speed << std::endl;
	write_settings << lives << std::endl;
	write_settings << str_laser_color_index;
	write_settings.close();
}

void adjust_jet_speed(sf::Vector2i mouse_position,sf::CircleShape & increase_bound1, float & jet_speed,sf::Text & jet_speed_string, sf::CircleShape & decrease_bound1) {
	//Selection Sound
	sf::SoundBuffer selectionbuffer;
	selectionbuffer.loadFromFile("sounds/Menu Selection Click.wav");
	sf::Sound selection;
	selection.setBuffer(selectionbuffer);

	if (mouse_position.x >= 1400 && mouse_position.x <= 1440 && mouse_position.y >= 405 && mouse_position.y <= 445) {
		increase_bound1.setFillColor(sf::Color::Red);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			selection.play();
			if (jet_speed < 10.0) {
				jet_speed += 0.5;
				jet_speed_string.setString(std::to_string(int(10 * jet_speed)));
			}
		}
	}
	else {
		increase_bound1.setFillColor(sf::Color::White);
	}

	if (mouse_position.x >= 1300 && mouse_position.x <= 1340 && mouse_position.y >= 405 && mouse_position.y <= 445) {
		decrease_bound1.setFillColor(sf::Color::Red);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			selection.play();
			if (jet_speed > 1.0) {
				jet_speed -= 0.5;
				jet_speed_string.setString(std::to_string(int(10 * jet_speed)));
			}
		}
	}
	else {
		decrease_bound1.setFillColor(sf::Color::White);
	}
}

void adjust_laser_speed(sf::Vector2i mouse_position, sf::CircleShape& increase_bound2, float& laser_speed, sf::Text& laser_speed_string, sf::CircleShape& decrease_bound2) {

	//Selection Sound
	sf::SoundBuffer selectionbuffer;
	selectionbuffer.loadFromFile("sounds/Menu Selection Click.wav");
	sf::Sound selection;
	selection.setBuffer(selectionbuffer);

	if (mouse_position.x >= 1400 && mouse_position.x <= 1440 && mouse_position.y >= 505 && mouse_position.y <= 545) {
		increase_bound2.setFillColor(sf::Color::Red);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			selection.play();
			if (laser_speed < 10.0) {
				laser_speed += 0.5;
				laser_speed_string.setString(std::to_string(int(10 * laser_speed)));
			}
		}
	}
	else {
		increase_bound2.setFillColor(sf::Color::White);
	}

	if (mouse_position.x >= 1300 && mouse_position.x <= 1340 && mouse_position.y >= 505 && mouse_position.y <= 545) {
		decrease_bound2.setFillColor(sf::Color::Red);
		selection.play();
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			if (laser_speed > 1.0) {
				laser_speed -= 0.5;
				laser_speed_string.setString(std::to_string(int(10 * laser_speed)));
			}
		}
	}
	else {
		decrease_bound2.setFillColor(sf::Color::White);
	}
}

void adjust_lives(sf::Vector2i mouse_position, sf::CircleShape& increase_bound3, int & lives, sf::Text& lives_string, sf::CircleShape& decrease_bound3) {
	
	//Selection Sound
	sf::SoundBuffer selectionbuffer;
	selectionbuffer.loadFromFile("sounds/Menu Selection Click.wav");
	sf::Sound selection;
	selection.setBuffer(selectionbuffer);

	if (mouse_position.x >= 1400 && mouse_position.x <= 1440 && mouse_position.y >= 605 && mouse_position.y <= 645) {
		increase_bound3.setFillColor(sf::Color::Red);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			selection.play();
			if (lives < 5) {
				lives++;
				lives_string.setString(std::to_string(lives));
			}
		}
	}
	else {
		increase_bound3.setFillColor(sf::Color::White);
	}

	if (mouse_position.x >= 1300 && mouse_position.x <= 1340 && mouse_position.y >= 605 && mouse_position.y <= 645) {
		decrease_bound3.setFillColor(sf::Color::Red);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			selection.play();
			if (lives > 1) {
				lives--;
				lives_string.setString(std::to_string(int(lives)));
			}
		}
	}
	else {
		decrease_bound3.setFillColor(sf::Color::White);
	}
}

void adjust_laser_color(sf::Vector2i mouse_position, sf::CircleShape& increase_bound4, int & str_laser_color_index, string str_laser_color[5], sf::Text & laser_color_string, sf::CircleShape& decrease_bound4) {
	
	//Selection Sound
	sf::SoundBuffer selectionbuffer;
	selectionbuffer.loadFromFile("sounds/Menu Selection Click.wav");
	sf::Sound selection;
	selection.setBuffer(selectionbuffer);

	if (mouse_position.x >= 1460 && mouse_position.x <= 1500 && mouse_position.y >= 705 && mouse_position.y <= 745) {
		increase_bound4.setFillColor(sf::Color::Red);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			selection.play();
			if (str_laser_color_index < 4) {
				str_laser_color_index++;
				laser_color_string.setString(str_laser_color[str_laser_color_index]);
			}
		}
	}
	else {
		increase_bound4.setFillColor(sf::Color::White);
	}
	if (mouse_position.x >= 1300 && mouse_position.x <= 1340 && mouse_position.y >= 705 && mouse_position.y <= 745) {
		decrease_bound4.setFillColor(sf::Color::Red);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			selection.play();
			if (str_laser_color_index > 0) {
				str_laser_color_index--;
				laser_color_string.setString(str_laser_color[str_laser_color_index]);
			}
		}
	}
	else {
		decrease_bound4.setFillColor(sf::Color::White);
	}
}

int main() {

	int high_score_arr[10];
	string high_score_combined[10];
	string high_score_player_names[10];
	//These Functions are to read high scores and sort them and write them back into the file
	read_data_for_high_score(high_score_combined);

	separating_strings(high_score_arr, high_score_player_names, high_score_combined);

	sorting(high_score_arr, high_score_player_names, high_score_combined);

	write_data_for_high_score(high_score_combined, high_score_player_names, high_score_arr);
	
	int option = 0;
	float laser_speed = 2.5;
	float jet_speed = 2.5;
	int lives = 3;
	string name = "PLAYER";
	int str_laser_color_index = 3;
	string str_laser_color[] = { "RED","BLUE","GREEN","CYAN","YELLOW"};

	//START SOUND
	sf::SoundBuffer startbuffer;
	startbuffer.loadFromFile("sounds/start.ogg");
	sf::Sound start_sound;
	start_sound.setBuffer(startbuffer);
	start_sound.play();

	menu_label:

	//Function to read stored settings from file
	read_data_for_settings(laser_speed, jet_speed, lives,str_laser_color_index);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	//Menu Window
	sf::RenderWindow menu_window(sf::VideoMode(1920.0f, 1001.0f), "MENU", sf::Style::Fullscreen);
	
	//Menu Selection Sound
	sf::SoundBuffer selectionbuffer;
	selectionbuffer.loadFromFile("sounds/Menu Selection Click.wav");
	sf::Sound selection;
	selection.setBuffer(selectionbuffer);

	//Menu Background
	sf::RectangleShape menu_background(sf::Vector2f(1920.0f,1001.0f));
	sf::Texture menu_background_texture;
	menu_background_texture.loadFromFile("images/space-1.png");
	menu_background.setTexture(&menu_background_texture);
	
	//Play Border
	sf::RectangleShape play_border(sf::Vector2f(110.0f,58.0f));
	play_border.setOrigin(0.0f, 0.0f);
	play_border.setPosition(sf::Vector2f(921.0f, 383.0f));

	//SETTINGS BORDER
	sf::RectangleShape settings_border(sf::Vector2f(215.0f,58.0f));
	settings_border.setOrigin(0.0f, 0.0f);
	settings_border.setPosition(sf::Vector2f(862.0f, 502.0f));

	//High Scores Border
	sf::RectangleShape high_scores_border(sf::Vector2f(275.0f, 58.0f));
	high_scores_border.setOrigin(0.0f,0.0f);
	high_scores_border.setPosition(sf::Vector2f(832.5f, 617.0f));
	high_scores_border.setFillColor(sf::Color::Blue);

	//QUIT BORDER
	sf::RectangleShape quit_border(sf::Vector2f(105.0f,58.0f));
	quit_border.setPosition(923.0f, 732.0f);

	//NAME BORDER
	sf::RectangleShape name_border(sf::Vector2f(250.0f,40.0f));
	name_border.setPosition(sf::Vector2f(900.0f,903.0f));
	name_border.setFillColor(sf::Color::Blue);

	//FONT
	sf::Font font;
	font.loadFromFile("Font/font.otf");

	//MENU TEXT SPACE SHOOTER
	sf::Text spaceshooter;
	spaceshooter.setFont(font);
	spaceshooter.setString("SPACE SHOOTER");
	spaceshooter.setCharacterSize(100);
	spaceshooter.setPosition(sf::Vector2f(715.0f,100.0f));
	spaceshooter.Bold;
	

	//Menu Text Play
	sf::Text play;
	play.setFont(font);
	play.setString("PLAY");
	play.setCharacterSize(60);
	play.setPosition(sf::Vector2f(925.0f,375.0f));
	play.Bold;
	play.Italic;

	//Menu Text SETTINGS
	sf::Text settings_text;
	settings_text.setFont(font);
	settings_text.setCharacterSize(60);
	settings_text.setString("SETTINGS");
	settings_text.setPosition(sf::Vector2f(864.0f,495.0f));
	settings_text.Bold;
	settings_text.Italic;

	//Menu Text High Score
	sf::Text high_score_menu_text;
	high_score_menu_text.setFont(font);
	high_score_menu_text.setString("HIGH SCORES");
	high_score_menu_text.setCharacterSize(60);
	high_score_menu_text.setPosition(sf::Vector2f(835.0f, 610.0f));
	high_score_menu_text.Bold;
	high_score_menu_text.Italic;
	
	//Menu Text Quit
	sf::Text quit;
	quit.setFont(font);
	quit.setString("QUIT");
	quit.setCharacterSize(60);
	quit.setPosition(sf::Vector2f(925.0f,725.0f));
	quit.Bold;
	quit.Italic;

	//Menu Text Name
	sf::Text name_text;
	name_text.setFont(font);
	name_text.setString("NAME");
	name_text.setCharacterSize(40);
	name_text.setPosition(sf::Vector2f(800.0f, 900.0f));
	name_text.Bold;
	name_text.Italic;

	//Menu Name String
	sf::Text name_string;
	name_string.setFont(font);
	name_string.setString(name);
	name_string.setCharacterSize(40);
	name_string.setPosition(sf::Vector2f(905.0f, 900.0f));

	while (menu_window.isOpen()) {
		sf::Event evnt;
		sf::Vector2i mouse_position = sf::Mouse::getPosition(menu_window);
		while (menu_window.pollEvent(evnt)) {
			//INPUT NAME FROM USER
			if (mouse_position.x >= 900 && mouse_position.x <= 1150 && mouse_position.y >= 903 && mouse_position.y <= 943) {
				name_border.setFillColor(sf::Color::White);
				name_string.setFillColor(sf::Color::Black);
				if (evnt.type == sf::Event::TextEntered) {
					if (evnt.text.unicode == '\b'&&name.size()>0) {
						selection.play();
						name.erase(name.size() - 1, 1);
						name_string.setString(name);
					}
					else {
						if (evnt.text.unicode>='A'&& evnt.text.unicode<='Z'|| evnt.text.unicode >= 'a' && evnt.text.unicode <= 'z') {
							selection.play();
							name += evnt.text.unicode;
							name_string.setString(name);
						}
					}
				}
			}
			else {
				name_border.setFillColor(sf::Color::Black);
				name_string.setFillColor(sf::Color::White);
			}
			
			switch (evnt.type) {
			case sf::Event::Closed:
				menu_window.close();
				return 0;
				break;
			}
		}
		menu_window.clear();
		menu_window.draw(menu_background);
		menu_window.draw(spaceshooter);
		menu_window.draw(play_border);
		menu_window.draw(play);
		menu_window.draw(settings_border);
		menu_window.draw(settings_text);
		menu_window.draw(high_scores_border);
		menu_window.draw(high_score_menu_text);
		menu_window.draw(quit_border);
		menu_window.draw(quit);
		menu_window.draw(name_text);
		menu_window.draw(name_border);
		menu_window.draw(name_string);
		menu_window.display();
		
		//PLAY BUTTON

		if (mouse_position.x >= 921 && mouse_position.x <= 1031 && mouse_position.y >= 383 && mouse_position.y <= 441) {
			play_border.setFillColor(sf::Color::White);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				selection.play();
				option = 1;
				menu_window.close();
			}
			play.setFillColor(sf::Color::Black);
		}
		else {
			play_border.setFillColor(sf::Color::Black);
			play.setFillColor(sf::Color::White);
		}

		//SETTINGS BUTTON

		if (mouse_position.x >= 862 && mouse_position.x <= 1077 && mouse_position.y >= 502 && mouse_position.y <= 560) {
			settings_border.setFillColor(sf::Color::White);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				selection.play();
				option = 2;
				menu_window.close();
			}
			settings_text.setFillColor(sf::Color::Black);
		}
		else {
			settings_border.setFillColor(sf::Color::Black);
			settings_text.setFillColor(sf::Color::White);
		}

		//HIGH SCORE BUTTON

		if (mouse_position.x >= 832.5 && mouse_position.x <= 1107.5 && mouse_position.y >= 617 && mouse_position.y <= 675) {
			high_scores_border.setFillColor(sf::Color::White);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				selection.play();
				option = 3;
				menu_window.close();
			}
			high_score_menu_text.setFillColor(sf::Color::Black);
		}
		else {
			high_scores_border.setFillColor(sf::Color::Black);
			high_score_menu_text.setFillColor(sf::Color::White);
		}

		//QUIT BUTTON

		if (mouse_position.x >= 923 && mouse_position.x <= 1028 && mouse_position.y >= 730 && mouse_position.y <= 788) {
			quit_border.setFillColor(sf::Color::White);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				selection.play();
				return 0;
			}
			quit.setFillColor(sf::Color::Black);
		}
		else {
			quit_border.setFillColor(sf::Color::Black);
			quit.setFillColor(sf::Color::White);
		}

	}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	if (option==2) {
		//SETTINGS Window

		sf::RenderWindow settings_window(sf::VideoMode(1920.0f, 1001.0f), "HIGH SCORES", sf::Style::Titlebar | sf::Style::Close | sf::Style::Default|sf::Style::Fullscreen);

		//SETTINGS BACKGROUND
		sf::RectangleShape settings_background(sf::Vector2f(1920.0f,1201.0f));
		sf::Texture settings_background_texture;
		settings_background_texture.loadFromFile("images/Space1.png");
		settings_background.setTexture(&settings_background_texture);
		settings_background.setOrigin(sf::Vector2f(0.0f, 0.0f));
		settings_background.setPosition(sf::Vector2f(0.0f, 0.0f));


		//Back Key
		sf::RectangleShape back_key(sf::Vector2f(50.0f,50.0f));
		back_key.setPosition(sf::Vector2f(75.0f, 75.0f));
		back_key.setOrigin(sf::Vector2f(0.0f, 0.0f));
		back_key.setFillColor(sf::Color::Red);
		sf::Texture back_key_texture;
		back_key_texture.loadFromFile("images/back1.png");
		back_key.setTexture(&back_key_texture);
		back_key.rotate(-90);


		//SETTINGS TEXT
		sf::Text main_settings_text;
		main_settings_text.setFont(font);
		main_settings_text.setCharacterSize(100);
		main_settings_text.setString("SETTINGS");
		main_settings_text.setPosition(sf::Vector2f(800.0f,100.0f));

		//LASER SPEED TEXT
		sf::Text laser_speed_text;
		laser_speed_text.setFont(font);
		laser_speed_text.setCharacterSize(40);
		laser_speed_text.setString("LASER SPEED");
		laser_speed_text.setPosition(sf::Vector2f(500.0f,500.0f));
		laser_speed_text.Bold;
		laser_speed_text.Italic;

		//LASER SPEED
		sf::Text laser_speed_string;
		laser_speed_string.setFont(font);
		laser_speed_string.setString(std::to_string(int(10*laser_speed)));
		laser_speed_string.setPosition(sf::Vector2f(1350.0f,500.0f));
		laser_speed_string.setCharacterSize(40);

		//JET SPEED TEXT
		sf::Text jet_speed_text;
		jet_speed_text.setFont(font);
		jet_speed_text.setCharacterSize(40);
		jet_speed_text.setString("JET SPEED");
		jet_speed_text.setPosition(sf::Vector2f(500.0f, 400.0f));
		jet_speed_text.Bold;
		jet_speed_text.Italic;

		//JET SPEED STRING
		sf::Text jet_speed_string;
		jet_speed_string.setFont(font);
		jet_speed_string.setString(std::to_string(int(10 * jet_speed)));
		jet_speed_string.setPosition(sf::Vector2f(1350.0f, 400.0f));
		jet_speed_string.setCharacterSize(40);

		//LIVES TEXT
		sf::Text lives_text;
		lives_text.setFont(font);
		lives_text.setCharacterSize(40);
		lives_text.setString("TOTAL LIVES");
		lives_text.setPosition(sf::Vector2f(500.0f, 600.0f));
		lives_text.Bold;
		lives_text.Italic;

		//LIVES STRING
		sf::Text lives_string;
		lives_string.setFont(font);
		lives_string.setString(std::to_string(int(lives)));
		lives_string.setPosition(sf::Vector2f(1360.0f, 600.0f));
		lives_string.setCharacterSize(40);

		//INCREASE1
		sf::CircleShape increase1(20.0f,3);
		increase1.setPosition(sf::Vector2f(1400.0f,405.0f));
		increase1.setFillColor(sf::Color::Black);

		//INCREASE1 BOUNDARY
		sf::CircleShape increase_bound1(20.0f);
		increase_bound1.setPosition(sf::Vector2f(1400.0f, 405.0f));

		//DECREASE1
		sf::CircleShape decrease1(20.0f, 3);
		decrease1.setPosition(sf::Vector2f(1340.0f, 444.0f));
		decrease1.rotate(180);
		decrease1.setFillColor(sf::Color::Black);

		//DECREASE1 BOUNDARY
		sf::CircleShape decrease_bound1(20.0f);
		decrease_bound1.setPosition(sf::Vector2f(1300.0f, 405.0f));
		
		//INCREASE2
		sf::CircleShape increase2(20.0f, 3);
		increase2.setPosition(sf::Vector2f(1400.0f, 505.0f));
		increase2.setFillColor(sf::Color::Black);

		//INCREASE2 BOUNDARY
		sf::CircleShape increase_bound2(20.0f);
		increase_bound2.setPosition(sf::Vector2f(1400.0f, 505.0f));

		//DECREASE2
		sf::CircleShape decrease2(20.0f, 3);
		decrease2.setPosition(sf::Vector2f(1340.0f, 544.0f));
		decrease2.rotate(180);
		decrease2.setFillColor(sf::Color::Black);

		//DECREASE2 BOUNDARY
		sf::CircleShape decrease_bound2(20.0f);
		decrease_bound2.setPosition(sf::Vector2f(1300.0f, 505.0f));

		//INCREASE3
		sf::CircleShape increase3(20.0f, 3);
		increase3.setPosition(sf::Vector2f(1400.0f, 605.0f));
		increase3.setFillColor(sf::Color::Black);

		//INCREASE3 BOUNDARY
		sf::CircleShape increase_bound3(20.0f);
		increase_bound3.setPosition(sf::Vector2f(1400.0f, 605.0f));

		//DECREASE3
		sf::CircleShape decrease3(20.0f, 3);
		decrease3.setPosition(sf::Vector2f(1340.0f, 644.0f));
		decrease3.rotate(180);
		decrease3.setFillColor(sf::Color::Black);

		//DECREASE3 BOUNDARY
		sf::CircleShape decrease_bound3(20.0f);
		decrease_bound3.setPosition(sf::Vector2f(1300.0f, 605.0f));

		//INCREASE4
		sf::CircleShape increase4(20.0f, 3);
		increase4.setPosition(sf::Vector2f(1460.0f, 705.0f));
		increase4.setFillColor(sf::Color::Black);

		//INCREASE4 BOUNDARY
		sf::CircleShape increase_bound4(20.0f);
		increase_bound4.setPosition(sf::Vector2f(1460.0f, 705.0f));

		//DECREASE4
		sf::CircleShape decrease4(20.0f, 3);
		decrease4.setPosition(sf::Vector2f(1340.0f, 744.0f));
		decrease4.rotate(180);
		decrease4.setFillColor(sf::Color::Black);

		//DECREASE4 BOUNDARY
		sf::CircleShape decrease_bound4(20.0f);
		decrease_bound4.setPosition(sf::Vector2f(1300.0f, 705.0f));

		//LASER COLOR TEXT
		sf::Text laser_color;
		laser_color.setFont(font);
		laser_color.setString("LASER COLOR");
		laser_color.setCharacterSize(40);
		laser_color.setPosition(sf::Vector2f(500.0f, 700.0f));

		//LASER COLOR STRING
		sf::Text laser_color_string;
		laser_color_string.setFont(font);
		laser_color_string.setString(str_laser_color[str_laser_color_index]);
		laser_color_string.setPosition(sf::Vector2f(1350.0f, 700.0f));
		laser_color_string.setCharacterSize(40);

		while (settings_window.isOpen()) {
			sf::Event evnt;
			sf::Vector2i mouse_position = sf::Mouse::getPosition(settings_window);
			while (settings_window.pollEvent(evnt)) {
				
				adjust_jet_speed(mouse_position,increase_bound1,jet_speed,jet_speed_string,decrease_bound1);

				adjust_laser_speed(mouse_position, increase_bound2, laser_speed, laser_speed_string, decrease_bound2);

				adjust_lives(mouse_position,increase_bound3,lives,lives_string,decrease_bound3);

				adjust_laser_color(mouse_position, increase_bound4,str_laser_color_index,str_laser_color,laser_color_string,decrease_bound4);
				
				switch (evnt.type) {
				case sf::Event::Closed:
					settings_window.close();
					return 0;
					break;
				}
			}
			settings_window.clear();
			settings_window.draw(settings_background);
			settings_window.draw(back_key);
			settings_window.draw(main_settings_text);
			settings_window.draw(jet_speed_text);
			settings_window.draw(jet_speed_string);
			settings_window.draw(increase_bound1);
			settings_window.draw(increase1);
			settings_window.draw(decrease_bound1);
			settings_window.draw(decrease1);
			settings_window.draw(laser_speed_text);
			settings_window.draw(laser_speed_string);
			settings_window.draw(increase_bound2);
			settings_window.draw(increase2);
			settings_window.draw(decrease_bound2);
			settings_window.draw(decrease2);
			settings_window.draw(lives_text);
			settings_window.draw(lives_string);
			settings_window.draw(increase_bound3);
			settings_window.draw(increase3);
			settings_window.draw(decrease_bound3);
			settings_window.draw(decrease3);
			settings_window.draw(laser_color);
			settings_window.draw(laser_color_string);
			settings_window.draw(increase_bound4);
			settings_window.draw(increase4);
			settings_window.draw(decrease_bound4);
			settings_window.draw(decrease4);
			settings_window.display();
			
			if (mouse_position.x >= 75 && mouse_position.x <= 125 && mouse_position.y >= 30 && mouse_position.y <= 80) {
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
					selection.play();
					goto menu_label;
				}
			}

			write_data_for_settings(laser_speed,jet_speed,lives,str_laser_color_index);
			
		}
	}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	if (option == 3) { 
		sf::RenderWindow high_score_window(sf::VideoMode(1920.0f, 1001.0f), "HIGH SCORES", sf::Style::Titlebar | sf::Style::Close | sf::Style::Fullscreen);
	
		//HIGH SCORE BACKGROUND
		sf::RectangleShape high_score_background(sf::Vector2f(1920.0f, 1201.0f));
		sf::Texture high_score_background_texture;
		high_score_background_texture.loadFromFile("images/Space1.png");
		high_score_background.setTexture(&high_score_background_texture);
		high_score_background.setPosition(sf::Vector2f(0.0f, 0.0f));

		//Back Key
		sf::RectangleShape back_key(sf::Vector2f(50.0f, 50.0f));
		back_key.setPosition(sf::Vector2f(75.0f, 75.0f));
		back_key.setOrigin(sf::Vector2f(0.0f, 0.0f));
		back_key.setFillColor(sf::Color::Red);
		sf::Texture back_key_texture;
		back_key_texture.loadFromFile("images/back1.png");
		back_key.setTexture(&back_key_texture);
		back_key.rotate(-90);

		//Text High Score
		sf::Text main_high_score_text;
		main_high_score_text.setFont(font);
		main_high_score_text.setString("HIGH SCORES");
		main_high_score_text.setCharacterSize(100);
		main_high_score_text.setPosition(sf::Vector2f(755.0f, 100.0f));
		main_high_score_text.Bold;
	
		//SCORES STRING
		sf::Text high_scores_string[10];
		for (int i = 0; i < 10; i++) {
			float ycoord_for_h_s_s = 200.0;
			high_scores_string[i].setFont(font);
			high_scores_string[i].setString(std::to_string(high_score_arr[i]));
			high_scores_string[i].setCharacterSize(60);
			high_scores_string[i].Bold;
		}
		high_scores_string[0].setPosition(sf::Vector2f(1200.0f,300.0f));
		high_scores_string[1].setPosition(sf::Vector2f(1200.0f,370.0f));
		high_scores_string[2].setPosition(sf::Vector2f(1200.0f,440.0f));
		high_scores_string[3].setPosition(sf::Vector2f(1200.0f,510.0f));
		high_scores_string[4].setPosition(sf::Vector2f(1200.0f,580.0f));
		high_scores_string[5].setPosition(sf::Vector2f(1200.0f,650.0f));
		high_scores_string[6].setPosition(sf::Vector2f(1200.0f,720.0f));
		high_scores_string[7].setPosition(sf::Vector2f(1200.0f,790.0f));
		high_scores_string[8].setPosition(sf::Vector2f(1200.0f,860.0f));
		high_scores_string[9].setPosition(sf::Vector2f(1200.0f,930.0f));

		//High Score Names
		sf::Text high_score_names[10];
		for (int i = 0; i < 10; i++) {
			high_score_names[i].setFont(font);
			high_score_names[i].setString(high_score_player_names[i]);
			high_score_names[i].setCharacterSize(60);
			high_score_names[i].Bold;
		}
		high_score_names[0].setPosition(sf::Vector2f(600.0f, 300.0f));
		high_score_names[1].setPosition(sf::Vector2f(600.0f, 370.0f));
		high_score_names[2].setPosition(sf::Vector2f(600.0f, 440.0f));
		high_score_names[3].setPosition(sf::Vector2f(600.0f, 510.0f));
		high_score_names[4].setPosition(sf::Vector2f(600.0f, 580.0f));
		high_score_names[5].setPosition(sf::Vector2f(600.0f, 650.0f));
		high_score_names[6].setPosition(sf::Vector2f(600.0f, 720.0f));
		high_score_names[7].setPosition(sf::Vector2f(600.0f, 790.0f));
		high_score_names[8].setPosition(sf::Vector2f(600.0f, 860.0f));
		high_score_names[9].setPosition(sf::Vector2f(600.0f, 930.0f));
		
		while (high_score_window.isOpen()) {
			sf::Event evnt;
			while (high_score_window.pollEvent(evnt)) {
				switch (evnt.type) {
				case sf::Event::Closed:
					high_score_window.close();
					return 0;
					break;
				}
			}

			high_score_window.clear();
			high_score_window.draw(high_score_background);
			high_score_window.draw(back_key);
			high_score_window.draw(main_high_score_text);
			for (int i = 0; i < 10; i++) {
				high_score_window.draw(high_scores_string[i]);
				high_score_window.draw(high_score_names[i]);
			}
			high_score_window.display();

			sf::Vector2i mouse_position = sf::Mouse::getPosition(high_score_window);
			if (mouse_position.x >= 75 && mouse_position.x <= 125 && mouse_position.y >= 30 && mouse_position.y <= 80) {
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
					selection.play();
					goto menu_label;
				}
			}
		}

	}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	label:

	int score = 0;
	int high_score;
	high_score = high_score_arr[0];

	//Window
	sf::RenderWindow window(sf::VideoMode(1920.0f, 1001.0f), "Space Shooter", sf::Style::Titlebar | sf::Style::Close | sf::Style::Fullscreen);

	//High Score Text
	sf::Text t_h_s;
	t_h_s.setFont(font);
	t_h_s.setString("HIGH SCORE ");
	t_h_s.setPosition(sf::Vector2f(1700.0f, 875.0f));

	//HIGH SCORE
	sf::Text display_high_score;
	display_high_score.setFont(font);
	string str_high_score = std::to_string(high_score);
	display_high_score.setString(str_high_score);
	display_high_score.setPosition(sf::Vector2f(1850.0f, 875.0f));

	//High Score Name
	sf::Text high_scorer;
	high_scorer.setFont(font);
	high_scorer.setString(high_score_player_names[0]);
	high_scorer.setPosition(sf::Vector2f(1700.0f, 925.0f));

	//Score text
	sf::Text t_s;
	t_s.setFont(font);
	t_s.setString("SCORE ");
	t_s.setPosition(sf::Vector2f(50.0f,875.0f));

	//score:
	sf::Text text_score;
	text_score.setFont(font);
	string s = std::to_string(score);
	text_score.setString(s);
	text_score.setPosition(sf::Vector2f(150.0f,875.0f));

	//scorer
	sf::Text scorer;
	scorer.setFont(font);
	scorer.setString(name);
	scorer.setPosition(sf::Vector2f(50,925));

	//Lives text
	sf::Text t_l;
	t_l.setFont(font);
	t_l.setString("LIVES ");
	t_l.setPosition(sf::Vector2f(900.0f, 950.0f));

	//Lives
	sf::Text text_lives;
	text_lives.setFont(font);
	string str_lives = std::to_string(lives);
	text_lives.setString(str_lives);
	text_lives.setPosition(sf::Vector2f(1000.0f, 950.0f));

	//Jet
	sf::RectangleShape jet(sf::Vector2f(64.0f,64.0f));
	jet.setOrigin(sf::Vector2f(32.0f, 32.0f));
	jet.setPosition(sf::Vector2f(960.0f,810.0f));
	sf::Texture jetTexture;
	jetTexture.loadFromFile("images/combatjet-32x32.png");
	jet.setTexture(&jetTexture);
	sf::Vector2u texturesize = jetTexture.getSize();
	texturesize.x /= 5;
	texturesize.y /= 1;
	jet.setTextureRect(sf::IntRect(texturesize.x * 2, texturesize.y * 0, texturesize.x, texturesize.y));

	//Background
	sf::RectangleShape background(sf::Vector2f(1910.0f,745.0f));
	background.setOrigin(sf::Vector2f(955.0f,372.5f));
	background.setPosition(sf::Vector2f(955.0f,372.5f));
	sf::Texture backgroundtexture;
	backgroundtexture.loadFromFile("images/Background.png");
	background.setTexture(&backgroundtexture);

	//Laser
	sf::RectangleShape laser(sf::Vector2f(50.0f, 50.0f));
	sf::Vector2f lasercoords;
	lasercoords = jet.getPosition();
	laser.rotate(-90.0);
	laser.setPosition(sf::Vector2f(lasercoords.x-20, lasercoords.y - 50));
	sf::Texture laserTexture;
	laserTexture.loadFromFile("images/14.png");
	laser.setTexture(&laserTexture);
	laser.setPosition(sf::Vector2f(jet.getPosition().x - 20, jet.getPosition().y - 50));
	if (str_laser_color_index==0) {
		laser.setFillColor(sf::Color::Red);
	}else if (str_laser_color_index == 1) {
		laser.setFillColor(sf::Color::Blue);
	}else if (str_laser_color_index == 2) {
		laser.setFillColor(sf::Color::Green);
	}
	else if (str_laser_color_index == 3) {
		laser.setFillColor(sf::Color::Cyan);
	}
	else {
		laser.setFillColor(sf::Color::Yellow);
	}

	//Enemies
	float y_coord = 5;
	float random = static_cast<float>(5 + (rand() % 1845));
	sf::RectangleShape enemy(sf::Vector2f(70.0f, 50.0f));
	enemy.setPosition(sf::Vector2f(random, y_coord));
	sf::Texture enemyTexture;
	enemyTexture.loadFromFile("images/enemies.png");
	enemy.setTexture(&enemyTexture);
	sf::Vector2u enemytexturesize = enemyTexture.getSize();
	enemytexturesize.x /= 4;
	enemytexturesize.y /= 5;
	enemy.setTextureRect(sf::IntRect(enemytexturesize.x * 3, enemytexturesize.y * 0, enemytexturesize.x, enemytexturesize.y));

	//Boundries
	sf::RectangleShape line_down, line_left, line_right, line_up;
	line_down.setSize(sf::Vector2f(1920.0f, 5.0f));
	line_down.setPosition(sf::Vector2f(5.0f, 750.0f));
	line_up.setSize(sf::Vector2f(1920.0f, 5.0f));
	line_up.setPosition(sf::Vector2f(5.0f, 5.0f));
	line_left.setSize(sf::Vector2f(5.0f, 750.0f));
	line_left.setPosition(sf::Vector2f(5.0f, 5.0f));
	line_right.setSize(sf::Vector2f(5.0f, 750.0f));
	line_right.setPosition(sf::Vector2f(1915.0f, 5.0f));

	//Explosion Sound
	sf::SoundBuffer explosionbuffer;
	explosionbuffer.loadFromFile("sounds/rumble.flac");
	sf::Sound boom;
	boom.setBuffer(explosionbuffer);

	//Missed Sound
	sf::SoundBuffer missedbuffer;
	missedbuffer.loadFromFile("sounds/misc1.wav");
	sf::Sound missed;
	missed.setBuffer(missedbuffer);

	bool fired = false;
	int count = 0;

	while (window.isOpen()) {
		sf::Event evnt;
		while (window.pollEvent(evnt)) {
			switch (evnt.type) {
				case sf::Event::Closed:
					window.close();
					return 0;
					break;
			}
			//PAUSE WINDOW
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
				sf::RenderWindow pause_window(sf::VideoMode(1920.0f, 1001.0f), "PAUSED", sf::Style::Fullscreen);
				
				//Pause Window Background
				sf::RectangleShape pause_window_background(sf::Vector2f(1920.0f, 1001.0f));
				sf::Texture pause_window_background_texture;
				pause_window_background_texture.loadFromFile("images/Space1.png");
				pause_window_background.setTexture(&pause_window_background_texture);
				pause_window_background.setPosition(sf::Vector2f(0.0f, 0.0f));

				//Back Key
				sf::RectangleShape back_key2(sf::Vector2f(50.0f, 50.0f));
				back_key2.setPosition(sf::Vector2f(75.0f, 75.0f));
				back_key2.setOrigin(sf::Vector2f(0.0f, 0.0f));
				back_key2.setFillColor(sf::Color::Red);
				sf::Texture back_key_texture2;
				back_key_texture2.loadFromFile("images/back1.png");
				back_key2.setTexture(&back_key_texture2);
				back_key2.rotate(-90);

				//PAUSE TEXT
				sf::Text paused;
				paused.setFont(font);
				paused.setCharacterSize(200);
				paused.setString("PAUSED");
				paused.setPosition(sf::Vector2f(700.0f,350.0f));
				paused.Bold;

				//Instruction
				sf::Text instruction;
				instruction.setFont(font);
				instruction.setCharacterSize(40);
				instruction.setString("PRESS ENTER KEY TO CONTINUE");
				instruction.setPosition(sf::Vector2f(750.0f,700.0f));

				while (pause_window.isOpen()) {
					sf::Event event1;
					while (pause_window.pollEvent(event1)) {
						switch (event1.type) {
						case sf::Event::Closed:
							pause_window.close();
							return 0;
							break;
						}
					}
					pause_window.clear();
					pause_window.draw(pause_window_background);
					pause_window.draw(back_key2);
					pause_window.draw(paused);
					pause_window.draw(instruction);
					pause_window.display();
					
					sf::Vector2i mouse_position = sf::Mouse::getPosition(pause_window);
					if (mouse_position.x >= 75 && mouse_position.x <= 125 && mouse_position.y >= 30 && mouse_position.y <= 80) {
						if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
							selection.play();
							pause_window.close();
						}
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
						selection.play();
						pause_window.close();
					}
				}
			}
		}
		//Checking if lives are not zero
		if (lives <= 0) {
			window.close();
		}

		//Keeping Enemies in Boundary
		if (enemy.getPosition().x + 70 >= 1915) {
			float random = static_cast<float>(5 + (rand() % 1845));
			enemy.setPosition(sf::Vector2f(random, y_coord));
		}

		//SHOOT LASER
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
			fired = true;
			//pew.play();
		}

		//JET MOVEMENT RIGHT
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
			jet.move(sf::Vector2f(jet_speed, 0.0f));
		}
		
		//JET MOVEMENT LEFT
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
			jet.move(sf::Vector2f(-jet_speed, 0.0f));
		}

		//Keeping Jet In Boundary
		if (jet.getPosition().x - 32.0f < 5.0f) {
			jet.setPosition(sf::Vector2f(37.0f, jet.getPosition().y));
		}
		if (jet.getPosition().x + 32.0f > 1915.0f) {
			jet.setPosition(sf::Vector2f(1883.0f, jet.getPosition().y));
		}
		
		string s = std::to_string(score);
		text_score.setString(s);
		string str_lives = std::to_string(lives);
		text_lives.setString(str_lives);
		str_high_score = std::to_string(high_score);

		window.clear();
		window.draw(background);
		window.draw(line_down);
		window.draw(line_up);
		window.draw(line_left);
		window.draw(line_right);
		window.draw(jet);
		window.draw(enemy);
		window.draw(text_score);
		window.draw(text_lives);
		window.draw(scorer);
		window.draw(t_s);
		window.draw(t_l);
		window.draw(t_h_s);
		window.draw(display_high_score);
		window.draw(high_scorer);
		
		if (fired) {
		window.draw(laser);
		}
		window.display();

		//Enemies movement from top to bottom
		sf::Vector2f enemypos;
		enemypos = enemy.getPosition();
		if (enemypos.y <= 705) {
			enemy.move(sf::Vector2f(0.0f, 0.5f));
		}
		else {
			missed.play();
			random = static_cast<float>(5 + (rand() % 1915));
			enemy.setPosition(sf::Vector2f(random, y_coord));
			lives--;
		}

		//LASER MOVEMENT FROM BOTTOM TO TOP
		if (fired) {
			if (count == 0) {
				laser.setPosition(sf::Vector2f(jet.getPosition().x - 20, jet.getPosition().y - 50));
			}
			count++;
			sf::Vector2f laserpos;
			laserpos = laser.getPosition();
			if (laserpos.y >= 5) {
				laser.move(sf::Vector2f(0.0f, -laser_speed));
			}
			else {
				count = 0;
				sf::Vector2f jetpos;
				jetpos = jet.getPosition();
				laser.setPosition(sf::Vector2f(jetpos.x - 20, jetpos.y - 50));
				fired = false;
			}
		}

		//COLLISION DETECTION

		sf::FloatRect enemyposition;
		enemyposition = enemy.getGlobalBounds();
		enemyposition.height -= 10;
		enemyposition.top += 5;
		enemyposition.left += 9;
		enemyposition.width -= 35;

		sf::FloatRect laserposition;
		laserposition = laser.getGlobalBounds();
		laserposition.height -= 20;
		laserposition.top += 10;
		laserposition.left += 18;
		laserposition.width -= 38;

		if (laserposition.intersects(enemyposition)) {
			random = static_cast<float>(5 + (rand() % 1845));
			enemy.setPosition(sf::Vector2f(random, y_coord));
			sf::Vector2f jetpos;
			jetpos = jet.getPosition();
			laser.setPosition(sf::Vector2f(jetpos.x - 20, jetpos.y - 50));
			score += 10;
			boom.play();
		}
	}

	if (score > high_score_arr[9]) {
		high_score_arr[9] = score;
		high_score_player_names[9] = name;
		high_score_combined[9] = high_score_player_names[9] + to_string(high_score_arr[9]);
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10 - i; j++) {
				if (high_score_arr[j] < high_score_arr[j + 1]) {
					swap(high_score_arr[j], high_score_arr[j + 1]);
					swap(high_score_player_names[j], high_score_player_names[j + 1]);
					swap(high_score_combined[j], high_score_combined[j + 1]);
				}
			}
		}

		write_data_for_high_score(high_score_combined,high_score_player_names,high_score_arr);
		read_data_for_high_score(high_score_combined);
		sorting(high_score_arr, high_score_player_names, high_score_combined);
	}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//GAME OVER WINDOW
	sf::RenderWindow game_over_window(sf::VideoMode(1920.0f, 1001.0f), "GAME OVER", sf::Style::Default | sf::Style::Titlebar | sf::Style::Close|sf::Style::Fullscreen);
	
	//GAME OVER TEXT
	sf::Text game_over_text;
	game_over_text.setFont(font);
	game_over_text.setCharacterSize(220);
	game_over_text.setString("GAME OVER");
	game_over_text.setPosition(sf::Vector2f(570.0f,100.0f));
	game_over_text.Bold;

	//RETRY TEXT BORDER
	sf::RectangleShape retry_border(sf::Vector2f(175.0f,70.0f));
	retry_border.setFillColor(sf::Color::Red);
	retry_border.setPosition(sf::Vector2f(400.0f,517.5f));

	//RETRY TEXT
	sf::Text retry_text;
	retry_text.setFont(font);
	retry_text.setCharacterSize(80);
	retry_text.setString("RETRY");
	retry_text.setPosition(sf::Vector2f(400.0f,500.0f));
	retry_text.Bold;
	retry_text.Italic;

	//QUIT GAME TEXT BORDER
	sf::RectangleShape quit_game_border(sf::Vector2f(140.0f,70.0f));
	quit_game_border.setPosition(sf::Vector2f(1350.0f,515.0f));

	//QUIT GAME TEXT
	sf::Text game_over_quit_text;
	game_over_quit_text.setFont(font);
	game_over_quit_text.setCharacterSize(80);
	game_over_quit_text.setString("QUIT");
	game_over_quit_text.setPosition(sf::Vector2f(1350.0f,500.0f));
	game_over_quit_text.Bold;
	game_over_quit_text.Italic;

	//GAME OVER BACKGROUND
	sf::RectangleShape game_over_background(sf::Vector2f(1920.0f,1001.0f));
	sf::Texture game_over_background_texture;
	game_over_background_texture.loadFromFile("images/Space1.png");
	game_over_background.setTexture(&game_over_background_texture);
	game_over_background.setPosition(sf::Vector2f(0.0f,0.0f));

	//GAME OVER SOUND
	sf::SoundBuffer game_over_buffer;
	game_over_buffer.loadFromFile("sounds/game_over_sound.wav");
	sf::Sound game_over_sound;
	game_over_sound.setBuffer(game_over_buffer);
	game_over_sound.play();

	while (game_over_window.isOpen()) {
		sf::Event evnt;
		while (game_over_window.pollEvent(evnt)) {
			switch (evnt.type) {
				case sf::Event::Closed:
					game_over_window.close();
					return 0;
				break;
			}
		}
		game_over_window.clear();
		game_over_window.draw(game_over_background);
		game_over_window.draw(game_over_text);
		game_over_window.draw(quit_game_border);
		game_over_window.draw(game_over_quit_text);
		game_over_window.draw(retry_border);
		game_over_window.draw(retry_text);
		game_over_window.display();
		
		sf::Vector2i mouse_position = sf::Mouse::getPosition(game_over_window);
		if (mouse_position.x >= 400 && mouse_position.x <= 575 && mouse_position.y >= 517 && mouse_position.y <= 587) {
					retry_border.setFillColor(sf::Color::White);
					read_data_for_settings(laser_speed, jet_speed, lives, str_laser_color_index);
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
						selection.play();
						goto label;
					}
					retry_text.setFillColor(sf::Color::Black);
		}
		else {
			retry_border.setFillColor(sf::Color::Black);
			retry_text.setFillColor(sf::Color::White);
		}
		if (mouse_position.x >= 1350 && mouse_position.x <= 1490 && mouse_position.y >= 515 && mouse_position.y <= 585) {
			quit_game_border.setFillColor(sf::Color::White);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				selection.play();
				game_over_window.close();
			}
			game_over_quit_text.setFillColor(sf::Color::Black);
		}
		else {
			quit_game_border.setFillColor(sf::Color::Black);
			game_over_quit_text.setFillColor(sf::Color::White);
		}
	}
}