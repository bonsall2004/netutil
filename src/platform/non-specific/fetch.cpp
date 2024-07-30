/*
 * netutil
 * Author: bonsall2004
 * Description: 
 */
#include <future>
#include <netutil/fetch.h>

std::string netutil::fetch(const std::string& url, uint64_t buffer_size)
{
  std::stringstream data_stream;
  bool result = fetch_stream(url, data_stream, buffer_size);
  if(!result) return "";
  else return data_stream.str();
}

std::future<std::string> netutil::fetch_async(const std::string& url, uint64_t buffer_size)
{
  return std::async(std::launch::async, fetch, url, buffer_size);
}

std::future<bool> netutil::fetch_stream_async(const std::string& url, std::stringstream& data_stream, uint64_t buffer_size)
{
  return std::async(std::launch::async, fetch_stream, url, std::ref(data_stream), buffer_size);
}