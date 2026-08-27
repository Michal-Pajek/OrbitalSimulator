#include "app/Application.hpp"
#include "platform/ConsoleEncoding.hpp"

int main()
{
	ConsoleEncoding::configureUtf8();

	app::Application app{};
	app.eventLoop();
}
