#include "context.hpp"
#include <libplatform/libplatform.h>
#include <v8.h>
#include <v8-platform.h>
#include <iostream>
#include <direct.h>

#define PATH_MAX        4096 

int main()
{
	std::string externalDataPath;
	{
		char cwd[PATH_MAX];
		_getcwd(cwd, sizeof(cwd));
		externalDataPath = cwd;
	}
	//std::cout << externalDataPath << std::endl;
	v8::V8::InitializeExternalStartupData(externalDataPath.c_str());
	auto platform = v8::platform::CreateDefaultPlatform();
	v8::V8::InitializePlatform(platform);
	{
		v8::V8::Initialize();
		v8pp::context context;
		v8::HandleScope handleScope(context.isolate());

		auto result = context.run_script("var i = 100; return i;");

		v8::String::Utf8Value resultString(context.isolate(), result);

		std::cout << "The result of the script was: " << *resultString << "\n";
		v8::V8::Dispose();
	}
	v8::V8::ShutdownPlatform();
	
}

