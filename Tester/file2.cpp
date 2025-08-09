//#include <iostream>
//#include <SFML/Graphics.hpp>
//
//int main(void)
//{
//	const unsigned int width = 800;
//	const unsigned int height = 600;
//	sf::RenderWindow window(sf::VideoMode({ width, height }), "Actual coding first hand");
//
//
//	while (window.isOpen())
//	{
//
//		while (const std::optional event = window.pollEvent())
//		{
//			if (event->is<sf::Event::Closed>())
//			{
//				window.close();
//			}
//			window.clear(sf::Color(0, 0, 0));
//			window.display();
//		}
//
//		// Drawing code goes here in the main loop
//		sf::Texture texture("./Assets/test.png");
//	}
//	return 0;
//}