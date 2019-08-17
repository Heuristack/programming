#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <yaml-cpp/yaml.h>

int main()
{
  boost::asio::io_service io;

  boost::asio::deadline_timer t(io, boost::posix_time::seconds(5));
  t.wait();

  YAML::Node node  = YAML::LoadFile("itch5.yaml");
  std::cout << node << std::endl;

  return 0;
}
