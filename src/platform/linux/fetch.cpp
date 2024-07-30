/*
 * netutil
 * Author: bonsall2004
 * Description: 
 */
#include <netutil/fetch.h>
#include <iostream>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

bool netutil::fetch_stream(const std::string& url, std::stringstream& data_stream, uint64_t buffer_size)
{
  std::string host;
  std::string path = "/";

  size_t pos = url.find("://");
  if(pos != std::string::npos)
  {
    pos += 3;
    size_t slash_pos = url.find('/', pos);
    if(slash_pos != std::string::npos)
    {
      host = url.substr(pos, slash_pos - pos);
      path = url.substr(slash_pos);
    }
    else
    {
      host = url.substr(pos);
    }
  }
  else
  {
    host = url;
  }

  struct hostent* server = gethostbyname(host.c_str());
  if(!server)
  {
    return false;
  }

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0)
  {
    return false;
  }

  struct sockaddr_in serv_addr{};
  std::memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(80);
  std::memcpy(&serv_addr.sin_addr.s_addr, server->h_addr_list[0], server->h_length);

  if(connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
  {
    close(sockfd);
    return false;
  }

  std::string request = "GET " + path + " HTTP/1.1\r\n" "Host: " + host + "\r\n" "Connection: close\r\n" "\r\n";

  ssize_t n = write(sockfd, request.c_str(), request.size());
  if(n < 0)
  {
    close(sockfd);
    return false;
  }

  char buffer[buffer_size];
  ssize_t bytes_read;
  bool headers_ended = false;

  while((bytes_read = read(sockfd, buffer, sizeof(buffer))) > 0)
  {
    if(!headers_ended)
    {
      std::string chunk(buffer, bytes_read);
      size_t header_end_pos = chunk.find("\r\n\r\n");
      if(header_end_pos != std::string::npos)
      {
        headers_ended = true;
        data_stream.write(chunk.data() + header_end_pos + 4, bytes_read - (header_end_pos + 4));
      }
      else
      {
        data_stream.write(chunk.data(), bytes_read);
      }
    }
    else
    {
      data_stream.write(buffer, bytes_read);
    }
  }

  if(bytes_read < 0)
  {
    close(sockfd);
    return false;
  }

  close(sockfd);
  return true;
}