/*
 * netutils
 * Author: bonsall2004
 * Description: 
 */
#include <iostream>
#include <sstream>
#include <netutil/fetch.h> // Adjust the path to your header file

int main() {
  // Define the URL to fetch data from
  std::string url = "https://example.com/resource";
  uint64_t buffer_size = 4096; // Buffer size for fetching data

  // 1. Using netutil::fetch
  try {
    std::string data = netutil::fetch(url, buffer_size);
    std::cout << "Data fetched using netutil::fetch:\n" << data << std::endl;
  } catch (const std::exception& e) {
    std::cerr << "Exception in netutil::fetch: " << e.what() << std::endl;
  }

  // 2. Using netutil::fetch_stream
  std::stringstream data_stream;
  bool success_stream = netutil::fetch_stream(url, data_stream, buffer_size);
  if (success_stream) {
    std::cout << "Data fetched using netutil::fetch_stream:\n" << data_stream.str() << std::endl;
  } else {
    std::cerr << "Failed to fetch data using netutil::fetch_stream.\n";
  }

  // 3. Using netutil::fetch_async
  try {
    auto future_data = netutil::fetch_async(url, buffer_size);
    std::string async_data = future_data.get(); // This will block until data is available
    std::cout << "Data fetched asynchronously using netutil::fetch_async:\n" << async_data << std::endl;
  } catch (const std::exception& e) {
    std::cerr << "Exception in netutil::fetch_async: " << e.what() << std::endl;
  }

  // 4. Using netutil::fetch_stream_async
  std::stringstream async_stream;
  try {
    auto future_success = netutil::fetch_stream_async(url, async_stream, buffer_size);
    bool async_success = future_success.get(); // This will block until the fetch operation completes
    if (async_success) {
      std::cout << "Data fetched asynchronously using netutil::fetch_stream_async:\n" << async_stream.str() << std::endl;
    } else {
      std::cerr << "Failed to fetch data asynchronously using netutil::fetch_stream_async.\n";
    }
  } catch (const std::exception& e) {
    std::cerr << "Exception in netutil::fetch_stream_async: " << e.what() << std::endl;
  }

  return 0;
}
