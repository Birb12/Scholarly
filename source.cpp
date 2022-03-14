#include "curl/curl.h"
#include "curl/easy.h"
#include <iostream>
#include <string>
#define CURL_STATICLIB
#pragma comment (lib, "Normaliz.lib")
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Wldap32.lib")
#pragma comment (lib, "advapi32.lib")



static size_t write(void* buffer, size_t size, size_t nmemb, void* param)
{
	std::string& text = *static_cast<std::string*>(param);
	size_t totalsize = size * nmemb;
	text.append(static_cast<char*>(buffer), totalsize);
	
	return totalsize;
}

void parser(std::string &result)
{

}

int main()
{
	// declaration
	CURL* curl;
	std::string result;
	CURLcode response;
	std::string url = "https://scholar.google.com/scholar?hl=en&as_sdt=0%2C5&q=psychology&btnG=";


	curl_global_init(CURL_GLOBAL_ALL);

	curl = curl_easy_init(); // initialization
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

		response = curl_easy_perform(curl);
		if (response != CURLE_OK) { // if response isn't "OK"
			std::cout << curl_easy_strerror(response);
		}
		else {
			std::cout << response << std::endl;
		}
		curl_easy_cleanup(curl); // cleanup

		parser(result);
	}
	else { // if Curl doesn't work because it hates me
		throw "Error";
	}

	curl_global_cleanup(); // cleanup
	std::cout << result;
}