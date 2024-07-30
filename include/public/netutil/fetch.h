/*
 * netutil
 * Author: bonsall2004
 * Description: Network utility functions for fetching data from URLs.
 */
#pragma once
#include <string>
#include <future>
#include <sstream>

namespace netutil
{
  /**
   * @brief Fetches data from a specified URL.
   *
   * This function retrieves data from the given URL and returns it as a `std::string`.
   * The buffer size determines the initial size of the buffer used for fetching data,
   * and the buffer will be resized if it is exceeded.
   *
   * @param url URL of the resource to fetch.
   * @param buffer_size Initial size of the buffer (default is 4096 bytes). This will be resized if necessary.
   * @return std::string Fetched data as a string.
   *
   * @code{.cpp}
   * std::string data = netutil::fetch("https://example.com/resource", 4096);
   * std::cout << data << '\n';
   * @endcode
   */
  std::string fetch(const std::string& url, uint64_t buffer_size = 4096);

  /**
   * @brief Fetches data from a specified URL and loads it into a stringstream.
   *
   * This function retrieves data from the given URL and writes it into the provided
   * `std::stringstream`. The buffer size determines the initial size of the buffer
   * used for fetching data, and the buffer will be resized if it is exceeded.
   *
   * @param url URL of the resource to fetch.
   * @param data_stream Reference to the `std::stringstream` where the fetched data will be loaded.
   * @param buffer_size Initial size of the buffer (default is 4096 bytes). This will be resized if necessary.
   * @return bool True if the data was fetched and written successfully; otherwise, false.
   *
   * @code{.cpp}
   * std::stringstream data_stream;
   * if (!netutil::fetch_stream("https://example.com/resource", data_stream, 4096)) {
   *     std::cerr << "Failed to fetch data.\n";
   *     return;
   * }
   * std::cout << data_stream.str() << '\n';
   * @endcode
   */
  bool fetch_stream(const std::string& url, std::stringstream& data_stream, uint64_t buffer_size = 4096);

  /**
   * @brief Asynchronously fetches data from a specified URL.
   *
   * This function starts an asynchronous operation to fetch data from the given URL.
   * It returns a `std::future<std::string>` that can be used to retrieve the fetched data
   * once the operation completes. The buffer size determines the initial size of the buffer
   * used for fetching data, and the buffer will be resized if it is exceeded.
   *
   * @param url URL of the resource to fetch.
   * @param buffer_size Initial size of the buffer (default is 4096 bytes). This will be resized if necessary.
   * @return std::future<std::string> Future object that will contain the fetched data once the operation completes.
   *
   * @code{.cpp}
   * auto future_data = netutil::fetch_async("https://example.com/resource", 4096);
   * // Perform other tasks while the data is being fetched
   * std::string data = future_data.get(); // This will block until the data is available
   * std::cout << data << '\n';
   * @endcode
   */
  std::future<std::string> fetch_async(const std::string& url, uint64_t buffer_size = 4096);

  /**
   * @brief Asynchronously fetches data from a specified URL and loads it into a stringstream.
   *
   * This function starts an asynchronous operation to fetch data from the given URL and
   * write it into the provided `std::stringstream`. The buffer size determines the initial size
   * of the buffer used for fetching data, and the buffer will be resized if it is exceeded.
   *
   * @param url URL of the resource to fetch.
   * @param data_stream Reference to the `std::stringstream` where the fetched data will be loaded.
   * @param buffer_size Initial size of the buffer (default is 4096 bytes). This will be resized if necessary.
   * @return std::future<bool> Future object that will be true if the data was fetched and written successfully;
   *                         otherwise, false.
   *
   * @code{.cpp}
   * std::stringstream data_stream;
   * auto future_success = netutil::fetch_stream_async("https://example.com/resource", data_stream, 4096);
   * // Perform other tasks while the data is being fetched
   * bool success = future_success.get(); // This will block until the fetch operation completes
   * if (success) {
   *     std::cout << data_stream.str() << '\n';
   * } else {
   *     std::cerr << "Failed to fetch data.\n";
   * }
   * @endcode
   */
  std::future<bool> fetch_stream_async(const std::string& url, std::stringstream& data_stream, uint64_t buffer_size = 4096);
}
