/*
 * netutil
 * Author: bonsall2004
 * Description: 
 */
#include <netutil/fetch.h>
#include <windows.h>
#include <wininet.h>
#include <vector>

bool netutil::fetch_stream(const std::string& url, std::stringstream& data_stream, uint64_t buffer_size)
{
  HINTERNET h_internet = InternetOpen("netutil fetch", INTERNET_OPEN_TYPE_DIRECT, nullptr, nullptr, 0);
  if(!h_internet)
  {
    return false;
  }

  HINTERNET h_connect = InternetOpenUrlA(h_internet, url.c_str(), nullptr, 0, INTERNET_FLAG_RELOAD, 0);
  if(!h_connect)
  {
    return false;
  }

  std::vector<char> buffer(buffer_size);
  DWORD bytes_read = 0;

  while(InternetReadFile(h_connect, buffer.data(), buffer.size(), &bytes_read) && bytes_read > 0)
  {
    data_stream.write(buffer.data(), bytes_read);

    if(bytes_read >= buffer.size())
    {
      buffer.resize(buffer.size() + (buffer.size() / 2));
    }
  }

  InternetCloseHandle(h_connect);
  InternetCloseHandle(h_internet);
  return true;
}
