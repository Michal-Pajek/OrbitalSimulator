#include "app/Application.hpp"
#include "platform/ConsoleEncoding.hpp"

int main()
{
	platform::console::configureUtf8();

	app::Application app{};
	app.eventLoop();
}
