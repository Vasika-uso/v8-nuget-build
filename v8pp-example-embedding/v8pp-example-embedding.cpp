#include "../v8pp/context.hpp"
#include <v8pp/libplatform/libplatform.h>
#include <v8pp/v8.h>
#include <iostream>


int main()
{
	v8::V8::InitializeExternalStartupData(R"(C:\Users\user\Downloads\v8pp-1.8.1\v8pp-1.8.1\v8pp-example-embedding)");
	auto platform = v8::platform::NewDefaultPlatform();
	v8::V8::InitializePlatform(platform.get());
	v8::V8::Initialize();
	v8pp::context context;
	v8::HandleScope handleScope(context.isolate());

	auto result = context.run_script(
		"function fib(n) {"
		"if (n == 0) {"
		"return 0;"
		"}"
		"else if (n == 1) {"
		"return 1;"
		"}"

		"return fib(n - 1) + fib(n - 2);"
		"}"

		"fib(8);");

	v8::String::Utf8Value resultString(context.isolate(), result);

	std::cout << "The result of the script was: " << *resultString << "\n";
	v8::V8::Dispose();
	v8::V8::ShutdownPlatform();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
